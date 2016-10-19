//------------------------------------------------------------------------------
// Module Name: UKeyboard.c
//
// Module Description:   processing a switchers keybord
//
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------
#include "UKeyboard.h"
#include "UDemoLoader.h"
#include "UCfgRX.h"
#include "UMCU_IO.h"
#include "SiIRX_API.h"


//------------------------------------------------------------------------------
// Function Name: KeyboardbSwCode
// Function Description:  Gets Sw keybord code, makes debouncing, if new switcher is set
//                        and confirmed, then function returns sw code. Otherwise Zero
//                        has been return
//------------------------------------------------------------------------------
BYTE KeyboardProcessor( BYTE bPCB_Id ){
BYTE bSwCode;
static KeyboardType Switcher = { 0xFF, 0x00 };
BYTE bResult = FALSE;
BYTE bSwitchMask;

    if ( bPCB_Id == SiI_CP9041 ) {
        bSwitchMask = 0xF5;
    }
    else if ( bPCB_Id == SiI_CP9031 ) {
        bSwitchMask = 0x20;
    }
    else if (( bPCB_Id == SiI_CP9133 )||( bPCB_Id == SiI_CP9135||bPCB_Id == SiI_CP9125 )) {
        bSwitchMask = 0x08;
    }

    bSwCode = halGetSwitchState( bSwitchMask );
    if ( bSwCode != Switcher.bCode ) {
        Switcher.bCode = bSwCode;
        Switcher.bRepeatCounter = 0;
    }
    else if ( Switcher.bRepeatCounter == SWTHRESHHOLD ) {
        Switcher.bRepeatCounter = SWTHRESHHOLD + 1;
		if ( (( bPCB_Id == SiI_CP9133 )||( bPCB_Id == SiI_CP9135||bPCB_Id == SiI_CP9125 ))&& !Switcher.bCode ) {		// There needs to be a better solution to returning 0x00 as a valid bResult!
			bResult = 0xCC;										// Until then, just return something not currently used.
		}
		else {
			bResult = Switcher.bCode;
		}
    }
    else if( Switcher.bRepeatCounter < SWTHRESHHOLD ) {
        Switcher.bRepeatCounter++;
    }
    return bResult;
}

//------------------------------------------------------------------------------
// Function Name:  KeyboardHandler()
// Function Description:
//
// Accepts: none
// Returns: none
// Globals: none
//------------------------------------------------------------------------------
void siiKeyboardHandler( void ) {

BYTE bSwCode, bPCB_Id;

	bPCB_Id = siiGetPCB_Id();
	bSwCode = KeyboardProcessor( bPCB_Id );

    if ( bSwCode ) {
		if ( bPCB_Id == SiI_CP9041 ) {
			siiDemoTaskLoader (bSwCode);
		}

		else if (( bPCB_Id == SiI_CP9133 )||( bPCB_Id == SiI_CP9135||bPCB_Id == SiI_CP9125 )) {
			SiI_RX_SetVideoInput ((bSwCode == 0x08) ? SiI_RX_VInCh1 : SiI_RX_VInCh2);
		}
    }
}
