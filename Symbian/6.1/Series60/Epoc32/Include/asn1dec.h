// ASN1DEC.H
//
// Copyright (c) 1998-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __ASN1DEC_H__
#define __ASN1DEC_H__

#include <e32std.h>
#include <e32base.h>
#include <bigint.h>
#include <asn1cons.h>

class TASN1DecGeneric
	{
public:
	IMPORT_C TASN1DecGeneric(const TDesC8& aSource);
	IMPORT_C void InitL();
	IMPORT_C TPtrC8 Encoding() const;
	IMPORT_C TInt LengthDER() const;
	IMPORT_C TPtrC8 GetContentDER(void) const;
	IMPORT_C TInt LengthDERContent(void) const;
	IMPORT_C TInt LengthDERHeader() const;
	IMPORT_C TTagType Tag() const;
	IMPORT_C TASN1Class Class() const;
private:
	TPtrC8 iEncoding;
	TInt iStartOfContents;
	TInt iLength;
	TTagType iExplicitTag;
	TASN1Class iClass;
	};

class TASN1DecString
	{
public:
protected:
	IMPORT_C TASN1DecString(const TTagType aTag);
	virtual TInt CheckValid(const TDesC8& aSource)=0;
	};

class TASN1DecBoolean
	{
public:
	IMPORT_C TASN1DecBoolean();
	IMPORT_C TBool DecodeDERL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C TBool DecodeDERL(const TASN1DecGeneric& Source);
private:
	};

class TASN1DecNull
	{
public:
	IMPORT_C TASN1DecNull();
	IMPORT_C void DecodeDERL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C void DecodeDERL(const TASN1DecGeneric& aSource);
	};

class TASN1DecEnumerated
	{
public:
	IMPORT_C TASN1DecEnumerated(void);
	};

class TASN1DecInteger
	{
public:
	IMPORT_C TASN1DecInteger();
	IMPORT_C TInt DecodeDERShortL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C TInt DecodeDERShortL(const TASN1DecGeneric& aSource);
	IMPORT_C CInteger* DecodeDERLongL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C CInteger* DecodeDERLongL(const TASN1DecGeneric& aSource);
	};

const TInt KNumberOfIDs=15;

class TASN1DecObjectIdentifier
	{
public:
	IMPORT_C TASN1DecObjectIdentifier();
	IMPORT_C HBufC* DecodeDERL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C HBufC* DecodeDERL(const TASN1DecGeneric& aSource);
private:
	TInt DecodeContentsL(TFixedArray<TInt, KNumberOfIDs>& aOID, const TDesC8& aSource);
	};

class TASN1DecSet
	{
public:
	IMPORT_C TASN1DecSet();
	IMPORT_C CArrayPtrFlat<TASN1DecGeneric>* NewDERLC(const TDesC8& aSource);
	IMPORT_C CArrayPtrFlat<TASN1DecGeneric>* DecodeDERLC(const TDesC8& aSource,TInt& aPos);
	IMPORT_C CArrayPtrFlat<TASN1DecGeneric>* DecodeDERLC(const TASN1DecGeneric& aSource);
	IMPORT_C CArrayPtrFlat<TASN1DecGeneric>* DecodeDERLC(const TDesC8& aSource,TInt& aPos, TInt aMin, TInt aMax);
	IMPORT_C CArrayPtrFlat<TASN1DecGeneric>* DecodeDERLC(const TASN1DecGeneric& aSource, TInt aMin, TInt aMax);
protected:
	void DecodeContentsL(const TDesC8& aSource, TInt& aPos, CArrayPtrFlat<TASN1DecGeneric>& aDest);
	static void CleanupSet(TAny* aArray);	
	};

class TASN1DecGraphicString
	{
public:
	IMPORT_C TASN1DecGraphicString();
	IMPORT_C HBufC* DecodeDERL(const TDesC8& aSource,TInt& aPos);
protected:
	IMPORT_C TInt CheckValid(const TDesC8& aSource);
private:
	HBufC* TASN1DecGraphicString::DecodeContentsL(const TDesC8& aSource);
	};

class TASN1DecVisibleString
	{
public:
	IMPORT_C TASN1DecVisibleString(void);
	IMPORT_C HBufC* DecodeDERL(const TDesC8& aSource,TInt& aPos);
protected:
	IMPORT_C TInt CheckValid(const TDesC8& aSource);
private:
	HBufC* DecodeContentsL(const TDesC8& aSource);
	};

class TASN1DecGeneralizedTime
	{
public:
	IMPORT_C TASN1DecGeneralizedTime();
	IMPORT_C TTime DecodeDERL(const TDesC8& aSource, TInt& aPos);
	IMPORT_C TTime DecodeDERL(const TASN1DecGeneric& aGen);
private:
	TTime GetTimeL(const TDesC8& aSource);
	};

class TASN1DecUTCTime
	{
public:
	IMPORT_C TASN1DecUTCTime();
	IMPORT_C TTime DecodeDERL(const TASN1DecGeneric& aGen);
	IMPORT_C TTime DecodeDERL(const TDesC8& aSource, TInt& aPos);
private:
	TTime GetTimeL(const TDesC8& aSource);
	};

