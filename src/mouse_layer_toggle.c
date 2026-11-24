/*
 * Copyright (c) 2026 The roBa contributors
 * SPDX-License-Identifier: MIT
 *
 * &ml_tog LAYER
 *   layer off            -> turn it on and keep it (no automouse timeout)
 *   layer on, not sticky -> lock the automouse session
 *   layer on and sticky  -> turn it off
 */

#define DT_DRV_COMPAT zmk_behavior_mouse_layer_toggle

#include <zephyr/device.h>
#include <zephyr/sys/util.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

#include <zmk/behavior.h>
#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/keymap.h>

#include "roba_mouse_layer.h"

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static bool mouse_layer_sticky;
static uint8_t mouse_layer_id = UINT8_MAX;

bool pmw3610_mouse_layer_sticky(void) { return mouse_layer_sticky; }

void pmw3610_mouse_layer_note(uint8_t layer, bool sticky) {
    mouse_layer_id = layer;
    mouse_layer_sticky = sticky;
}

static int roba_mouse_layer_listener(const zmk_event_t *eh) {
    const struct zmk_layer_state_changed *ev = as_zmk_layer_state_changed(eh);

    /* &to 0 and other exits must drop the lock, or the next ball move would not auto-enter. */
    if (ev != NULL && !ev->state && mouse_layer_id != UINT8_MAX && ev->layer == mouse_layer_id) {
        mouse_layer_sticky = false;
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(roba_mouse_layer, roba_mouse_layer_listener);
ZMK_SUBSCRIPTION(roba_mouse_layer, zmk_layer_state_changed);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int ml_tog_pressed(struct zmk_behavior_binding *binding,
                          struct zmk_behavior_binding_event event) {
    const uint8_t layer = binding->param1;
    const bool active = zmk_keymap_layer_active(layer);

    ARG_UNUSED(event);

    if (!active) {
        pmw3610_mouse_layer_note(layer, true);
        return zmk_keymap_layer_activate(layer);
    }

    if (!pmw3610_mouse_layer_sticky()) {
        pmw3610_mouse_layer_note(layer, true);
        return 0;
    }

    pmw3610_mouse_layer_note(layer, false);
    return zmk_keymap_layer_deactivate(layer);
}

static int ml_tog_released(struct zmk_behavior_binding *binding,
                           struct zmk_behavior_binding_event event) {
    ARG_UNUSED(binding);
    ARG_UNUSED(event);
    return 0;
}

#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
static const struct behavior_parameter_value_metadata param_values[] = {
    {
        .display_name = "Layer",
        .type = BEHAVIOR_PARAMETER_VALUE_TYPE_LAYER_ID,
    },
};

static const struct behavior_parameter_metadata_set param_metadata_set[] = {{
    .param1_values = param_values,
    .param1_values_len = ARRAY_SIZE(param_values),
}};

static const struct behavior_parameter_metadata metadata = {
    .sets_len = ARRAY_SIZE(param_metadata_set),
    .sets = param_metadata_set,
};
#endif

static const struct behavior_driver_api ml_tog_api = {
    .binding_pressed = ml_tog_pressed,
    .binding_released = ml_tog_released,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
    .parameter_metadata = &metadata,
#endif
};

#define ML_TOG_INST(n)                                                                             \
    BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, NULL, NULL, POST_KERNEL,                                \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &ml_tog_api);

DT_INST_FOREACH_STATUS_OKAY(ML_TOG_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
