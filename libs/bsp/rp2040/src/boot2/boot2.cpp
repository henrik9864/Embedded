#include <cstdint>

#define XIP_SSI_BASE 0x18000000

#define SSI_CTRLR0      XIP_SSI_BASE + 0x00
#define SSI_CTRLR1      XIP_SSI_BASE + 0x04
#define SSI_SSIENR      XIP_SSI_BASE + 0x08
#define SSI_BAUDR       XIP_SSI_BASE + 0x14
#define SSI_SPI_CTRLR0  XIP_SSI_BASE + 0xf4

#define CTRLR0_XIP \
    (0x0 << 21) |  /* Standard 1-bit SPI serial frames */ \
    (31  << 16) |  /* 32 clocks per data frame */ \
    (0x3 << 8)     /* Send instr + addr, receive data */

#define SPI_CTRLR0_XIP \
    (0xEB << 24) |  /* Value of instruction prefix */ \
    (6 << 2)     |  /* Total number of address + mode bits */ \
    (2 << 8)     |  /* 8 bit command prefix (field value is bits divided by 4) */ \
    (0x0 << 0)      /* command and address both in serial format */

inline void put(const uint32_t a1, const uint32_t a2)
{
    *reinterpret_cast<uint32_t*>(a1) = a2;
}

__attribute__((section(".boot2")))
void _stage2_boot()
{
    // Disable SSI to allow further config
    put(SSI_SSIENR, 0);

    // Set baud rate
    put(SSI_SSIENR, 4);
    put(SSI_CTRLR0, CTRLR0_XIP);
    put(SSI_SPI_CTRLR0, SPI_CTRLR0_XIP);

    // NDF=0 (single 32b read)
    put(SSI_CTRLR1, 0);

    // Re-enable SSI
    put(SSI_SSIENR, 1);

    // Exit from boot2
    //exit();
    //__asm("pop {r0}");
    __asm("#include \"exit_from_boot2.S\"");
    //__asm("msr msp, r0");
    //#include "exit_from_boot.s";
}