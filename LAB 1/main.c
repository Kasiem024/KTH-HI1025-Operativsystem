#include "FreeRTOS.h" /* Must come first. */
#include "task.h"     /* RTOS task related API prototypes. */

#include "gd32vf103.h" // Main MCU API header
#include "drivers.h"   // LED Panel & Keyboard driver API
// #include "lcd.h"      // LCD Panel driver API

void ledPanel(void *pvParameters)
{ // The Led Panel Task:
    while (1)
    {                     // Led Panel Super Loop...
        l88row(colset()); // ...show next row...
        vTaskDelay(1);    // ...wait 2ms and repeat!
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

    // Start the Scheduler!
    vTaskStartScheduler();
    // Should not reach here...

    while (1)
        ; // ...to be sure!
}
