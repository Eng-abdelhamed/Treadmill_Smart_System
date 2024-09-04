







#include"STD_TYPEs.h"
#include"BIT_MATH.h"
#include"DIO_register.h"
#include"DIO_interface.h"
#include"DIO_private.h"
#include"DIO_config.h"
#include"PIR_Interface.h"
#include"PIR_Config.h"


void PIR_Init(void)
{
	DIO_u8SetPinDirection(PIR_PORT,PIR_PIN,DIO_u8PIN_INPUT);
}
u8 PIR_GetState(u8*Copy_u8ReturnState)
{
	u8 Return_Status = 0;
	if(Copy_u8ReturnState == 0)
	{
		Return_Status =1;
	}
	else
	{
		*Copy_u8ReturnState = GET_BIT(PIND,PIR_PIN);
	}
	return Return_Status;

}
