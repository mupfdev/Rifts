// E32STD.H
//
// Copyright (c) 1994-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __E32STD_H__
#define __E32STD_H__
#include <e32def.h>

#define KNullUid TUid::Null()

const TInt KDefaultJustifyWidth=(-1);
const TInt KMaxCheckedUid=3;
const TInt KMaxUidName=10;
const TInt KMaxName=0x80;
const TInt KMaxOsName=(KMaxName-KMaxUidName-2-4);
const TInt KMaxInfoName=0x10;
const TInt KMaxFullName=(KMaxName<<1);
const TInt KMaxPassword=0x10;
const TInt KMaxExitCategoryName=0x10;
const TInt KMaxDayName=0x20;
const TInt KMaxDayNameAbb=0x08;
const TInt KMaxDays=7;
const TInt KMaxMonthName=0x20;
const TInt KMaxMonthNameAbb=0x08;
const TInt KMaxMonths=12;
const TInt KMaxSuffix=0x04;
const TInt KMaxSuffixes=31;
const TInt KMaxAmPmName=0x04;
const TInt KMaxAmPms=2;
const TInt KMaxTranslateTable=0x100;
const TInt KMaxCurrencySymbol=0x08;
const TInt KMaxShortDateFormatSpec=40;
const TInt KMaxLongDateFormatSpec=80;
const TInt KMaxTimeFormatSpec=60;
const TInt KMaxFileName=0x100;
const TInt KMaxVersionName=0x10;
const TInt KMaxPath=0x100;
const TInt KMaxDeviceInfo=0x80;
const TInt KMinHeapSize=0x100;
const TInt KDstHome=0x01;
const TInt KDstEuropean=0x02;
const TInt KDstNorthern=0x04;
const TInt KDstSouthern=0x08;
const TInt KDefaultStackSize=0x2000;
const TUint KNoChar=0xffffffffu;
const TInt KIndexPtr=(-1);
const TInt KCurrentProcessHandle=0xffff0000;
const TInt KHandleNoClose=0x00008000;
const TInt KCurrentThreadHandle=0xffff0001|KHandleNoClose;
const TInt KNullHandle=0;
const TInt KDefaultUnit=0x00;
const TInt KNullUnit=0xffffffff;
const TInt KMaxUnits=0x20;
const TInt KMaxMessageArguments=0x04;
const TInt KDefaultRealWidth=20;
const TInt KMinHeapGrowBy=0x1000;
const TInt KMaxExponentConversion=99;
const TInt KNullUidValue=0;
const TInt KDeltaTimerDefaultGranularity=100000;
const TInt KMaxTInt8=0x7f;
const TInt KMinTInt8=(-128);
const TUint KMaxTUint8=0xffu;
const TInt KMaxTInt16=0x7fff;
const TInt KMinTInt16=(-32768);
const TUint KMaxTUint16=0xffffu;
const TInt KMaxTInt32=0x7fffffff;
const TInt KMinTInt32=(TInt)0x80000000;
const TUint KMaxTUint32=0xffffffffu;
const TInt KMaxTInt=0x7fffffff;
const TInt KMinTInt=(TInt)0x80000000;
const TUint KMaxTUint=0xffffffffu;
const TUint KMatchAny='*';
const TUint KMatchOne='?';
const TInt KMaxLocalDrives=9;
const TInt KMaxPBusSockets=4;

const TInt KErrNone=0;
const TInt KErrNotFound=(-1); // Must remain set to -1
const TInt KErrGeneral=(-2);
const TInt KErrCancel=(-3);
const TInt KErrNoMemory=(-4);
const TInt KErrNotSupported=(-5);
const TInt KErrArgument=(-6);
const TInt KErrTotalLossOfPrecision=(-7);
const TInt KErrBadHandle=(-8);
const TInt KErrOverflow=(-9);
const TInt KErrUnderflow=(-10);
const TInt KErrAlreadyExists=(-11);
const TInt KErrPathNotFound=(-12);
const TInt KErrDied=(-13);
const TInt KErrInUse=(-14);
const TInt KErrServerTerminated=(-15);
const TInt KErrServerBusy=(-16);
const TInt KErrCompletion=(-17);
const TInt KErrNotReady=(-18);
const TInt KErrUnknown=(-19);
const TInt KErrCorrupt=(-20);
const TInt KErrAccessDenied=(-21);
const TInt KErrLocked=(-22);
const TInt KErrWrite=(-23);
const TInt KErrDisMounted=(-24);
const TInt KErrEof=(-25);
const TInt KErrDiskFull=(-26);
const TInt KErrBadDriver=(-27);
const TInt KErrBadName=(-28);
const TInt KErrCommsLineFail=(-29);
const TInt KErrCommsFrame=(-30);
const TInt KErrCommsOverrun=(-31);
const TInt KErrCommsParity=(-32);
const TInt KErrTimedOut=(-33);
const TInt KErrCouldNotConnect=(-34);
const TInt KErrCouldNotDisconnect=(-35);
const TInt KErrDisconnected=(-36);
const TInt KErrBadLibraryEntryPoint=(-37);
const TInt KErrBadDescriptor=(-38);
const TInt KErrAbort=(-39);
const TInt KErrTooBig=(-40);
const TInt KErrDivideByZero=(-41);		// Added by AnnW
const TInt KErrBadPower=(-42);
const TInt KErrDirFull=(-43);
const TInt KErrHardwareNotAvailable=(-44);

//const TInt KErrAbort;
//const TInt KErrNoLinearMemory=(-4);
//const TInt KErrDomain=(-8);
//const TInt KErrTooBig=(-25);
//const TInt KErrSubSystem=(-36);

const TInt KRequestPending=(-KMaxTInt);

enum TKernelPanic
	{
	EBadHandle=0,
	EAccessDenied=1,
	EBadName=2,
	ECausedException=3,
	ECompletion=4,
	ELeaveWithoutTrap=5,
	ESegmentReadOutOfRange=6,
	ESegmentWriteOutOfRange=7,
	EChunkSizeTooBig=8,
	ERequestAlreadyPending=9,
	ERequestNoInvalid=10,
	EBadUnitNumber=11,
	EEventAlreadyCaptured=12,
	EEventNotCaptured=13,
	EBadPriority=14,
	ETimerAlreadyPending=15,
	EAlreadyLoggedOn=16,
	EFailedKernelHeapCheck=17,
	ERequestFromWrongThread=18,
	EMesAlreadyPending=19,
	EEventRequestPending=20,
	EIllegalWsProcess=21,
	EHardwareNotAvailable=22,
	EUnsharableSession=23,
	EDesOverflow=24
	};

// Drive capabilities

enum TMediaType
	{
	EMediaNotPresent,
	EMediaUnknown,EMediaFloppy,EMediaHardDisk,EMediaCdRom,
	EMediaRam,EMediaFlash,EMediaRom,EMediaRemote
	};

enum TBatteryState {EBatNotSupported,EBatGood,EBatLow};

const TUint KDriveAttLocal=0x01;
const TUint KDriveAttRom=0x02;
const TUint KDriveAttRedirected=0x04;
const TUint KDriveAttSubsted=0x08;
const TUint KDriveAttInternal=0x10;
const TUint KDriveAttRemovable=0x20;
const TUint KDriveAttRemote=0x40;
const TUint KDriveAttTransaction=0x80;

const TUint KMediaAttVariableSize=0x01;
const TUint KMediaAttDualDensity=0x02;
const TUint KMediaAttFormattable=0x04;
const TUint KMediaAttWriteProtected=0x08;
const TUint KMediaAttLockable=0x10;
const TUint KMediaAttLocked=0x20;
const TUint KMediaAttHasPassword=0x40;

const TUint KDriveFileSysFAT=0x01;
const TUint KDriveFileSysROM=0x02;
const TUint KDriveFileSysLFFS=0x03;

enum TFalse {EFalse=FALSE};
enum TTrue {ETrue=TRUE};
enum TAllowDuplicates {ENoDuplicates,EAllowDuplicates};
enum TRadix {EBinary=2,EOctal=8,EDecimal=10,EHex=16};

/*
This list must have exactly 100 entries - locale-specific resource files have an extension
of the form RNN, where NN is two digits.
*/
enum TLanguage
	{
	ELangTest,					// 00
	ELangEnglish,				// 01
	ELangFrench,				// 02
	ELangGerman,				// 03
	ELangSpanish,				// 04
	ELangItalian,				// 05
	ELangSwedish,				// 06
	ELangDanish,				// 07
	ELangNorwegian,				// 08
	ELangFinnish,				// 09
	ELangAmerican,				// 10
	ELangSwissFrench,			// 11
	ELangSwissGerman,			// 12
	ELangPortuguese,			// 13
	ELangTurkish,				// 14
	ELangIcelandic,				// 15
	ELangRussian,				// 16
	ELangHungarian,				// 17
	ELangDutch,					// 18
	ELangBelgianFlemish,		// 19
	ELangAustralian,			// 20
	ELangBelgianFrench,			// 21
	ELangAustrian,				// 22
	ELangNewZealand,			// 23
	ELangInternationalFrench,	// 24
	ELangCzech,					// 25
	ELangSlovak,				// 26
	ELangPolish,				// 27
	ELangSlovenian,				// 28
	ELangTaiwanChinese,			// 29
	ELangHongKongChinese,		// 30
	ELangPrcChinese,			// 31
	ELangJapanese,				// 32
	ELangThai,					// 33
	ELangAfrikaans,				// 34
	ELangAlbanian,				// 35
	ELangAmharic,				// 36
	ELangArabic,				// 37
	ELangArmenian,				// 38
	ELangAzerbaijani,			// 39
	ELangTagalog = ELangAzerbaijani,  // Tagalog replaces Azerbaijani for Calypso. Both have same value.
	ELangBelarussian,			// 40
	ELangBengali,				// 41
	ELangBulgarian,				// 42
	ELangBurmese,				// 43
	ELangCatalan,				// 44
	ELangCroatian,				// 45
	ELangCanadianEnglish,		// 46
	ELangInternationalEnglish,	// 47
	ELangSouthAfricanEnglish,	// 48
	ELangEstonian,				// 49
	ELangFarsi,					// 50
	ELangCanadianFrench,		// 51
	ELangScotsGaelic,			// 52
	ELangGeorgian,				// 53
	ELangGreek,					// 54
	ELangCyprusGreek,			// 55
	ELangGujarati,				// 56
	ELangHebrew,				// 57
	ELangHindi,					// 58
	ELangIndonesian,			// 59
	ELangIrish,					// 60
	ELangSwissItalian,			// 61
	ELangKannada,				// 62
	ELangKazakh,				// 63
	ELangKhmer,					// 64
	ELangKorean,				// 65
	ELangLao,					// 66
	ELangLatvian,				// 67
	ELangLithuanian,			// 68
	ELangMacedonian,			// 69
	ELangMalay,					// 70
	ELangMalayalam,				// 71
	ELangMarathi,				// 72
	ELangMoldavian,				// 73
	ELangMongolian,				// 74
	ELangNorwegianNynorsk,		// 75
	ELangBrazilianPortuguese,	// 76
	ELangPunjabi,				// 77
	ELangRomanian,				// 78
	ELangSerbian,				// 79
	ELangSinhalese,				// 80
	ELangSomali,				// 81
	ELangInternationalSpanish,	// 82
	ELangLatinAmericanSpanish,	// 83
	ELangSwahili,				// 84
	ELangFinlandSwedish,		// 85
	ELangTajik,					// 86
	ELangTamil,					// 87
	ELangTelugu,				// 88
	ELangTibetan,				// 89
	ELangTigrinya,				// 90
	ELangCyprusTurkish,			// 91
	ELangTurkmen,				// 92
	ELangUkrainian,				// 93
	ELangUrdu,					// 94
	ELangUzbek,					// 95
	ELangVietnamese,			// 96
	ELangWelsh,					// 97
	ELangZulu,					// 98
	ELangOther					// 99
	};

enum TDateFormat {EDateAmerican,EDateEuropean,EDateJapanese};
enum TTimeFormat {ETime12,ETime24};
enum TClockFormat {EClockAnalog,EClockDigital};
enum TUnitsFormat {EUnitsImperial,EUnitsMetric};
enum TAmPm {EAm,EPm};

enum TDay
	{
	EMonday,ETuesday,EWednesday,EThursday,
	EFriday,ESaturday,ESunday
	};

enum TMonth
	{
	EJanuary,EFebruary,EMarch,EApril,
	EMay,EJune,EJuly,EAugust,
	ESeptember,EOctober,ENovember,EDecember
	};

enum TOwnerType {EOwnerProcess,EOwnerThread};
enum TDllReason {EDllProcessAttach,EDllThreadAttach,EDllThreadDetach,EDllProcessDetach};

enum TProcessPriority
	{
	EPriorityLow=150,
	EPriorityBackground=250,
	EPriorityForeground=350,
	EPriorityHigh=450,
	EPriorityWindowServer=650,
	EPriorityFileServer=750,
	EPriorityRealTimeServer=850,
	EPrioritySupervisor=950
	};

enum TThreadPriority
	{
	EPriorityNull=(-30),
	EPriorityMuchLess=(-20),
	EPriorityLess=(-10),
	EPriorityNormal=0,
	EPriorityMore=10,
	EPriorityMuchMore=20,
	EPriorityRealTime=30,
	EPriorityAbsoluteVeryLow=100,
	EPriorityAbsoluteLow=200,
	EPriorityAbsoluteBackground=300,
	EPriorityAbsoluteForeground=400,
	EPriorityAbsoluteHigh=500
	};

enum TExcType
	{
	EExcGeneral=0,
	EExcIntegerDivideByZero=1,
	EExcSingleStep=2,
	EExcBreakPoint=3,
	EExcIntegerOverflow=4,
	EExcBoundsCheck=5,
	EExcInvalidOpCode=6,
	EExcDoubleFault=7,
	EExcStackFault=8,
	EExcAccessViolation=9,
	EExcPrivInstruction=10,
	EExcAlignment=11,
	EExcPageFault=12,
	EExcFloatDenormal=13,
	EExcFloatDivideByZero=14,
	EExcFloatInexactResult=15,
	EExcFloatInvalidOperation=16,
	EExcFloatOverflow=17,
	EExcFloatStackCheck=18,
	EExcFloatUnderflow=19,
	EExcAbort=20,
	EExcKill=21,
	EExcUserInterrupt=22,
	EExcDataAbort=23,
	EExcCodeAbort=24,
	EExcMaxNumber=25,
	EExcInvalidVector=26,
	};

enum TExitType {EExitKill,EExitTerminate,EExitPanic,EExitPending};
enum TAlign {ELeft,ECenter,ERight};

const TInt KRealFormatTypesMask=0x00000007;
const TInt KRealFormatFixed=1;
const TInt KRealFormatExponent=2;
const TInt KRealFormatGeneral=3;
const TInt KRealFormatNoExponent=4;
const TInt KRealFormatCalculator=5;

// Extra flags ORed in with the previous types

const TInt KRealFormatTypeFlagsMask=0x7C000000;
const TInt KExtraSpaceForSign=0x40000000;
const TInt KAllowThreeDigitExp=0x20000000;
const TInt KUseSigFigs=0x10000000;
const TInt KDoNotUseTriads=0x08000000;
const TInt KGeneralLimit=0x04000000;

enum TLeave {ELeave};
enum TFirstWeekRule {EFirstWeek,EFirstFourDayWeek,EFirstFullWeek};

enum TTimerLockSpec
	{
	EOneOClock,
	ETwoOClock,
	EThreeOClock,
	EFourOClock,
	EFiveOClock,
	ESixOClock,
	ESevenOClock,
	EEightOClock,
	ENineOClock,
	ETenOClock,
	EElevenOClock,
	ETwelveOClock
	};

typedef TInt (*TThreadFunction)(TAny *aPtr);
typedef TInt (*TLibraryFunction)();
typedef TInt (*TLibraryEntry)(TDllReason aReason);

inline TInt Lim(TInt aVal,TUint aLimit)
	{return(((TUint)aVal)<=aLimit);}

inline TInt LimX(TInt aVal,TUint aLimit)
	{return(((TUint)aVal)<aLimit);}

template <class T>
inline T Min(T aLeft,T aRight)
	{return(aLeft<aRight ? aLeft : aRight);}

template <class T>
inline T Min(T aLeft,TUint aRight)
	{return(aLeft<(TInt)aRight ? aLeft : (T)aRight);}

template <class T>
inline T Max(T aLeft,T aRight)
	{return(aLeft<aRight ? aRight : aLeft);}

template <class T>
inline T Max(T aLeft,TUint aRight)
	{return(aLeft<(TInt)aRight ? (TInt)aRight : aLeft);}

template <class T>
inline T Abs(T aVal)
	{return(aVal<0 ? -aVal : aVal);}

template <class T>
inline TBool Rng(T aMin,T aVal,T aMax)
	{return(aVal>=aMin && aVal<=aMax);}

template <class T,class S>
inline T* PtrAdd(T* aPtr,S aVal)
	{return((T*)(((TUint8*)aPtr)+aVal));}

