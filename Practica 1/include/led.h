/**
 * @file    led.h
 * @brief   API del modulo LED
 *
 * Abstraccion de alto nivel para controlar un LED conectado a un pin GPIO.
 * Hace uso interno del driver GPIO para todas las operaciones de hardware.
 *
 * Objetivo: Nucleo-F411RE — LED de usuario en PA5
 *
 * @author  Vania Yareni Leal Espinoza
 * @version 1.0
 */

#ifndef LED_H
#define LED_H

#include "gpio_driver.h"

/* -----------------------------------------------------------------------
 * Mapeo de hardware (Nucleo-F411RE)
 * --------------------------------------------------------------------- */
#define LED_PORT    GPIOA
#define LED_PIN     GPIO_PIN_5

/* -----------------------------------------------------------------------
 * Prototipos de funciones
 * --------------------------------------------------------------------- */

/**
 * @brief  Inicializa el pin del LED como salida push-pull.
 *         Habilita el reloj del puerto y configura el pin en modo salida.
 *         El LED queda apagado al terminar la inicializacion.
 * @return GPIO_OK si la operacion fue exitosa.
 */
gpio_status_t led_init(void);

/**
 * @brief  Enciende el LED (lleva el pin a nivel ALTO).
 * @return GPIO_OK si la operacion fue exitosa.
 */
gpio_status_t led_on(void);

/**
 * @brief  Apaga el LED (lleva el pin a nivel BAJO).
 * @return GPIO_OK si la operacion fue exitosa.
 */
gpio_status_t led_off(void);

/**
 * @brief  Invierte el estado actual del LED.
 * @return GPIO_OK si la operacion fue exitosa.
 */
gpio_status_t led_toggle(void);

#endif /* LED_H */
