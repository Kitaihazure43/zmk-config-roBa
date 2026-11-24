# Vendored PMW3610 driver plus the mouse-layer lock behavior.
# Upstream: https://github.com/kumamuk-git/zmk-pmw3610-driver (main, 2026-11-24)

zephyr_include_directories(src)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/include)

zephyr_library()
zephyr_library_sources(src/mouse_layer_toggle.c)
zephyr_library_sources_ifdef(CONFIG_PMW3610 src/pmw3610.c)
