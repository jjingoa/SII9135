//------------------------------------------------------------------------------
// Module Name UMCU_IO
// Module Description: This mudule handels MCU input/output which doesn't
//                     belong to SiIHAL.c (API hardware abstraction layer)
//
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------
#include "UMCU_IO.h"
#include "UGlob.h"


BOOL qTXBusy;
//------------------------------------------------------------------------------
// Function Name: siiWriteGPIO
// Function Description: Write GPIO, this functionused for direct IO control
//------------------------------------------------------------------------------
void siiWriteGPIO( BYTE * pbGPIO ){

   if( pbGPIO[0] & 0x01 )
        halSetHPD1Pin();
   else
        halClearHPD1Pin();
   if( pbGPIO[0] & 0x02 )
        halSetHPD2Pin();
   else
        halClearHPD2Pin();
}
//------------------------------------------------------------------------------
// Function Name: siiReadGPIO
// Function Description: This function reads Hot Plug Detect pins
//------------------------------------------------------------------------------
void siiReadGPIO( BYTE * pbGPIO ){

    pbGPIO[0] = pbGPIO[1] = pbGPIO[2] = pbGPIO[3] = 0;
    if ( halGetHPD1Pin() )
        pbGPIO[0] |= 0x01;
    if ( halGetHPD2Pin() )
        pbGPIO[0] |= 0x02;
}

//------------------------------------------------------------------------------
// Function Name: SIO_InterruptHandler
// Function Description: This function reads Serial Port and writes data into command buffer
//                       Clears TX interrupts
//------------------------------------------------------------------------------
#ifdef _8051_
void SIO_InterruptHandler(void)  interrupt 4 {
static BYTE bChCount;

    if( RI ) {
        if ( bCommState == ReadyRX ) {
            if ( !qBuffInUse){
                if ( bRxIndex < RX_BUF_SIZE){
                    RXBuffer[ bRxIndex++ ] = SBUF;
                    bChCount++;
                    if ( qFuncExe && ( bChCount == 8 ) ) {
                        PutChar(0xE0);
                        bChCount = 0;
                        bRxIndex = 0;
                    }
                }
            }
        }
        else {
            if ( SBUF == START_FRAME_RX ){
                bCommState = ReadyRX;
                bCommTO = 10;
                bChCount = 0;
            }
        }
        RI = 0;
    }
    if ( TI ) {
        TI = 0;
        qTXBusy  = 0;
    }
}
#endif
//------------------------------------------------------------------------------
// Function Name: PutChar
// Function Description: This function sends Char to UART or Character LCD, it
//                       used for printing out debug information as well as
//                       supports communitation protocol with PC
//------------------------------------------------------------------------------
void PutChar( char Ch ){
#ifdef _8051_

    while( qTXBusy );
    qTXBusy = 1;
    SBUF = Ch;

#endif
}




