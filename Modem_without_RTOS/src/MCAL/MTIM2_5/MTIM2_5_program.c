/*
Author		: Abdelrahman Ahmed Aboalam
date		: 18/4/2024
version		: 1.2.0
description : MTIM2_5_program.c -> Function impel
peri		: for the developer in MCAL only not for the user
*/
/**********************************************/
/************************************************/

/***************	TIM2_5 Files include	***************/
/*Standard LIBS*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
/*TIM 2_5 files*/
#include "MTIM2_5_interface.h"
#include "MTIM2_5_private.h"
#include "MTIM2_5_config.h"
#include "MTIM2_5_register.h"


/******** global variables *******/
static void(*MTIM3_pvCallBack)(void)=NULL;
static void(*MTIM4_pvCallBack)(void)=NULL;
static void(*MTIM5_pvCallBack)(void)=NULL;
/*********************************************/
/*********************************************/

/***************	TIM2_5 Functions Implementations	***************/

/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidInitialize											 */
/* @Brief 	  :->		@ used to initialize selected timer(2:5) as GP timer	 		 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ timer count mode must be PreConfiged							 */
/*****************************************************************************************/
void TIM2_5_voidInitialize(MTIMx_NUMBER_t Copy_udtTimerNumber){
	switch (Copy_udtTimerNumber){
				case MTIM_2:
								/*no clock devision*/
							  CLR_BIT(MTIM2->CR1,CR1_CKD9);
							  CLR_BIT(MTIM2->CR1,CR1_CKD8);

							  /*enable AUTO RELOAD PRELOAD*/
							  SET_BIT(MTIM2->CR1,CR1_ARPE);
							  /*Set PreScaler*/
							  	 MTIM2->PSC=0x10;
							  /*set timer as edge aligned*/
							  	CLR_BIT(MTIM2->CR1,CR1_CMS6);
							  	CLR_BIT(MTIM2->CR1,CR1_CMS5);
							  /*Counter direction*/
							#if MTIM2_CMODE == MTIM_CDOWN
							  SET_BIT(MTIM2->CR1,CR1_DIR);
							#elif MTIM2_CMODE == MTIM_CUP
							  CLR_BIT(MTIM2->CR1,CR1_DIR);
							  #endif


							break;

				case MTIM_3 :
					/*no clock devision*/
								  CLR_BIT(MTIM3->CR1,CR1_CKD9);
								  CLR_BIT(MTIM3->CR1,CR1_CKD8);

								  /*enable AUTO RELOAD PRELOAD*/
								  SET_BIT(MTIM3->CR1,CR1_ARPE);
								  /*Set PreScaler*/
								  	 MTIM3->PSC=122;
								  /*set timer as edge aligned*/
								  	CLR_BIT(MTIM3->CR1,CR1_CMS6);
								  	CLR_BIT(MTIM3->CR1,CR1_CMS5);
								  /*Counter direction*/
								#if MTIM3_CMODE == MTIM_CDOWN
								  SET_BIT(MTIM3->CR1,CR1_DIR);
								#elif MTIM3_CMODE == MTIM_CUP
								  CLR_BIT(MTIM3->CR1,CR1_DIR);
								  #endif
								  	 break;
				case MTIM_4:
					/*no clock devision*/
								  CLR_BIT(MTIM4->CR1,CR1_CKD9);
								  CLR_BIT(MTIM4->CR1,CR1_CKD8);

								  /*enable AUTO RELOAD PRELOAD*/
								  SET_BIT(MTIM4->CR1,CR1_ARPE);
								  /*Set PreScaler*/
								  	 MTIM4->PSC=0x10;
								  /*set timer as edge aligned*/
								  	CLR_BIT(MTIM4->CR1,CR1_CMS6);
								  	CLR_BIT(MTIM4->CR1,CR1_CMS5);
								  /*Counter direction*/
								#if MTIM2_CMODE == MTIM_CDOWN
								  SET_BIT(MTIM4->CR1,CR1_DIR);
								#elif MTIM4_CMODE == MTIM_CUP
								  CLR_BIT(MTIM4->CR1,CR1_DIR);
								  #endif
								  break;
				case MTIM_5:
					/*no clock devision*/
				  CLR_BIT(MTIM5->CR1,CR1_CKD9);
				  CLR_BIT(MTIM5->CR1,CR1_CKD8);

				  /*enable AUTO RELOAD PRELOAD*/
				  SET_BIT(MTIM5->CR1,CR1_ARPE);
				  /*Set PreScaler*/
				  	 MTIM5->PSC=0x10;
				  /*set timer as edge aligned*/
				  	CLR_BIT(MTIM5->CR1,CR1_CMS6);
				  	CLR_BIT(MTIM5->CR1,CR1_CMS5);
				  /*Counter direction*/
				#if MTIM5_CMODE == MTIM_CDOWN
				  SET_BIT(MTIM5->CR1,CR1_DIR);
				#elif MTIM5_CMODE == MTIM_CUP
				  CLR_BIT(MTIM5->CR1,CR1_DIR);
				  #endif
					break;
					}
}
/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5TIM2_5_voidTimerStart									 */
/* @Brief 	  :->		@ used to Start count in selected timer(2:5) as GP timer	 	 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ timer count mode must be initialized 							 */
/*****************************************************************************************/
void TIM2_5_voidTimerStart(MTIMx_NUMBER_t Copy_udtTimerNumber){
	switch (Copy_udtTimerNumber){
			case MTIM_2:
							SET_BIT(MTIM2->CR1,CR1_CEN);
							break;

			case MTIM_3 :
							SET_BIT(MTIM3->CR1,CR1_CEN);
							break;

			case MTIM_4:
							SET_BIT(MTIM4->CR1,CR1_CEN);
							break;

			case MTIM_5:
							SET_BIT(MTIM5->CR1,CR1_CEN);
							break;
				}

}
/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidTimerStop											 */
/* @Brief 	  :->		@ used to Stop count in selected timer(2:5) as GP timer	 		 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ timer count mode must be initialized 							 */
/*****************************************************************************************/
void TIM2_5_voidTimerStop(MTIMx_NUMBER_t Copy_udtTimerNumber){
	switch (Copy_udtTimerNumber){
			case MTIM_2: CLR_BIT(MTIM2->CR1,CR1_CEN);
						break;

			case MTIM_3 : CLR_BIT(MTIM3->CR1,CR1_CEN);
						break;

			case MTIM_4 : CLR_BIT(MTIM4->CR1,CR1_CEN);
						break;

			case MTIM_5 : CLR_BIT(MTIM5->CR1,CR1_CEN);
						break;
				}
}



