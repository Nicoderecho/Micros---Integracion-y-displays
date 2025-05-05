#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define DS_PIN PK7

volatile uint8_t display_activo = 0;  // Variable global que indica qué display está encendido
