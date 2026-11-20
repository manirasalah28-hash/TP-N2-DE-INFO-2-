#ifndef ESTADOS_H_
#define ESTADOS_H_

typedef enum
{
    INICIO,
    ESPERA,
    DISPENSAR,
    ESPERA_RETIRO
} estados_t;

void enumerar_funciones(void);

estados_t f_inicio(void);
estados_t f_espera(void);
estados_t f_dispensar(void);
estados_t f_espera_retiro(void);

extern estados_t (*funciones_estado[])(void);

#endif
