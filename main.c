#include "estados.h"
#include "driver.h"

int main(void)
{
    estados_t estado = INICIO;

    init_mcu();
    enumerar_funciones();

    while (1)
    {
        estado = funciones_estado[estado]();
    }

    return 0;
}
