//------------------------------------------------------------------------------
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------

#include "SiITypeDefs.h"
#include "SiIIICDefs.h"

BYTE GetI2CState( void );

BYTE GetI2CStatus( void );
BYTE DDC_GetI2CStatus( void );

BYTE I2CSendByte( BYTE );
void I2CSendStop( void );
BYTE I2CSendAddr ( BYTE, BYTE );
//BYTE I2CGetLastByte( void );
BYTE _I2CGetByte( BYTE );

BYTE DDC_GetI2CState( void );
BYTE DDC_I2CSendByte( BYTE );
BYTE DDC_I2CSendAddr( BYTE , BYTE );
void DDC_I2CSendStop( void );
BYTE DDC__I2CGetByte( BYTE );
void ResetEEPROM( void );
void MakeSCLPulses( BYTE );
void DDC_MakeSCLPulses( BYTE);


