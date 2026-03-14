#include "driver_rcc.h"
#include "driver_gpio.h"
#include "driver_usart_debug.h"
#include "cli.h"

/* LED CONFIG */
#define LED_PORT   GPIOD
#define LED_PIN    4

int main(void)
{
    char cmd_buffer[64];

    /* Init system */
    SystemInit();

    // Initialize Delay 
    HAL_Delay_Init();

    // Initialize UART Prints
    HAL_UART_Init();

    // Enable GPIOD clock using RCC driver
    HAL_RCC_APB2_Enable(RCC_GPIOD);


    /* GPIO configuration moved here */
    HAL_GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_PUSH_PULL);

    /* Startup banner */
    HAL_UART_SendString("\r\n==============================\r\n");
    HAL_UART_SendString(" UART GPIO Command Console\r\n");
    HAL_UART_SendString(" Type 'help' for commands\r\n");
    HAL_UART_SendString("==============================\r\n");

    while (1)
    {
        HAL_UART_SendString("> ");
        HAL_UART_ReadLine(cmd_buffer, sizeof(cmd_buffer));
        CLI_Process(cmd_buffer);
    }
    return 0;
}