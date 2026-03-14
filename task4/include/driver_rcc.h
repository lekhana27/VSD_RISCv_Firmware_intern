#ifndef DRIVER_RCC_H
#define DRIVER_RCC_H

#include <stddef.h>
#include <stdint.h>
#include <driver_gpio.h>
#include "system_ch32v00x.h"

/* APB2_peripheral */
#define RCC_APB2Periph_AFIO              ((uint32_t)0x00000001)
#define RCC_APB2Periph_GPIOA             ((uint32_t)0x00000004)
#define RCC_APB2Periph_GPIOC             ((uint32_t)0x00000010)
#define RCC_APB2Periph_GPIOD             ((uint32_t)0x00000020)

#define RCC_BASEADDR                             (AHBPERIPH_BASEADDR + 0x1000)
#define SYSTICK_BASEADDR                         (0xE000F000U)

#define RCC                                     ((RCC_RegDef_t *)RCC_BASEADDR)

#define SysTick         ((SysTick_RegDef_t *) SYSTICK_BASEADDR)

/* ================== System Clock ================== */
#define SYSCLK (24000000U)  // 24 MHz for CH32V00x


// APB2 Peripherals (only the ones in SDK)
typedef enum {
    RCC_GPIOA = RCC_APB2Periph_GPIOA,
    RCC_GPIOC = RCC_APB2Periph_GPIOC,
    RCC_GPIOD = RCC_APB2Periph_GPIOD,
    RCC_AFIO  = RCC_APB2Periph_AFIO,
    // Add more if SDK defines them
} RCC_APB2Periph_t;

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

/* memory mapped structure for SysTick */
typedef struct
{
    // Systick Registers
    volatile uint32_t CTLR;
    volatile uint32_t SR;
    volatile uint32_t CNT;
    uint32_t RESERVED0;
    volatile uint32_t CMP;
    uint32_t RESERVED1;
}SysTick_RegDef_t;

// Enable/Disable APB2 peripheral clock
void HAL_RCC_APB2_Enable(RCC_APB2Periph_t periph);
void HAL_RCC_APB2_Disable(RCC_APB2Periph_t periph);

// Delay 
void SysTick_Handler(void);
void HAL_Delay_Init(void);
void HAL_Delay_us(uint32_t us);
void HAL_Delay_ms(uint32_t ms);

#endif