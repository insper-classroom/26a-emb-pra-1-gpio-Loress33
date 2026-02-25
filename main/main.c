/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN_PIN = 28;
const int LED_PIN = 5;
const int MTR_PINS[4] = {14, 15, 16, 17};

int main() {
    stdio_init_all();

    int n_steps = 2048;
    int ligados[4] = {0, 0, 0, 0};

    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_pull_up(LED_PIN);

    for (int i = 0; i < 4; i++) {
        gpio_init(MTR_PINS[i]);
        gpio_set_dir(MTR_PINS[i], GPIO_OUT);
        gpio_put(MTR_PINS[i], 0);
    }

    while (true) {
        if (!gpio_get(BTN_PIN)) {
            gpio_put(LED_PIN, 1);
            sleep_ms(300);

            for(int i = 0; i < n_steps; i++) {
                for (int j = 0; j < 4; j++) {
                    if (ligados[j]) {
                        gpio_put(MTR_PINS[j], 0);
                        ligados[j] = 0;
                    } else {
                        gpio_put(MTR_PINS[j], 1);
                        ligados[j] = 1;
                    }
                    sleep_ms(10);
                }
            }   

            gpio_put(LED_PIN, 0);
        }
    }
}
