//------------------------------------------------------------------------------
// Module Name: SiICom
//
// Module Description:  used for debugging RX system
//
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------
#include "UCom.h"
#include "UDebugHLIIC.h"
#include "SiIHAL.h"
#include "UMCU_IO.h"
#include "UGlob.h"
#include "SiISysCtrl.h"
#include "SiIRX_API.h"
#include "SiIHDMIRX.h"

#include "SiITTAudio.h"
#include "SiIVidF.h"
IRAM BYTE FuncRes[FUNC_RES_SIZE];
CmdType * CmdPtr;

//------------------------------------------------------------------------------
// Function Name: CommAccepted
// Function Description: Sends simple confirmation on received command
//------------------------------------------------------------------------------
static void CommAccepted( void ){

    if( halReadRXInt_Pin() )
        PutChar( COM_ACK );
    else
        PutChar( COM_ACK_SII_INTERRUPT );

}
//------------------------------------------------------------------------------
// Function Name: SendHandShake
// Function Description: Sends confirmation on received command
//------------------------------------------------------------------------------
static void SendHandShake( BYTE IICMDDCErrState){
BYTE bHandShake;

    if ( !IICMDDCErrState ){
        if ( halReadRXInt_Pin() )
            bHandShake = COM_ACK;
        else
            bHandShake = COM_ACK_SII_INTERRUPT;
    }
    else if ( IICMDDCErrState == IIC_CAPTURED)
        bHandShake = COM_ACK_IIC_CAPTUTED;
    else if ( IICMDDCErrState == IIC_NOACK)
        bHandShake = COM_ACK_IIC_NOACK;
    else if ( IICMDDCErrState == MDDC_NOACK)
        bHandShake = COM_ACK_MDDC_NOACK;
    PutChar( bHandShake );
}

//------------------------------------------------------------------------------
// Function Name: SendDataFrom8BAIICDevice
// Function Description: Sends data which has been reading from IIC device with 8 bit
//                       addressing mode.
//------------------------------------------------------------------------------
static void SendDataFrom8BAIICDevice( void ) {
BYTE i; BYTE bCheckSum, bState;

    bCheckSum = 0;
    bState = BlockRead_8BA(&CmdPtr->I2CCommand);
    SendHandShake( bState );
    if( !bState ) {// no errors
        for ( i = 0; i < CmdPtr->I2CCommand.NBytes; i++ ) {
            bCheckSum += CmdPtr->I2CCommand.Data[i];
                 PutChar(CmdPtr->I2CCommand.Data[i]);
        }
        PutChar( bCheckSum );
    }
}
//------------------------------------------------------------------------------
// Function Name: WriteDataTo8BAIICDevice
// Function Description: Writes data to IIC device with 8 bit addressing mode.
//------------------------------------------------------------------------------
static void WriteDataTo8BAIICDevice( void ) {
BYTE bState;

    bState = BlockWrite_8BA((I2CCommandType *)&CmdPtr->I2CCommand);
    SendHandShake( bState );

}
//------------------------------------------------------------------------------
// Function Name: WriteDataTo16BAIICDevice
// Function Description: Writes data to IIC device with 16 bit addressing mode.
//                       this device addressing mode used for "big" EEPROMs
//------------------------------------------------------------------------------
#ifdef _BIGEEPROM_

static void WriteDataTo16BAIICDevice( void ) {
BYTE bState;

    bState = BlockWrite_16BA((I2CCommandType *)&CmdPtr->I2CCommand);
    SendHandShake( bState );
}

//------------------------------------------------------------------------------
// Function Name: SendDataFrom16BAIICDevice
// Function Description: Sends data which has been reading from IIC device with 16 bit
//                       addressing mode. This address mode is used for big IIC EEPROMS
//------------------------------------------------------------------------------
static void SendDataFrom16BAIICDevice( void ){
BYTE i; BYTE bCheckSum, bState;

    bCheckSum = 0;
    bState = BlockRead_16BA( &CmdPtr->I2CCommand );
    SendHandShake( bState );
    if( !bState ){
        for(i = 0; i < CmdPtr->I2CCommand.NBytes; i++) {
            bCheckSum += CmdPtr->I2CCommand.Data[i];
            PutChar(CmdPtr->I2CCommand.Data[i]);
        }
        PutChar( bCheckSum );
    }
}

