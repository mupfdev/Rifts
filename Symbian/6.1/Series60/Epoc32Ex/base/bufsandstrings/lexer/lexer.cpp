// Lexer.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include <e32std.h>
#include <e32cons.h>

const TInt KMaxCalcCommandBuffer=80;

//Common literal text
 

_LIT(KTxtErrInExpress,"    Error in expression, cannot evaluate. ");


CConsoleBase* console;


///////////////////////////////////////////////////////////////////////////////////
// Stack classes
///////////////////////////////////////////////////////////////////////////////////

//
// Stack element class - linked list of TReals
//

class CRpnStackElement : public CBase
	{
	friend class CRpnStack ;

	private:
		CRpnStackElement* iNext ;
		TReal iValue ;

	public:
		static CRpnStackElement* NewL ( const TReal& aReal, CRpnStackElement* aStackElement) ;
		void   ConstructL (const TReal& aReal, CRpnStackElement* aStackElement) ;

	public:
		CRpnStackElement(const TReal& aReal, CRpnStackElement* aStackElement) { NewL(aReal, aStackElement) ; } ;
		CRpnStackElement() {} ;
	}  ;


//
// Stack class - just constructor, destructor, push, pop & empty-test.
//

class CRpnStack : public CBase
	{
	private: 
		CRpnStackElement* iTop ;  // pointer to top of stack element

	public:
		static CRpnStack* NewL () ;
		void   ConstructL () ;

		~CRpnStack() ;
		TReal Pop () ;
		void Push (TReal aReal) ;
		TBool IsEmpty () ;
	} ;


///////////////////////////////////////////////////////////////////////////////////
// Stack class implementations
///////////////////////////////////////////////////////////////////////////////////

// stack element construction (2-part)
CRpnStackElement* CRpnStackElement::NewL(const TReal& aReal, CRpnStackElement* aStackElement)
	{
	CRpnStackElement* self = new (ELeave) CRpnStackElement ;
	CleanupStack::PushL(self);
	self->ConstructL(aReal, aStackElement);
	CleanupStack::Pop();
	return self;
	}


void CRpnStackElement::ConstructL(const TReal& aReal, CRpnStackElement* aStackElement)
	{
	iValue = aReal;
	iNext = aStackElement ;
	}


// stack construction
CRpnStack* CRpnStack::NewL()
	{
	CRpnStack* self = new (ELeave) CRpnStack ;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}


void CRpnStack::ConstructL()
	{
	iTop = 0 ;
	}


// stack destructor
CRpnStack::~CRpnStack()
	{
	while (!IsEmpty())   
		Pop() ;
	}


// stack pop & delete top element
TReal CRpnStack::Pop ()
	{
	TReal value = iTop->iValue ;  // get return value
	CRpnStackElement* old = iTop ;  // keep old top of stack pointer
	iTop = iTop->iNext;  // move top of stack pointer to next element
	delete old ;  // delete old top of stack element
	old = 0 ;  // don't want old used again
	return value ;  // return the value
	} 


// stack push new element
void CRpnStack::Push (TReal aReal)
	{
	iTop = CRpnStackElement::NewL(aReal, iTop) ; 
	} 


// stack empty test
TBool CRpnStack::IsEmpty ()
	{
	return (iTop == 0) ;
	}


/////////////////////////////////////////////////////////////////////////////////
//  RPN calculator engine class
/////////////////////////////////////////////////////////////////////////////////

class CRpnCalculator
	{
	private:
		static TReal GetIntegerPart(TLex& aInput) ;
		static TReal GetFractionalPart(TLex& aInput) ;
		static TInt  DealWithNum(CRpnStack* aStack, TLex& aInput) ;
		static TInt  RPNCalcEngine(const TDesC& aCommand, TReal& aReturnValue) ;
		static TInt  doRPNCalcEngine(TLex& aInput,CRpnStack* stack,TReal& aReturnValue);
		static void  DisplayAnswer(TReal aValue) ;
		static TBool TextInput(TDes& aBuf) ;
	public:
		static void RunRPNCalculatorL() ;
	} ;


/////////////////////////////////////////////////////////////////////////////////
//  RPN calculator engine : numeric routines
/////////////////////////////////////////////////////////////////////////////////

