/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MACL             *********************/
/********************** SWC        : TIMER             *********************/
/********************** version    : 1.00          *********************/
/***********************************************************************/
/***********************************************************************/
#ifndef TIMER_REGISTER_h
#define TIMER_REGISTER_H

#define TCCR0                *((volatile u8 *)0x53) // timer 0 control register
#define TCCR0_CS00           0                       /*  Pre_scalar 0*/
#define TCCR0_CS01           1                       /*  Pre_scalar 1*/
#define TCCR0_CS02           2                       /*  Pre_scalar 2*/
#define TCCR0_WGRM01         3                       // wave form generation mode bit 1
#define TCCR0_COM00          4                       //control the Output Compare pin (OC0) behavior
#define TCCR0_COM01          5                         //control the Output Compare pin (OC0) behavior
#define TCCR0_WGRM00         6                         // wave form generation mode bit 0
#define TMSK_OCIE0           1                         // output compare 0 intrupt enable
#define TMSK_TOIE0           0
#define OCR0                 *((volatile u8 *)0x5C)    // output compare register 0
#define TIMSK                *((volatile u8 *)0x59)    // timer mask

#define TIMSK_TOIE1          2                         //Overflow Interrupt Enable
#define TIMSK_OCIE1B         3                        // Output Compare B Match Interrupt Enable
#define TIMSK_OCIE1A         4                        // Output Compare A Match Interrupt Enable
#define TIMSK_TICIE1         5                        //Input Capture Interrupt Enable

#define TCNT0                *((volatile u8 *)0x52)
#define TIFR                 *((volatile u8 *)0x58)
#define TIFR_TOV0            0
/* REGISTERS DEFINATION FOR TIMER 1 16 BIT TIMER*/

#define TCCR1A               *((volatile u8  *)0x4F)    // Timer/counter 1 countrol register A
#define TCCR1B               *((volatile u8  *)0x4E)    //Timer/Counter1 Control Register B
#define ICR1L                *((volatile u16 *)0x46)    //Input Capture Register LOW Byte
#define OCR1AL               *((volatile u16  *)0x4A)    // Output Compare Register A Low Byte
#define OCR1BL               *((volatile u16 *)0x48)
#define TCCR1A_WGM10         0
#define TCCR1A_WGM11         1
#define TCCR1A_FOC1A         3
#define TCCR1A_FOC1B         2
#define TCCR1A_COM1B0        4
#define TCCR1A_COM1B1        5
#define TCCR1A_COM1A0        6
#define TCCR1A_COM1A1        7
#define TCNT1               *((volatile u16 *)0x4C)



#define TCCR1B_CS10          0      // clock select Pre_scalar
#define TCCR1B_CS11          1      // clock select Pre_scalar
#define TCCR1B_CS12          2      // clock select Pre_scalar
#define TCCR1B_WGM12         3      //Waveform Generation Mode
#define TCCR1B_WGM13         4      //Waveform Generation Mode
#define TCCR1B_ICES1         6      //input capture edge select
#define TCCR1B_ICNC1         7      //Input Capture Noise Canceler

#define TCCR2                *((volatile u8 *)0x45)
#define TCCR2_WGM21          3
#define TCCR2_WGM20          6
#define TCCR2_COM20          4
#define TCCR2_COM21          5
#define TCCR2_CS20           0
#define TCCR2_CS21            1
#define TCCR2_CS22           2
#define OCR2           *((volatile u8 *)0x43)

#endif

