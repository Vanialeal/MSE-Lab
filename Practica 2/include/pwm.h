/**
 * @file    pwm.h
 * @brief   API del modulo PWM
 *
 * Abstraccion de alto nivel para generar senales PWM usando un timer
 * de hardware en modo de comparacion de salida. Hace uso interno del
 * driver TIM y del driver GPIO para la configuracion de funcion alternativa.
 *
 * Objetivo: TIM3 Canal 1 en PA6 (AF2) — Nucleo-F411RE
 *
 * Mapeo de pines (manual de usuario UM1724):
 *   PA6 → TIM3_CH1 → Funcion Alternativa 2 (AF2)
 *
 * @author  Vania Yareni Leal Espinoza
 * @version 1.0
 */

#ifndef PWM_H
#define PWM_H

#include <stdint.h>
#include "tim_driver.h"
#include "gpio_driver.h"

/* -----------------------------------------------------------------------
 * Mapeo de hardware
 * --------------------------------------------------------------------- */
#define PWM_TIM         TIM3            /**< Timer para generacion de PWM      */
#define PWM_CHANNEL     TIM_CHANNEL_1   /**< Canal de captura/comparacion      */
#define PWM_GPIO_PORT   GPIOA           /**< Puerto GPIO de la salida PWM      */
#define PWM_GPIO_PIN    GPIO_PIN_6      /**< Pin GPIO de la salida PWM         */
#define PWM_GPIO_AF     2U              /**< Funcion alternativa: TIM3_CH1     */

/* -----------------------------------------------------------------------
 * Prototipos de funciones
 * --------------------------------------------------------------------- */

/**
 * @brief  Inicializa el periferico PWM y el pin GPIO.
 *         - Habilita TIM3 y lo configura para la frecuencia dada.
 *         - Configura PA6 en modo funcion alternativa (AF2).
 *         - Activa modo PWM 1 en el canal 1.
 *         - NO arranca el timer (llamar a pwm_start() por separado).
 * @param  freq_hz   Frecuencia PWM en Hz (ej. 1000 para 1 kHz).
 * @return TIM_OK si fue exitoso, TIM_INVALID si los parametros son incorrectos.
 */
tim_status_t pwm_init(uint32_t freq_hz);

/**
 * @brief  Configura el ciclo de trabajo y actualiza el valor de comparacion.
 * @param  freq_hz    Frecuencia PWM en Hz (debe coincidir con pwm_init).
 * @param  duty_pct   Ciclo de trabajo en porcentaje (0 … 100).
 * @return TIM_OK si fue exitoso, TIM_INVALID si los parametros son incorrectos.
 */
tim_status_t pwm_setSignal(uint32_t freq_hz, uint8_t duty_pct);

/**
 * @brief  Activa la salida PWM (habilita timer y canal de comparacion).
 * @return TIM_OK si fue exitoso.
 */
tim_status_t pwm_start(void);

/**
 * @brief  Detiene la salida PWM (deshabilita canal de comparacion y timer).
 * @return TIM_OK si fue exitoso.
 */
tim_status_t pwm_stop(void);

#endif /* PWM_H */
