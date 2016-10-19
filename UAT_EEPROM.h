#ifndef SII_AT_EEPROM
#define SII_AT_EEPROM

#include "SiITypeDefs.h"
#include "AT89C51XD2.h"

#define halDisableMCUInterrupts() EA = 0
#define halEnableMCUInterrupts() EA = 1
#define halIsIntEEPROM_Busy() (EECON & 0x01)
#define halIntEEPROM_Enable() ( EECON |= 0x02 )
#define halIntEEPROM_Disable() ( EECON &= 0xFD )

void siiWriteByteInternEEPROM ( WORD , BYTE );
void siiReadByteInternEEPROM ( WORD , BYTE * );

#endif
