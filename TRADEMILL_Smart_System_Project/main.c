/*
 * main.c
 *
 *  Created on: Sep 3, 2024
 *      Author: abdel
 */

#include "STD_TYPEs.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"
#include "DCMOTOR_interface.h"
#include "PIR_Interface.h"
#include "util/delay.h"

// Function prototypes
void speed_down(void);
void speed_up(void);
void ISR_TIMERcount(void);

s32 Map(s32 input_min, s32 input_max, s32 output_min, s32 output_max, s32 input_val);

// Global variables
u8 PIR_Status;
u8 second = 0;
u8 minutes = 0;
u8 hours = 0;
u8 duty_cycle =25;

u8 stop_button;
u8 resume_button;
u8 reset_status_pin;

// Motor configuration
Motor_t motor1_pin = {
    .motor_Pin[0].Pin = DIO_u8PIN0,
    .motor_Pin[0].Port = DIO_u8PORTB,
    .motor_Pin[0].Motor_Status = MOTOR_OF,
    .motor_Pin[1].Pin = DIO_u8PIN1,
    .motor_Pin[1].Port = DIO_u8PORTB,
    .motor_Pin[1].Motor_Status = MOTOR_OF
};

int main(void)  // Changed return type to int for standard practice
{
    /* Global Interrupt Enable */
    GIE_voidEnable();
    DC_Motor_Init(&motor1_pin);
    /*************************************************************/
    /* Timer 0 for counter initialization */
    TIMER0_voidInit();
    timer2_pwm_Init();
    TIMER0_u8SetCallPack_OV(&ISR_TIMERcount);


    /*************************************************************/
    /* EXTI 0 for speed up button initialization */
    EXTI_voidInt0init();
    EXTI_u8INT0SetSenseCtrl(RISING_EDGE);
    EXIT_u8int0CallBack(&speed_up);
    /*************************************************************/
    /* EXTI 1 for speed down button initialization */
    EXTI_voidInt1init();
    EXTI_u8INT1SetSenseCtrl(RISING_EDGE);
    EXIT_u8int1CallBack(&speed_down);

    /*************************************************************/


    /*************************************************************/
    /* Initialize motor pin input */
    DC_Motor_Init(&motor1_pin);
    DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN2, DIO_u8PIN_INPUT);
    DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN3, DIO_u8PIN_INPUT);
    /* OCR1A -> Generating PWM */
    DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN7, DIO_u8PIN_Output);

    /*************************************************************/
    /* Initialize PIR pin input */
    PIR_Init();

    /*************************************************************/
    /* Initialize stop button pin input */
    DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN4, DIO_u8PIN_INPUT);
    /* Initialize resume button pin input */
    DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN6, DIO_u8PIN_INPUT);
    /* Initialize additional pin for resume button input */
    DIO_u8SetPinDirection(DIO_u8PORTC, DIO_u8PIN4, DIO_u8PIN_INPUT);
    /* Initialize additional pin for speed_up button input */
    DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN2, DIO_u8PIN_INPUT);
    /* Initialize additional pin for speed_down button input */
    DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN3, DIO_u8PIN_INPUT);
    /* Initialize additional pin for PWM button output */
      DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN7, DIO_u8PIN_Output);
    /*************************************************************/
    /* Initialize PORTA -> output */
    DIO_u8SetPortDirection(DIO_u8PORTA, 0x3f);
    /* Initialize 4 PINS in PORTC -> output */
    DIO_u8SetPortDirection(DIO_u8PORTC, 0x0f);

    pwm_timer2(10);
    /*************************************************************/
    while (1)
    {
        PIR_GetState(&PIR_Status);
        DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN6, &resume_button);
        DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN4, &stop_button);
        DIO_u8GetPinValue(DIO_u8PORTC, DIO_u8PIN4, &reset_status_pin);
        /*************************************************************/
        if (PIR_Status == 1)
        {
        	pwm_timer2(duty_cycle);
        	DIO_u8SetPortValue(DIO_u8PORTA,0x3f);
        	DIO_u8SetPortValue(DIO_u8PORTC,(u8)second%10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x20);
            _delay_ms(10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x1F);
            DIO_u8SetPortValue(DIO_u8PORTC,(u8)second/10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x10);
            _delay_ms(10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x2F);

            DIO_u8SetPortValue(DIO_u8PORTC,(u8)minutes%10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x08);
            _delay_ms(10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x37);

            DIO_u8SetPortValue(DIO_u8PORTC,(u8)minutes/10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x04);
            _delay_ms(10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x3B);
            DIO_u8SetPortValue(DIO_u8PORTC,(u8)hours%10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x02);
            _delay_ms(10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x3D);
            DIO_u8SetPortValue(DIO_u8PORTC,(u8)hours/10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x01);
            _delay_ms(10);
            DIO_u8SetPortValue(DIO_u8PORTA,0x3E);
         	 DC_Motor_Move_Left(&motor1_pin);
           /*************************************************************/
            if (reset_status_pin == 1)
            {
                second = 0;
                minutes = 0;
                hours = 0;
                /*while (reset_status_pin == 1)
                {
                    DIO_u8GetPinValue(DIO_u8PORTC, DIO_u8PIN4, &reset_status_pin);
                }*/
            }
            if(stop_button == 1)
            {
            	Set_Prescalar(NO_CLK_SOURCE);
            /*	while(stop_button == 1)
            	{
            		DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN4, &stop_button);
            	}*/
            }
            if(resume_button == 1)
            {
            	Set_Prescalar(CLK_64);
            	/* while(resume_button == 1)
            	{
            	    DIO_u8GetPinValue(DIO_u8PORTD, DIO_u8PIN6, &resume_button);
            	}*/
            }

        }
        else
        {
        	pwm_timer2(0);
            DIO_u8SetPortValue(DIO_u8PORTA, 0xC0);
        }
    }
}

/*************************************************************/
/* ISR Callback Functions */

void ISR_TIMERcount(void)
{
    static u16 counter = 0;
    counter++;
    if (counter == 489)
    {
        second++;
        counter = 0;
    }
    if (second == 60)
            {
                minutes++;
                second = 0;
            }
            if (minutes == 60)
            {
                hours++;
                minutes = 0;
            }
            if (hours == 24)
            {   hours++;
                hours = 0;
            }
}

/*************************************************************/

void speed_down(void) {
    // Decrease the duty cycle by 25, but not below 0
    if (duty_cycle > 25) {
        duty_cycle -= 25;
    } else {
        duty_cycle = 0; // Ensure duty_cycle does not go negative
    }

    // Update PWM with the new duty cycle value
    pwm_timer2(duty_cycle);
}

void speed_up(void) {
    // Increase the duty cycle by 25, but not above 255
    if (duty_cycle + 25 <= 255) {
        duty_cycle += 25;
    } else {
        duty_cycle = 255; // Cap duty_cycle at 255
    }

    // Update PWM with the new duty cycle value
    pwm_timer2(duty_cycle);
}