TReal CRpnCalculator::GetIntegerPart(TLex& aInput) 
// Finds a UInt. Also used before decimal point for RPN TReal processing
	{
	TReal accumulator =  0 ;

	while ((aInput.Peek()).IsDigit())
		{
		accumulator = (accumulator * 10) + ( (TReal)aInput.Get() - (TReal)'0' ) ;
		}
	return accumulator ;
	}


TReal CRpnCalculator::GetFractionalPart(TLex& aInput) 
// Finds a UInt. Used after decimal point for RPN TReal processing
	{
	TReal accumulator =  0 ;
	TReal multiplier = 0.1 ;

	while ((aInput.Peek()).IsDigit())
		{
		accumulator +=  ( (TReal)aInput.Get() - (TReal)'0' ) * multiplier ;
		multiplier /= 10 ;
		}
	return accumulator ;
	} 


TInt CRpnCalculator::DealWithNum(CRpnStack* aStack, TLex& aInput) 
// VERY basic scanning to extract and push a (Uint or real) number.
	{
	TBool negative = EFalse ;
	TReal answer =  0 ;
	TLexMark startMark ;

	// need something to parse
	if (aInput.Eos())
		return KErrNotFound ;
	if (!(aInput.Peek().IsDigit() || (aInput.Peek() == '.') ) )
		return KErrNotFound ;
	
	// mark where we are, so can unwind
	aInput.Mark(startMark) ;

	// deal with sign
	if (aInput.Peek() == '+') 
		aInput.Inc() ;
	if (aInput.Peek() == '-') 
		{
		aInput.Inc() ;
		negative = ETrue ;
		}

	// check there's something to parse
	if (aInput.Eos()) 
		return KErrNotFound ;

	// get number (may be complete integer or first part of a real)
	if ((aInput.Peek()).IsDigit())
		answer = CRpnCalculator::GetIntegerPart(aInput)  ;

	// negate if necessary
	if (negative) 
		answer *= -1 ;

	// look for decimal point - if found, parse real number
	if (aInput.Peek() == '.')
		{  // may be dealing with real number.
		aInput.Inc() ;
		if (!(aInput.Peek()).IsDigit())	
			{	// found non-digit after decimal point. Error, so rewind & exit
			aInput.UnGetToMark(startMark) ;
			return KErrCancel ;
			}
		// now must parse digit(s) after decimal point
		answer += CRpnCalculator::GetFractionalPart(aInput) ;
		aStack->Push(answer) ;
		return KErrNone ;
		}
	else
		{  // dealing with integer 
		aStack->Push(answer) ;
		return KErrNone ;
		}
	}


/////////////////////////////////////////////////////////////////////////////////
//  Main body of the RPN calculator engine : calculator
/////////////////////////////////////////////////////////////////////////////////

