// DADOS DE AUTENTIFICAÇÃO WIFI
#if CONFIG_ESP_WPA3_SAE_PWE_HUNT_AND_PECK
#define ESP_WIFI_SAE_MODE WPA3_SAE_PWE_HUNT_AND_PECK
#define EXAMPLE_H2E_IDENTIFIER ""
#elif CONFIG_ESP_WPA3_SAE_PWE_HASH_TO_ELEMENT
#define ESP_WIFI_SAE_MODE WPA3_SAE_PWE_HASH_TO_ELEMENT
#define EXAMPLE_H2E_IDENTIFIER CONFIG_ESP_WIFI_PW_ID
#elif CONFIG_ESP_WPA3_SAE_PWE_BOTH
#define EXAMPLE_H2E_IDENTIFIER CONFIG_ESP_WIFI_PW_ID
#endif
#if CONFIG_ESP_WIFI_AUTH_OPEN
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
#elif CONFIG_ESP_WIFI_AUTH_WEP
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WEP
#elif CONFIG_ESP_WIFI_AUTH_WPA_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WAPI_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WAPI_PSK
#endif

int modo_auto = 0;
int Quantidade_encher = 0;
double altura_agua = 2;
double area_Valvula = 0.000126;
int Tempo_encher = 0;
float G = 9.8;
float ml_sec = 5;

int calcularTempoEnchimento(double alturaColunaAgua, double areaSaidaValvula, double quantidadeAgua)
{
    // Cálculo da velocidade de saída usando a equação de Torricelli
    double velocidadeSaida = sqrt(2 * G * alturaColunaAgua);

    // Cálculo da taxa de vazão
    double taxaVazao = areaSaidaValvula * velocidadeSaida;

    // Cálculo do tempo necessário para encher a quantidade de água desejada
    int tempo = quantidadeAgua / taxaVazao;
    tempo = tempo* 1000;
    
    return tempo;
}

void Manipular_POST(char *web)
{
    sscanf(web, "{\"Quantidade\":\"%d\"}", &Quantidade_encher);
    //printf("Quantidade_encher:%d\n", Quantidade_encher);
    Tempo_encher = calcularTempoEnchimento(altura_agua,area_Valvula,Quantidade_encher);
    //printf("Tempo_encher:%d\n", Tempo_encher);
}

