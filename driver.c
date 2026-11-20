
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "driver.h"

// Definicion de pines
#define SENSOR_PRESENCIA (1 << PB0)
#define MOTOR            (1 << PB1)

// Variables del temporizador
volatile uint16_t contador_ms = 0;
volatile uint16_t tiempo_objetivo = 0;
volatile uint8_t temporizador_activo = 0;


// Funcion ejecutada cada 1 ms por Timer1
void f_tick_timer(void)
{
    if (temporizador_activo)
    {
        contador_ms++;

        if (contador_ms >= tiempo_objetivo)
        {
            temporizador_activo = 0;
        }
    }
}


// Inicializacion del microcontrolador
void init_mcu(void)
{
    GpioInitStructure_AVR puertos;

    // Configurar sensor como entrada
    puertos.port = avr_GPIO_B;
    puertos.modo = avr_GPIO_mode_Input;
    puertos.pines = SENSOR_PRESENCIA;
    init_gpio(puertos);

    // Configurar motor como salida
    puertos.port = avr_GPIO_B;
    puertos.modo = avr_GPIO_mode_Output;
    puertos.pines = MOTOR;
    init_gpio(puertos);

    // Motor apagado inicialmente
    clear_pin(avr_GPIOB_OUT, MOTOR);

    // Configurar Timer1 para interrupciones cada 1 ms
    SystickInitStructure_AVR timer;

    timer.timernumber = avr_TIM1;
    timer.time_ms = 1;
    timer.avr_systick_handler = f_tick_timer;

    init_Systick_timer(timer);

    // Habilitar interrupciones globales
    sei();
}


// Leer el sensor infrarrojo
int f_leer_presencia(void)
{
    return (avr_GPIOB_IN_0 == 1);
}


// Encender el motor
void f_activar_motor(void)
{
    set_pin(avr_GPIOB_OUT, MOTOR);
}


// Apagar el motor
void f_detener_motor(void)
{
    clear_pin(avr_GPIOB_OUT, MOTOR);
}


// Iniciar temporizador
void f_iniciar_temporizador(uint16_t tiempo_ms)
{
    uint8_t estado_anterior = SREG;

    cli();

    contador_ms = 0;
    tiempo_objetivo = tiempo_ms;
    temporizador_activo = 1;

    SREG = estado_anterior;
}


// Consultar si termino el tiempo
int f_tiempo_cumplido(void)
{
    return (temporizador_activo == 0);
}
