#ifndef ENCABEZADO_SENSORES_H
#define ENCABEZADO_SENSORES_H

#include <avr/io.h>

extern volatile uint8_t estados_bolos[6];
extern volatile uint8_t bolos_caidos;

// Inicializa los pines del puerto K como entrada con pull-up
void sensores_init(void);

// Funcion para iniciar cuenta de 1 segundo tras tirar bolos
void iniciar_timer1(void);

// Función que enciende el LED cuando se detecta un bolo caído
void manejar_bolo_caido(void);

#endif
