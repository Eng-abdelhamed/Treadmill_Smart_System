/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MACL             *********************/
/********************** SWC        : TIMER             *********************/
/********************** version    : 1.00          *********************/
/***********************************************************************/
/***********************************************************************/
#include"STD_TYPEs.h"
#include"BIT_MATH.h"
#include"TIMER_register.h"
#include"TIMER_private.h"
#include"TIMER_config.h"
#include"TIMER_interface.h"

static void (*callPackFunc_0)(void) = 0;
static void (*callPackFunc_1)(void) = 0;
static void (*callPackFunc_ICU)(void) = 0;
void TIMER0_voidsetPReload(u8 val)
{
	TCNT0 = val;
}

void TIMER0_voidInit(void)
{
	/*Initialize the  mode condition*/
#if   Waveform_Generation_Mode == NORMAL

	/*Setting the NORMAL mode*/
	CLR_BIT(TCCR0,TCCR0_WGRM01);
	CLR_BIT(TCCR0,TCCR0_WGRM00);

	/*Peripheral Interrupt Enable*/
	SET_BIT(TIMSK,TMSK_TOIE0);

	/*Setting the PreLOad Value */
	TCNT0 = Pre_Load_Value;


	/***************************************************/
#elif Waveform_Generation_Mode == CTC

	/*Setting the CTC Mode */
	SET_BIT(TCCR0,TCCR0_WGRM01);
	CLR_BIT(TCCR0,TCCR0_WGRM00);

	/*Setting the Output of OC0*/
#if COMPARE_MATCH_OUTPUT_MODE == OC0_DISCONNECT
	CLR_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_MATCH_OUTPUT_MODE ==  OC0_TOGGLE
	SET_BIT(TCCR0,TCCR0_COM00);
	CLR_BIT(TCCR0,TCCR0_COM01);

#elif COMPARE_MATCH_OUTPUT_MODE == OC0_CLR
	SET_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_MATCH_OUTPUT_MODE == OC0_SET
	SET_BIT(TCCR0,TCCR0_COM01);
	SET_BIT(TCCR0,TCCR0_COM00);
#endif

	/*Peripheral Interrupt Enable*/
	SET_BIT(TIMSK,TMSK_OCIE0);

	/*Set Compare Match Value*/
	OCR0 = COMPARE_MATCH_VALUE;

	/***************************************************/
#elif Waveform_Generation_Mode == FAST_PWM
	/*Setting the FAST PWM Mode*/
	SET_BIT(TCCR0,TCCR0_WGRM01);
	SET_BIT(TCCR0,TCCR0_WGRM00);

	/*Setting the output mode */
#if COMPARE_OUTPUT_FAST_PWM == OC0_DISCONNECT_fast
	CLR_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_OUTPUT_FAST_PWM == CLR_ON_COMP_MATCH_SET_ON_TOP
	SET_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_OUTPUT_FAST_PWM == SET_ON_COMP_MATCH_CLR_ON_TOP
	SET_BIT(TCCR0,TCCR0_COM01);
	SET_BIT(TCCR0,TCCR0_COM00);
#endif
	/***************************************************/
#elif Waveform_Generation_Mode == PWM_Phase_Correct
	/*Setting the FAST PWM Mode*/
	CLR_BIT(TCCR0,TCCR0_WGRM01);
	SET_BIT(TCCR0,TCCR0_WGRM00);

	/*Setting the output mode */
#if COMPARE_OUTPUT_FAST_PWM == OC0_DISCONNECT
	CLR_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_OUTPUT_FAST_PWM == CLR_ON_COMP_MATCH_SET_ON_TOP
	SET_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_OUTPUT_FAST_PWM == SET_ON_COMP_MATCH_CLR_ON_TOP
	SET_BIT(TCCR0,TCCR0_COM01);
	SET_BIT(TCCR0,TCCR0_COM00);
#endif


#endif
	/*PreScalar division  by 8 */  // Important to be last code to start timer
		TCCR0 &= PRE_SCALE_MASK;
		TCCR0 |= CLK_SELECT_BIT;

}
void timer0_delay(u16 time_in_ms)
{
	u16 overflow_time = (time_in_ms * 1000UL)/2048UL;
	u16 counts=0;

	CLR_BIT(TCCR0,TCCR0_WGRM01);
	CLR_BIT(TCCR0,TCCR0_WGRM00);

	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);

	TCNT0 = 0;
	while (counts < overflow_time)
	{
	 // Wait until overflow occurs
	 while (!(TIFR & (1 << TIFR_TOV0)));
	 // Clear overflow flag
	 SET_BIT(TIFR,TIFR_TOV0);
	 counts++;
	}
	 TCCR0 = 0x00;
}
void timer0_voidSetCompareValue(u8 value)
{
	OCR0 = value;
}



