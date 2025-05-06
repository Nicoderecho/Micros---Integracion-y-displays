#include "encabezado_sensores.h"
#include "encabezado_displays.h"
#include <avr/interrupt.h>

void sensores_init(void) {
	// Configura el puerto K como entrada y activa resistencias pull-up
	DDRK &= ~((1<<PK0)|(1<<PK1)|(1<<PK2)|(1<<PK3)|(1<<PK4)|(1<<PK5));    // Todo entrada
	PORTK |= (1<<PK0)|(1<<PK1)|(1<<PK2)|(1<<PK3)|(1<<PK4)|(1<<PK5);   // Pull-ups activados

	// Habilita interrupciones por cambio de pin en PK0–PK6 (PCINT16–21)
	PCICR |= (1 << PCIE2);      // Habilita grupo de interrupciones PCI2
	PCMSK2 |= (1<<PCINT16)|(1<<PCINT17)|(1<<PCINT18)|(1<<PCINT19)|(1<<PCINT20)|(1<<PCINT21);   // Habilita todos los PCINT del grupo 2 (PCINT16–22)


	sei();  // Habilita interrupciones globales
}

// ISR para interrupciones de cambio en pines PCINT16–23 (Puerto K)
ISR(PCINT2_vect) {
	manejar_bolo_caido();
}

void manejar_bolo_caido(void) {
	// Enciende un LED en PB0 (por ejemplo)
	DDRL |= (1 << PL6);
	PORTL |= (1 << PL6);

	// Mostrar el número 1 en el display 1
	set_display_1(1);
}
