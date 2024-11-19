/*****************************************************************************************
 * HEIG-VD
 * Haute Ecole d'Ingenerie et de Gestion du Canton de Vaud
 * School of Business and Engineering in Canton de Vaud
 *****************************************************************************************
 * REDS Institute
 * Reconfigurable Embedded Digital Systems
 *****************************************************************************************
 *
 * File                 : pio_function.c
 * Author               : 
 * Date                 : 
 *
 * Context              : ARE lab
 *
 *****************************************************************************************
 * Brief: Pio function
 *
 *****************************************************************************************
 * Modifications :
 * Ver    Date        Student      Comments
 * 1.0    11.10.24    Urs Behrmann
 *
*****************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "pio_function.h"
#include <stdio.h>


void Switchs_init(void){

    // Set R/W direction
    volatile uint32_t pio0_dir = PIO0_REG(REG_DIR);
    pio0_dir &= ~SWITCHS_BITS;
    PIO0_REG(REG_DIR) = pio0_dir;
}

void Leds_init(void){
    
    // Set R/W direction
    volatile uint32_t pio0_dir = PIO0_REG(REG_DIR);
    pio0_dir |= LEDS_BITS;
    PIO0_REG(REG_DIR) = pio0_dir;
}

void Keys_init(void){
    
    // Set R/W direction
    volatile uint32_t pio0_dir = PIO0_REG(REG_DIR);
    pio0_dir &= ~KEYS_BITS;
    PIO0_REG(REG_DIR) = pio0_dir;
}

void Segs7_init(void){
        
    // Set R/W direction
    volatile uint32_t pio1_dir = PIO1_REG(REG_DIR);
    pio1_dir |= HEX0_BITS | HEX1_BITS | HEX2_BITS | HEX3_BITS;
    PIO1_REG(REG_DIR) = pio1_dir;
}

uint32_t Switchs_read(void){
    
    uint32_t value = PIO0_REG(REG_BASE) & SWITCHS_BITS;

    return (value >> SWITCHS_OFFSET) & 0x3ff;
}

void Leds_write(uint32_t value){

    uint32_t valueToSend = value << LEDS_OFFSET;
        
    PIO0_REG(REG_BASE) = (PIO0_REG(REG_BASE) & ~LEDS_BITS) | (valueToSend & LEDS_BITS);
}

void Leds_set(uint32_t maskleds){

	uint32_t maskledToSend = maskleds << LEDS_OFFSET;
    
    PIO0_REG(REG_BASE) |= maskledToSend;
}

void Leds_clear(uint32_t maskleds){

	uint32_t maskledToSend = maskleds << LEDS_OFFSET;
    
    PIO0_REG(REG_BASE) &= ~maskledToSend;
}

void Leds_toggle(uint32_t maskleds){

	uint32_t maskledToSend = maskleds << LEDS_OFFSET;
    
    PIO0_REG(REG_BASE) ^=  maskledToSend;
}

bool Key_read(int key_number){
    
    return (PIO0_REG(REG_BASE) & (1 << (key_number + KEYS_OFFSET))) == 0;
}

void Seg7_write(int seg7_number, uint32_t value){
        
    switch(seg7_number){
        case 0:
            PIO1_REG(REG_BASE) = (PIO1_REG(REG_BASE) & ~HEX0_BITS) | (~value << HEX0_OFFSET & HEX0_BITS);
            break;
        case 1:
            PIO1_REG(REG_BASE) = (PIO1_REG(REG_BASE) & ~HEX1_BITS) | (~value << HEX1_OFFSET & HEX1_BITS);
            break;
        case 2:
            PIO1_REG(REG_BASE) = (PIO1_REG(REG_BASE) & ~HEX2_BITS) | (~value << HEX2_OFFSET & HEX2_BITS);
            break;
        case 3:
            PIO1_REG(REG_BASE) = (PIO1_REG(REG_BASE) & ~HEX3_BITS) | (~value << HEX3_OFFSET & HEX3_BITS);
            break;
    }
}

void Seg7_write_hex(int seg7_number, uint32_t value){

    // value to hex conversion
    const uint32_t intToHex[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
            
   switch(seg7_number){
       case 0:
           PIO1_REG(REG_BASE) = (PIO1_REG(REG_BASE) & ~HEX0_BITS) | (~intToHex[value] << HEX0_OFFSET & HEX0_BITS);
           break;
       case 1:
           PIO1_REG(REG_BASE) = (PIO1_REG(REG_BASE) & ~HEX1_BITS) | (~intToHex[value] << HEX1_OFFSET & HEX1_BITS);
           break;
       case 2:
           PIO1_REG(REG_BASE) = (PIO1_REG(REG_BASE) & ~HEX2_BITS) | (~intToHex[value] << HEX2_OFFSET & HEX2_BITS);
           break;
       case 3:
           PIO1_REG(REG_BASE) = (PIO1_REG(REG_BASE) & ~HEX3_BITS) | (~intToHex[value] << HEX3_OFFSET & HEX3_BITS);
           break;
   }
}
