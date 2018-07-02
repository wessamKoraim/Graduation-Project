#include "NVM_Manager.h"
#include "NVM_Config.h"

NVM_ConfigType NVM_ConfigParam [NO_OF_NVM_USED] = 
{
    {
        /*EEPROM Slave Address*/
        0xA0,
        /*Numer of Bytes*/
        3,
        /*Location Address to Read Or Write*/
        0x20,
        /*Write Call Back Function*/
        NVM_WriteDone,
        /*Read Call Back Function*/
        NVM_ReadDone,
        /*Error Call Back Function*/
        NVM_Error
    }
};


