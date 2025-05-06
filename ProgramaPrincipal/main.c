#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "encabezado_displays.h"
#include "encabezado_sensores.h"

int main(void) {
	init_displays();   // Configura pines de displays
	init_timer0();     // Activa multiplexado con Timer0
	sensores_init();   // Configura sensores con interrupciones

	// Mostrar 3 y 7 en los displays al arrancar
	set_display_1(5);
	set_display_2(5);

	while (1) {
		
	}
}

