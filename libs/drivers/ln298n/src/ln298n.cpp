#include "ln298n.hpp"

namespace drivers
{
	LN298NDriver::LN298NDriver(const uint32_t p1, const uint32_t p2, const uint32_t p3, const uint32_t p4)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
		, m_p4(p4)
	{

	}

	void LN298NDriver::stepForward()
	{
		if (m_Step++ > 3)
			m_Step = 0;

		preformStep(m_Step);
	}

	void LN298NDriver::stepForward(uint32_t steps, const uint32_t delay)
	{
		do
		{
			stepForward();
			hal::system::delay(delay);
		} while (steps-- >= 0);
	}

	void LN298NDriver::stepBackward()
	{
		if (m_Step-- < 0)
			m_Step = 3;

		preformStep(m_Step);
	}

	void LN298NDriver::stepBackward(uint32_t steps, const uint32_t delay)
	{
		do
		{
			stepBackward();
			hal::system::delay(delay);
		} while (steps-- >= 0);
	}

	void LN298NDriver::preformStep(const uint16_t step)
	{
		switch (step)
		{
		case 0:
			gpio::writePin(std::move(m_p1), 1);
			gpio::writePin(std::move(m_p2), 0);
			gpio::writePin(std::move(m_p3), 1);
			gpio::writePin(std::move(m_p4), 0);
			break;
		case 1:
			gpio::writePin(std::move(m_p1), 0);
			gpio::writePin(std::move(m_p2), 1);
			gpio::writePin(std::move(m_p3), 1);
			gpio::writePin(std::move(m_p4), 0);
			break;
		case 2:
			gpio::writePin(std::move(m_p1), 0);
			gpio::writePin(std::move(m_p2), 1);
			gpio::writePin(std::move(m_p3), 0);
			gpio::writePin(std::move(m_p4), 1);
			break;
		case 3:
			gpio::writePin(std::move(m_p1), 1);
			gpio::writePin(std::move(m_p2), 0);
			gpio::writePin(std::move(m_p3), 0);
			gpio::writePin(std::move(m_p4), 1);
			break;
		default:
			break;
		}
	}
}