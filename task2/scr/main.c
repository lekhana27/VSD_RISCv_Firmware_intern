#include <driver_gpio.h>
#include <driver_usart_debug.h>
#include "driver_rcc.h"

int main(void)
{
    uint32_t led_count = 0;

    SystemInit();

    HAL_UART_Init();

    // Initialize delay system
    HAL_Delay_Init();
    
    // Enable GPIOC clock using RCC driver
    HAL_RCC_APB2_Enable(RCC_GPIOD);

    // Initialize PD4 as push-pull output, 50MHz
    HAL_GPIO_Init(GPIOD, 4, GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_PUSH_PULL);

     /* Startup banner */
    HAL_UART_Print("\r\n*****************************************\r\n", UART_NO_NUMBER, 0);
    HAL_UART_Print("Board Name      : VSDSquadron Mini\r\n", UART_NO_NUMBER, 0);
    HAL_UART_Print("Firmware Version: v1.0.0\r\n", UART_NO_NUMBER, 0);
    HAL_UART_Print("Interface       : USART1 (PD5)\r\n", UART_NO_NUMBER, 0);
    HAL_UART_Print("*****************************************\r\n\r\n", UART_NO_NUMBER, 0);

    while (1)
    {
        HAL_GPIO_TogglePin(GPIOD, 4);   // toggle LED
        /* Print counter */
        HAL_UART_Print("LED Toggle Count: ", UART_NO_NUMBER, 0);
        HAL_UART_Print("", led_count, 10);
        HAL_UART_Print("\r\n", UART_NO_NUMBER, 0);

        led_count++;

        HAL_Delay_ms(50);
    }
    return 0;
}