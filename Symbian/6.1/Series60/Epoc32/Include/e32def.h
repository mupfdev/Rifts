// E32DEF.H
//
// Copyright (c) 1994-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __E32DEF_H__
#define __E32DEF_H__

#ifdef __PROFILING__
#define __PROFILE_START(aBin) RDebug::ProfileStart(aBin)
#define __PROFILE_END(aBin)   RDebug::ProfileEnd(aBin)
#define __PROFILE_RESET(aNumberOfBins) RDebug::ProfileReset(0,aNumberOfBins)
#define __PROFILE_DISPLAY(aNumberOfBins) \
			{	TFixedArray<TProfile, aNumberOfBins> result; \
				RDebug::ProfileResult(result.Begin(), 0, aNumberOfBins); \
				for (TInt i=0; i<aNumberOfBins; i++)   \
				RDebug::Print(_L("Profile bin %d:  Calls: %d, Clock ticks: %d\n" ),i,result[i].iCount,result[i].iTime);  \
			}
#else // __PROFILING__
#define __PROFILE_START(aBin) 
#define __PROFILE_END(aBin)   
#define __PROFILE_RESET(aNumberOfBins) 
#define __PROFILE_DISPLAY(aNumberOfBins)
#endif
//
#if defined(__VC32__)
#define __NO_CLASS_CONSTS__
#define IMPORT_C __declspec(dllexport)
#define EXPORT_C __declspec(dllexport)
#pragma warning( disable : 4511 )	// copy constructor could not be generated
#pragma warning( disable : 4512 )	// assignment operator could not be generated
#pragma warning( disable : 4514 )	// unreferenced inline function has been removed
#pragma warning( disable : 4699 )	// Note: Using precompiled header %s
#pragma warning( disable : 4710 )	// function not inlined
#if _MSC_VER  >= 1100
#define TEMPLATE_SPECIALIZATION template<>
#else
#define TEMPLATE_SPECIALIZATION
#endif
#endif
#if defined(__GCC32__)
#define __DESC_NO_BIT_FIELDS__
#define __NO_CLASS_CONSTS__
#define IMPORT_C
#if !defined __WINS__ && defined _WIN32 // VC++ Browser Hack
#define EXPORT_C
#define asm(x)
#else
#define EXPORT_C __declspec(dllexport)
#endif
#define TEMPLATE_SPECIALIZATION
#endif

#ifdef __MARM__
#define __DOUBLE_WORDS_SWAPPED__
#endif

#define __NO_MUTABLE_KEYWORD
#if defined(__NO_MUTABLE_KEYWORD)
#define __MUTABLE
#else
#define __MUTABLE mutable
#endif

#define CONST_CAST(type,exp) (const_cast<type>(exp))
#define STATIC_CAST(type,exp) (static_cast<type>(exp))
#define REINTERPRET_CAST(type,exp) (reinterpret_cast<type>(exp))
#if defined(__NO_MUTABLE_KEYWORD)
#define MUTABLE_CAST(type,exp) (const_cast<type>(exp))
#else
#define MUTABLE_CAST(type,exp) (exp)
#endif

#define GLREF_D extern
#define GLDEF_D
#define LOCAL_D static
#define GLREF_C extern
#define GLDEF_C
#define LOCAL_C static
#define FOREVER for(;;)
#define TRUE 1
#define FALSE 0
#define NULL 0
#define VA_START(ap,pn) ((ap)[0]=(TInt8 *)&pn+((sizeof(pn)+sizeof(TInt)-1)&~(sizeof(TInt)-1)),(void)0)
#define VA_ARG(ap,type) ((ap)[0]+=((sizeof(type)+sizeof(TInt)-1)&~(sizeof(TInt)-1)),(*(type *)((ap)[0]-((sizeof(type)+sizeof(TInt)-1)&~(sizeof(TInt)-1)))))
#define VA_END(ap) ((ap)[0]=0,(void)0)
#define _FOFF(c,f) ((TInt)(&((c *)0)->f))

