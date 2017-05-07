/**
  ******************************************************************************
  * @file    can_trans_recv.c
  * @author  Vu Trung Hieu
  * @version V1.0
  * @date    14-April-2017
  * @brief   This file provides firmware functions to use CAN1 & CAN2 
  *           + PB8 - RX, PB9 - TX (CAN1)
	*           + PB5 - RX, PB6 - TX (CAN2)
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
#include "stdio.h"
#include "uart_dma_timeout.h"
#include "string.h"
#include "stdbool.h"

/* Public variables ----------------------------------------------------------*/
#ifdef USE_BOARD_3
CanRxMsg RxMessage;
bool flag = false;
#endif
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
#define OFFSET_FILTERNUMBER 0
#define CAN_RX0_IRQn 				CAN1_RX0_IRQn
#define CAN_RX1_IRQn 				CAN1_RX1_IRQn
#define CAN_RX0_IRQHandler 	CAN1_RX0_IRQHandler
#define CAN_RX1_IRQHandler 	CAN1_RX1_IRQHandler
#endif

#ifdef USE_CAN2
#define RCC_Periph_GPIO 		RCC_AHB1Periph_GPIOB
#define RCC_Periph_CAN 			RCC_APB1Periph_CAN1 | RCC_APB1Periph_CAN2
#define CAN_GPIO 						GPIOB
#define CAN_GPIO_PinSrc_RX 	GPIO_PinSource5
#define CAN_GPIO_PinSrc_TX 	GPIO_PinSource6
#define GPIO_AF_CAN 				GPIO_AF_CAN2
#define CAN_GPIO_Pin 				GPIO_Pin_5 | GPIO_Pin_6
#define CAN_MODULE					CAN2
#define OFFSET_FILTERNUMBER 14
#define CAN_RX0_IRQn 				CAN2_RX0_IRQn
#define CAN_RX0_IRQHandler 	CAN2_RX0_IRQHandler
#endif
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes CAN
  * @note   Function contains configs for 3 board
	*         Just one board can active
  * @param  None
  * @retval None
  */
void CAN_Trans_Recv_Init(void)
{
#ifdef USE_BOARD_1
  GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  
	/* Enable GPIOB clock */
  RCC_AHB1PeriphClockCmd(RCC_Periph_GPIO, ENABLE);
	/* Enable CAN1 clock */
  RCC_APB1PeriphClockCmd(RCC_Periph_CAN, ENABLE);
	
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
	
		/* Config for CAN Recv */
	CAN_FilterInitStructure.CAN_FilterActivation = DISABLE;
  CAN_FilterInitStructure.CAN_FilterNumber = OFFSET_FILTERNUMBER;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList; //CAN_FilterMode_IdList //CAN_FilterMode_IdMask
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x01<<5;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0;//0x7FF<<5;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_FilterInitStructure.CAN_FilterActivation = DISABLE;
	CAN_FilterInitStructure.CAN_FilterNumber = OFFSET_FILTERNUMBER + 1;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x02<<5;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_FilterInitStructure.CAN_FilterActivation = DISABLE;
	CAN_FilterInitStructure.CAN_FilterNumber = OFFSET_FILTERNUMBER + 2;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x03<<5;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 1;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_FilterInitStructure.CAN_FilterActivation = DISABLE;
	CAN_FilterInitStructure.CAN_FilterNumber = OFFSET_FILTERNUMBER + 3;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x05<<5;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 1;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
  
  CAN_ITConfig(CAN_MODULE, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CAN_MODULE, CAN_IT_FMP1, ENABLE);
  
	NVIC_InitStructure.NVIC_IRQChannel = CAN_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN_RX1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef USE_BOARD_2
  GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
  
	/* Enable GPIOB clock */
  RCC_AHB1PeriphClockCmd(RCC_Periph_GPIO, ENABLE);
	/* Enable CAN1 clock */
  RCC_APB1PeriphClockCmd(RCC_Periph_CAN, ENABLE);
	
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
	
	/* CAN cell init*/	
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
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  
	/* Enable GPIOB clock */
  RCC_AHB1PeriphClockCmd(RCC_Periph_GPIO, ENABLE);
	/* Enable CAN1 clock */
  RCC_APB1PeriphClockCmd(RCC_Periph_CAN, ENABLE);
	
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
	
	/* CAN cell init */	
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
	
	/* Config for CAN Recv */
	CAN_FilterInitStructure.CAN_FilterActivation = DISABLE;
  CAN_FilterInitStructure.CAN_FilterNumber = OFFSET_FILTERNUMBER;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x321<<5;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0;//0x7FF<<5;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  CAN_ITConfig(CAN_MODULE, CAN_IT_FMP0, ENABLE);
  
	NVIC_InitStructure.NVIC_IRQChannel = CAN_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
#endif
}

