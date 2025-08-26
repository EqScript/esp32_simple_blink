/*
 *  @brief Simple single blinking LED project
 *  @file main.c
 *  @date 2021-07-20
 *  @author Sergio EqScript Belenkoff
 *  @version 0.1
 */

#include <stdint.h>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_task_wdt.h"

const char* TAG = "SIMPLE BLINKER";

#define LED_PIN 2
#define TIMES_TO_BLINK 10
#define BLINK_PERIOD_MS 500


void app_main() {
    uint64_t currentTimeMs      = 0;
    uint64_t lastTimeMs         = 0;
    size_t blinksCounter    = 0;
    bool ledState = false;

    // Pin setup
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // ESP Log level setLog level across the module
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    ESP_LOGI(TAG, "Starting blinking...");


    while(true) {
        currentTimeMs = (uint64_t) (esp_timer_get_time() / 1000); // us to ms divider

        if (currentTimeMs - lastTimeMs >= BLINK_PERIOD_MS) {
            lastTimeMs = currentTimeMs;
            
            if (ledState == false) {
                ledState = true;            // LED TOGGLING ON
                blinksCounter++;
                ESP_LOGD(TAG, "LED state: %d", ledState);
            } else {
                ledState = false;           // LED TOGGLING OFF
                ESP_LOGD(TAG, "LED state: %d", ledState);
            }

            if (blinksCounter >= TIMES_TO_BLINK) {
                break;                      // Blinking done, exit loop
            }
        }
        esp_task_wdt_reset(NULL); // WatchDog reset

    } // while

    ESP_LOGI(TAG, "Blinking done! Blinked %u times...", blinksCounter);
    
} // main