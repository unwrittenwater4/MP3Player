;*******************************************************************
;   AT89C51RC2 Special Function Registers
;*******************************************************************
;
;******* System ****************
ACC	    DATA	0xE0
B	    DATA	0xF0
SP	    DATA	0x81
DPL	    DATA	0x82
DPH	    DATA	0x83
PCON	DATA	0x87
PSW	    DATA	0xD0
AUXR        DATA        0x8E
AUXR1	DATA	0xA2
;------- Bit Addressable -------
CY	    BIT	    0xD7
AC	    BIT	    0xD6
F0	    BIT	    0xD5
RS1	    BIT	    0xD4
RS0	    BIT	    0xD3
OV	    BIT	    0xD2
F1	    BIT	    0xD1
P	    BIT	    0xD0
;*****CLOCK CONTROL************
CKRL        DATA        0x97
CKCON0      DATA        0x8F
CKCON1      DATA        0xAF
;******* Ports *****************
P0	    DATA	0x80
P1	    DATA	0x90
P2          DATA        0xA0
P3	    DATA	0xB0
;******* Serial Port ***********
SCON	DATA	0x98
SBUF	DATA	0x99
SADDR	DATA	0xA9
SADEN	DATA	0xB9
BDRCON  DATA    0x9B
BRL     DATA    0x9A
;SCON---- Bit Addressable -------
FE	    BIT	    0x9F
SM0	    BIT	    0x9F
SM1	    BIT	    0x9E
SM2	    BIT	    0x9D
REN	    BIT	    0x9C
TB8	    BIT	    0x9B
RB8	    BIT	    0x9A
TI	    BIT	    0x99
RI	    BIT	    0x98
;******* Timers ****************
TCON	DATA	0x88
TMOD	DATA	0x89
TL0	    DATA	0x8A
TH0	    DATA	0x8C
TL1	    DATA	0x8B
TH1	    DATA	0x8D
T2CON       DATA        0xC8
T2MOD       DATA        0xC9
TL2         DATA        0xCC
TH2         DATA        0xCD
RCAP2L      DATA        0xCA
RCAP2H      DATA        0xCB
;------- Bit Addressable -------
TF1	    BIT	    0x8F
TR1	    BIT	    0x8E
TF0	    BIT	    0x8D
TR0	    BIT	    0x8C
IE1	    BIT	    0x8B
IT1	    BIT	    0x8A
IE0	    BIT	    0x89
IT0	    BIT	    0x88
TF2         BIT     0xCF
EXF2        BIT     0xCE
RCLK        BIT     0xCD
TCLK        BIT     0xCC
EXEN2       BIT     0xCB
TR2         BIT     0xCA
C_T2        BIT     0xC9
CP_RL2      BIT     0xC8
;******* Watchdog **************
WDTRST	    DATA	0xA6
WDTPRG	DATA	0xA7
;******* Interrupts ************
IEN0	DATA	0xA8
IEN1	DATA	0xB1
IPL0	    DATA	0xB8
IPH0	DATA	0xB7
IPL1	    DATA	0xB2
IPH1	DATA	0xB3
;------- Bit Addressable -------
EA	    BIT	    0xAF
EC	BIT	    0xAE
ET2         BIT     0xAD
ES	    BIT	    0xAC
ET1	    BIT	    0xAB
EX1	    BIT	    0xAA
ET0	    BIT	    0xA9
EX0	    BIT	    0xA8
PPCL	BIT	    0xBE
PT2L         BIT     0xBD
PLS	    BIT	    0xBC
PT1L	    BIT	    0xBB
PX1L	    BIT	    0xBA
PT0L	    BIT	    0xB9
PX0L	    BIT	    0xB8
PPCH	BIT	    0xB6
PT2H         BIT     0xB5
PHS	    BIT	    0xB4
PT1H	    BIT	    0xB3
PX1H	    BIT	    0xB2
PT0H	    BIT	    0xB1
PX0H	    BIT	    0xB0
;****PROGRAMMABLE COUNTER ARRAY****
CCON       DATA     0xD8
CMOD       DATA     0xD9
CL         DATA     0xE9
CH         DATA     0xF9
CCAPM0     DATA     0xDA
CCAPM1     DATA     0xDB
CCAPM2     DATA     0xDC
CCAPM3     DATA     0xDD
CCAPM4     DATA     0xDE
CCAP0L     DATA     0xEA
CCAP1L     DATA     0xEB
CCAP2L     DATA     0xEC
CCAP3L     DATA     0xED
CCAP4L     DATA     0xEE
CCAP0H     DATA     0xFA
CCAP1H     DATA     0xFB
CCAP2H     DATA     0xFC
CCAP3H     DATA     0xFD
CCAP4H     DATA     0xFE  
;------- Bit Addressable -------
CF        BIT      0xDF
CR        BIT      0xDE

CCF4      BIT      0xDC
CCF3      BIT      0xDB
CCF2      BIT      0xDA
CCF1      BIT      0xD9
CCF0      BIT      0xD8
;*******SPI*************
SPCON     DATA     0xC3
SPSTA     DATA     0xC4
SPDAT     DATA     0xC5
;****KEYBOARD INTERFACE***
KBLS      DATA     0x9C
KBE       DATA     0x9D
KBF       DATA     0x9E