/**
  * @brief  CAN send
  * @note   can_Data must be a array 8
  * @param  Includes ID std, length, pointer of data
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

/**
  * @brief  CAN interrupt handler
  * @note   Just one CAN interrupt handler can be active
  * @param  none
  * @retval None
  */
#ifdef USE_BOARD_1
void CAN_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;
	uint8_t uart_data[30];
	
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
  CAN_Receive(CAN_MODULE, CAN_FIFO0, &RxMessage);
	if(RxMessage.StdId == 0x01)
	{
		sprintf((char*) &uart_data, "[temperature_%d]", RxMessage.Data[0]);
		//UART4_DMA_Send("[echoledL_OFF]", strlen("[echoledL_OFF]"));
		UART4_DMA_Send((char*) uart_data, strlen((char*) uart_data));
	}
	else if (RxMessage.StdId == 0x02)
	{
		sprintf((char*) &uart_data, "[fuel_%d]", RxMessage.Data[0]);
		UART4_DMA_Send((char*) uart_data, strlen((char*) uart_data));
	}
}

void CAN_RX1_IRQHandler(void)
{
	CanRxMsg RxMessage;
	uint8_t uart_data[30];
	
	GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
  CAN_Receive(CAN_MODULE, CAN_FIFO1, &RxMessage);
	if(RxMessage.StdId == 0x03)
	{
		sprintf((char*) &uart_data, "[velocity_%d]", RxMessage.Data[0]);
		UART4_DMA_Send((char*) uart_data, strlen((char*) uart_data));
	}
	else if (RxMessage.StdId == 0x05)
	{
		if(RxMessage.Data[0] == 0)
		{
			if(RxMessage.Data[1] == 0)
			{
				sprintf((char*) &uart_data, "[echoledL_OFF]");
				UART4_DMA_Send("[echoledL_OFF]", strlen("[echoledL_OFF]"));
			}
			else
			{
				sprintf((char*) &uart_data, "[echoledL_ON]");
				UART4_DMA_Send("[echoledL_ON]", strlen("[echoledL_ON]"));
			}
		}
		else
		{
			if(RxMessage.Data[1] == 0)
			{
				sprintf((char*) &uart_data, "[echoledR_OFF]");
				UART4_DMA_Send("[echoledR_OFF]", strlen("[echoledR_OFF]"));
			}
			else
			{
				sprintf((char*) &uart_data, "[echoledR_ON]");
				UART4_DMA_Send("[echoledR_ON]", strlen("[echoledR_ON]"));
			}
		}
	}
}
#endif

#ifdef USE_BOARD_2
//void CAN_RX0_IRQHandler(void)
//{
//	GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
//  //CAN_Receive(CAN_MODULE, CAN_FIFO0, &RxMessage);
//}
#endif

#ifdef USE_BOARD_3
void CAN_RX0_IRQHandler(void)
{
	GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
  CAN_Receive(CAN_MODULE, CAN_FIFO0, &RxMessage);
}
#endif


/*********************************END OF FILE**********************************/
