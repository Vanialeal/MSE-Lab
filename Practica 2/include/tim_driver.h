/**
 * @file    tim_driver.h
 * @brief   API del driver TIM para STM32F4xx
 *
 * Proporciona funciones para inicializar timers, configurar intervalos
 * de tiempo o frecuencias, y controlar canales de captura/comparacion para PWM.
 *
 * @author  Vania Yareni Leal Espinoza
 * @version 1.1
 */

#ifndef TIM_DRIVER_H
#define TIM_DRIVER_H

#include <stdint.h>
#include "stm32f4xx.h"

/* -----------------------------------------------------------------------
 * Constantes
 * --------------------------------------------------------------------- */

/** Frecuencia del reloj del sistema en Hz (HSI por defecto en STM32F411RE) */
#define TIM_SYSTEM_CLOCK_HZ     16000000UL

/* -----------------------------------------------------------------------
 * Definicion de tipos
 * --------------------------------------------------------------------- */

/**
 * @brief Codigos de retorno de las funciones del driver TIM.
 */
typedef enum
{
    TIM_OK      = 0,    /**< Operacion exitosa     */
    TIM_ERROR   = 1,    /**< Error generico        */
    TIM_INVALID = 2     /**< Parametro invalido    */
} tim_status_t;

/**
 * @brief Identificadores de canal de captura/comparacion.
 */
typedef enum
{
    TIM_CHANNEL_1 = 1,
    TIM_CHANNEL_2 = 2,
    TIM_CHANNEL_3 = 3,
    TIM_CHANNEL_4 = 4
} tim_channel_t;

/**
 * @brief Modos de comparacion/PWM para el registro CCMRx.
 */
typedef enum
{
    TIM_COMPARE_MODE_FROZEN    = 0x00,  /**< Salida sin cambio             */
    TIM_COMPARE_MODE_ACTIVE    = 0x01,  /**< Activo al comparar            */
    TIM_COMPARE_MODE_INACTIVE  = 0x02,  /**< Inactivo al comparar          */
    TIM_COMPARE_MODE_TOGGLE    = 0x03,  /**< Toggle al comparar            */
    TIM_COMPARE_MODE_PWM1      = 0x06,  /**< PWM modo 1 (alto mientras < CCR) */
    TIM_COMPARE_MODE_PWM2      = 0x07   /**< PWM modo 2 (bajo mientras < CCR) */
} tim_compare_mode_t;

/* -----------------------------------------------------------------------
 * Prototipos de funciones
 * --------------------------------------------------------------------- */

/**
 * @brief  Inicializa el subsistema TIM deshabilitando los relojes de todos
 *         los timers (estado de reset). Llamar una vez al inicio.
 * @return TIM_OK si fue exitoso.
 */
tim_status_t tim_init(void);

/**
 * @brief  Habilita el reloj periferico y resetea un timer especifico.
 * @param  tim  Puntero al periferico TIM (TIM1 … TIM5, TIM9 … TIM11).
 * @return TIM_OK si fue exitoso, TIM_INVALID si tim es NULL o desconocido.
 */
tim_status_t tim_initTimer(TIM_TypeDef *tim);

/**
 * @brief  Configura PSC y ARR para generar un evento de actualizacion
 *         cada el numero de milisegundos indicado.
 * @param  tim     Puntero al periferico TIM.
 * @param  ms      Intervalo deseado en milisegundos (1 … 65535).
 * @return TIM_OK si fue exitoso, TIM_INVALID si los parametros son incorrectos.
 */
tim_status_t tim_setTimerMs(TIM_TypeDef *tim, uint32_t ms);

/**
 * @brief  Configura PSC y ARR para generar un evento de actualizacion
 *         a la frecuencia especificada en Hz.
 * @param  tim   Puntero al periferico TIM.
 * @param  freq  Frecuencia deseada en Hz (1 … TIM_SYSTEM_CLOCK_HZ).
 * @return TIM_OK si fue exitoso, TIM_INVALID si los parametros son incorrectos.
 */
tim_status_t tim_setTimerFreq(TIM_TypeDef *tim, uint32_t freq);

/**
 * @brief  Arranca el timer especificado (activa el bit CEN en CR1).
 * @param  tim  Puntero al periferico TIM.
 * @return TIM_OK si fue exitoso, TIM_INVALID si tim es NULL.
 */
tim_status_t tim_enableTimer(TIM_TypeDef *tim);

/**
 * @brief  Detiene el timer especificado (limpia el bit CEN en CR1).
 * @param  tim  Puntero al periferico TIM.
 * @return TIM_OK si fue exitoso, TIM_INVALID si tim es NULL.
 */
tim_status_t tim_disableTimer(TIM_TypeDef *tim);

/**
 * @brief  Bloquea la ejecucion hasta que se active la bandera UIF,
 *         luego la limpia para evitar reactivaciones inmediatas.
 * @param  tim  Puntero al periferico TIM.
 * @return TIM_OK si fue exitoso, TIM_INVALID si tim es NULL.
 */
tim_status_t tim_waitTimer(TIM_TypeDef *tim);

/**
 * @brief  Establece el valor CCR de un canal de captura/comparacion.
 *         Define el umbral de comparacion (ciclo de trabajo en PWM).
 * @param  tim      Puntero al periferico TIM.
 * @param  channel  Numero de canal (TIM_CHANNEL_1 … TIM_CHANNEL_4).
 * @param  value    Valor de comparacion (0 … ARR).
 * @return TIM_OK si fue exitoso, TIM_INVALID si los parametros son incorrectos.
 */
tim_status_t tim_setTimerCompareChannelValue(TIM_TypeDef *tim,
                                             tim_channel_t channel,
                                             uint32_t value);

/**
 * @brief  Configura el modo de comparacion de salida de un canal via CCMRx.
 * @param  tim      Puntero al periferico TIM.
 * @param  channel  Numero de canal.
 * @param  mode     Modo de comparacion (tim_compare_mode_t).
 * @return TIM_OK si fue exitoso, TIM_INVALID si los parametros son incorrectos.
 */
tim_status_t tim_setTimerCompareMode(TIM_TypeDef *tim,
                                     tim_channel_t channel,
                                     tim_compare_mode_t mode);

/**
 * @brief  Habilita la salida de un canal de captura/comparacion (activa CCxE en CCER).
 * @param  tim      Puntero al periferico TIM.
 * @param  channel  Numero de canal.
 * @return TIM_OK si fue exitoso, TIM_INVALID si los parametros son incorrectos.
 */
tim_status_t tim_enableTimerCompareChannel(TIM_TypeDef *tim,
                                           tim_channel_t channel);

/**
 * @brief  Deshabilita la salida de un canal de captura/comparacion (limpia CCxE en CCER).
 * @param  tim      Puntero al periferico TIM.
 * @param  channel  Numero de canal.
 * @return TIM_OK si fue exitoso, TIM_INVALID si los parametros son incorrectos.
 */
tim_status_t tim_disableTimerCompareChannel(TIM_TypeDef *tim,
                                            tim_channel_t channel);

#endif /* TIM_DRIVER_H */
