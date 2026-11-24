#pragma once

#include <stdbool.h>
#include <stdint.h>

/* Shared with the PMW3610 driver. True while &ml_tog is holding the mouse layer. */
bool pmw3610_mouse_layer_sticky(void);
void pmw3610_mouse_layer_note(uint8_t layer, bool sticky);
