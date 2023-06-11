#include "Dio.h"
#include <setjmp.h>
#define led1 DIO_CHANNEL_PC13
#define led2 DIO_CHANNEL_PC14
#define led3 DIO_CHANNEL_PC15
#define btn1 DIO_CHANNEL_PA0
#define btn2 DIO_CHANNEL_PA1
#define btn3 DIO_CHANNEL_PA2

jmp_buf buf;

void delay_ms(uint8_t time);
void blinkLed(uint8_t time);
void lightupLed(uint8_t time);
void turnOffLed(void);
int main(void){
	int label;
	config(led1, OUTPUT);
	config(led2, OUTPUT);
	config(led3, OUTPUT);
	config(btn1, INPUT_PULLUP);
	config(btn2, INPUT_PULLUP);
	config(btn3, INPUT_PULLUP);
	Dio_WriteChannel(led1,STD_HIGH); 
	Dio_WriteChannel(led2,STD_HIGH);
	Dio_WriteChannel(led3,STD_HIGH);
	label = setjmp(buf);
	while(1)
	{
		if(Dio_ReadChannel(btn1) == STD_LOW) blinkLed(8);
		if(Dio_ReadChannel(btn2) == STD_LOW) lightupLed(8);
	}
}
void delay_ms(uint8_t time){
	uint32_t i;
	for(i = 0; i < time*9000; i++);
}

void blinkLed(uint8_t time){
	uint8_t i;
	for(i = 0; i < time; i++)
	{
		Dio_WriteChannel(led1,STD_LOW);
		Dio_WriteChannel(led2,STD_LOW);	
		Dio_WriteChannel(led3,STD_LOW);
		if(Dio_ReadChannel(btn3) == STD_LOW)
		{
			delay_ms(5);
			turnOffLed();
		}
		else delay_ms(80);
		Dio_WriteChannel(led1,STD_HIGH); 
		Dio_WriteChannel(led2,STD_HIGH);
		Dio_WriteChannel(led3,STD_HIGH);
		if(Dio_ReadChannel(btn3) == STD_LOW)
		{
			delay_ms(5);
			turnOffLed();
		}
		else delay_ms(80);
	}				
}
void lightupLed(uint8_t time){
	uint8_t i;
	for(i = 0; i < time; i++)
	{
		Dio_WriteChannel(led1,STD_LOW);
		Dio_WriteChannel(led2,STD_HIGH);	
		Dio_WriteChannel(led3,STD_HIGH);
		if(Dio_ReadChannel(btn3) == STD_LOW)
		{
			delay_ms(5);
			turnOffLed();
		}
		else delay_ms(80);
		Dio_WriteChannel(led1,STD_LOW);
		Dio_WriteChannel(led2,STD_LOW);	
		Dio_WriteChannel(led3,STD_HIGH);
		if(Dio_ReadChannel(btn3) == STD_LOW)
		{
			delay_ms(5);
			turnOffLed();
		}
		else delay_ms(80);
		Dio_WriteChannel(led1,STD_LOW);
		Dio_WriteChannel(led2,STD_LOW);	
		Dio_WriteChannel(led3,STD_LOW);
		if(Dio_ReadChannel(btn3) == STD_LOW)
		{
			delay_ms(5);
			turnOffLed();
		}
		else delay_ms(80);
		Dio_WriteChannel(led1,STD_HIGH);
		Dio_WriteChannel(led2,STD_HIGH);	
		Dio_WriteChannel(led3,STD_HIGH);
		if(Dio_ReadChannel(btn3) == STD_LOW)
		{
			delay_ms(5);
			turnOffLed();
		}
		else delay_ms(80);
	}
}

void turnOffLed(void){
	Dio_WriteChannel(led1,STD_HIGH);
	Dio_WriteChannel(led2,STD_HIGH);	
	Dio_WriteChannel(led3,STD_HIGH);
	longjmp(buf,1);
}
