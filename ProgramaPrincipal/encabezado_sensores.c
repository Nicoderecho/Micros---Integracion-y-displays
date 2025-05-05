#include "encabezado_sensores.h"
#include <avr/interrupt.h>

void sensores_init(void) {
    // Configura el puerto K como entrada y activa resistencias pull-up
    DDRK = 0x00;    // Todo entrada
    PORTK = 0xFF;   // Pull-ups activados

    // Habilita interrupciones por cambio de pin en PK0–PK7 (PCINT16–23)
    PCICR |= (1 << PCIE2);      // Habilita grupo de interrupciones PCI2
    PCMSK2 |= 0xFF;             // Habilita todos los PCINT del grupo 2 (PCINT16–23)

    sei();  // Habilita interrupciones globales
}

// ISR para interrupciones de cambio en pines PCINT16–23 (Puerto K)
ISR(PCINT2_vect) {
    manejar_bolo_caido();
}

void manejar_bolo_caido(void) {
    // Enciende un LED en PB0 (por ejemplo)
    DDRB |= (1 << PB0);
    PORTB |= (1 << PB0);
}
