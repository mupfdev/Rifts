// GULDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GULDEF_H__)
#define __GULDEF_H__

enum TGulAdjacent
	{
	EGulAdjNone		=0x00,
	EGulAdjTop		=0x01,
	EGulAdjBottom	=0x02,
	EGulAdjLeft		=0x04,
	EGulAdjRight	=0x08
	};
	
#define KRgbDitheredLightGray 	TRgb(204,204,204)
#define KRgb1in4DitheredGray 	TRgb(238,238,238)
#define KRgbSymbianGreen 		TRgb(0,153,153)
#define KRgbSymbianGreenLight	TRgb(0,183,183)
#define KRgbSymbianBlue 		TRgb(0,102,153)
#define KRgbSymbianBlueDark		TRgb(0,72,123)
#define KRgbSymbianOrange		TRgb(255,218,155)

#endif
