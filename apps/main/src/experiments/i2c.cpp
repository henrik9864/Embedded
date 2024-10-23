#include "experiments/i2c.hpp"

using namespace hal;
using namespace hal::pins;
using namespace bsp::rp2040;

void i2c_set_baudrate(const uint32_t baudrate)
{
    // No idea
    uint32_t period = (i2c_freq + baudrate / 2) / baudrate;
    uint32_t lcnt = period * 3 / 5; // oof this one hurts
    uint32_t hcnt = period - lcnt;

    s_i2c_0.fs.scl_hcnt = hcnt;
    s_i2c_0.fs.scl_lcnt = lcnt;
    s_i2c_0.fs_spklen = lcnt < 16 ? 1 : lcnt / 16;

    s_i2c_0.sda_hold.tx = ((i2c_freq * 3) / 10000000) + 1;
}

void i2c_init(const uint32_t baudrate)
{
    // Disable i2c
    s_i2c_0.enable.enable = 0x0;

    s_i2c_0.control.speed = 0x2;         // Set speed to fast
    s_i2c_0.control.master_mode = 0x1;   // Enable master mode
    s_i2c_0.control.slave_disable = 0x1; // Disable slave mode
    s_i2c_0.control.restart_en = 0x1;    // Enable master restart
    s_i2c_0.control.tx_empty_ctrl = 0x1;

    // Set FIFO watermarks to 1 to make things simpler. This is encoded by a register value of 0.
    s_i2c_0.tx_tl = 0x0;
    s_i2c_0.rx_tl = 0x0;

    i2c_set_baudrate(baudrate);

    // Enable i2c
    s_i2c_0.enable.enable = 0x1;
}

void i2c_write(const uint32_t address, const uint8_t data, bool nostop)
{
    s_i2c_0.enable.enable = 0x0;
    s_i2c_0.tar.tar = address;
    s_i2c_0.enable.enable = 0x1;

    s_i2c_0.data_cmd.dat = data;
    s_i2c_0.data_cmd.restart = 0x1;
    s_i2c_0.data_cmd.stop = !nostop;
}

uint8_t i2c_read(const uint32_t address, bool nostop)
{
    s_i2c_0.enable.enable = 0x0;
    s_i2c_0.tar.tar = address;
    s_i2c_0.enable.enable = 0x1;

    while (!(16 - s_i2c_0.txflr)) { system::delay(1); };

    //s_i2c_0.data_cmd.first_data_byte = 0x0B;
    s_i2c_0.data_cmd.cmd = 0x1;
    s_i2c_0.data_cmd.restart = 0x1;
    s_i2c_0.data_cmd.stop = !nostop;

    while (!s_i2c_0.rxflr) { system::delay(1); };
    gpio::writePin(14, true);

    return s_i2c_0.data_cmd.dat;
}

void i2cMain()
{
    uart::enable(0, 1, 115200);

    i2c_init(100 * 1000);

    // Setup I2C pins
    gpio::setupPin(std::move(4), pindir::out, pinfunc::I2C);
    gpio::setupPin(std::move(5), pindir::out, pinfunc::I2C);
    //s_pads_bank_0.gpio[26].pue = (1 << 26 | 1 << 27);

    gpio::setPullUp(std::move(4));
    gpio::setPullUp(std::move(5));

    gpio::setupPin(14, pindir::out, pinfunc::SIO);

    //gpio::writePin(14, true);

    while (true)
    {
        etl::format_spec format;
        format.hex().width(8).fill('0');

        etl::string<8> text;

        uart::send(etl::to_string(i2c_read(0x34, true), text, format));
        //uart::send(etl::to_string(i2c_read(0x0B), text, format));

        //i2c_write(0x36, 0x0C, true);
        //if (i2c_read(0x36, false) != 0)
        //    gpio::writePin(14, true);

        hal::system::delay(1);
    }
}