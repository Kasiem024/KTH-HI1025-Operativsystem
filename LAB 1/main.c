#include "FreeRTOS.h" /* Must come first. */
#include "task.h"     /* RTOS task related API prototypes. */

#include "gd32vf103.h" // Main MCU API header
#include "drivers.h"   // LED Panel & Keyboard driver API
// #include "lcd.h"      // LCD Panel driver API

void ledPanel(void *pvParameters)
{ // The Led Panel Task:
    // volatile char data[1800];
    while (1)
    {                     // Led Panel Super Loop...
        l88row(colset()); // ...show next row...
        vTaskDelay(1);    // ...wait 2ms and repeat!

        l88mem(0, 0);
        // l88mem(1, 1);
        // l88mem(2, 2);
        // l88mem(3, 3);
        l88mem(4, 0);
        l88mem(5, 0);
        l88mem(6, 0);
        l88mem(7, 0);

    } // (Must not terminate)
}

void ledTask(void *pvParameters)
{
    int delay = (int)pvParameters * 500, counter = (int)pvParameters, LEDCol = (int)pvParameters;

    while (1)
    { // Led Panel Super Loop...
        l88mem(LEDCol, counter++);

        vTaskDelay(delay); // ...wait 2+id ms and repeat!
    } // (Must not terminate)
}

int main(void)
{
    int id[4] = {0, 1, 2, 3};

    // Perform any driver setup necessary...
    colinit(); // Initialize column toolbox
    l88init(); // Initialize 8*8 led toolbox

    // Create (initially) needed application tasks...
    xTaskCreate(ledPanel, "LED", 512, (void *)NULL, 2, NULL);
    xTaskCreate(ledTask, "LEDTask1", 512, (void *)id[1], 1, NULL);
    xTaskCreate(ledTask, "LEDTask2", 512, (void *)id[2], 1, NULL);
    xTaskCreate(ledTask, "LEDTask3", 512, (void *)id[3], 1, NULL);

    // Start the Scheduler!
    vTaskStartScheduler();
    // Should not reach here...

    while (1)
        ; // ...to be sure!
}