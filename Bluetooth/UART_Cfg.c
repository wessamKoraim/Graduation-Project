#include "UART.h"
#include "UART_cfg.h"

void BluetoothTxDone(void);
void BluetoothRxDone(void);

const UART_ConfigType UART_ConfigParam[UART_PERIF_NUM] =
{
                {
                                UART_3,0,
                                BR115200,NOPARITY,STOP_ONE,UART_8_BITS,
                                BluetoothTxDone,BluetoothRxDone
                }
                };