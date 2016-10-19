//------------------------------------------------------------------------------
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------

#include "SiITypeDefs.h"
#include "SiIHAL.h"


#ifdef _STD_C_


#define halSetDDC_SDAPin()
#define halSetDDC_SCLPin()

#define halClearDDC_SDAPin()
#define halClearDDC_SCLPin()

#define halGetDDC_SDAPin() 0
#define halGetDDC_SCLPin() 0

#define halGetSwitchState( SWITCH_MASK) 0

#else ifdef  _8051_

#define halSetDDC_SDAPin()     DDC_SDA = 1
#define halSetDDC_SCLPin()     DDC_SCL = 1

#define halClearDDC_SDAPin()   DDC_SDA = 0
#define halClearDDC_SCLPin()   DDC_SCL = 0

#define halGetDDC_SDAPin()     DDC_SDA
#define halGetDDC_SCLPin()     DDC_SCL

#define halGetSwitchState( MASK ) ( P0 & MASK )

#endif

void siiReadGPIO( BYTE * );
void siiWriteGPIO( BYTE * );
void PutChar( char );


