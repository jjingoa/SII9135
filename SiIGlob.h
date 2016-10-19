//------------------------------------------------------------------------------
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------
#ifndef _SII_GLOB_
#define _SII_GLOB_

#include "SiITypeDefs.h"
#include "SiIVidRes.h"

#define SII_ADAC_PD_DELAY 0

// RX API Information
enum SiI_RX_API_Info {
    SiI_RX_API_Version = 0x01,
    SiI_RX_API_Revision = 0x02,//increased
    SiI_RX_API_Build = 0x3,//YMA 3
    SiI_RX_API_DiagnosticCommands = TRUE
};

typedef struct {

    WORD wProcLastAPI_Ticks;
    WORD wProcLastDoTasks_Ticks;

} SysTimerType;

typedef struct {

    BYTE bOutputVideoPath;
    BYTE bOutputSyncSelect;
    BYTE bOutputSyncCtrl;
    BYTE bOutputVideoCtrl;

} VideoFormatType;
/*
typedef struct {
	BYTE bInputColorDepth;
	BYTE bOutputColorDepth;
} DeepColorType;
*///move to AVIType (sync as Vlad's new API code)

typedef struct {

    BYTE sm_bVideo;
    BYTE sm_bAudio;
    BYTE bDevId;
    BYTE bRXInitPrm0;
    BYTE bVidInChannel;
    WORD wAudioTimeOut;
    WORD wVideoTimeOut;
    BYTE bInfoFrameTimeOut;
    BYTE bVideoPath;
    WORD wAudioOutputSelect;
    BYTE bShadowPixRepl;
    BYTE bIgnoreIntr;
    BYTE bHDCPFailFrmCnt;
    BYTE bHDCPStuckConfirmCnt;
    VideoFormatType VideoF;
    SysTimerType SysTimer;
//	DeepColorType DC_Info;      //move to AVIType (sync as Vlad's new API code)

} SiI_CtrlType;

typedef struct {
    BYTE bAudio;
    BYTE bIIC;
} ErrorType;

typedef struct {
    BYTE bRepresentation;         // Compressed, PCM, DSD
    BYTE bAccuracyAndFs;
    BYTE bLength;
    BYTE bNumberChannels;
}AudioStatusType;

typedef struct {

    BYTE bAVI_State;
    BYTE bInputColorSpace;
    BYTE bColorimetry;
    BYTE bPixRepl;
    BYTE bInputColorDepth;		//deep color API support
    BYTE bOutputColorDepth;		//Output color depth API support

}AVIType;

typedef struct {

    BYTE bVResId;
    AVIType AVI;
    BYTE bGlobStatus;
    BYTE bHDCPStatus;
    BYTE bNewInfoPkts;
    AudioStatusType AudioStatus;
    SyncInfoType Sync;
    BYTE bAudioErr;
    BYTE bIIC_Err;

} SiI_InfoType;

extern IRAM BYTE SiI_bWCode[ WRN_BUF_SIZE ];
extern IRAM BYTE SiI_bECode[ ERR_BUF_SIZE ];

extern IRAM SiI_InfoType SiI_Inf;
extern IRAM SiI_CtrlType SiI_Ctrl;


#endif // end _SII_GLOB_