template <class T,class S>
inline T* PtrSub(T* aPtr,S aVal)
	{return((T*)(((TUint8*)aPtr)-aVal));}

template <class T>
inline T Align2(T aValue)
	{return((T)((((TUint)aValue)+sizeof(TUint16)-1)&~(sizeof(TUint16)-1)));}

template <class T>
inline T Align4(T aValue)
	{return((T)((((TUint)aValue)+sizeof(TUint32)-1)&~(sizeof(TUint32)-1)));}

class TInt64
	{
public:
	inline TInt64();
	IMPORT_C TInt64(TInt aVal);
	inline TInt64(TUint aVal);
	inline TInt64(TUint aHigh,TUint aLow);
	IMPORT_C TInt64(TReal aVal);
	inline void Set(TUint aHigh,TUint aLow);
	inline TUint Low() const;
	inline TUint High() const;
	IMPORT_C TInt GetTInt() const;
	IMPORT_C TReal GetTReal() const;
	IMPORT_C TInt64 &operator=(TInt aVal);
	inline TInt64& operator=(TUint aVal);
	IMPORT_C TInt64& operator=(TReal aVal);
	IMPORT_C TInt64& operator+=(const TInt64 &aVal);
	IMPORT_C TInt64& operator-=(const TInt64 &aVal);
	IMPORT_C TInt64& operator*=(const TInt64 &aVal);
	IMPORT_C TInt64& operator/=(const TInt64 &aVal);
	IMPORT_C TInt64& operator%=(const TInt64 &aVal);
	IMPORT_C TInt64& operator>>=(TInt aShift);
	IMPORT_C TInt64& operator<<=(TInt aShift);
	IMPORT_C TInt64 operator+() const;
	IMPORT_C TInt64 operator-() const;
	IMPORT_C TInt64& operator++();
	IMPORT_C TInt64 operator++(TInt);
	IMPORT_C TInt64& operator--();
	IMPORT_C TInt64 operator--(TInt);
	IMPORT_C TInt64 operator+(const TInt64 &aVal) const;
	IMPORT_C TInt64 operator-(const TInt64 &aVal) const;
	IMPORT_C TInt64 operator*(const TInt64 &aVal) const;
	IMPORT_C TInt64 operator/(const TInt64 &aVal) const;
	IMPORT_C TInt64 operator%(const TInt64 &aVal) const;
	IMPORT_C TInt64 operator>>(TInt aShift) const;
	IMPORT_C TInt64 operator<<(TInt aShift) const;
	IMPORT_C void Lsr(TInt aShift);
	IMPORT_C void Mul10();
	IMPORT_C TInt MulTop(const TInt64 &aVal);
	IMPORT_C void DivMod(const TInt64 &aVal,TInt64 &aRemainder);
	IMPORT_C TInt operator==(const TInt64 &aVal) const;
	IMPORT_C TInt operator!=(const TInt64 &aVal) const;
	IMPORT_C TInt operator>=(const TInt64 &aVal) const;
	IMPORT_C TInt operator<=(const TInt64 &aVal) const;
	IMPORT_C TInt operator>(const TInt64 &aVal) const;
	IMPORT_C TInt operator<(const TInt64 &aVal) const;
protected:
	TUint iLow;
	TUint iHigh;
	};

typedef void TExceptionHandler(TExcType);

// masking constants

const TUint KExceptionAbort=0x01;
const TUint KExceptionKill=0x02;
const TUint KExceptionUserInterrupt=0x04;
const TUint KExceptionFpe=0x08;
const TUint KExceptionFault=0x10;
const TUint KExceptionInteger=0x20;
const TUint KExceptionDebug=0x40;

template <class T>
class TRefByValue
	{
public:
	inline TRefByValue(T& aRef);
	inline operator T&();
private:
	TRefByValue& operator=(TRefByValue aRef);
private:
	T &iRef;
	};

class TFunctor
	{
public:
	IMPORT_C virtual void operator()() =0;
	};

class TCallBack
	{
public:
	inline TCallBack();
	inline TCallBack(TInt (*aFunction)(TAny* aPtr));
	inline TCallBack(TInt (*aFunction)(TAny* aPtr),TAny* aPtr);
	inline TInt CallBack() const;
public:
	TInt (*iFunction)(TAny* aPtr);
	TAny* iPtr;
	};

class TSglQueLink
	{
#if defined _DEBUG
public:
	inline TSglQueLink() : iNext(NULL) {}
#endif
private:
	IMPORT_C void Enque(TSglQueLink* aLink);
public:
	TSglQueLink* iNext;
	friend class TSglQueBase;
	};

class TDblQueLinkBase
	{
public:
	inline TDblQueLinkBase() : iNext(NULL) {}
	IMPORT_C void Enque(TDblQueLinkBase* aLink);
	IMPORT_C void AddBefore(TDblQueLinkBase* aLink);
public:
	TDblQueLinkBase* iNext;
	TDblQueLinkBase* iPrev;
	};

class TDblQueLink : public TDblQueLinkBase
	{
public:
	IMPORT_C void Deque();
	};

class TPriQueLink : public TDblQueLink
	{
public:
	TInt iPriority;
	};

class TDeltaQueLink : public TDblQueLinkBase
	{
public:
	TInt iDelta;
	};

class TSglQueBase
	{
public:
	IMPORT_C TBool IsEmpty() const;
	IMPORT_C void SetOffset(TInt anOffset);
	IMPORT_C void Reset();
protected:
	IMPORT_C TSglQueBase();
	IMPORT_C TSglQueBase(TInt anOffset);
	IMPORT_C void DoAddFirst(TAny* aPtr);
	IMPORT_C void DoAddLast(TAny* aPtr);
	IMPORT_C void DoRemove(TAny* aPtr);
protected:
	TSglQueLink* iHead;
	TSglQueLink* iLast;
	TInt iOffset;
private:
	TSglQueBase(const TSglQueBase& aQue);
	TSglQueBase &operator=(const TSglQueBase& aQue);
	friend class TSglQueIterBase;
	};

class TDblQueBase
	{
public:
	IMPORT_C TBool IsEmpty() const;
	IMPORT_C void SetOffset(TInt anOffset);
	IMPORT_C void Reset();
protected:
	IMPORT_C TDblQueBase();
	IMPORT_C TDblQueBase(TInt anOffset);
	IMPORT_C void DoAddFirst(TAny* aPtr);
	IMPORT_C void DoAddLast(TAny* aPtr);
	IMPORT_C void DoAddPriority(TAny* aPtr);
	IMPORT_C void __DbgTestEmpty() const;
protected:
	TDblQueLink iHead;
	TInt iOffset;
private:
	TDblQueBase(const TSglQueBase& aQue);
	TDblQueBase& operator=(const TSglQueBase& aQue);
	friend class TDblQueIterBase;
	};

class TDeltaQueBase : public TDblQueBase
	{
public:
	IMPORT_C TBool CountDown();
	IMPORT_C TBool CountDown(TInt aValue);
	IMPORT_C TBool FirstDelta(TInt& aValue);
	IMPORT_C void Reset();
protected:
	IMPORT_C TDeltaQueBase();
	IMPORT_C TDeltaQueBase(TInt anOffset);
	IMPORT_C void DoAddDelta(TAny* aPtr,TInt aDelta);
	IMPORT_C void DoRemove(TAny* aPtr);
	IMPORT_C TAny* DoRemoveFirst();
protected:
	TInt* iFirstDelta;
	};

template <class T>
class TSglQue : public TSglQueBase
	{
public:
	inline TSglQue();
	inline TSglQue(TInt anOffset);
	inline void AddFirst(T& aRef);
	inline void AddLast(T& aRef);
	inline TBool IsFirst(const T* aPtr) const;
	inline TBool IsLast(const T* aPtr) const;
	inline T* First() const;
	inline T* Last() const;
	inline void Remove(T& aRef);
	};

template <class T>
class TDblQue : public TDblQueBase
	{
public:
	inline TDblQue();
	inline TDblQue(TInt anOffset);
	inline void AddFirst(T& aRef);
	inline void AddLast(T& aRef);
	inline TBool IsHead(const T* aPtr) const;
	inline TBool IsFirst(const T* aPtr) const;
	inline TBool IsLast(const T* aPtr) const;
	inline T* First() const;
	inline T* Last() const;
	};

template <class T>
class TPriQue : public TDblQueBase
	{
public:
	inline TPriQue();
	inline TPriQue(TInt anOffset);
	inline void Add(T& aRef);
	inline TBool IsHead(const T* aPtr) const;
	inline TBool IsFirst(const T* aPtr) const;
	inline TBool IsLast(const T* aPtr) const;
	inline T* First() const;
	inline T* Last() const;
	};

template <class T>
class TDeltaQue : public TDeltaQueBase
	{
public:
	inline TDeltaQue();
	inline TDeltaQue(TInt anOffset);
	inline void Add(T& aRef,TInt aDelta);
	inline void Remove(T& aRef);
	inline T* RemoveFirst();
	};

class TSglQueIterBase
	{
public:
	IMPORT_C void SetToFirst();
protected:
	IMPORT_C TSglQueIterBase(TSglQueBase& aQue);
	IMPORT_C TAny* DoPostInc();
	IMPORT_C TAny* DoCurrent();
	IMPORT_C void DoSet(TAny* aLink);
protected:
	TInt iOffset;
	TSglQueLink* iHead;
	TSglQueLink* iNext;
	};

template <class T>
class TSglQueIter : public TSglQueIterBase
	{
public:
	inline TSglQueIter(TSglQueBase& aQue);
	inline void Set(T& aLink);
	inline operator T*();
	inline T* operator++(TInt);
	};

class TDblQueIterBase
	{
public:
	IMPORT_C void SetToFirst();
	IMPORT_C void SetToLast();
protected:
	IMPORT_C TDblQueIterBase(TDblQueBase& aQue);
	IMPORT_C TAny* DoPostInc();
	IMPORT_C TAny* DoPostDec();
	IMPORT_C TAny* DoCurrent();
	IMPORT_C void DoSet(TAny* aLink);
protected:
	TInt iOffset;
	TDblQueLinkBase* iHead;
	TDblQueLinkBase* iNext;
	};
//
template <class T>
class TDblQueIter : public TDblQueIterBase
	{
public:
	inline TDblQueIter(TDblQueBase& aQue);
	inline void Set(T& aLink);
	inline operator T*();
	inline T* operator++(TInt);
	inline T* operator--(TInt);
	};

enum TKeyCmpText
	{
	ECmpNormal,ECmpNormal8,ECmpNormal16,
	ECmpFolded,ECmpFolded8,ECmpFolded16,
	ECmpCollated,ECmpCollated8,ECmpCollated16
	};

enum TKeyCmpNumeric
	{
	ECmpTInt8=((ECmpCollated16+1)<<1),ECmpTInt16,ECmpTInt32,ECmpTInt,
	ECmpTUint8,ECmpTUint16,ECmpTUint32,ECmpTUint,
	ECmpTInt64
	};

class TKey
	{
public:
	inline void SetPtr(const TAny* aPtr);
	IMPORT_C virtual TInt Compare(TInt aLeft,TInt aRight) const;
	IMPORT_C virtual TAny* At(TInt anIndex) const;
protected:
	IMPORT_C TKey();
	IMPORT_C TKey(TInt anOffset,TKeyCmpText aType);
	IMPORT_C TKey(TInt anOffset,TKeyCmpText aType,TInt aLength);
	IMPORT_C TKey(TInt anOffset,TKeyCmpNumeric aType);
protected:
	TInt iKeyOffset;
	TInt iKeyLength;
	TInt iCmpType;
	const TAny* iPtr;
	};

class TSwap
	{
public:
	IMPORT_C TSwap();
	IMPORT_C virtual void Swap(TInt aLeft,TInt aRight) const;
	};

class TDesC16;	// forward declaration for TChar member functions
class TPtrC16;	// forward declaration for TChar member functions

class TChar
	{
public:

	/*
	General Unicode character category: these are composed of a high nybble encoding the major category
	(Mark, Number, etc.) and a low nybble for the subdivisions of that category.
	*/
	enum TCategory
		{
		EAlphaGroup = 0x00,								// alphabetic letters
		ELetterOtherGroup = 0x10,						// other letters
		ELetterModifierGroup = 0x20,					// letter modifiers
		EMarkGroup = 0x30,
		ENumberGroup = 0x40,
		EPunctuationGroup = 0x50,
		ESymbolGroup = 0x60,
		ESeparatorGroup = 0x70,
		EControlGroup = 0x80,
		EMaxAssignedGroup = 0xE0,
		EUnassignedGroup = 0xF0,

		ELuCategory = EAlphaGroup | 0,					// Letter, Uppercase
		ELlCategory = EAlphaGroup | 1,					// Letter, Lowercase
		ELtCategory = EAlphaGroup | 2,					// Letter, Titlecase
		ELoCategory = ELetterOtherGroup | 0,			// Letter, Other
		EMaxLetterCategory = ELetterOtherGroup | 0x0F,	// the highest possible (non-modifier) letter category

		ELmCategory = ELetterModifierGroup | 0,			// Letter, Modifier
		EMaxLetterOrLetterModifierCategory = ELetterModifierGroup | 0x0F, // the highest possible letter category

		EMnCategory = EMarkGroup | 0,					// Mark, Non-Spacing
		EMcCategory = EMarkGroup | 1,					// Mark, Combining
		EMeCategory = EMarkGroup | 2,					// Mark, Enclosing
		ENdCategory = ENumberGroup | 0,					// Number, Decimal Digit
		ENlCategory = ENumberGroup | 1,					// Number, Letter
		ENoCategory = ENumberGroup | 2,					// Number, Other
		EPcCategory = EPunctuationGroup | 0,			// Punctuation, Connector
		EPdCategory = EPunctuationGroup | 1,			// Punctuation, Dash
		EPsCategory = EPunctuationGroup | 2,			// Punctuation, Open
		EPeCategory = EPunctuationGroup | 3,			// Punctuation, Close
		EPiCategory = EPunctuationGroup | 4,			// Punctuation, Initial Quote
		EPfCategory = EPunctuationGroup | 5,			// Punctuation, Final Quote
		EPoCategory = EPunctuationGroup | 6,			// Punctuation, Other
		ESmCategory = ESymbolGroup | 0,					// Symbol, Math
		EScCategory = ESymbolGroup | 1,					// Symbol, Currency
		ESkCategory = ESymbolGroup | 2,					// Symbol, Modifier
		ESoCategory = ESymbolGroup | 3,					// Symbol, Other
		EMaxGraphicCategory = ESymbolGroup | 0x0F,		// the highest possible graphic character category

		EZsCategory = ESeparatorGroup | 0,				// Separator, Space
		EMaxPrintableCategory = EZsCategory,			// the highest possible printable character category

		EZlCategory = ESeparatorGroup | 1,				// Separator, Line
		EZpCategory = ESeparatorGroup | 2,				// Separator, Paragraph
		ECcCategory = EControlGroup | 0,				// Other, Control
		ECfCategory = EControlGroup | 1,				// Other, Format
		EMaxAssignedCategory = EMaxAssignedGroup | 0x0F,// the highest possible category for assigned 16-bit characters;
														// does not include surrogates, which are interpreted as pairs
														// and have no meaning on their own

		ECsCategory = EUnassignedGroup | 0,				// Other, Surrogate
		ECoCategory = EUnassignedGroup | 1,				// Other, Private Use
		ECnCategory = EUnassignedGroup | 2				// Other, Not Assigned
		};

	// Bidirectional Unicode character category
	enum TBdCategory
		{
		ELeftToRight,				// L Left-to-Right 
		ELeftToRightEmbedding,		// LRE Left-to-Right Embedding 
		ELeftToRightOverride,		// LRO Left-to-Right Override 
		ERightToLeft,				// R Right-to-Left 
		ERightToLeftArabic,			// AL Right-to-Left Arabic 
		ERightToLeftEmbedding,		// RLE Right-to-Left Embedding 
		ERightToLeftOverride,		// RLO Right-to-Left Override 
		EPopDirectionalFormat,		// PDF Pop Directional Format 
		EEuropeanNumber,			// EN European Number 
		EEuropeanNumberSeparator,	// ES European Number Separator 
		EEuropeanNumberTerminator,	// ET European Number Terminator 
		EArabicNumber,				// AN Arabic Number 
		ECommonNumberSeparator,		// CS Common Number Separator 
		ENonSpacingMark,			// NSM Non-Spacing Mark 
		EBoundaryNeutral,			// BN Boundary Neutral 
		EParagraphSeparator,		// B Paragraph Separator 
		ESegmentSeparator,			// S Segment Separator 
		EWhitespace,				// WS Whitespace 
		EOtherNeutral				// ON Other Neutrals 
		};

	// Width as known to East Asian encodings.
	enum TCjkWidth
		{
		ENeutralWidth,			// includes 'ambiguous width' defined in Unicode Technical Report 11: East Asian Width;
		EHalfWidth,				// other categories are as defined in the report
		EFullWidth,
		ENarrow,
		EWide
		};

  	// Encoding systems: used by the translation functions
  	enum TEncoding
  		{
  		EUnicode,				// the Unicode encoding
  		EShiftJIS				// the shift-JIS encoding (used in Japan)
  		};
  
	// Flags passed to the Fold() function.
	enum
		{
		EFoldCase = 1,			// convert characters to their lower case form if any
		EFoldAccents = 2,		// strip accents
		EFoldDigits = 4,		// convert digits representing values 0..9 to characters '0'..'9'
		EFoldSpaces = 8,		// convert all spaces (ordinary, fixed-width, ideographic, etc.) to ' '
		EFoldKana = 16,			// convert hiragana to katakana
		EFoldWidth = 32,		// fold fullwidth and halfwidth variants to their standard forms
		EFoldStandard = EFoldCase | EFoldAccents | EFoldDigits | EFoldSpaces,
								// perform standard folding operations; those done by Fold with no argument

		EFoldAll = -1			// perform all possible folding operations
		};

	// A structure used to return information about a Unicode character.
	struct TCharInfo
		{
		TCategory iCategory;				// general category
		TBdCategory iBdCategory;			// bidirectional category
		TInt iCombiningClass;				// combining class
		TUint iLowerCase;					// lower case form
		TUint iUpperCase;					// upper case form
		TUint iTitleCase;					// title case form
		TBool iMirrored;					// true if the character is mirrored
		TInt iNumericValue;					// integer numeric value: -1 if none, -2 if a fraction
		};

	inline TChar();
	inline TChar(TUint aChar);
	inline TChar& operator-=(TUint aChar);
	inline TChar& operator+=(TUint aChar);
	inline TChar operator-(TUint aChar);
	inline TChar operator+(TUint aChar);
	inline operator TUint() const;
	inline void Fold();
	inline void LowerCase();
	inline void UpperCase();
	inline TBool Eos() const;
	IMPORT_C TUint GetUpperCase() const;
	IMPORT_C TUint GetLowerCase() const;
	IMPORT_C TBool IsLower() const;
	IMPORT_C TBool IsUpper() const;
	IMPORT_C TBool IsAlpha() const;
	IMPORT_C TBool IsDigit() const;
	IMPORT_C TBool IsAlphaDigit() const;
	IMPORT_C TBool IsHexDigit() const;
	IMPORT_C TBool IsSpace() const;
	IMPORT_C TBool IsPunctuation() const;
	IMPORT_C TBool IsGraph() const;
	IMPORT_C TBool IsPrint() const;
	IMPORT_C TBool IsControl() const;
	inline void Fold(TInt aFlags);
	inline void TitleCase();
	IMPORT_C TUint GetTitleCase() const;
	IMPORT_C TBool IsTitle() const;
	IMPORT_C TBool IsAssigned() const;
	IMPORT_C void GetInfo(TCharInfo& aInfo) const;
	IMPORT_C TCategory GetCategory() const;
	IMPORT_C TBdCategory GetBdCategory() const;
	IMPORT_C TInt GetCombiningClass() const;
	IMPORT_C TBool IsMirrored() const;
	IMPORT_C TInt GetNumericValue() const;
	IMPORT_C TCjkWidth GetCjkWidth() const;
	IMPORT_C static TBool Compose(TUint& aResult,const TDesC16& aSource);
	IMPORT_C TBool Decompose(TPtrC16& aResult) const;
  	IMPORT_C TBool TranslateFromUnicode(TUint& aCode,TEncoding aEncoding) const;
  	IMPORT_C static TBool TranslateToUnicode(TUint& aTo,TUint aFrom,TEncoding aEncoding);

protected:
	inline void SetChar(TUint aChar);
private:
	TUint iChar;
	__DECLARE_TEST;
	};

