/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MACL             *********************/
/********************** SWC        : TIMER             *********************/
/********************** version    : 1.00             *********************/
/***********************************************************************/
/***********************************************************************/
#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

/**
 * Waveform Generation Mode options:
 *         1 - NORMAL
 *         2 - PWM_Phase_Correct
 *         3 - CTC
 *         4 - FAST_PWM
 */
#define Waveform_Generation_Mode  NORMAL

/**
 * Clock Select options:
 *          1- NO_CLK_SOURCE
 *          2- CLK_NO_PRESCALING
 *          3- CLK_8
 *          4- CLK_64
 *          5- CLK_256
 *          6- CLK_1024
 *          7- EXT_CLK_FALLING_EDGE
 *          8- EXT_CLK_RISING_EDGE
 */
#define CLK_SELECT_BIT            CLK_64
#define CLK_Select_NEW            CLK_64
/**
 * Compare match value for 8-bit overflow
 */
#define COMPARE_MATCH_VALUE       64
#define Pre_Load_Value           184
/**
 * Compare Match Output Mode options:
 *         1 - OC0_DISCONNECT
 *         2 - OC0_TOGGLE
 *         3 - OC0_CLR
 *         4 - OC0_SET
 */
#define COMPARE_MATCH_OUTPUT_MODE    OC0_DISCONNECT
/**
 * Compare Match Output Mode options:
 *         1 - OC0_DISCONNECT_fast
 *         2 - CLR_ON_COMP_MATCH_SET_ON_TOP
 *         3 - SET_ON_COMP_MATCH_CLR_ON_TOP
 */
#define COMPARE_OUTPUT_FAST_PWM   CLR_ON_COMP_MATCH_SET_ON_TOP
/**
 * Compare Match Output Mode options:
 *         1 - OC0_DISCONNECT
 *         2 - CLR_ON_UP_COUNTING_SET_ON_DOWN_COUNTING(inverted)
 *         3 - CLR_ON_DOWN_COUNTING_SET_ON_UP_COUNTING(non inverted)
 */
#define COMPARE_OUTPUT_PWM_Phase_Correct     CLR_ON_DOWN_COUNTING_SET_ON_UP_COUNTING
/*************************************************************************************/
/**
 * for timer 1
 */
/**
 * Channel Options:
 *             1 - CHANNEL_A
 *             2 - CHANNEL_B
 */
#define CHANNEL_SELECT    CHANNEL_A

/**
 * NORMAL_1
 * CTC_1
 * PWM_Phase_Correct_8_bit_1
 * Fast_PWM_8_bit_1
 * Fast_PWM_SERVO_1
 *
 */

#define Waveform_Generation_Mode_TIMER1    Fast_PWM_8_bit_1

/**
 * Compare Match Output Mode options:
 *         1 - OC1_DISCONNECT_1
 *         2 - OC1_TOGGLE
 *         3 - OC1_CLR
 *         4 - OC1_SET
 */

#define COMPARE_MATCH_OUTPUT_MODE_TIMER1   OC1_DISCONNECT_1
/**
 * fast pwm Mode options:
 *         1 - OC1_DISCONNECT
 *         2 - OC1_TOGGLE
 *         3 - SET_ON_Top_CLR_ON_COMP
 *         4 - SET_ON_COMP_CLR_ON_TOP
 */
#define COMPARE_MATCH_OUTPUT_MODE_TIMER1_FAST_PWM  SET_ON_Top_CLR_ON_COMP
/**
 * phase correct pwm Mode options:
 *         1 - OC1_DISCONNECT
 *         2 - OC1_TOGGLE
 *         3 - SET_ON_UP_COUNT_CLR_ON_DOWN_COUNT
 *         4 - CLR_ON_UP_COUNT_SET_ON_DOWN_COUNT
 */
#define COMPARE_MATCH_OUTPUT_MODE_TIMER1_PHASE_PWM SET_ON_UP_COUNT_CLR_ON_DOWN_COUNT
#endif
