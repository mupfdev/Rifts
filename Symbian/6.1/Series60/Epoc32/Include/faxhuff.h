// FAXHUFF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__FAXHUFF_H__)
#define __FAXHUFF_H__

#define KFaxBlack 0		// Mask for CFbsBitmap bytes
#define KFaxWhite 0xFF	// Reversing gives a negative image

typedef TUint32 TCodeDef;
#define HUFF(len,bits) (TUint(len)<<16)|(bits)
#define HUFFLEN(def) (TUint(def)>>16)
#define HUFFBITS(def) (TUint(def)<<16)

const TCodeDef KCodes[] =
	{
	// interleaved black/white runs
	HUFF(10,0x0dc0),  // 0 black = 10 bit code is 0000110111
	HUFF(8,0x3500),// 0 white = 8 bit code is 00110101
	HUFF(3,0x4000),// 1 black = 3 bit code is 010
	HUFF(6,0x1c00),// 1 white = 6 bit code is 000111
	HUFF(2,0xc000),// 2 black = 2 bit code is 11
	HUFF(4,0x7000),// 2 white = 4 bit code is 0111
	HUFF(2,0x8000),// 3 black = 2 bit code is 10
	HUFF(4,0x8000),// 3 white = 4 bit code is 1000
	HUFF(3,0x6000),// 4 black = 3 bit code is 011
	HUFF(4,0xb000),// 4 white = 4 bit code is 1011
	HUFF(4,0x3000),// 5 black = 4 bit code is 0011
	HUFF(4,0xc000),// 5 white = 4 bit code is 1100
	HUFF(4,0x2000),// 6 black = 4 bit code is 0010
	HUFF(4,0xe000),// 6 white = 4 bit code is 1110
	HUFF(5,0x1800),// 7 black = 5 bit code is 00011
	HUFF(4,0xf000),// 7 white = 4 bit code is 1111
	HUFF(6,0x1400),// 8 black = 6 bit code is 000101
	HUFF(5,0x9800),// 8 white = 5 bit code is 10011
	HUFF(6,0x1000),// 9 black = 6 bit code is 000100
	HUFF(5,0xa000),// 9 white = 5 bit code is 10100
	HUFF(7,0x0800),// 10 black = 7 bit code is 0000100
	HUFF(5,0x3800),// 10 white = 5 bit code is 00111
	HUFF(7,0x0a00),// 11 black = 7 bit code is 0000101
	HUFF(5,0x4000),// 11 white = 5 bit code is 01000
	HUFF(7,0x0e00),// 12 black = 7 bit code is 0000111
	HUFF(6,0x2000),// 12 white = 6 bit code is 001000
	HUFF(8,0x0400),// 13 black = 8 bit code is 00000100
	HUFF(6,0x0c00),// 13 white = 6 bit code is 000011
	HUFF(8,0x0700),// 14 black = 8 bit code is 00000111
	HUFF(6,0xd000),// 14 white = 6 bit code is 110100
	HUFF(9,0x0c00),// 15 black = 9 bit code is 000011000
	HUFF(6,0xd400),// 15 white = 6 bit code is 110101
	HUFF(10,0x05c0),  // 16 black = 10 bit code is 0000010111
	HUFF(6,0xa800),// 16 white = 6 bit code is 101010
	HUFF(10,0x0600),  // 17 black = 10 bit code is 0000011000
	HUFF(6,0xac00),// 17 white = 6 bit code is 101011
	HUFF(10,0x0200),  // 18 black = 10 bit code is 0000001000
	HUFF(7,0x4e00),// 18 white = 7 bit code is 0100111
	HUFF(11,0x0ce0),  // 19 black = 11 bit code is 00001100111
	HUFF(7,0x1800),// 19 white = 7 bit code is 0001100
	HUFF(11,0x0d00),  // 20 black = 11 bit code is 00001101000
	HUFF(7,0x1000),// 20 white = 7 bit code is 0001000
	HUFF(11,0x0d80),  // 21 black = 11 bit code is 00001101100
	HUFF(7,0x2e00),// 21 white = 7 bit code is 0010111
	HUFF(11,0x06e0),  // 22 black = 11 bit code is 00000110111
	HUFF(7,0x0600),// 22 white = 7 bit code is 0000011
	HUFF(11,0x0500),  // 23 black = 11 bit code is 00000101000
	HUFF(7,0x0800),// 23 white = 7 bit code is 0000100
	HUFF(11,0x02e0),  // 24 black = 11 bit code is 00000010111
	HUFF(7,0x5000),// 24 white = 7 bit code is 0101000
	HUFF(11,0x0300),  // 25 black = 11 bit code is 00000011000
	HUFF(7,0x5600),// 25 white = 7 bit code is 0101011
	HUFF(12,0x0ca0),  // 26 black = 12 bit code is 000011001010
	HUFF(7,0x2600),// 26 white = 7 bit code is 0010011
	HUFF(12,0x0cb0),  // 27 black = 12 bit code is 000011001011
	HUFF(7,0x4800),// 27 white = 7 bit code is 0100100
	HUFF(12,0x0cc0),  // 28 black = 12 bit code is 000011001100
	HUFF(7,0x3000),// 28 white = 7 bit code is 0011000
	HUFF(12,0x0cd0),  // 29 black = 12 bit code is 000011001101
	HUFF(8,0x0200),// 29 white = 8 bit code is 00000010
	HUFF(12,0x0680),  // 30 black = 12 bit code is 000001101000
	HUFF(8,0x0300),// 30 white = 8 bit code is 00000011
	HUFF(12,0x0690),  // 31 black = 12 bit code is 000001101001
	HUFF(8,0x1a00),// 31 white = 8 bit code is 00011010
	HUFF(12,0x06a0),  // 32 black = 12 bit code is 000001101010
	HUFF(8,0x1b00),// 32 white = 8 bit code is 00011011
	HUFF(12,0x06b0),  // 33 black = 12 bit code is 000001101011
	HUFF(8,0x1200),// 33 white = 8 bit code is 00010010
	HUFF(12,0x0d20),  // 34 black = 12 bit code is 000011010010
	HUFF(8,0x1300),// 34 white = 8 bit code is 00010011
	HUFF(12,0x0d30),  // 35 black = 12 bit code is 000011010011
	HUFF(8,0x1400),// 35 white = 8 bit code is 00010100
	HUFF(12,0x0d40),  // 36 black = 12 bit code is 000011010100
	HUFF(8,0x1500),// 36 white = 8 bit code is 00010101
	HUFF(12,0x0d50),  // 37 black = 12 bit code is 000011010101
	HUFF(8,0x1600),// 37 white = 8 bit code is 00010110
	HUFF(12,0x0d60),  // 38 black = 12 bit code is 000011010110
	HUFF(8,0x1700),// 38 white = 8 bit code is 00010111
	HUFF(12,0x0d70),  // 39 black = 12 bit code is 000011010111
	HUFF(8,0x2800),// 39 white = 8 bit code is 00101000
	HUFF(12,0x06c0),  // 40 black = 12 bit code is 000001101100
	HUFF(8,0x2900),// 40 white = 8 bit code is 00101001
	HUFF(12,0x06d0),  // 41 black = 12 bit code is 000001101101
	HUFF(8,0x2a00),// 41 white = 8 bit code is 00101010
	HUFF(12,0x0da0),  // 42 black = 12 bit code is 000011011010
	HUFF(8,0x2b00),// 42 white = 8 bit code is 00101011
	HUFF(12,0x0db0),  // 43 black = 12 bit code is 000011011011
	HUFF(8,0x2c00),// 43 white = 8 bit code is 00101100
	HUFF(12,0x0540),  // 44 black = 12 bit code is 000001010100
	HUFF(8,0x2d00),// 44 white = 8 bit code is 00101101
	HUFF(12,0x0550),  // 45 black = 12 bit code is 000001010101
	HUFF(8,0x0400),// 45 white = 8 bit code is 00000100
	HUFF(12,0x0560),  // 46 black = 12 bit code is 000001010110
	HUFF(8,0x0500),// 46 white = 8 bit code is 00000101
	HUFF(12,0x0570),  // 47 black = 12 bit code is 000001010111
	HUFF(8,0x0a00),// 47 white = 8 bit code is 00001010
	HUFF(12,0x0640),  // 48 black = 12 bit code is 000001100100
	HUFF(8,0x0b00),// 48 white = 8 bit code is 00001011
	HUFF(12,0x0650),  // 49 black = 12 bit code is 000001100101
	HUFF(8,0x5200),// 49 white = 8 bit code is 01010010
	HUFF(12,0x0520),  // 50 black = 12 bit code is 000001010010
	HUFF(8,0x5300),// 50 white = 8 bit code is 01010011
	HUFF(12,0x0530),  // 51 black = 12 bit code is 000001010011
	HUFF(8,0x5400),// 51 white = 8 bit code is 01010100
	HUFF(12,0x0240),  // 52 black = 12 bit code is 000000100100
	HUFF(8,0x5500),// 52 white = 8 bit code is 01010101
	HUFF(12,0x0370),  // 53 black = 12 bit code is 000000110111
	HUFF(8,0x2400),// 53 white = 8 bit code is 00100100
	HUFF(12,0x0380),  // 54 black = 12 bit code is 000000111000
	HUFF(8,0x2500),// 54 white = 8 bit code is 00100101
	HUFF(12,0x0270),  // 55 black = 12 bit code is 000000100111
	HUFF(8,0x5800),// 55 white = 8 bit code is 01011000
	HUFF(12,0x0280),  // 56 black = 12 bit code is 000000101000
	HUFF(8,0x5900),// 56 white = 8 bit code is 01011001
	HUFF(12,0x0580),  // 57 black = 12 bit code is 000001011000
	HUFF(8,0x5a00),// 57 white = 8 bit code is 01011010
	HUFF(12,0x0590),  // 58 black = 12 bit code is 000001011001
	HUFF(8,0x5b00),// 58 white = 8 bit code is 01011011
	HUFF(12,0x02b0),  // 59 black = 12 bit code is 000000101011
	HUFF(8,0x4a00),// 59 white = 8 bit code is 01001010
	HUFF(12,0x02c0),  // 60 black = 12 bit code is 000000101100
	HUFF(8,0x4b00),// 60 white = 8 bit code is 01001011
	HUFF(12,0x05a0),  // 61 black = 12 bit code is 000001011010
	HUFF(8,0x3200),// 61 white = 8 bit code is 00110010
	HUFF(12,0x0660),  // 62 black = 12 bit code is 000001100110
	HUFF(8,0x3300),// 62 white = 8 bit code is 00110011
	HUFF(12,0x0670),  // 63 black = 12 bit code is 000001100111
	HUFF(8,0x3400),// 63 white = 8 bit code is 00110100
	// code 0x80 and 0x81 not used for makeup.. use for tag codes instead!
	HUFF(9,0x0180),	// two-dimensional EOL plus singleton 1 tag bit = 000000011
	HUFF(9,0x0100), // two-dimensional EOL plus singleton 0 tag bit = 000000010
	// interleaved black/white makeup
	HUFF(10,0x03c0),  // 64 black = 10 bit code is 0000001111
	HUFF(5,0xd800),// 64 white = 5 bit code is 11011
	HUFF(12,0x0c80),  // 128 black = 12 bit code is 000011001000
	HUFF(5,0x9000),// 128 white = 5 bit code is 10010
	HUFF(12,0x0c90),  // 192 black = 12 bit code is 000011001001
	HUFF(6,0x5c00),// 192 white = 6 bit code is 010111
	HUFF(12,0x05b0),  // 256 black = 12 bit code is 000001011011
	HUFF(7,0x6e00),// 256 white = 7 bit code is 0110111
	HUFF(12,0x0330),  // 320 black = 12 bit code is 000000110011
	HUFF(8,0x3600),// 320 white = 8 bit code is 00110110
	HUFF(12,0x0340),  // 384 black = 12 bit code is 000000110100
	HUFF(8,0x3700),// 384 white = 8 bit code is 00110111
	HUFF(12,0x0350),  // 448 black = 12 bit code is 000000110101
	HUFF(8,0x6400),// 448 white = 8 bit code is 01100100
	HUFF(13,0x0360),  // 512 black = 13 bit code is 0000001101100
	HUFF(8,0x6500),// 512 white = 8 bit code is 01100101
	HUFF(13,0x0368),  // 576 black = 13 bit code is 0000001101101
	HUFF(8,0x6800),// 576 white = 8 bit code is 01101000
	HUFF(13,0x0250),  // 640 black = 13 bit code is 0000001001010
	HUFF(8,0x6700),// 640 white = 8 bit code is 01100111
	HUFF(13,0x0258),  // 704 black = 13 bit code is 0000001001011
	HUFF(9,0x6600),// 704 white = 9 bit code is 011001100
	HUFF(13,0x0260),  // 768 black = 13 bit code is 0000001001100
	HUFF(9,0x6680),// 768 white = 9 bit code is 011001101
	HUFF(13,0x0268),  // 832 black = 13 bit code is 0000001001101
	HUFF(9,0x6900),// 832 white = 9 bit code is 011010010
	HUFF(13,0x0390),  // 896 black = 13 bit code is 0000001110010
	HUFF(9,0x6980),// 896 white = 9 bit code is 011010011
	HUFF(13,0x0398),  // 960 black = 13 bit code is 0000001110011
	HUFF(9,0x6a00),// 960 white = 9 bit code is 011010100
	HUFF(13,0x03a0),  // 1024 black = 13 bit code is 0000001110100
	HUFF(9,0x6a80),// 1024 white = 9 bit code is 011010101
	HUFF(13,0x03a8),  // 1088 black = 13 bit code is 0000001110101
	HUFF(9,0x6b00),// 1088 white = 9 bit code is 011010110
	HUFF(13,0x03b0),  // 1152 black = 13 bit code is 0000001110110
	HUFF(9,0x6b80),// 1152 white = 9 bit code is 011010111
	HUFF(13,0x03b8),  // 1216 black = 13 bit code is 0000001110111
	HUFF(9,0x6c00),// 1216 white = 9 bit code is 011011000
	HUFF(13,0x0290),  // 1280 black = 13 bit code is 0000001010010
	HUFF(9,0x6c80),// 1280 white = 9 bit code is 011011001
	HUFF(13,0x0298),  // 1344 black = 13 bit code is 0000001010011
	HUFF(9,0x6d00),// 1344 white = 9 bit code is 011011010
	HUFF(13,0x02a0),  // 1408 black = 13 bit code is 0000001010100
	HUFF(9,0x6d80),// 1408 white = 9 bit code is 011011011
	HUFF(13,0x02a8),  // 1472 black = 13 bit code is 0000001010101
	HUFF(9,0x4c00),// 1472 white = 9 bit code is 010011000
	HUFF(13,0x02d0),  // 1536 black = 13 bit code is 0000001011010
	HUFF(9,0x4c80),// 1536 white = 9 bit code is 010011001
	HUFF(13,0x02d8),  // 1600 black = 13 bit code is 0000001011011
	HUFF(9,0x4d00),// 1600 white = 9 bit code is 010011010
	HUFF(13,0x0320),  // 1664 black = 13 bit code is 0000001100100
	HUFF(6,0x6000),// 1664 white = 6 bit code is 011000
	HUFF(13,0x0328),  // 1728 black = 13 bit code is 0000001100101
	HUFF(9,0x4d80), // 1728 white = 9 bit code is 010011011
	// extra codes
	HUFF(8,0x0100),	  // one-dimensional EOL = 00000001
	HUFF(4,0x1000),   // pass mode = 4 bit code is 0001
	HUFF(3,0x2000),   // horizontal mode = 3 bit code is 001 followed by run lengths (a1-a0) (a2-a1)
	// vertical mode codes
	HUFF(7,0x0600),   // +3 b1-a1 = 7 bit code is 0000011
	HUFF(6,0x0c00),   // +2 b1-a1 = 6 bit code is 000011 
	HUFF(3,0x6000),   // +1 b1-a1 = 3 bit code is 011 
	HUFF(1,0x8000),   //  0 b1=a1 = 1 bit code is 1 
	HUFF(3,0x4000),   // -1 b1-a1 = 3 bit code is 010
	HUFF(6,0x0800),   // -2 b1-a1 = 6 bit code is 000010
	HUFF(7,0x0400)    // -3 b1-a1 = 7 bit code is 0000010
	};

const TInt KRleBlack=0;
const TInt KRleWhite=1;
const TInt KRleMakeup=128;
const TInt KRleTag1D=KRleMakeup;	// exploit the two holes in the table
const TInt KRleTag2D=KRleMakeup+1;
const TInt KRleExtra=KRleMakeup+2*(1+(1728>>6));
const TInt KRleStd1D=KRleExtra;
const TInt KRlePassMode=KRleExtra+1;
const TInt KRleHorzMode=KRleExtra+2;
const TInt KRleVertMode0=KRleExtra+6;

const TInt KRleMakeupMask=~(KRleWhite|KRleMakeup);

#endif
