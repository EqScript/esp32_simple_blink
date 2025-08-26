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

#define TIMES_TO_BLINK 10
#define BLINK_PERIOD_MS 500
const gpio_num_t LED_PIN = GPIO_NUM_1; //  IO1/2 == DR1/2


void app_main() {
    uint64_t currentTimeMs      = 0;
    uint64_t lastTimeMs         = 0;
    size_t blinksCounter        = 0;
    bool ledState = false;

    // Pin setup
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // ESP Log level setLog level across the module
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    ESP_LOGI(TAG, "Starting blinking...");

 

    while(true) {
        currentTimeMs = (uint64_t) (esp_timer_get_time() / 1000); // us to ms divider
        ESP_LOGV(TAG, "Current time: %" PRIu64 " ms", currentTimeMs);

        if (currentTimeMs - lastTimeMs >= BLINK_PERIOD_MS) {
            // Ok, it's time to blink

            // Updating last time we blinked
            lastTimeMs = currentTimeMs;

            if (ledState == false) {
                ledState = true;            // LED TOGGLING ON
                gpio_set_level(LED_PIN, ledState);
                blinksCounter++;
                ESP_LOGD(TAG, "LED state: %d, counter: %u", ledState, blinksCounter);
            } else {
                ledState = false;           // LED TOGGLING OFF
                gpio_set_level(LED_PIN, ledState);
                ESP_LOGD(TAG, "LED state: %d", ledState);
            }

            if (blinksCounter >= TIMES_TO_BLINK) {
                break;                      // Blinking done, exit loop
            }
        }
        vTaskDelay(1); // Feeding the Watch Dog

    } // while

    ESP_LOGI(TAG, "Blinking done! Blinked %u times...", blinksCounter);

} // main