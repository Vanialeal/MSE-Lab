/**
 * @file    button.h
 * @brief   API del modulo Button
 *
 * Interfaz para leer un pulsador conectado a un pin GPIO.
 * Internamente hace uso del driver GPIO de bajo nivel.
 *
 * Objetivo: Nucleo-F411RE — Boton de usuario (B1) en PC13
 * Nota:     El boton es activo en BAJO (presionado = 0, suelto = 1).
 *
 * @author  Vania Yareni Leal Espinoza
 * @version 1.0
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "gpio_driver.h"
#include <stddef.h>

/* -----------------------------------------------------------------------
 * Mapeo de hardware (Nucleo-F411RE)
 * --------------------------------------------------------------------- */
#define BUTTON_PORT     GPIOC
#define BUTTON_PIN      GPIO_PIN_13

/* -----------------------------------------------------------------------
 * Estados logicos del boton
 * --------------------------------------------------------------------- */
typedef enum
{
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED  = 1
} button_state_t;

/* -----------------------------------------------------------------------
 * Prototipos de funciones
 * --------------------------------------------------------------------- */

/**
 * @brief  Inicializa el pin del boton como entrada digital.
 *         Habilita el reloj del puerto y configura el pin en modo entrada.
 * @return GPIO_OK si la operacion fue exitosa.
 */
gpio_status_t button_init(void);

/**
 * @brief  Devuelve el estado logico del boton.
 *         Considera el cableado activo en bajo: IDR LOW = BUTTON_PRESSED.
 * @param  state  Salida: BUTTON_PRESSED o BUTTON_RELEASED.
 * @return GPIO_OK si fue exitoso, GPIO_INVALID si el puntero state es NULL.
 */
gpio_status_t button_get_state(button_state_t *state);

#endif /* BUTTON_H */
