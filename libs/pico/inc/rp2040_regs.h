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

struct Clocks
{
    struct
    {
        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t : 5;
                uint32_t auxsrc : 4;
                uint32_t : 1;
                uint32_t kill : 1;
                uint32_t enable : 1;
                uint32_t dc50 : 1;
                uint32_t : 3;
                uint32_t phase : 2;
                uint32_t : 2;
                uint32_t nudge : 1;
            };
        } control;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t frac : 8;
                uint32_t integer : 24;
            };
        } div;

        uint32_t selected;
    } gpio[4];

    struct
    {
        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t src : 2;
                uint32_t : 3;
                uint32_t auxsrc : 2;
            };
        } control;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t : 8;
                uint32_t integer : 2;
            };
        } div;

        uint32_t selected;
    } ref;

    struct
    {
        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t src : 1;
                uint32_t : 4;
                uint32_t auxsrc : 3;
            };
        } control;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t frac : 8;
                uint32_t integer : 24;
            };
        } div;

        uint32_t selected;
    } sys;
};

struct IO_BANK_0 {
    struct {
        union {
            uint32_t : 32;
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
            };
        } status;
        union {
            uint32_t : 32;
            union {
                uint32_t funcsel : 5;
                uint32_t : 3;
                uint32_t outover : 2;
                uint32_t : 2;
                uint32_t oeover : 2;
                uint32_t : 2;
                uint32_t inover : 2;
                uint32_t : 10;
                uint32_t irqover : 2;
            };
        } control;
    } gpio[30];
};

struct RESETS {
    union {
        uint32_t : 32;
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
        };
    } reset;
    union {
        uint32_t : 32;
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
        };
    } wdsel;
    union {
        uint32_t : 32;
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
        };
    } reset_done;
};

struct RSOC
{
    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t freq_range : 12;
            uint32_t enable : 12;
        };
    } control;

    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t ds0 : 3;
            uint32_t : 1;
            uint32_t ds1 : 3;
            uint32_t : 1;
            uint32_t ds2 : 3;
            uint32_t : 1;
            uint32_t ds3 : 3;
            uint32_t : 1;
            uint32_t passwd : 16;
        };
    } freqa;

    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t ds4 : 3;
            uint32_t : 1;
            uint32_t ds5 : 3;
            uint32_t : 1;
            uint32_t ds6 : 3;
            uint32_t : 1;
            uint32_t ds7 : 3;
            uint32_t : 1;
            uint32_t passwd : 16;
        };
    } freqb;

    uint32_t dormant;

    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t div : 12;
        };
    } div;
};

struct XSOC
{
    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t freq_range : 12;
            uint32_t enable : 12;
        };
    } control;

    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t freq_range : 2;
            uint32_t : 10;
            uint32_t enabled : 1;
            uint32_t : 11;
            uint32_t badwrite : 1;
            uint32_t : 6;
            uint32_t stable : 1;
        };
    } status;

    uint32_t dormant;

    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t delay : 14;
            uint32_t : 5;
            uint32_t x4 : 1;
        };
    } startup;

    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t counter : 8;
        };
    } count;
};

struct PLL
{
    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t refdiv : 6;
            uint32_t : 2;
            uint32_t bypass : 1;
            uint32_t : 22;
            uint32_t lock : 1;
        };
    } control;

    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t pd : 1;
            uint32_t : 1;
            uint32_t dsmpd : 1;
            uint32_t postdivpd : 1;
            uint32_t : 1;
            uint32_t vcopd : 1;
        };
    } pwr;

    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t div : 12;
        };
    } fbdiv;

    union
    {
        uint32_t : 32;
        struct
        {
            uint32_t : 12;
            uint32_t postdiv2 : 3;
            uint32_t : 1;
            uint32_t postdiv1 : 3;
        };
    } prim;
};

volatile SIO s_sio __attribute__((section(".sio_regs")));
volatile IO_BANK_0 s_io_bank_0 __attribute__((section(".io_bank_0_regs")));
volatile RESETS s_resets __attribute__((section(".reset_regs")));
volatile Clocks s_clocks __attribute__((section(".clock_regs")));
volatile RSOC s_rsoc __attribute__((section(".rsoc_regs")));
volatile XSOC s_xsoc __attribute__((section(".xsoc_regs")));
volatile PLL s_pll_sys __attribute__((section(".pll_sys_regs")));
volatile PLL s_pll_usb __attribute__((section(".pll_sys_usb")));