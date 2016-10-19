//------------------------------------------------------------------------------
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------

#include "SiITypeDefs.h"

typedef struct {

    WORD Min;
    WORD Max;

}CTSLimitsType;

typedef struct {

    WORD wOutputSelect;
    WORD wI2SBusFormat;
    BYTE bI2SMap;
	BYTE bDSDHBRFormat; 
} AudioOutputFormatType;

extern AudioOutputFormatType SavedAudioOutputFormat;
#define siiSetAudioMuteEvent() siiAudioFIFO_Reset()
#define GetFIFO_DiffPointer() siiReadByteHDMIRXP1( RX_FIFO_DIFF_ADDR )

void siiAudioFIFO_Reset ( void );
BOOL siiCheckAudio_IfOK_InitACR( void );
BOOL siiPrepareTurningAudioOn( void );
void siiTurningAudio( BOOL );
void siiSetAnalogAudioMux( BYTE );
void siiSetDigitalAudioMux( void );
void siiClearGotCTSAudioPacketsIterrupts ( void );
void siiClearCTSChangeInterruprt( void );
void siiSetAudioOutputFormat( AudioOutputFormatType * );
void siiGetAudioOutputFormat( AudioOutputFormatType * );
void siiSaveInputAudioStatus( void );
BOOL siiIsAudioStatusReady( void );
void siiSetAutoFIFOReset(BOOL);
void siiAudioMute( BOOL ); 

void siiChangeDSDAudioStreamHandler ( void );
void siiChangeHBRAudioStreamHandler ( void );
