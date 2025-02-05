#pragma once

#include "pins.hpp"
#include "spi.hpp"

namespace drivers::flash
{
	struct flash_info
	{
		std::uint8_t manufacture_id;
		std::uint16_t device_id;
	};

	struct flash_status
	{
		bool busy;
		bool write_enable;
	};

	template<typename T>
	class w25q32
	{
	public:
		w25q32(hal::spi_base<T>& spi)
			: m_Spi{spi}
		{
			
		}

		flash_info read_info()
		{
			etl::array<std::uint8_t, 6> toSend{ READ_DEVICE_MANUFACTURE_ID };
			etl::array<std::uint8_t, 6> toRecv{};
			m_Spi.template writeAndRead<std::uint8_t, 6, 6>(toSend, toRecv);

			return flash_info{
				.manufacture_id = toRecv.at(1),
				.device_id = (toRecv.at(2) << 8) | toRecv.at(3)
			};
		}

		flash_status read_status()
		{
			etl::array<std::uint8_t, 6> toSend{ READ_STATUS };
			etl::array<std::uint8_t, 6> toRecv{};
			m_Spi.template writeAndRead<std::uint8_t, 6, 6>(toSend, toRecv);

			return flash_status{
				.busy = (toRecv.at(1) >> 0) & 0x01,
				.write_enable = (toRecv.at(1) >> 1) & 0x01,
			};
		}

		template <std::uint32_t BYTES>
		etl::array<std::uint8_t, BYTES> read_bytes(const std::uint32_t address)
		{
			etl::array<std::uint8_t, 1 + BYTES> toSend{ READ_SECTOR };
			etl::array<std::uint8_t, 1 + BYTES> toRecv{};

			m_Spi.template writeAndRead<std::uint8_t, 1+ BYTES, 1 + BYTES>(toSend, toRecv);

			etl::array<std::uint8_t, BYTES> out{};
			etl::copy(toRecv.begin() + 1, toRecv.end(), out.begin());

			return out;
		}

		template <std::uint32_t BYTES>
		void write_bytes(std::uint32_t address, etl::array<std::uint8_t, BYTES> bytes)
		{
			write_enable();

			std::uint8_t addres_0 = ((std::uint8_t*)(&address))[0];
			std::uint8_t addres_1 = ((std::uint8_t*)(&address))[1];
			std::uint8_t addres_2 = ((std::uint8_t*)(&address))[2];

			etl::array<std::uint8_t, 4 + BYTES> toSend{ WRITE_SECTOR, addres_0, addres_1, addres_2 };
			etl::array<std::uint8_t, 4 + BYTES> toRecv{};

			etl::copy(bytes.begin(), bytes.end(), toSend.begin() + 4);

			m_Spi.template writeAndRead<std::uint8_t, 4 + BYTES, 4 + BYTES>(toSend, toRecv);
		}

		void write_enable()
		{
			etl::array<std::uint8_t, 1> toSend{ WRITE_ENABLE };
			etl::array<std::uint8_t, 1> toRecv{};
			m_Spi.template writeAndRead<std::uint8_t, 1, 1>(toSend, toRecv);
		}

	private:
		hal::spi_base<T> m_Spi;

		const std::uint8_t READ_DEVICE_MANUFACTURE_ID = 0x9F;
		const std::uint8_t READ_STATUS = 0x01;
		const std::uint8_t READ_SECTOR = 0x03;
		const std::uint8_t WRITE_SECTOR = 0x02;
		const std::uint8_t WRITE_ENABLE = 0x06;
	};
}