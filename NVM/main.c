#include "NVM_Manager.h"
#include "delay.h"
uint8_t NVM_WriteDoneFlag = 0;
uint8_t NVM_ReadDoneFlag = 0;
uint16_t s7s = 0;

void NVM_WriteDone(void)
{
	NVM_WriteDoneFlag = 1;
}

void NVM_ReadDone(void)
{
	NVM_ReadDoneFlag = 1;
}

void NVM_Error(uint8_t ID)
{
	GPIO_Write(1,PIN_MASK_14,HIGH);
	s7s = 1;
}

int main(void)
{
	uint8_t x=0;
	uint8_t Data[4] = {0x20,0x00,0x66};
	uint8_t RecData[3] = {0,0,0};
	NVM_CheckType y = NVM_OK;
	GPIO_Init();
	Delay_ms(100);
	I2C_Init();
	NVM_Init();
	
	while(1)
	{
		I2C_Manager();
		NVM_Manager();
		Delay_ms(1);
		
		switch(x)
		{
			case 0:
			{
				y = NVM_Write(0,Data);
				
				if(y == NVM_NOT_BUSY)
				{
						x = 1;
				}
			}
			break;

			case 1:
			{
				if(NVM_WriteDoneFlag == 1)
				{
					x = 2;
					GPIO_Write(1,PIN_MASK_12,HIGH);
				}
			}
			break;

			case 2:
			{
				Delay_ms(100);
				x = 3;
			}
			break;

			case 3:
			{
				NVM_Read(0, RecData);

				x = 4;
			}
			break;

			case 4:
			{
				if(NVM_ReadDoneFlag == 1)
				{
					x = 5;
					GPIO_Write(1,PIN_MASK_13,HIGH);
				}
			}
			break;

			case 5:
			{
				if(	(RecData[0] == 0x20) &&
					(RecData[1] == 0x00) &&
					(RecData[2] == 0x66))
				{
					GPIO_Write(1,PIN_MASK_15,HIGH);
					x = 6;
				}
			}
			break;

			default: break;
		}
	}

}

