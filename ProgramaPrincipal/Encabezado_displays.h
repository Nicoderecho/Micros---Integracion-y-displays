#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define DS_PIN PK7

volatile uint8_t display_activo = 0;  // Variable global que indica qué display está encendido

void init_displays(void) {
    DDRK = 0xFF;  // PK0-PK7 como salidas
}


// Depende de estado activo un display o el otro
void activar_display(uint8_t estado) {
    if (estado == 0) {
        PORTK &= ~(1 << DS_PIN);  // Ds = 0
    } else {
        PORTK |= (1 << DS_PIN);   // Ds = 1
    }
}
// Tabla de segmentos para cada número (nivel alto = encendido)
// Orden de bits: g f e d c b a → PK6..PK0
const uint8_t tabla_segmentos[10] = {
    0b0111111, // 0 → a b c d e f
    0b0000110, // 1 → b c
    0b1011011, // 2 → a b d e g
    0b1001111, // 3 → a b c d g
    0b1100110, // 4 → b c f g
    0b1101101, // 5 → a c d f g
    0b1111101, // 6 → a c d e f g
    0b0000111, // 7 → a b c
    0b1111111, // 8 → todos
    0b1101111  // 9 → a b c d f g
};

void mostrar_digito(uint8_t numero) {
    if (numero < 10) {
        escribir_segmentos(tabla_segmentos[numero]);
    } else {
        escribir_segmentos(0x00); // Apagar todos si el número no es válido
    }
}