typedef void TAny;
typedef signed char TInt8;
typedef unsigned char TUint8;
typedef short int TInt16;
typedef unsigned short int TUint16;
typedef long int TInt32;
typedef unsigned long int TUint32;
typedef signed int TInt;
typedef unsigned int TUint;
typedef float TReal32;
typedef double TReal64;
typedef double TReal;
typedef unsigned char TText8;
typedef unsigned short int TText16;
typedef int TBool;

#define _L8(a) (TPtrC8((const TText8 *)(a)))
#define _S8(a) ((const TText8 *)a)
#define _LIT8(name,s) const static TLitC8<sizeof(s)> name={sizeof(s)-1,s}
#define _L16(a) (TPtrC16((const TText16 *)L ## a))
#define _S16(a) ((const TText16 *)L ## a)
#define _LIT16(name,s) const static TLitC16<sizeof(L##s)/2> name={sizeof(L##s)/2-1,L##s}

#if defined(_UNICODE)
typedef TText16 TText;
#define _L(a) (TPtrC((const TText *)L ## a))
#define _S(a) ((const TText *)L ## a)
#define _LIT(name,s) const static TLitC<sizeof(L##s)/2> name={sizeof(L##s)/2-1,L##s}
#else
typedef TText8 TText;
#define _L(a) (TPtrC((const TText *)(a)))
#define _S(a) ((const TText *)a)
#define _LIT(name,s) const static TLitC<sizeof(s)> name={sizeof(s)-1,s}
#endif

typedef TInt8 *VA_LIST[1];
#define __ASSERT_ALWAYS(c,p) (void)((c)||(p,0))

#if defined(_DEBUG)
#define __ASSERT_DEBUG_MB(aCond,aPanicNo) (void)((aCond)||(PanicMB(aPanicNo,_L(#aPanicNo),_L(#aCond)),0))
#define __ASSERT_DEBUG(c,p) (void)((c)||(p,0))
#define __DECLARE_NAME(t)
#define __TEST_INVARIANT __DbgTestInvariant()
//
#define __UHEAP_MARK User::__DbgMarkStart(RHeap::EUser)
#define __UHEAP_CHECK(aCount) User::__DbgMarkCheck(RHeap::EUser,EFalse,aCount,TPtrC8((TText8*)__FILE__),__LINE__)
#define __UHEAP_CHECKALL(aCount) User::__DbgMarkCheck(RHeap::EUser,ETrue,aCount,TPtrC8((TText8*)__FILE__),__LINE__)
#define __UHEAP_MARKEND User::__DbgMarkEnd(RHeap::EUser,0)
#define __UHEAP_MARKENDC(aCount) User::__DbgMarkEnd(RHeap::EUser,aCount)
#define __UHEAP_FAILNEXT(aCount) User::__DbgSetAllocFail(RHeap::EUser,RHeap::EFailNext,aCount)
#define __UHEAP_SETFAIL(aType,aValue) User::__DbgSetAllocFail(RHeap::EUser,aType,aValue)
#define __UHEAP_RESET User::__DbgSetAllocFail(RHeap::EUser,RHeap::ENone,1)
//
#define __KHEAP_MARK User::__DbgMarkStart(RHeap::EKernel)
#define __KHEAP_CHECK(aCount) User::__DbgMarkCheck(RHeap::EKernel,EFalse,aCount,TPtrC8((TText8*)__FILE__),__LINE__)
#define __KHEAP_CHECKALL(aCount) User::__DbgMarkCheck(RHeap::EKernel,ETrue,aCount,TPtrC8((TText8*)__FILE__),__LINE__)
#define __KHEAP_MARKEND User::__DbgMarkEnd(RHeap::EKernel,0)
#define __KHEAP_MARKENDC(aCount) User::__DbgMarkEnd(RHeap::EKernel,aCount)
#define __KHEAP_FAILNEXT(aCount) User::__DbgSetAllocFail(RHeap::EKernel,RHeap::EFailNext,aCount)
#define __KHEAP_SETFAIL(aType,aValue) User::__DbgSetAllocFail(RHeap::EKernel,aType,aValue)
#define __KHEAP_RESET User::__DbgSetAllocFail(RHeap::EKernel,RHeap::ENone,1)
//
#define __RHEAP_MARK(aHeap) (aHeap)->__DbgMarkStart()
#define __RHEAP_CHECK(aHeap,aCount) (aHeap)->__DbgMarkCheck(EFalse,aCount,TPtrC8((TText8*)__FILE__),__LINE__)
#define __RHEAP_CHECKALL(aHeap,aCount) (aHeap)->__DbgMarkCheck(ETrue,aCount,TPtrC8((TText8*)__FILE__),__LINE__)
#define __RHEAP_MARKEND(aHeap) (aHeap)->__DbgMarkEnd(0)
#define __RHEAP_MARKENDC(aHeap,aCount) (aHeap)->__DbgMarkEnd(aCount)
#define __RHEAP_FAILNEXT(aHeap,aCount) (aHeap)->__DbgSetAllocFail(RHeap::EFailNext,aCount)
#define __RHEAP_SETFAIL(aHeap,aType,aValue) (aHeap)->__DbgSetAllocFail(aType,aValue)
#define __RHEAP_RESET(aHeap) (aHeap)->__DbgSetAllocFail(RHeap::ENone,1)
//
#if defined (__WINS__) 
#define __DEBUGGER() {if (User::JustInTime()) _asm int 3}
#else
#define __DEBUGGER()
#endif

