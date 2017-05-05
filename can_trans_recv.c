/**
  ******************************************************************************
  * @file    uart_dma_timeout.c
  * @author  Vu Trung Hieu
  * @version V1.0
  * @date    14-April-2017
  * @brief   This file provides firmware functions to use CAN1          
  *           + 
	*           + 
  * 
@verbatim  
 ===============================================================================
                      ##### How to use this driver #####
 ===============================================================================
   (#)      
   (#) :
       (--) 
       (--) 
       (++) 
       (++) 
       (++) 
   (#) :
       (++) 		 
@endverbatim        
  *
  ******************************************************************************
  * @attention
  * (#) 
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "can_trans_recv.h"

/* Public variables ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#ifdef USE_CAN1
#define RCC_Periph_GPIO 		RCC_AHB1Periph_GPIOB
#define RCC_Periph_CAN 			RCC_APB1Periph_CAN1
#define CAN_GPIO 						GPIOB
#define CAN_GPIO_PinSrc_RX 	GPIO_PinSource8
#define CAN_GPIO_PinSrc_TX 	GPIO_PinSource9
#define GPIO_AF_CAN 				GPIO_AF_CAN1
#define CAN_GPIO_Pin 				GPIO_Pin_8 | GPIO_Pin_9
#define CAN_MODULE					CAN1
#endif

#ifdef USE_CAN2
#define RCC_Periph_GPIO 		RCC_AHB1Periph_GPIOB
#define RCC_Periph_CAN 			RCC_APB1Periph_CAN2
#define CAN_GPIO 						GPIOB
#define CAN_GPIO_PinSrc_RX 	GPIO_PinSource5
#define CAN_GPIO_PinSrc_TX 	GPIO_PinSource6
#define GPIO_AF_CAN 				GPIO_AF_CAN2
#define CAN_GPIO_Pin 				GPIO_Pin_5 | GPIO_Pin_6
#define CAN_MODULE					CAN2
#endif
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes CAN
  * @note   ...
  * @param  None
  * @retval None
  */
void CAN_Trans_Recv_Init(void)
{
#ifdef USE_BOARD_1
  GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
  
	/* Enable GPIOB clock */
  RCC_AHB1PeriphClockCmd(RCC_Periph_GPIO, ENABLE);
	/* Enable CAN1 clock */
  RCC_APB1PeriphClockCmd(RCC_Periph_CAN , ENABLE);
	
	/* Connect CAN1 pins to AF9 */ 
	GPIO_PinAFConfig(CAN_GPIO, CAN_GPIO_PinSrc_RX, GPIO_AF_CAN); 
	GPIO_PinAFConfig(CAN_GPIO, CAN_GPIO_PinSrc_TX, GPIO_AF_CAN); 
	
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin =  CAN_GPIO_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(CAN_GPIO, &GPIO_InitStructure);
  
  /* CAN register init */
	CAN_DeInit(CAN_MODULE);
	
	/*CAN1 cell init*/	
	CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
  CAN_InitStructure.CAN_Prescaler = 2;
  CAN_Init(CAN_MODULE, &CAN_InitStructure);
#endif

#ifdef USE_BOARD_2
  GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
  
	/* Enable GPIOB clock */
  RCC_AHB1PeriphClockCmd(RCC_Periph_GPIO, ENABLE);
	/* Enable CAN1 clock */
  RCC_APB1PeriphClockCmd(RCC_Periph_CAN , ENABLE);
	
	/* Connect CAN1 pins to AF9 */ 
	GPIO_PinAFConfig(CAN_GPIO, CAN_GPIO_PinSrc_RX, GPIO_AF_CAN); 
	GPIO_PinAFConfig(CAN_GPIO, CAN_GPIO_PinSrc_TX, GPIO_AF_CAN); 
	
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin =  CAN_GPIO_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(CAN_GPIO, &GPIO_InitStructure);
  
  /* CAN register init */
	CAN_DeInit(CAN_MODULE);
	
	/*CAN1 cell init*/	
	CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
  CAN_InitStructure.CAN_Prescaler = 2;
  CAN_Init(CAN_MODULE, &CAN_InitStructure);
#endif

#ifdef USE_BOARD_3
  GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
  
	/* Enable GPIOB clock */
  RCC_AHB1PeriphClockCmd(RCC_Periph_GPIO, ENABLE);
	/* Enable CAN1 clock */
  RCC_APB1PeriphClockCmd(RCC_Periph_CAN , ENABLE);
	
	/* Connect CAN1 pins to AF9 */ 
	GPIO_PinAFConfig(CAN_GPIO, CAN_GPIO_PinSrc_RX, GPIO_AF_CAN); 
	GPIO_PinAFConfig(CAN_GPIO, CAN_GPIO_PinSrc_TX, GPIO_AF_CAN); 
	
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin =  CAN_GPIO_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(CAN_GPIO, &GPIO_InitStructure);
  
  /* CAN register init */
	CAN_DeInit(CAN_MODULE);
	
	/*CAN1 cell init*/	
	CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
  CAN_InitStructure.CAN_Prescaler = 2;
  CAN_Init(CAN_MODULE, &CAN_InitStructure);
#endif
}

/**
  * @brief  ICAN send
  * @note   ...
  * @param  ...
  * @retval None
  */
void CAN_Trans_Txmessage(uint32_t can_StdID, uint8_t can_DLC, uint8_t* can_Data)
{
	int i;
	/* Transmit Structure preparation */
	CanTxMsg TxMessage;
	TxMessage.StdId = can_StdID;
  TxMessage.DLC = can_DLC;
	for(i = 0; i < 8; i++)
	{
		TxMessage.Data[i] = can_Data[i];
	}
	TxMessage.ExtId = 0;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.IDE = CAN_ID_STD;
	/*CAN Send*/
	CAN_Transmit(CAN_MODULE, &TxMessage);
}

//void CAN2_RX0_IRQHandler(void)
//{
//	GPIO_SetBits(GPIOD, GPIO_Pin_15);
//  CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);
//}

//void test(void)
//{
//	NVIC_InitTypeDef  NVIC_InitStructure;
//	GPIO_InitTypeDef  GPIO_InitStructure;
//  
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//  GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_CAN2);//PB5 - CAN2_RX
//  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_CAN2);//PB6 - CAN2_TX
//	
//  /* Configure CAN RX and TX pins */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 ;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//  /*Init CAN*/
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1 | RCC_APB1Periph_CAN2, ENABLE);
//  
//  /* CAN register init */
//	CAN_DeInit(CAN2); 
//  /*CAN1 cell init*/
//	
//	CAN_InitStructure.CAN_TTCM = DISABLE;
//  CAN_InitStructure.CAN_ABOM = DISABLE;
//  CAN_InitStructure.CAN_AWUM = DISABLE;
//  CAN_InitStructure.CAN_NART = DISABLE;
//  CAN_InitStructure.CAN_RFLM = DISABLE;
//  CAN_InitStructure.CAN_TXFP = DISABLE;
//  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
//  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
//  CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
//  CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
//  CAN_InitStructure.CAN_Prescaler = 2;
//  CAN_Init(CAN2, &CAN_InitStructure);	

//  CAN_FilterInitStructure.CAN_FilterActivation = DISABLE;
//  CAN_FilterInitStructure.CAN_FilterNumber = 14;
//  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
//  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
//  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x321<<5;
//  CAN_FilterInitStructure.CAN_FilterIdLow = 0;
//  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0;//0x7FF<<5;
//  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0;
//  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
//  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
//  CAN_FilterInit(&CAN_FilterInitStructure);
//  
//  CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
//  
//	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//}

/*********************************END OF FILE**********************************/
