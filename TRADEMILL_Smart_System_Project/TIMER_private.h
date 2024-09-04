/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MACL             *********************/
/********************** SWC        : TIMER             *********************/
/********************** version    : 1.00             *********************/
/***********************************************************************/
/***********************************************************************/
#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H

// Waveform Generation Mode options
#define NORMAL                        0
#define PWM_Phase_Correct             1
#define CTC                           2
#define FAST_PWM                      3

// Clock Select options
#define NO_CLK_SOURCE                 0
#define CLK_NO_PRESCALING             1
#define CLK_8                         2
#define CLK_64                        3
#define CLK_256                       4
#define CLK_1024                      5
#define EXT_CLK_FALLING_EDGE          6
#define EXT_CLK_RISING_EDGE           7

// Compare Match Output Mode options_CTC_NORMAL

#define OC0_TOGGLE                    1
#define OC0_CLR                       2
#define OC0_SET                       3


// Compare Match Output Mode optionsFast_PWM

#define CLR_ON_COMP_MATCH_SET_ON_TOP                    1
#define SET_ON_COMP_MATCH_CLR_ON_TOP                    2

// Masks for register configurations
#define OC0_MASK                      0b11001111
#define PRE_SCALE_MASK                0b11111000
#define Waveform_Generation_Mode_MASK 0b10110111

// Compare Match Output Mode options_PHASECPRRECT_PWM

#define OC0_DISCONNECT_0                                  1
#define CLR_ON_UP_COUNTING_SET_ON_DOWN_COUNTING         2
#define CLR_ON_DOWN_COUNTING_SET_ON_UP_COUNTING         3

/**************************************************************/
//channels
#define CHANNEL_A    1
#define CHANNEL_B    2

// ctc and normal mode
#define  OC1_DISCONNECT_1                     0
#define  OC1_TOGGLE                         1
#define  OC1_CLR                            2
#define  OC1_SET                            3

// wave generation mode
#define NORMAL_1                            0
#define CTC_1                               1
#define PWM_Phase_Correct_8_bit_1           2
#define Fast_PWM_8_bit_1                    3
#define Fast_PWM_SERVO_1                    4

// fast pwm

#define OC1_TOGGLE                          1
#define SET_ON_Top_CLR_ON_COMP              2
#define SET_ON_COMP_CLR_ON_TOP              3

// phase correct
#define OC1_DISCONNECT_1                      0
#define OC1_TOGGLE                          1
#define SET_ON_UP_COUNT_CLR_ON_DOWN_COUNT   2
#define CLR_ON_UP_COUNT_SET_ON_DOWN_COUNT   3

#endif