class TCharF : public TChar
	{
public:
	inline TCharF(TUint aChar);
	inline TCharF(const TChar &aChar);
	inline TCharF& operator=(TUint aChar);
	inline TCharF& operator=(const TChar &aChar);
	};

class TCharLC : public TChar
	{
public:
	inline TCharLC(TUint aChar);
	inline TCharLC(const TChar& aChar);
	inline TCharLC& operator=(TUint aChar);
	inline TCharLC& operator=(const TChar& aChar);
	};

class TCharUC : public TChar
	{
public:
	inline TCharUC(TUint aChar);
	inline TCharUC(const TChar& aChar);
	inline TCharUC& operator=(TUint aChar);
	inline TCharUC& operator=(const TChar& aChar);
	};

class TRealFormat
	{
public:
	IMPORT_C TRealFormat();
	IMPORT_C TRealFormat(TInt aWidth);
	IMPORT_C TRealFormat(TInt aWidth,TInt aDecimalPlaces);
public:
	TInt iType;
	TInt iWidth;
	TInt iPlaces;
	TChar iPoint;
	TChar iTriad;
	TInt iTriLen;
	};

#include <e32des8.h>
#include <e32des16.h>

#define __Align(s) ((((s)+__Size-1)/__Size)*__Size)

#if defined(_UNICODE)
#define __Size (sizeof(TUint)/sizeof(TUint16))
typedef TDesC16 TDesC;
typedef TPtrC16 TPtrC;
typedef TDes16 TDes;
typedef TPtr16 TPtr;
typedef HBufC16 HBufC;
typedef TDes16Overflow TDesOverflow;
#else
#define __Size (sizeof(TUint)/sizeof(TUint8))
typedef TDesC8 TDesC;
typedef TPtrC8 TPtrC;
typedef TDes8 TDes;
typedef TPtr8 TPtr;
typedef HBufC8 HBufC;
typedef TDes8Overflow TDesOverflow;
#endif

template <TInt S>
#ifdef _UNICODE
class TBufC : public TBufCBase16
#else
class TBufC : public TBufCBase8
#endif
	{
public:
	inline TBufC();
	inline TBufC(const TText* aString);
	inline TBufC(const TDesC& aDes);
	inline TBufC<S>& operator=(const TText* aString);
	inline TBufC<S>& operator=(const TDesC& aDes);
	inline TPtr Des();
private:
	TText iBuf[__Align(S)];
	};

template <TInt S>
#ifdef _UNICODE
class TBuf : public TBufBase16
#else
class TBuf : public TBufBase8
#endif
	{
public:
	inline TBuf();
	inline TBuf(TInt aLength);
	inline TBuf(const TText* aString);
	inline TBuf(const TDesC& aDes);
	inline TBuf<S>& operator=(const TText* aString);
	inline TBuf<S>& operator=(const TDesC& aDes);
	inline TBuf<S>& operator=(const TBuf<S>& aBuf);
private:
	TText iBuf[__Align(S)];
	};

typedef TRefByValue<const TDesC> __TRefDesC;
template <TInt S>
class TLitC
	{
public:
	enum {BufferSize=S-1};
	inline const TDesC* operator&() const;
	inline operator const TDesC&() const;
	inline const TDesC& operator()() const;
	inline operator const __TRefDesC() const;
public:
#if !defined(_UNICODE)
	typedef TUint8 __TText;
#elif defined(__GCC32__)
	typedef __wchar_t __TText;
#elif defined(__VC32__)
	typedef TUint16 __TText;
#else
#error  no typedef for __TText
#endif
public:
	TUint iTypeLength;
	__TText iBuf[__Align(S)];
	};

_LIT(KNullDesC,"");
_LIT8(KNullDesC8,"");
_LIT16(KNullDesC16,"");

template <class T>
class TPckgC : public TPtrC8
	{
public:
	inline TPckgC(const T& aRef);
	inline const T& operator()() const;
private:
	TPckgC<T>& operator=(const TPckgC<T>& aRef);
	};

template <class T>
class TPckg : public TPtr8
	{
public:
	inline TPckg(const T& aRef);
	inline T& operator()();
private:
	TPckg<T>& operator=(const TPckg<T>& aRef);
	};

template <class T>
class TPckgBuf : public TBuf8<sizeof(T)>
	{
public:
	inline TPckgBuf();
	inline TPckgBuf(const T& aRef);
	inline TPckgBuf& operator=(const TPckgBuf<T>& aRef);
	inline T& operator=(const T& aRef);
	inline T& operator()();
	};

typedef TBuf<KMaxName> TName;
typedef TBuf<KMaxInfoName> TInfoName;
typedef TBuf<KMaxFullName> TFullName;
typedef TBuf<KMaxExitCategoryName> TExitCategoryName;
typedef TBuf<KMaxFileName> TFileName;
typedef TBuf<KMaxPath> TPath;
typedef TBuf<KMaxDeviceInfo> TDeviceInfo;
typedef TBuf<KMaxVersionName> TVersionName;
typedef TBuf<KMaxPassword> TPassword;

class TLexMark8
	{
public:
	inline TLexMark8();
private:
	inline TLexMark8(const TUint8* aString);
	const TUint8* iPtr;
	friend class TLex8;
	__DECLARE_TEST;
	};

class TRealX;
class TLex8
	{
public:
	IMPORT_C TLex8();
	inline TLex8(const TUint8* aString);
	inline TLex8(const TDesC8& aDes);
	inline TLex8& operator=(const TUint8* aString);
	inline TLex8& operator=(const TDesC8& aDes);
	inline TBool Eos() const;
	inline void Mark(TLexMark8& aMark) const;
	inline void Mark();
	IMPORT_C void Inc();
	IMPORT_C void Inc(TInt aNumber);
	IMPORT_C TChar Get();
	IMPORT_C TChar Peek() const;
	IMPORT_C void UnGet();
	inline void UnGetToMark();
	IMPORT_C void UnGetToMark(const TLexMark8 aMark);
	IMPORT_C void SkipSpace();
	inline void SkipAndMark(TInt aNumber);
	IMPORT_C void SkipAndMark(TInt aNumber, TLexMark8& aMark);
	inline void SkipSpaceAndMark();
	IMPORT_C void SkipSpaceAndMark(TLexMark8& aMark);
	IMPORT_C void SkipCharacters();
	inline TInt TokenLength() const;
	IMPORT_C TInt TokenLength(const TLexMark8 aMark) const;
	IMPORT_C TPtrC8 MarkedToken() const;
	IMPORT_C TPtrC8 MarkedToken(const TLexMark8 aMark) const;
	IMPORT_C TPtrC8 NextToken();
	IMPORT_C TPtrC8 Remainder() const;
	IMPORT_C TPtrC8 RemainderFromMark() const;
	IMPORT_C TPtrC8 RemainderFromMark(const TLexMark8 aMark) const;
	IMPORT_C TInt Offset() const;
	inline TInt MarkedOffset() const;
	IMPORT_C TInt MarkedOffset(const TLexMark8 aMark) const;
	IMPORT_C TInt Val(TInt8& aVal);
	IMPORT_C TInt Val(TInt16& aVal);
	IMPORT_C TInt Val(TInt32& aVal);
	IMPORT_C TInt Val(TInt64& aVal);
	inline TInt Val(TInt& aVal);
	IMPORT_C TInt Val(TUint8& aVal,TRadix aRadix);
	IMPORT_C TInt Val(TUint16& aVal,TRadix aRadix);
	IMPORT_C TInt Val(TUint32& aVal,TRadix aRadix);
	IMPORT_C TInt Val(TInt64& aVal,TRadix aRadix);
	inline TInt Val(TUint& aVal,TRadix aRadix=EDecimal);
	IMPORT_C TInt Val(TInt32& aVal,TInt aLimit);
	IMPORT_C TInt Val(TInt64& aVal,const TInt64& aLimit);
	IMPORT_C TInt Val(TUint32& aVal,TRadix aRadix,TUint aLimit);
	IMPORT_C TInt Val(TInt64& aVal,TRadix aRadix,const TInt64 &aLimit);
	IMPORT_C TInt Val(TReal32& aVal);
	IMPORT_C TInt Val(TReal32& aVal,TChar aPoint);
	IMPORT_C TInt Val(TReal64& aVal);
	IMPORT_C TInt Val(TReal64& aVal,TChar aPoint);
	inline void Assign(const TLex8& aLex);
	IMPORT_C void Assign(const TUint8* aString);
	IMPORT_C void Assign(const TDesC8& aDes);
	TInt Val(TRealX& aVal);
	TInt Val(TRealX& aVal, TChar aPoint);
private:
	void Scndig(TInt& aSig,TInt& aExp,TInt64& aDl);
	void ScndigAfterPoint(TInt& aSig,TInt64& aDl);
	void ValidateMark(const TLexMark8 aMark) const;
private:
	const TUint8* iNext;
	const TUint8* iBuf;
	const TUint8* iEnd;
	TLexMark8 iMark;
	__DECLARE_TEST;
	};

class TLexMark16
	{
public:
	inline TLexMark16();
private:
	inline TLexMark16(const TUint16* aString);
	const TUint16* iPtr;
	friend class TLex16;	
	__DECLARE_TEST;
	};

class TLex16
	{
public:
	IMPORT_C TLex16();
	inline TLex16(const TUint16* aString);
	inline TLex16(const TDesC16& aDes);
	inline TLex16& operator=(const TUint16* aString);
	inline TLex16& operator=(const TDesC16& aDes);
	inline TBool Eos() const;
	inline void Mark();
	inline void Mark(TLexMark16& aMark) const;
	IMPORT_C void Inc();
	IMPORT_C void Inc(TInt aNumber);
	IMPORT_C TChar Get();
	IMPORT_C TChar Peek() const;
	IMPORT_C void UnGet();
	inline void UnGetToMark();
	IMPORT_C void UnGetToMark(const TLexMark16 aMark);
	IMPORT_C void SkipSpace();
	inline void SkipAndMark(TInt aNumber);
	IMPORT_C void SkipAndMark(TInt aNumber, TLexMark16& aMark);
	IMPORT_C void SkipSpaceAndMark(TLexMark16& aMark);
	inline void SkipSpaceAndMark();
	IMPORT_C void SkipCharacters();
	inline TInt TokenLength() const;
	IMPORT_C TInt TokenLength(const TLexMark16 aMark) const;
	IMPORT_C TPtrC16 MarkedToken() const;
	IMPORT_C TPtrC16 MarkedToken(const TLexMark16 aMark) const;
	IMPORT_C TPtrC16 NextToken();
	IMPORT_C TPtrC16 Remainder() const;
	IMPORT_C TPtrC16 RemainderFromMark() const;
	IMPORT_C TPtrC16 RemainderFromMark(const TLexMark16 aMark) const;
	IMPORT_C TInt Offset() const;
	inline TInt MarkedOffset() const;
	IMPORT_C TInt MarkedOffset(const TLexMark16 aMark) const;
	IMPORT_C TInt Val(TInt8& aVal);
	IMPORT_C TInt Val(TInt16& aVal);
	IMPORT_C TInt Val(TInt32& aVal);
	IMPORT_C TInt Val(TInt64& aVal);
	inline TInt Val(TInt& aVal);
	IMPORT_C TInt Val(TUint8& aVal,TRadix aRadix);
	IMPORT_C TInt Val(TUint16& aVal,TRadix aRadix);
	IMPORT_C TInt Val(TUint32& aVal,TRadix aRadix);
	IMPORT_C TInt Val(TInt64& aVal,TRadix aRadix);
	inline TInt Val(TUint& aVal,TRadix aRadix=EDecimal);
	IMPORT_C TInt Val(TInt32& aVal,TInt aLimit);
	IMPORT_C TInt Val(TInt64& aVal,const TInt64& aLimit);
	IMPORT_C TInt Val(TUint32& aVal,TRadix aRadix,TUint aLimit);
	IMPORT_C TInt Val(TInt64& aVal,TRadix aRadix,const TInt64& aLimit);
	IMPORT_C TInt Val(TReal32& aVal);
	IMPORT_C TInt Val(TReal32& aVal,TChar aPoint);
	IMPORT_C TInt Val(TReal64& aVal);
	IMPORT_C TInt Val(TReal64& aVal,TChar aPoint);
	inline void Assign(const TLex16& aLex);
	IMPORT_C void Assign(const TUint16* aString);
	IMPORT_C void Assign(const TDesC16& aDes);		
	TInt Val(TRealX& aVal);
	TInt Val(TRealX& aVal, TChar aPoint);
private:
	void Scndig(TInt& aSig,TInt& aExp,TInt64& aDl);
	void ValidateMark(const TLexMark16 aMark) const;
private:
	const TUint16* iNext;
	const TUint16* iBuf;
	const TUint16* iEnd;
	TLexMark16 iMark;
	__DECLARE_TEST;
	};

#if defined(_UNICODE)
typedef TLex16 TLex;
typedef TLexMark16 TLexMark;
#else
typedef TLex8 TLex;
typedef TLexMark8 TLexMark;
#endif

typedef TBuf<KMaxUidName> TUidName;
class TUid
	{
public:
	IMPORT_C TInt operator==(const TUid& aUid) const;
	IMPORT_C TInt operator!=(const TUid& aUid) const;
	IMPORT_C TUidName Name() const;
	static inline TUid Uid(TInt aUid);
	static inline TUid Null();
public:
	TInt32 iUid;
	};

