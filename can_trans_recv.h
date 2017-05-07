/**
  ******************************************************************************
  * @file    can_trans_recv.h
  * @author  Vu Trung Hieu
  * @version V1.0
  * @date    5-May-2017
  * @brief   This file contains the functions prototypes for can_trans_recv
  *          library.  
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_TRANS_RECV_H
#define __CAN_TRANS_RECV_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Define --------------------------------------------------------------------*/
#define USE_CAN1
//#define USE_CAN2

#define USE_BOARD_1	 
//#define USE_BOARD_2
//#define USE_BOARD_3
	 
/* Initialization and Configuration functions --------------------------------*/
void CAN_Trans_Recv_Init(void);
	 
/* Send function -------------------------------------------------------------*/
void CAN_Trans_Txmessage(uint32_t can_StdID, uint8_t can_DLC, uint8_t* can_Data);
	 
#ifdef __cplusplus
}
#endif

#endif /*__CAN_TRANS_RECV_H */


/*********************************END OF FILE**********************************/
