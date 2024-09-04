/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed ******************/
/********************** Layer      : MCAL             ******************/
/********************** SWC        : External Interrupt ****************/
/********************** version    : 1.00             ******************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPEs.h"
#include "BIT_MATH.h"
#include "EXTI_config.h"
#include "EXTI_register.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"
/*                   Global Pointer to function   to use in ISR                */
void(*EXTI_pvInt0Func)(void) = 0;
void(*EXTI_pvInt1Func)(void) = 0;
void(*EXTI_pvInt2Func)(void) = 0;

void EXTI_voidInt0init(void) /*Pin PD2*/
{
    #if INT0_SENSE == FALLING_EDGE
        /* set sense control for INT0 to falling edge */
        SET_BIT(MCUCR, MCUCR_ISC01);
        CLR_BIT(MCUCR, MCUCR_ISC00);
    #elif INT0_SENSE == LOW_LEVEL
        /* set sense control for INT0 to low level */
        CLR_BIT(MCUCR, MCUCR_ISC00);
        CLR_BIT(MCUCR, MCUCR_ISC01);
    #elif INT0_SENSE == RISING_EDGE
        /* set sense control for INT0 to rising edge */
        SET_BIT(MCUCR, MCUCR_ISC00);
        SET_BIT(MCUCR, MCUCR_ISC01);
    #elif INT0_SENSE == ANY_LOGICAL_CHANGE
        /* set sense control for INT0 to any logical change */
        SET_BIT(MCUCR, MCUCR_ISC00);
        CLR_BIT(MCUCR, MCUCR_ISC01);
    #else
        //#error "Invalid INT0_SENSE configuration"
    #endif

    #if INT0_INIT_STATE == ENABLED
        SET_BIT(GICR, GICR_INT0);
    #elif INT0_INIT_STATE == DISABLED
        CLR_BIT(GICR, GICR_INT0);
    #else
        #error "Invalid INT0_INIT_STATE configuration"
    #endif
}

void EXTI_voidInt1init(void) /*Pin PD3*/
{
    #if INT1_SENSE == LOW_LEVEL
        /* set sense control for INT1 to low level */
        CLR_BIT(MCUCR, MCUCR_ISC10);
        CLR_BIT(MCUCR, MCUCR_ISC11);
    #elif INT1_SENSE == ANY_LOGICAL_change
        /* set sense control for INT1 to any logical change */
        SET_BIT(MCUCR, MCUCR_ISC10);
        CLR_BIT(MCUCR, MCUCR_ISC11);
    #elif INT1_SENSE == FALLING_EDGE
        /* set sense control for INT1 to falling edge */
        CLR_BIT(MCUCR, MCUCR_ISC10);
        SET_BIT(MCUCR, MCUCR_ISC11);
    #elif INT1_SENSE == RISING_EDGE
        /* set sense control for INT1 to rising edge */
        SET_BIT(MCUCR, MCUCR_ISC10);
        SET_BIT(MCUCR, MCUCR_ISC11);
    #else
        #error "Invalid INT1_SENSE configuration"
    #endif

    #if INT1_INIT_STATE == ENABLED
        SET_BIT(GICR, GICR_INT1);
    #elif INT1_INIT_STATE == DISABLED
        CLR_BIT(GICR, GICR_INT1);
    #else
        #error "Invalid INT1_INIT_STATE configuration"
    #endif
}

void EXTI_voidInt2init(void) /*Pin PB2*/
{
    #if INT2_SENSE == FALLING_EDGE
        /* set sense control for INT2 to falling edge */
        CLR_BIT(MCUCSR, MCUCSR_INT2);
    #elif INT2_SENSE == RISING_EDGE
        /* set sense control for INT2 to rising edge */
        SET_BIT(MCUCSR, MCUCSR_INT2);
    #else
        #error "Invalid INT2_SENSE configuration"
    #endif

    #if INT2_INIT_STATE == ENABLED
        SET_BIT(GICR, GICR_INT2);
    #elif INT2_INIT_STATE == DISABLED
        CLR_BIT(GICR, GICR_INT2);
    #else
        #error "Invalid INT2_INIT_STATE configuration"
    #endif
}
// post puild
u8 EXTI_u8INT0SetSenseCtrl(u8 senseControl)
{
    u8 local_u8ReturnState = 0;
    switch(senseControl)
    {
        case LOW_LEVEL:
            CLR_BIT(MCUCR, MCUCR_ISC00);
            CLR_BIT(MCUCR, MCUCR_ISC01);
            break;
        case ANY_LOGICAL_change:
            SET_BIT(MCUCR, MCUCR_ISC00);
            CLR_BIT(MCUCR, MCUCR_ISC01);
            break;
        case FALLING_EDGE:
            SET_BIT(MCUCR, MCUCR_ISC01);
            CLR_BIT(MCUCR, MCUCR_ISC00);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCR, MCUCR_ISC00);
            SET_BIT(MCUCR, MCUCR_ISC01);
            break;
        default:
            local_u8ReturnState = 1;
    }
    return local_u8ReturnState;
}

