#include <cstdint>

extern "C" void __stop() { while (true); }

#define DEFINE_DEFAULT_ISR(name) \
    __attribute__((weak, alias("__stop"))) \
    void name();

DEFINE_DEFAULT_ISR(defaultISR)
DEFINE_DEFAULT_ISR(ResetHandler)
DEFINE_DEFAULT_ISR(NMI_Handler)
DEFINE_DEFAULT_ISR(HardFault_Handler)
DEFINE_DEFAULT_ISR(MemManage_Handler)
DEFINE_DEFAULT_ISR(BusFault_Handler)
DEFINE_DEFAULT_ISR(UsageFault_Handler)
DEFINE_DEFAULT_ISR(SVC_Handler)
DEFINE_DEFAULT_ISR(DebugMon_Handler)
DEFINE_DEFAULT_ISR(PendSV_Handler)
DEFINE_DEFAULT_ISR(SysTick_Handler)
DEFINE_DEFAULT_ISR(USART1_IRQHandler)

extern std::uint32_t _estack;
extern std::uintptr_t g_pfnVectors[];
std::uintptr_t g_pfnVectors[]
__attribute__((section(".isr_vector"))) {
        // Stack Ptr initialization
        reinterpret_cast<std::uintptr_t>(&_estack),
        // Entry point
        reinterpret_cast<std::uintptr_t>(ResetHandler),
        // Exceptions
        reinterpret_cast<std::uintptr_t>(NMI_Handler),              /* NMI_Handler */
        reinterpret_cast<std::uintptr_t>(HardFault_Handler),        /* HardFault_Handler */
        reinterpret_cast<std::uintptr_t>(MemManage_Handler),        /* MemManage_Handler */
        reinterpret_cast<std::uintptr_t>(BusFault_Handler),         /* BusFault_Handler */
        reinterpret_cast<std::uintptr_t>(UsageFault_Handler),       /* UsageFault_Handler */
        reinterpret_cast<std::uintptr_t>(nullptr),                  /* 0 */
        reinterpret_cast<std::uintptr_t>(nullptr),                  /* 0 */
        reinterpret_cast<std::uintptr_t>(nullptr),                  /* 0 */
        reinterpret_cast<std::uintptr_t>(nullptr),                  /* 0 */
        reinterpret_cast<std::uintptr_t>(SVC_Handler),              /* SVC_Handler */
        reinterpret_cast<std::uintptr_t>(DebugMon_Handler),         /* DebugMon_Handler */
        reinterpret_cast<std::uintptr_t>(nullptr),                  /* 0 */
        reinterpret_cast<std::uintptr_t>(PendSV_Handler),           /* PendSV_Handler */
        reinterpret_cast<std::uintptr_t>(SysTick_Handler),          /* SysTick_Handler */
        // External Interrupts
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* WWDG_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* PVD_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TAMP_STAMP_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* RTC_WKUP_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* FLASH_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* RCC_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* EXTI0_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* EXTI1_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* EXTI2_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* EXTI3_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* EXTI4_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA1_Stream0_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA1_Stream1_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA1_Stream2_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA1_Stream3_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA1_Stream4_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA1_Stream5_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA1_Stream6_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* ADC_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* CAN1_TX_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* CAN1_RX0_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* CAN1_RX1_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* CAN1_SCE_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* EXTI9_5_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM1_BRK_TIM9_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM1_UP_TIM10_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM1_TRG_COM_TIM11_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM1_CC_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM2_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM3_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM4_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* I2C1_EV_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* I2C1_ER_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* I2C2_EV_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* I2C2_ER_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* SPI1_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* SPI2_IRQHandler */
        reinterpret_cast<std::uintptr_t>(USART1_IRQHandler),        /* USART1_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* USART2_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* USART3_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* EXTI15_10_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* RTC_Alarm_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* OTG_FS_WKUP_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM8_BRK_TIM12_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM8_UP_TIM13_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM8_TRG_COM_TIM14_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM8_CC_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA1_Stream7_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* FMC_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* SDMMC1_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM5_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* SPI3_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* UART4_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* UART5_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM6_DAC_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* TIM7_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA2_Stream0_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA2_Stream1_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA2_Stream2_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA2_Stream3_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA2_Stream4_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* ETH_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* ETH_WKUP_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* CAN2_TX_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* CAN2_RX0_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* CAN2_RX1_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* CAN2_SCE_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* OTG_FS_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA2_Stream5_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA2_Stream6_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA2_Stream7_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* USART6_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* I2C3_EV_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* I2C3_ER_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* OTG_HS_EP1_OUT_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* OTG_HS_EP1_IN_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* OTG_HS_WKUP_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* OTG_HS_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DCMI_IRQHandler */
        reinterpret_cast<std::uintptr_t>(nullptr),                  /* 0 */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* RNG_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* FPU_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* UART7_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* UART8_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* SPI4_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* SPI5_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* SPI6_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* SAI1_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* LTDC_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* LTDC_ER_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* DMA2D_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* SAI2_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* QUADSPI_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* LPTIM1_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* CEC_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* I2C4_EV_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* I2C4_ER_IRQHandler */
        reinterpret_cast<std::uintptr_t>(defaultISR),               /* SPDIF_RX_IRQHandler */
};