/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidEnableInterrupt									 */
/* @Brief 	  :->		@ used to enable timer mode interrupt					 		 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ timer count mode must be initialized 							 */
/*****************************************************************************************/
void TIM2_5_voidEnableInterrupt(MTIMx_NUMBER_t Copy_udtTimerNumber){
	switch (Copy_udtTimerNumber){
			case MTIM_2: SET_BIT(MTIM2->CR1,DIER_TIE);
						break;

			case MTIM_3 : SET_BIT(MTIM3->CR1,DIER_TIE);
						break;
			case MTIM_4 : SET_BIT(MTIM4->CR1,DIER_TIE);
						break;

			case MTIM_5 : SET_BIT(MTIM5->CR1,DIER_TIE);
						break;
				}
}
/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidDisableInterrupt									 */
/* @Brief 	  :->		@ used to Disable timer mode interrupt					 		 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ timer count mode must be initialized 							 */
/*****************************************************************************************/
void TIM2_5_voidDisableInterrupt(MTIMx_NUMBER_t Copy_udtTimerNumber){
	switch (Copy_udtTimerNumber){
			case MTIM_2: CLR_BIT(MTIM2->CR1,DIER_TIE);
						break;

			case MTIM_3 : CLR_BIT(MTIM3->CR1,DIER_TIE);
						break;

			case MTIM_4 : CLR_BIT(MTIM4->CR1,DIER_TIE);
						break;

			case MTIM_5 : CLR_BIT(MTIM5->CR1,DIER_TIE);
						break;
				}
}
/*********************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidSetBusyWait										 	 */
/* @Brief 	  :->		@ used to set timer delay using pooling method			 		 	 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 	 */
/*						@ Copy_u32TickNum: the corresponding ticktime representing delay time*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		  	 */
/*						@ timer must be enabled with RCC								 	 */
/*						@ timer count mode must be initialized 							 	 */
/*********************************************************************************************/
void TIM2_5_voidSetBusyWait(MTIMx_NUMBER_t Copy_udtTimerNumber,u32 Copy_u32TickNum){
	switch (Copy_udtTimerNumber){
	case MTIM_2:
					/*clear timer value */
					MTIM2->CNT=0x00000000;
					/*set PreLoad value */
					MTIM2->ARR=Copy_u32TickNum;
					/*start timer*/
					SET_BIT(MTIM2->CR1,CR1_CEN);
					/*wait for timer*/
					while(GET_BIT(MTIM2->SR,SR_UIF)!=1);
					/*stop timer*/
					CLR_BIT(MTIM2->CR1,CR1_CEN);
					break;
	case MTIM_3: /*clear timer value */
		/*clear timer value */
			MTIM3->CNT=0x00000000;
			/*set PreLoad value */
			MTIM3->ARR=Copy_u32TickNum;
			/*start timer*/
			SET_BIT(MTIM3->CR1,CR1_CEN);
			/*wait for timer*/
			while(GET_BIT(MTIM3->SR,SR_UIF)!=1);
			/*stop timer*/
			CLR_BIT(MTIM3->CR1,CR1_CEN);
			break;
	case MTIM_4: /*clear timer value */
		/*clear timer value */
			MTIM4->CNT=0x00000000;
			/*set PreLoad value */
			MTIM4->ARR=Copy_u32TickNum;
			/*start timer*/
			SET_BIT(MTIM4->CR1,CR1_CEN);
			/*wait for timer*/
			while(GET_BIT(MTIM4->SR,SR_UIF)!=1);
			/*stop timer*/
			CLR_BIT(MTIM4->CR1,CR1_CEN);
			break;
	case MTIM_5: /*clear timer value */
		/*clear timer value */
		MTIM5->CNT=0x00000000;
		/*set PreLoad value */
		MTIM5->ARR=Copy_u32TickNum;
		/*start timer*/
		SET_BIT(MTIM5->CR1,CR1_CEN);
		/*wait for timer*/
		while(GET_BIT(MTIM5->SR,SR_UIF)!=1);
		/*stop timer*/
		CLR_BIT(MTIM5->CR1,CR1_CEN);
		break;
	}
	}
