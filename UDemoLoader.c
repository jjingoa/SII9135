//------------------------------------------------------------------------------
// Module Name: DemoLoader
//
// Module Description:
// 1. Search for key linked data module
// 2. Reading command
// 3. Executing command
//
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------
#include <stdio.h>


#include "UDemoloader.h"
#include "UEEPROM.h"

//------------------------------------------------------------------------------
// Function Name:   SearchAddressOfSelectedModule
// Function Description:  Search for module selected by switcher through EEPROM
//                        every module contains 512 bytes of data
//                        if module found return module id, otherwise 0xFF
//------------------------------------------------------------------------------
BYTE SearchAddressOfSelectedModule ( BYTE bSwitchCode, WORD * wpLoaderModuleAddress ){
BYTE abData[3];
WORD wLoaderMapAddr;
WORD wLoaderModuleAddress = 0;
BYTE bLoaderMapSize;
BYTE bError;
BOOL qFound = FALSE;

BYTE i;

    wLoaderMapAddr = SII_LOADAR_MAP_ADDR;
    bError = siiBlockReadEEPROM ( wLoaderMapAddr++, 1, &bLoaderMapSize );
    if ( (!bError) && ( bLoaderMapSize < 64 ) ) {
        for ( i = 0; i < bLoaderMapSize; i++ ){
            siiBlockReadEEPROM ( wLoaderMapAddr, 3, abData );
            if ( abData[0] == bSwitchCode ){
                qFound = TRUE;
                *wpLoaderModuleAddress = abData[1] | ( abData[2] << 8);
                break;
            }
            wLoaderMapAddr +=3;
        }
    }
    if (!qFound )
        bError = 0xFF;
    return bError;
}
//------------------------------------------------------------------------------
// Function Name:  ExecuteI2C_NoAutoInc_Command
// Function Description:  SiI_ReadAndWriteNoAutoInc command read data from EEPROM
//                        and sends to I2C device
//
//------------------------------------------------------------------------------
BYTE ExecuteI2C_NoAutoInc_Command( WORD * wpCommandAddress ){

BYTE abData[16], i, NBytes, bError = FALSE;
I2CShortCommandType I2C_Cmd;

    bError = siiBlockReadEEPROM ( * wpCommandAddress, 3, abData );
    if ( !bError ) {

        I2C_Cmd.SlaveAddr = abData[0];
        I2C_Cmd.Flags = 0;
        I2C_Cmd.NBytes = abData[2];
        I2C_Cmd.RegAddrL = abData[1];
        I2C_Cmd.RegAddrH = 0;
        * wpCommandAddress += 3; // move address on data area
        bError = siiBlockReadEEPROM ( * wpCommandAddress, I2C_Cmd.NBytes, abData );
        if ( !bError ) {
            NBytes = I2C_Cmd.NBytes;
            I2C_Cmd.NBytes = 1;
            for ( i = 0; i < NBytes; i++) {
                bError = hlBlockWrite_8BAS((I2CShortCommandType *)&I2C_Cmd, &abData[i] );
                I2C_Cmd.RegAddrL++;
            }
        }
    }
    * wpCommandAddress += NBytes; // Move address on next command
    return bError;
}
//------------------------------------------------------------------------------
// Function Name:  ExecuteMoodule
// Function Description:  Get Demo Loader commad and call execution of the command
//                        if last command is 0xFF, then job has done, errors
//                        terminates function
//------------------------------------------------------------------------------
BOOL ExecuteMoodule( WORD wModuleAddress ){
BYTE bCommand, bError = FALSE;


    do {
        bError = siiBlockReadEEPROM ( wModuleAddress++, 1, &bCommand );
        if ( bCommand == SiI_ReadAndWriteNoAutoInc ) {
            bError = ExecuteI2C_NoAutoInc_Command( &wModuleAddress );
        }
    }
    while ( (bCommand != 0xFF) && (!bError) );
    if ( bError )
        printf ("Errors");
    else
        printf ("Done");
    return bError;
}
//------------------------------------------------------------------------------
// Function Name: siiDemoTaskLoader
// Function Description: Call searching of Demo laoder command, call command execution
//
// Accepts: none
// Returns: BYTE
// Globals: none
//------------------------------------------------------------------------------
BYTE siiDemoTaskLoader( BYTE bSwCode ){
WORD wModuleAddress;
BYTE bError;
    printf ("\n Start demo loader: ");

    bError = SearchAddressOfSelectedModule( bSwCode, &wModuleAddress );
    printf (" Switch %i ", (int) bSwCode );
    if ( !bError ){ // modume address cannot be Zero
        printf ( " Starting demo...");
        bError = ExecuteMoodule( wModuleAddress );
    }
    else {
        printf ("Demo not found\n");
    }

    return bError;
}

