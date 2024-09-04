/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MACL             *********************/
/********************** SWC        : TIMER             *********************/
/********************** version    : 1.00             *********************/
/***********************************************************************/
/***********************************************************************/
#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H
#define CLK_64                        3
#define NO_CLK_SOURCE 0
/*For Edge select ICU*/
#define ICU_RISING_EDGE     1
/*For Edge select ICU*/
#define ICU_FALLING_EDGE    0

/**
 * @brief  initialize  for the Timer0 [normal , ctc , fast pwm , phase correct pwm ].
 * @param  void
 * @return void
 */
void TIMER0_voidInit(void);
void timer0_delay(u16 time_in_ms);
void TIMER0_voidsetPReload(u8 val);
/**
 * @brief  Sets the callback function for the Timer0 Compare Match interrupt.
 * @param  CAll_packFunc: Pointer to the callback function.
 * @return u8: Status of the function (OK if successful, NOK if not).
 */
u8  TIMER0_u8SetCallPack_cmp(void(*CAll_packFunc)(void));
u8  TIMER0_u8SetCallPack_OV(void(*CAll_packFunc)(void));
/**
 * @brief  set the OC0 the compare match value [fast pwm on pin 0c0 ]
 * @param  value range from 0 -> 255
 * @return void
 */
void timer0_voidSetCompareValue(u8 value);

/**
 * @brief  initialize  for the Timer1
 * @param  void
 * @return void
 */
void Set_Prescalar(u8 value);
/*******************************************************/

void timer1_set(u16 value);

u16 read_timer1(void);

void TIMER1_voidInit(void);

void TIMER1_voidSetICR(u16 copy_u16ICRVAL);

void timer1_voidSetChannelA_CompareMatch(u16 value);

u8 timer1_voidSetCallBack_OV (void(*callbackfunc)(void));

u8 timer1_voidSetCallBack_Cmp (void(*callbackfunc)(void));

void timer2_pwm_Init(void);
void pwm_timer2(u8 val);
/*******************************************************/

/** set the icu modes
 * @param void
 */
void ICU_VoidInit(void);


/**
 * choose option
 *  ICU_RISING_EDGE    1
    ICU_FALLING_EDGE   0
 * @param Copy_u8trigger
 */
void IVU_VoidSetTriggerEdge(u8 copu_u8Edge);

/**
 * @param void
 */
void ICU_VoidInteruptEnable(void);
/**
 * @param void
 */
void ICU_VoidInteruptDisable(void);
/**
 * @param void
 */
u16 ICU_u16ReadCaptureUnit(void);

u8 ICU_voidSetCallBack(void(*SETCallBackFunc)(void));

#endif
