#define POWER_DISP_ONE PORTD = 0X70;
#define POWER_DISP_TWO PORTD = 0XBF;
#define LED_OFF PORTB = 0XFF;
#define GON PORTC = (0 << PC0);
#define GOFF PORTC = (1 << PC0);
#define BIT_IS_SET(byte, bit) (byte & (1 << bit))
#define BIT_IS_CLEAR(byte, bit) (!(byte & (1 << bit)))
#define F_CPU 16000000UL

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

int TEMPERATURE_SENC()
{
	float bin;
	ADMUX = 0b01100101;
	ADCSRA = 0b10000011;      //Reading A5
	
	ADCSRA |= (1 << ADSC);// start ADC
	if(BIT_IS_SET(ADCRA, ADSC))
	{
	    _delay_ms(5);
	    bin = ADCH;
	}
	if(BIT_IS_CLEAR(ADCRA, ADSC))
	{
	    ADCSRA |= (1 << ADSC);
	}
	bin = ADCH;							// assign contents of ADC high register to bin
	return bin;
}

void zero()
{
	PORTB = 0X00;
}
void one()
{
	PORTB = 0X0F;
}
void two()
{
	PORTB = 0X24;
	GON;
}
void three()
{
	PORTB = 0X30;
	GON;
}
void four()
{
	PORTB = 0X19;
	GON;
}
void five()
{
	PORTB = 0X12;
	GON;
}
void six()
{
	PORTB = 0X02;
	GON;
}
void seven()
{
	PORTB = 0X38;
}
void eight()
{
	PORTB = 0X00;
	GON;
}
void nine()
{
	PORTB = 0X10;
	GON;
}
void DISPLAYsingle(int i)
{
	switch(i)
	{
		case 0:
		GOFF;
		LED_OFF;
		zero();
		break;
		
		case 1:
		GOFF;
		LED_OFF;
		one();
		break;
		
		case 2:
		GOFF;
		LED_OFF;
		two();
		break;
		
		case 3:
		GOFF;
		LED_OFF;
		three();
		break;
		
		case 4:
		GOFF;
		LED_OFF;
		four();
		break;
		
		case 5:
		GOFF;
		LED_OFF;
		five();
		break;
		
		case 6:
		GOFF;
		LED_OFF;
		six();
		break;
		
		case 7:
		GOFF;
		LED_OFF;
		seven();
		break;
		
		case 8:
		GOFF;
		LED_OFF;
		eight();
		break;
		
		case 9:
		GOFF;
		LED_OFF;
		nine();
		break;
				
		default:
		GOFF;
		LED_OFF;
	}
}
void numberposition(int num, int *r1, int *r0)
{
	int pos0 = 0, pos1 = 1;
	*r1 = num / pow(10, pos1);
	*r1 = *r1 % 10;
	
	*r0 = num / pow(10, pos0);
	*r0 = *r0 % 10;
}
void DISPLAY_HOUR(int hour)
{
	int position_one, position_zero;
	numberposition(hour, &position_one, &position_zero);
	PORTD = 0X00;
	PORTD = (1 << PD4);
	DISPLAYsingle(position_one);
	_delay_ms(5);
	LED_OFF;
	PORTD = 0X00;
	PORTD = (1 << PD5);
	DISPLAYsingle(position_zero);
	_delay_ms(5);
}

void DISPLAY_MINUTE(int minute)
{
	int position_one, position_zero;
	numberposition(minute, &position_one, &position_zero);
	PORTD = 0X00;
	PORTD = (1 << PD6);
	DISPLAYsingle(position_one);
	_delay_ms(5);
	LED_OFF;
	PORTD = 0X00;
	PORTD = (1 << PD7);
	DISPLAYsingle(position_zero);
	_delay_ms(5);
}
void DISPLAY_DEGREE_CEL()
{
	PORTD = 0X00;
	PORTD = (1 << PD6);
	GOFF;
	LED_OFF;
	PORTB = 0X1C;
	GON;
	_delay_ms(5);
	LED_OFF;
	PORTD = 0X00;
	PORTD = (1 << PD7);
	GOFF;
	LED_OFF;
	PORTB = 0X06;
	_delay_ms(5);	
}

int main(void)
{
	/* Replace with your application code */
	float hour = 0;
	int hhour = 0, i = 0;
	DDRB |= 0XFF;
	DDRD |= 0XFF;
	DDRC |= (1 << PC0);
	while(1)
	{
		if(i > 49)
		{
			i = 0;
			hour = TEMPERATURE_SENC();
		}
		hhour = 10*hour/9.3;
		DISPLAY_HOUR(hhour);

		DISPLAY_DEGREE_CEL();
		i++;
	}
	return 0;
}