class TUidType
	{
public:
	IMPORT_C TUidType();
	IMPORT_C TUidType(TUid aUid1);
	IMPORT_C TUidType(TUid aUid1,TUid aUid2);
	IMPORT_C TUidType(TUid aUid1,TUid aUid2,TUid aUid3);
	IMPORT_C TInt operator==(const TUidType& aUidType) const;
	IMPORT_C TInt operator!=(const TUidType& aUidType) const;
	IMPORT_C const TUid& operator[](TInt anIndex) const;
	IMPORT_C TUid MostDerived() const;
	IMPORT_C TBool IsPresent(TUid aUid) const;
	IMPORT_C TBool IsValid() const;
private:
	TUid iUid[KMaxCheckedUid];
	};

class TCheckedUid
	{
public:
	IMPORT_C TCheckedUid();
	IMPORT_C TCheckedUid(const TUidType& aUidType);
	IMPORT_C TCheckedUid(const TDesC8& aPtr);
	IMPORT_C void Set(const TUidType& aUidType);
	IMPORT_C void Set(const TDesC8& aPtr);
	IMPORT_C TPtrC8 Des() const;
	inline const TUidType& UidType() const;
protected:
	IMPORT_C TUint Check() const;
private:
	TUidType iType;
	TUint iCheck;
	};

class TVersion
	{
public:
	IMPORT_C TVersion();
	IMPORT_C TVersion(TInt aMajor,TInt aMinor,TInt aBuild);
	IMPORT_C TVersionName Name();
public:
	TInt8 iMajor;
	TInt8 iMinor;
	TInt16 iBuild;
	};

class TDateTime
	{
public:
	inline TDateTime();
	IMPORT_C TDateTime(TInt aYear,TMonth aMonth,TInt aDay,TInt aHour,TInt aMinute, TInt aSecond,TInt aMicroSecond);
	IMPORT_C TInt Set(TInt aYear,TMonth aMonth,TInt aDay,TInt aHour,TInt aMinute, TInt aSecond,TInt aMicroSecond);
	IMPORT_C TInt SetYear(TInt aYear);
	IMPORT_C TInt SetYearLeapCheck(TInt aYear);
	IMPORT_C TInt SetMonth(TMonth aMonth);
	IMPORT_C TInt SetDay(TInt aDay);
	IMPORT_C TInt SetHour(TInt aHour);
	IMPORT_C TInt SetMinute(TInt aMinute);
	IMPORT_C TInt SetSecond(TInt aSecond);
	IMPORT_C TInt SetMicroSecond(TInt aMicroSecond);
	inline TInt Year() const;
	inline TMonth Month() const;
	inline TInt Day() const;
	inline TInt Hour() const;
	inline TInt Minute() const;
	inline TInt Second() const;
	inline TInt MicroSecond() const;
private:
	TInt iYear;
	TMonth iMonth;
	TInt iDay;
	TInt iHour;
	TInt iMinute;
	TInt iSecond;
	TInt iMicroSecond;
	};

class TTimeIntervalMicroSeconds
	{
public:
	inline TTimeIntervalMicroSeconds();
	inline TTimeIntervalMicroSeconds(const TInt64& aInterval);
	inline TTimeIntervalMicroSeconds& operator=(const TInt64& aInterval);
	inline TBool operator==(const TTimeIntervalMicroSeconds& aInterval) const;
	inline TBool operator!=(const TTimeIntervalMicroSeconds& aInterval) const;
	inline TBool operator>=(const TTimeIntervalMicroSeconds& aInterval) const;
	inline TBool operator<=(const TTimeIntervalMicroSeconds& aInterval) const;
	inline TBool operator>(const TTimeIntervalMicroSeconds& aInterval) const;
	inline TBool operator<(const TTimeIntervalMicroSeconds& aInterval) const;
	inline const TInt64& Int64() const;
private:
	TInt64 iInterval;
	};

class TTimeIntervalBase
	{
public:
	inline TBool operator==(TTimeIntervalBase aInterval) const;
	inline TBool operator!=(TTimeIntervalBase aInterval) const;
	inline TBool operator>=(TTimeIntervalBase aInterval) const;
	inline TBool operator<=(TTimeIntervalBase aInterval) const;
	inline TBool operator>(TTimeIntervalBase aInterval) const;
	inline TBool operator<(TTimeIntervalBase aInterval) const;
	inline TInt Int() const;
protected:
	inline TTimeIntervalBase();
	inline TTimeIntervalBase(TInt aInterval);
protected:
	TInt iInterval;
	};

class TTimeIntervalMicroSeconds32 : public TTimeIntervalBase
	{
public:
	inline TTimeIntervalMicroSeconds32();
	inline TTimeIntervalMicroSeconds32(TInt aInterval);
	inline TTimeIntervalMicroSeconds32& operator=(TInt aInterval);
	};

class TTimeIntervalSeconds : public TTimeIntervalBase
	{
public:
	inline TTimeIntervalSeconds();
	inline TTimeIntervalSeconds(TInt aInterval);
	inline TTimeIntervalSeconds& operator=(TInt aInterval);
	};

class TTimeIntervalMinutes : public TTimeIntervalBase
	{
public:
	inline TTimeIntervalMinutes();
	inline TTimeIntervalMinutes(TInt aInterval);
	inline TTimeIntervalMinutes& operator=(TInt aInterval);
	};

class TTimeIntervalHours : public TTimeIntervalBase
	{
public:
	inline TTimeIntervalHours();
	inline TTimeIntervalHours(TInt aInterval);
	inline TTimeIntervalHours& operator=(TInt aInterval);
	};

class TTimeIntervalDays : public TTimeIntervalBase
	{
public:
	inline TTimeIntervalDays();
	inline TTimeIntervalDays(TInt aInterval);
	inline TTimeIntervalDays& operator=(TInt aInterval);
	};

class TTimeIntervalMonths : public TTimeIntervalBase
	{
public:
	inline TTimeIntervalMonths();
	inline TTimeIntervalMonths(TInt aInterval);
	inline TTimeIntervalMonths& operator=(TInt aInterval);
	};

class TTimeIntervalYears : public TTimeIntervalBase
	{
public:
	inline TTimeIntervalYears();
	inline TTimeIntervalYears(TInt aInterval);
	inline TTimeIntervalYears& operator=(TInt aInterval);
	};

enum {EParseTimePresent=0x1,EParseDatePresent=0x2};

class TTime
	{
public:
	inline TTime();
	inline TTime(const TInt64& aTime);
	IMPORT_C TTime(const TDesC& aString);
	IMPORT_C TTime(const TDateTime& aDateTime);
	inline TTime& operator=(const TInt64& aTime);
	IMPORT_C TTime& operator=(const TDateTime& aDateTime);
	IMPORT_C void HomeTime();
	IMPORT_C void UniversalTime();
	IMPORT_C TInt Set(const TDesC& aString);

	IMPORT_C TDateTime DateTime() const;
	IMPORT_C TTimeIntervalMicroSeconds MicroSecondsFrom(TTime aTime) const;
	IMPORT_C TInt SecondsFrom(TTime aTime,TTimeIntervalSeconds& aInterval) const;
	IMPORT_C TInt MinutesFrom(TTime aTime,TTimeIntervalMinutes& aInterval) const;
	IMPORT_C TInt HoursFrom(TTime aTime,TTimeIntervalHours& aInterval) const;
	IMPORT_C TTimeIntervalDays DaysFrom(TTime aTime) const;
	IMPORT_C TTimeIntervalMonths MonthsFrom(TTime aTime) const;
	IMPORT_C TTimeIntervalYears YearsFrom(TTime aTime) const;

	IMPORT_C TInt DaysInMonth() const;
	IMPORT_C TDay DayNoInWeek() const;
	IMPORT_C TInt DayNoInMonth() const;
	IMPORT_C TInt DayNoInYear() const;
	IMPORT_C TInt DayNoInYear(TTime aStartDate) const;
	IMPORT_C TInt WeekNoInYear() const;
	IMPORT_C TInt WeekNoInYear(TTime aStartDate) const;
	IMPORT_C TInt WeekNoInYear(TFirstWeekRule aRule) const;
	IMPORT_C TInt WeekNoInYear(TTime aStartDate,TFirstWeekRule aRule) const;
	IMPORT_C void FormatL(TDes& aDes,const TDesC& aFormat) const;
	IMPORT_C void RoundUpToNextMinute();
	IMPORT_C TInt Parse(const TDesC& aDes,TInt aCenturyOffset=0);

	IMPORT_C TTime operator+(TTimeIntervalYears aYear) const;
	IMPORT_C TTime operator+(TTimeIntervalMonths aMonth) const;
	IMPORT_C TTime operator+(TTimeIntervalDays aDay) const;
	IMPORT_C TTime operator+(TTimeIntervalHours aHour) const;
	IMPORT_C TTime operator+(TTimeIntervalMinutes aMinute) const;
	IMPORT_C TTime operator+(TTimeIntervalSeconds aSecond) const;  	
	IMPORT_C TTime operator+(TTimeIntervalMicroSeconds aMicroSecond) const;
	IMPORT_C TTime operator+(TTimeIntervalMicroSeconds32 aMicroSecond) const;
	IMPORT_C TTime operator-(TTimeIntervalYears aYear) const;
	IMPORT_C TTime operator-(TTimeIntervalMonths aMonth) const;
	IMPORT_C TTime operator-(TTimeIntervalDays aDay) const;
	IMPORT_C TTime operator-(TTimeIntervalHours aHour) const;
	IMPORT_C TTime operator-(TTimeIntervalMinutes aMinute) const;
	IMPORT_C TTime operator-(TTimeIntervalSeconds aSecond) const;  	
	IMPORT_C TTime operator-(TTimeIntervalMicroSeconds aMicroSecond) const;
	IMPORT_C TTime operator-(TTimeIntervalMicroSeconds32 aMicroSecond) const;
	IMPORT_C TTime& operator+=(TTimeIntervalYears aYear);
	IMPORT_C TTime& operator+=(TTimeIntervalMonths aMonth);
	IMPORT_C TTime& operator+=(TTimeIntervalDays aDay);
	IMPORT_C TTime& operator+=(TTimeIntervalHours aHour);
	IMPORT_C TTime& operator+=(TTimeIntervalMinutes aMinute);
	IMPORT_C TTime& operator+=(TTimeIntervalSeconds aSecond);	
	IMPORT_C TTime& operator+=(TTimeIntervalMicroSeconds aMicroSecond);
	IMPORT_C TTime& operator+=(TTimeIntervalMicroSeconds32 aMicroSecond);
	IMPORT_C TTime& operator-=(TTimeIntervalYears aYear);
	IMPORT_C TTime& operator-=(TTimeIntervalMonths aMonth);
	IMPORT_C TTime& operator-=(TTimeIntervalDays aDay);
	IMPORT_C TTime& operator-=(TTimeIntervalHours aHour);
	IMPORT_C TTime& operator-=(TTimeIntervalMinutes aMinute);
	IMPORT_C TTime& operator-=(TTimeIntervalSeconds aSecond);	
	IMPORT_C TTime& operator-=(TTimeIntervalMicroSeconds aMicroSecond);
	IMPORT_C TTime& operator-=(TTimeIntervalMicroSeconds32 aMicroSecond);
	inline TBool operator==(TTime aTime) const;
	inline TBool operator!=(TTime aTime) const;
	inline TBool operator>=(TTime aTime) const;
	inline TBool operator<=(TTime aTime) const;
	inline TBool operator>(TTime aTime) const;
	inline TBool operator<(TTime aTime) const;
	inline const TInt64& Int64() const;
private:
	static TTime Convert(const TDateTime& aDateTime);
private:
	TInt64 iTime;
	__DECLARE_TEST;
	};

class Time
	{
public:
	IMPORT_C static TTime NullTTime();
	IMPORT_C static TTime MaxTTime();
	IMPORT_C static TTime MinTTime();
	IMPORT_C static TInt DaysInMonth(TInt aYear, TMonth aMonth);
	IMPORT_C static TBool IsLeapYear(TInt aYear);
	IMPORT_C static TInt LeapYearsUpTo(TInt aYear);
	};

class TDayName : public TBuf<KMaxDayName>
	{
public:
	IMPORT_C TDayName();
	IMPORT_C TDayName(TDay aDay);
	IMPORT_C void Set(TDay aDay);
	};

class TDayNameAbb : public TBuf<KMaxDayNameAbb>
	{
public:
	IMPORT_C TDayNameAbb();
	IMPORT_C TDayNameAbb(TDay aDay);
	IMPORT_C void Set(TDay aDay);
	};

class TMonthName : public TBuf<KMaxMonthName>
	{
public:
	IMPORT_C TMonthName();
	IMPORT_C TMonthName(TMonth aMonth);
	IMPORT_C void Set(TMonth aMonth);
	};

class TMonthNameAbb : public TBuf<KMaxMonthNameAbb>
	{
public:
	IMPORT_C TMonthNameAbb();
	IMPORT_C TMonthNameAbb(TMonth aMonth);
	IMPORT_C void Set(TMonth aMonth);
	};

class TDateSuffix : public TBuf<KMaxSuffix>
	{
public:
	IMPORT_C TDateSuffix();
	IMPORT_C TDateSuffix(TInt aDateSuffix);
	IMPORT_C void Set(TInt aDateSuffix);
	};

class TAmPmName : public TBuf<KMaxAmPmName>
	{
public:
	IMPORT_C TAmPmName();
	IMPORT_C TAmPmName(TAmPm aSelector);
	IMPORT_C void Set(TAmPm aSelector);
	};

class TCurrencySymbol : public TBuf<KMaxCurrencySymbol>
	{
public:
	IMPORT_C TCurrencySymbol();
	IMPORT_C void Set();
	};

class TShortDateFormatSpec : public TBuf<KMaxShortDateFormatSpec> // to be passed into TTime::FormatL
	{
public:
	IMPORT_C TShortDateFormatSpec();
	IMPORT_C void Set();
	};

class TLongDateFormatSpec : public TBuf<KMaxLongDateFormatSpec> // to be passed into TTime::FormatL
	{
public:
	IMPORT_C TLongDateFormatSpec();
	IMPORT_C void Set();
	};

class TTimeFormatSpec : public TBuf<KMaxTimeFormatSpec> // to be passed into TTime::FormatL
	{
public:
	IMPORT_C TTimeFormatSpec();
	IMPORT_C void Set();
	};

enum TDaylightSavingZone
	{
	EDstHome=0x40000000,
	EDstNone=0,
	EDstEuropean=1,
	EDstNorthern=2,
	EDstSouthern=4
	};

const TInt KMaxDateSeparators=4;
const TInt KMaxTimeSeparators=4;
enum TLocalePos {ELocaleBefore,ELocaleAfter};


