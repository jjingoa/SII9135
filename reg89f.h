/*--------------------------------------------------------------------------
REG89F.H

Header file for SST89F58.


--------------------------------------------------------------------------*/

/*  BYTE Registers  */
sfr P0    = 0x80;
sfr P1    = 0x90;
sfr P2    = 0xA0;
sfr P3    = 0xB0;
sfr PSW   = 0xD0;
sfr ACC   = 0xE0;
sfr B     = 0xF0;
sfr SP    = 0x81;
sfr DPL   = 0x82;
sfr DPH   = 0x83;
sfr PCON  = 0x87;
sfr TCON  = 0x88;
sfr TMOD  = 0x89;
sfr TL0   = 0x8A;
sfr TL1   = 0x8B;
sfr TH0   = 0x8C;
sfr TH1   = 0x8D;
sfr IE    = 0xA8;
sfr IP    = 0xB8;
sfr SCON  = 0x98;
sfr SBUF  = 0x99;

/* SST89F specific registers */
sfr SFCF = 0xF7;  // SuperFlash Configuration/Status
sfr SFDT = 0xF8;  // SuperFlash Data
sfr SFAL = 0xF9;  // SuperFlash Address Low
sfr SFAH = 0xFA;  // SuperFlash Address High
sfr SFCM = 0xFB;  // SuperFlash Command
sfr WDTC = 0xC0;  // Watchdog timer Control
sfr WDTD = 0x86;  // Watchdog Timer Data/Reload

/*  BIT Registers for SST89F  */
/*  WDTC - Watchdog timer control  */
sbit WDRE = 0xC3;
sbit WDTS = 0xC2;
sbit WDT = 0xC1;
sbit SWDT = 0xC0;


/*  8052 Extensions  */
sfr T2CON = 0xC8;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2   = 0xCC;
sfr TH2   = 0xCD;


/*  BIT Registers  */
/*  PSW  */
sbit CY    = 0xD7;
sbit AC    = 0xD6;
sbit F0    = 0xD5;
sbit RS1   = 0xD4;
sbit RS0   = 0xD3;
sbit OV    = 0xD2;
sbit P     = 0xD0;

/*  TCON  */
sbit TF1   = 0x8F;
sbit TR1   = 0x8E;
sbit TF0   = 0x8D;
sbit TR0   = 0x8C;
sbit IE1   = 0x8B;
sbit IT1   = 0x8A;
sbit IE0   = 0x89;
sbit IT0   = 0x88;

/*  IE  */
sbit EA    = 0xAF;
sbit ES    = 0xAC;
sbit ET1   = 0xAB;
sbit EX1   = 0xAA;
sbit ET0   = 0xA9;
sbit EX0   = 0xA8;

/*  IP  */
sbit PS    = 0xBC;
sbit PT1   = 0xBB;
sbit PX1   = 0xBA;
sbit PT0   = 0xB9;
sbit PX0   = 0xB8;

/*  P3  */
sbit RD    = 0xB7;
sbit WR    = 0xB6;
sbit T1    = 0xB5;
sbit T0    = 0xB4;
sbit INT1  = 0xB3;
sbit INT0  = 0xB2;
sbit TXD   = 0xB1;
sbit RXD   = 0xB0;

/*  SCON  */
sbit SM0   = 0x9F;
sbit SM1   = 0x9E;
sbit SM2   = 0x9D;
sbit REN   = 0x9C;
sbit TB8   = 0x9B;
sbit RB8   = 0x9A;
sbit TI    = 0x99;
sbit RI    = 0x98;

/*  8052 Extensions  */
/*  IE  */
sbit ET2   = 0xAD;

/*  IP  */
sbit PT2   = 0xBD;

/*  P1  */
sbit T2EX  = 0x91;
sbit T2    = 0x90;
             
/*  T2CON  */
sbit TF2   = 0xCF;
sbit EXF2  = 0xCE;
sbit RCLK  = 0xCD;
sbit TCLK  = 0xCC;
sbit EXEN2 = 0xCB;
sbit TR2   = 0xCA;
sbit C_T2  = 0xC9;
sbit CP_RL2= 0xC8;