void TIMER1_voidInit(void)
{
	/** SELECT the CHANNEL*/
#if (CHANNEL_SELECT == CHANNEL_A)

	if(Waveform_Generation_Mode_TIMER1 == NORMAL_1 || Waveform_Generation_Mode_TIMER1 == CTC_1)
	{
		/**initialize the mode of the timer  */
		if(COMPARE_MATCH_OUTPUT_MODE_TIMER1 == OC1_DISCONNECT_1)
		{
			CLR_BIT(TCCR1A,TCCR1A_COM1A0);
			CLR_BIT(TCCR1A,TCCR1A_COM1A1);
		}
		else if(COMPARE_MATCH_OUTPUT_MODE_TIMER1 == OC1_TOGGLE)
		{
			SET_BIT(TCCR1A,TCCR1A_COM1A0);
			CLR_BIT(TCCR1A,TCCR1A_COM1A1);
		}
		else if(COMPARE_MATCH_OUTPUT_MODE_TIMER1 == OC1_CLR)
		{
			SET_BIT(TCCR1A,TCCR1A_COM1A1);
			CLR_BIT(TCCR1A,TCCR1A_COM1A0);
		}
		else if(COMPARE_MATCH_OUTPUT_MODE_TIMER1 == 4)
		{
			SET_BIT(TCCR1A,TCCR1A_COM1A1);
			SET_BIT(TCCR1A,TCCR1A_COM1A0);
		}
#if(Waveform_Generation_Mode_TIMER1 == CTC_1 )
	// set interrupt
	SET_BIT(TIMSK,TIMSK_OCIE1A);
	// set the wave generation mode of CTC
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);

#elif(Waveform_Generation_Mode_TIMER1 == NORMAL_1)
	// set interrupt
	SET_BIT(TIMSK,TIMSK_TOIE1);
	// set the wave generation mode of normal mode
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
#endif
	}
	else if(Waveform_Generation_Mode_TIMER1 == PWM_Phase_Correct_8_bit_1)
	{
		if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_PHASE_PWM == SET_ON_UP_COUNT_CLR_ON_DOWN_COUNT)
		{
			// inititalize the mode of non inverted
			CLR_BIT(TCCR1A,TCCR1A_COM1A0);
			SET_BIT(TCCR1A,TCCR1A_COM1A1);
		}
		else if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_PHASE_PWM == CLR_ON_UP_COUNT_SET_ON_DOWN_COUNT)
		{
			// inititalize the mode of inverted
			SET_BIT(TCCR1A,TCCR1A_COM1A1);
			SET_BIT(TCCR1A,TCCR1A_COM1A0);
		}
		else
		{
			//inititalize the non
			CLR_BIT(TCCR1A,TCCR1A_COM1A0);
			CLR_BIT(TCCR1A,TCCR1A_COM1A1);
		}
		//inititalize the waveform generation mode of the phase correct_pwm
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);

	}
	else if(Waveform_Generation_Mode_TIMER1 == Fast_PWM_8_bit_1)
	{

		if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_FAST_PWM == SET_ON_Top_CLR_ON_COMP)
		{
			// initialize the mode if non inverted
			CLR_BIT(TCCR1A,TCCR1A_COM1A0);
			SET_BIT(TCCR1A,TCCR1A_COM1A1);

		}
	     if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_FAST_PWM == SET_ON_COMP_CLR_ON_TOP)
		{
			// initialize the mode of inverted
			SET_BIT(TCCR1A,TCCR1A_COM1A1);
			SET_BIT(TCCR1A,TCCR1A_COM1A0);
		}
		if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_FAST_PWM ==0)
		{
			// normal port operation
			CLR_BIT(TCCR1A,TCCR1A_COM1A0);
			CLR_BIT(TCCR1A,TCCR1A_COM1A1);
		}
		//initialize the mode of the wave generation mode
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
	}
	else if(Waveform_Generation_Mode_TIMER1 == Fast_PWM_SERVO_1)
	{
		if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_FAST_PWM == SET_ON_Top_CLR_ON_COMP)
		{
			// initialize the mode if non inverted
			CLR_BIT(TCCR1A,TCCR1A_COM1A0);
			SET_BIT(TCCR1A,TCCR1A_COM1A1);

		}
		else if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_FAST_PWM == SET_ON_COMP_CLR_ON_TOP)
		{
			// initialize the mode of inverted
			SET_BIT(TCCR1A,TCCR1A_COM1A1);
			SET_BIT(TCCR1A,TCCR1A_COM1A0);
		}
		else if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_FAST_PWM == SET_ON_COMP_CLR_ON_TOP)
		{
			// normal port operation
			CLR_BIT(TCCR1A,TCCR1A_COM1A0);
			CLR_BIT(TCCR1A,TCCR1A_COM1A1);
		}
		//initialize the mode of the wave generation mode
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);

	}

