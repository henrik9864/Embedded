#pragma once

#include "etl/array.h"

#include "pins.hpp"

#include <memory>

namespace hal
{
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