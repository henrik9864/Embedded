#pragma once

#include "regs.hpp"

namespace Pico
{
    struct Sio
    {
        Register<uint32_t, 32, read_only> cpuid;
        Register<uint32_t, 32, read_only> gpio_in;
        Register<uint32_t, 32, read_only> gpio_hi_in;
    private:
        Register<uint32_t, 32, read_only> reserved;
    public:
        Register<uint32_t, 32, read_write> gpio_out;
        Register<uint32_t, 32, write_only> gpio_out_set;
        Register<uint32_t, 32, write_only> gpio_out_clr;
        Register<uint32_t, 32, write_only> gpio_out_xor;
        Register<uint32_t, 32, read_write> gpio_oe;
        Register<uint32_t, 32, write_only> gpio_oe_set;
        Register<uint32_t, 32, write_only> gpio_oe_clr;
        Register<uint32_t, 32, write_only> gpio_oe_xor;
        Register<uint32_t, 32, read_write> gpio_hi_out;
        Register<uint32_t, 32, write_only> gpio_hi_out_set;
        Register<uint32_t, 32, write_only> gpio_hi_out_clr;
        Register<uint32_t, 32, write_only> gpio_hi_out_xor;
        Register<uint32_t, 32, read_write> gpio_hi_oe;
        Register<uint32_t, 32, write_only> gpio_hi_oe_set;
        Register<uint32_t, 32, write_only> gpio_hi_oe_clr;
        Register<uint32_t, 32, write_only> gpio_hi_oe_xor;
    };

    struct IOBank0
    {
        struct
        {
            union
            {
                uint32_t : 32;
                union
                {
                    uint32_t : 8;
                    Register<uint32_t, 1, read_only> out_from_peri;
                    Register<uint32_t, 1, read_only> out_to_pad;
                    uint32_t : 2;
                    Register<uint32_t, 1, read_only> oe_from_peri;
                    Register<uint32_t, 1, read_only> oe_to_pad;
                    uint32_t : 2;
                    Register<uint32_t, 1, read_only> in_from_pad;
                    uint32_t : 1;
                    Register<uint32_t, 1, read_only> in_to_peri;
                    uint32_t : 4;
                    Register<uint32_t, 1, read_only> irq_from_pad;
                    uint32_t : 1;
                    Register<uint32_t, 1, read_only> irq_to_proc;
                    uint32_t : 5;
                };
            } status;

            union
            {
                uint32_t : 32;
                union
                {
                    Register<uint32_t, 5, read_write> funcsel;
                    uint32_t : 3;
                    Register<uint32_t, 2, read_write> outover;
                    uint32_t : 2;
                    Register<uint32_t, 2, read_write> oeover;
                    uint32_t : 2;
                    Register<uint32_t, 2, read_write> inover;
                    uint32_t : 10;
                    Register<uint32_t, 2, read_write> irqover;
                };
            } control;
        } gpio[30];
    };

    struct Resets
    {
        struct
        {
            Register<uint32_t, 1, read_write> adc;
            Register<uint32_t, 1, read_write> busctr;
            Register<uint32_t, 1, read_write> dma;
            Register<uint32_t, 1, read_write> i2c0;
            Register<uint32_t, 1, read_write> i2c1;
            Register<uint32_t, 1, read_write> io_bank_0;
            Register<uint32_t, 1, read_write> io_qspi;
            Register<uint32_t, 1, read_write> jtag;
            Register<uint32_t, 1, read_write> pads_bank_0;
            Register<uint32_t, 1, read_write> pads_qspi;
            Register<uint32_t, 1, read_write> pio_0;
            Register<uint32_t, 1, read_write> pio_1;
            Register<uint32_t, 1, read_write> pll_sys;
            Register<uint32_t, 1, read_write> pll_usb;
            Register<uint32_t, 1, read_write> pwm;
            Register<uint32_t, 1, read_write> rtc;
            Register<uint32_t, 1, read_write> spi_0;
            Register<uint32_t, 1, read_write> spi_1;
            Register<uint32_t, 1, read_write> syscfg;
            Register<uint32_t, 1, read_write> sysinfo;
            Register<uint32_t, 1, read_write> tbman;
            Register<uint32_t, 1, read_write> timer;
            Register<uint32_t, 1, read_write> uart_0;
            Register<uint32_t, 1, read_write> uart_1;
            Register<uint32_t, 1, read_write> usbctrl;
            uint32_t : 7;
        } reset, wdsel, reset_done;
    };
}

Pico::Sio sio __attribute__((section(".sio_regs")));
Pico::IOBank0 iobank0 __attribute__((section(".io_bank_0_regs")));
//Pico::Resets resets __attribute__((section(".reset_regs")));