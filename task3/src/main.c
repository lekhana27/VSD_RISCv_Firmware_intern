#include "driver_pwm_tim.h"

int main(void)
{
    uint16_t duty = 0;
    int16_t step = 25;

    SystemInit();

    // Initialize Delay 
    HAL_Delay_Init();

    // Initialize UART Prints
    HAL_UART_Init();

    // Enable GPIOD clock using RCC driver
    HAL_RCC_APB2_Enable(RCC_GPIOD);

    HAL_UART_Print("\r\nPWM Demo (GPIO in main)\r\n", UART_NO_NUMBER, 0);

    /* GPIO configuration moved here */
    HAL_GPIO_Init(GPIOD, 2, GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_AF_PUSH_PULL);

    /* PWM init: 1kHz, 1000-step resolution */
    HAL_PWM_Init(1000, 1000);
    HAL_PWM_Start();
    HAL_UART_Print("Frequency is 1kHz", UART_NO_NUMBER, 0);
    HAL_UART_Print("\r\n", UART_NO_NUMBER, 0);

    while (1)
    {
        HAL_PWM_SetDuty(duty);
        // Calculate percentage (0 to 100)
        uint16_t percent = duty / 10;

        HAL_UART_Print("Duty = ", UART_NO_NUMBER, 0);
        HAL_UART_Print("", duty, 10);   // Raw value (0-1000)
        HAL_UART_Print(" (", UART_NO_NUMBER, 0);
        HAL_UART_Print("", percent, 10); // Percentage value (0-100)
        HAL_UART_Print("%)\r\n", UART_NO_NUMBER, 0);

        duty += step;
        if (duty >= 1000 || duty == 0)
            step = -step;

        HAL_Delay_ms(40);
    }
    return 0;
}