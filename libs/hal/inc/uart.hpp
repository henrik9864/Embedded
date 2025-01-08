#pragma once

#include "etl/string.h"
#include "pins.hpp"
#include "clock.hpp"

namespace hal
{
  enum class uart_id : std::uint32_t;

  // Empty base class, the concept will force the derived class to implement the set method
  template <typename T>
  class uart_base
  {
  public:
	  static uart_base<T> getInstance(const uart_id& id)
	  {
		  return T::getInstance(id);
	  }

	  uart_base(T impl)
		  : m_Impl(impl)
	  {

	  }

	  void enable(const pins::pin_id& tx, const pins::pin_id& rx, const std::uint32_t baudrate) noexcept
	  {
		  m_Impl.enable(tx, rx, baudrate);
	  }

	  void send(std::uint32_t value) noexcept
	  {
		  m_Impl.send(value);
	  }

	  void send(etl::string_view str) noexcept
	  {
		  m_Impl.send(str);
	  }

	  std::uint32_t recv() noexcept
	  {
		  return m_Impl.recv();
	  }

  private:
	  T m_Impl;
  };
}