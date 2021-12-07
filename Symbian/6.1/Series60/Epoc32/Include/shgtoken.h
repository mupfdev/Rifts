// SHGTOKEN.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.

#if !defined(__SHGTOKEN_H__)
#define __SHGTOKEN_H__

#if !defined(__E32STD_H__)
#include <e32def.h>
#endif

const TInt KTokenByteSize = 2;

class Token
	{
public:
	enum TLexTokenClass	
		{EClassOperator=0,EClassDelimiter=1,EClassFunction=2,EClassOperand=3};
	enum TFunctionArgumentType 
		{ETypeNumber=0x00,ETypeRange=0x01,ETypeAll=0x02,ETypeVariable=0x03};
	enum {EMultipleArguments=0xff};
	};

enum TFormulaToken
	{
// Operators
	ETokStart=0,
	ETokOpLT,		ETokOpLE,		ETokOpGT,		ETokOpGE,
	ETokOpNE,		ETokOpEQ,
	ETokOpAdd,		ETokOpSub,		ETokOpMul,		ETokOpDiv,
	ETokOpPower,
	ETokOpUnaryPlus,ETokOpUnaryMinus,ETokOpNOT,//unary
	ETokOpAND,		ETokOpOR,		ETokOpConcatenate,
// Delimitors 
	ETokDmOpnBkt,
	ETokFirstDelimiter=ETokDmOpnBkt,
	ETokDmClsBkt,	ETokDmArgumentSeparator,	ETokDmEOL,
// Other Delimiters		
	ETokDmDBSTK,	ETokDmStop,		ETokDmCOLON,	ETokDmAbsolute,
	ETokDmTick,		ETokDmQuote,	ETokDmHAT,		ETokDmBackSlash,
// Lexer Flag - never put into formulae
	ETokLexNoTokSaved,
// Operands
	ETokCnReal,		ETokCnInt,		ETokCnInt8,		ETokCnInt16,
	ETokCnNull,//reserved
	ETokCnArray,// reserved
	ETokCnName,
	ETokCnText,
	ETokCnCell,		
	ETokCnRange,
// Stat function helpers
	ETokFnStatRange,
	ETokFnStatLit,
	ETokFnStatEnd,

// Functions - ETokFnError is the first function in Functions[]

// Error functions
	ETokFirstFn,
	ETokFnErrNull=ETokFirstFn,
	ETokFnErrDivByZero,
	ETokFnErrValue,
	ETokFnErrRef,
	ETokFnErrName,
	ETokFnErrNum,
	ETokFnErrNa,

// Logical functions
	ETokFnFALSE,
	ETokFnIF,
	ETokFnTRUE,

// Information functions
	ETokFnCELL,
	ETokFnERRORTYPE,
	ETokFnISBLANK,
	ETokFnISERR,
	ETokFnISERROR,
	ETokFnISLOGICAL,
	ETokFnISNA,
	ETokFnISNONTEXT,
	ETokFnISNUMBER,
	ETokFnISTEXT,
	ETokFnN,
	ETokFnTYPE,

	// lookup functions
	ETokFnADDRESS,
	ETokFnCOLUMN,
    ETokFnCOLUMNS,
	ETokFnHLOOKUP,
	ETokFnINDEX,
    ETokFnINDIRECT,
	ETokFnLOOKUP,
    ETokFnOFFSET,
	ETokFnROW,
	ETokFnROWS,
    ETokFnVLOOKUP,

	// text functions
	ETokFnCHAR,
	ETokFnCODE,
	ETokFnEXACT,
	ETokFnFIND,
	ETokFnLEFT,
	ETokFnLENGTH,
	ETokFnLOWER,
	ETokFnMID,
	ETokFnPROPER,	
	ETokFnREPLACE,	
	ETokFnREPT,	
    ETokFnRIGHT,
	ETokFnSTRING,
	ETokFnT,
	ETokFnTRIM,
	ETokFnUPPER,
	ETokFnVALUE,

// Ddate and time functions
    ETokFnDATE,		
	ETokFnDATEVALUE,
    ETokFnDAY,
	ETokFnHOUR,
	ETokFnMINUTE,
	ETokFnMONTH,
	ETokFnNOW,
	ETokFnSECOND,
    ETokFnTIME,		
	ETokFnTIMEVAL,
	ETokFnTODAY,
	ETokFnYEAR,

// Mathematical functions
	ETokFnABS,
	ETokFnACOS,
	ETokFnASIN,		
	ETokFnATAN,
	ETokFnATAN2,
	ETokFnCOS,
	ETokFnDEGREES,
	ETokFnEXP,
	ETokFnFACT,
	ETokFnINT,
	ETokFnLN,
	ETokFnLOG10,
	ETokFnMOD,
	ETokFnPI,
	ETokFnRADIANS,
	ETokFnRAND,
	ETokFnROUND,
	ETokFnSIGN,
	ETokFnSIN,
	ETokFnSQRT,
	ETokFnSUMPRODUCT,
	ETokFnTAN,
	ETokFnTRUNC,

// Financial functions
	ETokFnCTERM,	
	ETokFnDDB,
	ETokFnFV,
	ETokFnIRR,
	ETokFnNPV,
	ETokFnPMT,
	ETokFnPV,
	ETokFnRATE,
	ETokFnSLN,
    ETokFnSYD,			
	ETokFnTERM,

// Statistical functions
	ETokFnCOMBIN,
	ETokFnPERMUT,

// Added for App engines 5.2
	ETokFnPOWER,

	ETokLastFn=ETokFnPOWER,

// Statistical list functions
	ETokFirstFnBeginStat,
	ETokFnBeginAVERAGE=ETokFirstFnBeginStat,
	ETokFnBeginCHOOSE,
	ETokFnBeginCOUNT,
	ETokFnBeginCOUNTA,
	ETokFnBeginCOUNTBLANK,
	ETokFnBeginMAX,
	ETokFnBeginMIN,	
	ETokFnBeginPRODUCT,
	ETokFnBeginSTDEVP,
	ETokFnBeginSTDEV,
	ETokFnBeginSUM,
	ETokFnBeginSUMSQ,
	ETokFnBeginVARP,
	ETokFnBeginVAR,

	ETokLastFnBeginStat=ETokFnBeginVAR,
	ETokLastArrayFn=ETokLastFnBeginStat,
	};
#endif
