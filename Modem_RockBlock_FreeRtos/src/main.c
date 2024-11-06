/*
Author		: Abdelrahman Ahmed Aboalam
date		: 19/4/2024
version		: 1.0.0
description : main.c-> Application
peri		: for user to implement code
*/
/*********************************************/
/*********************************************/

/***************	Standard LIBS include	***************/

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

/***************	FreeRtos LIBS include	***************/

#include"../FreeRTOS/include/FreeRTOS.h"
#include"../FreeRTOS/FreeRTOSConfig.h"
#include"../FreeRTOS/include/task.h"
#include"../FreeRTOS/include/queue.h"
#include"../FreeRTOS/include/semphr.h"

/***************	MCAL  include	***************/

#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MNVIC/MNVIC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MUART/MUART_interface.h"
#include "MCAL/MEXTI/MEXTI_interface.h"

/***************	Hal include	***************/

#include "HAL/RockBlock_interface.h"

/***************	Define tasks 	***************/

TaskHandle_t VReceive_Alert = NULL;
TaskHandle_t VReceive_States = NULL;

/***************	Proto type of tasks 	***************/


void Receive_Alert ();
void Receive_States ();
void Interrupt(void);

/***********************	Entry Point in My Application	**********************/

int main ( )
{
/***********************	Here I initialize Peripherals 	**********************/

/*****************************************************************************************/
/* @RCC  	  :->		@ CLOCK 16MHZ (GPIOA,UART1,TIM3)    							 */
/* @UART      :->    	@ UART1 (Baud Rate = 19200)                                		 */
/* @EXT0      :->	    @ I initialize Line 0 To Pin 0 GPIO A in FALLING EDGE			 */
/*****************************************************************************************/
	MRCC_voidInitializeSystemClock();
	MUSART_voidInit();
	MRCC_voidEnablePeripheralClock(MRCC_AHB1,MRCC_GPIOA_EN);
	MRCC_voidEnablePeripheralClock(MRCC_APB2,MRCC_USART1_EN);
	MEXTI_voidSelectPort(MEXTI_LINE0,MEXTI_PORTA);
	MEXTI_voidEnableEXTI(MEXTI_LINE0);
	MEXTI_voidTriggerSource(MEXTI_LINE0,MEXTI_FALLING_EDGE);

/***********************	Here is The Pin OUT 	**********************/

/*************************************GPIO_A_*************************************************/
/* @Pin_0  	  :->		@ Input  ----> For External Interrupt       				    	 */
/* @Pin_5 	  :->		@ Output ----> For Relay                                             */
/* @Pin_9     :->    	@ PushPull---> For TX in UART  -----> AltFunc in line AF7          	 */
/* @Pin_10    :->	    @ PushPull---> For RX in UART  -----> AltFunc in line AF7	       	 */
/*********************************************************************************************/

	MGPIO_voidSetPinMode(MGPIO_u8PORTA,0,MGPIO_u8INPUT);
	MGPIO_voidSetOutputType(MGPIO_u8PORTA,9,MGPIO_u8PUSHPULL);
	MGPIO_voidSetOutputType(MGPIO_u8PORTA,10,MGPIO_u8NOPushPull);

	MGPIO_voidSetPinMode(MGPIO_u8PORTA,9,MGPIO_u8ALTFUNC);
	MGPIO_voidSetPinMode(MGPIO_u8PORTA,10,MGPIO_u8ALTFUNC);

	MGPIO_voidSetAltFunc(MGPIO_u8PORTA,9,GPIO_u8AF7);
	MGPIO_voidSetAltFunc(MGPIO_u8PORTA,10,GPIO_u8AF7);

	MGPIO_voidSetPinMode(MGPIO_u8PORTA,5,MGPIO_u8OUTPUT);

/***********************	Here I send Function to ISR 	**********************/

/*************************************_*******************************************************/
/* @EXTERNAL INTERRUPT        :->	@ I send Line 0 And Function     			     	     */
/*********************************************************************************************/
	MEXTI_voidSetCallBack(MEXTI_LINE0,&Interrupt);

/***********************	Here Enable Peripherals 	**********************/

	MUSART_voidEnable();
	MNVIC_voidEnableInterrupt(6);
	MNVIC_voidEnableInterrupt(37);

/***********************	Here I creat tasks 	**********************/

	xTaskCreate (Receive_Alert , "Task1" ,128, NULL ,1,&VReceive_Alert );
	xTaskCreate (Receive_States , "Task2" ,128, NULL ,2,&VReceive_States );

/***********************	Here I start schedler 	**********************/

	vTaskStartScheduler();

	return 0;
}

/***********************	Global Functions Implementations tasks **********************/

/*****************************************************************************************************/
/* @Name  	  :->		@ Receive_Alert										                         */
/* @Brief 	  :->		@ Used to Send ALERT to Stalite                                         	 */
/* @parameters   :-> 	@ No Parameters                                                     		 */
/* @PreRequsteis :->	@ Same Function of SEND_Massage	           							 		 */
/*****************************************************************************************************/

void Receive_Alert ()
{
	while(1)
	{
/***********************	Here I suspend task itself until ISR open 	**********************/
		vTaskSuspend(NULL);
		Error_state_t Error_State=  Send_Massage((u8 *)"ALERT");
		while (Error_State == false )
		{
			 Error_State=  Send_Massage((u8 *)"ALERT");
		}
		vTaskDelay(300);
	}

}
/*****************************************************************************************************/
/* @Name  	  :->		@ Receive_States										             */
/* @Brief 	  :->		@ Used to check massage from Model if TURNOFF or TURNON to control Relay	 */
/* @parameters   :-> 	@ No Parameters                                                     		 */
/* @PreRequsteis :->	@ GPIO MUST be initialized	            							 		 */
/*****************************************************************************************************/

void Receive_States ()
{
	u8 *Message_Received=NULL;
		Message_Received=Recive_Massage();
		if(Message_Received[0]=='T'&&Message_Received[5]=='N')
		{
			MGPIO_voidSetPinValue(MGPIO_u8PORTA,5,MGPIO_u8HIGH);
		}
		else if (Message_Received[0]=='T'&&Message_Received[5]=='F')
		{
			MGPIO_voidSetPinValue(MGPIO_u8PORTA,5,MGPIO_u8LOW);
		}
	while(1)
	{


	}

}

/*****************************************************************************************************/
/* @Name  	  :->		@ Interrupt										                             */
/* @Brief 	  :->		@ to send this func to ISR and resume task                               	 */
/* @parameters   :-> 	@ No Parameters                                                     		 */
/* @PreRequsteis :->	@ Must find task suspended	            							 		 */
/*****************************************************************************************************/

void Interrupt(void)
{
	BaseType_t Check_Yield;
	Check_Yield=xTaskResumeFromISR(VReceive_Alert);
	portYIELD_FROM_ISR(Check_Yield);
}
