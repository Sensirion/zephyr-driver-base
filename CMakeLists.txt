if (CONFIG_SENSIRION_DRIVER_CORE)
    zephyr_include_directories(include)

    zephyr_library_sources(
    src/crc_tables.c
    src/sensirion_common.c
    src/sensirion_i2c.c
    )
endif()