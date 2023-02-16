#pragma once

#include <cstdint>
#include <cstddef>
#include <array>

#include "hal.hpp"
#include "pins.hpp"
#include "uart.hpp"
#include "rp2040.hpp"

#include "etl/string.h"
#include "etl/string_stream.h"

const uint32_t i2c_freq = 12 * 1000000;

void i2cMain();