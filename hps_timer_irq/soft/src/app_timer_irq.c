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
#include "pio_function.h"

#include "exceptions.h"

extern bool timerGo;

int __auto_semihosting;

int main(void)
{

    uint32_t timer = 0;
    uint32_t lastLED = 0;
    uint32_t ledAtStart = 0;

    disable_A9_interrupts();

    set_A9_IRQ_stack();

    // Configure the timer
    config_GIC();

    config_timer();

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
        uint32_t leds = 0;

        // Read the keys
        bool key0 = Key_read(0);
        bool key1 = Key_read(1);
        bool key2 = Key_read(2);

        // Start the timer
        if (key0)
        {
            start_timer();

            // Set led 8
            lastLED |= (1 << 8);
        }

        // Stop the timer
        if (key1)
        {
            stop_timer();

            // Remove led 8
            lastLED &= ~(1 << 8);
        }

        if (timerGo && timer > 0)
        {
            timer--;
            timerGo = 0;

            lastLED ^= (1 << 9);
        }

        leds |= lastLED;

        // Set start value
        if (key2)
        {
            timer = switches * 10;
            ledAtStart = switches;
        }

        leds |= ledAtStart;

        Leds_write(leds);

        // Show the timer value on the 7-segments display
        Seg7_write_hex(0, timer % 10);
        Seg7_write_hex(1, (timer / 10) % 10);
        Seg7_write_hex(2, (timer / 100) % 10);
        Seg7_write_hex(3, (timer / 1000) % 10);
    }
}
