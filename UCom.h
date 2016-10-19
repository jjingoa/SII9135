//------------------------------------------------------------------------------
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------

#include "SiITypeDefs.h"

#ifndef _SII_COM_
#define _SII_COM_

typedef struct {
    BYTE Dummy;
    BYTE NBytes;
    BYTE Flags;
    BYTE Ctrl;
    BYTE SlaveAddr;
    BYTE RegAddrL;
    BYTE RegAddrH;
    BYTE Data[16];
} I2CCommandType;


typedef struct {
    BYTE Cmd;
    BYTE NumberBytes;
    BYTE Flags;
    BYTE Ctrl;
    BYTE SlaveAddr;
    BYTE DestAddrL;
    BYTE DestAddrH;
    BYTE Data[16];
}DemoCPCmdType;
//--------------------------------------------------------------------
typedef struct {
    BYTE Cmd;
    BYTE notused1;
    BYTE notused2;
    BYTE Ctrl;
    BYTE notused4;
    BYTE notused5;
} ResetControlType;
//--------------------------------------------------------------------
typedef struct {
    BYTE Cmd;
    BYTE notused1;
    BYTE notused2;
    BYTE notused3;
    BYTE notused4;
    BYTE notused5;
    BYTE Data[1];

} MiscControlType;
//---------------------------------------------------------------------
typedef struct {
    BYTE Dummy;
    BYTE NBytes;
    BYTE Flags;
    BYTE Ctrl;
    BYTE SlaveAddr;
    BYTE RegAddrL;
    BYTE RegAddrH;
    BYTE Data[16];
} FuncCommandType;

//---------------------------------------------------------------------
typedef union  CmdUnion {

    BYTE cmdbuf[24];

    I2CCommandType I2CCommand;
    FuncCommandType FuncCommand;
    ResetControlType ResetControl;
    MiscControlType MiscControl;

} CmdType;

#define BEG_FUNC_CALLS 0xA0
#define FUNC_RESULT 0x7F


#define NO_ACK_FROM_IIC_DEV 0xF1
#define COMMAND_NOT_SUPPORTED 0xAA

#define COM_ACK 0xFF
#define COM_ACK_SII_INTERRUPT 0xFE
#define COM_ACK_IIC_CAPTUTED  0xF0
#define COM_ACK_IIC_NOACK     0xF1
#define COM_ACK_MDDC_CAPTUTED 0xF3
#define COM_ACK_MDDC_NOACK    0xF4


#define FLG_SHORT 0x01 // Used for Ri Short Read
#define FLG_NOSTOP 0x02 // Don't release IIC Bus
#define FLG_CONTD 0x04 // Continued from previous operation

#define MDDC_READ  1
#define MDDC_WRITE 0



typedef enum {

    IIC8BARead,
    IIC10BARead,
    IIC16BARead,
    SystemState,
    VersionInfo,
    IIC8BAWrite = 0x80,
    IIC10BAWrite,
    IIC16BAWrite,
    Resets,
    SetPassiveMode,
    ResetPassiveMode,
    Syncronyze,
    GetErr,
    ResetRX,
    RXAPI_GetNCTS = 0xDB,
    RXAPI_GetABKSV = 0xDC,
    RXAPI_GetIPacket = 0xDD,
    RXAPI_GetVideoInputResolution = 0xDE,
    API_GetLastAPI_ExeTime = 0xDF,
    RXAPI_InitializeSystem = 0xE0,
    RXAPI_GetVersionInfo =  0xE1,
    RXAPI_SetVideoFormat =  0xE2,
    RXAPI_GetVideoFormat =  0xE3,
    RXAPI_GetInfo =         0xE4,
    RXAPI_SetGlobalPower =     0xE5,
    RXAPI_SetAudioVideoMute =  0xE6,
    RXAPI_GetAPIInfo =      0xE7,
    RXAPI_GetSystemInformation = 0xE8,
    RXAPI_GetTasksSchedule =    0xE9,
    RXAPI_SetMasterClock =      0xEA,
    RXAPI_GetAudioInputStatus = 0xEB,
    RXAPI_GetAudioOutputFormat = 0xEC,
    RXAPI_SetAudioOutputFormat = 0xED,
    RXAPI_SetVideoInput = 0xEE,
    API_GetWarningData = 0xEF,
    API_GetErrorData = 0xF0,

    CmdGetGPIO = 0xF1,
    CmdSendGPIO = 0xF2,
    TestSyncSWRst = 0xF3,
    TestPLLId = 0xF4,
    TX_AudioPath = 0xF5,
    AVIInfo = 0xF7,
    TX_VideoPath = 0xF8,
    TX_DE_656_AudioPresetCfg = 0xF9,
    TXVideoAudioCfg = 0xFA,
    MakeRecoveryClock = 0xFB,
    GetAudioStatData = 0xFC,
    GoAudioStatTest = 0xFD,
    OutVCfg = 0xFE,
    GetTimingPrms = 0xFF
} CommandId;

#define FUNC_RES_SIZE 33 // in bytes

void siiCommunicationHandler( void );

#endif

