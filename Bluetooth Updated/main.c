#include "BT_Config.h"
#include "BT_Driver.h"
#include "BT_Manager.h"
#include "delay.h"

uint8_t TxDone = 0;
uint8_t RxDone = 0;
uint8_t ConnectionState = 0;

int main (void)
{
    uint8_t x = 255;
	volatile uint64_t i = 0;
	uint8_t RecArr[20] = {0};
	GPIO_Init();
	Delay_ms(100);
	UART_Init();
	BT_Init();
	
	GPIO_Write(1,PIN_MASK_0,HIGH);
	
	while(1)
	{
		BT_Manager();
		Delay_ms(1);
		switch(x)
		{
			case 255:
			{
				BT_ConnectionStatus();
				x = 254;
			}
			break;
			
			case 254:
			{
				if(ConnectionState == 4)
				{
					x = 0;
				}
				else
				{
					x = 254;
				}
			}
			break;
			
			case 0:
			{
				BT_StartReceivingData(RecArr,2);
				x = 1;
			}
			break;
				
			case 1:
			{
				if(RxDone == 1)
				{
					RxDone = 0;

					GPIO_Write(1,PIN_MASK_15,HIGH);
					if(RecArr[0]=='h')
					{
						GPIO_Write(1,PIN_MASK_12,HIGH);
						x = 2;
					}
				}
				else 
				{
					x = 1;
				}
			}
			break;
			
			case 90:
			{
				if(TxDone == 1)
				{
					TxDone = 0;
					x = 91;
				}
			}
			break;

			case 2:
			{
				BT_StartSendingData((uint8_t*)"HELLO",5);
				x = 3;
			}
			break;

			case 3:
			{
				if(TxDone == 1)
				{
					x = 4;
					TxDone = 0;
				}
				else
				{
					x = 3;
				}
			}
			break;

			case 4:
			{
				BT_ConnectionStatus();
				x=5;
			}
			break;

			default: break;
		}
	}
}

void BT_TransmissionnDoneCallBack(void)
{
	TxDone = 1;
}
void BT_ReceptionDoneCallBack(void)
{
	RxDone = 1;
}

void BT_DisconnectedCallBack(void)
{
	
}

void BT_StatusCallBack(uint8_t Connected)
{
	if( Connected == 1)
	{
		GPIO_Write(1,PIN_MASK_15,HIGH);
		ConnectionState = 2;
	}
	else
	{
		GPIO_Write(1,PIN_MASK_13,HIGH);
		ConnectionState = 4;
	}
}

void BT_ErrorCallBack(uint8_t ID)
{
	GPIO_Write(1,PIN_MASK_14,HIGH);
}