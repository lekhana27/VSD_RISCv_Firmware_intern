#ifndef __CH32V00x_GPIO_H
#define __CH32V00x_GPIO_H

#include <stddef.h>
#include <stdint.h>

/* Memory Map Base Addresses of System Memory and Peripherals */
#define FLASH_START (0x00000000U)
#define SRAM_START (0x20000000U)
#define PERIPHERALS_BASEADDR (0x40000000U)

/* Memory Map Base Addresses of System Buses */
#define APB1PERIPH_BASEADDR (PERIPHERALS_BASEADDR)
#define APB2PERIPH_BASEADDR (PERIPHERALS_BASEADDR + 0x10000U)
#define AHBPERIPH_BASEADDR (PERIPHERALS_BASEADDR + 0x20000U)

/* GPIO (Port A, C, D) Peripheral Base Addresses */
#define GPIOA_BASEADDR (APB2PERIPH_BASEADDR + 0x0800U)
#define GPIOC_BASEADDR (APB2PERIPH_BASEADDR + 0x1000U)
#define GPIOD_BASEADDR (APB2PERIPH_BASEADDR + 0x1400U)

/* Assign GPIO Ports Base Addresses to the GPIO Registers */
#define GPIOA ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOC ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t *)GPIOD_BASEADDR)

typedef struct
{
    // GPIO Registers
    volatile uint32_t CFGLR;
    uint32_t RESERVED0;
    volatile uint32_t INDR;
    volatile uint32_t OUTDR;
    volatile uint32_t BSHR;
    volatile uint32_t BCR;
    volatile uint32_t LCKR;
} GPIO_RegDef_t;

// GPIO Pin Modes
typedef enum {
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT_10MHz,
    GPIO_MODE_OUTPUT_2MHz,
    GPIO_MODE_OUTPUT_50MHz
} GPIO_Mode_t;

// GPIO Configurations
typedef enum {
    GPIO_CNF_PUSH_PULL = 0,
    GPIO_CNF_OPEN_DRAIN,
    GPIO_CNF_AF_PUSH_PULL,
    GPIO_CNF_AF_OPEN_DRAIN
} GPIO_CNF_t;

// Initialize a single GPIO pin
void HAL_GPIO_Init(GPIO_RegDef_t *GPIOx, uint8_t pin, GPIO_Mode_t mode, GPIO_CNF_t cnf);

// Write pin (0 = LOW, 1 = HIGH)
void HAL_GPIO_WritePin(GPIO_RegDef_t *GPIOx, uint8_t pin, uint8_t state);

// Toggle pin
void HAL_GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t pin);

// Read pin (returns 0 or 1)
uint8_t HAL_GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t pin);

#endif //__CH32V00x_GPIO_H