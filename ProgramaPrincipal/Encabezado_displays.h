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
