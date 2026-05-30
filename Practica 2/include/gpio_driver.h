/**
 * @file    gpio_driver.h
 * @brief   API del driver GPIO para STM32F4xx
 *
 * Define los tipos, enumeraciones y prototipos de funciones para
 * inicializar puertos, configurar modos de pin y controlar/leer estados.
 *
 * @author  Vania Yareni Leal Espinoza
 * @version 1.0
 */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>
#include "stm32f4xx.h"
#include <stddef.h>

/* -----------------------------------------------------------------------
 * Definicion de tipos
 * --------------------------------------------------------------------- */

/**
 * @brief Codigos de retorno de las funciones del driver GPIO.
 */
typedef enum
{
    GPIO_OK      = 0,   /**< Operacion exitosa                  */
    GPIO_ERROR   = 1,   /**< Error generico                     */
    GPIO_INVALID = 2    /**< Parametro invalido (puerto/pin/modo) */
} gpio_status_t;

/**
 * @brief Modos de operacion de un pin GPIO.
 */
typedef enum
{
    GPIO_MODE_INPUT    = 0x00,  /**< Entrada digital               */
    GPIO_MODE_OUTPUT   = 0x01,  /**< Salida digital (push-pull)    */
    GPIO_MODE_ALT_FUNC = 0x02,  /**< Funcion alternativa           */
    GPIO_MODE_ANALOG   = 0x03   /**< Modo analogico                */
} gpio_mode_t;

/**
 * @brief Identificadores de pin (0–15).
 */
typedef enum
{
    GPIO_PIN_0  = 0,
    GPIO_PIN_1  = 1,
    GPIO_PIN_2  = 2,
    GPIO_PIN_3  = 3,
    GPIO_PIN_4  = 4,
    GPIO_PIN_5  = 5,
    GPIO_PIN_6  = 6,
    GPIO_PIN_7  = 7,
    GPIO_PIN_8  = 8,
    GPIO_PIN_9  = 9,
    GPIO_PIN_10 = 10,
    GPIO_PIN_11 = 11,
    GPIO_PIN_12 = 12,
    GPIO_PIN_13 = 13,
    GPIO_PIN_14 = 14,
    GPIO_PIN_15 = 15
} gpio_pin_t;

/**
 * @brief Estado logico de un pin GPIO.
 */
typedef enum
{
    GPIO_PIN_LOW  = 0,
    GPIO_PIN_HIGH = 1
} gpio_pin_state_t;

/* -----------------------------------------------------------------------
 * Prototipos de funciones
 * --------------------------------------------------------------------- */

/**
 * @brief  Inicializa el subsistema GPIO (resetea todos los puertos a su estado por defecto).
 *         Debe llamarse una vez al inicio antes de cualquier otra funcion GPIO.
 * @return GPIO_OK si la operacion fue exitosa.
 */
gpio_status_t gpio_init(void);

/**
 * @brief  Activa el reloj periferico de un puerto GPIO especifico.
 * @param  port  Puntero al puerto GPIO (GPIOA … GPIOE).
 * @return GPIO_OK si fue exitoso, GPIO_INVALID si el puerto es NULL o desconocido.
 */
gpio_status_t gpio_initPort(GPIO_TypeDef *port);

/**
 * @brief  Configura el modo de operacion de un pin especifico.
 * @param  port  Puntero al puerto GPIO.
 * @param  pin   Numero de pin (GPIO_PIN_0 … GPIO_PIN_15).
 * @param  mode  Modo deseado (gpio_mode_t).
 * @return GPIO_OK si fue exitoso, GPIO_INVALID si los parametros son incorrectos.
 */
gpio_status_t gpio_setPinMode(GPIO_TypeDef *port, gpio_pin_t pin, gpio_mode_t mode);

/**
 * @brief  Pone un pin en nivel logico ALTO usando BSRR (escritura atomica).
 * @param  port  Puntero al puerto GPIO.
 * @param  pin   Numero de pin.
 * @return GPIO_OK si fue exitoso, GPIO_INVALID si los parametros son incorrectos.
 */
gpio_status_t gpio_setPin(GPIO_TypeDef *port, gpio_pin_t pin);

/**
 * @brief  Pone un pin en nivel logico BAJO usando BSRR (escritura atomica).
 * @param  port  Puntero al puerto GPIO.
 * @param  pin   Numero de pin.
 * @return GPIO_OK si fue exitoso, GPIO_INVALID si los parametros son incorrectos.
 */
gpio_status_t gpio_clearPin(GPIO_TypeDef *port, gpio_pin_t pin);

/**
 * @brief  Invierte el estado actual de un pin mediante XOR sobre ODR.
 * @param  port  Puntero al puerto GPIO.
 * @param  pin   Numero de pin.
 * @return GPIO_OK si fue exitoso, GPIO_INVALID si los parametros son incorrectos.
 */
gpio_status_t gpio_togglePin(GPIO_TypeDef *port, gpio_pin_t pin);

/**
 * @brief  Lee el estado digital actual de un pin mediante IDR.
 * @param  port   Puntero al puerto GPIO.
 * @param  pin    Numero de pin.
 * @param  state  Parametro de salida: GPIO_PIN_LOW o GPIO_PIN_HIGH.
 * @return GPIO_OK si fue exitoso, GPIO_INVALID si los parametros son incorrectos.
 */
gpio_status_t gpio_readPin(GPIO_TypeDef *port, gpio_pin_t pin, gpio_pin_state_t *state);

/**
 * @brief  Configura la funcion alternativa de un pin especifico.
 * @param  port     Puntero al puerto GPIO.
 * @param  pin      Numero de pin.
 * @param  alt_func Numero de funcion alternativa (0–15, ver hoja de datos).
 * @return GPIO_OK si fue exitoso, GPIO_INVALID si los parametros son incorrectos.
 */
gpio_status_t gpio_setAlternateFunction(GPIO_TypeDef *port, gpio_pin_t pin, uint8_t alt_func);


#endif /* GPIO_DRIVER_H */
