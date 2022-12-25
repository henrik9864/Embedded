#include "experiments/i2c.hpp"

using namespace hal::pins;
using namespace bsp::rp2040;

void init_i2c(const uint32_t baudrate)
{
    // Disable i2c
    s_i2c_0.enable.enable = 0x0;

    s_i2c_0.control.speed = 0x2;         // Set spped to fast
    s_i2c_0.control.master_mode = 0x1;   // Enable master mode
    s_i2c_0.control.slave_disable = 0x1; // Disable slave mode
    s_i2c_0.control.restart_en = 0x1;    // Enable master restart
    s_i2c_0.control.tx_empty_ctrl = 0x1;

    // Set FIFO watermarks to 1 to make things simpler. This is encoded by a register value of 0.
    s_i2c_0.tx_tl = 0x0;
    s_i2c_0.rx_tl = 0x0;

    uint32_t period = (freq_133mhz + baudrate / 2) / baudrate;
    uint32_t lcnt = period * 3 / 5; // oof this one hurts
    uint32_t hcnt = period - lcnt;

    // Mathy stuff to figure out baudrate
    s_i2c_0.fs.scl_hcnt = hcnt;
    s_i2c_0.fs.scl_lcnt = lcnt;
    s_i2c_0.fs_spklen = lcnt < 16 ? 1 : lcnt / 16;
    s_i2c_0.sda_hold.tx = ((freq_133mhz * 3) / 10000000) + 1;

    s_i2c_0.tar.tar = 0x76; // Set devide id to 0x076;

    s_i2c_0.enable.enable = 0x1;
}

void i2cMain()
{
    init_i2c(100 * 1000);

    // Setup I2C pins
    gpio::setupPin(std::move(0), pindir::out, pinfunc::I2C);
    gpio::setupPin(std::move(1), pindir::out, pinfunc::I2C);
    //s_pads_bank_0.gpio[26].pue = (1 << 26 | 1 << 27);
}