//------------------------------------------------------------------------------
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------

#ifndef _MCUDEFS_
#define _MCUDEFS_

#include "reg89f.h"

// hardware resets of RX

sbit Reset_HDMIRX	= P0^1;

// Port Select
sbit PSEL_Pin		= P0^3;


// i2c ports

sbit DDC_SCL       = P1^4;
sbit DDC_SDA       = P1^5;
sbit SCL           = P1^6;
sbit SDA           = P1^7;


//-------------------------------------------------------------------------------
//    Audio Mux
sbit AudioSel0 = P2^2;
sbit AudioSel1 = P2^3;

sbit AudioSelAlt0 = P2^1;
sbit AudioSelAlt1 = P2^2;

//-------------------------------------------------------------------------------
sbit VideoFiltSelect_Pin = P2^1;
//    Audio DAC control pins (uned for AK DAC)
sbit PDN = P2^6;
sbit MUTE = P2^0;
sbit MUTE_AUX = P3^5;
sbit SOFTMUTE = P3^7;
//-------------------------------------------------------------------------------
sbit HPCh1Ctrl_Pin = P2^4;
sbit HPCh2Ctrl_Pin = P2^5;
sbit ACRSyncPin = P2^7;
//-------------------------------------------------------------------------------
sbit TXInt_Pin  = P3^3;
sbit RXInt_Pin  = P3^2;


sbit SELECT_Pin = P1^3;
sbit SelectChSw_Pin = P0^5;

#define OSC 11059200    /* Oscillator frequency of 11.0592 MHz */
#define REF_FREQ 92160000       // OSC/12 * 10 (mul by 10 to incr. resolution of VSync )

#endif

