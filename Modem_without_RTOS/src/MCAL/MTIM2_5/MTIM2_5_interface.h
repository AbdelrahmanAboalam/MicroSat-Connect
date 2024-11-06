/*
Author		: Abdelrahman Ahmed Aboalam
date		: 18/4/2024
version		: 1.2.0
description : MTIM2_5_interface.h -> function prototypes
peri		: for user in MCAL
*/
#ifndef MTIM2_5_MTIM2_5_INTERFACE_H_
#define MTIM2_5_MTIM2_5_INTERFACE_H_

/*********************************************/
/*********************************************/
/******************************	user defined MACROS		******************************/


/******************************	user defined DATA TYPES		******************************/
/***************	TIM2_5 select timer***************/
typedef enum{
 MTIM_2=2	,
 MTIM_3		,
 MTIM_4		,
 MTIM_5
}MTIMx_NUMBER_t;
/***************	TIM2_5 select PWM Channel NUMBER ****************/
typedef enum{
	MTIM2_5_ch1,
	MTIM2_5_ch2,
	MTIM2_5_ch3,
	MTIM2_5_ch4,
}MTIM2_5_PWM_channel_num;
/*********** ICU polarity mode *******************/
typedef enum{
	MTIM_RisingEdge,
	MTIM_FallingEdge,
	MTIM_AnyChange
}MTIM2_5_polarity;

/************************************************/
/*********************************************/

/***************	TIM2_5 FUNCTIONS prototypes	***************/
/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidInitialize											 */
/* @Brief 	  :->		@ used to initialize selected timer(2:5) as GP timer	 		 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ timer count mode must be PreConfiged							 */
/*****************************************************************************************/
void TIM2_5_voidInitialize(MTIMx_NUMBER_t Copy_udtTimerNumber);
/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5TIM2_5_voidTimerStart									 */
/* @Brief 	  :->		@ used to Start count in selected timer(2:5) as GP timer	 	 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ timer count mode must be initialized 							 */
/*****************************************************************************************/
void TIM2_5_voidTimerStart(MTIMx_NUMBER_t Copy_udtTimerNumber);
/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidTimerStop											 */
/* @Brief 	  :->		@ used to Stop count in selected timer(2:5) as GP timer	 		 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ timer count mode must be initialized 							 */
/*****************************************************************************************/
void TIM2_5_voidTimerStop(MTIMx_NUMBER_t Copy_udtTimerNumber);
/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidEnableInterrupt									 */
/* @Brief 	  :->		@ used to enable timer mode interrupt					 		 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ timer count mode must be initialized 							 */
/*****************************************************************************************/
void TIM2_5_voidEnableInterrupt(MTIMx_NUMBER_t Copy_udtTimerNumber);
/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidDisableInterrupt									 */
/* @Brief 	  :->		@ used to Disable timer mode interrupt					 		 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ timer count mode must be initialized 							 */
/*****************************************************************************************/
void TIM2_5_voidDisableInterrupt(MTIMx_NUMBER_t Copy_udtTimerNumber);
/*********************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidSetBusyWait										 	 */
/* @Brief 	  :->		@ used to set timer delay using pooling method			 		 	 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 	 */
/*						@ Copy_u32TickNum: the corresponding ticktime representing delay time*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		  	 */
/*						@ timer must be enabled with RCC								 	 */
/*						@ timer count mode must be initialized 							 	 */
/*********************************************************************************************/
void TIM2_5_voidSetBusyWait(MTIMx_NUMBER_t Copy_udtTimerNumber,u32 Copy_u16TickNum);
/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidPWM_Init											 */
/* @Brief 	  :->		@ used to initialize selected timer(2:5) as PWM source	 		 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/*						@ Copy_udtPWMchannel: Channel that generates the PWM signal		 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ PWM preScaler must be PreConfiged in config file				 */
/*****************************************************************************************/
void TIM2_5_voidPWM_Init(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtPWMchannel);
/*********************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidSetPWM													 */
/* @Brief 	  :->		@ used to SET PWM duty cycle selected timer(2:5) as PWM source	 	 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer					 */
/*						@ Copy_udtPWMchannel: Channel that generates the PWM signal		 	 */
/*						@ Copy_u16Frequency: PWM frequancy								 	 */
/*						@ Copy_DutyCycle: signal duty cycle 							 	 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 			 */
/*						@ timer must be enabled with RCC									 */
/*						@ timer must be initialized as PWM									 */
/*						@ PWM preScaler must be PreConfiged in config file					 */
/*						@ the GPIO pin corresponding to the cahannel must be set as alt-func */
/*********************************************************************************************/
void TIM2_5_voidSetPWM(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtPWMchannel,u16 Copy_u16Frequency,u16 Copy_DutyCycle);
/********************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidICU_init											 	*/
/* @Brief 	  :->		@ used to initialize selected timer(2:5) as ICU source	 		 	*/
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 	*/
/*						@ Copy_udtICUchannel: Channel that captures the Input value		 	*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 	*/
/*						@ timer must be enabled with RCC								 	*/
/*						@ ICU preScaler must be PreConfiged in config file				  	*/
/*						@ the GPIO pin corresponding to the cahannel must be set as alt-func*/
/********************************************************************************************/
void TIM2_5_voidICU_init(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel);
/********************************************************************************************/
/* @Name  	  :->		@ TIM2_5_u32ReturnICUvalue										 	*/
/* @Brief 	  :->		@ used to return the capture value in the CCRx register				*/
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 	*/
/*						@ Copy_udtICUchannel: Channel that captures the Input value		 	*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 	*/
/*						@ timer must be enabled with RCC								 	*/
/*						@ Timer must be initialized as icu								  	*/
/*						@ the GPIO pin corresponding to the cahannel must be set as alt-func*/
/********************************************************************************************/
u32 TIM2_5_u32ReturnICUvalue(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel);
/********************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidEnable_ICU_Interrupt								 	*/
/* @Brief 	  :->		@ used to enable ICU interrupt on timer(2:5) 						*/
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 	*/
/*						@ Copy_udtICUchannel: Channel that captures the Input value		 	*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 	*/
/*						@ timer must be enabled with RCC								 	*/
/*						@ Timer must be initialized as icu								  	*/
/*						@ the GPIO pin corresponding to the cahannel must be set as alt-func*/
/********************************************************************************************/
void TIM2_5_voidEnable_ICU_Interrupt(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel);
/********************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidDisable_ICU_Interrupt								 	*/
/* @Brief 	  :->		@ used to disable ICU interrupt on timer(2:5) 						*/
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 	*/
/*						@ Copy_udtICUchannel: Channel that captures the Input value		 	*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 	*/
/*						@ timer must be enabled with RCC								 	*/
/*						@ Timer must be initialized as icu								  	*/
/*						@ the GPIO pin corresponding to the cahannel must be set as alt-func*/
/********************************************************************************************/
void TIM2_5_voidDisable_ICU_Interrupt(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel);
/********************************************************************************************/
/* @Name  	  :->		@ TIM2_5_ChangICUpolaritiy										 	*/
/* @Brief 	  :->		@ used to change ICU sense polarity during runtime					*/
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 	*/
/*						@ Copy_udtICUchannel: Channel that captures the Input value		 	*/
/*						@ Copy_udtPolarity: sense polarity for the ICU channel				*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 	*/
/*						@ timer must be enabled with RCC								 	*/
/*						@ Timer must be initialized as icu								  	*/
/*						@ the GPIO pin corresponding to the cahannel must be set as alt-func*/
/********************************************************************************************/

