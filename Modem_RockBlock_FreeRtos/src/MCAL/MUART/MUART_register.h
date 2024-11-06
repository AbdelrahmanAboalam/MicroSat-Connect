/*
Author		: Abdelrahman Ahmed Aboalam
date		: 18/4/2024
version		: 1.2.0
description : MUART_register.h -> Register File
peri		: for the developer in MCAL only not for the user
*/
#ifndef MUART_MUART_REGISTER_H_
#define MUART_MUART_REGISTER_H_

#define MUSART1_BASE_ADDRESS  0x40011000UL


typedef struct{
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;
}USART_t;

#define MUSART1 ((volatile USART_t*)(MUSART1_BASE_ADDRESS))


#endif /* MUART_MUART_REGISTER_H_ */