#elif (CHANNEL_SELECT == CHANNEL_B)
	if(Waveform_Generation_Mode_TIMER1 == NORMAL_1 || Waveform_Generation_Mode_TIMER1 == CTC_1)
		{
			/**initialize the mode of the timer  */
			if(COMPARE_MATCH_OUTPUT_MODE_TIMER1 == OC1_DISCONNECT)
			{
				CLR_BIT(TCCR1A,TCCR1A_COM1B0);
				CLR_BIT(TCCR1A,TCCR1A_COM1B1);
			}
			else if(COMPARE_MATCH_OUTPUT_MODE_TIMER1 == OC1_TOGGLE)
			{
				SET_BIT(TCCR1A,TCCR1A_COM1B0);
				CLR_BIT(TCCR1A,TCCR1A_COM1B1);
			}
			else if(COMPARE_MATCH_OUTPUT_MODE_TIMER1 == OC1_CLR)
			{
				SET_BIT(TCCR1A,TCCR1A_COM1B1);
				CLR_BIT(TCCR1A,TCCR1A_COM1B0);
			}
			else
			{
				SET_BIT(TCCR1A,TCCR1A_COM1B1);
				SET_BIT(TCCR1A,TCCR1A_COM1B0);
			}
	#if(Waveform_Generation_Mode_TIMER1 == CTC_1 )
		// set interrupt
		SET_BIT(TIMSK,TIMSK_OCIE1A);
		// set the wave generation mode of CTC
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);

	#elif(Waveform_Generation_Mode_TIMER1 == NORMAL_1)
		// set interrupt
		SET_BIT(TIMSK,TIMSK_TOIE1);
		// set the wave generation mode of normal mode
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
	#endif
		}
		else if(Waveform_Generation_Mode_TIMER1 == PWM_Phase_Correct_8_bit_1)
		{
			if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_PHASE_PWM == SET_ON_UP_COUNT_CLR_ON_DOWN_COUNT)
			{
				// inititalize the mode of non inverted
				CLR_BIT(TCCR1A,TCCR1A_COM1B0);
				SET_BIT(TCCR1A,TCCR1A_COM1B1);
			}
			else if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_PHASE_PWM == CLR_ON_UP_COUNT_SET_ON_DOWN_COUNT)
			{
				// inititalize the mode of inverted
				SET_BIT(TCCR1A,TCCR1A_COM1B1);
				SET_BIT(TCCR1A,TCCR1A_COM1B0);
			}
			else
			{
				//inititalize the non
				CLR_BIT(TCCR1A,TCCR1A_COM1B0);
				CLR_BIT(TCCR1A,TCCR1A_COM1B1);
			}
			//inititalize the waveform generation mode of the phase correct_pwm
			SET_BIT(TCCR1A,TCCR1A_WGM10);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			CLR_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);

		}
		else if(Waveform_Generation_Mode_TIMER1 == Fast_PWM_8_bit_1)
		{

			if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_FAST_PWM == SET_ON_Top_CLR_ON_COMP)
			{
				// initialize the mode if non inverted
				CLR_BIT(TCCR1A,TCCR1A_COM1B0);
				SET_BIT(TCCR1A,TCCR1A_COM1B1);

			}
			else if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_FAST_PWM == SET_ON_COMP_CLR_ON_TOP)
			{
				// initialize the mode of inverted
				SET_BIT(TCCR1A,TCCR1A_COM1B1);
				SET_BIT(TCCR1A,TCCR1A_COM1B0);
			}
			else
			{
				// normal port operation
				CLR_BIT(TCCR1A,TCCR1A_COM1B0);
				CLR_BIT(TCCR1A,TCCR1A_COM1B1);
			}
			//initialize the mode of the wave generation mode
			SET_BIT(TCCR1A,TCCR1A_WGM10);
			CLR_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			CLR_BIT(TCCR1B,TCCR1B_WGM13);
		}
		else if(Waveform_Generation_Mode_TIMER1 == Fast_PWM_SERVO_1)
		{
			if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_FAST_PWM == SET_ON_Top_CLR_ON_COMP)
			{
				// initialize the mode if non inverted
				CLR_BIT(TCCR1A,TCCR1A_COM1B0);
				SET_BIT(TCCR1A,TCCR1A_COM1B1);

			}
			else if(COMPARE_MATCH_OUTPUT_MODE_TIMER1_FAST_PWM == SET_ON_COMP_CLR_ON_TOP)
			{
				// initialize the mode of inverted
				SET_BIT(TCCR1A,TCCR1A_COM1B1);
				SET_BIT(TCCR1A,TCCR1A_COM1B0);
			}
			else
			{
				// normal port operation
				CLR_BIT(TCCR1A,TCCR1A_COM1B0);
				CLR_BIT(TCCR1A,TCCR1A_COM1B1);
			}
			//initialize the mode of the wave generation mode
			CLR_BIT(TCCR1A,TCCR1A_WGM10);
			SET_BIT(TCCR1A,TCCR1A_WGM11);
			SET_BIT(TCCR1B,TCCR1B_WGM12);
			SET_BIT(TCCR1B,TCCR1B_WGM13);

		}

