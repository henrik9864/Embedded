#pragma once

#include <cstdint>

struct SIO {
	uint32_t cpuid;
	uint32_t gpio_in;
	uint32_t gpio_hi_in;
	uint32_t reserved;
	uint32_t gpio_out;
	uint32_t gpio_out_set;
	uint32_t gpio_out_clr;
	uint32_t gpio_out_xor;
	uint32_t gpio_oe;
	uint32_t gpio_oe_set;
	uint32_t gpio_oe_clr;
	uint32_t gpio_oe_xor;
	uint32_t gpio_hi_out;
	uint32_t gpio_hi_out_set;
	uint32_t gpio_hi_out_clr;
	uint32_t gpio_hi_out_xor;
	uint32_t gpio_hi_oe;
	uint32_t gpio_hi_oe_set;
	uint32_t gpio_hi_oe_clr;
	uint32_t gpio_hi_oe_xor;
};

struct IO_BANK_0 {
    struct {
        union {
            uint32_t regs;
            struct {
                uint32_t : 8;
                uint32_t outfromperi : 1;
                uint32_t outtopad : 1;
                uint32_t : 2;
                uint32_t oefromperi : 1;
                uint32_t oetopad : 1;
                uint32_t : 2;
                uint32_t infrompad : 1;
                uint32_t : 1;
                uint32_t intoperi : 1;
                uint32_t : 4;
                uint32_t irqfrompad : 1;
                uint32_t : 1;
                uint32_t irqtoproc : 1;
            } bits;
        } status;
        union {
            uint32_t regs;
            struct {
                uint32_t funcsel : 5;
                uint32_t : 3;
                uint32_t outover : 2;
                uint32_t : 2;
                uint32_t oeover : 2;
                uint32_t : 2;
                uint32_t inover : 2;
                uint32_t : 10;
                uint32_t irqover : 2;
            } bits;
        } control;
    } gpio[30];
};

struct RESETS {
    union {
        uint32_t regs;
        struct {
            uint32_t adc : 1;
            uint32_t busctrl : 1;
            uint32_t dma : 1;
            uint32_t i2c0 : 1;
            uint32_t i2c1 : 1;
            uint32_t io_bank_0 : 1;
            uint32_t io_qspi : 1;
            uint32_t jtag : 1;
            uint32_t pads_bank_0 : 1;
            uint32_t pads_qspi : 1;
            uint32_t pio_0 : 1;
            uint32_t pio_1 : 1;
            uint32_t pll_sys : 1;
            uint32_t pll_usb : 1;
            uint32_t pwm : 1;
            uint32_t rtc : 1;
            uint32_t spi_0 : 1;
            uint32_t spi_1 : 1;
            uint32_t syscfg : 1;
            uint32_t sysinfo : 1;
            uint32_t tbman : 1;
            uint32_t timer : 1;
            uint32_t uart_0 : 1;
            uint32_t uart_1 : 1;
            uint32_t usbctrl : 1;
        } bits;
    } reset;
    union {
        uint32_t regs;
        struct {
            uint32_t adc : 1;
            uint32_t busctrl : 1;
            uint32_t dma : 1;
            uint32_t i2c0 : 1;
            uint32_t i2c1 : 1;
            uint32_t io_bank_0 : 1;
            uint32_t io_qspi : 1;
            uint32_t jtag : 1;
            uint32_t pads_bank_0 : 1;
            uint32_t pads_qspi : 1;
            uint32_t pio_0 : 1;
            uint32_t pio_1 : 1;
            uint32_t pll_sys : 1;
            uint32_t pll_usb : 1;
            uint32_t pwm : 1;
            uint32_t rtc : 1;
            uint32_t spi_0 : 1;
            uint32_t spi_1 : 1;
            uint32_t syscfg : 1;
            uint32_t sysinfo : 1;
            uint32_t tbman : 1;
            uint32_t timer : 1;
            uint32_t uart_0 : 1;
            uint32_t uart_1 : 1;
            uint32_t usbctrl : 1;
        } bits;
    } wdsel;
    union {
        uint32_t regs;
        struct {
            uint32_t adc : 1;
            uint32_t busctrl : 1;
            uint32_t dma : 1;
            uint32_t i2c0 : 1;
            uint32_t i2c1 : 1;
            uint32_t io_bank_0 : 1;
            uint32_t io_qspi : 1;
            uint32_t jtag : 1;
            uint32_t pads_bank_0 : 1;
            uint32_t pads_qspi : 1;
            uint32_t pio_0 : 1;
            uint32_t pio_1 : 1;
            uint32_t pll_sys : 1;
            uint32_t pll_usb : 1;
            uint32_t pwm : 1;
            uint32_t rtc : 1;
            uint32_t spi_0 : 1;
            uint32_t spi_1 : 1;
            uint32_t syscfg : 1;
            uint32_t sysinfo : 1;
            uint32_t tbman : 1;
            uint32_t timer : 1;
            uint32_t uart_0 : 1;
            uint32_t uart_1 : 1;
            uint32_t usbctrl : 1;
        } bits;
    } reset_done;
};

volatile SIO s_sio __attribute__((section(".sio_regs")));
volatile IO_BANK_0 s_io_bank_0 __attribute__((section(".io_bank_0_regs")));
volatile RESETS s_resets __attribute__((section(".reset_regs")));