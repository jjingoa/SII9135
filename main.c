//------------------------------------------------------------------------------
// Module Name main
// Module Description: this file is used to call initalization of MCU, RX API
//                     call users tasks, including HDMI RX API, processing
//                     Audio Contant Protection (ACP) on user's level.
//
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------

#include "SiIGlob.h"
#include "SiIRX_API.h"
#include "UGlob.h"
#include "UInitMCU.h"
#include "UCfgRX.h"
#include "UCom.h"
#include "UKeyboard.h"

#ifdef _STD_C_
#pragma hdrstop
#endif
//---------------------------------------------------------------------------
// RX API Global data
//---------------------------------------------------------------------------
IRAM SiI_InfoType SiI_Inf;
IRAM SiI_CtrlType SiI_Ctrl;

IRAM BYTE SiI_bWCode[ WRN_BUF_SIZE ];
IRAM BYTE SiI_bECode[ ERR_BUF_SIZE ];

//---------------------------------------------------------------------------
// User Global data used for task management
//---------------------------------------------------------------------------
BOOL qReqTasksProcessing = FALSE; //  request to process user's tasks
WORD wTickCounter = 0;
WORD wNewTaskTickCounter = 0;
BYTE bNewTaskSlot = 0;

//---------------------------------------------------------------------------
// These global data are used in debugger mode
//---------------------------------------------------------------------------
IRAM BYTE RXBuffer[ RX_BUF_SIZE ];
BYTE bRxIndex, bCommState, bCommTO;
BOOL qBuffInUse, qFuncExe, qDebugModeOnlyF;

//------------------------------------------------------------------------------
// Function Name: userHDMItask
// Function Description:
//------------------------------------------------------------------------------
static void userHDMItask ( void ) {
BYTE bRX_ChEvents;
BYTE abRXParameters[8];
static BOOL qACPStatus = FALSE;

    SiI_RX_DoTasks( &bRX_ChEvents );

    if ( bRX_ChEvents & SiI_RX_API_GlobalStatus_Changed ) {
            SiI_RX_GetSystemInformation( abRXParameters );
            if (  (abRXParameters[6] & SiI_RX_GlobalHDMI_ACP) && ( !qACPStatus ) ){
                // SPDIF must be disabled
                qACPStatus = TRUE;
                SiI_RX_GetAudioOutputFormat( abRXParameters );
                // modify to disable SPDIF
                SiI_RX_SetAudioOutputFormat( (WORD) (abRXParameters[0] | abRXParameters[1] << 8) & (~SiI_RX_AOut_SPDIF) ,
                                             (WORD) (abRXParameters[2] | abRXParameters[3] << 8) ,
                                                    0x00,
													abRXParameters[5] );
            }
            else {
                if (  (!(abRXParameters[6] & SiI_RX_GlobalHDMI_ACP)) && qACPStatus  ){
                    qACPStatus = FALSE;
                    SiI_RX_GetAudioOutputFormat( abRXParameters );
                    // modify to enable SPDIF
                    SiI_RX_SetAudioOutputFormat( (WORD) (abRXParameters[0] | abRXParameters[1] << 8) | SiI_RX_AOut_SPDIF ,
                                                 (WORD) (abRXParameters[2] | abRXParameters[3] << 8) ,
                                                        0x00,
														abRXParameters[5] );
                }
            }
    }
}
//------------------------------------------------------------------------------
// Function Name:   main
// Function Description: call uinitilizations and infinite loop with user's tasks
//------------------------------------------------------------------------------

int main( void ) {


    qDebugModeOnlyF = FALSE;
    siiInitializeMCU();

    siiRXConfig();

    while ( 1 ){
        if ( qReqTasksProcessing ) {

            qReqTasksProcessing = FALSE;

            if ( !qDebugModeOnlyF ) {
                if ( bNewTaskSlot == TASK_HDMI_RX_API ) {
                    userHDMItask();
                }
                else if ( bNewTaskSlot == TASK_KEYBOARD ) {
                    siiKeyboardHandler();
                }
            }
            if ( bNewTaskSlot == TASK_COMM ) {
                    siiCommunicationHandler();
            }
        }
    }
    return 0;
}
//---------------------------------------------------------------------------

