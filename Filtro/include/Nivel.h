#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_adc_cal.h"

#define DEFAULT_VREF    1100        // Valor de referência da tensão em mV (use o valor adequado para o seu ESP32)
#define Sensor_Nivel    ADC1_CHANNEL_4    // Canal ADC1_4 corresponde ao pino D32 (GPIO 32)
#define Saida_Nivel     GPIO_NUM_2


void setup_nivel(){
    // Configuração do ADC
    adc1_config_width(ADC_WIDTH_BIT_12);                      // Configura a largura de 12 bits para a resolução do ADC
    adc1_config_channel_atten(Sensor_Nivel, ADC_ATTEN_DB_11);  // Configura a atenuação para a entrada analógica
    gpio_pad_select_gpio(Saida_Nivel);
    gpio_set_direction(Saida_Nivel, GPIO_MODE_OUTPUT);
}
