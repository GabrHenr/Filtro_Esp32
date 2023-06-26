#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Nivel.h"
#include "Distancia.h"
#include <stdlib.h>
#include "esp_task_wdt.h"



// Função da primeira tarefa
void nivel(void *pvParameters)
{
    // Setup do sensor de nível
    setup_nivel();
    int limite_nivel_MIN = 1500;
    int limite_nivel_MAX = 300;
    // Calibração do ADC
    esp_adc_cal_characteristics_t Nivel_bias;
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, DEFAULT_VREF, &Nivel_bias);
    int flag_nivel = 0;
    for (;;)
    {
        // Realiza a leitura do valor analógico
        uint32_t Sensor_nivel = 0;
        int i=0;
        // loop
        while (i<10)
        {
            Sensor_nivel += adc1_get_raw(Sensor_Nivel);
            i+=1;
            vTaskDelay(10 / portTICK_PERIOD_MS); // Aguarda 0.1 segundo
        }
        //Média das leituras
         Sensor_nivel =  Sensor_nivel / i;
        // Realiza a conversão do valor analógico para tensão em mV
        uint32_t voltage_Nivel = esp_adc_cal_raw_to_voltage(Sensor_nivel, &Nivel_bias);
        //printf("Distancia no sensor nivel:%u\n", voltage_Nivel);
        // converter uint para int
        int Nivel = voltage_Nivel;
        if (Nivel < limite_nivel_MAX && flag_nivel == 0)
        {
            // ligar a saída de agua para o filtro
            //printf("Ligando a saida de agua para o filtro\n");
            gpio_set_level(Saida_Nivel, 1);    // Define o pino 2 como HIGH (nível lógico alto)

            flag_nivel = 1;
        }
        else if (Nivel >= limite_nivel_MIN && flag_nivel == 1)
        {
            // desligar a saída de agua  para o filtro
            //printf("Desligando a saida de agua para o filtro\n");
            gpio_set_level(Saida_Nivel, 0);    // Define o pino 4 como LOW (nível lógico baixo)
            flag_nivel = 0;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS); // Aguarda 1 segundo
    }
}

// Função da segunda tarefa
void copo(void *pvParameters)
{
    setup_distancia();
    int distancia;
    int limite_copo_Ativar = 5;
    int limite_copo_Desativar = 6;
    for (;;)
    {
        distancia = calculo_distancia() / 10000 ;
        printf("Distancia no sensor copo cm:%d\n", distancia);
        //printf("Tempo_encher = %d\n", Tempo_encher);
        if (modo_auto == 0)
        {
            if (distancia <= limite_copo_Ativar)
            {
                // ligar a saída de agua para o copo
                printf("Ligando a saida de agua para o copo\n");
                gpio_set_level(Saida_Copo, 1);    // Define o pino 2 como LOW (nível lógico baixo)
            }
            else if (distancia > limite_copo_Desativar)
            {
                // desligar a saída de agua  para o copo
                printf("Desligando a saida de agua para o copo\n");
                gpio_set_level(Saida_Copo, 0);    // Define o pino 4 como HIGH (nível lógico alto)
            }
        }
        else if (modo_auto ==1 && Tempo_encher != 0)
        {
            
            if (distancia <= limite_copo_Ativar)
            {
                // ligar a saída de agua para o copo
                printf("-----------Ligando a saida de agua para o copo para quantidade\n");
                gpio_set_level(Saida_Copo, 1);    // Define o pino 2 como LOW (nível lógico baixo)
                vTaskDelay(Tempo_encher / portTICK_PERIOD_MS); // Aguarda ms
                gpio_set_level(Saida_Copo, 0);    // Define o pino 4 como HIGH (nível lógico alto)
                printf("-----------Desligando a saida de agua para o copo para quantidade\n");
                Tempo_encher = 0;
                modo_auto = 0;
            }
            gpio_set_level(Saida_Copo, 0);    // Define o pino 4 como HIGH (nível lógico alto)
        }
        vTaskDelay(100 / portTICK_PERIOD_MS); // Aguarda 0.1 segundos
    }
}

void tasks()
{
    // Desativar o watchdog
    esp_task_wdt_deinit();
    //printf("Iniciar nivel\n");
    xTaskCreate(&nivel, "Controle de nivel", 5000, NULL, 1, NULL); // Cria a tarefa 1
    //printf("Iniciar copo\n");
    xTaskCreate(&copo, "Encher automatico", 5000, NULL, 2, NULL);  // Cria a tarefa 2
}