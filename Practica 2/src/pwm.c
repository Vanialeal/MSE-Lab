/**
 * @file    pwm.c
 * @brief   Implementacion del modulo PWM
 *
 * Genera una senal PWM usando TIM3 Canal 1 en PA6 (AF2).
 * La frecuencia se configura mediante tim_setTimerFreq() y el ciclo
 * de trabajo se calcula como fraccion del valor ARR.
 *
 * @author  Vania Yareni Leal Espinoza
 * @version 1.0
 */

#include "pwm.h"

/**
 * @brief Valor ARR almacenado en cache — necesario para calcular CCR a partir del porcentaje.
 */
static uint32_t pwm_arr = 0;

/**
 * @brief Inicializa TIM3 y PA6 para salida PWM.
 */
tim_status_t pwm_init(uint32_t freq_hz)
{
    tim_status_t status;

    if (freq_hz == 0) return TIM_INVALID;

    /* --- Configurar GPIO PA6 como TIM3_CH1 (AF2) --- */
    status = (tim_status_t)gpio_initPort(PWM_GPIO_PORT);
    if (status != TIM_OK) return status;

    status = (tim_status_t)gpio_setAlternateFunction(PWM_GPIO_PORT,
                                                     PWM_GPIO_PIN,
                                                     PWM_GPIO_AF);
    if (status != TIM_OK) return status;

    /* --- Inicializar TIM3 --- */
    status = tim_initTimer(PWM_TIM);
    if (status != TIM_OK) return status;

    /* --- Configurar la frecuencia de la senal --- */
    status = tim_setTimerFreq(PWM_TIM, freq_hz);
    if (status != TIM_OK) return status;

    /* Guardar ARR para los calculos de ciclo de trabajo */
    pwm_arr = PWM_TIM->ARR;

    /* --- Configurar modo PWM 1 en el canal 1 --- */
    status = tim_setTimerCompareMode(PWM_TIM, PWM_CHANNEL, TIM_COMPARE_MODE_PWM1);
    if (status != TIM_OK) return status;

    /* --- Iniciar con ciclo de trabajo 0% --- */
    status = tim_setTimerCompareChannelValue(PWM_TIM, PWM_CHANNEL, 0);

    return status;
}

/**
 * @brief Establece la frecuencia y el ciclo de trabajo de la senal PWM.
 *
 * CCR = (duty_pct / 100) * (ARR + 1)
 *
 * PWM modo 1: salida en ALTO mientras CNT < CCR → duty = CCR / (ARR + 1)
 */
tim_status_t pwm_setSignal(uint32_t freq_hz, uint8_t duty_pct)
{
    tim_status_t status;

    if (freq_hz == 0)    return TIM_INVALID;
    if (duty_pct > 100U) return TIM_INVALID;

    /* Reconfigurar frecuencia si es necesario */
    status = tim_setTimerFreq(PWM_TIM, freq_hz);
    if (status != TIM_OK) return status;

    pwm_arr = PWM_TIM->ARR;

    /* Calcular el valor de comparacion a partir del porcentaje de ciclo de trabajo */
    uint32_t ccr = ((pwm_arr + 1U) * duty_pct) / 100U;

    status = tim_setTimerCompareChannelValue(PWM_TIM, PWM_CHANNEL, ccr);

    return status;
}

/**
 * @brief Habilita la salida del canal de comparacion y arranca el timer.
 */
tim_status_t pwm_start(void)
{
    tim_status_t status;

    status = tim_enableTimerCompareChannel(PWM_TIM, PWM_CHANNEL);
    if (status != TIM_OK) return status;

    status = tim_enableTimer(PWM_TIM);

    return status;
}

/**
 * @brief Deshabilita la salida del canal de comparacion y detiene el timer.
 */
tim_status_t pwm_stop(void)
{
    tim_status_t status;

    status = tim_disableTimerCompareChannel(PWM_TIM, PWM_CHANNEL);
    if (status != TIM_OK) return status;

    status = tim_disableTimer(PWM_TIM);

    return status;
}
