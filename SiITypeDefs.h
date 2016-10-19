//------------------------------------------------------------------------------
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------

#include "SiICmplDefs.h"
#ifndef _TYPEDEFS_
#define _TYPEDEFS_

#include "typedef.h"


//typedef unsigned char  BYTE;
typedef unsigned char  U8BIT;
//typedef unsigned short int WORD;
typedef unsigned short int U16BIT;
typedef unsigned long U32BIT;
//typedef unsigned long DWORD;

#ifdef _8051_   // for 8051 family of microcontrollers

#define ROM   code       // 8051 type of ROM memory
#define IRAM  idata      // 8051 type of RAM memory

//typedef  bit BOOL;

#else

typedef unsigned char BOOL;
#define ROM
#define IRAM

#endif

#define FALSE  0
#define TRUE  1

#define ABSENT   0
#define PRESENT  1


#endif


