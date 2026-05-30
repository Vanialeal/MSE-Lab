/**
 * @file    led.c
 * @brief   Implementacion del modulo LED
 *
 * Controla el LED de usuario de la Nucleo-F411RE (PA5)
 * haciendo uso del driver GPIO de bajo nivel.
 *
 * @author  Vania Yareni Leal Espinoza
 * @version 1.0
 */

#include "led.h"


gpio_status_t led_init(void)
{
    gpio_status_t status;

    /* Habilitar reloj del puerto */
    status = gpio_initPort(LED_PORT);
    if (status != GPIO_OK) return status;

    /* Configurar pin como salida digital */
    status = gpio_setPinMode(LED_PORT, LED_PIN, GPIO_MODE_OUTPUT);
    if (status != GPIO_OK) return status;

    /* Apagar LED al iniciar */
    status = gpio_clearPin(LED_PORT, LED_PIN);

    return status;
}

gpio_status_t led_on(void)
{
    return gpio_setPin(LED_PORT, LED_PIN);
}

gpio_status_t led_off(void)
{
    return gpio_clearPin(LED_PORT, LED_PIN);
}

gpio_status_t led_toggle(void)
{
    return gpio_togglePin(LED_PORT, LED_PIN);
}
