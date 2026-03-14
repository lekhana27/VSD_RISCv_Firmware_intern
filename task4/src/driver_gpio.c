#include <stdint.h>
#include <driver_gpio.h>

/*********************************************************************
 * @fn      HAL_GPIO_Init
 *
 * @brief   Initializes the specified GPIO pin with the given mode 
 *          and configuration.
 *
 * @param   GPIOx - Pointer to the GPIO peripheral (GPIOA, GPIOC, GPIOD, etc.)
 * @param   pin   - Pin number to configure (0-15)
 * @param   mode  - Pin mode (Input, Output, Analog, etc.)
 * @param   cnf   - Pin configuration (Push-Pull, Open-Drain, Pull-Up, Pull-Down, etc.)
 *
 * @return  none
 */
void HAL_GPIO_Init(GPIO_RegDef_t *GPIOx, uint8_t pin, GPIO_Mode_t mode, GPIO_CNF_t cnf)
{
    // Clear 4 bits for this pin in CFGLR register
    GPIOx->CFGLR &= ~(0xF << (pin * 4));

    // Combine CNF (upper 2 bits) and MODE (lower 2 bits)
    uint32_t val = ((cnf << 2) | mode) & 0xF;

    // Set new configuration for the pin
    GPIOx->CFGLR |= (val << (pin * 4));
}

/*********************************************************************
 * @fn      HAL_GPIO_WritePin
 *
 * @brief   Sets or resets the specified GPIO pin.
 *
 * @param   GPIOx - Pointer to the GPIO peripheral
 * @param   pin   - Pin number to write (0-7)
 * @param   state - Pin state: 0 = LOW, 1 = HIGH
 *
 * @return  none
 */
void HAL_GPIO_WritePin(GPIO_RegDef_t *GPIOx, uint8_t pin, uint8_t state)
{
    if(state)
        GPIOx->OUTDR |= (1 << pin);    // Set pin HIGH
    else
        GPIOx->OUTDR &= ~(1 << pin);   // Set pin LOW
}

/*********************************************************************
 * @fn      HAL_GPIO_TogglePin
 *
 * @brief   Toggles the output state of the specified GPIO pin.
 *
 * @param   GPIOx - Pointer to the GPIO peripheral
 * @param   pin   - Pin number to toggle (0-7)
 *
 * @return  none
 */
void HAL_GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t pin)
{
    GPIOx->OUTDR ^= (1 << pin);  // XOR to toggle the pin
}

/*********************************************************************
 * @fn      HAL_GPIO_ReadPin
 *
 * @brief   Reads the current logic level of the specified GPIO pin.
 *
 * @param   GPIOx - Pointer to the GPIO peripheral
 * @param   pin   - Pin number to read (0-15)
 *
 * @return  uint8_t - Pin state: 0 = LOW, 1 = HIGH
 */
uint8_t HAL_GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t pin)
{
    return (GPIOx->INDR >> pin) & 0x1;  // Shift and mask to get pin value
}