/**
 * @file    timer.c
 * @brief   Implementacion del modulo Timer — Generacion de retardos
 *
 * Utiliza TIM2 a traves del driver TIM para generar retardos bloqueantes
 * con precision de milisegundos.
 *
 * @author  Vania Yareni Leal Espinoza
 * @version 1.0
 */

#include "timer.h"

tim_status_t timer_init(void)
{
    /* Inicializar TIM2 como timer de retardo */
    return tim_initTimer(TIMER_DELAY_TIM);
}

tim_status_t timer_delay_ms(uint32_t ms)
{
    tim_status_t status;

    if (ms == 0 || ms > 65535) return TIM_INVALID;

    /* Configurar el periodo del timer */
    status = tim_setTimerMs(TIMER_DELAY_TIM, ms);
    if (status != TIM_OK) return status;

    /* Arrancar el contador */
    status = tim_enableTimer(TIMER_DELAY_TIM);
    if (status != TIM_OK) return status;

    /* Esperar hasta que transcurra el tiempo configurado */
    status = tim_waitTimer(TIMER_DELAY_TIM);
    if (status != TIM_OK) return status;

    /* Detener el timer al finalizar el retardo */
    status = tim_disableTimer(TIMER_DELAY_TIM);

    return status;
}
