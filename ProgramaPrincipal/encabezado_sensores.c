#include "encabezado_sensores.h"
#include "encabezado_displays.h"
#include <avr/interrupt.h>

volatile uint8_t bolos_caidos = 0;
volatile uint8_t estados_bolos[6] = {0};
volatile uint8_t reinicio_pendiente = 0;
volatile uint8_t estado_anterior = 0xFF;  // Con pull-ups activos, el estado inicial es todo 1


void sensores_init(void) {
	// Configura el puerto K como entrada y activa resistencias pull-up
	DDRK &= ~((1<<PK0)|(1<<PK1)|(1<<PK2)|(1<<PK3)|(1<<PK4)|(1<<PK5));    // Todo entrada
	PORTK |= (1<<PK0)|(1<<PK1)|(1<<PK2)|(1<<PK3)|(1<<PK4)|(1<<PK5);   // Pull-ups activados

	// Habilita interrupciones por cambio de pin en PK0–PK6 (PCINT16–21)
	PCICR |= (1 << PCIE2);      // Habilita grupo de interrupciones PCI2
	PCMSK2 |= (1<<PCINT16)|(1<<PCINT17)|(1<<PCINT18)|(1<<PCINT19)|(1<<PCINT20)|(1<<PCINT21);   // Habilita todos los PCINT del grupo 2 (PCINT16–22)


	sei();  // Habilita interrupciones globales
}

void iniciar_timer1(void) {
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // Modo CTC, prescaler 1024
	OCR1A = 2*7812; // 2 segundos si F_CPU = 8 MHz
	TIMSK1 |= (1 << OCIE1A); // Habilita interrupción por comparación
	TCNT1 = 0;
}


// ISR para interrupciones de cambio en pines PCINT16–23 (Puerto K)
ISR(PCINT2_vect) {
	uint8_t estado_actual = (0b00111111)&PINK;
	uint8_t cambios = estado_anterior ^ estado_actual;      // Bits que han cambiado
	uint8_t caidas = cambios & ~estado_actual;              // Cambios que pasaron de 1 a 0

	for (int i = 0; i < 6; i++) {
		if ((caidas & (1 << i)) && estados_bolos[i] == 0) {
			estados_bolos[i] = 1;
			bolos_caidos++;
			mostrar_numero(bolos_caidos); // Mostrar en displays

			if (!reinicio_pendiente) {
				iniciar_timer1(); // Inicia cuenta atrás de 2 segundos
				reinicio_pendiente = 1;
			}
		}
	}

	estado_anterior = estado_actual;  // Actualiza para la próxima interrupción
}


ISR(TIMER1_COMPA_vect) {
	for (int i = 0; i < 6; i++) estados_bolos[i] = 0; // Solo reiniciar estados

	TIMSK1 &= ~(1 << OCIE1A); // Desactiva la interrupción para no repetir
	reinicio_pendiente = 0;
}


void manejar_bolo_caido(void) {
	// Enciende un LED en PB0 (por ejemplo)
	DDRL |= (1 << PL6);
	PORTL |= (1 << PL6);

	// Mostrar el número 1 en el display 1
	set_display_1(1);
}