/*****************************************************************************************/
/* @Name  	  :->		@ TIM2_5_voidPWM_Init											 */
/* @Brief 	  :->		@ used to initialize selected timer(2:5) as PWM source	 		 */
/* @parameters   :-> 	@ Copy_udtTimerNumber: the number of the used timer				 */
/*						@ Copy_udtPWMchannel: Channel that generates the PWM signal		 */
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 */
/*						@ timer must be enabled with RCC								 */
/*						@ PWM preScaler must be PreConfiged in config file				 */
/*****************************************************************************************/
void TIM2_5_voidPWM_Init(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtPWMchannel){
		switch (Copy_udtTimerNumber){
		case MTIM_3:
			switch(Copy_udtPWMchannel){
			case MTIM2_5_ch1:
				/*set the preScaler value in the preScaler register*/
				MTIM3->PSC=TIM3_PWM_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM3->CCMR1,CCRM1_OC1M_6);
				SET_BIT(MTIM3->CCMR1,CCRM1_OC1M_5);
				CLR_BIT(MTIM3->CCMR1,CCRM1_OC1M_4);
				/*enable output compare auto reload register*/
				SET_BIT(MTIM3->CCMR1,CCRM1_OC1PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC1E);
				 break;
			case MTIM2_5_ch2:
				/*set the preScaler value in the preScaler register*/
				MTIM3->PSC=TIM3_PWM_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM3->CCMR1,CCRM1_OC2M_14);
				SET_BIT(MTIM3->CCMR1,CCRM1_OC2M_13);
				CLR_BIT(MTIM3->CCMR1,CCRM1_OC2M_12);
				/*enable output compare auto reload register*/
				SET_BIT(MTIM3->CCMR1,CCRM1_OC2PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC2E);
		    	  break;
			case MTIM2_5_ch3:
				/*set the preScaler value in the preScaler register*/
				MTIM3->PSC=TIM3_PWM_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM3->CCMR2,CCRM2_OC3M_6);
				SET_BIT(MTIM3->CCMR2,CCRM2_OC3M_5);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC3M_4);
				/*enable output compare auto reload register*/
				SET_BIT(MTIM3->CCMR2,CCRM2_OC3PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC3E);
				break;
			case MTIM2_5_ch4:
				/*set the preScaler value in the preScaler register*/
				MTIM3->PSC=TIM3_PWM_PRESCALER;
				/*select the pwm mode*/
				SET_BIT(MTIM3->CCMR2,CCRM2_OC4M_14);
				SET_BIT(MTIM3->CCMR2,CCRM2_OC4M_13);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC4M_12);
				/*enable output compare auto reload register*/
				SET_BIT(MTIM3->CCMR2,CCRM2_OC4PE);
				/*enable out put on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC4E);
				 break;
			}
			break;
		case MTIM_4:
			switch(Copy_udtPWMchannel){
				case MTIM2_5_ch1:
					/*set the preScaler value in the preScaler register*/
					MTIM4->PSC=TIM4_PWM_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM4->CCMR1,CCRM1_OC1M_6);
					SET_BIT(MTIM4->CCMR1,CCRM1_OC1M_5);
					CLR_BIT(MTIM4->CCMR1,CCRM1_OC1M_4);
					/*enable output compare auto reload register*/
					SET_BIT(MTIM4->CCMR1,CCRM1_OC1PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC1E);
					 break;
				case MTIM2_5_ch2:
					/*set the preScaler value in the preScaler register*/
					MTIM4->PSC=TIM4_PWM_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM4->CCMR1,CCRM1_OC2M_14);
					SET_BIT(MTIM4->CCMR1,CCRM1_OC2M_13);
					CLR_BIT(MTIM4->CCMR1,CCRM1_OC2M_12);
					/*enable output compare auto reload register*/
					SET_BIT(MTIM4->CCMR1,CCRM1_OC2PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC2E);
			    	  break;
				case MTIM2_5_ch3:
					/*set the preScaler value in the preScaler register*/
					MTIM4->PSC=TIM4_PWM_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM4->CCMR2,CCRM2_OC3M_6);
					SET_BIT(MTIM4->CCMR2,CCRM2_OC3M_5);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC3M_4);
					/*enable output compare auto reload register*/
					SET_BIT(MTIM4->CCMR2,CCRM2_OC3PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC3E);
					break;
				case MTIM2_5_ch4:
					/*set the preScaler value in the preScaler register*/
					MTIM4->PSC=TIM4_PWM_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM4->CCMR2,CCRM2_OC4M_14);
					SET_BIT(MTIM4->CCMR2,CCRM2_OC4M_13);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC4M_12);
					/*enable output compare auto reload register*/
					SET_BIT(MTIM4->CCMR2,CCRM2_OC4PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC4E);
					 break;
				}
				break;
		case MTIM_5:
			switch(Copy_udtPWMchannel){
				case MTIM2_5_ch1:
					/*set the preScaler value in the preScaler register*/
					MTIM5->PSC=TIM5_PWM_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM5->CCMR1,CCRM1_OC1M_6);
					SET_BIT(MTIM5->CCMR1,CCRM1_OC1M_5);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC1M_4);
					/*enable output compare auto reload register*/
					SET_BIT(MTIM5->CCMR1,CCRM1_OC1PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC1E);
					 break;
				case MTIM2_5_ch2:
					/*set the preScaler value in the preScaler register*/
					MTIM5->PSC=TIM5_PWM_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM5->CCMR1,CCRM1_OC2M_14);
					SET_BIT(MTIM5->CCMR1,CCRM1_OC2M_13);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC2M_12);
					/*enable output compare auto reload register*/
					SET_BIT(MTIM5->CCMR1,CCRM1_OC2PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC2E);
			    	  break;
				case MTIM2_5_ch3:
					/*set the preScaler value in the preScaler register*/
					MTIM5->PSC=TIM5_PWM_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM5->CCMR2,CCRM2_OC3M_6);
					SET_BIT(MTIM5->CCMR2,CCRM2_OC3M_5);
					CLR_BIT(MTIM5->CCMR2,CCRM2_OC3M_4);
					/*enable output compare auto reload register*/
					SET_BIT(MTIM5->CCMR2,CCRM2_OC3PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC3E);
					break;
				case MTIM2_5_ch4:
					/*set the preScaler value in the preScaler register*/
					MTIM5->PSC=TIM5_PWM_PRESCALER;
					/*select the pwm mode*/
					SET_BIT(MTIM5->CCMR2,CCRM2_OC4M_14);
					SET_BIT(MTIM5->CCMR2,CCRM2_OC4M_13);
					CLR_BIT(MTIM5->CCMR2,CCRM2_OC4M_12);
					/*enable output compare auto reload register*/
					SET_BIT(MTIM5->CCMR2,CCRM2_OC4PE);
					/*enable out put on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC4E);
					 break;
				}
				break;
	}
}


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
void TIM2_5_voidSetPWM(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtPWMchannel,u16 Copy_u16Frequency,u16 Copy_DutyCycle){
switch(Copy_udtTimerNumber){
case MTIM_3:
			switch(Copy_udtPWMchannel){
			case MTIM2_5_ch1:
							/*set the frequency of the PWM*/
							MTIM3->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM3->CCR1=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM3->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch2:
							/*set the frequency of the PWM*/
							MTIM3->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM3->CCR2=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM3->CR1,CR1_CEN);
								break;
			case MTIM2_5_ch3:
							/*set the frequency of the PWM*/
							MTIM3->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM3->CCR3=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM3->CR1,CR1_CEN);
							break;
						case MTIM2_5_ch4:
							/*set the frequency of the PWM*/
							MTIM3->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM3->CCR4=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM3->CR1,CR1_CEN);
							break;
						}
					break;
case MTIM_4:
			switch(Copy_udtPWMchannel){
			case MTIM2_5_ch1:
							/*set the frequency of the PWM*/
							MTIM4->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM4->CCR1=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM4->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch2:
							/*set the frequency of the PWM*/
							MTIM4->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM4->CCR2=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM4->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch3:
							/*set the frequency of the PWM*/
							MTIM4->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM4->CCR3=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM4->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch4:
							/*set the frequency of the PWM*/
							MTIM4->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM4->CCR4=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM4->CR1,CR1_CEN);
							break;
					}
					break;
