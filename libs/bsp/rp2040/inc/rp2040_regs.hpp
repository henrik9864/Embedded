#pragma once

#include <cstdint>

namespace bsp::rp2040
{
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

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t : 5;
                    uint32_t auxsrc : 3;
                    uint32_t : 2;
                    uint32_t kill : 1;
                    uint32_t enable : 1;
                };
            } control;

            uint32_t selected;
        } peripheral;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t : 5;
                    uint32_t auxsrc : 3;
                    uint32_t : 2;
                    uint32_t kill : 1;
                    uint32_t enable : 1;
                    uint32_t : 4;
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
                    uint32_t : 8;
                    uint32_t integer : 2;
                };
            } div;

            uint32_t selected;
        } usb;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t : 5;
                    uint32_t auxsrc : 3;
                    uint32_t : 2;
                    uint32_t kill : 1;
                    uint32_t enable : 1;
                    uint32_t : 4;
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
                    uint32_t : 8;
                    uint32_t integer : 2;
                };
            } div;

            uint32_t selected;
        } adc;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t : 5;
                    uint32_t auxsrc : 3;
                    uint32_t : 2;
                    uint32_t kill : 1;
                    uint32_t enable : 1;
                    uint32_t : 4;
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
                    uint32_t : 8;
                    uint32_t integer : 24;
                };
            } div;

            uint32_t selected;
        } rtc;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t timeout : 8;
                    uint32_t enable : 1;
                    uint32_t : 3;
                    uint32_t force : 1;
                    uint32_t : 3;
                    uint32_t clear : 1;
                };
            } control;

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t resussed : 1;
                };

            } status;

        } sys_resus;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t ref_khz : 20;
                };

            };

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t min_khz : 25;
                };

            };

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t max_khz : 25;
                };

            };

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t delay : 3;
                };

            };

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t interval : 4;
                };

            };

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t src : 8;
                };

            };

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t pass : 1;
                    uint32_t : 3;
                    uint32_t done : 1;
                    uint32_t : 3;
                    uint32_t running : 1;
                    uint32_t : 3;
                    uint32_t waiting : 1;
                    uint32_t : 3;
                    uint32_t fail : 1;
                    uint32_t : 3;
                    uint32_t slow : 1;
                    uint32_t : 3;
                    uint32_t fast : 1;
                    uint32_t : 3;
                    uint32_t died : 1;
                };

            } status;

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t frac : 5;
                    uint32_t : 3;
                    uint32_t khz : 25;
                };

            } result;
        } fc0;
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

    struct PIO
    {
        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t sm_enable : 4;
                uint32_t sm_restart : 4;
                uint32_t clkdiv_restart : 4;
            };
        } control;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t rxfull : 4;
                uint32_t : 4;
                uint32_t rxempty : 4;
                uint32_t : 4;
                uint32_t txfull : 4;
                uint32_t : 4;
                uint32_t txempty : 4;
            };
        } fstat;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t rxstall : 4;
                uint32_t : 4;
                uint32_t rxunder : 4;
                uint32_t : 4;
                uint32_t txover : 4;
                uint32_t : 4;
                uint32_t txstall : 4;
            };
        } fdebug;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t tx0 : 4;
                uint32_t rx0 : 4;
                uint32_t tx1 : 4;
                uint32_t rx1 : 4;
                uint32_t tx2 : 4;
                uint32_t rx2 : 4;
                uint32_t tx3 : 4;
                uint32_t rx3 : 4;
            };
        } flevel;

        uint32_t txf[4];
        uint32_t rxf[4];

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t state_irq : 8;
            };
        };

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t state_irq_force : 8;
            };
        };

        uint32_t input_sync_bypass;
        uint32_t dbg_padout;
        uint32_t dbg_padoe;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t fifo_depth : 6;
                uint32_t : 2;
                uint32_t sm_count : 4;
                uint32_t : 4;
                uint32_t imem_size : 6;
            };
        } dbg_cfginfo;

        uint32_t instr_mem[32];

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t : 8;
                    uint32_t frac : 8;
                    uint32_t integer : 16;
                };
            } clkdiv;

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t status_n : 4;
                    uint32_t status_sel : 1;
                    uint32_t : 2;
                    uint32_t wrap_bottom : 5;
                    uint32_t wrap_top : 5;
                    uint32_t out_sticky : 1;
                    uint32_t inline_out_en : 1;
                    uint32_t out_en_sel : 5;
                    uint32_t jmp_pin : 5;
                    uint32_t side_pindir : 1;
                    uint32_t side_en : 1;
                    uint32_t exec_stalled : 1;
                };
            } execctrl;

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t : 16;
                    uint32_t autopush : 1;
                    uint32_t autopull : 1;
                    uint32_t in_shiftdir : 1;
                    uint32_t out_shiftdir : 1;
                    uint32_t push_tresh : 5;
                    uint32_t pull_tresh : 5;
                    uint32_t fjoin_tx : 1;
                    uint32_t fjoin_rx : 1;
                };
            } shiftctrl;

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t addr : 5;
                };
            };

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t instr : 16;
                };
            };

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t out_base : 5;
                    uint32_t set_base : 5;
                    uint32_t sideset_base : 5;
                    uint32_t in_base : 5;
                    uint32_t out_count : 6;
                    uint32_t set_count : 3;
                    uint32_t sideset_count : 3;
                };
            } pinctrl;
        } sm[4];

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t sm0_rxnempty : 1;
                uint32_t sm1_rxnempty : 1;
                uint32_t sm2_rxnempty : 1;
                uint32_t sm3_rxnempty : 1;
                uint32_t sm0_txfull : 1;
                uint32_t sm1_txfull : 1;
                uint32_t sm2_txfull : 1;
                uint32_t sm3_txfull : 1;
                uint32_t sm0 : 1;
                uint32_t sm1 : 1;
                uint32_t sm2 : 1;
                uint32_t sm3 : 1;
            };
        } intr;

        union
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t sm0_rxnempty : 1;
                    uint32_t sm1_rxnempty : 1;
                    uint32_t sm2_rxnempty : 1;
                    uint32_t sm3_rxnempty : 1;
                    uint32_t sm0_txfull : 1;
                    uint32_t sm1_txfull : 1;
                    uint32_t sm2_txfull : 1;
                    uint32_t sm3_txfull : 1;
                    uint32_t sm0 : 1;
                    uint32_t sm1 : 1;
                    uint32_t sm2 : 1;
                    uint32_t sm3 : 1;
                };
            } intr;

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t sm0_rxnempty : 1;
                    uint32_t sm1_rxnempty : 1;
                    uint32_t sm2_rxnempty : 1;
                    uint32_t sm3_rxnempty : 1;
                    uint32_t sm0_txfull : 1;
                    uint32_t sm1_txfull : 1;
                    uint32_t sm2_txfull : 1;
                    uint32_t sm3_txfull : 1;
                    uint32_t sm0 : 1;
                    uint32_t sm1 : 1;
                    uint32_t sm2 : 1;
                    uint32_t sm3 : 1;
                };
            } intf;

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t sm0_rxnempty : 1;
                    uint32_t sm1_rxnempty : 1;
                    uint32_t sm2_rxnempty : 1;
                    uint32_t sm3_rxnempty : 1;
                    uint32_t sm0_txfull : 1;
                    uint32_t sm1_txfull : 1;
                    uint32_t sm2_txfull : 1;
                    uint32_t sm3_txfull : 1;
                    uint32_t sm0 : 1;
                    uint32_t sm1 : 1;
                    uint32_t sm2 : 1;
                    uint32_t sm3 : 1;
                };
            } ints;
        } irq[1];
    };

    struct PADS_BANK_0
    {
        union
        {
            uint32_t : 32;
            union
            {
                uint32_t voltage_select : 1;
            };
        };

        union
        {
            uint32_t : 32;
            union
            {
                uint32_t slewfast : 1;
                uint32_t schmitt : 1;
                uint32_t pde : 1;
                uint32_t pue : 1;
                uint32_t drive : 2;
                uint32_t ie : 1;
                uint32_t od : 1;
            };
        } gpio[30];

        union
        {
            uint32_t : 32;
            union
            {
                uint32_t slewfast : 1;
                uint32_t schmitt : 1;
                uint32_t pde : 1;
                uint32_t pue : 1;
                uint32_t drive : 2;
                uint32_t ie : 1;
                uint32_t od : 1;
            };
        } swclk;

        union
        {
            uint32_t : 32;
            union
            {
                uint32_t slewfast : 1;
                uint32_t schmitt : 1;
                uint32_t pde : 1;
                uint32_t pue : 1;
                uint32_t drive : 2;
                uint32_t ie : 1;
                uint32_t od : 1;
            };
        } swd;
    };

    volatile SIO s_sio __attribute__((section(".sio_regs")));
    volatile IO_BANK_0 s_io_bank_0 __attribute__((section(".io_bank_0_regs")));
    volatile PADS_BANK_0 s_pads_bank_0 __attribute__((section(".pads_bank_0_regs")));
    volatile RESETS s_resets __attribute__((section(".reset_regs")));
    volatile Clocks s_clocks __attribute__((section(".clock_regs")));
    volatile RSOC s_rsoc __attribute__((section(".rsoc_regs")));
    volatile XSOC s_xsoc __attribute__((section(".xsoc_regs")));
    volatile PLL s_pll_sys __attribute__((section(".pll_sys_regs")));
    volatile PLL s_pll_usb __attribute__((section(".pll_usb_regs")));
    volatile PIO s_pio_0 __attribute__((section(".pio_0_regs")));
    volatile PIO s_pio_1 __attribute__((section(".pio_1_regs")));
}