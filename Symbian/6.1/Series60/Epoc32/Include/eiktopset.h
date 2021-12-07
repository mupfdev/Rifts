#ifndef EIKTOPSET_H
#define EIKTOPSET_H

#include <e32base.h>

/* The interface class. All functions have template parameters to differentiate 
 * overloaded instances. 
 * All params are pointers which makes functions binary compatable over different 
 * types, allowing casts between different template instances to remain valid.
 * Intended use:
 *   class CMyTopSetMember : public ???, public MTopSetMember<CMyClass> (more MTopSetMembers are possible)
 *		{ implemetations of MTopSetMember pure virtuals for CMyClass};
 *   Instances of CMyTopSetMember can be added to CTopSet<CMyClass> instances.
 */
template <class T>
class MTopSetMember
	{
public:
	virtual TInt MtsmPosition(const T* aObject) const = 0;
	virtual void MtsmObject(T*& aObject) = 0;
	};


/* Base class implemented in terms of MTopSetMember<TAny>*, which can be substituted
 * for any MTopSetMember template instance.
 */
class CTopSetBase : public CBase
	{
public:
	enum TTopSetMemberPosition
		{
		ENoPosition = KMinTInt
		};

public:
	IMPORT_C ~CTopSetBase();
	IMPORT_C void AddL(MTopSetMember<TAny>* aMember);
	IMPORT_C void Remove(MTopSetMember<TAny>* aMember);
	IMPORT_C TAny* Top();
private:
	CArrayFixFlat<MTopSetMember<TAny>*>* iMembers;
	};


/* CTopSet type safe thin template wrapper. Overloads and hides the TAny function
 * in the base class.
 * The clever part here is where the compiler adjust the concrete class pointer at
 * call time to the MTopSetMember pointer appropriate for this set, by tempated type.
 */
template <class T>
class CTopSet : public CTopSetBase
	{
public:
	inline void AddL(MTopSetMember<T>* aMember);
	inline void Remove(MTopSetMember<T>* aMember);
	inline T* Top();
	};


template <class T>
inline void CTopSet<T>::AddL(MTopSetMember<T>* aMember)
	{ CTopSetBase::AddL(reinterpret_cast<MTopSetMember<TAny>*>(aMember)); }

template <class T>
inline void CTopSet<T>::Remove(MTopSetMember<T>* aMember)
	{ CTopSetBase::Remove(reinterpret_cast<MTopSetMember<TAny>*>(aMember)); }

template <class T>
inline T* CTopSet<T>::Top()
	{ return reinterpret_cast<T*>(CTopSetBase::Top()); }


#endif
