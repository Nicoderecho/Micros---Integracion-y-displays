#ifndef ENCABEZADO_SENSORES_H
#define ENCABEZADO_SENSORES_H

#include <avr/io.h>

// Inicializa los pines del puerto K como entrada con pull-up
void sensores_init(void);

// Función que enciende el LED cuando se detecta un bolo caído
void manejar_bolo_caido(void);

#endif
