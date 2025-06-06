#include <avr/io.h>
#include <avr/interrupt.h>
#include "encabezado_displays.h"

#define DS_PIN PK7

// Segmentos en nivel alto: g f e d c b a ? PK6..PK0
const uint8_t tabla_segmentos[10] = {
	0b0111111, // 0
	0b0000110, // 1
	0b1011011, // 2
	0b1001111, // 3
	0b1100110, // 4
	0b1101101, // 5
	0b1111101, // 6
	0b0000111, // 7
	0b1111111, // 8
	0b1101111  // 9
};

volatile uint8_t display_activo = 0;
volatile uint8_t valor_display_1 = 0;
volatile uint8_t valor_display_2 = 0;

void init_displays(void) {
	//displays como salidas (segmentos y Ds)
	DDRB |= (1<<PB1) | (1<<PB2) | (1<<PB3) | (1<<PB4); //DA, DB, DC, DD
	DDRD |= (1<<PD6) | (1<<PD7); //DE, DF
	DDRK |=  (1 << PK6) |(1<<PK7); //DG, DS
	

}

void activar_display(uint8_t estado) {
	if (estado == 0) {
		PORTK &= ~(1 << DS_PIN);
		} else {
		PORTK |= (1 << DS_PIN);
	}
}

void escribir_segmentos(uint8_t valor) {
	// Limpiar pines usados
	PORTB &= ~((1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4)); // a-d
	PORTD &= ~((1 << PD6) | (1 << PD7));                           // e-f
	PORTK &= ~(1 << PK6);                                          // g

	// Establecer los bits según el valor
	if (valor & (1 << 0)) PORTB |= (1 << PB1); // a
	if (valor & (1 << 1)) PORTB |= (1 << PB2); // b
	if (valor & (1 << 2)) PORTB |= (1 << PB3); // c
	if (valor & (1 << 3)) PORTB |= (1 << PB4); // d
	if (valor & (1 << 4)) PORTD |= (1 << PD6); // e
	if (valor & (1 << 5)) PORTD |= (1 << PD7); // f
	if (valor & (1 << 6)) PORTK |= (1 << PK6); // g
}


void mostrar_digito(uint8_t numero) {
	if (numero < 10) {
		escribir_segmentos(tabla_segmentos[numero]);
		} else {
		escribir_segmentos(0x00); // Apagar segmentos si es inválido
	}
}

void init_timer0(void) {
	TCCR0A = (1 << WGM01); // Modo CTC
	TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler 64
	OCR0A = 124; // Para 1 ms: (8MHz/64) = 125kHz ? 125 ciclos = 1 ms
	TIMSK0 = (1 << OCIE0A); // Habilitar interrupción por comparación
	sei(); // Activar interrupciones globales
}

void set_display_1(uint8_t valor) {
	valor_display_1 = valor;
}

void set_display_2(uint8_t valor) {
	valor_display_2 = valor;
}

void mostrar_numero(uint8_t numero) {
	uint8_t unidades = numero % 10;
	uint8_t decenas = numero / 10;

	set_display_1(unidades);
	set_display_2(decenas);
}

ISR(TIMER0_COMPA_vect) {
	if (display_activo == 0) {
		activar_display(0);
		mostrar_digito(valor_display_1);
		display_activo = 1;
		} else {
		activar_display(1);
		mostrar_digito(valor_display_2);
		display_activo = 0;
	}
}