#endif
	/*SET the Pre-Scalar Value*/
		TCCR1B &= PRE_SCALE_MASK;
		TCCR1B |= CLK_64;

}
void timer1_voidSetChannelA_CompareMatch(u16 value)
{
	OCR1AL =  value;
}



void TIMER1_voidSetICR(u16 copy_u16ICRVAL)
{
	/*Set the ICR top value with value for servo motor fast_pwm */
	ICR1L = copy_u16ICRVAL;
}


u8  TIMER0_u8SetCallPack_OV(void(*CAll_packFunc)(void))
{
	u8 Local_u8ReturnState = OK;

	if(CAll_packFunc == 0)
	{
		Local_u8ReturnState = NOK;
	}
	else
	{
		callPackFunc_0 = CAll_packFunc;
	}
	return Local_u8ReturnState;
}

u8  TIMER0_u8SetCallPack_cmp(void(*CAll_packFunc)(void))
{
	u8 Local_u8ReturnState = OK;

	if(CAll_packFunc == 0)
	{
		Local_u8ReturnState = NOK;
	}
	else
	{
		callPackFunc_0 = CAll_packFunc;
	}
	return Local_u8ReturnState;
}

u8 timer1_voidSetCallBack_OV (void(*callbackfunc)(void))
{
	u8 return_Status = OK;
	if(callbackfunc == 0)
	{
		return_Status =NOK;
	}
	else
	{
		callPackFunc_1 = callbackfunc;
	}
    return return_Status;
}

