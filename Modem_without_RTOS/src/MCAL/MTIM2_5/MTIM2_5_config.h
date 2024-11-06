/*
Author		: Abdelrahman Ahmed Aboalam
date		: 18/4/2024
version		: 1.2.0
description : MTIM2_5_config.h -> pre build config File
peri		: for user in MCAL
*/
#ifndef MTIM2_5_MTIM2_5_CONFIG_H_
#define MTIM2_5_MTIM2_5_CONFIG_H_
/*
 * COUNNTER/TIMER mode
 * options->
 * 			1- MTIM_CUP
 * 	**		2- MTIM_CDOWN
 */
#define 	 MTIM2_CMODE	MTIM_CUP
#define 	 MTIM3_CMODE	MTIM_CUP
#define		 MTIM4_CMODE	MTIM_CUP
#define 	 MTIM5_CMODE	MTIM_CUP

/**********************************************/
/*
 * set the prescaler value for PWM mode->
 *
 */
#define TIM2_PWM_PRESCALER    0
#define TIM3_PWM_PRESCALER    16
#define TIM4_PWM_PRESCALER    16
#define TIM5_PWM_PRESCALER    16

/**********************************************/
/*
 * set the preScaler value for ICU mode->
 *
 */
#define TIM2_ICU_PRESCALER    0
#define TIM3_ICU_PRESCALER    16
#define TIM4_ICU_PRESCALER    16
#define TIM5_ICU_PRESCALER    0
/*
 * set the ARR value for PWM mode->
 *
 */
#define TIM2_ICU_ARRval    65535
#define TIM3_ICU_ARRval    65535
#define TIM4_ICU_ARRval    65535
#define TIM5_ICU_ARRval    65535
#endif /* MTIM2_5_MTIM2_5_CONFIG_H_ */
