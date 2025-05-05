#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define DS_PIN PK7

volatile uint8_t display_activo = 0;  // Variable global que indica qué display está encendido

void init_displays(void);
void activar_display(uint8_t estado);
void escribir_segmentos(uint8_t valor);
void init_timer0(void);

int main(void) {
    // Inicializar
    init_displays();
    init_timer0();
    sei();  // Habilitar interrupciones globales

    while (1) {
        // El programa principal está libre para hacer otras cosas
        // No es necesario hacer nada aquí
    }
}

void init_displays(void) {
    DDRK = 0xFF;  // PK0-PK7 como salidas
}

void activar_display(uint8_t estado) {
    if (estado == 0) {
        PORTK &= ~(1 << DS_PIN);  // Ds = 0
    } else {
        PORTK |= (1 << DS_PIN);   // Ds = 1
    }
}

void escribir_segmentos(uint8_t valor) {
    PORTK = (PORTK & (1 << DS_PIN)) | (valor & 0x7F);
}

void init_timer0(void) {
    TCCR0A = (1 << WGM01);   // Modo CTC
    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler = 64

    // Cálculo para 1 ms:
    // F_timer = F_CPU / prescaler = 8MHz / 64 = 125kHz
    // T_timer = 1 / 125000 = 8 µs
    // Queremos 1ms → 1ms / 8µs = 125 cuentas
    OCR0A = 125 - 1; // (El contador cuenta de 0 a OCR0A incluido)

    TIMSK0 = (1 << OCIE0A);  // Habilitar interrupción por comparación
}

// Interrupción del Timer 0 cada 1 ms
ISR(TIMER0_COMPA_vect) {
    // Alternar display
    if (display_activo == 0) {
        activar_display(0);
        escribir_segmentos(0x7F);  // Todos segmentos encendidos
        display_activo = 1;
    } else {
        activar_display(1);
        escribir_segmentos(0x7F);  // Todos segmentos encendidos
        display_activo = 0;
    }
}
