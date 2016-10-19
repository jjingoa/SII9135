//------------------------------------------------------------------------------
// Module Name:SiISW_IIC.c
//
// Module Description: this module dedicated for low level IIC routines
//
//
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------
#include "SiISW_IIC.h"
#include "SiIHAL.h"


//-------------------------------------------------------------------------------
BYTE GetI2CStatus( void ){
BYTE Status;

    Status = 0;
    if( halGetSCLPin() )
        Status |= 0x01;
    if( halGetSDAPin() )
        Status |= 0x02;
    return Status;
}

//-------------------------------------------------------------------------------
BYTE GetI2CState( void ){
BYTE i,j;

    halSetSCLPin() ;
    for( i = 0; i < 10; i++ ){
        if( halGetSCLPin() ){
            halSetSDAPin();
            for( j = 0; j < 10; j++){
                if( halGetSDAPin() )
                    return 0;   // OK
            }
            return 1;      // SCL OK, SDA someone pull down
        }
    }
    return 2;          // error, someone holds the SCL bus
}

//-----------------------------------------------------------------------------------
void _I2CSCLHigh( void ) {       // set SCL high, and wait for it to go high
register int err;

    halSetSCLPin();
    while ( !halGetSCLPin() ){
        err++;
        if ( !err ) {
      //_i2c_error &= 0x02;     // SCL stuck, something's holding it down
            return;
        }
    }
}

//-------------------------------------------------------------------------------
// First I2C Port
BYTE I2CSendByte( BYTE bt ){
register unsigned char i;
unsigned char error=0; // if error =1 then there was an error in getting ACK

    for ( i = 0; i < 8; i++) {
        if (bt & 0x80)
            halSetSDAPin();      // send each bit, MSB first
        else
            halClearSDAPin();
        _I2CSCLHigh();
        halClearSCLPin() ;
        bt = bt << 1;
    }
    halSetSDAPin();                       // listen for ACK
    _I2CSCLHigh();
    if ( halGetSDAPin() )
        error=1;
    halClearSCLPin() ;
    return( error ); // return 0 if no error, else return 1
}
//------------------------------------------------------------------------------
BYTE I2CSendAddr( BYTE addr, BYTE rd ){
volatile unsigned char x = 0;		//YMA included wilma partial fix for PD issue
    halSetSCLPin() ;
	x++;
    halClearSDAPin();               // generate start
	x++;
    halClearSCLPin() ;
	x++;
    return I2CSendByte( addr+rd );  // send address byte
}
//----------------------------------------------------------------------------
BYTE _I2CGetByte(BYTE lastone) { // lastone == 1 for last byte
register unsigned char i, res;

    res = 0;
    for ( i = 0; i < 8; i++ ) {          // each bit at a time, MSB first

        _I2CSCLHigh();
        res *= 2;
        if ( halGetSDAPin() )
            res++;
        halClearSCLPin() ;

    }

    if ( lastone )
        halSetSDAPin();           // send ACK according to 'lastone'
    else
        halClearSDAPin();
    _I2CSCLHigh();
    halClearSCLPin();
    halSetSDAPin();
    return  res;
}

void I2CSendStop( void ){

    halClearSDAPin();
    _I2CSCLHigh();
    halSetSDAPin();

}
//-----------------------------------------------------------------------------
void MakeSCLPulses(BYTE Count ){
BYTE i;

    if(!Count)
        return;
    for(i = 1; i <=Count; i++){
        halSetSCLPin();
        halSetSCLPin();
        halClearSCLPin();
        halClearSCLPin();
     }
     halSetSCLPin();
     halSetSCLPin();
}

