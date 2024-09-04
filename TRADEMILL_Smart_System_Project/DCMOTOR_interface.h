#ifndef DC_MOTOR_INTERFACE_H
#define DC_MOTOR_INTERFACE_H


#define MOTOR_OF 0
#define MOTOR_ON 1
typedef struct
{
	u8 Pin;
	u8 Port;
	u8 Motor_Status;
}Motor_Spec;

typedef struct
{
	Motor_Spec motor_Pin[2];
}Motor_t;


u8 DC_Motor_Init(const Motor_t *Motor);
u8 DC_Motor_Move_Right(const Motor_t *Motor);
u8 DC_Motor_Move_Left(const Motor_t *Motor);
u8 DC_Motor_Stop(const Motor_t *Motor);

#endif