class TASN1DecBitString
// We might be able to bash this to work as a TASN1DecString but I've not
// thought about that yet.
	{
public:
	IMPORT_C TASN1DecBitString();
	IMPORT_C HBufC8* DecodeDERL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C HBufC8* DecodeDERL(const TASN1DecGeneric& aSource);
	//we need the next 2 functions 'cos standards designers insist on 
	//stuffing things into bit strings, even when they shouldn't
	IMPORT_C HBufC8* ExtractOctetStringL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C HBufC8* ExtractOctetStringL(const TASN1DecGeneric& aSource);
//	TASN1DecBase* CopyL(void) const;
	// need to add functionality to set, clear and check individual bits.
	// need to add handling for constructed form (a dynamic retyping would be 
	// really handy for that!)
	// Just thinking about this:
	// 1) We can't really use an abstract factory approach although it seems 
	//    like the obvious way to go - the problem is that the two bitstring
	//    classes will appear in different places in the object hierarchy. 
	// 2) Defining an interface could get messy too but is more likely to get
	//    a usable result. 
	// 3) The other possibility (which is looking most likely right now, if we
	//    even attempt to tackle this problem) is that we move this object in 
	//    the hierarchy to inherit from TASN1DecComposite. This would allow us to
	//    define the functionality required for the composite form without 
	//    much implementation but would mean theres quite a lot of baggage 
	//    being carted around with each TASN1DecBitString object.
	// 4) We might be able to set up some converter functionality from a 
	//    composite bitstring to a standard bitstring thing but I don't know
	//    where I'd start trying to do that.
	// For the moment I'm going to leave this without the ability to deal with 
	// the composite form. *documented omission!*
	// We might be able to push this off into the TASN1DecGenericString class but
	// I don't know yet.
	};

class TASN1DecIA5String
	{
public:
	IMPORT_C TASN1DecIA5String();
	IMPORT_C HBufC* DecodeDERL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C HBufC* DecodeDERL(const TASN1DecGeneric& aSource);
protected:
	IMPORT_C TInt CheckValid(const TDesC8& aSource);
private:
	HBufC* DecodeContentsL(const TDesC8& aSource);
	};

class TASN1DecGenericString
	{
public:
	IMPORT_C TASN1DecGenericString();
	TInt GetContentDER(TDes8& aContent);
	TInt Length(void);
private:
	};

class TASN1DecUTF8String
	{
public:
	IMPORT_C TASN1DecUTF8String();
	IMPORT_C HBufC* DecodeDERL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C HBufC* DecodeDERL(const TASN1DecGeneric& aSource);
protected:
	IMPORT_C TInt CheckValid(const TDesC8& aSource);
private:
	HBufC* DecodeContentsL(const TDesC8& aSource);
	};

class TASN1DecGeneralString
	{
public:
	IMPORT_C TASN1DecGeneralString();
	IMPORT_C HBufC* DecodeDERL(const TDesC8& aSource,TInt& aPos);
protected:
	IMPORT_C TInt CheckValid(const TDesC8& aSource);
private:
	HBufC* DecodeContentsL(const TDesC8& aSource);
	};

class TASN1DecOctetString
	{
public:
	IMPORT_C TASN1DecOctetString();
	IMPORT_C HBufC8* DecodeDERL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C HBufC8* DecodeDERL(const TASN1DecGeneric& aSource);
protected:
	IMPORT_C TInt CheckValid(const TDesC8& aSource);
	};

class TASN1DecNumericString
	{
public:
	IMPORT_C TASN1DecNumericString();
	IMPORT_C HBufC* DecodeDERL(const TDesC8& aSource,TInt& aPos);
protected:
	TInt CheckValid(const TDesC8& aSource);
private:
	HBufC* DecodeContentsL(const TDesC8& aSource);
	};

class TASN1DecVideotexString
	{
public:
	IMPORT_C TASN1DecVideotexString();
	IMPORT_C HBufC* DecodeDERL(const TDesC8& aSource,TInt& aPos);
protected:
	IMPORT_C TInt CheckValid(const TDesC8& aSource);
private:
	HBufC* DecodeContentsL(const TDesC8& aSource);
	};

class TASN1DecPrintableString
	{
public:
	IMPORT_C TASN1DecPrintableString();
	IMPORT_C HBufC* DecodeDERL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C HBufC* DecodeDERL(const TASN1DecGeneric& aSource);
protected:
	TInt CheckValid(const TDesC8& aSource);
private:
	HBufC* DecodeContentsL(const TDesC8& aSource);
	};

class TASN1DecTeletexString
	{
public:
	IMPORT_C TASN1DecTeletexString();
	IMPORT_C HBufC* DecodeDERL(const TDesC8& aSource,TInt& aPos);
	IMPORT_C HBufC* DecodeDERL(const TASN1DecGeneric& Source);
protected:
	IMPORT_C TInt CheckValid(const TDesC8& aSource);
private:
	HBufC* DecodeContentsL(const TDesC8& aSource);
	};

class TASN1DecSequence
	{
public:
	IMPORT_C TASN1DecSequence();
	IMPORT_C CArrayPtrFlat<TASN1DecGeneric>* DecodeDERLC(const TDesC8& aSource,TInt& aPos);
	IMPORT_C CArrayPtrFlat<TASN1DecGeneric>* DecodeDERLC(const TASN1DecGeneric& aSource);
	IMPORT_C CArrayPtrFlat<TASN1DecGeneric>* DecodeDERLC(const TDesC8& aSource,TInt& aPos, TInt aMin, TInt aMax);
	IMPORT_C CArrayPtrFlat<TASN1DecGeneric>* DecodeDERLC(const TASN1DecGeneric& aSource, TInt aMin, TInt aMax);
protected:
	void DecodeContentsL(const TDesC8& aSource, CArrayPtrFlat<TASN1DecGeneric>& aDest);
	static void CleanupSequence(TAny* aArray);
	};

#endif
