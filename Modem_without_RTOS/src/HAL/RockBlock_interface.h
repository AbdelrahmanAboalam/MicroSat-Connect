/*
Author		: Abdelrahman Ahmed Aboalam
date		: 19/4/2024
version		: 1.0.0
description : RockBlock_interface.h -> Functions functions prototypes
peri		: for user in HAL
*/

#ifndef HAL_ROCKBLOCK_INTERFACE_H_
#define HAL_ROCKBLOCK_INTERFACE_H_

/*********************************************/
/*********************************************/

/***************	user defined data types 	***************/


/* Values of Error State*/
typedef enum
{
	 false ,
	 true
}Error_state_t;

/***************	Function Prototypes		***************/

/*****************************************************************************************/
/* @Name  	  :->		@ Buffering_voidData											 */
/* @Brief 	  :->		@ used to Buffer Data from UART DR register	                     */
/* @parameters   :-> 	@ No parameters                                         		 */
/* @PreRequsteis :->	@ UART MUST be initialized								 		 */
/*						@ NVIC Enable interrupt must be used after this function		 */
/*****************************************************************************************/

void Buffering_voidData (void);

/*****************************************************************************************/
/* @Name  	  :->		@ Clear_voidBuffer      										 */
/* @Brief 	  :->		@ used to clear buffer to receive new response 	                 */
/* @parameters   :-> 	@ No parameters                                         		 */
/* @PreRequsteis :->	@ No thing                                                       */
/*****************************************************************************************/

void Clear_voidBuffer(void);

/*****************************************************************************************/
/* @Name  	  :->		@ Clear_voidBuffer      										 */
/* @Brief 	  :->		@ used to clear buffer to receive new response 	                 */
/* @parameters   :-> 	@ No parameters                                         		 */
/* @PreRequsteis :->	@ No thing                                                       */
/*****************************************************************************************/

u8 CheckRecieve();

/*****************************************************************************************/
/* @Name  	  :->		@ Send_Massage      											 */
/* @Brief 	  :->		@ used to send message to Our Modem     	                     */
/* @parameters   :-> 	@ Copy_pu8Message                                         		 */
/* @PreRequsteis :->	@ UART MUST be initialized	                                     */
/*                      @ SYSTICK MUST be initialized                   		 		 */
/*						@ NVIC Enable interrupt must be used after this function		 */
/*****************************************************************************************/

u8 Send_Massage(const u8 *Copy_pu8Message);

/*****************************************************************************************/
/* @Name  	  :->		@ Recive_Massage      											 */
/* @Brief 	  :->		@ used to Receive message to Our Modem     	                     */
/* @parameters   :-> 	@ No parameters                                         		 */
/* @PreRequsteis :->	@ UART MUST be initialized	                                     */
/*                      @ SYSTICK MUST be initialized                   		 		 */
/*						@ NVIC Enable interrupt must be used after this function		 */
/*****************************************************************************************/

u8 *Recive_Massage(void);


#endif /* HAL_ROCKBLOCK_INTERFACE_H_ */
