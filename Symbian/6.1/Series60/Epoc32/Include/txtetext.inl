// TXTETEXT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


TBool CEditableText::HasChanged()const
	{return iHasChanged;}


TBool CPlainText::FieldSetPresent()const
	{return (iFieldSet.IsPtr() && iFieldSet.AsPtr()!=NULL);}


const MTextFieldFactory* CPlainText::FieldFactory()const
	{return (FieldSetPresent()) ? iFieldSet->FieldFactory() : NULL;}


void CPlainText::ConsumeAdornmentL(RReadStream& aStream)
	{
	TStreamId id;
	aStream>> id;
	}


TUid CPlainText::UidFromStreamL(RReadStream& aStream)
	{
	TUid uid;
	aStream>> uid;
	return uid;
	}
