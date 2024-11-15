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
void enable_A9_interrupts(void);
void config_GIC(void);
void config_interrupt(int N, int CPU_target);

#endif // EXCEPTIONS_H
