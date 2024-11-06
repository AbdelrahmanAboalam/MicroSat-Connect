/*
Author		: Abdelrahman Ahmed Aboalam
date		: 20/4/2024
version		: 1.0.0
description : main.c-> Application
peri		: for user to implement code
*/
/*********************************************/
/*********************************************/

/***************	Standard LIBS include	***************/
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

/***************	MCAL Files include	***************/
#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MNVIC/MNVIC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSTK_interface.h"
#include "MCAL/MUART/MUART_interface.h"
#include "MCAL/MEXTI/MEXTI_interface.h"
#include "MCAL/MTIM2_5/MTIM2_5_interface.h"

/***************	HAL Files include	***************/
#include "HAL/RockBlock_interface.h"

/*********************************************/
/*********************************************/

/***************	Global Prototypes of Functions For Call_Back to ISR 	***************/
void Func_voidRecieve_Message (void);
void Func_voidSendingALERT (void);



/***********************	Entry Point in My Application	**********************/
int main ( )
{


/***********************	Here I initialize Peripherals 	**********************/

/*****************************************************************************************/
/* @RCC  	  :->		@ CLOCK 16MHZ (GPIOA,UART1,TIM3)    							 */
/* @Timer3 	  :->		@ Prescaler = 122                                                */
/* @UART      :->    	@ UART1 (Baud Rate = 19200)                                		 */
/* @EXT0      :->	    @ I initialize Line 0 To Pin 0 GPIO A in FALLING EDGE			 */
/*****************************************************************************************/
	MRCC_voidInitializeSystemClock();
	TIM2_5_voidInitialize(MTIM_3);
	MUSART_voidInit();
	MRCC_voidEnablePeripheralClock(MRCC_AHB1,MRCC_GPIOA_EN);
	MRCC_voidEnablePeripheralClock(MRCC_APB2,MRCC_USART1_EN);
	MRCC_voidEnablePeripheralClock(MRCC_APB1,MRCC_TIM3_EN);
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
	MGPIO_voidSetPinMode(MGPIO_u8PORTA,5,MGPIO_u8OUTPUT);
	MGPIO_voidSetOutputType(MGPIO_u8PORTA,9,MGPIO_u8PUSHPULL);
	MGPIO_voidSetOutputType(MGPIO_u8PORTA,10,MGPIO_u8NOPushPull);
	MGPIO_voidSetPinMode(MGPIO_u8PORTA,9,MGPIO_u8ALTFUNC);
	MGPIO_voidSetPinMode(MGPIO_u8PORTA,10,MGPIO_u8ALTFUNC);
	MGPIO_voidSetAltFunc(MGPIO_u8PORTA,9,GPIO_u8AF7);
	MGPIO_voidSetAltFunc(MGPIO_u8PORTA,10,GPIO_u8AF7);

/***********************	Here I send Functions to ISR 	**********************/

/*************************************_*******************************************************/
/* @EXTERNAL INTERRUPT        :->	@ I send Line 0 And Function     			     	     */
/* @TIMER For Periodic Event  :->	@ I send NUM of ticks it equal =~ 1 S                    */
/*********************************************************************************************/


	MEXTI_voidSetCallBack(MEXTI_LINE0,&Func_voidSendingALERT);
	MTM3_setInterval_Asyncrouns(130000 , &Func_voidRecieve_Message );

/**************	Here I Make Groups and Sub by NVIC to make nested Interrupts for Make Alert high priority  	****************/

/*************************************_*******************************************************/
/* @EXTERNAL INTERRUPT        :->	@ Group 0 (HIGH piriprity)       			     	     */
/* @TIMER For Periodic Event  :->	@ Group 1 (LOW piriprity)                    */
/*********************************************************************************************/

	MNVIC_voidSetInterruptGroupMode(MNVIC_GROUPMODE_G8S2 );
	MNVIC_voidSetInterruptPeriority(6,0,0,MNVIC_GROUPMODE_G8S2);
	MNVIC_voidSetInterruptPeriority(29,1,0,MNVIC_GROUPMODE_G8S2);

/***********************	Here Enable Peripherals 	**********************/

    MUSART_voidEnable();
	MNVIC_voidEnableInterrupt(6);
	MNVIC_voidEnableInterrupt(37);
	MNVIC_voidEnableInterrupt(29);

	while (1)
	{


	}
	return 0;

}

/*************** Global Functions Implementations	***************/

/*****************************************************************************************************/
/* @Name  	  :->		@ Func_voidRecieve_Message										             */
/* @Brief 	  :->		@ Used to check massage from Model if TURNOFF or TURNON to control Relay	 */
/* @parameters   :-> 	@ No Parameters                                                     		 */
/* @PreRequsteis :->	@ GPIO MUST be initialized	            							 		 */
/*****************************************************************************************************/

void Func_voidRecieve_Message (void)
{
	u8 *Message_Received=NULL;
		Message_Received=Recive_Massage();
		/* CHECK IF TURNON SO [0] is 'T' and [5] is 'N'*/
		if(Message_Received[0]=='T'&&Message_Received[5]=='N')
		{
			MGPIO_voidSetPinValue(MGPIO_u8PORTA,5,MGPIO_u8HIGH);
		}
		/* CHECK IF TURNON SO [0] is 'T' and [5] is 'F'*/
		else if (Message_Received[0]=='T'&&Message_Received[5]=='F')
		{
			MGPIO_voidSetPinValue(MGPIO_u8PORTA,5,MGPIO_u8LOW);
		}

}

/*****************************************************************************************************/
/* @Name  	  :->		@ Func_voidSendingALERT 										             */
/* @Brief 	  :->		@ Used to Send ALERT to Stalite                                          	 */
/* @parameters   :-> 	@ No Parameters                                                     		 */
/* @PreRequsteis :->	@ Same Function of SEND_Massage            							 		 */
/*****************************************************************************************************/

void Func_voidSendingALERT (void)
{
	Error_state_t Error_State=  Send_Massage((u8 *)"ALERT");
			while (Error_State == false )
			{
				 Error_State=  Send_Massage((u8 *)"ALERT");
			}
}
