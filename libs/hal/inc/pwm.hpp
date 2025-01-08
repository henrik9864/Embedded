#pragma once

#include <cstdint>
#include <cstddef>
#include <array>
#include "pins.hpp"

namespace hal
{
    /*
    class pwm
    {
    public:
        static void enable(const pins::pin_id& pin);
        static void disable(const pins::pin_id& pin);

        static void writeCompare(const pins::pin_id& pin, const uint32_t value);
        static void writeWrap(const pins::pin_id& pin, const uint32_t value);
    };
    */

	enum class pwn_id : std::uint32_t;

	// Empty base class, the concept will force the derived class to implement the set method
	template <typename T>
	class pwn_base
	{
	public:
		static pwn_base<T> getInstance(const pwn_id& id)
		{
			return T::getInstance(id);
		}

		pwn_base(T impl)
			: m_Impl(impl)
		{

		}

		void enable(const pins::pin_id& pin) noexcept
		{
			m_Impl.enable(pin);
		}

		void disable(const pins::pin_id& pin) noexcept
		{
			m_Impl.disable(pin);
		}

		void writeCompare(const pins::pin_id& pin, const uint32_t value) noexcept
		{
			m_Impl.writeCompare(pin, value);
		}

		void writeWrap(const pins::pin_id& pin, const uint32_t value) noexcept
		{
			m_Impl.writeWrap(pin, value);
		}

	private:
		T m_Impl;
	};
}