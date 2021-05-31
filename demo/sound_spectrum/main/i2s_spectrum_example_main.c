/* I2S Digital Microphone Spectrum Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include <math.h>
#include "esp_log.h"
#include "esp_dsp.h"

static const char* TAG = "PDM_MIC";

#define AUDIO_SAMPLE_RATE       (16000)
#define PDM_MIC_CLK_IO          (22)
#define PDM_MIC_DATA_IO         (23)
#define I2S_CH                  I2S_NUM_0
#define SAMPLES_NUM             (1024)

float wind[SAMPLES_NUM];
float y_cf[SAMPLES_NUM*2];
float* y1_cf = &y_cf[0];

static void init_microphone(void) 
{
    // Configure the I2S peripheral for the PDM microphone
    i2s_config_t i2s_config = {
        .mode = I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM,
        .sample_rate = AUDIO_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 256,
    };

    // Set the Clock and Data pins
    i2s_pin_config_t pin_config;
    pin_config.bck_io_num = I2S_PIN_NO_CHANGE;
    pin_config.ws_io_num = PDM_MIC_CLK_IO;
    pin_config.data_out_num = I2S_PIN_NO_CHANGE;
    pin_config.data_in_num = PDM_MIC_DATA_IO;
    
    i2s_driver_install(I2S_CH, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_CH, &pin_config);
    i2s_set_clk(I2S_CH, AUDIO_SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);
}

static void init_fft(void)
{
    // Init the FFT
    esp_err_t ret;
    ESP_LOGI(TAG, "FFT Initialization");
    ret = dsps_fft2r_init_fc32(NULL, CONFIG_DSP_MAX_FFT_SIZE);
    if (ret  != ESP_OK)
    {
        ESP_LOGE(TAG, "Not possible to initialize FFT. Error = %i", ret);
        return;
    }
}

static void fft_process_and_show(float* data, int length)
{
    // Complex FFT of radix 2 
    dsps_fft2r_fc32(data, length);
    // Bit reverse 
    dsps_bit_rev_fc32(data, length);
    // Convert one complex vector to two complex vectors
    dsps_cplx2reC_fc32(data, length);

    for (int i = 0 ; i < length/2 ; i++) {
        data[i] = 10 * log10f((data[i * 2 + 0] * data[i * 2 + 0] + data[i * 2 + 1] * data[i * 2 + 1])/SAMPLES_NUM);
    }

    // Show power spectrum in 64x10 window
    dsps_view_spectrum(data, length/2, 30, 100);
}

static void spectrum_task_example(void* arg)
{
    static int16_t i2s_readraw_buff[SAMPLES_NUM];
    size_t bytesread;
    
    while (1) {
        // Read data from the microphone output
        i2s_read(I2S_CH, (char *)i2s_readraw_buff, SAMPLES_NUM * 2, &bytesread, (100 / portTICK_RATE_MS));
        // Convert two input vectors to one complex vector
        for (int i=0 ; i< SAMPLES_NUM ; i++)
        {
            y_cf[i*2 + 0] = i2s_readraw_buff[i];
            y_cf[i*2 + 1] = 0;
        }
        // Create the spectrum bars visualization
        fft_process_and_show(y_cf, SAMPLES_NUM);
        vTaskDelay(50/portTICK_RATE_MS);
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "PDM microphone Example start");

    // Init the PDM digital microphone
    init_microphone();
    // Init the FFT library
    init_fft();

    // Create audio processing task for FFT and spectrum analyzer
    xTaskCreate(spectrum_task_example, "spectrum_task_example", 2048, NULL, 10, NULL);
}
