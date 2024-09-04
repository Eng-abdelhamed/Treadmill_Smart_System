/*********************************************   **************************/
/******************************************      **************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : HAL              *********************/
/********************** SWC        : DC_Motor         *********************/
/********************** version    : 1.00             *********************/
/**********************************************   *************************/
/*********************************************   **************************/
#include"STD_TYPEs.h"
#include"BIT_MATH.h"
#include"DIO_register.h"
#include"DIO_interface.h"
#include"DIO_config.h"
#include"DIO_private.h"
#include"DCMOTOR_interface.h"
#include"DCMOTOR_config.h"
#include"DCMOTOR_private.h"


u8 DC_Motor_Init(const Motor_t *Motor)
{
u8 Return_Status = OK;
   if(Motor == NULL)
   {
	   Return_Status = NOK;
   }
   else
   {
	   DIO_u8SetPinDirection(Motor->motor_Pin[0].Port , Motor->motor_Pin[0].Pin,DIO_u8PIN_Output);
	   DIO_u8SetPinDirection(Motor->motor_Pin[1].Port , Motor->motor_Pin[1].Pin,DIO_u8PIN_Output);
   }
   return Return_Status;
}
u8 DC_Motor_Move_Right(const Motor_t *Motor)
{
	u8 Return_Status = OK;
	   if(Motor == NULL)
	   {
		   Return_Status = NOK;
	   }
	   else
	   {
		DIO_u8SetPinValue(Motor->motor_Pin[0].Port , Motor->motor_Pin[0].Pin,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(Motor->motor_Pin[1].Port , Motor->motor_Pin[1].Pin,DIO_u8PIN_LOW);
	   }
	   return Return_Status;
}
u8 DC_Motor_Move_Left(const Motor_t *Motor)
{
	u8 Return_Status = OK;
	   if(Motor == NULL)
	   {
		   Return_Status = NOK;
	   }
	   else
	   {
		DIO_u8SetPinValue(Motor->motor_Pin[0].Port , Motor->motor_Pin[0].Pin,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Motor->motor_Pin[1].Port , Motor->motor_Pin[1].Pin,DIO_u8PIN_HIGH);
	   }
	   return Return_Status;
}
u8 DC_Motor_Stop(const Motor_t *Motor)
{
	u8 Return_Status = OK;
	   if(Motor == NULL)
	   {
		   Return_Status = NOK;
	   }
	   else
	   {
		DIO_u8SetPinValue(Motor->motor_Pin[0].Port , Motor->motor_Pin[0].Pin,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Motor->motor_Pin[1].Port , Motor->motor_Pin[1].Pin,DIO_u8PIN_LOW);
	   }
	   return Return_Status;
}
