#include "rp2040_regs.hpp"

namespace bsp::rp2040
{
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
    volatile PWM s_pwm __attribute__((section(".pwm_regs")));
    volatile I2C s_i2c_0 __attribute__((section(".i2c_0_regs")));
    volatile I2C s_i2c_1 __attribute__((section(".i2c_1_regs")));
    volatile Uart s_uart_0 __attribute__((section(".uart_0_regs")));
    volatile Uart s_uart_1 __attribute__((section(".uart_1_regs")));
    volatile SPI s_spi_0 __attribute__((section(".spi_0_regs")));
    volatile SPI s_spi_1 __attribute__((section(".spi_1_regs")));
    volatile DMA s_dma __attribute__((section(".dma_regs")));
    volatile DMA_INTR s_dma_intr __attribute__((section(".dma_intr_regs")));
    volatile DMA_DBG s_dma_dbg __attribute__((section(".dma_dbg_regs")));
}