case MTIM_5:
			switch(Copy_udtPWMchannel){
			case MTIM2_5_ch1:
							/*set the frequency of the PWM*/
							MTIM5->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM5->CCR1=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM5->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch2:
							/*set the frequency of the PWM*/
							MTIM5->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM5->CCR2=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM5->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch3:
							/*set the frequency of the PWM*/
							MTIM5->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM5->CCR3=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM5->CR1,CR1_CEN);
							break;
			case MTIM2_5_ch4:
							/*set the frequency of the PWM*/
							MTIM5->ARR=Copy_u16Frequency;
							/*set the duty cycle of the PWM*/
							MTIM5->CCR4=Copy_DutyCycle;
							/*enable timer to start the PWM*/
							SET_BIT(MTIM5->CR1,CR1_CEN);
							break;
					}
					break;
	}
}

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
void TIM2_5_voidICU_init(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel){
	switch (Copy_udtTimerNumber){
	case MTIM_3:
		switch(Copy_udtICUchannel){
		case MTIM2_5_ch1:
			/*Select ICU*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_CC1S1);
			SET_BIT(MTIM3->CCMR1,CCRM1_CC1S0);
			/*set the ICU FILTER value=0*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC1M_7);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC1M_6);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC1M_5);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC1M_4);
			/*set ICU PRESCALER= no preScaler*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_IC1PSC3);
			CLR_BIT(MTIM3->CCMR1,CCRM1_IC1PSC2);
			/*select the rising edge sense control*/
			SET_BIT(MTIM3->CCER,CCER_CC1P);
			SET_BIT(MTIM3->CCER,CCER_CC1NP);
			/*enable capture on the corresponding PIN*/
			SET_BIT(MTIM3->CCER,CCER_CC1E);

			/* Set prescaler  */
			MTIM3->PSC = TIM3_ICU_PRESCALER;
			/* Set Preload */
			MTIM3->ARR=TIM3_ICU_ARRval;

			/*enable interrupt*/
			SET_BIT(MTIM3->DIER,DIER_CC1IE);
			/*enable timer to start ICU*/
			SET_BIT(MTIM3->CR1,CR1_CEN);
			break;
		case MTIM2_5_ch2:
			/*Select ICU*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_CC2S1);
			SET_BIT(MTIM3->CCMR1,CCRM1_CC2S0);
			/*set the ICU FILTER value=0*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC2M_15);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC2M_14);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC2M_13);
			CLR_BIT(MTIM3->CCMR1,CCRM1_OC2M_12);
			/*set ICU PRESCALER= no preScaler*/
			CLR_BIT(MTIM3->CCMR1,CCRM1_IC2PSC10);
			CLR_BIT(MTIM3->CCMR1,CCRM1_IC2PSC11);
			/*select the rising edge sense control*/
			SET_BIT(MTIM3->CCER,CCER_CC2NP);
			SET_BIT(MTIM3->CCER,CCER_CC2P);
			/*enable capture on the corresponding PIN*/
			SET_BIT(MTIM3->CCER,CCER_CC2E);
			/* Set prescaler  */
			MTIM3->PSC = TIM3_ICU_PRESCALER;
			/* Set Preload */
			MTIM3->ARR=TIM3_ICU_ARRval;
			/*enable interrupt*/
			SET_BIT(MTIM3->DIER,DIER_CC2IE);
			/*enable timer to start ICU*/
			SET_BIT(MTIM3->CR1,CR1_CEN);
			 break;
		case MTIM2_5_ch3:
				/*Select ICU*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_CC3S1);
				SET_BIT(MTIM3->CCMR2,CCRM2_CC3S0);
				/*set the ICU FILTER value=0*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC3M_7);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC3M_6);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC3M_5);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC3M_4);
				/*set ICU PRESCALER= no preScaler*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_IC3PSC3);
				CLR_BIT(MTIM3->CCMR2,CCRM2_IC3PSC2);
				/*select the rising edge sense control*/
				SET_BIT(MTIM3->CCER,CCER_CC3NP);
				SET_BIT(MTIM3->CCER,CCER_CC3P);
				/*enable capture on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC3E);
				/* Set prescaler  */
				MTIM3->PSC = TIM3_ICU_PRESCALER;
				/* Set Preload */
				MTIM3->ARR=TIM3_ICU_ARRval;
				/*enable interrupt*/
				SET_BIT(MTIM3->DIER,DIER_CC3IE);
				/*enable timer to start ICU*/
				SET_BIT(MTIM3->CR1,CR1_CEN);
				 break;
			case MTIM2_5_ch4:
				/*Select ICU*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_CC4S1);
				SET_BIT(MTIM3->CCMR2,CCRM2_CC4S0);
				/*set the ICU FILTER value=0*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC4M_15);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC4M_14);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC4M_13);
				CLR_BIT(MTIM3->CCMR2,CCRM2_OC4M_12);
				/*set ICU PRESCALER= no preScaler*/
				CLR_BIT(MTIM3->CCMR2,CCRM2_IC4PSC10);
				CLR_BIT(MTIM3->CCMR2,CCRM2_IC4PSC11);
				/*select the rising edge sense control*/
				SET_BIT(MTIM3->CCER,CCER_CC4NP);
				SET_BIT(MTIM3->CCER,CCER_CC4P);
				/*enable capture on the corresponding PIN*/
				SET_BIT(MTIM3->CCER,CCER_CC4E);
				/* Set prescaler  */
				MTIM3->PSC = TIM3_ICU_PRESCALER;
				/* Set Preload */
				MTIM3->ARR=TIM3_ICU_ARRval;
				/*enable interrupt*/
				SET_BIT(MTIM3->DIER,DIER_CC4IE);
				/*enable timer to start ICU*/
				SET_BIT(MTIM3->CR1,CR1_CEN);
				 break;
}
		break;
		case MTIM_4:
			switch(Copy_udtICUchannel){
			case MTIM2_5_ch1:
				/*Select ICU*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_CC1S1);
				SET_BIT(MTIM4->CCMR1,CCRM1_CC1S0);
				/*set the ICU FILTER value=0*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC1M_7);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC1M_6);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC1M_5);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC1M_4);
				/*set ICU PRESCALER= no preScaler*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_IC1PSC3);
				CLR_BIT(MTIM4->CCMR1,CCRM1_IC1PSC2);
				/*select the rising edge sense control*/
				SET_BIT(MTIM4->CCER,CCER_CC1P);
				SET_BIT(MTIM4->CCER,CCER_CC1NP);
				/*enable capture on the corresponding PIN*/
				SET_BIT(MTIM4->CCER,CCER_CC1E);
				/* Set prescaler  */
				MTIM4->PSC = TIM4_ICU_PRESCALER;
				/* Set Preload */
				MTIM4->ARR=TIM4_ICU_ARRval;
				/*enable interrupt*/
				SET_BIT(MTIM4->DIER,DIER_CC1IE);
				/*enable timer to start ICU*/
				SET_BIT(MTIM4->CR1,CR1_CEN);
				 break;
			case MTIM2_5_ch2:
				/*Select ICU*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_CC2S1);
				SET_BIT(MTIM4->CCMR1,CCRM1_CC2S0);
				/*set the ICU FILTER value=0*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC2M_15);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC2M_14);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC2M_13);
				CLR_BIT(MTIM4->CCMR1,CCRM1_OC2M_12);
				/*set ICU PRESCALER= no preScaler*/
				CLR_BIT(MTIM4->CCMR1,CCRM1_IC2PSC10);
				CLR_BIT(MTIM4->CCMR1,CCRM1_IC2PSC11);
				/*select the rising edge sense control*/
				SET_BIT(MTIM4->CCER,CCER_CC2NP);
				SET_BIT(MTIM4->CCER,CCER_CC2P);
				/*enable capture on the corresponding PIN*/
				SET_BIT(MTIM4->CCER,CCER_CC2E);
				/* Set prescaler  */
				MTIM4->PSC = TIM4_ICU_PRESCALER;
				/* Set Preload */
				MTIM4->ARR=TIM4_ICU_ARRval;
				/*enable interrupt*/
				SET_BIT(MTIM4->DIER,DIER_CC2IE);
				/*enable timer to start ICU*/
				SET_BIT(MTIM4->CR1,CR1_CEN);
				 break;
			case MTIM2_5_ch3:
					/*Select ICU*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_CC3S1);
					SET_BIT(MTIM4->CCMR2,CCRM2_CC3S0);
					/*set the ICU FILTER value=0*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC3M_7);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC3M_6);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC3M_5);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC3M_4);
					/*set ICU PRESCALER= no preScaler*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_IC3PSC3);
					CLR_BIT(MTIM4->CCMR2,CCRM2_IC3PSC2);
					/*select the rising edge sense control*/
					SET_BIT(MTIM4->CCER,CCER_CC3NP);
					SET_BIT(MTIM4->CCER,CCER_CC3P);
					/*enable capture on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC3E);
					/* Set prescaler  */
					MTIM4->PSC = TIM4_ICU_PRESCALER;
					/* Set Preload */
					MTIM4->ARR=TIM4_ICU_ARRval;
					/*enable interrupt*/
					SET_BIT(MTIM4->DIER,DIER_CC3IE);
					/*enable timer to start ICU*/
					SET_BIT(MTIM4->CR1,CR1_CEN);
					 break;
				case MTIM2_5_ch4:
					/*Select ICU*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_CC4S1);
					SET_BIT(MTIM4->CCMR2,CCRM2_CC4S0);
					/*set the ICU FILTER value=0*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC4M_15);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC4M_14);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC4M_13);
					CLR_BIT(MTIM4->CCMR2,CCRM2_OC4M_12);
					/*set ICU PRESCALER= no preScaler*/
					CLR_BIT(MTIM4->CCMR2,CCRM2_IC4PSC10);
					CLR_BIT(MTIM4->CCMR2,CCRM2_IC4PSC11);
					/*select the rising edge sense control*/
					SET_BIT(MTIM4->CCER,CCER_CC4NP);
					SET_BIT(MTIM4->CCER,CCER_CC4P);
					/*enable capture on the corresponding PIN*/
					SET_BIT(MTIM4->CCER,CCER_CC4E);
					/* Set prescaler  */
					MTIM4->PSC = TIM4_ICU_PRESCALER;
					/* Set Preload */
					MTIM4->ARR=TIM4_ICU_ARRval;
					/*enable interrupt*/
					SET_BIT(MTIM4->DIER,DIER_CC4IE);
					/*enable timer to start ICU*/
					SET_BIT(MTIM4->CR1,CR1_CEN);
					 break;
	}
			break;
			case MTIM_5:
				switch(Copy_udtICUchannel){
				case MTIM2_5_ch1:
					/*Select ICU*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_CC1S1);
					SET_BIT(MTIM5->CCMR1,CCRM1_CC1S0);
					/*set the ICU FILTER value=0*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC1M_7);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC1M_6);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC1M_5);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC1M_4);
					/*set ICU PRESCALER= no preScaler*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_IC1PSC3);
					CLR_BIT(MTIM5->CCMR1,CCRM1_IC1PSC2);
					/*select the rising edge sense control*/
					SET_BIT(MTIM5->CCER,CCER_CC1P);
					SET_BIT(MTIM5->CCER,CCER_CC1NP);
					/*enable capture on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC1E);
					/* Set prescaler  */
					MTIM5->PSC = TIM5_ICU_PRESCALER;
					/* Set Preload */
					MTIM5->ARR=TIM5_ICU_ARRval;
					/*enable interrupt*/
					SET_BIT(MTIM5->DIER,DIER_CC1IE);
					/*enable timer to start ICU*/
					SET_BIT(MTIM5->CR1,CR1_CEN);
					 break;
				case MTIM2_5_ch2:
					/*Select ICU*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_CC2S1);
					SET_BIT(MTIM5->CCMR1,CCRM1_CC2S0);
					/*set the ICU FILTER value=0*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC2M_15);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC2M_14);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC2M_13);
					CLR_BIT(MTIM5->CCMR1,CCRM1_OC2M_12);
					/*set ICU PRESCALER= no preScaler*/
					CLR_BIT(MTIM5->CCMR1,CCRM1_IC2PSC10);
					CLR_BIT(MTIM5->CCMR1,CCRM1_IC2PSC11);
					/*select the rising edge sense control*/
					SET_BIT(MTIM5->CCER,CCER_CC2NP);
					SET_BIT(MTIM5->CCER,CCER_CC2P);
					/*enable capture on the corresponding PIN*/
					SET_BIT(MTIM5->CCER,CCER_CC2E);
					/* Set prescaler  */
					MTIM5->PSC = TIM5_ICU_PRESCALER;
					/* Set Preload */
					MTIM5->ARR=TIM5_ICU_ARRval;
					/*enable interrupt*/
					SET_BIT(MTIM5->DIER,DIER_CC2IE);
					/*enable timer to start ICU*/
					SET_BIT(MTIM5->CR1,CR1_CEN);
					 break;
				case MTIM2_5_ch3:
						/*Select ICU*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_CC3S1);
						SET_BIT(MTIM5->CCMR2,CCRM2_CC3S0);
						/*set the ICU FILTER value=0*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC3M_7);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC3M_6);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC3M_5);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC3M_4);
						/*set ICU PRESCALER= no preScaler*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_IC3PSC3);
						CLR_BIT(MTIM5->CCMR2,CCRM2_IC3PSC2);
						/*select the rising edge sense control*/
						SET_BIT(MTIM5->CCER,CCER_CC3NP);
						SET_BIT(MTIM5->CCER,CCER_CC3P);
						/*enable capture on the corresponding PIN*/
						SET_BIT(MTIM5->CCER,CCER_CC3E);
						/* Set prescaler  */
						MTIM5->PSC = TIM5_ICU_PRESCALER;
						/* Set Preload */
						MTIM5->ARR=TIM5_ICU_ARRval;
						/*enable interrupt*/
						SET_BIT(MTIM5->DIER,DIER_CC3IE);
						/*enable timer to start ICU*/
						SET_BIT(MTIM5->CR1,CR1_CEN);
						 break;
					case MTIM2_5_ch4:
						/*Select ICU*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_CC4S1);
						SET_BIT(MTIM5->CCMR2,CCRM2_CC4S0);
						/*set the ICU FILTER value=0*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC4M_15);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC4M_14);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC4M_13);
						CLR_BIT(MTIM5->CCMR2,CCRM2_OC4M_12);
						/*set ICU PRESCALER= no preScaler*/
						CLR_BIT(MTIM5->CCMR2,CCRM2_IC4PSC10);
						CLR_BIT(MTIM5->CCMR2,CCRM2_IC4PSC11);
						/*select the rising edge sense control*/
						SET_BIT(MTIM5->CCER,CCER_CC4NP);
						SET_BIT(MTIM5->CCER,CCER_CC4P);
						/*enable capture on the corresponding PIN*/
						SET_BIT(MTIM5->CCER,CCER_CC4E);
						/* Set prescaler  */
						MTIM5->PSC = TIM5_ICU_PRESCALER;
						/* Set Preload */
						MTIM5->ARR=TIM5_ICU_ARRval;
						/*enable interrupt*/
						SET_BIT(MTIM5->DIER,DIER_CC4IE);
						/*enable timer to start ICU*/
						SET_BIT(MTIM5->CR1,CR1_CEN);
						 break;
		}
				break;
	}

}

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
void TIM2_5_voidEnable_ICU_Interrupt(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel){
	switch (Copy_udtTimerNumber){
			case MTIM_2: switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		SET_BIT(MTIM2->DIER,DIER_CC1IE);	break;   /*ENABLE INTERRUPT for TIM2 ICU CH 1*/
							case MTIM2_5_ch2:		SET_BIT(MTIM2->DIER,DIER_CC2IE);	break;   /*ENABLE INTERRUPT for TIM2 ICU CH 2*/
							case MTIM2_5_ch3:		SET_BIT(MTIM2->DIER,DIER_CC3IE);	break;   /*ENABLE INTERRUPT for TIM2 ICU CH 3*/
							case MTIM2_5_ch4:		SET_BIT(MTIM2->DIER,DIER_CC4IE);	break;   /*ENABLE INTERRUPT for TIM2 ICU CH 4*/
				}
				break;
			case MTIM_3 :switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		SET_BIT(MTIM3->DIER,DIER_CC1IE);	break;    /**ENABLE INTERRUPT for TIM3 ICU CH 1*/
							case MTIM2_5_ch2:		SET_BIT(MTIM3->DIER,DIER_CC2IE);	break;    /**ENABLE INTERRUPT for TIM3 ICU CH 2*/
							case MTIM2_5_ch3:		SET_BIT(MTIM3->DIER,DIER_CC3IE);	break;    /**ENABLE INTERRUPT for TIM3 ICU CH 3*/
							case MTIM2_5_ch4:		SET_BIT(MTIM3->DIER,DIER_CC4IE);	break;    /**ENABLE INTERRUPT for TIM3 ICU CH 4*/
				}
				break;

			case MTIM_4 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		SET_BIT(MTIM4->DIER,DIER_CC1IE);	break;    /**ENABLE INTERRUPT for TIM4 ICU CH 1*/
							case MTIM2_5_ch2:		SET_BIT(MTIM4->DIER,DIER_CC2IE);	break;    /**ENABLE INTERRUPT for TIM4 ICU CH 2*/
							case MTIM2_5_ch3:		SET_BIT(MTIM4->DIER,DIER_CC3IE);	break;    /**ENABLE INTERRUPT for TIM4 ICU CH 3*/
							case MTIM2_5_ch4:		SET_BIT(MTIM4->DIER,DIER_CC4IE);	break;    /**ENABLE INTERRUPT for TIM4 ICU CH 4*/
				}
				break;
			case MTIM_5 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		SET_BIT(MTIM5->DIER,DIER_CC1IE);	break;     /**ENABLE INTERRUPT for TIM5 ICU CH 1*/
							case MTIM2_5_ch2:		SET_BIT(MTIM5->DIER,DIER_CC2IE);	break;     /**ENABLE INTERRUPT for TIM5 ICU CH 2*/
							case MTIM2_5_ch3:		SET_BIT(MTIM5->DIER,DIER_CC3IE);	break;     /**ENABLE INTERRUPT for TIM5 ICU CH 3*/
							case MTIM2_5_ch4:		SET_BIT(MTIM5->DIER,DIER_CC4IE);	break;     /**ENABLE INTERRUPT for TIM5 ICU CH 4*/
				}
				break;
	}
}
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
void TIM2_5_voidDisable_ICU_Interrupt(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel){
	switch (Copy_udtTimerNumber){
			case MTIM_2: switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM2->DIER,DIER_CC1IE);	break;   /*DISABLE INTERRUPT for TIM2 ICU CH 1*/
							case MTIM2_5_ch2:		CLR_BIT(MTIM2->DIER,DIER_CC2IE);	break;   /*DISABLE INTERRUPT for TIM2 ICU CH 2*/
							case MTIM2_5_ch3:		CLR_BIT(MTIM2->DIER,DIER_CC3IE);	break;   /*DISABLE INTERRUPT for TIM2 ICU CH 3*/
							case MTIM2_5_ch4:		CLR_BIT(MTIM2->DIER,DIER_CC4IE);	break;   /*DISABLE INTERRUPT for TIM2 ICU CH 4*/
				}
				break;
			case MTIM_3 :switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM3->DIER,DIER_CC1IE);	break;    /*DISABLE INTERRUPT for TIM3 ICU CH 1*/
							case MTIM2_5_ch2:		CLR_BIT(MTIM3->DIER,DIER_CC2IE);	break;    /*DISABLE INTERRUPT for TIM3 ICU CH 2*/
							case MTIM2_5_ch3:		CLR_BIT(MTIM3->DIER,DIER_CC3IE);	break;    /*DISABLE INTERRUPT for TIM3 ICU CH 3*/
							case MTIM2_5_ch4:		CLR_BIT(MTIM3->DIER,DIER_CC4IE);	break;    /*DISABLE INTERRUPT for TIM3 ICU CH 4*/
				}
				break;

			case MTIM_4 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM4->DIER,DIER_CC1IE);	break;    /*DISABLE INTERRUPT for TIM4 ICU CH 1*/
							case MTIM2_5_ch2:		CLR_BIT(MTIM4->DIER,DIER_CC2IE);	break;    /*DISABLE INTERRUPT for TIM4 ICU CH 2*/
							case MTIM2_5_ch3:		CLR_BIT(MTIM4->DIER,DIER_CC3IE);	break;    /*DISABLE INTERRUPT for TIM4 ICU CH 3*/
							case MTIM2_5_ch4:		CLR_BIT(MTIM4->DIER,DIER_CC4IE);	break;    /*DISABLE INTERRUPT for TIM4 ICU CH 4*/
				}
				break;
			case MTIM_5 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM5->DIER,DIER_CC1IE);	break;     /*DISABLE INTERRUPT for TIM5 ICU CH 1*/
							case MTIM2_5_ch2:		CLR_BIT(MTIM5->DIER,DIER_CC2IE);	break;     /*DISABLE INTERRUPT for TIM5 ICU CH 2*/
							case MTIM2_5_ch3:		CLR_BIT(MTIM5->DIER,DIER_CC3IE);	break;     /*DISABLE INTERRUPT for TIM5 ICU CH 3*/
							case MTIM2_5_ch4:		CLR_BIT(MTIM5->DIER,DIER_CC4IE);	break;     /*DISABLE INTERRUPT for TIM5 ICU CH 4*/
				}
				break;
	}
}
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
void TIM2_5_ChangICUpolaritiy(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel,MTIM2_5_polarity Copy_udtPolarity){
switch (Copy_udtPolarity){
case MTIM_RisingEdge:
	switch (Copy_udtTimerNumber){
			case MTIM_2: switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:	CLR_BIT(MTIM2->CCER,CCER_CC1P); CLR_BIT(MTIM2->CCER,CCER_CC1NP); break;  /*Set timer2 ICU  sense mode as rising edge */
							case MTIM2_5_ch2:	CLR_BIT(MTIM2->CCER,CCER_CC2P); CLR_BIT(MTIM2->CCER,CCER_CC2NP); break;  /*Set timer2 ICU  sense mode as rising edge */
							case MTIM2_5_ch3:	CLR_BIT(MTIM2->CCER,CCER_CC3P); CLR_BIT(MTIM2->CCER,CCER_CC3NP); break;  /*Set timer2 ICU  sense mode as rising edge */
							case MTIM2_5_ch4:	CLR_BIT(MTIM2->CCER,CCER_CC4P); CLR_BIT(MTIM2->CCER,CCER_CC4NP); break;  /*Set timer2 ICU  sense mode as rising edge */
				}
				break;
			case MTIM_3 :switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:	CLR_BIT(MTIM3->CCER,CCER_CC1P); CLR_BIT(MTIM3->CCER,CCER_CC1NP); break;  /*Set timer3 ICU  sense mode as rising edge */
							case MTIM2_5_ch2:	CLR_BIT(MTIM3->CCER,CCER_CC2P); CLR_BIT(MTIM3->CCER,CCER_CC2NP); break;  /*Set timer3 ICU  sense mode as rising edge */
							case MTIM2_5_ch3:	CLR_BIT(MTIM3->CCER,CCER_CC3P); CLR_BIT(MTIM3->CCER,CCER_CC3NP); break;  /*Set timer3 ICU  sense mode as rising edge */
							case MTIM2_5_ch4:	CLR_BIT(MTIM3->CCER,CCER_CC4P); CLR_BIT(MTIM3->CCER,CCER_CC4NP); break;  /*Set timer3 ICU  sense mode as rising edge */
				}
				break;

			case MTIM_4 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM4->CCER,CCER_CC1P); CLR_BIT(MTIM4->CCER,CCER_CC1NP); break;  /*Set timer4 ICU  sense mode as rising edge */
							case MTIM2_5_ch2:		CLR_BIT(MTIM4->CCER,CCER_CC2P); CLR_BIT(MTIM4->CCER,CCER_CC2NP); break;  /*Set timer4 ICU  sense mode as rising edge */
							case MTIM2_5_ch3:		CLR_BIT(MTIM4->CCER,CCER_CC3P); CLR_BIT(MTIM4->CCER,CCER_CC3NP); break;  /*Set timer4 ICU  sense mode as rising edge */
							case MTIM2_5_ch4:		CLR_BIT(MTIM4->CCER,CCER_CC4P); CLR_BIT(MTIM4->CCER,CCER_CC4NP); break;  /*Set timer4 ICU  sense mode as rising edge */
				}
				break;
			case MTIM_5 : switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:		CLR_BIT(MTIM5->CCER,CCER_CC1P); CLR_BIT(MTIM5->CCER,CCER_CC1NP); break;  /*Set timer5 ICU  sense mode as rising edge */
							case MTIM2_5_ch2:		CLR_BIT(MTIM5->CCER,CCER_CC2P); CLR_BIT(MTIM5->CCER,CCER_CC2NP); break;  /*Set timer5 ICU  sense mode as rising edge */
							case MTIM2_5_ch3:		CLR_BIT(MTIM5->CCER,CCER_CC3P); CLR_BIT(MTIM5->CCER,CCER_CC3NP); break;  /*Set timer5 ICU  sense mode as rising edge */
							case MTIM2_5_ch4:		CLR_BIT(MTIM5->CCER,CCER_CC4P); CLR_BIT(MTIM5->CCER,CCER_CC4NP); break;  /*Set timer5 ICU  sense mode as rising edge */
				}
				break;
	}
	break;
	case MTIM_FallingEdge:
		switch (Copy_udtTimerNumber){
				case MTIM_2: switch (Copy_udtICUchannel){
								case MTIM2_5_ch1:  SET_BIT(MTIM2->CCER,CCER_CC1P); CLR_BIT(MTIM2->CCER,CCER_CC1NP); break;   /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch2:  SET_BIT(MTIM2->CCER,CCER_CC2P); CLR_BIT(MTIM2->CCER,CCER_CC2NP); break;   /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch3:  SET_BIT(MTIM2->CCER,CCER_CC3P); CLR_BIT(MTIM2->CCER,CCER_CC3NP); break;   /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch4:  SET_BIT(MTIM2->CCER,CCER_CC4P); CLR_BIT(MTIM2->CCER,CCER_CC4NP); break;   /*Set timer3 ICU  sense mode as falling edge */
					}
					break;
				case MTIM_3 :switch (Copy_udtICUchannel){
								case MTIM2_5_ch1:	SET_BIT(MTIM3->CCER,CCER_CC1P); CLR_BIT(MTIM3->CCER,CCER_CC1NP); break;   /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch2:	SET_BIT(MTIM3->CCER,CCER_CC2P); CLR_BIT(MTIM3->CCER,CCER_CC2NP); break;   /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch3:	SET_BIT(MTIM3->CCER,CCER_CC3P); CLR_BIT(MTIM3->CCER,CCER_CC3NP); break;   /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch4:	SET_BIT(MTIM3->CCER,CCER_CC4P); CLR_BIT(MTIM3->CCER,CCER_CC4NP); break;   /*Set timer3 ICU  sense mode as falling edge */
					}
					break;

				case MTIM_4 : switch (Copy_udtICUchannel){
								case MTIM2_5_ch1:	SET_BIT(MTIM4->CCER,CCER_CC1P); CLR_BIT(MTIM4->CCER,CCER_CC1NP); break;     /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch2:	SET_BIT(MTIM4->CCER,CCER_CC2P); CLR_BIT(MTIM4->CCER,CCER_CC2NP); break;     /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch3:	SET_BIT(MTIM4->CCER,CCER_CC3P); CLR_BIT(MTIM4->CCER,CCER_CC3NP); break;     /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch4:	SET_BIT(MTIM4->CCER,CCER_CC4P); CLR_BIT(MTIM4->CCER,CCER_CC4NP); break;     /*Set timer3 ICU  sense mode as falling edge */
					}
					break;
				case MTIM_5 : switch (Copy_udtICUchannel){
								case MTIM2_5_ch1:   SET_BIT(MTIM5->CCER,CCER_CC1P); CLR_BIT(MTIM5->CCER,CCER_CC1NP); break;     /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch2:   SET_BIT(MTIM5->CCER,CCER_CC2P); CLR_BIT(MTIM5->CCER,CCER_CC2NP); break;     /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch3:   SET_BIT(MTIM5->CCER,CCER_CC3P); CLR_BIT(MTIM5->CCER,CCER_CC3NP); break;     /*Set timer3 ICU  sense mode as falling edge */
								case MTIM2_5_ch4:   SET_BIT(MTIM5->CCER,CCER_CC4P); CLR_BIT(MTIM5->CCER,CCER_CC4NP); break;     /*Set timer3 ICU  sense mode as falling edge */
					}
					break;
		}
		break;
}
}
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
u32 TIM2_5_u32ReturnICUvalue(MTIMx_NUMBER_t Copy_udtTimerNumber,MTIM2_5_PWM_channel_num Copy_udtICUchannel){
	u32 Local_RetVALUE=0;
	switch (Copy_udtTimerNumber){
			case MTIM_2: switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:	Local_RetVALUE=MTIM2->CCR1	; break;     /*get the value from the CCRx register*/
							case MTIM2_5_ch2:	Local_RetVALUE=MTIM2->CCR2	; break;     /*get the value from the CCRx register*/
							case MTIM2_5_ch3:	Local_RetVALUE=MTIM2->CCR3	; break;     /*get the value from the CCRx register*/
							case MTIM2_5_ch4:	Local_RetVALUE=MTIM2->CCR4	; break;     /*get the value from the CCRx register*/
				}
				break;
			case MTIM_3 :switch (Copy_udtICUchannel){
							case MTIM2_5_ch1:	Local_RetVALUE=MTIM3->CCR1	; break;     /*get the value from the CCRx register*/
							case MTIM2_5_ch2:	Local_RetVALUE=MTIM3->CCR2	; break;     /*get the value from the CCRx register*/
							case MTIM2_5_ch3:	Local_RetVALUE=MTIM3->CCR3	; break;     /*get the value from the CCRx register*/
							case MTIM2_5_ch4:	Local_RetVALUE=MTIM3->CCR4	; break;     /*get the value from the CCRx register*/
				}
				break;

			case MTIM_4 : switch (Copy_udtICUchannel){
						case MTIM2_5_ch1:	Local_RetVALUE=MTIM4->CCR1	; break;         /*get the value from the CCRx register*/
						case MTIM2_5_ch2:	Local_RetVALUE=MTIM4->CCR2	; break;         /*get the value from the CCRx register*/
						case MTIM2_5_ch3:	Local_RetVALUE=MTIM4->CCR3	; break;         /*get the value from the CCRx register*/
						case MTIM2_5_ch4:	Local_RetVALUE=MTIM4->CCR4	; break;         /*get the value from the CCRx register*/
				}
				break;
			case MTIM_5 : switch (Copy_udtICUchannel){
						case MTIM2_5_ch1:	Local_RetVALUE=MTIM5->CCR1	; break;         /*get the value from the CCRx register*/
						case MTIM2_5_ch2:	Local_RetVALUE=MTIM5->CCR2	; break;         /*get the value from the CCRx register*/
						case MTIM2_5_ch3:	Local_RetVALUE=MTIM5->CCR3	; break;         /*get the value from the CCRx register*/
						case MTIM2_5_ch4:	Local_RetVALUE=MTIM5->CCR4	; break;         /*get the value from the CCRx register*/
				}
				break;

	}
	return Local_RetVALUE;	/*return the captured value*/
}

