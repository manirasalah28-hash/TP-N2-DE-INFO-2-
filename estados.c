#include "estados.h"
#include "driver.h"

estados_t (*funciones_estado[4])(void);

void enumerar_funciones(void)
{
    funciones_estado[INICIO] = f_inicio;
    funciones_estado[ESPERA] = f_espera;
    funciones_estado[DISPENSAR] = f_dispensar;
    funciones_estado[ESPERA_RETIRO] = f_espera_retiro;
}

estados_t f_inicio(void)
{
    f_detener_motor();
    return ESPERA;
}

estados_t f_espera(void)
{
    if (f_leer_presencia())
    {
        f_iniciar_temporizador(2000);
        return DISPENSAR;
    }

    return ESPERA;
}

estados_t f_dispensar(void)
{
    f_activar_motor();

    if (f_tiempo_cumplido())
    {
        f_detener_motor();
        return ESPERA_RETIRO;
    }

    return DISPENSAR;
}

estados_t f_espera_retiro(void)
{
    if (!f_leer_presencia())
    {
        return ESPERA;
    }

    return ESPERA_RETIRO;
}

