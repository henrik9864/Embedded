#pragma once

#include "etl/string.h"
#include "pins.hpp"

namespace hal
{
  class uart
  {
  public:
    static void enable(const pins::pin_id&& tx, const pins::pin_id&& rx);

    static void send(uint32_t);
    static void send(etl::string_view str);
    static uint32_t recv();
  };
}