class TLocale
	{
public:
	enum TNegativeCurrencyFormat
		{
		ELeadingMinusSign,
		EInBrackets,// this one must be non-zero for binary compatibility with the old TBool TLocale::iCurrencyNegativeInBrackets which was exposed in the binary interface because it was accessed via *inline* functions
		ETrailingMinusSign,
		EInterveningMinusSign
		};

	enum 
		{
		EFlagNegativeLoseSpace = 0x00000001,
		EFlagNegativeCurrencySymbolOpposite=0x00000002
		};
public:
	IMPORT_C TLocale();
	IMPORT_C void Refresh();
	IMPORT_C void Set() const;
	IMPORT_C void FormatCurrency(TDes& aText, TInt aAmount);
	IMPORT_C void FormatCurrency(TDes& aText, TInt64 aAmount);
	IMPORT_C void FormatCurrency(TDes& aText, TDesOverflow& aOverflowHandler, TInt aAmount); 
	IMPORT_C void FormatCurrency(TDes& aText, TDesOverflow& aOverflowHandler, TInt64 aAmount); 
	
	inline TInt CountryCode() const;
	inline void SetCountryCode(TInt aCode);
	inline TTimeIntervalSeconds UniversalTimeOffset() const;
	inline void SetUniversalTimeOffset(const TTimeIntervalSeconds& anOffset);
	inline TDateFormat DateFormat() const;
	inline void SetDateFormat(TDateFormat aFormat);
	inline TTimeFormat TimeFormat() const;
	inline void SetTimeFormat(TTimeFormat aFormat);
	inline TLocalePos CurrencySymbolPosition() const;
	inline void SetCurrencySymbolPosition(TLocalePos aPos);
	inline TBool CurrencySpaceBetween() const;
	inline void SetCurrencySpaceBetween(TBool aSpace);
	inline TInt CurrencyDecimalPlaces() const;
	inline void SetCurrencyDecimalPlaces(TInt aPlaces);
	inline TBool CurrencyNegativeInBrackets() const;        // These two functions are deprecated
	inline void SetCurrencyNegativeInBrackets(TBool aBool); // They are here to maintain compatibility. Use the New functions -> NegativeCurrencyFormat setter/getter. 
 	inline TBool CurrencyTriadsAllowed() const;  
	inline void SetCurrencyTriadsAllowed(TBool aBool);
	inline TChar ThousandsSeparator() const;
	inline void SetThousandsSeparator(const TChar& aChar);
	inline TChar DecimalSeparator() const;
	inline void SetDecimalSeparator(const TChar& aChar);
	inline TChar DateSeparator(TInt aIndex) const;
	inline void SetDateSeparator(const TChar& aChar,TInt aIndex);
	inline TChar TimeSeparator(TInt aIndex) const;
	inline void SetTimeSeparator(const TChar& aChar,TInt aIndex);
	inline TBool AmPmSpaceBetween() const;
	inline void SetAmPmSpaceBetween(TBool aSpace);
	inline TLocalePos AmPmSymbolPosition() const;
	inline void SetAmPmSymbolPosition(TLocalePos aPos);
	inline TUint DaylightSaving() const;
	inline void SetDaylightSaving(TUint aDaylightSaving);
	inline TBool QueryHomeHasDaylightSavingOn() const;
	inline TDaylightSavingZone HomeDaylightSavingZone() const;
	inline void SetHomeDaylightSavingZone(TDaylightSavingZone aZone);
	inline TUint WorkDays() const;
	inline void SetWorkDays(TUint aMask);
	inline TDay StartOfWeek() const;
	inline void SetStartOfWeek(TDay aDay);
	inline TClockFormat ClockFormat() const;
	inline void SetClockFormat(TClockFormat aFormat);
	inline TUnitsFormat UnitsGeneral() const;
	inline void SetUnitsGeneral(TUnitsFormat aFormat);
	inline TUnitsFormat UnitsDistanceShort() const;
	inline void SetUnitsDistanceShort(TUnitsFormat aFormat);
	inline TUnitsFormat UnitsDistanceLong() const;
	inline void SetUnitsDistanceLong(TUnitsFormat aFormat);
	inline TNegativeCurrencyFormat NegativeCurrencyFormat() const;
	inline void SetNegativeCurrencyFormat(TNegativeCurrencyFormat aNegativeCurrencyFormat);
	inline TBool NegativeLoseSpace() const;
	inline void SetNegativeLoseSpace(TBool aBool);
	inline TBool NegativeCurrencySymbolOpposite() const;
	inline void SetNegativeCurrencySymbolOpposite(TBool aBool);
private:
	TInt iCountryCode;
	TTimeIntervalSeconds iUniversalTimeOffset;
	TDateFormat iDateFormat;
	TTimeFormat iTimeFormat;
	TLocalePos iCurrencySymbolPosition;
	TBool iCurrencySpaceBetween;
	TInt iCurrencyDecimalPlaces;
	TNegativeCurrencyFormat iNegativeCurrencyFormat; //	replaced TBool iCurrencyNegativeInBrackets
	TBool iCurrencyTriadsAllowed;
	TChar iThousandsSeparator;
	TChar iDecimalSeparator;
	TChar iDateSeparator[KMaxDateSeparators];
	TChar iTimeSeparator[KMaxTimeSeparators];
	TLocalePos iAmPmSymbolPosition;
	TBool iAmPmSpaceBetween;
	TUint iDaylightSaving;
	TDaylightSavingZone iHomeDaylightSavingZone;
	TUint iWorkDays;
	TDay iStartOfWeek;
	TClockFormat iClockFormat;
	TUnitsFormat iUnitsGeneral;
	TUnitsFormat iUnitsDistanceShort;
	TUnitsFormat iUnitsDistanceLong;
	TUint iExtraNegativeCurrencyFormatFlags;
	TInt iSpare[0x22];
	};

class TSize;
class TPoint
	{
public:
	enum TUninitialized { EUninitialized };
	TPoint(TUninitialized) {}
	inline TPoint();
	inline TPoint(TInt aX,TInt aY);
	IMPORT_C TInt operator==(const TPoint& aPoint) const;
	IMPORT_C TInt operator!=(const TPoint& aPoint) const;
	IMPORT_C TPoint& operator-=(const TPoint& aPoint);
	IMPORT_C TPoint& operator+=(const TPoint& aPoint);
	IMPORT_C TPoint& operator-=(const TSize& aSize);
	IMPORT_C TPoint& operator+=(const TSize& aSize);
	IMPORT_C TPoint operator-(const TPoint& aPoint) const;
	IMPORT_C TPoint operator+(const TPoint& aPoint) const;
	IMPORT_C TPoint operator-(const TSize& aSize) const;
	IMPORT_C TPoint operator+(const TSize& aSize) const;
	IMPORT_C TPoint operator-() const;
	IMPORT_C void SetXY(TInt aX,TInt aY);
	IMPORT_C TSize AsSize() const;
public:
	TInt iX;
	TInt iY;
	};

class TSize
	{
public:
	enum TUninitialized { EUninitialized };
	TSize(TUninitialized) {}
	inline TSize();
	inline TSize(TInt aWidth,TInt aHeight);
	IMPORT_C TInt operator==(const TSize& aSize) const;
	IMPORT_C TInt operator!=(const TSize& aSize) const;
	IMPORT_C TSize& operator-=(const TSize& aSize);
	IMPORT_C TSize& operator-=(const TPoint& aPoint);
	IMPORT_C TSize& operator+=(const TSize& aSize);
	IMPORT_C TSize& operator+=(const TPoint& aPoint);
	IMPORT_C TSize operator-(const TSize& aSize) const;
	IMPORT_C TSize operator-(const TPoint& aPoint) const;
	IMPORT_C TSize operator+(const TSize& aSize) const;
	IMPORT_C TSize operator+(const TPoint& aPoint) const;
	IMPORT_C TSize operator-() const;
	IMPORT_C void SetSize(TInt aWidth,TInt aHeight);
	IMPORT_C TPoint AsPoint() const;
public:
	TInt iWidth;
	TInt iHeight;
	};

class TRect
	{
public:
	enum TUninitialized { EUninitialized };
	TRect(TUninitialized) {}
	IMPORT_C TRect();
	IMPORT_C TRect(TInt aAx,TInt aAy,TInt aBx,TInt aBy);
	IMPORT_C TRect(const TPoint& aPointA,const TPoint& aPointB);
	IMPORT_C TRect(const TPoint& aPoint,const TSize& aSize);
	IMPORT_C TRect(const TSize& aSize);
	IMPORT_C TInt operator==(const TRect& aRect) const;
	IMPORT_C TInt operator!=(const TRect& aRect) const;
	IMPORT_C void SetRect(TInt aAx,TInt aAy,TInt aBx,TInt aBy);
	IMPORT_C void SetRect(const TPoint& aPointTL,const TPoint& aPointBR);
	IMPORT_C void SetRect(const TPoint& aPoint,const TSize& aSize);
	IMPORT_C void Move(TInt aDx,TInt aDy);
	IMPORT_C void Move(const TPoint& aOffset);
	IMPORT_C void Resize(TInt aDx,TInt aDy);
	IMPORT_C void Resize(const TSize& aSize);
	IMPORT_C void Shrink(TInt aDx,TInt aDy);
	IMPORT_C void Shrink(const TSize& aSize);
	IMPORT_C void Grow(TInt aDx,TInt aDy);
	IMPORT_C void Grow(const TSize& aSize);
	IMPORT_C void BoundingRect(const TRect& aRect);
	IMPORT_C TBool IsEmpty() const;
	IMPORT_C TBool Intersects(const TRect& aRect) const;
	IMPORT_C void Intersection(const TRect& aRect);
	IMPORT_C void Normalize();
	IMPORT_C TBool Contains(const TPoint& aPoint) const;
	IMPORT_C TSize Size() const;
	IMPORT_C TInt Width() const;
	IMPORT_C TInt Height() const;
	IMPORT_C TBool IsNormalized() const;
	IMPORT_C TPoint Center() const;
	IMPORT_C void SetSize(const TSize& aSize);
	IMPORT_C void SetWidth(TInt aWidth);
	IMPORT_C void SetHeight(TInt aHeight);
private:
	void Adjust(TInt aDx,TInt aDy);
public:
	TPoint iTl;
	TPoint iBr;
	};

class TRegion
	{
public:
	inline TInt Count() const;
	inline const TRect* RectangleList() const;
	inline TBool CheckError() const;
	IMPORT_C TBool IsEmpty() const;
	IMPORT_C TRect BoundingRect() const;
	IMPORT_C const TRect& operator[](TInt aIndex) const;
	IMPORT_C void Copy(const TRegion& aRegion);
	IMPORT_C void AddRect(const TRect& aRect);
	IMPORT_C void SubRect(const TRect& aRect,TRegion* aSubtractedRegion=NULL);
	IMPORT_C void Offset(TInt aXoffset,TInt aYoffset);
	IMPORT_C void Offset(const TPoint& aOffset);
	IMPORT_C void Union(const TRegion& aRegion);
	IMPORT_C void Intersection(const TRegion& aRegion,const TRegion& aRegion2);
	IMPORT_C void Intersect(const TRegion& aRegion);
	IMPORT_C void SubRegion(const TRegion& aRegion,TRegion* aSubtractedRegion=NULL);
	IMPORT_C void ClipRect(const TRect& aRect);
	IMPORT_C void Clear();
	IMPORT_C void Tidy();
	IMPORT_C TInt Sort();
	IMPORT_C TInt Sort(const TPoint& aOffset);
	IMPORT_C void ForceError();
	IMPORT_C TBool IsContainedBy(const TRect& aRect) const;
	IMPORT_C TBool Contains(const TPoint& aPoint) const;
protected:
	IMPORT_C TRect* RectangleListW();
	IMPORT_C TRegion(TInt aAllocedRects);
	inline TRegion();
	TBool SetListSize(TInt aCount);
	void AppendRect(const TRect& aRect);
	void DeleteRect(TRect* aRect);
	void AppendRegion(TRegion& aRegion);
protected:
	TInt iCount;
	TBool iError;
	TInt iAllocedRects;
protected:
	enum {ERRegionBuf=0x40000000};
	};

class RRegion : public TRegion
	{
private:
	enum {EDefaultGranularity=5};
protected:
	IMPORT_C RRegion(TInt aBuf,TInt aGran);
public:
	IMPORT_C RRegion();
	IMPORT_C RRegion(TInt aGran);
	IMPORT_C RRegion(const RRegion& aRegion);
	IMPORT_C RRegion(const TRect& aRect,TInt aGran=EDefaultGranularity);
	IMPORT_C RRegion(TInt aCount,TRect* aRectangleList,TInt aGran=EDefaultGranularity);
	IMPORT_C void Close();
	IMPORT_C void Destroy();
	inline TInt CheckSpare() const;
private:
	TInt iGranularity;
	TRect* iRectangleList;
	friend class TRegion;
	};

template <TInt S>
class RRegionBuf : public RRegion
	{
public:
	inline RRegionBuf();
	inline RRegionBuf(const RRegion& aRegion);
	inline RRegionBuf(const RRegionBuf<S>& aRegion);
	inline RRegionBuf(const TRect& aRect);
private:
	TInt8 iRectangleBuf[S*sizeof(TRect)];
	};

template <TInt S>
class TRegionFix : public TRegion
	{
public:
	inline TRegionFix();
	inline TRegionFix(const TRect& aRect);
	inline TRegionFix(const TRegionFix<S>& aRegion);
private:
	TInt8 iRectangleBuf[S*sizeof(TRect)];
	};

class TRequestStatus
	{
public:
	inline TRequestStatus();
	inline TRequestStatus(TInt aVal);
	inline TInt operator=(TInt aVal);
	inline TInt operator==(TInt aVal) const;
	inline TInt operator!=(TInt aVal) const;
	inline TInt operator>=(TInt aVal) const;
	inline TInt operator<=(TInt aVal) const;
	inline TInt operator>(TInt aVal) const;
	inline TInt operator<(TInt aVal) const;
	inline TInt Int() const;
private:
	TInt iStatus;
	};

class TFindHandleBase
	{
public:
	IMPORT_C TFindHandleBase();
	IMPORT_C TFindHandleBase(const TDesC& aMatch);
	IMPORT_C void Find(const TDesC& aMatch);
	inline TInt Handle() const;
protected:
	TInt iFindHandle;
	TFullName iMatch;
	};

class TFindSemaphore : public TFindHandleBase
	{
public:
	inline TFindSemaphore();
	inline TFindSemaphore(const TDesC& aMatch);
	IMPORT_C TInt Next(TFullName& aResult);
	};

class TFindMutex : public TFindHandleBase
	{
public:
	inline TFindMutex();
	inline TFindMutex(const TDesC& aMatch);
	IMPORT_C TInt Next(TFullName& aResult);
	};

class TFindChunk : public TFindHandleBase
	{
public:
	inline TFindChunk();
	inline TFindChunk(const TDesC& aMatch);
	IMPORT_C TInt Next(TFullName& aResult);
	};

class TFindThread : public TFindHandleBase
	{
public:
	inline TFindThread();
	inline TFindThread(const TDesC& aMatch);
	IMPORT_C TInt Next(TFullName& aResult);
	};

class TFindProcess : public TFindHandleBase
	{
public:
	inline TFindProcess();
	inline TFindProcess(const TDesC& aMatch);
	IMPORT_C TInt Next(TFullName& aResult);
	};

class TFindLogicalDevice : public TFindHandleBase
	{
public:
	inline TFindLogicalDevice();
	inline TFindLogicalDevice(const TDesC& aMatch);
	IMPORT_C TInt Next(TFullName& aResult);
	};

class TFindPhysicalDevice : public TFindHandleBase
	{
public:
	inline TFindPhysicalDevice();
	inline TFindPhysicalDevice(const TDesC& aMatch);
	IMPORT_C TInt Next(TFullName& aResult);
	};

class TFindLogicalChannel : public TFindHandleBase
	{
public:
	inline TFindLogicalChannel();
	inline TFindLogicalChannel(const TDesC& aMatch);
	IMPORT_C TInt Next(TFullName& aResult);
	};

class TFindServer : public TFindHandleBase
	{
public:
	inline TFindServer();
	inline TFindServer(const TDesC& aMatch);
	IMPORT_C TInt Next(TFullName& aResult);
	};

class TFindLibrary : public TFindHandleBase
	{
public:
	inline TFindLibrary();
	inline TFindLibrary(const TDesC& aMatch);
	IMPORT_C TInt Next(TFullName& aResult);
	};

class THandleInfo
	{
public:
	TInt iNumOpenInProcess;
	TInt iNumOpenInThread;
	TInt iNumProcesses;
	TInt iNumThreads;
	};

class RThread;
class RHandleBase
	{
public:
	enum
		{
		EReadAccess=0x1,
		EWriteAccess=0x2,
		EDirectReadAccess=0x4,
		EDirectWriteAccess=0x8,
		};
public:
	inline RHandleBase();
	IMPORT_C void Close();
	IMPORT_C TName Name() const;
	IMPORT_C TFullName FullName() const;
	inline void SetHandle(TInt aHandle);
	IMPORT_C void SetHandleNC(TInt aHandle);
	IMPORT_C TInt Duplicate(const RThread& aSrc,TOwnerType aType=EOwnerProcess);
	IMPORT_C void HandleInfo(THandleInfo* anInfo);
	IMPORT_C TUint Attributes() const;
	inline TInt Handle() const;
protected:
	inline RHandleBase(TInt aHandle);
	IMPORT_C TInt Open(const TFindHandleBase& aHandle,TOwnerType aType);
protected:
	TInt iHandle;
	};

