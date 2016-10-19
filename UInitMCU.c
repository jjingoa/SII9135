//------------------------------------------------------------------------------
// Module Name: SiIInitMCU
//
// Module Description: Initialization of Microcontroller, this file must be customized
//                     by user, unless same micorocontroller is used
//
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------
#include "UInitMCU.h"
#include "SiIHAL.h"

#ifdef _8051_

#include "UMCUDefs.h"

#endif

//------------------------------------------------------------------------------
// Function Name:  SetUART
// Function Description:  setup UART
//------------------------------------------------------------------------------
static void SetUART( WORD wBaudrate ) {
#ifdef _8051_
// Setup TIMER1 to generate the proper baud rate.

    SM0 = 0; SM1 = 1;               /* serial port MODE 1 */
    SM2 = 0;
    REN = 1;                        /* enable serial receiver */

// Clear transmit interrupt and buffer.

    TI = 0;                          /* clear transmit interrupt */
    RI = 0;

// Set timer 1 up as a baud rate generator.

    TR1 = 0;                            /* stop timer 1 */
    ET1 = 0;                            /* disable timer 1 interrupt */

    PCON |= 0x80;                       /* 0x80=SMOD: set serial baudrate doubler */

    TMOD &= ~0xF0;                      /* clear timer 1 mode bits */
    TMOD |= 0x20;                       /* put timer 1 into MODE 2 */

    TH1 = (BYTE) (256 - (OSC / (16L * 12L * wBaudrate)));

    TR1 = 1;                            /* start timer 1 */

    TI = 1; // First symbol

#endif
}

//------------------------------------------------------------------------------
// Function Name: SetSystemTickTimer
// Function Description: Setup system timer which used sync. API engine and delays
//------------------------------------------------------------------------------
static void SetSystemTickTimer( void ){
#ifdef _8051_
    TL0 = 25;                      // Timer 0 for interruput every 250 us
    TH0 = 25;                      // internal clock div/ 12 and div 230 then
    TR0 = 1;
    ET0 = 1;                        // Timer 0  interrupts enable
    TMOD |= 0x02;                   // Timer 0 in Mode 2 (8-bit auto-reload)
#endif
}
//------------------------------------------------------------------------------
// Function Name: SetInterrupts
// Function Description: Setup microcontrollers interrupts
//------------------------------------------------------------------------------
static void SetInterrupts( void ){
#ifdef _8051_
    ES = 1;                // Serial interrupts enable
    ET0 = 1;               // Timer 0  interrupts enable
    IP = 0xA0;             // Highest priority goes to T2 (VRefreshRate)
    EA = 1;
#endif
}
//------------------------------------------------------------------------------
// Function Name: siiInitializeMCU
// Function Description: Initialaze microcontroller
//
// Accepts: none
// Returns: none
// Globals: none
//------------------------------------------------------------------------------
void siiInitializeMCU( void ){

   SetUART( 19200 );
   SetSystemTickTimer();
   SetInterrupts();

}

