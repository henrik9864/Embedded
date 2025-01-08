#pragma once

#include "uart.hpp"
#include "pins.hpp"
#include "clock.hpp"

#include "rp2040_regs.hpp"
#include "rp2040_pins.hpp"

namespace hal
{
	enum class uart_id : std::uint32_t
	{
		uart0,
		uart1
	};

	class uart_rp2040
	{
	public:
		static hal::uart_base<uart_rp2040> getInstance(const hal::uart_id& id) noexcept
		{
			switch (id)
			{
			case hal::uart_id::uart0:
				return hal::uart_base<uart_rp2040>{ uart_rp2040{ &bsp::rp2040::s_uart_0 } };
			case hal::uart_id::uart1:
				return hal::uart_base<uart_rp2040>{ uart_rp2040{ &bsp::rp2040::s_uart_1 } };
			default:
				return hal::uart_base<uart_rp2040>{ uart_rp2040{ &bsp::rp2040::s_uart_0 } }; // TODO: Not optimal
			}
		}

		void enable(const pins::pin_id& tx, const pins::pin_id& rx, const std::uint32_t baudrate) noexcept;

		void send(uint32_t) noexcept;
		void send(etl::string_view str) noexcept;
		uint32_t recv() noexcept;
	private:
		volatile bsp::rp2040::Uart* m_Uart;

		uart_rp2040(volatile bsp::rp2040::Uart* uart)
			: m_Uart(uart)
		{

		}
	};

	using uart = hal::uart_base<uart_rp2040>;
}