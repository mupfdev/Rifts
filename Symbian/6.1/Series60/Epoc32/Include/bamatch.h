// BAMATCH.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//	Started by Brendan, January 1996
// 	Descended from HCIMATCH.H
//	Incremental matcher class
//

#if !defined (__BAMATCH_H__)
#define __BAMATCH_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__BAMDESCA_H__)
#include <bamdesca.h>
#endif


class RTextBuf
	{
public:
	IMPORT_C RTextBuf();
	IMPORT_C ~RTextBuf();
public:
	inline TPtr& Text();
	inline const TPtr& Text() const;
	inline TInt MaxLength() const;
	inline void SetText(const TDesC &aDes);
	IMPORT_C void SetMaxLengthL(TInt aMaxLength);
private:
	TPtr iPtr;
	TText* iText;
	};

class RIncrMatcherBase
	{
public:
    IMPORT_C virtual ~RIncrMatcherBase();
protected:
	inline RIncrMatcherBase() {}
protected:
	virtual TDes& MatchDes()=0;
	virtual const TDes& MatchDes() const=0; 
public:
	inline TInt MaxLength() const;
	inline TInt MatchLength() const;
	inline TPtrC MatchText() const;
//
	inline void Clear();
	IMPORT_C void DeleteLastChar();
	IMPORT_C void AppendChar(TChar aLetter);
	inline void SetMatchText(const TDesC& aText);
//
	IMPORT_C void SetBestMatch(const TDesC& aBuf);
	IMPORT_C void SetBestMatchC(const TDesC& aBuf);
	IMPORT_C void SetBestMatchF(const TDesC& aBuf);
	IMPORT_C TBool IsMatch(const TDesC& aBuf) const;
	IMPORT_C TBool IsMatchC(const TDesC& aBuf) const;
	IMPORT_C TBool IsMatchF(const TDesC& aBuf) const;
	IMPORT_C TInt FirstMatchingIndex(TInt& aResult,const MDesCArray& aDesArray,TInt aStartIndex=0) const;
	IMPORT_C TInt FirstMatchingIndexC(TInt& aResult,const MDesCArray& aDesArray,TInt aStartIndex=0) const;
	IMPORT_C TInt FirstMatchingIndexF(TInt& aResult,const MDesCArray& aDesArray,TInt aStartIndex=0) const;
private:
	typedef TInt (*TCompareFunc)(const TText*,TInt,const TText*,TInt);
	TBool DoIsMatch(const TDesC& aQuery,TCompareFunc aCompare) const;
	TInt DoFirstMatchingIndex(TInt& aIndex,const MDesCArray& aDesArray,TCompareFunc aCompare) const;
	void DoSetBestMatch(const TDesC& aBuf,TCompareFunc aCompare);
	};

class RIncrMatcherPtr : public RIncrMatcherBase
	{
public:
	IMPORT_C RIncrMatcherPtr();
	IMPORT_C RIncrMatcherPtr(TDes& aDes);
    IMPORT_C virtual ~RIncrMatcherPtr();
public:
	inline void SetMatcherPtr(TDes& aDes);
protected:
	IMPORT_C TDes& MatchDes();
	IMPORT_C const TDes& MatchDes() const;
private:
	TDes* iDesPtr;
	};

class RIncrMatcherTextBuf : public RIncrMatcherBase
	{
public:
    IMPORT_C RIncrMatcherTextBuf();
    IMPORT_C virtual ~RIncrMatcherTextBuf();
	inline void SetMatcherLengthL(TInt aMaxLength);
protected:
	IMPORT_C TDes& MatchDes();
	IMPORT_C const TDes& MatchDes() const;
private:
	RTextBuf iTextBuf;
	};

template <TInt aMaximumSize>
class RIncrMatcherBuf : public RIncrMatcherBase
	{
public:
	RIncrMatcherBuf() {}
protected:
	TDes& MatchDes()
		{return(iMatchBuf);}
	const TDes& MatchDes() const
 		{return(iMatchBuf);}
	RIncrMatcherBuf(const RIncrMatcherBuf& aMatcher)
		{iMatchBuf=aMatcher.iMatchBuf;}
private:
	TBuf<aMaximumSize> iMatchBuf;
    };


inline TPtr& RTextBuf::Text()
	{return(iPtr);}
inline const TPtr& RTextBuf::Text() const
	{return(iPtr);}
inline TInt RTextBuf::MaxLength() const
	{return(iPtr.MaxLength());}
inline void RTextBuf::SetText(const TDesC &aDes)
	{iPtr.Copy(aDes);}


inline TInt RIncrMatcherBase::MaxLength() const
	{return(MatchDes().MaxLength());}
inline TInt RIncrMatcherBase::MatchLength() const
	{return(MatchDes().Length());}
inline TPtrC RIncrMatcherBase::MatchText() const
	{return(TPtrC(MatchDes()));}
inline void RIncrMatcherBase::SetMatchText(const TDesC& aText)
	{MatchDes()=aText;}
inline void RIncrMatcherBase::Clear()
	{MatchDes().Zero();}

inline void RIncrMatcherPtr::SetMatcherPtr(TDes& aDes)
	{iDesPtr=&aDes;}

inline void RIncrMatcherTextBuf::SetMatcherLengthL(TInt aMaxLength)
	{iTextBuf.SetMaxLengthL(aMaxLength);}

#endif
