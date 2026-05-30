/**
 * @file    button.c
 * @brief   Implementacion del modulo Button
 *
 * Lee el estado del boton de usuario de la Nucleo-F411RE (PC13)
 * mediante el driver GPIO. La logica es activa en BAJO:
 * el pin lee LOW cuando el boton esta presionado.
 *
 * @author  Vania Yareni Leal Espinoza
 * @version 1.0
 */

#include "button.h"


gpio_status_t button_init(void)
{
    gpio_status_t status;

    /* Activar reloj del puerto del boton */
    status = gpio_initPort(BUTTON_PORT);
    if (status != GPIO_OK) return status;

    /* Configurar pin como entrada digital */
    status = gpio_setPinMode(BUTTON_PORT, BUTTON_PIN, GPIO_MODE_INPUT);
    return status;
}

gpio_status_t button_get_state(button_state_t *state)
{
    if (state == NULL) return GPIO_INVALID;

    gpio_pin_state_t pin_state;
    gpio_status_t status = gpio_readPin(BUTTON_PORT, BUTTON_PIN, &pin_state);

    if (status != GPIO_OK) return status;

    /* Nivel BAJO en el pin corresponde a boton PRESIONADO (activo en bajo) */
    *state = (pin_state == GPIO_PIN_LOW) ? BUTTON_PRESSED : BUTTON_RELEASED;

    return GPIO_OK;
}
