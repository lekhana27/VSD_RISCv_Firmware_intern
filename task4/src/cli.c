#include "cli.h"


/*********************************************************************
 * @fn      str_to_lower
 *
 * @brief   Converts a string to lowercase in-place.
 *
 * @param   s - Pointer to the string to convert
 *
 * @return  none
 *
 * @note    - Modifies the original string.
 *          - Uses standard C tolower().
 *          - Stops at null terminator '\0'.
 *          - Declared static since it is used only within cli.c.
 */
/* Convert string to lowercase */
static void str_to_lower(char *s)
{
    while (*s)
    {
        *s = tolower((unsigned char)*s);
        s++;
    }
}


/*********************************************************************
 * @fn      CLI_Process
 *
 * @brief   Processes a command string received from UART CLI.
 *
 * @param   cmd - Null-terminated command string entered by user
 *
 * @return  none
 *
 * @note    - Converts command to lowercase for case-insensitive matching.
 *          - Supports the following commands:
 *              help                → Shows available commands
 *              led on              → Turns LED ON
 *              led off             → Turns LED OFF
 *              blink <ms> <count>  → Blinks LED with delay and count
 *              read <pin>          → Reads GPIO pin value
 *          - Performs basic input validation.
 *          - Sends responses via UART.
 *          - Blocking behavior may occur during blink delays.
 */
void CLI_Process(char *cmd)
{
    /* normalize */
    str_to_lower(cmd);

    /* ---- HELP ---- */
    if (strcmp(cmd, "help") == 0)
    {
        HAL_UART_SendString("Commands:\r\n");
        HAL_UART_SendString("help\r\n");
        HAL_UART_SendString("led on\r\n");
        HAL_UART_SendString("led off\r\n");
        HAL_UART_SendString("blink <ms> <count>\r\n");
        HAL_UART_SendString("read <pin>\r\n");
    }

    /* ---- LED ON ---- */
    else if (strcmp(cmd, "led on") == 0)
    {
        HAL_GPIO_WritePin(LED_PORT, LED_PIN, 1);
        HAL_UART_SendString("LED ON\r\n");
    }

    /* ---- LED OFF ---- */
    else if (strcmp(cmd, "led off") == 0)
    {
        HAL_GPIO_WritePin(LED_PORT, LED_PIN, 0);
        HAL_UART_SendString("LED OFF\r\n");
    }

    /* ---- BLINK ---- */
    else if (strncmp(cmd, "blink ", 6) == 0)
    {
        int ms = 0;
        int count = 0;

        /* Parse two integers */
        if (sscanf(&cmd[6], "%d %d", &ms, &count) != 2)
        {
            HAL_UART_SendString("Usage: blink <ms> <count>\r\n");
            return;
        }

        if (ms <= 0 || count <= 0)
        {
            HAL_UART_SendString("Error: invalid values\r\n");
            return;
        }

        HAL_UART_SendString("Blinking...\r\n");

        for (int i = 0; i < count; i++)
        {
            HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
            HAL_Delay_ms(ms);
        }

        HAL_UART_SendString("Done\r\n");
    }

    /* ---- READ PIN ---- */
    else if (strncmp(cmd, "read ", 5) == 0)
    {
        int pin = atoi(&cmd[5]);

        if (pin < 0 || pin > 15)
        {
            HAL_UART_SendString("Error: invalid pin\r\n");
            return;
        }

        uint8_t val = HAL_GPIO_ReadPin(GPIOD, pin);

        HAL_UART_SendString("Pin value: ");
        HAL_UART_Print("", val, 10);
        HAL_UART_SendString("\r\n");
    }

    /* ---- UNKNOWN ---- */
    else
    {
        HAL_UART_SendString("Error: Unknown command\r\n");
    }
}