void MTM3_setInterval_Asyncrouns(u32 Copy_u32TickNum , void(* Copy_pvCallBACK)(void))
{
	MTIM3->CNT=0x00000000;
				/*set PreLoad value */
				MTIM3->ARR=Copy_u32TickNum;
				SET_BIT(MTIM3->DIER , 0);
				/*start timer*/
				SET_BIT(MTIM3->CR1,CR1_CEN);
				MTIM3_pvCallBack=Copy_pvCallBACK;

}
/**************************************************************************************************/
/* @Name  	  :->		@ MTIM3_setCALLBACK												 		  */
/* @Brief 	  :->		@ used to set the ISR for timer	3 interrupts							  */
/* @parameters   :-> 	@ Copy_pvCallBACK: pointer to the function to be excuted at interrupt fire*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 		  */
/*						@ timer must be enabled with RCC								 		  */
/*						@ Timer must interrupt must be enabled							  		  */
/*						@ timer interrupt must be enabled in NVIC								  */
/**************************************************************************************************/
void MTIM3_setCALLBACK(void (*Copy_pvCallBACK)(void)){
	MTIM3_pvCallBack=Copy_pvCallBACK;	/*Set the ISR for TIMER 3 interrupt*/
}
/**************************************************************************************************/
/* @Name  	  :->		@ MTIM4_setCALLBACK												 		  */
/* @Brief 	  :->		@ used to set the ISR for timer 4 interrupts							  */
/* @parameters   :-> 	@ Copy_pvCallBACK: pointer to the function to be excuted at interrupt fire*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 		  */
/*						@ timer must be enabled with RCC								 		  */
/*						@ Timer must interrupt must be enabled							  		  */
/*						@ timer interrupt must be enabled in NVIC								  */
/**************************************************************************************************/
void MTIM4_setCALLBACK(void (*Copy_pvCallBACK)(void)){
	MTIM4_pvCallBack=Copy_pvCallBACK;  /*Set the ISR for TIMER 4 interrupt*/
}
/**************************************************************************************************/
/* @Name  	  :->		@ MTIM5_setCALLBACK												 		  */
/* @Brief 	  :->		@ used to set the ISR for timer 5 interrupts						      */
/* @parameters   :-> 	@ Copy_pvCallBACK: pointer to the function to be excuted at interrupt fire*/
/* @PreRequsteis :->	@ RCC MUST be initialized								 		 		  */
/*						@ timer must be enabled with RCC								 		  */
/*						@ Timer must interrupt must be enabled							  		  */
/*						@ timer interrupt must be enabled in NVIC								  */
/**************************************************************************************************/
void MTIM5_setCALLBACK(void (*Copy_pvCallBACK)(void)){
	MTIM5_pvCallBack=Copy_pvCallBACK;        /*Set the ISR for TIMER 5 interrupt*/
}
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/************************Interrupt handlers for timers 2:5**********************************/

void TIM2_IRQHandler(void){

}

void TIM3_IRQHandler(void){
	if(GET_BIT(MTIM3->SR,0) ==1)
	{
		CLR_BIT(MTIM3->SR,0);
		MTIM3_pvCallBack();
	}
}
void TIM4_IRQHandler(void){
	MTIM4_pvCallBack();
}

void TIM5_IRQHandler(void){
	MTIM5_pvCallBack();
}
/***********************************/
