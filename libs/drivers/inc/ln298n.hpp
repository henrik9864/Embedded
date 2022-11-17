#pragma once

#include <cstdint>
#include <stdexcept>

#include "hal.hpp"
#include "pins.hpp"

using namespace hal::pins;

namespace drivers
{
	class LN298NDrivers
	{
	public:
		LN298NDrivers(const uint32_t p1, const uint32_t p2, const uint32_t p3, const uint32_t p4);

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

	LN298NDrivers::LN298NDrivers(const uint32_t p1, const uint32_t p2, const uint32_t p3, const uint32_t p4)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
		, m_p4(p4)
	{

	}

	void LN298NDrivers::stepForward()
	{
		if (m_Step++ > 3)
			m_Step = 0;

		preformStep(m_Step);
	}

	void LN298NDrivers::stepForward(uint32_t steps, const uint32_t delay)
	{
		do
		{
			stepForward();
			hal::delay(delay);
		} while (steps-- >= 0);
	}

	void LN298NDrivers::stepBackward()
	{
		if (m_Step-- < 0)
			m_Step = 3;

		preformStep(m_Step);
	}

	void LN298NDrivers::stepBackward(uint32_t steps, const uint32_t delay)
	{
		do
		{
			stepBackward();
			hal::delay(delay);
		} while (steps-- >= 0);
	}

	void LN298NDrivers::preformStep(const uint16_t step)
	{
		switch (step)
		{
		case 0:
			gpio::writePin(std::move(m_p1), 1);
			gpio::writePin(std::move(m_p2), 0);
			gpio::writePin(std::move(m_p3), 1);
			gpio::writePin(std::move(m_p4), 0);
		case 1:
			gpio::writePin(std::move(m_p1), 0);
			gpio::writePin(std::move(m_p2), 1);
			gpio::writePin(std::move(m_p3), 1);
			gpio::writePin(std::move(m_p4), 0);
		case 2:
			gpio::writePin(std::move(m_p1), 0);
			gpio::writePin(std::move(m_p2), 1);
			gpio::writePin(std::move(m_p3), 0);
			gpio::writePin(std::move(m_p4), 1);
		case 3:
			gpio::writePin(std::move(m_p1), 1);
			gpio::writePin(std::move(m_p2), 0);
			gpio::writePin(std::move(m_p3), 0);
			gpio::writePin(std::move(m_p4), 1);
		default:
			break;
		}
	}
}