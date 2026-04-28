/**
 * @file    led.h
 * @brief   API del modulo LED — Practica 2
 *
 * Capa de abstraccion para el control del LED de usuario.
 * Se apoya en el driver GPIO para las operaciones de registro.
 *
 * Objetivo: Nucleo-F411RE — LED de usuario en PA8
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
#define LED_PIN     GPIO_PIN_8

/* -----------------------------------------------------------------------
 * Prototipos de funciones
 * --------------------------------------------------------------------- */

/**
 * @brief  Configura el pin del LED como salida push-pull y lo apaga.
 *         Activa el reloj del puerto antes de configurar el modo del pin.
 * @return GPIO_OK si la operacion fue exitosa.
 */
gpio_status_t led_init(void);

/**
 * @brief  Activa el LED poniendo el pin en nivel ALTO.
 * @return GPIO_OK si la operacion fue exitosa.
 */
gpio_status_t led_on(void);

/**
 * @brief  Desactiva el LED poniendo el pin en nivel BAJO.
 * @return GPIO_OK si la operacion fue exitosa.
 */
gpio_status_t led_off(void);

/**
 * @brief  Cambia el estado del LED al opuesto del actual.
 * @return GPIO_OK si la operacion fue exitosa.
 */
gpio_status_t led_toggle(void);

#endif /* LED_H */