class RDevice : public RHandleBase
	{
public:
	inline TInt Open(const TFindLogicalDevice& aFind,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Open(const TDesC& aName,TOwnerType aType=EOwnerProcess);
	IMPORT_C void GetCaps(TDes8& aDes) const;
	IMPORT_C TBool QueryVersionSupported(const TVersion& aVer) const;
	IMPORT_C TBool IsAvailable(TInt aUnit,const TDesC* aPhysicalDevice,const TDesC* anInfo) const;
	};

const TUint	KBusDevModeInvalid=0xFFFFFFFF;
const TUint	KBusDevSocketInfoMask=0x0000FFFF;
const TUint KBusDevPhase1Start=0x00010000;
const TUint KBusDevPhase2Start=0x00020000;

class MBusDev
	{
public:
    IMPORT_C MBusDev();
    TInt CheckOpenMode(const TDesC& aDeviceName,TInt aUnit);
	TInt DoAsyncStart();
	TInt DoAsyncLateOpen(TInt aHandle,TInt anOpenInfo);
	inline TBool MayRequireRestart() {return(iStartInfo);}
	inline TInt DevSocketNumber() {return(iStartInfo&KBusDevSocketInfoMask);}
	inline TInt& Status() {return(iStatus);}
	inline void SetStatus(TInt aVal) {iStatus=aVal;}
private:
    TUint iStartInfo;
	TInt iStatus;
	};

class RBusLogicalChannel : public RHandleBase, public MBusDev
	{
protected:
	IMPORT_C TInt DoCreate(const TDesC& aDevice,const TVersion& aVer,const TDesC* aChan,TInt aUnit,const TDesC* aDriver,const TDesC8* anInfo,TOwnerType aType=EOwnerProcess);
	IMPORT_C void DoCancel(TUint aReqMask);
	IMPORT_C void DoRequest(TInt aReqNo,TRequestStatus& aStatus);
	IMPORT_C void DoRequest(TInt aReqNo,TRequestStatus& aStatus,TAny* a1);
	IMPORT_C void DoRequest(TInt aReqNo,TRequestStatus& aStatus,TAny* a1,TAny* a2);
	IMPORT_C TInt DoControl(TInt aFunction);
	IMPORT_C TInt DoControl(TInt aFunction,TAny* a1);
	IMPORT_C TInt DoControl(TInt aFunction,TAny* a1,TAny* a2);
	IMPORT_C TInt DoSvControl(TInt aFunction);
	IMPORT_C TInt DoSvControl(TInt aFunction,TAny* a1);
	IMPORT_C TInt DoSvControl(TInt aFunction,TAny* a1,TAny* a2);
private:
	TInt CheckBusStatus();
	TInt DoCheckBusStatus(TInt aSocket);
	};

class RTimer : public RHandleBase
	{
public:
	IMPORT_C TInt CreateLocal();
	IMPORT_C void Cancel();
	IMPORT_C void After(TRequestStatus& aStatus,TTimeIntervalMicroSeconds32 anInterval);
	IMPORT_C void At(TRequestStatus& aStatus,const TTime& aTime);
	IMPORT_C void Lock(TRequestStatus& aStatus,TTimerLockSpec aLock);
	IMPORT_C void Inactivity(TRequestStatus& aStatus, TTimeIntervalSeconds aSeconds);
	};

class RLibrary : public RHandleBase
	{
public:
	IMPORT_C void Close();
	IMPORT_C TInt Load(const TDesC& aFileName,const TUidType &aType);
	IMPORT_C TInt Load(const TDesC& aFileName,const TDesC& aPath=KNullDesC);
	IMPORT_C TInt Load(const TDesC& aFileName,const TDesC& aPath,const TUidType &aType);
	IMPORT_C TInt LoadRomLibrary(const TDesC& aFileName,const TDesC& aPath);
	IMPORT_C TLibraryFunction Lookup(TInt anOrdinal) const;
	IMPORT_C TUidType Type() const;
	IMPORT_C TLibraryEntry EntryPoint() const;
	IMPORT_C TUint* DllRefTable() const;
	TInt LibraryCallList(TInt& aNumEps, TUint*& aCallList);
	IMPORT_C TFileName FileName() const;
	IMPORT_C TInt GetRamSizes(TInt& aCodeSize, TInt& aConstDataSize);
	};

class RSemaphore : public RHandleBase
	{
public:
	inline TInt Open(const TFindSemaphore& aFind,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt CreateLocal(TInt aCount,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt CreateGlobal(const TDesC& aName,TInt aCount,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt OpenGlobal(const TDesC& aName,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Count();
	IMPORT_C void Wait();
	IMPORT_C void Signal();
	IMPORT_C void Signal(TInt aCount);
	};

class RCriticalSection : private RSemaphore
	{
public:
	IMPORT_C RCriticalSection();
	IMPORT_C TInt CreateLocal(TOwnerType aType=EOwnerProcess);
	IMPORT_C void Close();
	IMPORT_C void Wait();
	IMPORT_C void Signal();
	inline TBool IsBlocked() const;
private:
	TInt iBlocked;
	};

class RMutex : public RHandleBase
	{
public:
	inline TInt Open(const TFindMutex& aFind,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt CreateLocal(TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt CreateGlobal(const TDesC& aName,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt OpenGlobal(const TDesC& aName,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Count();
	IMPORT_C void Wait();
	IMPORT_C void Signal();
	};

class RChunk : public RHandleBase
	{
public:
	inline TInt Open(const TFindChunk& aFind,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt CreateLocal(TInt aSize,TInt aMaxSize,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt CreateLocalCode(TInt aSize,TInt aMaxSize,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt CreateGlobal(const TDesC& aName,TInt aSize,TInt aMaxSize,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt CreateDoubleEndedLocal(TInt aInitialBottom, TInt aInitialTop,TInt aMaxSize,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt CreateDoubleEndedGlobal(const TDesC& aName,TInt aInitialBottom,TInt aInitialTop,TInt aMaxSize,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt OpenGlobal(const TDesC& aName,TBool isReadOnly,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Adjust(TInt aNewSize) const;
	IMPORT_C TInt AdjustDoubleEnded(TInt aBottom, TInt aTop) const;
	IMPORT_C TUint8* Base() const;
	IMPORT_C TInt Size() const;
	IMPORT_C TInt Bottom() const;
	IMPORT_C TInt Top() const;
	IMPORT_C TInt MaxSize() const;
	inline TBool IsReadable() const;
	inline TBool IsWritable() const;
private:
	friend class UserHeap;
	};

class RHeap;
class THeapWalk
	{
protected:
	enum TCellType
		{
		EGoodAllocatedCell,EGoodFreeCell,
		EBadAllocatedCellSize,EBadAllocatedCellAddress,
		EBadFreeCellAddress
		};
public:
	IMPORT_C THeapWalk(const RHeap &aHeap);
	IMPORT_C TInt Walk();
	virtual void Info(TCellType aType,TAny* aBase,TInt aLength)=0;
protected:
	inline TInt Value() const;
	inline void SetValue(TInt aValue);
private:
	RHeap* iHeap;
	TInt iValue;
	};

class UserHeap
	{
public:
	IMPORT_C static RHeap* FixedHeap(TAny* aBase, TInt aMaxLength);
	IMPORT_C static RHeap* ChunkHeap(const TDesC* aName, TInt aMinLength, TInt aMaxLength, TInt aGrowBy=KMinHeapGrowBy);
	IMPORT_C static RHeap* ChunkHeap(RChunk& aChunk, TInt aMinLength, TInt aGrowBy=KMinHeapGrowBy);
	};

IMPORT_C TInt CalcChunkHeapCompression(RHeap* aHeap,TInt aBaseOffset);

// Base class introduced to ensure vptr is at the same offset it always was.
// This makes it easier to run with euser.dll replaced in RAM.
class RHeapBase
	{
public:
	enum THeapType {EFixedAddress,EChunkSupervisor,EChunkStack,EChunkNormal};
	struct SCell {TInt len;SCell* next;};
protected:
	TInt iMinLength;
	TInt iMaxLength;
	TInt iOffset;
	TInt iGrowBy;
	TInt iAccessCount;
	THeapType iType;
	RChunk iChunk;
	RCriticalSection iLock;
	TUint8* iBase;
	TUint8* iTop;
	SCell iFree;
	friend class THeapWalk;
	friend class S;
	friend TInt CalcChunkHeapCompression(RHeap* aHeap,TInt aBaseOffset);
	friend class UserHeap;
protected:
	RHeapBase(TInt aMaxLength);
	RHeapBase(const RChunk& aChunk,TInt anOffset,TInt aMinLength,TInt aMaxLength,TInt aGrowBy);
	virtual TInt ChunkAdjust(TInt aSize)=0;
	virtual TInt CompressAll()=0;
	};

class RHeap : public RHeapBase
	{
public:
	typedef TUint32 TAllocSize;
	enum TAllocFail {ERandom,ETrueRandom,EDeterministic,ENone,EFailNext};
	enum TDbgHeapType {EUser,EKernel};
public:
	IMPORT_C TInt Open();
	IMPORT_C void Close();
	IMPORT_C TInt AllocLen(const TAny* aCell) const;
	IMPORT_C TInt AllocSize(TInt& aTotalAllocSize) const;
	IMPORT_C TAny* Alloc(TInt aSize);
	IMPORT_C TAny* AllocL(TInt aSize);
	IMPORT_C TAny* AllocLC(TInt aSize);
	IMPORT_C TAny* Adjust(TAny* aCell,TInt anOffset,TInt aDelta);
	IMPORT_C TAny* AdjustL(TAny* aCell,TInt anOffset,TInt aDelta);
	IMPORT_C TInt Compress();
	IMPORT_C void Free(TAny* aCell);
	IMPORT_C void FreeZ(TAny* &aCell);
	IMPORT_C void FreeAll();
	IMPORT_C TAny* ReAlloc(TAny* aCell,TInt aSize);
	IMPORT_C TAny* ReAllocL(TAny* aCell,TInt aSize);
	IMPORT_C THeapType Type() const;
	IMPORT_C TUint8* Base() const;
	IMPORT_C TInt Size() const;
	IMPORT_C TInt Available(TInt& aBiggestBlock) const;
	IMPORT_C void Check() const;
	IMPORT_C TInt Count() const;
	IMPORT_C TInt Count(TInt& aFreeCount) const;
	IMPORT_C void __DbgMarkStart();
	IMPORT_C TUint32 __DbgMarkEnd(TInt aCount);
	IMPORT_C void __DbgMarkCheck(TBool aCountAll,TInt aCount,const TDesC8& aFileName,TInt aLineNum);
	IMPORT_C void __DbgSetAllocFail(TAllocFail aType,TInt aValue);
protected:
	IMPORT_C RHeap(TInt aMaxLength);
	IMPORT_C RHeap(const RChunk& aChunk,TInt anOffset,TInt aMinLength,TInt aMaxLength,TInt aGrowBy);
	IMPORT_C TAny* operator new(TUint aSize,TAny* aBase);
	IMPORT_C void Initialise();
	IMPORT_C SCell* GetAddress(TAny* aCell);
	IMPORT_C virtual TInt ChunkAdjust(TInt aSize);
	IMPORT_C virtual TInt CompressAll();
protected:
	friend class THeapWalk;
	friend class S;
	friend TInt CalcChunkHeapCompression(RHeap* aHeap,TInt aBaseOffset);
	friend class UserHeap;
private:
	void ChunkHeapCreated() const;	// for use by UserHeap::ChunkHeap
	TInt TryToGrowHeap(TInt aSize, SCell* pC, SCell* pP);
public:
	struct SDebugCell {TInt len;TInt nestingLevel;TInt allocCount;};
#if defined(_DEBUG)
private:
	TInt AllocCount();
	TInt NestingLevel() const;
	void SetLevelNumAllocCells();
	void IncLevelNumAllocCells();
	TInt LevelNumAllocCells() const;
	void FoundHeaven(TAny* aBase,TInt aLength,TInt aNestingLevel,TInt aCount,TInt aNumStrandedCells);
	TBool CheckForSimulatedAllocFail();
#endif
public:
	TBool iTestCodeRunning;	
	TInt iTestNestingLevel;
	TInt iTestNumAllocCells;
	TUint iTestAddress;
	TInt iTestSize;
	TInt iTestAllocCount;
private:
	TInt iNestingLevel;
	TInt iAllocCount;
	TInt iLevelNumAllocCells;
	SDebugCell* iPtrDebugCell;
	TAllocFail iFailType;
	TInt iFailRate;
	TBool iFailed;
	TInt iFailAllocCount;
	TInt iRand;
	__DECLARE_TEST;
	};

class TThreadId
	{
public:
	inline TThreadId();
	inline TThreadId(TUint anId);
	inline operator TUint();
	inline TInt operator==(TThreadId aId);
	inline TInt operator!=(TThreadId aId);
private:
	TUint iId;
	};

class RProcess;
class RThread : public RHandleBase
	{
public:
	inline RThread();
	IMPORT_C TInt Create(const TDesC& aName,TThreadFunction aFunction,TInt aStackSize,TAny* aPtr,RLibrary* aLibrary,RHeap* aHeap, TInt aHeapMinSize,TInt aHeapMaxSize,TOwnerType aType);
	IMPORT_C TInt Create(const TDesC& aName,TThreadFunction aFunction,TInt aStackSize,TInt aHeapMinSize,TInt aHeapMaxSize,TAny *aPtr,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Create(const TDesC& aName,TThreadFunction aFunction,TInt aStackSize,RHeap* aHeap,TAny* aPtr,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt SetInitialParameter(TAny* aPtr);
	IMPORT_C TInt Open(const TDesC& aFullName,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Open(TThreadId aID,TOwnerType aType=EOwnerProcess);
	IMPORT_C TThreadId Id() const;
	IMPORT_C void Resume() const;
	IMPORT_C void Suspend() const;
	IMPORT_C TInt Rename(const TDesC& aName) const;
	IMPORT_C void Kill(TInt aReason);
	IMPORT_C void Terminate(TInt aReason);
	IMPORT_C void Panic(const TDesC& aCategory,TInt aReason);
	IMPORT_C TInt Process(RProcess& aProcess) const;
	IMPORT_C TThreadPriority Priority() const;
	IMPORT_C void SetPriority(TThreadPriority aPriority) const;
	IMPORT_C TProcessPriority ProcessPriority() const;
	IMPORT_C void SetProcessPriority(TProcessPriority aPriority) const;
	IMPORT_C TBool System() const;
	IMPORT_C void SetSystem(TBool aState) const;
	IMPORT_C TBool Protected() const;
	IMPORT_C void SetProtected(TBool aState) const;
	IMPORT_C TInt RequestCount() const;
	IMPORT_C TExitType ExitType() const;
	IMPORT_C TInt ExitReason() const;
	IMPORT_C TExitCategoryName ExitCategory() const;
	IMPORT_C void RequestComplete(TRequestStatus*& aStatus,TInt aReason) const;
	IMPORT_C TInt GetDesLength(const TAny* aPtr) const;
	IMPORT_C TInt GetDesMaxLength(const TAny* aPtr) const;
	IMPORT_C void ReadL(const TAny* aPtr,TDes8& aDes,TInt anOffset) const;
	IMPORT_C void ReadL(const TAny* aPtr,TDes16 &aDes,TInt anOffset) const;
	IMPORT_C void WriteL(const TAny* aPtr,const TDesC8& aDes,TInt anOffset) const;
	IMPORT_C void WriteL(const TAny* aPtr,const TDesC16& aDes,TInt anOffset) const;
	IMPORT_C void Logon(TRequestStatus& aStatus) const;
	IMPORT_C TInt LogonCancel(TRequestStatus& aStatus) const;
	IMPORT_C RHeap* Heap();	
	IMPORT_C void HandleCount(TInt& aProcessHandleCount, TInt& aThreadHandleCount) const;
	IMPORT_C TExceptionHandler* ExceptionHandler() const;
	IMPORT_C TInt SetExceptionHandler(TExceptionHandler* aHandler,TUint32 aMask);
	IMPORT_C void ModifyExceptionMask(TUint32 aClearMask, TUint32 aSetMask);
	IMPORT_C TInt RaiseException(TExcType aType);
	IMPORT_C TBool IsExceptionHandled(TExcType aType);
	IMPORT_C void Context(TDes8& aDes) const;
	IMPORT_C TInt GetRamSizes(TInt& aHeapSize,TInt& aStackSize);
	IMPORT_C TInt GetCpuTime(TTimeIntervalMicroSeconds& aCpuTime) const;
	inline TInt Open(const TFindThread& aFind,TOwnerType aType=EOwnerProcess);
	};

class TProcessId
	{
public:
	inline TProcessId();
	inline TProcessId(TUint anId);
	inline operator TUint();
	inline TInt operator==(TProcessId aId);
	inline TInt operator!=(TProcessId aId);
private:
	TUint iId;
	};

class RProcess : public RHandleBase
	{
public:
	inline RProcess();
	IMPORT_C TInt Create(const TDesC& aFileName,const TDesC& aCommand,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Create(const TDesC& aFileName,const TDesC& aCommand,const TUidType &aUidType, TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Open(const TDesC& aName,TOwnerType aType=EOwnerProcess);
	IMPORT_C TInt Open(TProcessId aId,TOwnerType aType=EOwnerProcess);
	IMPORT_C TUidType Type() const;
	IMPORT_C void SetType(const TUidType& aType);
	IMPORT_C TProcessId Id() const;
	IMPORT_C TInt Rename(const TDesC& aName);
	IMPORT_C void Kill(TInt aReason);
	IMPORT_C void Terminate(TInt aReason);
	IMPORT_C void Panic(const TDesC& aCategory,TInt aReason);
	IMPORT_C void Resume();
	IMPORT_C TFileName FileName() const;
	IMPORT_C TInt CommandLineLength() const;
	IMPORT_C void CommandLine(TDes &aCommand) const;
	IMPORT_C TExitType ExitType() const;
	IMPORT_C TInt ExitReason() const;
	IMPORT_C TExitCategoryName ExitCategory() const;
	IMPORT_C TProcessPriority Priority() const;
	IMPORT_C void SetPriority(TProcessPriority aPriority) const;
	IMPORT_C TBool System() const;
	IMPORT_C void SetSystem(TBool aState) const;
	IMPORT_C TBool Protected() const;
	IMPORT_C void SetProtected(TBool aState) const;
	IMPORT_C TBool LoadedFromRam() const;
	IMPORT_C TInt Owner(RProcess &anOwner) const;
	IMPORT_C void SetOwner(const RProcess& aProcess) const;
	IMPORT_C void Logon(TRequestStatus& aStatus) const;
	IMPORT_C TInt LogonCancel(TRequestStatus& aStatus) const;
	IMPORT_C TInt GetRamSizes(TInt& aCodeSize, TInt& aConstDataSize, TInt& anInitialisedDataSize, TInt& anUninitialisedDataSize);
	inline TInt Open(const TFindProcess& aFind,TOwnerType aType=EOwnerProcess);
protected:
	inline RProcess(TInt aHandle);
	};

class RMessage;
class RMessagePtr
	{
	friend TBool operator==(RMessagePtr aLeft,RMessagePtr aRight);
public:
	inline RMessagePtr();
	inline RMessagePtr(const RMessage& aMessage);
	inline TBool IsNull();
	IMPORT_C void Complete(TInt aReason) const;
private:
	TInt iHandle;
	};
inline TBool operator==(RMessagePtr aLeft,RMessagePtr aRight);
inline TBool operator!=(RMessagePtr aLeft,RMessagePtr aRight);

class RMessage
	{
	friend class CServer;
	friend class RMessagePtr;
public:
	enum TSessionMessages {EConnect=-1,EDisConnect=-2};
public:
	IMPORT_C RMessage();
	IMPORT_C void Complete(TInt aReason) const;
	IMPORT_C void ReadL(const TAny* aPtr,TDes8& aDes) const;
	IMPORT_C void ReadL(const TAny* aPtr,TDes8& aDes,TInt anOffset) const;
	IMPORT_C void ReadL(const TAny* aPtr,TDes16& aDes) const;
	IMPORT_C void ReadL(const TAny* aPtr,TDes16& aDes,TInt anOffset) const;
	IMPORT_C void WriteL(const TAny* aPtr,const TDesC8& aDes) const;
	IMPORT_C void WriteL(const TAny* aPtr,const TDesC8& aDes,TInt anOffset) const;
	IMPORT_C void WriteL(const TAny* aPtr,const TDesC16& aDes) const;
	IMPORT_C void WriteL(const TAny* aPtr,const TDesC16& aDes,TInt anOffset) const;
	IMPORT_C void Panic(const TDesC& aCategory,TInt aReason) const;
	IMPORT_C void Kill(TInt aReason) const;
	IMPORT_C void Terminate(TInt aReason) const;
	inline TInt Function() const;
	inline const RThread& Client() const;
	inline TInt Int0() const;
	inline TInt Int1() const;
	inline TInt Int2() const;
	inline TInt Int3() const;
	inline const TAny* Ptr0() const;
	inline const TAny* Ptr1() const;
	inline const TAny* Ptr2() const;
	inline const TAny* Ptr3() const;
	inline const RMessagePtr MessagePtr() const;
protected:
	TInt iFunction;
	TInt iArgs[KMaxMessageArguments];
	RThread iClient;
	const TAny* iSessionPtr;
	TInt iHandle;
	};

class RServer : public RHandleBase
	{
public:
	IMPORT_C TInt CreateGlobal(const TDesC& aName);
	IMPORT_C void Receive(TRequestStatus& aStatus);
	IMPORT_C void Receive();
	IMPORT_C void Cancel();
	inline const RMessage& Message() const;
private:
	RMessage iMessage;
	};

class RSessionBase : public RHandleBase
	{
	friend class RSubSessionBase;
public:
	enum TAttachMode {EExplicitAttach,EAutoAttach};
public:
	IMPORT_C TInt Share(TAttachMode aAttachMode=EExplicitAttach);
	IMPORT_C TInt Attach() const;
protected:
	inline TInt CreateSession(const TDesC& aServer,const TVersion& aVersion);
	IMPORT_C TInt CreateSession(const TDesC& aServer,const TVersion& aVersion,TInt aAsyncMessageSlots);
	IMPORT_C TInt Send(TInt aFunction,TAny* aPtr) const;
	IMPORT_C void SendReceive(TInt aFunction,TAny* aPtr,TRequestStatus& aStatus) const;
	IMPORT_C TInt SendReceive(TInt aFunction,TAny* aPtr) const;
private:
	TInt SendAsync(TInt aFunction,TAny* aPtr,TRequestStatus* aStatus) const;
	TInt SendSync(TInt aFunction,TAny *aPtr) const;
	};

class RSubSessionBase
	{
public:
	inline TInt SubSessionHandle();
protected:
	inline RSubSessionBase();
	inline RSessionBase& Session();
	IMPORT_C TInt CreateSubSession(RSessionBase& aSession,TInt aFunction,const TAny* aPtr);
	IMPORT_C void CloseSubSession(TInt aFunction);
	IMPORT_C TInt Send(TInt aFunction,const TAny* aPtr) const;
	IMPORT_C void SendReceive(TInt aFunction,const TAny* aPtr,TRequestStatus& aStatus) const;
	IMPORT_C TInt SendReceive(TInt aFunction,const TAny* aPtr) const;
private:
	RSessionBase iSession;
	TInt iSubSessionHandle;
	};

class RRefBase
	{
public:
	IMPORT_C void Free();
protected:
	inline RRefBase();
	inline RRefBase(const RRefBase& aRef);
	IMPORT_C void DoAlloc(const TAny* aPtr,TInt aSize);
	IMPORT_C void DoAllocL(const TAny* aPtr,TInt aSize);
	IMPORT_C void Copy(const RRefBase& aRef);
private:
	IMPORT_C void operator=(const RRefBase& aRef);
protected:
	TInt* iPtr;
	};

template <class T>
class RRef : public RRefBase
	{
public:
	inline RRef();
	inline RRef(const RRef<T>& anObject);
	inline void operator=(const RRef<T>& anObject);
	inline T* operator->();
	inline operator T*();
	inline void Alloc(const T& anObject);
	inline void Alloc(const T& anObject,TInt aSize);
	inline void AllocL(const T& anObject);
	inline void AllocL(const T& anObject,TInt aSize);
	};

class RChangeNotifier : public RHandleBase
	{
public:
	IMPORT_C TInt Create();
	IMPORT_C TInt Logon(TRequestStatus& aStatus) const;
	IMPORT_C TInt LogonCancel() const;
	};

enum TChanges
	{
	EChangesLocale=0x01,
	EChangesMidnightCrossover=0x02,
	EChangesThreadDeath=0x04,
	EChangesPowerStatus=0x08,
	EChangesSystemTime=0x10,
	EChangesFreeMemory=0x20,
	EChangesOutOfMemory=0x40,
	};

class RUndertaker : public RHandleBase
	{
public:
	IMPORT_C TInt Create();
	IMPORT_C TInt Logon(TRequestStatus& aStatus,TInt& aThreadHandle) const;
	IMPORT_C TInt LogonCancel() const;
	};

class TNotifyInfo
	{
public:
	const TDesC* iLine1;
	const TDesC* iLine2;
	const TDesC* iButton1;
	const TDesC* iButton2;
	TPtr* iButtonVal;
	};

/**
 * Client interface to allow engines or other low level components to communicate with the UI.
 */
class RNotifier : public RSessionBase
	{
public :
	IMPORT_C RNotifier();
	IMPORT_C TInt Connect();
	IMPORT_C TInt StartNotifier(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
	IMPORT_C TInt CancelNotifier(TUid aNotifierUid);
	IMPORT_C TInt UpdateNotifier(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
	IMPORT_C void StartNotifierAndGetResponse(TRequestStatus& aRs,TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
	IMPORT_C TInt UnloadNotifiers(TUid aNotifierUid);
	IMPORT_C TInt LoadNotifiers(TUid aNotifierUid);
	IMPORT_C void Notify(const TDesC& aLine1,const TDesC& aLine2,const TDesC& aBut1,const TDesC& aBut2,TInt& aButtonVal,TRequestStatus& aStatus);
	IMPORT_C TInt InfoPrint(const TDesC& aDes);
private:
	TPtr iButtonVal;
	TPckgBuf<TNotifyInfo> iInfo;
	};

const TInt KMediaPasswordNotifyUid(0x10004c00);
const TInt KMaxMediaPassword(16);
typedef TBuf8<KMaxMediaPassword> TMediaPassword;	// 128 bit

enum TMediaPswdNotifyExitMode {EMPEMUnlock, EMPEMCancel, EMPEMUnlockAndStore};

struct TMediaPswdNotifyBase
	{
	enum TCardType {ECTMmcPassword} iCT;
	TVersion iVersion;
	};

struct TMediaPswdSendNotifyInfoV1 : public TMediaPswdNotifyBase
	{
	// empty.
	};

struct TMediaPswdSendNotifyInfoV1Debug : public TMediaPswdSendNotifyInfoV1
	{
	TInt iSleepPeriod;							// us, -ve means maximum range
	TMediaPswdNotifyExitMode iEM;
	TText8 iPW[KMaxMediaPassword];
	};

struct TMediaPswdReplyNotifyInfoV1 : public TMediaPswdNotifyBase
	{
	TText8 iPW[KMaxMediaPassword];
	TMediaPswdNotifyExitMode iEM;
	};

class TTrapHandler
	{
public:
	IMPORT_C TTrapHandler();
	IMPORT_C virtual void Trap()=0;
	IMPORT_C virtual void UnTrap()=0;
	IMPORT_C virtual void Leave(TInt aValue)=0;
	};

const TInt KNoCallEntryPoint = 0x01;

class TDllRefTable
	{
public:
	TUint16 iFlags;
	TUint16 iNumberOfEntries;
	};

class TDllRefTableEntry
	{
public:
	TUint iEntryPoint;
	TDllRefTable* iDllRefTable;
	};

struct TCollationMethod; // forward declaration

class Mem
	{
public:
	IMPORT_C static TUint8* Copy(TAny* aTrg,const TAny* aSrc,TInt aLength);
	IMPORT_C static TUint8* Move(TAny* aTrg,const TAny* aSrc,TInt aLength);
	IMPORT_C static TInt Compare(const TUint8* aLeft,TInt aLeftL,const TUint8* aRight,TInt aRightL);
	IMPORT_C static TInt Compare(const TUint16* aLeft,TInt aLeftL,const TUint16* aRight,TInt aRightL);
	IMPORT_C static TInt CompareF(const TUint8* aLeft,TInt aLeftL,const TUint8* aRight,TInt aRightL);
	IMPORT_C static TInt CompareF(const TUint16* aLeft,TInt aLeftL,const TUint16* aRight,TInt aRightL);
	IMPORT_C static TInt CompareC(const TUint8* aLeft,TInt aLeftL,const TUint8* aRight,TInt aRightL);
	IMPORT_C static TInt CompareC(const TUint16* aLeft,TInt aLeftL,const TUint16* aRight,TInt aRightL);
	IMPORT_C static TInt CompareC(const TUint16* aLeft,TInt aLeftL,const TUint16* aRight,TInt aRightL,
								  TInt aMaxLevel,const TCollationMethod* aCollationMethod);
	IMPORT_C static TInt CollationMethods();
	IMPORT_C static TUint CollationMethodId(TInt aIndex);
	IMPORT_C static const TCollationMethod* CollationMethodByIndex(TInt aIndex);
	IMPORT_C static const TCollationMethod* CollationMethodById(TUint aId);
	IMPORT_C static void Fill(TAny* aTrg,TInt aLength,TChar aChar);
	IMPORT_C static void FillZ(TAny* aTrg,TInt aLength);
	IMPORT_C static void Swap(TAny* aPtr1,TAny* aPtr2,TInt aLength);
	IMPORT_C static void Crc(TUint16& aCrc,const TAny* aPtr,TInt aLength);
	};

class Password
	{
public:
	IMPORT_C static TBool IsEnabled();
	IMPORT_C static TInt SetEnabled(const TPassword& aPassword,TBool aIsEnabled);
	IMPORT_C static TBool IsValid(const TPassword& aPassword);
	IMPORT_C static TInt Set(const TPassword& anOldPassword,const TPassword& aNewPassword);
	};

class User : public UserHeap
	{
public:
	// Execution control
	IMPORT_C static void Exit(TInt aReason);
	IMPORT_C static void Panic(const TDesC& aCategory,TInt aReason);
	IMPORT_C static TInt StartThread(TThreadFunction anEntryPt,TAny* aPtr);
	IMPORT_C static void HandleException(TExceptionHandler* aHandler, TExcType anException);
	// Cleanup support
	IMPORT_C static void Leave(TInt aReason);
	IMPORT_C static void LeaveNoMemory();
	IMPORT_C static TInt LeaveIfError(TInt aReason);
	IMPORT_C static TAny* LeaveIfNull(TAny* aPtr);
	IMPORT_C static TTrapHandler* SetTrapHandler(TTrapHandler* aHandler);
	IMPORT_C static TTrapHandler* TrapHandler();
	// Infoprint
	IMPORT_C static TInt InfoPrint(const TDesC& aDes);
	// Asynchronous service support
	IMPORT_C static void RequestComplete(TRequestStatus*& aStatus,TInt aReason);
	IMPORT_C static void WaitForAnyRequest();
	IMPORT_C static void WaitForRequest(TRequestStatus& aStatus);
	IMPORT_C static void WaitForRequest(TRequestStatus& aStatus1,TRequestStatus& aStatus2);
	// User heap management
	IMPORT_C static TAny* Adjust(TAny* aCell,TInt anOffset,TInt aDelta);
	IMPORT_C static TAny* AdjustL(TAny* aCell,TInt anOffset,TInt aDelta);
	IMPORT_C static TInt AllocLen(const TAny* aCell);
	IMPORT_C static TAny* Alloc(TInt aSize);
	IMPORT_C static TAny* AllocL(TInt aSize);
	IMPORT_C static TAny* AllocLC(TInt aSize);
	IMPORT_C static TInt AllocSize(TInt& aTotalAllocSize);
	IMPORT_C static TInt Available(TInt& aBiggestBlock);
	IMPORT_C static TInt CountAllocCells();
	IMPORT_C static TInt CountAllocCells(TInt& aFreeCount);
	IMPORT_C static void Free(TAny* aCell);
	IMPORT_C static void FreeZ(TAny*& aCell);
	IMPORT_C static RHeap& Heap();
	IMPORT_C static TAny* ReAlloc(TAny* aCell,TInt aSize);
	IMPORT_C static TAny* ReAllocL(TAny* aCell,TInt aSize);
	IMPORT_C static RHeap* SwitchHeap(RHeap* aHeap);
	IMPORT_C static TInt CompressAllHeaps();
	// Synchronous timer services
	IMPORT_C static void After(TTimeIntervalMicroSeconds32 anInterval);
	IMPORT_C static TInt At(const TTime& aTime);
	// Set time
	IMPORT_C static TInt SetHomeTime(const TTime& aTime);
	// Set locale information
	IMPORT_C static void SetCurrencySymbol(const TDesC& aSymbol);
	// Timers
	IMPORT_C static TUint TickCount();
	IMPORT_C static TTimerLockSpec LockPeriod();
	IMPORT_C static TInt LockedInc(TInt& aValue);
	IMPORT_C static TInt LockedDec(TInt& aValue);
	IMPORT_C static TTimeIntervalSeconds InactivityTime();
	IMPORT_C static void ResetInactivityTime();
	IMPORT_C static TUint32 FastCounter();
	// Beep
	IMPORT_C static TInt Beep(TInt aFrequency,TTimeIntervalMicroSeconds32 aDuration);
	// Information
	IMPORT_C static TInt IsRomAddress(TBool& aBool,TAny* aPtr);
	// Algorithms
	IMPORT_C static TInt BinarySearch(TInt aCount,const TKey& aKey,TInt& aPos);
	IMPORT_C static TInt QuickSort(TInt aCount,const TKey& aKey,const TSwap& aSwap);
	// Language-dependent character functions
	IMPORT_C static TLanguage Language();
	IMPORT_C static TUint Collate(TUint aChar);
	IMPORT_C static TUint Fold(TUint aChar);
	IMPORT_C static TUint LowerCase(TUint aChar);
	IMPORT_C static TUint UpperCase(TUint aChar);
	IMPORT_C static TUint Fold(TUint aChar,TInt aFlags);
	IMPORT_C static TUint TitleCase(TUint aChar);
	// C-style string length
	IMPORT_C static TInt StringLength(const TUint8* aString);
	IMPORT_C static TInt StringLength(const TUint16* aString);
	// Device management
	IMPORT_C static TInt FreeLogicalDevice(const TDesC& aDeviceName);
	IMPORT_C static TInt FreePhysicalDevice(const TDesC& aDriverName);
	IMPORT_C static TInt LoadLogicalDevice(const TDesC& aFileName);
	IMPORT_C static TInt LoadPhysicalDevice(const TDesC& aFileName);
	// Version information
	IMPORT_C static TBool QueryVersionSupported(const TVersion& aCurrent,const TVersion& aRequested);
	IMPORT_C static TVersion Version();
	// Machine configuration
	IMPORT_C static TInt SetMachineConfiguration(const TDesC8& aConfig);
	IMPORT_C static TInt MachineConfiguration(TDes8& aConfig,TInt& aSize);
	// Debugging support
	IMPORT_C static void SetDebugMask(TUint32 aVal);
	IMPORT_C static void SetJustInTime(const TBool aBoolean);
	IMPORT_C static void Check();
	IMPORT_C static void Invariant();
	IMPORT_C static TBool JustInTime();
	IMPORT_C static void __DbgMarkStart(RHeap::TDbgHeapType aHeapType);
	IMPORT_C static void __DbgMarkCheck(RHeap::TDbgHeapType aHeapType,TBool aCountAll,TInt aCount,const TDesC8& aFileName,TInt aLineNum);
	IMPORT_C static TUint32 __DbgMarkEnd(RHeap::TDbgHeapType aHeapType,TInt aCount);
	IMPORT_C static void __DbgSetAllocFail(RHeap::TDbgHeapType aHeapType,RHeap::TAllocFail aType,TInt aRate);
	// Name Validation
	IMPORT_C static TInt ValidateName(const TDesC& aName);
	// Instruction Memory Barrier
	IMPORT_C static void IMB_Range(TAny* aStart, TAny* aEnd);
	};

class ExecHandler;
class TTrap
	{
public:
	inline TTrap();
	IMPORT_C TInt Trap(TInt& aResult);
	IMPORT_C static void UnTrap();
protected:
	enum {EMaxState=0x10};
protected:
	TInt iState[EMaxState];
	TTrap* iNext;
	TInt* iResult;
	TTrapHandler* iHandler;
	friend void User::Leave(TInt aNumber);
	friend class ExecHandler;
	};

#define TRAP(_r,_s) {TTrap __t;if (__t.Trap(_r)==0){_s;TTrap::UnTrap();}}
#define TRAPD(_r,_s) TInt _r;{TTrap __t;if (__t.Trap(_r)==0){_s;TTrap::UnTrap();}}

class Dll
	{
public:
	static TInt GlobalAlloc(TInt aSize);
	static TBool GlobalAllocated();
	static TInt GlobalRead(TInt aPos, TInt aLength, TDes8& aDes);
	static TInt GlobalWrite(TInt aPos,const TDesC8& aDes);
	static TInt SetTls(TAny* aPtr);
	static TAny* Tls();
	static void FreeTls();
	static TInt InitialiseData();
	static void FreeData();
	static void FileName(TFileName &aFileName);
	};

class CBase;

template <class T>
class TArray
	{
public:
	inline TArray(TInt (*aCount)(const CBase* aPtr),const TAny*(*anAt)(const CBase* aPtr,TInt anIndex),const CBase* aPtr);
	inline TInt Count() const;
	inline const T& operator[](TInt anIndex) const;
private:
	const CBase* iPtr;
	TInt (*iCount)(const CBase* aPtr);
	const TAny*(*iAt)(const CBase* aPtr,TInt anIndex);
	};

template <class T,TInt S> 
class TFixedArray
// Range checking wrapper+ class for C++ arrays
// Can be embedded in C-objects, or used on the stack: use Reset() to zero it
	{
	typedef TFixedArray<T,S> ThisClass;
public:
	inline TFixedArray();
	inline TFixedArray(const T* aList, TInt aLength);
	//
	inline void Copy(const T* aList, TInt aLength);
	inline void Reset();		// zero fill
	inline void DeleteAll();
	//
	inline TInt Count() const;
	inline TInt Length() const;
	// Accessors - debug range checking
	inline T& operator[](TInt aIndex);
	inline const T& operator[] (TInt aIndex) const;
	// Accessors - always range checking
	inline T& At(TInt aIndex);
	inline const T& At(TInt aIndex) const;
	// Provides pointers to the beginning and end of the array
	inline T* Begin();
	inline T* End();
	inline const T* Begin() const;
	inline const T* End() const;
	//
	inline TArray<T> Array() const;
protected:
	inline static TBool InRange(TInt aIndex);
	inline static TInt CountFunctionR(const CBase* aThis);
	inline static const TAny* AtFunctionR(const CBase* aThis,TInt aIndex);
protected:
	T iRep[S];
	};

#define DECLARE_ROM_ARRAY( AName, AData, AType ) \
   	const TFixedArray<AType,(sizeof(AData)/sizeof((AData)[0]))>& \
            AName = *(reinterpret_cast<const TFixedArray<AType, \
                           (sizeof(AData)/sizeof((AData)[0]))>* > (AData))

typedef TBool (*TGeneralIdentityRelation)(const TAny*, const TAny*);
typedef TInt (*TGeneralLinearOrder)(const TAny*, const TAny*);

template <class T>
class TIdentityRelation
	{
public:
	inline TIdentityRelation( TBool(*anIdentity)(const T&, const T&) );
	inline operator TGeneralIdentityRelation() const;
private:
	TGeneralIdentityRelation iIdentity;
	};

template <class T>
class TLinearOrder
	{
public:
	inline TLinearOrder( TInt(*anOrder)(const T&, const T&) );
	inline operator TGeneralLinearOrder() const;
private:
	TGeneralLinearOrder iOrder;
	};

class RPointerArrayBase
	{
protected:
	IMPORT_C RPointerArrayBase();
	IMPORT_C RPointerArrayBase(TInt aGranularity);
 	IMPORT_C RPointerArrayBase(TAny** aEntries, TInt aCount);
	IMPORT_C void Close();
	IMPORT_C TInt Count() const;
	inline void ZeroCount() {iCount=0;}
	inline TAny** Entries() {return iEntries;}
	IMPORT_C TAny*& At(TInt anIndex) const;
	IMPORT_C TInt Append(const TAny* anEntry);
	IMPORT_C TInt Insert(const TAny* anEntry, TInt aPos);
	IMPORT_C void Remove(TInt anIndex);
	IMPORT_C void Compress();
	IMPORT_C void GranularCompress();
	IMPORT_C void Reset();
	IMPORT_C TInt Find(const TAny* anEntry) const;
	IMPORT_C TInt Find(const TAny* anEntry, TGeneralIdentityRelation anIdentity) const;
	IMPORT_C TInt FindIsqSigned(TInt anEntry) const;
	IMPORT_C TInt FindIsqUnsigned(TUint anEntry) const;
	IMPORT_C TInt FindIsq(const TAny* anEntry, TGeneralLinearOrder anOrder) const;
	IMPORT_C TInt InsertIsqSigned(TInt anEntry, TBool aAllowRepeats);
	IMPORT_C TInt InsertIsqUnsigned(TUint anEntry, TBool aAllowRepeats);
	IMPORT_C TInt InsertIsq(const TAny* anEntry, TGeneralLinearOrder anOrder, TBool aAllowRepeats);
	IMPORT_C void HeapSortSigned();
	IMPORT_C void HeapSortUnsigned();
	IMPORT_C void HeapSort(TGeneralLinearOrder anOrder);
	IMPORT_C TInt BinarySearchSigned(TInt anEntry, TInt& anIndex) const;
	IMPORT_C TInt BinarySearchUnsigned(TUint anEntry, TInt& anIndex) const;
	IMPORT_C TInt BinarySearch(const TAny* anEntry, TInt& anIndex, TGeneralLinearOrder anOrder) const;
	IMPORT_C static TInt GetCount(const CBase* aPtr);
	IMPORT_C static const TAny* GetElementPtr(const CBase* aPtr, TInt aIndex);
private:
	TInt Grow();
private:
	TInt iCount;
	TAny** iEntries;
	TInt iAllocated;
	TInt iGranularity;
	};

template <class T>
class RPointerArray : private RPointerArrayBase
	{
public:
	inline RPointerArray();
	inline RPointerArray(TInt aGranularity);
 	inline RPointerArray(T** aEntries, TInt aCount);
	inline void Close();
	inline TInt Count() const;
	inline const T*& operator[](TInt anIndex) const;
	inline T*& operator[](TInt anIndex);
	inline TInt Append(const T* anEntry);
	inline TInt Insert(const T* anEntry, TInt aPos);
	inline void Remove(TInt anIndex);
	inline void Compress();
	inline void GranularCompress();
	inline void Reset();
	void ResetAndDestroy();
	inline TInt Find(const T* anEntry) const;
	inline TInt Find(const T* anEntry, TIdentityRelation<T> anIdentity) const;
	inline TInt FindInAddressOrder(const T* anEntry) const;
	inline TInt FindInOrder(const T* anEntry, TLinearOrder<T> anOrder) const;
	inline TInt FindInAddressOrder(const T* anEntry, TInt& anIndex) const;
	inline TInt FindInOrder(const T* anEntry, TInt& anIndex, TLinearOrder<T> anOrder) const;
	inline TInt InsertInAddressOrder(const T* anEntry);
	inline TInt InsertInOrder(const T* anEntry, TLinearOrder<T> anOrder);
	inline TInt InsertInAddressOrderAllowRepeats(const T* anEntry);
	inline TInt InsertInOrderAllowRepeats(const T* anEntry, TLinearOrder<T> anOrder);
	inline void SortIntoAddressOrder();
	inline void Sort(TLinearOrder<T> anOrder);
	inline TArray<T> Array() const;
	};

class RArrayBase
	{
protected:
	IMPORT_C RArrayBase(TInt anEntrySize);
 	IMPORT_C RArrayBase(TInt aEntrySize,TAny* aEntries, TInt aCount);
	IMPORT_C RArrayBase(TInt anEntrySize, TInt aGranularity);
	IMPORT_C RArrayBase(TInt anEntrySize, TInt aGranularity, TInt aKeyOffset);
	IMPORT_C void Close();
	IMPORT_C TInt Count() const;
	IMPORT_C TAny* At(TInt anIndex) const;
	IMPORT_C TInt Append(const TAny* anEntry);
	IMPORT_C TInt Insert(const TAny* anEntry, TInt aPos);
	IMPORT_C void Remove(TInt anIndex);
	IMPORT_C void Compress();
	IMPORT_C void GranularCompress();
	IMPORT_C void Reset();
	IMPORT_C TInt Find(const TAny* anEntry) const;
	IMPORT_C TInt Find(const TAny* anEntry, TGeneralIdentityRelation anIdentity) const;
	IMPORT_C TInt FindIsqSigned(const TAny* anEntry) const;
	IMPORT_C TInt FindIsqUnsigned(const TAny* anEntry) const;
	IMPORT_C TInt FindIsq(const TAny* anEntry, TGeneralLinearOrder anOrder) const;
	IMPORT_C TInt InsertIsqSigned(const TAny* anEntry, TBool aAllowRepeats);
	IMPORT_C TInt InsertIsqUnsigned(const TAny* anEntry, TBool aAllowRepeats);
	IMPORT_C TInt InsertIsq(const TAny* anEntry, TGeneralLinearOrder anOrder, TBool aAllowRepeats);
	IMPORT_C void HeapSortSigned();
	IMPORT_C void HeapSortUnsigned();
	IMPORT_C void HeapSort(TGeneralLinearOrder anOrder);
	IMPORT_C TInt BinarySearchSigned(const TAny* anEntry, TInt& anIndex) const;
	IMPORT_C TInt BinarySearchUnsigned(const TAny* anEntry, TInt& anIndex) const;
	IMPORT_C TInt BinarySearch(const TAny* anEntry, TInt& anIndex, TGeneralLinearOrder anOrder) const;
	IMPORT_C static TInt GetCount(const CBase* aPtr);
	IMPORT_C static const TAny* GetElementPtr(const CBase* aPtr, TInt aIndex);
private:
	TInt Grow();
private:
	TInt iCount;
	TAny* iEntries;
	TInt iEntrySize;
	TInt iKeyOffset;
	TInt iAllocated;
	TInt iGranularity;
	};

template <class T>
class RArray : private RArrayBase
	{
public:
	inline RArray();
	inline RArray(TInt aGranularity);
	inline RArray(TInt aGranularity, TInt aKeyOffset);
 	inline RArray(TInt aEntrySize,T* aEntries, TInt aCount);
	inline void Close();
	inline TInt Count() const;
	inline const T& operator[](TInt anIndex) const;
	inline T& operator[](TInt anIndex);
	inline TInt Append(const T& anEntry);
	inline TInt Insert(const T& anEntry, TInt aPos);
	inline void Remove(TInt anIndex);
	inline void Compress();
	inline void GranularCompress();
	inline void Reset();
	inline TInt Find(const T& anEntry) const;
	inline TInt Find(const T& anEntry, TIdentityRelation<T> anIdentity) const;
	inline TInt FindInSignedKeyOrder(const T& anEntry) const;
	inline TInt FindInUnsignedKeyOrder(const T& anEntry) const;
	inline TInt FindInOrder(const T& anEntry, TLinearOrder<T> anOrder) const;
	inline TInt FindInSignedKeyOrder(const T& anEntry, TInt& anIndex) const;
	inline TInt FindInUnsignedKeyOrder(const T& anEntry, TInt& anIndex) const;
	inline TInt FindInOrder(const T& anEntry, TInt& anIndex, TLinearOrder<T> anOrder) const;
	inline TInt InsertInSignedKeyOrder(const T& anEntry);
	inline TInt InsertInUnsignedKeyOrder(const T& anEntry);
	inline TInt InsertInOrder(const T& anEntry, TLinearOrder<T> anOrder);
	inline TInt InsertInSignedKeyOrderAllowRepeats(const T& anEntry);
	inline TInt InsertInUnsignedKeyOrderAllowRepeats(const T& anEntry);
	inline TInt InsertInOrderAllowRepeats(const T& anEntry, TLinearOrder<T> anOrder);
	inline void SortSigned();
	inline void SortUnsigned();
	inline void Sort(TLinearOrder<T> anOrder);
	inline TArray<T> Array() const;
	};

TEMPLATE_SPECIALIZATION class RArray<TInt> : private RPointerArrayBase
	{
public:
	inline RArray();
	inline RArray(TInt aGranularity);
	inline void Close();
	inline TInt Count() const;
	inline const TInt& operator[](TInt anIndex) const;
	inline TInt& operator[](TInt anIndex);
	inline TInt Append(TInt anEntry);
	inline TInt Insert(TInt anEntry, TInt aPos);
	inline void Remove(TInt anIndex);
	inline void Compress();
	inline void GranularCompress();
	inline void Reset();
	inline TInt Find(TInt anEntry) const;
	inline TInt FindInOrder(TInt anEntry) const;
	inline TInt FindInOrder(TInt anEntry, TInt& anIndex) const;
	inline TInt InsertInOrder(TInt anEntry);
	inline TInt InsertInOrderAllowRepeats(TInt anEntry);
	inline void Sort();
	inline TArray<TInt> Array() const;
	};

TEMPLATE_SPECIALIZATION class RArray<TUint> : private RPointerArrayBase
	{
public:
	inline RArray();
	inline RArray(TInt aGranularity);
	inline void Close();
	inline TInt Count() const;
	inline const TUint& operator[](TInt anIndex) const;
	inline TUint& operator[](TInt anIndex);
	inline TInt Append(TUint anEntry);
	inline TInt Insert(TUint anEntry, TInt aPos);
	inline void Remove(TInt anIndex);
	inline void Compress();
	inline void Reset();
	inline TInt Find(TUint anEntry) const;
	inline TInt FindInOrder(TUint anEntry) const;
	inline TInt FindInOrder(TUint anEntry, TInt& anIndex) const;
	inline TInt InsertInOrder(TUint anEntry);
	inline TInt InsertInOrderAllowRepeats(TUint anEntry);
	inline void Sort();
	inline TArray<TUint> Array() const;
	};

inline TAny* operator new(TUint aSize, TAny* aBase);
inline TAny* operator new(TUint aSize, TLeave);

GLREF_C TAny* operator new(TUint aSize);
GLREF_C TAny* operator new(TUint aSize,TUint anExtraSize);
GLREF_C void operator delete(TAny* aPtr);

#ifdef __GCC32__
inline TAny* operator new[](TUint aSize, TLeave);
#endif

#if !defined(__BOOL_NO_TRUE_TRAP__)
TBool operator==(TTrue,volatile const TBool);
TBool operator==(volatile const TBool,TTrue);
TBool operator!=(TTrue,volatile const TBool);
TBool operator!=(volatile const TBool,TTrue);
#endif


#if (defined (CALYPSO_PROFILE_DEBUG_SLOW_WINS_OR_HARDWARE) || (defined CALYPSO_PROFILE_DEBUG_FAST_WINS))

enum THeapActivityType
	{
	EHeapActivityAlloc=1,
	EHeapActivityFree=2,
	EHeapActivityReallocGrowInSitu=3,
	EHeapActivityReallocFreeInSitu=4,
	EHeapActivityReallocGrowAndMove=5,
	EHeapActivityMarker=6
	};
#endif // defined () || defined ()
#ifdef CALYPSO_PROFILE_DEBUG_FAST_WINS

class TSingleHeapActivity
	{
public:
	THeapActivityType iActivityType;
	TInt iActivityCount;
	TInt iAddress;
	TInt iSize;
	TInt iAllocCount;
	TInt iNestingLevel;
	TInt iEpocThreadId;
	TInt64 iEpocTimeInMicroseconds;
	TInt iActivitySpecificData;
	};

class THeapActivityData
	{
public:
	TInt iTotalActivities;
	TSingleHeapActivity* iHeapActivity;
	};

IMPORT_C  THeapActivityData HeapInfo();  //Get the current array of heap info
IMPORT_C  void MarkHeapInfo(TInt aMark);  //Set a mark in the heap array
IMPORT_C  void ResetHeapInfo();  //Empty & Reset the heap array

#endif //CALYPSO_PROFILE_DEBUG_FAST_WINS


// Inline methods
#include <e32std.inl>
#endif