//
#if defined(__DLL__)
#define __DECLARE_TEST public: IMPORT_C void __DbgTestInvariant() const; void __DbgTest(TAny *aPtr) const
#else
#define __DECLARE_TEST public: void __DbgTestInvariant() const; void __DbgTest(TAny *aPtr) const
#endif

#else
#define __ASSERT_DEBUG(c,p)
#define __DECLARE_NAME(t)
#define __TEST_INVARIANT
#if defined(__DLL__)
#define __DECLARE_TEST public: IMPORT_C void __DbgTestInvariant() const; void __DbgTest(TAny *aPtr) const
#else
#define __DECLARE_TEST public: void __DbgTestInvariant() const; void __DbgTest(TAny *aPtr) const
#endif
#define __UHEAP_MARK
#define __UHEAP_CHECK(aCount)
#define __UHEAP_CHECKALL(aCount)
#define __UHEAP_MARKEND
#define __UHEAP_MARKENDC(aCount)
#define __UHEAP_FAILNEXT(aCount)
#define __UHEAP_SETFAIL(aType,aValue)
#define __UHEAP_RESET
//
#define __KHEAP_MARK
#define __KHEAP_CHECK(aCount)
#define __KHEAP_CHECKALL(aCount)
#define __KHEAP_MARKEND
#define __KHEAP_MARKENDC(aCount)
#define __KHEAP_FAILNEXT(aCount)
#define __KHEAP_SETFAIL(aType,aValue)
#define __KHEAP_RESET
//
#define __RHEAP_MARK(aHeap)
#define __RHEAP_CHECK(aHeap,aCount)
#define __RHEAP_CHECKALL(aHeap,aCount)
#define __RHEAP_MARKEND(aHeap)
#define __RHEAP_MARKENDC(aHeap,aCount)
#define __RHEAP_FAILNEXT(aHeap,aCount)
#define __RHEAP_SETFAIL(aHeap,aType,aValue)
#define __RHEAP_RESET(aHeap)
//
#define __DEBUGGER()
#endif

#if defined (__WINS__)
#define __WINS_UID(aUid0,aUid1,aUid2) TUid uid[KMaxCheckedUid]={aUid0,aUid1,aUid2};
#else
#define __WINS_UID(aUid0,aUid1,aUid2)
#endif

#if defined(__OPT__)
#define __ASSERT_OPT(c,p) (void)((c)||(p,0))
#else
#define __ASSERT_OPT(c,p)
#endif

#if defined(_UNICODE)
#if !defined(UNICODE)
#define UNICODE
#endif
#endif

#if defined(_DEBUG)
#define __DECLARE_TEST_DEBUG __DECLARE_TEST
#else
#define __DECLARE_TEST_DEBUG
#endif

#if !defined(ASSERT)
#define ASSERT(x) __ASSERT_DEBUG(x,User::Invariant())
#endif

#endif

