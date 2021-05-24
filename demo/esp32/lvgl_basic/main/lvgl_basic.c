// Copyright 2015-2021 Espressif Systems (Shanghai) CO LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "assert.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lvgl.h"
#include "lvgl_helpers.h"

#define TAG "LVGL"

#define LV_TICK_PERIOD_MS 1
static void lvgl_tick_task(void *arg)
{
    (void) arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

void bsp_display_task(void *pvParameter)
{
    lv_init();

    /* Initialize SPI or I2C bus used by the drivers */
    lvgl_driver_init();

    lv_color_t *buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1 != NULL);

    /* Use double buffered when not working with monochrome displays */
    lv_color_t *buf2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2 != NULL);

    static lv_disp_buf_t disp_buf;
    lv_disp_buf_init(&disp_buf, buf1, buf2, DISP_BUF_SIZE);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lvgl_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t lvgl_tick_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, LV_TICK_PERIOD_MS * 1000));

    /* Notify parent task that LVGL is ready, if parent task is provided */
    if (pvParameter != NULL) {
        xTaskNotifyGive((TaskHandle_t)pvParameter);
    }

    while (1) {
        lv_task_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    /* This task should NEVER return */
    esp_timer_stop(lvgl_tick_timer);
    esp_timer_delete(lvgl_tick_timer);
    free(buf1);
    free(buf2);
    vTaskDelete(NULL);
}

void app_main(void)
{
    TaskHandle_t bsp_display_task_handle;
    int ret = xTaskCreate(bsp_display_task, "bsp_display", 4096 * 2, xTaskGetCurrentTaskHandle(), 3, &bsp_display_task_handle);
    assert(ret == pdPASS);

    /* Wait until LVGL is ready */
    if (ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000))) {
        vTaskSuspend(bsp_display_task_handle);

    /*Create a window*/
    lv_obj_t * win = lv_win_create(lv_scr_act(), NULL);
    /*Set the title*/
    lv_win_set_title(win, "ESP32 LVGL Blink Example");

    /*Create a LED and switch it OFF*/
    lv_obj_t * led  = lv_led_create(lv_scr_act(), NULL);
    lv_obj_align(led, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_led_set_bright(led, LV_LED_BRIGHT_MAX);
    lv_led_off(led);
    // lv_led_on(led);

        vTaskResume(bsp_display_task_handle);
    } else {
        ESP_LOGW(TAG, "LVGL init timed out");
    }
}
