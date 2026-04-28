/**
 * @file    timer.h
 * @brief   API del modulo Timer — Generacion de retardos
 *
 * Abstraccion de alto nivel para generar retardos bloqueantes
 * usando un timer de hardware. Internamente usa el driver TIM.
 *
 * Timer objetivo: TIM2 (APB1, proposito general, disponible en F411RE)
 *
 * @author  Vania Yareni Leal Espinoza
 * @version 1.0
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "tim_driver.h"

/* -----------------------------------------------------------------------
 * Mapeo de hardware
 * --------------------------------------------------------------------- */
#define TIMER_DELAY_TIM     TIM2    /**< Timer usado para generacion de retardos */

/* -----------------------------------------------------------------------
 * Prototipos de funciones
 * --------------------------------------------------------------------- */

/**
 * @brief  Inicializa el timer de retardo.
 *         Habilita el reloj de TIM2 y lo lleva a un estado conocido.
 *         Debe llamarse antes de cualquier llamada a timer_delay_ms().
 * @return TIM_OK si fue exitoso.
 */
tim_status_t timer_init(void);

/**
 * @brief  Bloquea la ejecucion durante el numero de milisegundos indicado.
 *         Configura TIM2, lo arranca, espera el evento de actualizacion
 *         y luego detiene el timer.
 * @param  ms  Duracion en milisegundos (1 … 65535).
 * @return TIM_OK si fue exitoso, TIM_INVALID si ms esta fuera de rango.
 */
tim_status_t timer_delay_ms(uint32_t ms);

#endif /* TIMER_H */
