#ifndef COEMOP_H
#define COEMOP_H

#include <e32std.h>


#define DECLARE_TYPE_ID(id) enum { ETypeId = id };


class TTypeUid : public TUid
	{
public:
	class Ptr		// can only be created by TTypeUid::MakePtr(), or TTypeUid::Null()
		{
		friend class TTypeUid;
	private:
		explicit inline Ptr(TAny* aPtr)
			: iPtr(aPtr)
			{}
	public:
		inline TAny* Pointer() const
			{return iPtr;}
	private:
		TAny* iPtr;
		};
public:
	inline TTypeUid(TInt aUid)
		{ iUid = aUid; }
	inline static Ptr Null()
		{ return Ptr(NULL); }
	template <class T> inline Ptr MakePtr(T* aT) const
		{ __ASSERT_DEBUG(iUid == T::ETypeId,User::Invariant()); return Ptr(aT); }
	};



class MObjectProvider
	{
public:
	template<class T>
	T* MopGetObject(T*& aPtr) 
		{ return (aPtr=static_cast<T*>(MopGetById(T::ETypeId))); }

private: // must be overridden
	virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId) = 0;

private: // may be overridden to continue chain of responsibility
	IMPORT_C virtual MObjectProvider* MopNext();

private: // internal implementation
	IMPORT_C TAny* MopGetById(TTypeUid aId);
	};

#endif