TInt CRpnCalculator::doRPNCalcEngine(TLex& aInput,CRpnStack* stack,TReal& aReturnValue)
	{
	//		extract a number if possible & push
	//		extract token, perform operation & push result
	//		if token is '=' or at end of string, pop & print value
	TInt Err       = KErrNone;
	TReal operand1 = 0;
	TReal operand2 = 0 ;
	TReal memory   = 0 ;

	do 
		{
		aInput.SkipSpace() ;

		if (CRpnCalculator::DealWithNum(stack, aInput)== KErrNone) ;  // parse for number 

    /*  above line can be replaced by the following equivalent code:
 			
			if (aInput.Val(extractReal) == KErrNone)
				stack->Push(extractReal) ;
			else if (aInput.Val(extractUint) == KErrNone)
				stack->Push(TReal(extractUint)) ;
	*/

		else switch ( aInput.Get() )
			{
			case'+' :
				if (!stack->IsEmpty()) operand2 = stack->Pop() ; else Err = KErrGeneral ;
				if (!stack->IsEmpty()) operand1 = stack->Pop() ; else Err = KErrGeneral;
				if (Err==KErrNone) stack->Push (operand1 + operand2) ;
				break ;

			case'-' :
				if (!stack->IsEmpty()) operand2 = stack->Pop() ; else Err = KErrGeneral ;
				if (!stack->IsEmpty()) operand1 = stack->Pop() ; else Err = KErrGeneral;
				if (Err==KErrNone) stack->Push (operand1 - operand2) ;
				break ;

			case '*' :
				if (!stack->IsEmpty()) operand2 = stack->Pop() ; else Err = KErrGeneral ;
				if (!stack->IsEmpty()) operand1 = stack->Pop() ; else Err = KErrGeneral;
				if (Err==KErrNone) stack->Push (operand1 * operand2) ;
				break ;

			case'/' :
				if (!stack->IsEmpty()) operand2 = stack->Pop() ; else Err = KErrGeneral ;
				if (!stack->IsEmpty()) operand1 = stack->Pop() ; else Err = KErrGeneral;
				if (Err==KErrNone) stack->Push (operand1 / operand2) ;
				break ;	
						
			case '=' :
				if ( !(stack->IsEmpty() ) )
				{	aReturnValue = stack->Pop() ;
					return KErrNone ;
				}
				else return KErrArgument ;

			// not found a valid one-character symbol, try key words...
			default :			
				if (aInput.Offset() > 0)  // if not at start of line
					aInput.UnGet() ;  // restore 'got' character

				aInput.Mark() ;  // remember where we are
				aInput.SkipCharacters() ;  // move to end of character token


				if ( aInput.TokenLength() != 0 )  // if valid potential token
					{
					_LIT(KTxtMEMSET,"MEMSET");
					_LIT(KTxtMEMGET,"MEMGET");
					TPtrC token = aInput.MarkedToken() ;  // extract token
					if ( token.CompareF(KTxtMEMSET) == 0)
						{
						if ( !(stack->IsEmpty()) )  // MEMSET - store top stack element
							memory = stack->Pop() ;
						if ( stack->IsEmpty() )  // valid command, but empty stack will cause error, so
							stack->Push(memory) ;
						}
					else if ( token.CompareF(KTxtMEMGET) == 0)
						stack->Push (memory) ;  // MEMGET - push memory value
					else 
						return KErrNotSupported ;  // unrecognised token
					}
				else  // exit - can't be anything else
					{
					return KErrGeneral ;
					}
			} ;  // end switch
		if (Err == KErrGeneral)	
		 	// error in expression (usually as there aren't 2 stack elements for token to operate on)
			return KErrArgument ;
		
		} 	while (!aInput.Eos())  ;

	if ( !(stack->IsEmpty() ) )
		{
		aReturnValue = stack->Pop() ;
		return KErrNone ;
		}
	else return KErrArgument ;
	}	



/////////////////////////////////////////////////////////////////////////////////
//  RPN calculator engine : calculator
/////////////////////////////////////////////////////////////////////////////////

TInt CRpnCalculator::RPNCalcEngine(const TDesC& aCommand, TReal& aReturnValue)
	{
	TInt ret;
	TLex input(aCommand);
	
	CRpnStack* stack = CRpnStack::NewL();
	CleanupStack::PushL(stack);
	ret = CRpnCalculator::doRPNCalcEngine(input,stack,aReturnValue);
	CleanupStack::PopAndDestroy(); 
	return ret;
	}



/////////////////////////////////////////////////////////////////////////////////
//  RPN calculator UI : display routines
/////////////////////////////////////////////////////////////////////////////////

void CRpnCalculator::DisplayAnswer(TReal aValue)
	{
	TRealFormat format ;
	TBuf<0x100> convertRealToString;

	// want a TLex from the value

	if (convertRealToString.Num(aValue,format) < KErrNone )  // if -ve, is an error, not a string length 
		console->Printf(KTxtErrInExpress);
	else
		{
		convertRealToString.ZeroTerminate();

		TLex string(convertRealToString) ;
		// got a TLex
	
		TLexMark start ;
		string.Mark (start) ;  // remember start of string position

		// run through string, setting 'end' to last digit found
		while (!string.Eos() )
			{
			if ( !(string.Get() == '0') ) string.Mark() ;
			}

		string.UnGetToMark() ;  // reset next character pointer to last digit
		// if Mark points to decimal point and not at Eos (i.e. a zero follows), include the zero
		if ( string.Get() == '.' && !string.Eos() )
			string.Mark() ;

		// display spaces after entered line
		_LIT(KTxtSpaces,"  ");
		console->Write(KTxtSpaces) ;
		// set Mark to start of string and display answer
		console->Write( string.MarkedToken(start)  ) ;
		}
	}


