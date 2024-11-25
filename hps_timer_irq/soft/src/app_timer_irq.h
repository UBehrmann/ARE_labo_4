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

#ifndef APP_TIMER_IRQ_H
#define APP_TIMER_IRQ_H

#include <stdint.h>
#include <stdbool.h>

void hps_timer_ISR(void);

#endif // EXCEPTIONS_H
