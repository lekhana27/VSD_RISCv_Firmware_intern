#include "driver_pwm_tim.h"

static uint16_t pwm_arr;

/*********************************************************************
 * @fn      HAL_PWM_Init
 *
 * @brief   Initializes TIM1 peripheral for PWM generation on CH1.
 *
 * @param   freq_hz     Desired PWM frequency in Hertz.
 * @param   resolution  PWM resolution (number of steps per period).
 *
 * @formulas
 *          Timer_Clock   = SystemCoreClock
 *
 *          ARR (Auto-Reload Register) value:
 *              ARR = resolution − 1
 *
 *          Prescaler value:
 *              PSC = (Timer_Clock / (freq_hz × resolution)) − 1
 *
 *          PWM Frequency:
 *              PWM_Freq = Timer_Clock /
 *                         ((PSC + 1) × (ARR + 1))
 *
 *          Duty Cycle %:
 *              Duty% = (CCR / (ARR + 1)) × 100
 * 
 *  @registers
 *          RCC->APB2PCENR   - Enable TIM1 clock (TIM1EN bit).
 *          TIM1->PSC        - Prescaler register.
 *          TIM1->ATRLR      - Auto-reload register (ARR).
 *          TIM1->CNT        - Counter register reset to 0.
 *          TIM1->CHCTLR1    - Channel control (PWM mode, preload).
 *          TIM1->CCER       - Capture/Compare enable register.
 *          TIM1->CH1CVR     - Compare register (CCR1 duty value).
 *          TIM1->BDTR       - Break & Dead-Time (MOE bit).
 *          TIM1->CTLR1      - Control register (ARPE bit).
 * 
 * @note    - Enables clock for TIM1 on APB2 bus.
 *          - Calculates prescaler and auto-reload based on
 *            SystemCoreClock, frequency, and resolution.
 *          - Configures TIM1 Channel 1 in PWM Mode 1.
 *          - Enables preload for CCR and ARR registers.
 *          - Enables main output (MOE) for advanced timer.
 *          - Duty cycle is initialized to 0%.
 *
 * @return  none
 *********************************************************************/
void HAL_PWM_Init(uint32_t freq_hz, uint16_t resolution)
{
    uint32_t prescaler;
    uint32_t timer_clk = SystemCoreClock;

    /* Enable TIM1 clock only */
    RCC->APB2PCENR |= (1 << 11);   // TIM1EN

    /* PWM frequency calculation */
    pwm_arr = resolution - 1;
    prescaler = (timer_clk / (freq_hz * resolution)) - 1;

    /* Timer base */
    TIM1->PSC   = prescaler;
    TIM1->ATRLR = pwm_arr;
    TIM1->CNT   = 0;

    /* PWM Mode 1 on CH1 */
    TIM1->CHCTLR1 &= ~(0x7 << 4);
    TIM1->CHCTLR1 |=  (0x6 << 4);   // OC1M = PWM1
    TIM1->CHCTLR1 |=  (1 << 3);     // OC1PE

    /* Enable CH1 output */
    TIM1->CCER |= (1 << 0);

    /* Initial duty */
    TIM1->CH1CVR = 0;

    /* Advanced timer main output enable */
    TIM1->BDTR |= (1 << 15);        // MOE

    /* Auto-reload preload */
    TIM1->CTLR1 |= (1 << 7);        // ARPE
}

/*********************************************************************
 * @fn      HAL_PWM_SetDuty
 *
 * @brief   Updates PWM duty cycle value for TIM1 Channel 1.
 *
 * @param   duty  Duty cycle value (0 to resolution-1).
 * 
 * @formulas
 *          Duty% = (CCR / (ARR + 1)) × 100
 * 
 *  @registers
 *          TIM1->CH1CVR   - Compare register updated with duty value.
 *
 * @note    - Clamps duty value to maximum ARR limit.
 *          - Writes duty value into CH1 compare register.
 *          - Effective immediately if preload enabled.
 *
 * @return  none
 *********************************************************************/
void HAL_PWM_SetDuty(uint16_t duty)
{
    if (duty > pwm_arr)
        duty = pwm_arr;

    TIM1->CH1CVR = duty;
}

/*********************************************************************
 * @fn      HAL_PWM_Start
 *
 * @brief   Starts PWM signal generation on TIM1.
 *
 * @note    - Sets CEN (Counter Enable) bit in TIM1 control register.
 *          - Timer begins counting and PWM output becomes active.
 *
 * @return  none
 *********************************************************************/
void HAL_PWM_Start(void)
{
    TIM1->CTLR1 |= (1 << 0);        // CEN
}

/*********************************************************************
 * @fn      HAL_PWM_Stop
 *
 * @brief   Stops PWM signal generation on TIM1.
 *
 * @note    - Clears CEN (Counter Enable) bit in TIM1 control register.
 *          - Timer stops and PWM output is disabled.
 *
 * @return  none
 *********************************************************************/
void HAL_PWM_Stop(void)
{
    TIM1->CTLR1 &= ~(1 << 0);
}