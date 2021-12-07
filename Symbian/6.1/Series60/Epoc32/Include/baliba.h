// BALIBA.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Written by Brendan, Dec 1996
//	Library associated files for pluggable components
//
#if !defined(__LIBASSOC_H__)
#define __LIBASSOC_H__
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

class TLibAssocBase
	{
protected:
	inline TLibAssocBase();
	IMPORT_C TLibAssocBase(const RLibrary& aLib,TAny* aPtr);
	IMPORT_C void Set(const RLibrary& aLib,TAny* aPtr);
	IMPORT_C static void DoUnload(TAny* aThis);
public:
	inline TBool IsNull() const;
private:
	RLibrary iLibrary;
protected:
	TAny* iPtr;
	};

//	class TLibAssoc inlines
inline TLibAssocBase::TLibAssocBase()
	: iPtr(NULL)
	{}
inline TBool TLibAssocBase::IsNull() const
	{return iPtr==NULL;}

//
//	class TLibAssoc
//

template <class T>
class TLibAssoc : public TLibAssocBase
	{
public:
	inline TLibAssoc();
	inline TLibAssoc(const RLibrary& aLib,T* aClass);
	inline void Set(const RLibrary& aLib,T* aClass);
	//
	inline void Unload();
	//
	inline operator TCleanupItem();
	operator TLibAssoc*(); // undefined, but here to prevent accidental delete(TLibAssoc)
	//
	inline T* Ptr();
	inline const T* PtrC() const;
	//
	inline operator T*();
	inline operator const T*() const;
	//
	inline T* operator->();
	inline const T* operator->() const;
private:
	static void Cleanup(TAny* aThis); // for TCleanupOperation
	};

template <class T>
inline TLibAssoc<T>::TLibAssoc()
	{}
template <class T>
inline TLibAssoc<T>::TLibAssoc(const RLibrary& aLib,T* aClass)
	: TLibAssocBase(aLib,aClass)
	{}
template <class T>
inline void TLibAssoc<T>::Set(const RLibrary& aLib,T* aClass)
	{TLibAssocBase::Set(aLib,aClass);}
template <class T>
inline T* TLibAssoc<T>::Ptr()
	{return (T*)iPtr;}
template <class T>
inline const T* TLibAssoc<T>::PtrC() const
	{return (const T*)iPtr;}
template <class T>
inline TLibAssoc<T>::operator T*()
	{return (T*)iPtr;}
template <class T>
inline TLibAssoc<T>::operator const T*() const
	{return (const T*)iPtr;}
template <class T>
inline T* TLibAssoc<T>::operator->()
	{return (T*)iPtr;}
template <class T>
inline const T* TLibAssoc<T>::operator->() const
	{return (const T*)iPtr;}
template <class T>
inline TLibAssoc<T>::operator TCleanupItem()
	{return(TCleanupItem(Cleanup,this));}
template <class T>
inline void TLibAssoc<T>::Unload()
	{Cleanup(this);}

template <class T>
void TLibAssoc<T>::Cleanup(TAny* aThis)
	{
	delete (T*)(((TLibAssoc<T>*)aThis)->iPtr);
	TLibAssocBase::DoUnload(aThis);
	}

#endif
