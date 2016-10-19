//------------------------------------------------------------------------------
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------

#include "SiITypeDefs.h"
#include "SiIRXDefs.h"


enum HDCPErrorProcessing {
    cbHDCPStuckConfirmThres = 4,
    cbHDCPFailFrmThres = 4
};

BYTE siiRX_PinInterruptHandler( void );
BYTE siiRX_BitInterruptHandler( void );
void siiCheckTransitionToDVIModeAndResetHDMIInfoIfConfirmed( void );
void siiTraceRXInterrupts ( void );

/* Declaratins of functions which used only inside the module */

static BOOL CheckAVIHader( void );
static void SetNoAVIIntrrupts( BOOL );
static void ProcessChangeBetween_DVI_HDMI_Modes( void );
static void EnableCheckHDCPFailureWithVSyncRate ( BOOL );
static void AVI_And_NoAVI_WorkAround( BYTE * );
static BOOL GotNConsecutiveVSyncHDCPFailure ( void );
static BOOL DetectHDCPStuck( void );
static BYTE GotNConsecutiveHDCPStuckInterrupt ( void );
static BYTE HDCPErrorHandler ( BYTE , BYTE );
static BYTE RXInterruptHandler( void );

