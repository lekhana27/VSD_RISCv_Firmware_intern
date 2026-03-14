
#ifndef __CH32V00x_USART_DEBUG_H
#define __CH32V00x_USART_DEBUG_H

#include <stdint.h>
#include <driver_gpio.h>
#include <driver_rcc.h>

/* ================= REGISTER DEFINITIONS ================= */

#define RCC_APB2ENR   (*(volatile uint32_t*)0x40021018)
#define GPIOD_CRH     (*(volatile uint32_t*)0x40011404)
#define USART1_BASE   (0x40013800U)

typedef struct
{
    volatile uint16_t STATR;
    uint16_t RESERVED0;
    volatile uint16_t DATAR;
    uint16_t RESERVED1;
    volatile uint16_t BRR;
    uint16_t RESERVED2;
    volatile uint16_t CTLR1;
    uint16_t RESERVED3;
    volatile uint16_t CTLR2;
    uint16_t RESERVED4;
    volatile uint16_t CTLR3;
    uint16_t RESERVED5;
    volatile uint16_t GPR;
    uint16_t RESERVED6;
} USART_RegDef_t;

#define USART1 ((USART_RegDef_t*)USART1_BASE)

/* RCC bits */
#define RCC_IOPDEN   (1 << 5)
#define RCC_USART1EN (1 << 14)

/* USART flags */
#define USART_TXE    (1 << 7)
#define USART_UE     (1 << 13)
#define USART_TE     (1 << 3)

/* special value → print string only */
#define UART_NO_NUMBER  -1


void HAL_UART_Init(void);
void HAL_UART_SendChar(char c);
char HAL_UART_ReadChar(void);
void HAL_UART_SendString(const char *s);
void HAL_UART_ReadLine(char *buf, uint8_t maxLen);

/*
 * UART_Print
 *  str  : string to print
 *  val  : number to print OR UART_NO_NUMBER
 *  base : 10 (decimal) or 16 (hex)
 */
void HAL_UART_Print(const char *str, int32_t val, uint8_t base);

#endif /* __CH32V00x_USART_DEBUG_H */