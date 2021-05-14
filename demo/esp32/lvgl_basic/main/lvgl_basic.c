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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"

#include "esp_log.h"

/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_helpers.h"

const static char *TAG = "LVGL";


void app_main(void)
{
    // TaskHandle_t bsp_display_task_handle;
    // int ret = xTaskCreate(bsp_display_task, "bsp_display", 4096 * 2, xTaskGetCurrentTaskHandle(), 3, &bsp_display_task_handle);
    // assert(ret == pdPASS);

    // /* Wait until LVGL is ready */
    // if (ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000))) {
    //     vTaskSuspend(bsp_display_task_handle);
    //     /*Create a window*/
    //     lv_obj_t *win = lv_win_create(lv_scr_act(), NULL);
    //     lv_win_set_title(win, "ESP-WROVER-KIT:\nBoard Support Package example");
    //     lv_win_set_scrollbar_mode(win, LV_SCROLLBAR_MODE_OFF);

    //     /* Container */
    //     lv_obj_t *cont = lv_cont_create(win, NULL);
    //     lv_cont_set_fit(cont, LV_FIT_TIGHT);
    //     lv_cont_set_layout(cont, LV_LAYOUT_COLUMN_LEFT);

    //     /* Checkboxes */
    //     lv_obj_t *recording_checkbox = lv_checkbox_create(cont, NULL);
    //     lv_checkbox_set_text(recording_checkbox, "Checkbox 1");
    //     lv_obj_t *playing_checkbox = lv_checkbox_create(cont, NULL);
    //     lv_checkbox_set_text(playing_checkbox, "Checkbox 2");

    //     vTaskResume(bsp_display_task_handle);
    // } else {
    //     ESP_LOGW(TAG, "LVGL init timed out");
    // }
}
