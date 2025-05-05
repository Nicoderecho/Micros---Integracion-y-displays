#ifndef ENCABEZADO_DISPLAYS_H
#define ENCABEZADO_DISPLAYS_H

#include <stdint.h>

// Inicializa puerto y timer
void init_displays(void);
void init_timer0(void);

// Activa el display seleccionado (0 o 1)
void activar_display(uint8_t estado);

// Muestra un número (0-9) en el display activo
void mostrar_digito(uint8_t numero);

// Cambia los segmentos activos directamente (nivel alto = encendido)
void escribir_segmentos(uint8_t valor);

#endif
