#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos para conexão com as GPIOs correspondentes ao LED RGB;
#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12

// Definição da GPIO em que o botão A está conectado
#define BTN_A_PIN 5

/*
* Função para inicialização das GPIOs
*/
void init() {
    gpio_init(LED_R_PIN);
    gpio_init(LED_G_PIN);
    gpio_init(LED_B_PIN);
    gpio_init(BTN_A_PIN);

    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);

    gpio_pull_up(BTN_A_PIN);
}

int64_t turn_off_callback(alarm_id_t id, void *user_data) {}


int main() {
    stdio_init_all();
    init();

    while (true) {
        if(gpio_get(BTN_A_PIN) == 0) {
            sleep_ms(50);
            if(gpio_get(BTN_A_PIN) == 0) {
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            }
        }
        sleep_ms(10);
    }
}
