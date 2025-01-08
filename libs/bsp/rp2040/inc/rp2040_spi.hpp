#pragma once

#include "spi.hpp"
#include "pins.hpp"
#include "clock.hpp"

#include "rp2040.hpp"

namespace hal
{
	enum class clk_phase {
		phase_0 = 0,
		phase_1 = 1
	};

	enum class clock_polarity {
		polarity_0 = 0,
		polarity_1 = 1
	};

	enum bit_order {
		lsb = 0,
		msb = 1
	};

	enum class spi_id : std::uint32_t
	{
		spi0,
		spi1
	};

	class spi_rp2040
	{
	public:
		static hal::spi_base<spi_rp2040> getInstance(const hal::spi_id& id) noexcept
		{
			switch (id)
			{
			case hal::spi_id::spi0:
				return hal::spi_base<spi_rp2040>{ spi_rp2040{ &bsp::rp2040::s_spi_0 } };
			case hal::spi_id::spi1:
				return hal::spi_base<spi_rp2040>{ spi_rp2040{ &bsp::rp2040::s_spi_1 } };
			default:
				return hal::spi_base<spi_rp2040>{ spi_rp2040{ &bsp::rp2040::s_spi_0 } }; // TODO: Not optimal
			}
		}

		void init(const hal::pins::pin_id& clk, const hal::pins::pin_id& csn, const hal::pins::pin_id& tx, const hal::pins::pin_id& rx, const std::uint32_t baudrate) noexcept;

		template<typename T, std::uint32_t sizeIn, std::uint32_t sizeOut>
		void writeAndRead(const etl::array<T, sizeIn>& dataOut, etl::array<T, sizeOut>& dataIn) noexcept;
	private:
		volatile bsp::rp2040::SPI* m_Spi;

		spi_rp2040(volatile bsp::rp2040::SPI* spi)
			: m_Spi(spi)
		{

		}

		std::uint32_t setBaudrate(const std::uint32_t baudrate);
		void setFormat(const uint32_t dataBits, const hal::clk_phase& phase, const hal::clock_polarity& polarity, const hal::bit_order& bitOrder);
	};

	using spi = hal::spi_base<spi_rp2040>;
};