u8 timer1_voidSetCallBack_Cmp (void(*callbackfunc)(void))
{
	u8 return_Status = OK;
		if(callbackfunc == 0)
		{
			return_Status =NOK;
		}
		else
		{
			callPackFunc_1 = callbackfunc;
		}
		return return_Status;
}
void timer1_set(u16 value)
{
	TCNT1 = value;
}

u16 read_timer1(void)
{
	return TCNT1;
}

void ICR_VoidInit(void)
{
	/*Set the trigger mode to Rising Edge mode*/
	SET_BIT(TCCR1B,TCCR1B_ICES1);
	/* Enable ICU Interrupt */
	SET_BIT(TIMSK,TIMSK_TICIE1);
}
void IVU_VoidSetTriggerEdge(u8 copu_u8Edge)
{
	u8 return_State = 1;
  if(copu_u8Edge == ICU_RISING_EDGE)
  {
	  SET_BIT(TCCR1B,TCCR1B_ICES1);
  }
  else if(copu_u8Edge == ICU_FALLING_EDGE)
  {
	  CLR_BIT(TCCR1B,TCCR1B_ICES1);
  }

}

void ICU_VoidInteruptEnable(void)
{
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

void ICU_VoidInteruptDisable(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

u16 ICU_u16ReadCaptureUnit(void)
{
	return ICR1L;
}

u8 ICU_voidSetCallBack(void(*SETCallBackFunc)(void))
{
	u8 Return_state = OK;
	if(SETCallBackFunc == 0)
	{
		Return_state = NOK;
	}
	else
	{
		callPackFunc_ICU = SETCallBackFunc;
	}
	return Return_state;

}
/*******************************ISR************************************************/
/*ISR FUNCTION for ctc intrupt fro timer 0*/
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{

	callPackFunc_0();

}
/*ISR FUNCTION for OVER Flow intrupt for timer 0*/
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{

	callPackFunc_0();
}
/*ISR FUNCTION for OVER Flow intrupt for timer 1*/
void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	callPackFunc_1();
}
/*ISR FUNCTION for cmp match event(CTC) for timer 1*/
void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	callPackFunc_1();
}
/*ISR FUNCTION for ICU */
void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	callPackFunc_ICU();
}
void Set_Prescalar(u8 value)
{
if(value == 0)
{
	CLR_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
}
else if(value == 3)
{
	    SET_BIT(TCCR0,TCCR0_CS00);
	    SET_BIT(TCCR0,TCCR0_CS01);
		CLR_BIT(TCCR0,TCCR0_CS02);
}

}
void timer2_pwm_Init(void)
{
	SET_BIT(TCCR2,TCCR2_WGM20);
	SET_BIT(TCCR2,TCCR2_WGM21);

	CLR_BIT(TCCR2,TCCR2_COM20);
	SET_BIT(TCCR2,TCCR2_COM21);

	SET_BIT(TCCR2,TCCR2_CS22);
	CLR_BIT(TCCR2,TCCR2_CS20);
	CLR_BIT(TCCR2,TCCR2_CS21);
    //OCR2 = value;
}
void pwm_timer2(u8 val)
{
	OCR2 = val;
}





