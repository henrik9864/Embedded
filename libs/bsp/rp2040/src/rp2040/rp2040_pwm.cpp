#include "rp2040_pwm.hpp"

using namespace hal;
using namespace bsp::rp2040;
using namespace hal::pins;

uint32_t getPwmSlice(const pin_id& pin)
{
    return pin / 2;
}

pwm_channel getPwmChannel(const pin_id& pin)
{
    return pin % 2 == 0 ? pwm_channel::A : pwm_channel::B;
}

void hal::pwn_rp2040::enable(const pin_id& pin)
{
    s_pwm.ch[getPwmSlice(std::move(pin))].csr.en = 1;
}

void hal::pwn_rp2040::disable(const pin_id& pin)
{
    s_pwm.ch[getPwmSlice(std::move(pin))].csr.en = 0;
}

void hal::pwn_rp2040::writeCompare(const pins::pin_id& pin, const uint32_t value)
{
    if (getPwmChannel(pin) == pwm_channel::A)
    {
        s_pwm.ch[getPwmSlice(pin)].cc.a = value;
    }
    else if (getPwmChannel(pin) == pwm_channel::B)
    {
        s_pwm.ch[getPwmSlice(pin)].cc.b = value;
    }
}

void hal::pwn_rp2040::writeWrap(const pins::pin_id& pin, const uint32_t value)
{
    s_pwm.ch[getPwmSlice(pin)].top.counter_wrap = value;
}