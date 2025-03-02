/*****************************************************************************************
 * HEIG-VD
 * Haute Ecole d'Ingenerie et de Gestion du Canton de Vaud
 * School of Business and Engineering in Canton de Vaud
 *****************************************************************************************
 * REDS Institute
 * Reconfigurable Embedded Digital Systems
 *****************************************************************************************
 *
 * File                 : execptions.c
 * Author               : Anthony Convers
 * Date                 : 27.10.2022
 *
 * Context              : ARE lab
 *
 *****************************************************************************************
 * Brief: defines exception vectors for the A9 processor
 *        provides code that sets the IRQ mode stack, and that dis/enables interrupts
 *        provides code that initializes the generic interrupt controller
 *
 *****************************************************************************************
 * Modifications :
 * Ver    Date        Engineer      Comments
 * 0.0    27.10.2022  ACS           Initial version.
 * 1.0    25.11.2024  UBN           Final version.
 *****************************************************************************************/
#include "exceptions.h"

#include <stdint.h>
#include <stdio.h>

#include "address_map_arm.h"
#include "axi_lw.h"
#include "int_defines.h"
#include "app_timer_irq.h"
#include "pio_function.h"

/* This file:
 * 1. defines exception vectors for the A9 processor
 * 2. provides code that sets the IRQ mode stack, and that dis/enables interrupts
 * 3. provides code that initializes the generic interrupt controller
 */

bool timerGo = 0;

/*
 * Define the IRQ exception handler
 */
void hps_timer_ISR(void)
{
	timerGo = 1;

	// Read the register to clear the interrupt
	volatile int dummy = OSC1_LW_REG(EOI);

	// To not have a warning
	(void)dummy;
}

// Define the IRQ exception handler
void __attribute__((interrupt)) __cs3_isr_irq(void)
{
	// Read CPU Interface registers to determine which peripheral has caused an interrupt
	int interrupt_ID = *((int *)0xFFFEC10C) & 0x3FF;

	// Handle the interrupt if it comes from the timer
	if (interrupt_ID == TIMER_OSC1_O_IRQ)
	{
		hps_timer_ISR();
	}

	// Clear interrupt from the CPU Interface bits 9-0
	*((int *)0xFFFEC110) = interrupt_ID & 0x3FF;
}

// Define the remaining exception handlers
void __attribute__((interrupt)) __cs3_reset(void)
{
	while (1)
		;
}

void __attribute__((interrupt)) __cs3_isr_undef(void)
{
	while (1)
		;
}

void __attribute__((interrupt)) __cs3_isr_swi(void)
{
	while (1)
		;
}

void __attribute__((interrupt)) __cs3_isr_pabort(void)
{
	while (1)
		;
}

void __attribute__((interrupt)) __cs3_isr_dabort(void)
{
	while (1)
		;
}

void __attribute__((interrupt)) __cs3_isr_fiq(void)
{
	while (1)
		;
}

void set_A9_IRQ_stack(void)
{
	uint32_t stack, mode;
	stack = A9_ONCHIP_END - 7; // top of A9 onchip memory, aligned to 8 bytes
	/* change processor to IRQ mode with interrupts disabled */
	mode = INT_DISABLE | IRQ_MODE;
	asm("msr cpsr, %[ps]" : : [ps] "r"(mode));
	/* set banked stack pointer */
	asm("mov sp, %[ps]" : : [ps] "r"(stack));

	/* go back to SVC mode before executing subroutine return! */
	mode = INT_DISABLE | SVC_MODE;
	asm("msr cpsr, %[ps]" : : [ps] "r"(mode));
}

void disable_A9_interrupts(void)
{
	uint32_t status = SVC_MODE | INT_DISABLE;
	asm("msr cpsr, %[ps]" : : [ps] "r"(status));
}

void enable_A9_interrupts(void)
{
	uint32_t status = SVC_MODE | INT_ENABLE;
	asm("msr cpsr, %[ps]" : : [ps] "r"(status));
}

void config_GIC(void)
{
	config_interrupt(201, CPU0);

	// Set Interrupt Priority Mask Register (ICCPMR). Enable interrupts of all
	// priorities
	*((int *)ICCPMR) = 0xFFFF;

	// Set CPU Interface Control Register (ICCICR). Enable signaling of
	// interrupts
	*((int *)ICCICR) = 1;

	// Configure the Distributor Control Register (ICDDCR) to send pending
	// interrupts to CPUs
	*((int *)ICDDCR) = 1;
}

void config_interrupt(int N, int CPU_target)
{
	int reg_offset, index, value, address;
	/* Configure the Interrupt Set-Enable Registers (ICDISERn).
	 * reg_offset = (integer_div(N / 32) * 4
	 * value = 1 << (N mod 32) */
	reg_offset = (N >> 3) & 0xFFFFFFFC;
	index = N & 0x1F;
	value = 0x1 << index;
	address = 0xFFFED100 + reg_offset;
	/* Now that we know the register address and value, set the appropriate bit */
	*(int *)address |= value;
	/* Configure the Interrupt Processor Targets Register (ICDIPTRn)
	 * reg_offset = integer_div(N / 4) * 4
	 * index = N mod 4 */
	reg_offset = (N & 0xFFFFFFFC);
	index = N & 0x3;
	address = 0xFFFED800 + reg_offset + index;
	/* Now that we know the register address and value, write to (only) the
	 * appropriate byte */
	*(char *)address = (char)CPU_target;
}

void config_timer(void)
{
	OSC1_LW_REG(CONTROL) = TIMER1_MODE;

	OSC1_LW_REG(LOADCOUNT) = Ticks_100ms;
}

void start_timer(void)
{
	OSC1_LW_REG(CONTROL) = TIMER1_ENABLE | TIMER1_MODE ;
}

void stop_timer(void)
{
	OSC1_LW_REG(CONTROL) = TIMER1_MODE;
}