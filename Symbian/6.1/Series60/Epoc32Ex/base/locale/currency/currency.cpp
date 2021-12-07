// Currency.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "CommonFramework.h" // standard example framework

// advance declarations
void printCurrency();
void formatCurrency(TDes &aBuffer, TReal currencyAmount);

LOCAL_C void doExampleL()
    {
		// construct and initialize application data
		// Locale information includes whether there is a space between 
		// currency symbol and amount, whether negative currency amounts 
		// are enclosed in brackets, and whether digits to left of decimal 
		// separator are grouped in threes ("Triads"). 
	TLocale locale;	// locale information
	TCurrencySymbol currencySymbol;
	currencySymbol.Set();	// Get system wide currency symbol setting
	locale.SetCurrencySymbolPosition(ELocaleBefore); 
	locale.SetCurrencySpaceBetween(EFalse);	
	locale.SetCurrencyNegativeInBrackets(EFalse); 
	locale.SetCurrencyDecimalPlaces(2);	
	locale.SetCurrencyTriadsAllowed(ETrue);	
	locale.SetThousandsSeparator(',');
	locale.SetDecimalSeparator('.');
	locale.Set();			// set system default settings
	printCurrency();
	}

void printCurrency()
	{
	TBuf<30> aBuffer; // receives formatted currency string
	aBuffer.Zero(); // empty buffer
	TReal currencyAmount=-12345678.119;
	formatCurrency(aBuffer, currencyAmount);
	_LIT(KFormat1,"Currency value is: %S\n");
	console->Printf(KFormat1,&aBuffer);
	}
		
void formatCurrency(TDes &aBuffer, TReal currencyAmount)
	{
		//
		// Format the currency starting with the currency symbol 
		//
	TLocale locale;			// System locale settings
	TRealFormat realFormat; 
		//
		// Set up a TRealFormat object from locale information.
		// This involves setting decimal and thousands separators, 
		// whether triads are allowed or not and number of decimal places.
		//
	realFormat.iType=KRealFormatFixed; // converts number to the form
	                                   //"nnn.ddd" (n=integer, d=decimal) 
	realFormat.iWidth=30;	           // Max. number of characters allowed
									   // to  represent the number
	realFormat.iPlaces=locale.CurrencyDecimalPlaces(); 
	realFormat.iPoint=locale.DecimalSeparator(); 
	realFormat.iTriad=locale.ThousandsSeparator();
	realFormat.iTriLen=(locale.CurrencyTriadsAllowed() ? 1 : 0); 
	TCurrencySymbol symbol;			  // get currency symbol from
									  // system setting
			
	_LIT(KTxtOpenBra,"(");
	_LIT(KTxtSpace," ");
	_LIT(KTxtCloseBra,")");
									  // enclose negative currency amounts
									  // in brackets.
									  // Currency symbol can appear before or
	                                  // after the value.
	                                  // We can have spaces between the currency
	                                  // symbol and the value.
	if ((currencyAmount<0)&&(locale.CurrencyNegativeInBrackets()))
		aBuffer.Append(KTxtOpenBra);

	if (locale.CurrencySymbolPosition()==ELocaleBefore)
		{
		aBuffer.Append(symbol); 
		if (locale.CurrencySpaceBetween())
			aBuffer.Append(KTxtSpace);
		}
									  // append negative currency value to
	                                  // remove minus sign.
	if ((currencyAmount<0)&&(locale.CurrencyNegativeInBrackets()))
		aBuffer.AppendNum(-currencyAmount,realFormat);
	else
		aBuffer.AppendNum(currencyAmount,realFormat);
	
	if (locale.CurrencySymbolPosition()==ELocaleAfter)
		{ 
		if (locale.CurrencySpaceBetween())
			aBuffer.Append(KTxtSpace);
		aBuffer.Append(symbol);
		}
	
	if ((currencyAmount<0)&&(locale.CurrencyNegativeInBrackets()))
		aBuffer.Append(KTxtCloseBra);
 	}	
