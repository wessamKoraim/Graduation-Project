#include "NVM_Manager.h"
#include "NVM_Config.h"

NVM_ConfigType NVM_ConfigParam [NO_OF_NVM_USED] = 
{
    {
        /*EEPROM Slave Address*/
        0xA0,
        /*Numer of Bytes*/
        4,
        /*Location Address to Read Or Write*/
        0x30,
        /*Write Call Back Function*/
        NVM_WriteDone,
        /*Read Call Back Function*/
        NVM_ReadDone,
        /*Error Call Back Function*/
        NVM_Error
    },
	{
        /*EEPROM Slave Address*/
        0xA0,
        /*Numer of Bytes*/
        4,
        /*Location Address to Read Or Write*/
        0x00,
        /*Write Call Back Function*/
        NVM_WriteDone,
        /*Read Call Back Function*/
        NVM_ReadDone,
        /*Error Call Back Function*/
        NVM_Error
    }
};