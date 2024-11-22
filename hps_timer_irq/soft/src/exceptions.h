/*****************************************************************************************
 * HEIG-VD
 * Haute Ecole d'Ingenerie et de Gestion du Canton de Vaud
 * School of Business and Engineering in Canton de Vaud
 *****************************************************************************************
 * REDS Institute
 * Reconfigurable Embedded Digital Systems
 *****************************************************************************************
 *
 * File                 : exceptions.h
 * Author               : Urs Behrmann
 * Date                 : 15.11.2024
 *
 * Context              : ARE lab
 *
 *****************************************************************************************
 * Brief:
 *
 *****************************************************************************************
 * Modifications :
 * Ver    Date        Student      Comments
 * 0.0    15.11.2024  UBN          Initial version.
 *
 *****************************************************************************************/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>
#include <stdbool.h>

extern bool timerGo;

#define osc1timer0base 0xFFD00000

#define loadcount 0x00
#define currentvalue 0x04
#define control 0x08
#define EOI 0x0C

#define OSC1_LW_REG(_x_) *(volatile uint32_t *)(osc1timer0base + _x_) // _x_ is an offset with respect to the base address

// Define ticks for 100ms with 25MHz clock
#define Ticks_100ms 2500000

// Function prototypes for exception handlers
void __cs3_isr_irq(void) __attribute__((interrupt));
void __cs3_reset(void) __attribute__((interrupt));
void __cs3_isr_undef(void) __attribute__((interrupt));
void __cs3_isr_swi(void) __attribute__((interrupt));
void __cs3_isr_pabort(void) __attribute__((interrupt));
void __cs3_isr_dabort(void) __attribute__((interrupt));
void __cs3_isr_fiq(void) __attribute__((interrupt));

// Function prototypes for initializing and configuring exceptions
void set_A9_IRQ_stack(void);
void disable_A9_interrupts(void);
void enable_A9_interrupts(void);
void config_GIC(void);
void config_interrupt(int N, int CPU_target);
void config_timer(void);
void start_timer(void);
void stop_timer(void);

#endif // EXCEPTIONS_H