u8 EXTI_u8INT1SetSenseCtrl(u8 senseControl)  
{
    u8 local_u8ReturnState = 0;
    switch(senseControl)
    {
        case LOW_LEVEL:
            CLR_BIT(MCUCR, MCUCR_ISC10);
            CLR_BIT(MCUCR, MCUCR_ISC11);
            break;
        case ANY_LOGICAL_change:
            SET_BIT(MCUCR, MCUCR_ISC10);
            CLR_BIT(MCUCR, MCUCR_ISC11);
            break;
        case FALLING_EDGE:
            CLR_BIT(MCUCR, MCUCR_ISC10);
            SET_BIT(MCUCR, MCUCR_ISC11);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCR, MCUCR_ISC10);
            SET_BIT(MCUCR, MCUCR_ISC11);
            break;
        default:
            local_u8ReturnState = 1;
    }
    return local_u8ReturnState;
}

u8 EXTI_u8INT2SetSenseCtrl(u8 senseControl)
{
    u8 local_u8ReturnState = 0;
    switch(senseControl)
    {
        case FALLING_EDGE:
            CLR_BIT(MCUCSR, MCUCSR_INT2);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCSR, MCUCSR_INT2);
            break;
        default:
            local_u8ReturnState = 1;
    }
    return local_u8ReturnState;
}

u8 EXTI_u8INTEnable(u8 INT)
{
    u8 local_u8ReturnState = 0;
    switch(INT)
    {
        case GICR_INT0:
            SET_BIT(GICR, GICR_INT0);
            break;
        case GICR_INT1:
            SET_BIT(GICR, GICR_INT1);
            break;
        case GICR_INT2:
            SET_BIT(GICR, GICR_INT2);
            break;
        default:
            local_u8ReturnState = 1;
    }
    return local_u8ReturnState;
}

u8 EXTI_u8INTDisable(u8 INT)
{
    u8 local_u8ReturnState = 0;
    switch(INT)
    {
        case GICR_INT0:
            CLR_BIT(GICR, GICR_INT0);
            break;
        case GICR_INT1:
            CLR_BIT(GICR, GICR_INT1);
            break;
        case GICR_INT2:
            CLR_BIT(GICR, GICR_INT2);
            break;
        default:
            local_u8ReturnState = 1;
    }
    return local_u8ReturnState;
}

u8 EXIT_u8int0CallBack(void (*copy_pvFuncint0)(void))
{
	u8 local_returnState =0;
	if(copy_pvFuncint0 == 0)
	{
		/*return error */
		local_returnState =1;
	}
	else
	{
		EXTI_pvInt0Func = copy_pvFuncint0;
	}
	return local_returnState;
}

u8 EXIT_u8int1CallBack(void (*copy_pvFuncint1)(void))
{
	u8 local_returnState = 0;
	if(copy_pvFuncint1 ==  0)
	{
		/*return error */
		local_returnState =1;
	}
	else
	{
		EXTI_pvInt1Func = copy_pvFuncint1;
	}
	return local_returnState;
}
u8 EXIT_u8int2CallBack(void (*copy_pvFuncint2)(void))
{
	u8 local_returnState = 0;
	if(copy_pvFuncint2 ==  0)
	{
		/*return error */
		local_returnState = 1;
	}
	else
	{
		EXTI_pvInt2Func=copy_pvFuncint2;
	}
	return local_returnState;
}

    /*          ISR of INT0         */
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	EXTI_pvInt0Func();
}



/*              ISR of INT1         */
void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	EXTI_pvInt1Func();
}



/*              ISR of INT2         */
void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	EXTI_pvInt2Func();
}
