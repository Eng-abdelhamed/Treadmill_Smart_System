/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MCAL             *********************/
/********************** SWC        : External interrupt  *********************/
/********************** version    : 1.00             *********************/
/***********************************************************************/
/***********************************************************************/
#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/*option to choose sense control
1- ANY_LOGICAL_change
2-LOW_LEVEL
3-FALLING_EDGE
4-RISING_EDGE
*/

/*option to choose the init state
1-enable
2-disable
*/
#define INT0_SENSE          RISING_EDGE
#define INT0_INIT_STATE     ENABLED

#define INT1_SENSE          RISING_EDGE
#define INT1_INIT_STATE     ENABLED


#define INT2_SENSE          RISING_EDGE
#define INT2_INIT_STATE     ENABLED


#endif // EXTI_CONFIG_H_
