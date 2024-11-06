/*
Author		: Abdelrahman Ahmed Aboalam
date		: 19/4/2024
version		: 1.0.0
description : RockBlock.c -> Functions impelemntations
peri		: for the developer in HAL only not for the user
*/
/*********************************************/
/*********************************************/

/***************	Standard LIBS include	***************/

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

/***************	RockBlock Files include	***************/
#include "RockBlock_interface.h"
/***************	MCAL Files include	***************/
#include "../MCAL/MUART/MUART_interface.h"
#include "../MCAL/MUART/MUART_register.h"
#include "../MCAL/MUART/MUART_private.h"
#include "../MCAL/MUART/MUART_config.h"
#include "../MCAL/MSTK/MSTK_interface.h"
/*********************************************/
/*********************************************/

/***************	Global VAR	***************/

static u8 Global_u8Counter=0;
static u8 Global_u8Data[50];
Error_state_t Error_Flag= false;


/***************	RockBlock Functions Implementations	***************/

/*****************************************************************************************/
/* @Name  	  :->		@ Buffering_voidData											 */
/* @Brief 	  :->		@ used to Buffer Data from UART DR register	                     */
/* @parameters   :-> 	@ No parameters                                         		 */
/* @PreRequsteis :->	@ UART MUST be initialized								 		 */
/*						@ NVIC Enable interrupt must be used after this function		 */
/*****************************************************************************************/
void Buffering_voidData (void)
{
	Global_u8Data[Global_u8Counter]= MUSART1->DR;
	Global_u8Counter++;
}

/*****************************************************************************************/
/* @Name  	  :->		@ Send_Massage      											 */
/* @Brief 	  :->		@ used to send message to Our Modem     	                     */
/* @parameters   :-> 	@ Copy_pu8Message                                         		 */
/* @PreRequsteis :->	@ UART MUST be initialized	                                     */
/*                      @ SYSTICK MUST be initialized                   		 		 */
/*						@ NVIC Enable interrupt must be used after this function		 */
/*****************************************************************************************/
u8 Send_Massage(const u8 *Copy_pu8Message)
{

	MUSART_voidRecieveAsynchronous();
	MUSART_voidSetCallBack(&Buffering_voidData);
/***************  Sending AT and the right response is --------------> OK  *************/
	MUSART_voidSendString((u8 *) "AT/r/n");
	MSTK_voidDelayMS(200);
	Error_Flag = CheckRecieve();
	Clear_voidBuffer();

	if (Error_Flag==true)
	{
/***************  Sending AT+SBDWT=Massage and the right response is --------------> OK  *************/
		MUSART_voidSendString((u8 *) "AT+SBDWT=");
		MUSART_voidSendString(Copy_pu8Message);
		MUSART_voidSendString((u8 *) "/r/n");
		MSTK_voidDelayMS(300);
		Error_Flag = CheckRecieve();
		if (Error_Flag==true)
		{
			asm("NOP");
		}
		else
		{
			Error_Flag= false;
		}
	}
	else
	{
		Error_Flag= false;
	}
	Clear_voidBuffer();
	return Error_Flag;

}

/*****************************************************************************************/
/* @Name  	  :->		@ Clear_voidBuffer      										 */
/* @Brief 	  :->		@ used to clear buffer to receive new response 	                 */
/* @parameters   :-> 	@ No parameters                                         		 */
/* @PreRequsteis :->	@ No thing                                                       */
/*****************************************************************************************/

void Clear_voidBuffer(void)
{
	for(s8 L_u8Iterator = Global_u8Counter-1 ; L_u8Iterator>=0;L_u8Iterator--)
	{
		Global_u8Data[L_u8Iterator]=0;
	}
	Global_u8Counter=0;
}

/*****************************************************************************************/
/* @Name  	  :->		@ Recive_Massage      											 */
/* @Brief 	  :->		@ used to Receive message to Our Modem     	                     */
/* @parameters   :-> 	@ No parameters                                         		 */
/* @PreRequsteis :->	@ UART MUST be initialized	                                     */
/*                      @ SYSTICK MUST be initialized                   		 		 */
/*						@ NVIC Enable interrupt must be used after this function		 */
/*****************************************************************************************/

u8 *Recive_Massage(void)
{
	static u8 Message_Buffer[50];
	for(u8 L_u8Iterator = 0 ; L_u8Iterator<50;L_u8Iterator++)
	{
		Message_Buffer[L_u8Iterator]=0;
	}
	u8 *Message=NULL;
	MUSART_voidRecieveAsynchronous();
	MUSART_voidSetCallBack(&Buffering_voidData);

/***************  Sending AT and the right response is --------------> OK  *************/

	MUSART_voidSendString((u8 *) "AT/r/n");
	MSTK_voidDelayMS(100);
	Error_Flag = CheckRecieve();
	Clear_voidBuffer();

	if (Error_Flag==true)
		{

/***************  Sending AT&K0 and the right response is --------------> OK  *************/
			MUSART_voidSendString((u8 *) "AT&K0\r\n");
			MSTK_voidDelayMS(100);
			Error_Flag = CheckRecieve();
			Clear_voidBuffer();

			if (Error_Flag==true)
			{

/*****  Sending AT+SBDIX and the right response is --------------> +SBDIX: 0, 1, 1, 1, 6, 8 and 0 zero is right ressponse  ******/
				MUSART_voidSendString((u8 *) "AT+SBDIX\r\n");
				MSTK_voidDelayMS(300);
				if (Global_u8Data[8]=='0')
				{

					Clear_voidBuffer();
/*****  Sending AT+SBDRT and the right response is --------------> +SBDRT: Message OK  ******/
					MUSART_voidSendString((u8 *) "AT+SBDRT\r\n");
					MSTK_voidDelayMS(500);
					if (Global_u8Data[1]=='S')
					{
						u8 Message_u8Itirator=0;
						for(u8 L_u8Iterator =8 ; L_u8Iterator<Global_u8Counter;L_u8Iterator++ )
						{
							Message_Buffer[Message_u8Itirator]=Global_u8Data[L_u8Iterator];
							Message_u8Itirator++;

						}
						Message=Message_Buffer;
					}
					else
					{
						Error_Flag =false;
					}
					Clear_voidBuffer();
				}
			}
}
	return Message;
}

/*****************************************************************************************/
/* @Name  	  :->		@ CheckRecieve          										 */
/* @Brief 	  :->		@ used to chek if response is OK                                 */
/* @parameters   :-> 	@ No parameters                                         		 */
/* @PreRequsteis :->	@ No thing                                                       */
/*****************************************************************************************/
u8 CheckRecieve()
{

	if (Global_u8Data[0]=='O'&&Global_u8Data[1]=='K')
			{
			Error_Flag= true;
			}
			else
			{
				Error_Flag= false;
			}
	return Error_Flag;
}

