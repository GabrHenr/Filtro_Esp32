#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "esp_http_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Backend.h"
#include "WEB.h"
#include "WIFI.h"
#include "Tasks.h"


/* Tarefa principal */
void app_main()
{
    // Variável para desligar modo auto
    
    // Inicializa NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    wifi_init_sta();
    start_webserver();
    tasks();
}
