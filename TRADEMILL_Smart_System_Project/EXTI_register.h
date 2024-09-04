/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MCAL             *********************/
/********************** SWC        : External interrupt  *********************/
/********************** version    : 1.00             *********************/
/***********************************************************************/
/***********************************************************************/
#ifndef EXTI_REGISTER_H
#define EXTI_REGISTER_H


#define GICR                 *((volatile u8*)0x5B)  /* general interrupt control register*/
#define GICR_INT1               7
#define GICR_INT0               6
#define GICR_INT2               5

#define GIFR                 *((volatile u8*)0x5A)  /* general interrupt flag register*/
#define MCUCR                *((volatile u8*)0x55)  /* MCU control register*/
#define MCUCR_ISC00             0
#define MCUCR_ISC01             1
#define MCUCR_ISC10             2
#define MCUCR_ISC11             3


#define MCUCSR               *((volatile u8*)0x54)  /* MCU control and  status register*/
#define MCUCSR_INT2             6



#endif // EXTI_REGISTER_H
