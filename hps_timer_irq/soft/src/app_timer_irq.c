/*****************************************************************************************
 * HEIG-VD
 * Haute Ecole d'Ingenerie et de Gestion du Canton de Vaud
 * School of Business and Engineering in Canton de Vaud
 *****************************************************************************************
 * REDS Institute
 * Reconfigurable Embedded Digital Systems
 *****************************************************************************************
 *
 * File                 : app_timer_irq.c
 * Author               : Anthony Convers
 * Date                 : 27.10.2022
 *
 * Context              : ARE lab
 *
 *****************************************************************************************
 * Brief: Using timer IRQ on DE1-SoC board
 *
 *****************************************************************************************
 * Modifications :
 * Ver    Date        Student      Comments
 * 0.0    27.10.2022  ACS           Initial version.
 *
 *****************************************************************************************/
#include "app_timer_irq.h"

#include <stdio.h>
#include "axi_lw.h"
#include "exceptions.h"
#include "pio_function.h"

int __auto_semihosting;

static uint32_t timer = 0;
static bool timerActive = 0;

static int lastLED = 0x0;

int main(void)
{

    disable_A9_interrupts();

    set_A9_IRQ_stack();

    // Configure the timer
    config_GIC();

    // Initialisation des PIO
    Leds_init();
    Keys_init();
    Switchs_init();
    Segs7_init();

    enable_A9_interrupts();

    printf("Laboratoire: Timer IRQ \n");

    // Test de la constante
    printf("constanteID: 0x%X\n", (unsigned int)AXI_LW_REG(0));

    while (1)
    {
        // Read the switches 7-0
        uint32_t switches = Switchs_read() & 0xFF;
        uint32_t leds = 0x0;

        // Read the keys
        bool key0 = Key_read(0);
        bool key1 = Key_read(1);
        bool key2 = Key_read(2);

        // Start the timer
        if (key0)
        {
            timerActive = 1;
        }

        // Stop the timer
        if (key1)
        {
            timerActive = 0;
        }

        if(timerActive){
            leds |= (1 << 8);
        }

        if (timerActive && timer > 0 && go)
        {
            go = 0;

            lastLED ^= (1 << 9);
            leds |= lastLED;

            timer--;
        }

        // Set start value
        if (key2)
        {
            timer = switches * 10;
        }

        Leds_write(leds);

        // Show the timer value on the 7-segments display
        Seg7_write_hex(0, timer % 10);
        Seg7_write_hex(1, (timer / 10) % 10);
        Seg7_write_hex(2, (timer / 100) % 10);
        Seg7_write_hex(3, (timer / 1000) % 10);
    }
}
