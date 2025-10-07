#pragma once
#include <stdint.h>

struct i2c_dt_spec {
	const void *bus;
};

inline void k_usleep(uint32_t usec)
{
}
inline int i2c_write_dt(const struct i2c_dt_spec *spec, const uint8_t *buf, size_t len)
{
	return 0;
}
inline int i2c_read_dt(const struct i2c_dt_spec *spec, uint8_t *buf, size_t len)
{
	return 0;
}
inline int i2c_write(const void *bus, const uint8_t *buf, size_t len, uint16_t addr)
{
	return 0;
}
