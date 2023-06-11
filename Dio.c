#include "Dio.h"
void config(Dio_ChannelType ChannelId, PinMode Mode){
	identifyPin
	
	GPIOMode_TypeDef libPinMode;
	uint32_t RCC_APB2Periph;
	
	if(gpioPort == GPIOA)RCC_APB2Periph = RCC_APB2Periph_GPIOA;
	else if(gpioPort == GPIOB)RCC_APB2Periph = RCC_APB2Periph_GPIOB;
	else RCC_APB2Periph = RCC_APB2Periph_GPIOC;
	
	if(Mode == INPUT_PULLUP)libPinMode = GPIO_Mode_IPU;
	else if(Mode == OUTPUT) libPinMode = GPIO_Mode_Out_PP;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph,ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Pin = gpioPin;
	gpio.GPIO_Mode = libPinMode;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(gpioPort, &gpio);
}

void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level){
	identifyPin
	if(Level == STD_LOW) GPIO_ResetBits(gpioPort, gpioPin);
	else GPIO_SetBits(gpioPort, gpioPin);
}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId){
	identifyPin
	if(GPIO_ReadInputDataBit(gpioPort,gpioPin) == 0) return STD_LOW;
	else return STD_HIGH;
}
void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level){
	GPIO_TypeDef * gpioPort;
	if(PortId == PortA)gpioPort = GPIOA;
	else if(PortId == PortB)gpioPort = GPIOB;
	else gpioPort = GPIOC;
	GPIO_Write(gpioPort,Level);
}