void TIM2_5_ChangICUpolaritiy(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel,MTIM2_5_polarity Copy_udtPolarity);

/**************************************************************************************************/
/* @Name  	  :->		@ MTIM3_setCALLBACK												 		  */
/* @Brief 	  :->		@ used to set the ISR for timer	3 interrupts					          */
/* @parameters   :-> 	@ Copy_pvCallBACK: pointer to the function to be excuted at interrupt fire*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 		  */
/*						@ timer must be enabled with RCC								 		  */
/*						@ Timer must interrupt must be enabled							  		  */
/*						@ timer interrupt must be enabled in NVIC								  */
/**************************************************************************************************/
void MTIM3_setCALLBACK(void (*Copy_pvCallBACK)(void));
/**************************************************************************************************/
/* @Name  	  :->		@ MTIM4_setCALLBACK												 		  */
/* @Brief 	  :->		@ used to set the ISR for timer 4 interrupts							  */
/* @parameters   :-> 	@ Copy_pvCallBACK: pointer to the function to be excuted at interrupt fire*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 		  */
/*						@ timer must be enabled with RCC								 		  */
/*						@ Timer must interrupt must be enabled							  		  */
/*						@ timer interrupt must be enabled in NVIC								  */
/**************************************************************************************************/
void MTIM4_setCALLBACK(void (*Copy_pvCallBACK)(void));

/**************************************************************************************************/
/* @Name  	  :->		@ MTIM5_setCALLBACK												 		  */
/* @Brief 	  :->		@ used to set the ISR for timer 5 interrupts						      */
/* @parameters   :-> 	@ Copy_pvCallBACK: pointer to the function to be excuted at interrupt fire*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 		  */
/*						@ timer must be enabled with RCC								 		  */
/*						@ Timer must interrupt must be enabled							  		  */
/*						@ timer interrupt must be enabled in NVIC								  */
/**************************************************************************************************/
void MTIM5_setCALLBACK(void (*Copy_pvCallBACK)(void));

void MTM3_setInterval_Asyncrouns(u32 Copy_u32TickNum , void(* Copy_pvCallBACK)(void));

#endif /* MTIM2_5_MTIM2_5_INTERFACE_H_ */
