#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_timer.h>

#define TRIGGER_PIN GPIO_NUM_27
#define ECHO_PIN    GPIO_NUM_26
#define Saida_Copo  GPIO_NUM_4

void setup_distancia()
{
    gpio_pad_select_gpio(TRIGGER_PIN);
    gpio_pad_select_gpio(ECHO_PIN);
    gpio_set_direction(TRIGGER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(ECHO_PIN, GPIO_MODE_INPUT);
    gpio_pad_select_gpio(Saida_Copo);
    gpio_set_direction(Saida_Copo, GPIO_MODE_OUTPUT);
}

float calculo_distancia()
{
    gpio_set_level(TRIGGER_PIN, 1);
    ets_delay_us(10000);
    gpio_set_level(TRIGGER_PIN, 0);

    uint32_t start_time = 0;
    uint32_t echo_time = 0;
    while (gpio_get_level(ECHO_PIN) == 0)
    {
        start_time = xthal_get_ccount();
    }
    while (gpio_get_level(ECHO_PIN) == 1)
    {
        echo_time = xthal_get_ccount() - start_time;
    }

    // Convertendo o tempo de eco para centímetros
    float distance_cm = (echo_time * 34300.0) / (2.0 * CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ * 100.0);

    return distance_cm;
}



