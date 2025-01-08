#pragma once

#include "pwm.hpp"
#include "rp2040.hpp"

namespace hal
{
    enum class pwm_channel
    {
        A,
        B
    };

	enum class pwn_id : std::uint32_t
	{
		pwn0
	};

	class pwn_rp2040
	{
	public:
		static hal::pwn_base<pwn_rp2040> getInstance(const hal::pwn_id& id) noexcept
		{
			switch (id)
			{
			case hal::pwn_id::pwn0:
				return hal::pwn_base<pwn_rp2040>{ pwn_rp2040{ &bsp::rp2040::s_pwm } };
			default:
				return hal::pwn_base<pwn_rp2040>{ pwn_rp2040{ &bsp::rp2040::s_pwm } }; // TODO: Not optimal
			}
		}

		void enable(const pins::pin_id& pin) noexcept;
		void disable(const pins::pin_id& pin) noexcept;

		void writeCompare(const pins::pin_id& pin, const uint32_t value) noexcept;
		void writeWrap(const pins::pin_id& pin, const uint32_t value) noexcept;
	private:
		volatile bsp::rp2040::PWM* m_pwn;

		pwn_rp2040(volatile bsp::rp2040::PWM* pwn)
			: m_pwn(pwn)
		{

		}
	};

	using pwn = hal::pwn_base<pwn_rp2040>;
}