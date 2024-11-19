/*****************************************************************************************
 * HEIG-VD
 * Haute Ecole d'Ingenerie et de Gestion du Canton de Vaud
 * School of Business and Engineering in Canton de Vaud
 *****************************************************************************************
 * REDS Institute
 * Reconfigurable Embedded Digital Systems
 *****************************************************************************************
 *
 * File                 : pio_function.h
 * Author               : Anthony Convers
 * Date                 : 27.07.2022
 *
 * Context              : ARE lab
 *
 *****************************************************************************************
 * Brief: Header file for pio function
 *
 *****************************************************************************************
 * Modifications :
 * Ver    Date        Student      Comments
 * 0.0    27.07.2022  ACS           Initial version.
 * 1.0    11.10.24    Urs Behrmann
 *****************************************************************************************/

#ifndef PIO_FUNCTION_H
#define PIO_FUNCTION_H

#include <stdint.h>
#include <stdbool.h>
#include "axi_lw.h"

// Base address
#define PIO_CORE0_BASE_ADD 0xff200100
#define PIO_CORE1_BASE_ADD 0xff200120

// ACCESS MACROS
#define PIO0_REG(_x_) *(volatile uint32_t *)(PIO_CORE0_BASE_ADD + _x_) // _x_ is an offset with respect to the base address
#define PIO1_REG(_x_) *(volatile uint32_t *)(PIO_CORE1_BASE_ADD + _x_)

// PIO Registers
#define REG_BASE 0x000000
#define REG_DIR 0x000004
#define REG_INTERRUPT 0x000008
#define REG_EDGE 0x00000C
#define REG_OUTSET 0x000010
#define REG_OUTCLEAR 0x000014

// Define PIO bits usage

// PIO0
#define KEYS_BITS 0x00F00000
#define LEDS_BITS 0x000FFC00
#define SWITCHS_BITS 0x000003FF

#define KEYS_OFFSET 20
#define SWITCHS_OFFSET 0
#define LEDS_OFFSET 10

// PIO1
#define HEX0_BITS 0x0000007F
#define HEX1_BITS 0x00003F80
#define HEX2_BITS 0x001FC000
#define HEX3_BITS 0x0FE00000

#define HEX0_OFFSET 0
#define HEX1_OFFSET 7
#define HEX2_OFFSET 14
#define HEX3_OFFSET 21

//***************************//
//****** Init function ******//

// Switchs_init function : Initialize all Switchs in PIO core (SW9 to SW0)
void Switchs_init(void);

// Leds_init function : Initialize all Leds in PIO core (LED9 to LED0)
void Leds_init(void);

// Keys_init function : Initialize all Keys in PIO core (KEY3 to KEY0)
void Keys_init(void);

// Segs7_init function : Initialize all 7-segments display in PIO core (HEX3 to HEX0)
void Segs7_init(void);

//***********************************//
//****** Global usage function ******//

// Switchs_read function : Read the switchs value
// Parameter : None
// Return : Value of all Switchs (SW9 to SW0)
uint32_t Switchs_read(void);

// Leds_write function : Write a value to all Leds (LED9 to LED0)
// Parameter : "value"= data to be applied to all Leds
// Return : None
void Leds_write(uint32_t value);

// Leds_set function : Set to ON some or all Leds (LED9 to LED0)
// Parameter : "maskleds"= Leds selected to apply a set (maximum 0x3FF)
// Return : None
void Leds_set(uint32_t maskleds);

// Leds_clear function : Clear to OFF some or all Leds (LED9 to LED0)
// Parameter : "maskleds"= Leds selected to apply a clear (maximum 0x3FF)
// Return : None
void Leds_clear(uint32_t maskleds);

// Leds_toggle function : Toggle the curent value of some or all Leds (LED9 to LED0)
// Parameter : "maskleds"= Leds selected to apply a toggle (maximum 0x3FF)
// Return : None
void Leds_toggle(uint32_t maskleds);

// Key_read function : Read one Key status, pressed or not (KEY0 or KEY1 or KEY2 or KEY3)
// Parameter : "key_number"= select the key number to read, from 0 to 3
// Return : True(1) if key is pressed, and False(0) if key is not pressed
bool Key_read(int key_number);

// Seg7_write function : Write digit segment value to one 7-segments display (HEX0 or HEX1 or HEX2 or HEX3)
// Parameter : "seg7_number"= select the 7-segments number, from 0 to 3
// Parameter : "value"= digit segment value to be applied on the selected 7-segments (maximum 0x7F to switch ON all segments)
// Return : None
void Seg7_write(int seg7_number, uint32_t value);

// Seg7_write_hex function : Write an Hexadecimal value to one 7-segments display (HEX0 or HEX1 or HEX2 or HEX3)
// Parameter : "seg7_number"= select the 7-segments number, from 0 to 3
// Parameter : "value"= Hexadecimal value to be display on the selected 7-segments, form 0x0 to 0xF
// Return : None
void Seg7_write_hex(int seg7_number, uint32_t value);

#endif // PIO_FUNCTION_H