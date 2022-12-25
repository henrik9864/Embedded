#pragma once

#include <cstdint>
#include <stdexcept>

#include "hal.hpp"
#include "pins.hpp"

using namespace hal::pins;

namespace drivers
{
	class LN298NDriver
	{
	public:
		LN298NDriver(const uint32_t p1, const uint32_t p2, const uint32_t p3, const uint32_t p4);

		void stepForward();
		void stepForward(const uint32_t steps, const uint32_t delay);
		void stepBackward();
		void stepBackward(const uint32_t steps, const uint32_t delay);


	private:
		const uint32_t m_p1;
		const uint32_t m_p2;
		const uint32_t m_p3;
		const uint32_t m_p4;

		uint16_t m_Step;

		void preformStep(const uint16_t step);
	};
}