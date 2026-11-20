#ifndef DRIVER_H_
#define DRIVER_H_

#include <stdint.h>
#include "avr_Gpio.h"
#include "avr_Timers.h"

void init_mcu(void);

int f_leer_presencia(void);

void f_activar_motor(void);
void f_detener_motor(void);

void f_iniciar_temporizador(uint16_t tiempo_ms);
int f_tiempo_cumplido(void);

#endif
