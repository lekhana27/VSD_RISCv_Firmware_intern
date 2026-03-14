#ifndef DRIVER_PWM_H
#define DRIVER_PWM_H

#include <stdint.h>
#include "driver_usart_debug.h"
#include "driver_rcc.h"
#include "driver_gpio.h"
#include "system_ch32v00x.h"

/* Peripheral memory map */
#define FLASH_BASE                              ((uint32_t)0x08000000U) /* FLASH base address in the alias region */
#define SRAM_BASE                               ((uint32_t)0x20000000U) /* SRAM base address in the alias region */
#define PERIPHERALS_BASEADDR                    (0x40000000U) /* Peripheral base address in the alias region */

#define APB1PERIPH_BASEADDR                         (PERIPHERALS_BASEADDR)
//#define APB2PERIPH_BASEADDR                         (PERIPHERALS_BASEADDR + 0x10000)
#define AHBPERIPH_BASEADDR                          (PERIPHERALS_BASEADDR + 0x20000U)
#define TIM1_BASEADDR                               (APB2PERIPH_BASEADDR + 0x2C00)
#define TIM2_BASEADDR                               (APB1PERIPH_BASEADDR + 0x0000)
#define TIM2                                        ((TIM_RegDef_t *)TIM2_BASEADDR)
#define TIM1                                        ((TIM_RegDef_t *)TIM1_BASEADDR)

#define RCC_BASEADDR                                (AHBPERIPH_BASEADDR + 0x1000)
#define RCC                                         ((RCC_RegDef_t *)RCC_BASEADDR)


/* TIM Registers */
typedef struct
{
    volatile uint16_t CTLR1;
    uint16_t      RESERVED0;
    volatile uint16_t CTLR2;
    uint16_t      RESERVED1;
    volatile uint16_t SMCFGR;
    uint16_t      RESERVED2;
    volatile uint16_t DMAINTENR;
    uint16_t      RESERVED3;
    volatile uint16_t INTFR;
    uint16_t      RESERVED4;
    volatile uint16_t SWEVGR;
    uint16_t      RESERVED5;
    volatile uint16_t CHCTLR1;
    uint16_t      RESERVED6;
    volatile uint16_t CHCTLR2;
    uint16_t      RESERVED7;
    volatile uint16_t CCER;
    uint16_t      RESERVED8;
    volatile uint16_t CNT;
    uint16_t      RESERVED9;
    volatile uint16_t PSC;
    uint16_t      RESERVED10;
    volatile uint16_t ATRLR;
    uint16_t      RESERVED11;
    volatile uint16_t RPTCR;
    uint16_t      RESERVED12;
    volatile uint32_t CH1CVR;
    volatile uint32_t CH2CVR;
    volatile uint32_t CH3CVR;
    volatile uint32_t CH4CVR;
    volatile uint16_t BDTR;
    uint16_t      RESERVED13;
    volatile uint16_t DMACFGR;
    uint16_t      RESERVED14;
    volatile uint16_t DMAADR;
    uint16_t      RESERVED15;
} TIM_RegDef_t;

#if 0
typedef struct
{
    // RCC Peripheral Registers
    volatile uint32_t CTLR;
    volatile uint32_t CFGR0;
    volatile uint32_t INTR;
    volatile uint32_t APB2PRSTR;
    volatile uint32_t APB1PRSTR;
    volatile uint32_t AHBPCENR;
    volatile uint32_t APB2PCENR;
    volatile uint32_t APB1PCENR;
    volatile uint32_t RESERVED0;
    volatile uint32_t RSTSCKR;
} RCC_RegDef_t;
#endif

void HAL_PWM_Init(uint32_t freq_hz, uint16_t resolution);
void HAL_PWM_SetDuty(uint16_t duty);
void HAL_PWM_Start(void);
void HAL_PWM_Stop(void);

#endif