#endif  // end _BIGEEPROM_
//------------------------------------------------------------------------------
// Function Name: SendResultOfFunction
// Function Description: Sends function result through UART
//------------------------------------------------------------------------------
static void SendResultOfFunction( void ){
BYTE bCheckSum, i;

    bCheckSum = 0;
    for (i = 0; i < CmdPtr->FuncCommand.NBytes; i++){
        bCheckSum +=  FuncRes[i];
        PutChar( FuncRes[i]);
    }
    PutChar( bCheckSum );
}

//------------------------------------------------------------------------------
// Function Name: ClearFuncBuff
// Function Description: ckears function result buffer
//------------------------------------------------------------------------------
static void ClearFuncBuff( void ){
BYTE i;

    for ( i = 0; i < FUNC_RES_SIZE; i++)
        FuncRes[i] = 0;
}
//------------------------------------------------------------------------------
// Function Name: ParseCommand
// Function Description: this function is used for parsing of command which received
//                       trough UART interface
//------------------------------------------------------------------------------
static void ParseCommand( void ){

    if( CmdPtr->cmdbuf[0] >= BEG_FUNC_CALLS ) { // check for function space Id

        ClearFuncBuff();
        if( CmdPtr->cmdbuf[0] != FUNC_RESULT )

        switch( CmdPtr->cmdbuf[0] ) {// command decoding
            case CmdGetGPIO:
                        CommAccepted();
                        qFuncExe = TRUE;
                        qBuffInUse = FALSE;
                        siiReadGPIO( FuncRes );
                        qFuncExe = FALSE;
                        break;
            case CmdSendGPIO:
                        CommAccepted();
                        siiWriteGPIO( &CmdPtr->FuncCommand.Data[0] );
                        break;
            case MakeRecoveryClock:
                        CommAccepted();
                        DoRecoverySCLs ( );
                        break;
            case RXAPI_InitializeSystem:
                        CommAccepted();
						siiTurnAudioOffAndSetSM_AudioOff();
						siiMuteVideo(ON);
                        FuncRes[0] = SiI_RX_InitializeSystem ( &CmdPtr->FuncCommand.Data[0] );
                        break;
            case RXAPI_SetVideoInput:
                        CommAccepted();
                        FuncRes[0] = SiI_RX_SetVideoInput (CmdPtr->FuncCommand.Data[0]);
                        break;
            case RXAPI_GetVideoFormat:
                        CommAccepted();
                        FuncRes[0] = SiI_RX_GetVideoOutputFormat (&FuncRes[1]);
                        break;
            case RXAPI_GetVideoInputResolution:
                        CommAccepted();
                        FuncRes[0] = SiI_RX_GetVideoInputResolution (&FuncRes[1]);
                        break;
            case RXAPI_SetVideoFormat:
                        CommAccepted();
                        FuncRes[0] = SiI_RX_SetVideoOutputFormat (
                                    CmdPtr->FuncCommand.Data[0],
                                    CmdPtr->FuncCommand.Data[1],
                                    CmdPtr->FuncCommand.Data[2],
                                    CmdPtr->FuncCommand.Data[3]
                                    );
                        break;
            case RXAPI_SetGlobalPower:
                        CommAccepted();
                        FuncRes[0] = SiI_RX_GlobalPower (CmdPtr->FuncCommand.Data[0]);
                        break;
            case RXAPI_SetAudioVideoMute:
                        CommAccepted();
                        FuncRes[0] = SiI_RX_SetAudioVideoMute (CmdPtr->FuncCommand.Data[0]);
                        break;
            case RXAPI_GetAPIInfo:
                        CommAccepted();
                        FuncRes[0] = SiI_RX_GetAPI_Info ( &FuncRes[1] );
                        break;
            case RXAPI_GetSystemInformation:
                        CommAccepted();
                        FuncRes[0] = SiI_RX_GetSystemInformation ( &FuncRes[1] );
                        break;
            /* Command has been removed from API 1.0 specification
            case RXAPI_GetTasksSchedule:
                        CommAccepted();
                        FuncRes[0] = SiI_RX_GetTasksSchedule ( &FuncRes[1] );
                        break;
            */
            case RXAPI_GetAudioInputStatus:
                        CommAccepted();
                        FuncRes[0] = SiI_RX_GetAudioInputStatus( &FuncRes[1] );
                        break;
            case RXAPI_GetNCTS:
                        FuncRes[0] = SiI_Diagnostic_GetNCTS (  &FuncRes[1] );
                        CommAccepted();
                        break;
            case RXAPI_GetABKSV:
                        FuncRes[0] = SiI_Diagnostic_GetABKSV (  &FuncRes[1] );
                        CommAccepted();
                        break;
            case RXAPI_GetAudioOutputFormat:
                        FuncRes[0] = SiI_RX_GetAudioOutputFormat ( &FuncRes[1] );
                        CommAccepted();
                        break;
            case RXAPI_SetAudioOutputFormat:
                        CommAccepted();
                        FuncRes[0] = SiI_RX_SetAudioOutputFormat ( (WORD) ( CmdPtr->FuncCommand.Data[0] | (CmdPtr->FuncCommand.Data[1] << 8 )),
                                                                   (WORD) ( CmdPtr->FuncCommand.Data[2] | (CmdPtr->FuncCommand.Data[3] << 8 )),
                                                                            CmdPtr->FuncCommand.Data[4],CmdPtr->FuncCommand.Data[5] //YMA 2 add DSDHBRformat
                                                                 );
                        break;

            case RXAPI_GetIPacket:
                        FuncRes[0] = SiI_RX_GetPackets ( CmdPtr->FuncCommand.Data[0], &FuncRes[1] );
                        CommAccepted();
                        break;
            case API_GetWarningData:
                        FuncRes[0] = SiI_GetWarnings( &FuncRes[1] );
                        CommAccepted();
                        break;
            case API_GetErrorData:
                        FuncRes[0] = SiI_GetErrors( &FuncRes[1] );
                        CommAccepted();

                        break;
            case API_GetLastAPI_ExeTime:
                        CommAccepted();
                        FuncRes[0] = SiI_Diagnostic_GetAPIExeTime( &FuncRes[1] );
                        break;
            default:

                        PutChar(COMMAND_NOT_SUPPORTED);
          }
    }
    else if(CmdPtr->cmdbuf[0]==FUNC_RESULT){
            CommAccepted();
            SendResultOfFunction();
    }
    else {
        switch( CmdPtr->cmdbuf[0] ) {// command decoding


            case  IIC8BARead:
                        SendDataFrom8BAIICDevice();
                        break;
            case  IIC16BARead:
#ifdef _BIGEEPROM_
                        SendDataFrom16BAIICDevice();
#else
                        PutChar(COMMAND_NOT_SUPPORTED);
#endif
                        break;
            case  IIC8BAWrite:
                        WriteDataTo8BAIICDevice();
                        break;
            case  IIC16BAWrite:
#ifdef _BIGEEPROM_
                        WriteDataTo16BAIICDevice();
#else
                        PutChar(COMMAND_NOT_SUPPORTED);
#endif
                        break;

            case  ResetRX:
                        CommAccepted();
                        siiRXHardwareReset();
                        break;
            case  VersionInfo:
                        break;

            case  SetPassiveMode:
                        CommAccepted();
                        qDebugModeOnlyF = TRUE;

                        break;
            case  ResetPassiveMode:
                        CommAccepted();
                        qDebugModeOnlyF = FALSE;

                        break;

            default:  PutChar(COMMAND_NOT_SUPPORTED);
        }

   }
   qBuffInUse = FALSE;
}
//------------------------------------------------------------------------------
// Function Name: GetCommand
// Function Description: receives command, makes check sum check
//------------------------------------------------------------------------------
static BOOL GetCommand( void ){
BYTE bCommandLength, bCheckSum, i;
BOOL qResult = FALSE;

    if ( RXBuffer[0] & 0x80 )
        bCommandLength = RXBuffer[1] + 6; // 6 is header length
    else
        bCommandLength = 6;
    if( bRxIndex >= RX_BUF_SIZE){ // PC speed is too fast, it sent more BYTEs than
                                  // processed by MCU
        bRxIndex = 0; bCommState = WaitStartRX; bCommTO = 0;
    }
    else if((bCommandLength + 1 + 1) == bRxIndex){  // it's good, but need to check bCheckSum anyway

        qBuffInUse = TRUE;
        bCheckSum = 's';
        bRxIndex = 0; bCommState = WaitStartRX; bCommTO = 0;
        CmdPtr = (CmdType *)&RXBuffer[0];

        for ( i = 0; i <= bCommandLength; i++)
            bCheckSum += RXBuffer[i];
        if ( bCheckSum == RXBuffer[bCommandLength + 1] )
            qResult = TRUE;
        else
            qBuffInUse = FALSE;
    }
    return qResult;

}
//------------------------------------------------------------------------------
// Function Name: siiCommunicationHandler
// Function Description: this checks if commad was received makes parsing and
//                       executing
// Accepts: none
// Returns: none
// Globals: none
//------------------------------------------------------------------------------
void siiCommunicationHandler( void ){
    if( GetCommand() )
        ParseCommand();
}

