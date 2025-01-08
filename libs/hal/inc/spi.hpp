#pragma once

#include "etl/array.h"

#include "pins.hpp"

#include <memory>

namespace hal
{
	/*
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

	class spi
	{
	public:
		static void init(const pins::pin_id&& clk, const pins::pin_id&& csn, const pins::pin_id&& tx, const pins::pin_id&& rx, const uint32_t baudrate) noexcept;

		template<typename T, std::uint32_t sizeIn, std::uint32_t sizeOut>
		static void writeAndRead(const etl::array<T, sizeIn>& dataOut, etl::array<T, sizeOut>& dataIn) noexcept;
	private:
		static std::uint32_t setBaudrate(const std::uint32_t baudrate);
		static void setFormat(const uint32_t dataBits, const hal::clk_phase&& phase, const hal::clock_polarity&& polarity, const hal::bit_order&& bitOrder);
	};
	*/

	enum class spi_id : std::uint32_t;

	// Empty base class, the concept will force the derived class to implement the set method
	template <typename T>
	class spi_base
	{
	public:
		static spi_base<T> getInstance(const spi_id& id)
		{
			return T::getInstance(id);
		}

		spi_base(T impl)
			: m_Impl(impl)
		{

		}

		void init(const pins::pin_id& clk, const pins::pin_id& csn, const pins::pin_id& tx, const pins::pin_id& rx, const std::uint32_t baudrate) noexcept
		{
			m_Impl.init(clk, csn, tx, rx, baudrate);
		}

		template<typename DataType, std::uint32_t sizeIn, std::uint32_t sizeOut>
		void writeAndRead(const etl::array<DataType, sizeIn>& dataOut, etl::array<DataType, sizeOut>& dataIn) noexcept
		{
			m_Impl.template writeAndRead<DataType, sizeIn, sizeOut>(dataOut, dataIn);
		}

	private:
		T m_Impl;
	};
}