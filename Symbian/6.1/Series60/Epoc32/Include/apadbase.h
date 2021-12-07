// APADBASE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APADBASE_H__
#define __APADBASE_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__S32STD_H__)
#include <s32std.h>
#endif
#if !defined(__GDI_H__)
#include <gdi.h>
#endif


class CApaDoorBase : public CPicture
// Baseclass for a wrapper for embedded CApaDocuments
// Doors in general can display either as an icon or as a glass picture
	{
public:
	enum TFormat {
		EIconic,
		EGlassDoor,
		ETemporarilyIconic
		};
public:
	inline TFormat Format()const;
	inline TUid Source()const;
	inline void SetSource(TUid aSource);
protected:
	IMPORT_C void ExternalizeBaseStreamL(CStreamStore& aStore,CStreamDictionary& aStreamDict)const;
	IMPORT_C TSize InternalizeBaseStreamL(const CStreamStore& aStore,const CStreamDictionary& aStreamDict); // returns current size in twips
	virtual TSize GlassDoorSize()const=0;
protected:
	TFormat iFormat;
	TUid iSource; // foreign representation of a translated door (eg MS Word doc)
	};

//
// inlines
//

inline CApaDoorBase::TFormat CApaDoorBase::Format()const
	{ return iFormat; }

inline TUid CApaDoorBase::Source()const
	{ return iSource; }

inline void CApaDoorBase::SetSource(TUid aSource)
	{ iSource=aSource; }

#endif
