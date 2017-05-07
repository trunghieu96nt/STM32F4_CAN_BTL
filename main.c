#include "stm32f4xx.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"
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
uint8_t cmd_message[6];
uint8_t value_message[4];
uint8_t can_Data[8];
uint8_t i, count = 0;
#endif

#ifdef USE_BOARD_3
extern uint8_t rcv_message[BUFF_SIZE];
extern bool b_UART_DMA_Timeout;
uint8_t receive[6]={0,0,0,0,0,0};
uint8_t count = 0;
uint8_t i;
uint8_t send_mes[2];
uint8_t send[8]={0};
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
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
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
		if(tick_count == 100)
		{
			tick_count = 0;	
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		}	
		else
		{
			if(b_UART_DMA_Timeout)
			{
				b_UART_DMA_Timeout = false;
				
				count = 0;
				while(rcv_message[count] != '\0')
				{
					count++;
				}
				
				for(i=0; i<5;i++)
					cmd_message[i] = rcv_message[i];
				cmd_message[i] = 0;
				
				if(!strcmp((char*) cmd_message, "[temp"))
				{
					GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
					for(i = 13;i<count-1;i++)
						value_message[i-13] = rcv_message[i];
					value_message[i-13] = 0;
					can_Data[0] = atoi((char*)value_message);
					CAN_Trans_Txmessage(0x01, 1, can_Data);
				}
				else if(!strcmp((char*) cmd_message, "[fuel"))
				{
					GPIO_ToggleBits(GPIOD,GPIO_Pin_14);
					for(i = 6;i<count-1;i++)
						value_message[i-6] = rcv_message[i];
					value_message[i-6] = 0;
					can_Data[0] = atoi((char*)value_message);
					CAN_Trans_Txmessage(0x02, 1, can_Data);
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
			if(flag == true)
			{
				flag = false;
				if((RxMessage.Data[0] == 0)&&(RxMessage.Data[1]==0)) 
				{
					GPIO_SetBits(GPIOD,GPIO_Pin_12);
					UART4_DMA_Send("ledL_OFF", strlen("ledL_OFF"));
				}
				else if((RxMessage.Data[0] == 0)&&(RxMessage.Data[1]==1)) 
				{
					GPIO_SetBits(GPIOD,GPIO_Pin_13);
					UART4_DMA_Send("ledL_ON", strlen("ledL_ON"));
				}
				else if((RxMessage.Data[0] == 1)&&(RxMessage.Data[1]==0)) 
				{
					GPIO_SetBits(GPIOD,GPIO_Pin_14);
					UART4_DMA_Send("ledR_OFF", strlen("ledR_OFF"));
				}
				else if((RxMessage.Data[0] == 1)&&(RxMessage.Data[1]==1)) 
				{
					GPIO_SetBits(GPIOD,GPIO_Pin_15);
					UART4_DMA_Send("ledR_ON", strlen("ledR_ON"));
				}
			}
			if(b_UART_DMA_Timeout)
			{
				b_UART_DMA_Timeout = false;
				while(rcv_message[count] != '\0')
				{
					count++;
				}
				for(i=0; i<5;i++)
					receive[i] = rcv_message[i];
				receive[i] = 0;
				if(!strcmp((char*) receive, "[velo"))
				{
					GPIO_SetBits(GPIOD,GPIO_Pin_15);
					for(i = 10;i<count-1;i++)
						send_mes[i-10] = rcv_message[i];
					send_mes[i-10] = 0;
					send[0] = atoi((char*)send_mes);
					CAN_Trans_Txmessage(0x03, 1, send);
				}
				else if(!strcmp((char*) receive, "echol"))
				{
					if(!strcmp((char*) rcv_message, "echoledL_OFF"))
					{
						send_mes[0] = 0;
						send_mes[1] = 0;
						CAN_Trans_Txmessage(0x05, 2, send_mes);
					}
					else if(!strcmp((char*) rcv_message, "echoledL_ON"))
					{
						send_mes[0] = 0;
						send_mes[1] = 1;
						CAN_Trans_Txmessage(0x05, 2, send_mes);
					}
					else if(!strcmp((char*) rcv_message, "echoledR_OFF"))
					{
						send_mes[0] = 1;
						send_mes[1] = 0;
						CAN_Trans_Txmessage(0x05, 2, send_mes);
					}
					else if(!strcmp((char*) rcv_message, "echoledR_ON"))
					{
						send_mes[0] = 1;
						send_mes[1] = 1;
						CAN_Trans_Txmessage(0x05, 2, send_mes);
					}
				}
			}
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
