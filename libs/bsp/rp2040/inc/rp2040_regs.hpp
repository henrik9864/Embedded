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
            struct
            {
                uint32_t voltage_select : 1;
            };
        };

        union
        {
            uint32_t : 32;
            struct
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
            struct
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
            struct
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

    struct PWM
    {
        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t en : 1;
                    uint32_t ph_correct : 1;
                    uint32_t a_inv : 1;
                    uint32_t b_inv : 1;
                    uint32_t divmode : 2;
                    uint32_t ph_ret : 1;
                    uint32_t ph_adv : 1;
                };
            } csr;

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t frac : 4;
                    uint32_t integer : 8;
                };
            } div;

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t ctr : 16;
                };
            };

            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t a : 16;
                    uint32_t b : 16;
                };
            } cc;


            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t counter_wrap : 16;
                };
            } top;
        } ch[8];

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t ch0 : 1;
                uint32_t ch1 : 1;
                uint32_t ch2 : 1;
                uint32_t ch3 : 1;
                uint32_t ch4 : 1;
                uint32_t ch5 : 1;
                uint32_t ch6 : 1;
                uint32_t ch7 : 1;
            };
        } en;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t ch0 : 1;
                uint32_t ch1 : 1;
                uint32_t ch2 : 1;
                uint32_t ch3 : 1;
                uint32_t ch4 : 1;
                uint32_t ch5 : 1;
                uint32_t ch6 : 1;
                uint32_t ch7 : 1;
            };
        } intr;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t ch0 : 1;
                uint32_t ch1 : 1;
                uint32_t ch2 : 1;
                uint32_t ch3 : 1;
                uint32_t ch4 : 1;
                uint32_t ch5 : 1;
                uint32_t ch6 : 1;
                uint32_t ch7 : 1;
            };
        } inte;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t ch0 : 1;
                uint32_t ch1 : 1;
                uint32_t ch2 : 1;
                uint32_t ch3 : 1;
                uint32_t ch4 : 1;
                uint32_t ch5 : 1;
                uint32_t ch6 : 1;
                uint32_t ch7 : 1;
            };
        } intf;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t ch0 : 1;
                uint32_t ch1 : 1;
                uint32_t ch2 : 1;
                uint32_t ch3 : 1;
                uint32_t ch4 : 1;
                uint32_t ch5 : 1;
                uint32_t ch6 : 1;
                uint32_t ch7 : 1;
            };
        } ints;
    };

    struct I2C
    {
        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t master_mode : 1;
                    uint32_t speed : 2;
                    uint32_t slave_10_bit_addr : 1;
                    uint32_t master_10_bit_addr : 1;
                    uint32_t restart_en : 1;
                    uint32_t slave_disable : 1;
                    uint32_t stop_det_if_addressed : 1;
                    uint32_t tx_empty_ctrl : 1;
                    uint32_t rx_fifo_full_hld_ctrl : 1;
                    uint32_t stop_det_if_master_active : 1;
                };
            };
        } control;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t tar : 10;
                    uint32_t gc_or_start : 1;
                    uint32_t special : 1;
                };
            };
        } tar;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t sar : 10;
                };
            };
        } sar;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t dat : 8;
                    uint32_t cmd : 1;
                    uint32_t stop : 1;
                    uint32_t restart : 1;
                    uint32_t first_data_byte : 1;
                };
            };
        } data_cmd;

        struct
        {
            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t scl_hcnt : 16;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t scl_lcnt : 16;
                    };
                };
            };
        } ss;

        struct
        {
            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t scl_hcnt : 16;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t scl_lcnt : 16;
                    };
                };
            };
        } fs;

        struct
        {
            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t rx_under : 1;
                        uint32_t rx_over : 1;
                        uint32_t rx_full : 1;
                        uint32_t tx_over : 1;
                        uint32_t tx_empty : 1;
                        uint32_t rd_req : 1;
                        uint32_t tx_abrt : 1;
                        uint32_t rx_done : 1;
                        uint32_t activity : 1;
                        uint32_t stop_det : 1;
                        uint32_t start_det : 1;
                        uint32_t gen_call : 1;
                        uint32_t restart_det : 1;
                    };
                };
            } status;

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t rx_under : 1;
                        uint32_t rx_over : 1;
                        uint32_t rx_full : 1;
                        uint32_t tx_over : 1;
                        uint32_t tx_empty : 1;
                        uint32_t rd_req : 1;
                        uint32_t tx_abrt : 1;
                        uint32_t rx_done : 1;
                        uint32_t activity : 1;
                        uint32_t stop_det : 1;
                        uint32_t start_det : 1;
                        uint32_t gen_call : 1;
                        uint32_t restart_det : 1;
                    };
                };
            } mask;

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t rx_under : 1;
                        uint32_t rx_over : 1;
                        uint32_t rx_full : 1;
                        uint32_t tx_over : 1;
                        uint32_t tx_empty : 1;
                        uint32_t rd_req : 1;
                        uint32_t tx_abrt : 1;
                        uint32_t rx_done : 1;
                        uint32_t activity : 1;
                        uint32_t stop_det : 1;
                        uint32_t start_det : 1;
                        uint32_t gen_call : 1;
                        uint32_t restart_det : 1;
                    };
                };
            } raw_mask;
        } interupt;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t rx_tl : 8;
                };
            };
        };

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t tx_tl : 8;
                };
            };
        };

        struct
        {
            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t interupt : 1;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t rx_under : 1;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t rx_over : 1;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t tx_over : 1;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t rd_req : 1;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t tx_abrt : 1;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t rx_done : 1;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t activity : 1;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t stop_det : 1;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t start_det : 1;
                    };
                };
            };

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t gen_call : 1;
                    };
                };
            };
        } clr;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t enable : 1;
                    uint32_t abort : 1;
                    uint32_t tx_cmd_block : 1;
                };
            };
        } enable;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t activity : 1;
                    uint32_t tfnf : 1;
                    uint32_t tfe : 1;
                    uint32_t rfne : 1;
                    uint32_t rff : 1;
                    uint32_t mst_activity : 1;
                    uint32_t slv_activity : 1;
                };
            };
        } status;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t txflr : 5;
                };
            };
        };

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t rxflr : 5;
                };
            };
        };

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t tx : 16;
                    uint32_t rx : 8;
                };
            };
        } sda_hold;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t abrt_7b_addr_noack : 1;
                    uint32_t abrt_10addr1_noack : 1;
                    uint32_t abrt_10addr2_noack : 1;
                    uint32_t abrt_txdata_noack : 1;
                    uint32_t abrt_gcall_noack : 1;
                    uint32_t abrt_gcall_read : 1;
                    uint32_t abrt_hs_ackdet : 1;
                    uint32_t abrt_sbyte_ackdet : 1;
                    uint32_t abrt_hs_norstr : 1;
                    uint32_t abrt_sbyte_norstr : 1;
                    uint32_t abrt_10b_rd_norstr : 1;
                    uint32_t abrt_master_dis : 1;
                    uint32_t abrt_lost : 1;
                    uint32_t abrt_slvflush_txfifo : 1;
                    uint32_t abrt_slv_arblost : 1;
                    uint32_t abrt_slvrd_intx : 1;
                    uint32_t abrt_user_abrt : 1;
                    uint32_t : 6;
                    uint32_t tx_flush_cnt : 9;
                };
            };
        } tx_abrt_source;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t nack : 1;
                };
            };
        } slv_data_nack_only;

        struct
        {
            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t rdmae : 1;
                        uint32_t tdmae : 1;
                    };
                };
            } cr;

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t dmatdl : 4;
                    };
                };
            } tdlr;

            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t dmardl : 4;
                    };
                };
            } rdlr;
        } dma;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t sda_setup : 8;
                };
            };
        };

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t ack_general_call : 1;
                };
            };
        };

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t en : 1;
                    uint32_t slv_disabled_while_busy : 1;
                    uint32_t slv_rx_data_lost : 1;
                };
            };
        } enable_status;

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t fs_spklen : 8;
                };
            };
        };

        struct
        {
            union
            {
                uint32_t : 32;
                struct
                {
                    uint32_t clr_restart_det : 8;
                };
            };
        };

        struct
        {
            struct
            {
                union
                {
                    uint32_t : 32;
                    struct
                    {
                        uint32_t apb_data_width : 2;
                        uint32_t max_speed_mode : 2;
                        uint32_t hc_count_values : 1;
                        uint32_t inter_io : 1;
                        uint32_t has_dma : 1;
                        uint32_t add_encoded_params : 1;
                        uint32_t rx_buffer_depth : 8;
                        uint32_t tx_buffer_depth : 8;
                    };
                };
            } param_1;

            uint32_t version;
            uint32_t type;
        } comp;
    };

    struct Uart
    {
        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t data : 8;
                uint32_t fe : 1;
                uint32_t pe : 1;
                uint32_t be : 1;
                uint32_t oe : 1;
            };
        } dr;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t fe : 1;
                uint32_t pe : 1;
                uint32_t be : 1;
                uint32_t oe : 1;
            };
        } rsr;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t cts : 1;
                uint32_t dsr : 1;
                uint32_t dcd : 1;
                uint32_t busy : 1;
                uint32_t rxfe : 1;
                uint32_t txff : 1;
                uint32_t rxff : 1;
                uint32_t txfe : 1;
                uint32_t ri : 1;
            };
        } fr;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t ilpdvsr : 8;
            };
        } ilpr;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t baud_divint : 16;
            };
        } ibrd;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t baud_divfrac : 16;
            };
        } fbrd;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t brk : 1;
                uint32_t pen : 1;
                uint32_t eps : 1;
                uint32_t stp2 : 1;
                uint32_t fen : 1;
                uint32_t wlen : 1;
                uint32_t sps : 1;
            };
        } lcr_h;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t uarten : 1;
                uint32_t siren : 1;
                uint32_t sirlp : 1;
                uint32_t : 4;
                uint32_t lbe : 1;
                uint32_t txe : 1;
                uint32_t rxe : 1;
                uint32_t dtr : 1;
                uint32_t rts : 1;
                uint32_t out1 : 1;
                uint32_t out2 : 1;
                uint32_t rtsen : 1;
                uint32_t ctsen : 1;
            };
        } cr;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t txiflsel : 3;
                uint32_t rxiflsel : 3;
            };
        } ifls;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t rimm : 1;
                uint32_t ctsmim : 1;
                uint32_t dcdmim : 1;
                uint32_t dsrmim : 1;
                uint32_t rxim : 1;
                uint32_t txim : 1;
                uint32_t rtim : 1;
                uint32_t feim : 1;
                uint32_t peim : 1;
                uint32_t beim : 1;
                uint32_t oeim : 1;
            };
        } imsc;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t rirmis : 1;
                uint32_t ctsrmis : 1;
                uint32_t dcdrmis : 1;
                uint32_t dsrrmis : 1;
                uint32_t rxris : 1;
                uint32_t txris : 1;
                uint32_t rtris : 1;
                uint32_t feris : 1;
                uint32_t peris : 1;
                uint32_t beris : 1;
                uint32_t oeris : 1;
            };
        } ris;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t rimmis : 1;
                uint32_t ctsmmis : 1;
                uint32_t dcdmmis : 1;
                uint32_t dsrmmis : 1;
                uint32_t rxmis : 1;
                uint32_t txmis : 1;
                uint32_t rtmis : 1;
                uint32_t femis : 1;
                uint32_t pemis : 1;
                uint32_t bemis : 1;
                uint32_t oemis : 1;
            };
        } mis;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t rmic : 1;
                uint32_t ctsmic : 1;
                uint32_t dcdmic : 1;
                uint32_t dsrmic : 1;
                uint32_t rxic : 1;
                uint32_t txic : 1;
                uint32_t rtic : 1;
                uint32_t feic : 1;
                uint32_t peic : 1;
                uint32_t beic : 1;
                uint32_t oeic : 1;
            };
        } icr;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t rxdmae : 1;
                uint32_t txdmae : 1;
                uint32_t dmaonerr : 1;
            };
        } dmacr;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t partnumber0 : 8;
            };
        } periphid0;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t partnumber1 : 4;
                uint32_t designer0 : 4;
            };
        } periphid1;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t designer1 : 4;
                uint32_t revision : 4;
            };
        } periphid2;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t configuration : 8;
            };
        } periphid3;

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t uartpcellid0 : 8;
            };
        };

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t uartpcellid1 : 8;
            };
        };

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t uartpcellid2 : 8;
            };
        };

        union
        {
            uint32_t : 32;
            struct
            {
                uint32_t uartpcellid3 : 8;
            };
        };
    };

    extern volatile SIO s_sio;
    extern volatile IO_BANK_0 s_io_bank_0;
    extern volatile PADS_BANK_0 s_pads_bank_0;
    extern volatile RESETS s_resets;
    extern volatile Clocks s_clocks;
    extern volatile RSOC s_rsoc;
    extern volatile XSOC s_xsoc;
    extern volatile PLL s_pll_sys;
    extern volatile PLL s_pll_usb;
    extern volatile PIO s_pio_0;
    extern volatile PIO s_pio_1;
    extern volatile PWM s_pwm;
    extern volatile I2C s_i2c_0;
    extern volatile I2C s_i2c_1;
    extern volatile Uart s_uart_0;
    extern volatile Uart s_uart_1;
}