// IMCVCODC.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//


//----------------------------------------------------------------------------------------
LOCAL_C inline TInt BlankLine(TDes8& rOutputLine, TInt& rPaddingCount)
//----------------------------------------------------------------------------------------
	{
	rOutputLine = KNullDesC8;
	rPaddingCount = KNullDesC8().Length();
	return 1;
	}


// function for adding 8 bit descriptor onto a 16bit descritpr.
//----------------------------------------------------------------------------------------
LOCAL_C inline void Append(TDes& aBuffer, const TDesC8& aAddition)
//----------------------------------------------------------------------------------------
	{
	TInt addLen = aAddition.Length();
	TInt  bufLen = aBuffer.Length();

	aBuffer.SetLength(bufLen+addLen);
	for(TInt i = 0; i < addLen; i++)
		aBuffer[bufLen+i] = aAddition[i];
	}

//----------------------------------------------------------------------------------------
LOCAL_C inline void Append(TDes& aBuffer, const TDesC16& aAddition)
//----------------------------------------------------------------------------------------
	{
	TInt addLen = aAddition.Length();
	TInt  bufLen = aBuffer.Length();

	aBuffer.SetLength(bufLen+addLen);
	for(TInt i = 0; i < addLen; i++)
		aBuffer[bufLen+i] = aAddition[i];
	}


//----------------------------------------------------------------------------------------
inline TBool TImCodecQP::IsPlain( TChar aChar )
//----------------------------------------------------------------------------------------
	{
	TLex8 lex(iEncodeCharList);
	while(!lex.Eos())
		if ( aChar==lex.Get() ) 
			return EFalse;

	if ( ((aChar >= 33) && (aChar <= 60)) || ((aChar >= 62) && (aChar <= 126)) )
		return ETrue;

	lex = iPlainCharList;
	while(!lex.Eos())
		if ( aChar==lex.Get() ) 
			return ETrue;

	return EFalse;
	}

//----------------------------------------------------------------------------------------
void TImCodecQP::AddSoftLineBreak( TDes8& aPtr, TInt& aPadding, TInt& aWritten)
//----------------------------------------------------------------------------------------  
	{
	__ASSERT_ALWAYS( aPtr.Length()+4< aPtr.MaxLength(), gPanic(KPanicDescriptorToSmall) );
	aPtr.Append(KImcvSP);
	aPtr.Append(iQPCharacter);
	aPtr.Append(KImcvCRLF);
	aWritten+=4;
	aPadding+=3;
	}

//----------------------------------------------------------------------------------------
void TImCodecQP::AddSoftLineBreak(const TUint8* apEnd, TUint8* aPtr, TInt& aPadding, TInt& aWritten)
//----------------------------------------------------------------------------------------  
	{
	__ASSERT_ALWAYS( aPtr+3<apEnd, gPanic(KPanicDescriptorToSmall) );
	*aPtr = KImcvSP;
	*aPtr = iQPCharacter;
	*aPtr = KImcvCR;
	*aPtr = KImcvLF;
	*aPtr+=4;
	aWritten+=4;
	aPadding+=3;
	}


//----------------------------------------------------------------------------------------
inline TBool TImCodec::IsDigit( TChar aChar )
//----------------------------------------------------------------------------------------
	{
	return ( (aChar >= '0') && (aChar <= '9') );
	}

//----------------------------------------------------------------------------------------
inline TUint8 TImCodecQP::ReplacementChar( TChar aControlChar )
//----------------------------------------------------------------------------------------
	{
	if (aControlChar==CEditableText::ETabCharacter)
		return KImcvTab;

	if (aControlChar==CEditableText::ENonBreakingHyphen)
		return KImcvHyphen;

	if (aControlChar==CEditableText::ENonBreakingSpace)
		return KImcvSP;

	return 0;
	}

//----------------------------------------------------------------------------------------
inline void TImCodecQP::AddPlainChar( const TDesC8& aCharList )
//----------------------------------------------------------------------------------------
	{
	iPlainCharList.Set(aCharList);
	}
	
	
//----------------------------------------------------------------------------------------
inline void TImCodecQP::AddEncodeChar( const TDesC8& aCharList )
//----------------------------------------------------------------------------------------
	{
	iEncodeCharList.Set(aCharList);
	}

//----------------------------------------------------------------------------------------
inline void TImCodecQP::SetQPChar( TUint8 aChar )
//----------------------------------------------------------------------------------------
	{
	iQPCharacter=aChar;
	}
	
// this function rather meanly allows a line break on a non-breaking tab and non-breaking 
// space, as defined in CEditableText

//----------------------------------------------------------------------------------------
inline TBool TImCodecQP::IsBreakable( TChar aChar)
//----------------------------------------------------------------------------------------
	{
	return (aChar==' '||aChar=='\t');
	}


//----------------------------------------------------------------------------------------
inline CImConvertCharconv& CImConvertHeader::CharConv()	
//----------------------------------------------------------------------------------------
	{
	return iCharConv;
	}



