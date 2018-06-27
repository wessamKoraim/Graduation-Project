#include "NVM_Manager.h"
#include "delay.h"
uint8_t NVM_WriteDoneFlag = 0;
uint8_t NVM_ReadDoneFlag = 0;

void NVM_WriteDone(void)
{
	NVM_WriteDoneFlag = 1;
}

void NVM_ReadDone(void)
{
	NVM_ReadDoneFlag = 1;
}

int main(void)
{
	uint8_t x=0;
	uint8_t Data[4] = {0x30,0x44,0x55,0x66};
	uint8_t RecData[3] = {0,0,0};
	GPIO_Init();
	I2C_Init();
	NVM_Init();
	
	while(1)
	{
		I2C_Manager();
		NVM_Manager();

		switch(x)
		{
			case 0:
			{
				NVM_Write(0,Data);
				x = 1;
			}
			break;

			case 1:
			{
				if(NVM_WriteDoneFlag == 1)
				{
					x = 2;
					GPIO_Write(2,1);
				}
			}
			break;

			case 2:
			{
				Delay_ms(10);
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
					GPIO_Write(3,1);
				}
			}
			break;

			case 5:
			{
				if(	(RecData[0] == 0x44) &&
					(RecData[1] == 0x55) &&
					(RecData[2] == 0x66))
				{
					GPIO_Write(5,1);
					x = 6;
				}
			}
			break;

			default: break;
		}
	}

}