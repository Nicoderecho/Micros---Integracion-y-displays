#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "encabezado_displays.h"

extern volatile uint8_t valor_display_1;
extern volatile uint8_t valor_display_2;

int main(void) {
    init_displays();
    init_timer0();

    // Mostrar 3 y 7 en los displays
    valor_display_1 = 3;
    valor_display_2 = 7;

    while (1) {
        // Aquí podrías actualizar los valores en tiempo real si quieres
        // valor_display_1 = nueva_valor1;
        // valor_display_2 = nueva_valor2;
    }
}
