#include "driver_rcc.h"

/*********************************************************************
 * @fn      HAL_RCC_APB2_Enable
 *
 * @brief   Enables the clock for the specified APB2 peripheral.
 *
 * @param   periph - Peripheral bitmask to enable (RCC_APB2Periph_t)
 *
 * @return  none
 */
void HAL_RCC_APB2_Enable(RCC_APB2Periph_t periph)
{
    RCC->APB2PCENR |= periph;
}

/*********************************************************************
 * @fn      HAL_RCC_APB2_Disable
 *
 * @brief   Disables the clock for the specified APB2 peripheral.
 *
 * @param   periph - Peripheral bitmask to disable (RCC_APB2Periph_t)
 *
 * @return  none
 */
void HAL_RCC_APB2_Disable(RCC_APB2Periph_t periph)
{
    RCC->APB2PCENR &= ~periph;
}

/*********************************************************************
 * @var     ms_ticks
 *
 * @brief   Millisecond tick counter used by SysTick for delays.
 */
volatile uint32_t ms_ticks = 0;

/*********************************************************************
 * @fn      SysTick_Handler
 *
 * @brief   SysTick interrupt handler. Increments the millisecond counter.
 *
 * @note    This handler is automatically called every SysTick interrupt.
 *
 * @return  none
 */
void SysTick_Handler(void)
{
    ms_ticks++;
}

/*********************************************************************
 * @fn      HAL_Delay_Init
 *
 * @brief   Initializes the SysTick timer for 1ms tick generation.
 *
 * @note    Sets up SysTick without enabling interrupts. For interrupt-
 *          based delays, ensure the NVIC exception is enabled.
 *
 * @return  none
 */
void HAL_Delay_Init(void)
{
    ms_ticks = 0;
    SysTick->CMP = SYSCLK / 1000 - 1;  // 1ms tick
    SysTick->CNT = 0;
    SysTick->CTLR = 5; // enable SysTick with processor clock, interrupts off

    // For interrupt-based delay, enable the IRQ in NVIC
    // CH32V003: usually SysTick exception is always active
}

/*********************************************************************
 * @fn      HAL_Delay_ms
 *
 * @brief   Provides a blocking delay for a specified number of milliseconds.
 *
 * @param   ms - Number of milliseconds to delay
 *
 * @return  none
 *
 * @note    Uses a simple busy-wait loop. Accuracy depends on CPU clock.
 */
void HAL_Delay_ms(uint32_t ms)
{
    #if 1
    for (uint32_t i = 0; i < ms; i++)
        for (volatile uint32_t j = 0; j < 8000; j++); // ~1ms
    #endif

    #if 0
    uint32_t start = ms_ticks;
    while ((ms_ticks - start) < ms);
    #endif
}


/*********************************************************************
 * @fn      HAL_Delay_us
 *
 * @brief   Provides a blocking delay for a specified number of microseconds.
 *
 * @param   us - Number of microseconds to delay
 *
 * @return  none
 *
 * @note    Uses a busy-wait loop based on CPU cycles. Approximate delay.
 */
void HAL_Delay_us(uint32_t us)
{
    uint32_t ticks = (SYSCLK / 1000000UL) * us;
    while (ticks--)
        __asm volatile("nop");
}
