//------------------------------------------------------------------------------
// Module Name: SiIHLVIIC
//
// Module Description:  high level i2c routines
//
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------
#include "SiIHLVIIC.h"
#include "SiISW_IIC.h"
#include "SiIIICDefs.h"
#include "SiIHAL.h"


//------------------------------------------------------------------------
BOOL hlWaitForAck( BYTE bSlvAddr, WORD wTimeOut ){
BYTE bError;
BOOL qResult = FALSE;

    do {

        bError = I2CSendAddr( bSlvAddr, WRITE );
        I2CSendStop();

        if ( !bError ){
            qResult = TRUE;
            break;
        }
        halDelayMS( 1 );
    } while ( wTimeOut-- );
    return qResult;
}


//------------------------------------------------------------------------------------
BYTE hlBlockRead_8BAS( I2CShortCommandType * IIC, BYTE * Data ) {
BYTE i, bState;

        if(!(IIC->Flags & FLG_CONTD)) {
            bState = GetI2CState();
            if(bState){
                return IIC_CAPTURED;
            }
            bState = I2CSendAddr(IIC->SlaveAddr,WRITE);
            if(bState){
                I2CSendStop();
                return IIC_NOACK;
            }
            bState = I2CSendByte(IIC->RegAddrL);
            if(bState) {
                I2CSendStop();
                return IIC_NOACK;
            }
            bState = I2CSendAddr (IIC->SlaveAddr,READ);
            if(bState) {
                I2CSendStop();
                return IIC_NOACK;
            }
        }
        for (i = 0; i < IIC->NBytes - 1; i++)
            Data[i] = I2CGetByte();
        if(IIC->Flags & FLG_NOSTOP) {
            Data[i] = I2CGetByte();
        }
        else {
            Data[i] = I2CGetLastByte();
            I2CSendStop();
        }
        return IIC_OK;

}

//------------------------------------------------------------------------------------

BYTE hlBlockWrite_8BAS( I2CShortCommandType * IIC, BYTE * Data ){
BYTE i, bState;

        if(!(IIC->Flags & FLG_CONTD)) {
            bState = GetI2CState();
            if( bState )
                return IIC_CAPTURED;
            bState = I2CSendAddr(IIC->SlaveAddr,WRITE);
            if( bState ){
                I2CSendStop();
                return IIC_NOACK;
            }
            bState = I2CSendByte(IIC->RegAddrL);
            if(bState){
                I2CSendStop();
                return IIC_NOACK;
            }
        }
        for (i=0; i<IIC->NBytes; i++)
            I2CSendByte(Data[i]);
        if(!(IIC->Flags & FLG_NOSTOP))
            I2CSendStop();
        return 0;

}
//-------------------------------------------------------------------
BYTE hlReadByte_8BA ( BYTE SlaveAddr, BYTE RegAddr ){
BYTE Data;

        I2CSendAddr(SlaveAddr,WRITE);
        I2CSendByte(RegAddr);

        I2CSendAddr (SlaveAddr,READ);
        Data = I2CGetLastByte();
        I2CSendStop();
        return Data;
}

//--------------------------------------------------------------------

WORD hlReadWord_8BA( BYTE SlaveAddr, BYTE RegAddr ) {
WORD Data;

        I2CSendAddr( SlaveAddr, WRITE );
        I2CSendByte( RegAddr++);

        I2CSendAddr (SlaveAddr, READ );
        Data = I2CGetByte();
        Data |= (I2CGetLastByte() << 8 );
        I2CSendStop();
        return Data;
}


//-------------------------------------------------------------------
void hlWriteByte_8BA ( BYTE SlaveAddr, BYTE RegAddr, BYTE Data ) {

        I2CSendAddr(SlaveAddr,WRITE);
        I2CSendByte(RegAddr);
        I2CSendByte(Data);
        I2CSendStop();

}
//-------------------------------------------------------------------

void hlWriteWord_8BA( BYTE SlaveAddr, BYTE RegAddr, WORD Data ){

        I2CSendAddr(SlaveAddr,WRITE);
        I2CSendByte(RegAddr);
        I2CSendByte(Data & 0xff);
        I2CSendByte(Data >> 8);
        I2CSendStop();

}


