/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MCAL             *********************/
/********************** SWC        : External interrupt  *********************/
/********************** version    : 1.00             *********************/
/***********************************************************************/
/***********************************************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

/*
POST-BUILD CONFIGURATION : in the parameters of the function ,, better to use in repeating components , easy in software ,less memory (one function)
PRE -BUILD CONFIGURATION : #if , #elif check in the pre_processor phase before run time operations , complex in spftware , not applicable 
LINK-TIME  CONFIGURATION : happen in the linker phase
*/







/* defines the post-build configuration choices for the user */
#define LOW_LEVEL          1
#define ANY_LOGICAL_change 2
#define FALLING_EDGE       3
#define RISING_EDGE        4

/*pre_build configuration*/
void EXTI_voidInt0init(void);
void EXTI_voidInt1init(void);
void EXTI_voidInt2init(void);
/***************************/

/*post build configuration*/
u8 EXTI_u8INT0SetSenseCtrl(u8 sensecontrol);
u8 EXTI_u8INT1SetSenseCtrl(u8 sensecontrol);
u8 EXTI_u8INT2SetSenseCtrl(u8 sensecontrol);
/***************************/


/*pheripheral enable / disbale - postbuild configuration */
u8 EXTI_u8INTEnable (u8 INT);
u8 EXTI_u8INTDisable(u8 INT);
/***************************/



/*function-pointer call back function for interupt service routine (ISR) */
u8 EXIT_u8int0CallBack(void (*copy_pvFuncint0)(void));
u8 EXIT_u8int1CallBack(void (*copy_pvFuncint1)(void));
u8 EXIT_u8int2CallBack(void (*copy_pvFuncint2)(void));
/****************************************************/



#endif // EXTI_INTERFACE_H
