/**
 * @file    led.c
 * @brief   Implementacion del modulo LED — Practica 2
 *
 * Gestiona el LED de usuario de la Nucleo-F411RE mediante el driver GPIO.
 * En esta practica el LED indica la actividad del bucle principal.
 *
 * @author  Vania Yareni Leal Espinoza
 * @version 1.0
 */

#include "led.h"


gpio_status_t led_init(void)
{
    gpio_status_t status;

    /* Habilitar reloj del puerto GPIOA */
    status = gpio_initPort(LED_PORT);
    if (status != GPIO_OK) return status;

    /* Configurar el pin como salida push-pull */
    status = gpio_setPinMode(LED_PORT, LED_PIN, GPIO_MODE_OUTPUT);
    if (status != GPIO_OK) return status;

    /* Asegurar que el LED inicia apagado */
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
