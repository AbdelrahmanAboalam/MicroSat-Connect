/*
Author		: Abdelrahman Ahmed Aboalam
date		: 18/4/2024
version		: 1.2.0
description : MUART_interface.h -> function prototypes
peri		: for user in MCAL
*/
#ifndef MUART_MUART_INTERFACE_H_
#define MUART_MUART_INTERFACE_H_

void MUSART_voidInit(void);

void MUSART_voidSendData(u8 Copy_u8Data);
u8 MUSART_voidReciveData(void);

u8 MUSART_voidRecieveAsynchronous(void);

void MUSART_voidEnable(void);

void MUSART_voidDisable(void);

void MUSART_voidSendString(const u8 *Copy_pu8Data);

void MUSART_voidSetCallBack(void(*vp_Fumc)(void));

#endif /* MUART_MUART_INTERFACE_H_ */
