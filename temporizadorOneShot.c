#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

/* Desenvolvedor: Marco Túlio Macêdo Oliveira dos Santos */

// Definição dos pinos para conexão com as GPIOs correspondentes ao LED RGB
#define LED_R_PIN 12
#define LED_G_PIN 13
#define LED_B_PIN 11

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

    gpio_pull_up(BTN_A_PIN); // Habilita resistor de pull-up para o botão
}

// Tabela de controle dos LEDs (cada bit representa um LED)
uint8_t leds_control[4] = {
    0b111,  // Todos acesos
    0b011,  // Verde e vermelho acesos
    0b001,  // Apenas vermelho aceso
    0b000   // Todos apagados
};

uint8_t state = 3; // Estado inicial (todos os LEDs apagados)

/*
* Atualiza os LEDs com base no estado atual
*/ 
void set_state() {
    gpio_put(LED_B_PIN, (leds_control[state] >> 2) & 1);
    gpio_put(LED_R_PIN, (leds_control[state] >> 1) & 1);
    gpio_put(LED_G_PIN, (leds_control[state] >> 0) & 1);
}

/*
* Callback para apagar os LEDs gradualmente
*/  
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    state++;    // Avança para o próximo estado
    set_state(); // Atualiza os LEDs
    return 0;   // Não agenda novos alarmes, pois já estão programados no loop principal
}

int main() {
    stdio_init_all();
    init();

    while (true) {
        // Verifica se o botão foi pressionado e os LEDs estão apagados
        if (gpio_get(BTN_A_PIN) == 0 && state == 3) {
            sleep_ms(50); // Pequeno atraso para debounce do botão
            if (gpio_get(BTN_A_PIN) == 0) { // Confirma que o botão ainda está pressionado
                state = 0; // Inicia sequência de acendimento
                set_state();

                // Programa os timers para desligar os LEDs em sequência
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
                add_alarm_in_ms(6000, turn_off_callback, NULL, false);
                add_alarm_in_ms(9000, turn_off_callback, NULL, false);
            }
        }
        sleep_ms(100); // Reduz o uso da CPU no loop principal
    }
}
