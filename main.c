#include "stm32f4xx.h"
#include "stdbool.h"
#include "string.h"
#include "system_timetick.h"
#include "uart_dma_timeout.h"
#include "can_trans_recv.h"

#ifdef USE_BOARD_1
extern uint8_t rcv_message[BUFF_SIZE];
extern bool b_UART_DMA_Timeout;
uint8_t can_Data[8];
#endif

#ifdef USE_BOARD_2
extern uint8_t rcv_message[BUFF_SIZE];
extern bool b_UART_DMA_Timeout;
uint8_t can_Data[8];
#endif

#ifdef USE_BOARD_3

#endif

void init_main(void);

int main(void)
{
	/* Enable SysTick at 10ms interrupt */
	SysTick_Config(SystemCoreClock/100);

	init_main();

	while(1)
	{
#ifdef USE_BOARD_1
		if(tick_count == 100)
		{
			tick_count = 0;
			//while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
			//USART_SendData(UART4,(uint8_t)65);	
			
			//GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
		}	
		else
		{
			if(b_UART_DMA_Timeout)
			{
				b_UART_DMA_Timeout = false;
				if(!strcmp((char*) rcv_message, "[PD12_TOGGLE]"))
				{
					GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
					UART4_DMA_Send("[DONE]", strlen("[DONE]"));
				}
				else if(!strcmp((char*) rcv_message, "[ledL_OFF]"))
				{
					can_Data[0] = 0;
					can_Data[1] = 0;
					CAN_Trans_Txmessage(0x04, 2, can_Data);
				}
				else if(!strcmp((char*) rcv_message, "[ledL_ON]"))
				{
					can_Data[0] = 0;
					can_Data[1] = 1;
					CAN_Trans_Txmessage(0x04, 2, can_Data);
				}
				else if(!strcmp((char*) rcv_message, "[ledR_OFF]"))
				{
					can_Data[0] = 1;
					can_Data[1] = 0;
					CAN_Trans_Txmessage(0x04, 2, can_Data);
				}
				else if(!strcmp((char*) rcv_message, "[ledR_ON]"))
				{
					can_Data[0] = 1;
					can_Data[1] = 1;
					CAN_Trans_Txmessage(0x04, 2, can_Data);
				}
			}
		}
#endif
		
#ifdef USE_BOARD_2
		if(tick_count == 150)
		{
			tick_count = 151;
			can_Data[0] = 0x14;
			can_Data[1] = 0x15;
			CAN_Trans_Txmessage(0x01, 1, can_Data);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
		}	
		else if (tick_count == 300)
		{
			tick_count = 301;
			can_Data[0] = 0x10;
			can_Data[0] = 0x13;
			CAN_Trans_Txmessage(0x321, 1, can_Data);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		}
		else if (tick_count == 450)
		{
			tick_count = 0;
			can_Data[0] = 0x16;
			can_Data[0] = 0x17;
			CAN_Trans_Txmessage(0x02, 2, can_Data);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
		}
		else
		{
			if(b_UART_DMA_Timeout)
			{
				b_UART_DMA_Timeout = false;
				if(!strcmp((char*) rcv_message, "[PD12_TOGGLE]"))
				{
					GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
					UART4_DMA_Send("[DONE]", strlen("[DONE]"));
				}
				else if(!strcmp((char*) rcv_message, "[PD12_ON]"))
				{
					GPIO_SetBits(GPIOD, GPIO_Pin_12);
					UART4_DMA_Send("[DONE]", strlen("[DONE]"));
				}
				else if(!strcmp((char*) rcv_message, "[PD12_OFF]"))
				{
					GPIO_ResetBits(GPIOD, GPIO_Pin_12);
					UART4_DMA_Send("[DONE]", strlen("[DONE]"));
				}
			}
		}
#endif

#ifdef USE_BOARD_3
		if(tick_count == 100)
		{
			
		}	
		else
		{
			
		}
#endif
	}
}

void init_main(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
   
	/* Enable GPIOD clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD12, PD13 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	UART_DMA_Timeout_Init();
  CAN_Trans_Recv_Init();
}
