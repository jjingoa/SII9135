//------------------------------------------------------------------------------
// Copyright © 2002-2005, Silicon Image, Inc.  All rights reserved.
//
// No part of this work may be reproduced, modified, distributed, transmitted,
// transcribed, or translated into any language or computer format, in any form
// or by any means without written permission of: Silicon Image, Inc.,
// 1060 East Arques Avenue, Sunnyvale, California 94085
//------------------------------------------------------------------------------

#include "SiITypeDefs.h"

#define SII_RD_AND_WR_NOAUTOINV 0x01

typedef enum {
    SiI_ReadAndWriteNoAutoInc = 0x01

}SiI_DemoLoaderCommands;

#define SII_LOADAR_MAP_ADDR 0x100

BYTE siiDemoTaskLoader( BYTE );

