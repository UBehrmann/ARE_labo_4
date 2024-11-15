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
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "axi_lw.h"
#include "exceptions.h"
#include "pio_function.h"

int __auto_semihosting;

int main(void){

    printf("Laboratoire: Timer IRQ \n");

    // Test de la constante
    printf("constanteID: 0x%X\n", (unsigned int)AXI_LW_REG(0));

    // Initialisation des PIO
    Leds_init();
    Keys_init();
    Switchs_init();
    Segs7_init();

    // Configure the timer
    config_GIC();

    // Configure IOs
    
    while(1);

}