/////////////////////////////////////////////////////////////////////////////////
//  RPN calculator UI : line input  routine (adapted from tuiedit)
/////////////////////////////////////////////////////////////////////////////////

_LIT(KTxtBackSlashSeven,"\7");
_LIT(KTxtCursor,"_");

TBool CRpnCalculator::TextInput(TDes& aBuf)
    {
	TInt  pos;
	
	pos  = 0;
	aBuf.Zero();
	console->SetPos(0);
	console->Write(KTxtCursor) ;  // "cursor"
	console->SetPos(0);

	FOREVER
		{
		TChar gChar=console->Getch();
		switch (gChar)
			{
			case EKeyEscape:
				return (EFalse);
			case EKeyEnter:
				return (ETrue);
			case EKeyBackspace:	
				if (pos)
					{
					pos--;
					aBuf.Delete(pos,1);
					}
				break;
			default:
				if (!gChar.IsPrint())
					break;
				else
					if ((aBuf.Length()<KMaxCalcCommandBuffer)&&(pos<KDefaultConsWidth-3))
						{
						TBuf<0x02> b;
						b.Append(gChar);
						aBuf.Insert(pos++,b);
						}
					else
						{
						console->Write(KTxtBackSlashSeven);
						break;
						}
			}
			console->SetPos(pos) ;
			console->ClearToEndOfLine();
			console->SetPos(0);
			console->Write(aBuf);
			console->Write(KTxtCursor) ;  // "cursor"
			console->SetPos(pos);
		}
	}


/////////////////////////////////////////////////////////////////////////////////
//  finally the RPN calculator's driver code
/////////////////////////////////////////////////////////////////////////////////

_LIT(KTxtStartingRPNCalc,"Starting RPN Calculator\n\n");
_LIT(KTxtNewLine," \n");
_LIT(KTxtInvite,"Type in a Reverse Polish\nexpression.\nPress ENTER to evaluate it\nPress ESC to end\n");



void CRpnCalculator::RunRPNCalculatorL()
	{
	TBuf<KMaxCalcCommandBuffer> command;	
	
	console->Printf(KTxtStartingRPNCalc);
	console->Printf(KTxtInvite);

	while (CRpnCalculator::TextInput(command) ) 
		{
		TReal answer;

		if (CRpnCalculator::RPNCalcEngine(command, answer) == KErrNone ) 
			CRpnCalculator::DisplayAnswer(answer) ;
		else
			console->Printf(KTxtErrInExpress) ;
				
		console->Printf(KTxtNewLine) ;
		console->Printf(KTxtInvite);
		}
	}


/////////////////////////////////////////////////////////////////////////////////
// This section deals with EPOC32 initialisation and ensuring we have a console active
/////////////////////////////////////////////////////////////////////////////////


void SetupConsoleL();

_LIT(KTxtRPNCalcErr,"RPN Calculator example error");

GLDEF_C TInt E32Main()  // main function called by E32
    {
	CTrapCleanup* cleanup=CTrapCleanup::New();  // get clean-up stack
	TRAPD(error,SetupConsoleL());  // more initialization, then do example
	__ASSERT_ALWAYS(!error,User::Panic(KTxtRPNCalcErr,error));
	delete cleanup;  // destroy clean-up stack
	return 0;  // and return
    }


void SetupConsoleL()  // initialize and call example code under cleanup stack
    {
	_LIT(KTxtIntro,"eulexrpn - RPN Calculator");
	_LIT(KFormat1,"failed: leave code=%d");
	_LIT(KTxtPressAnyKey,"[Press any key to exit]");

	console=Console::NewL(KTxtIntro,TSize(KConsFullScreen,KConsFullScreen));
	CleanupStack::PushL(console);
	TRAPD(error, CRpnCalculator::RunRPNCalculatorL());  // perform example function
	if (error)
		console->Printf(KFormat1, error);
	console->Printf(KTxtPressAnyKey);
	console->Getch();  // get and ignore character
	CleanupStack::PopAndDestroy();  // close console
    }

	
