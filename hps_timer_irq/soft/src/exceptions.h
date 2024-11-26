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
 * 1.0    25.11.2024  UBN           Final version.
 *****************************************************************************************/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>
#include <stdbool.h>

extern bool timerGo;

#define osc1timer0base 0xFFD00000

#define LOADCOUNT 0x00
#define CURRENT_VALUE 0x04
#define CONTROL 0x08
#define EOI 0x0C

#define TIMER_OSC1_O_IRQ 201
#define ICCPMR 0xFFFEC104
#define ICCICR 0xFFFEC100
#define ICDDCR 0xFFFED000

// timer1controlreg bit masks
#define TIMER1_ENABLE 0x01
#define TIMER1_MODE 0x02
#define TIMER1_INT 0x04

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

/*
 * Initialize the banked stack pointer register for IRQ mode
 */
void set_A9_IRQ_stack(void);

/*
 * Turn off interrupts in the ARM processor
 */
void disable_A9_interrupts(void);

/*
 * Turn on interrupts in the ARM processor
 */
void enable_A9_interrupts(void);

/*
 * Configure the Generic Interrupt Controller (GIC)
 */
void config_GIC(void);

/*
 * Configure Set Enable Registers (ICDISERn) and Interrupt Processor Target
 * Registers (ICDIPTRn). The default (reset) values are used for other registers
 * in the GIC.
 */
void config_interrupt(int N, int CPU_target);

/*
 * Configure the timer
 */
void config_timer(void);

/*
 * Start the timer
 */
void start_timer(void);

/*
 * Stop the timer
 */
void stop_timer(void);

#endif // EXCEPTIONS_H
