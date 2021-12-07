// EIKDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDEF_H__)
#define __EIKDEF_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

enum TPopupTargetPosType
	{
	EPopupTargetTopLeft,
	EPopupTargetTopRight,
	EPopupTargetBottomLeft,
	EPopupTargetBottomRight
	};

#define iEikonEnv (STATIC_CAST(CEikonEnv*,iCoeEnv))

#define KEikEditableControlBorder TGulBorder::EShallowSunken
#if defined(_DEBUG)
#define __UHEAP_CHECK_INTEGRITY User::Heap().Check()
#else
#define __UHEAP_CHECK_INTEGRITY
#endif

#define PROFILE_POINT_EIKON_FIRST		32
#define PROFILE_POINT_EIKON_LAST		39

#define PROFILE_POINT_EIKON_SIMPLE		32
#define PROFILE_POINT_EIKON_DIALOG_LOAD	33
#define PROFILE_POINT_EIKON_APP_LAUNCH	34
#define PROFILE_POINT_EIKON_CLOCK		35
#define PROFILE_POINT_EIKON_CALENDER	35
#define PROFILE_POINT_EIKON_LIBS_LOAD	36
#define PROFILE_POINT_EIKON_ADD_RES		37

#define KEikEikonBitmapStore		KNullDesC
_LIT(KEikDefaultAppBitmapStore,"*");

const TInt KUidValueEikColorSchemeChangeEvent	=0x10006956;

const TInt KEikCustomColorsArrayValue			=0x100057C2;

const TInt KEikMessageFadeAllWindows			=0x100056C2;
const TInt KEikMessageUnfadeWindows				=0x100056C3;
const TInt KEikMessageColorSchemeChange			=0x100056C4;
const TInt KEikMessageWindowsFadeChange			=0x10006890;
#define KEikColorResourceChange KEikMessageColorSchemeChange // for source compatibility
const TInt KEikMessageZoomChange				=0x100057C3;
const TInt KEikMessageVirtualCursorStateChange	=0x10005D0A;
const TInt KEikMessageCapsLock					=0x100048F9;
const TInt KEikMessagePrepareForSave			=0x100069FD;
const TInt KEikMessageEmbedLevelChange			=0x1000A4AA;

// added by LMB [20/6/00] for CEikCaptionedControl 
const TInt KEikMessageCaptionedControlEditableStateChange			=0x10008E99;
const TInt KEikMessageCaptionedControlNotEditableStateChange		=0x10008E9A;
const TInt KEikMessageCaptionedControlEditableStateChangeWideWithGraphic			=0x101F5FBA;
const TInt KEikMessageCaptionedControlEditableStateChangeWideWithoutGraphic			=0x101F5FBB;
const TInt KEikMessageCaptionedControlNotEditableStateChangeWideWithGraphic			=0x101F5FBC;
const TInt KEikMessageCaptionedControlNotEditableStateChangeWideWithoutGraphic		=0x101F5FBD;

const TInt KEikPartialForegroundFade			=0x101f538d;	// deprecated
const TInt KEikPartialForegroundNoFade			=0x101f538e;	// deprecated
const TInt KEikRequestPartialForegroundEvent	=0x101f53c5;	// deprecated
const TInt KEikClearPartialForegroundState		=0x101f54f4;
const TInt KEikPartialForeground				=0x101f6aab;

const TInt KEikResIdQueryDialog	=0;
const TInt KEikResIdInfoDialog	=1;

#define KAknPhoneIdleViewId TVwsViewId(TUid::Uid(0x100058b3), TUid::Uid(0x100058b3))
#define KAknApplicationShellViewId TVwsViewId(TUid::Uid(0x101F4CD2), TUid::Uid(0x00000001))

#define COMPARE_BOOLS(a,b) (((a) && (b)) || (!(a) && !(b)))

template <class T>
class TBitFlagsT
	{
public:
	inline TBitFlagsT();
	inline TBitFlagsT(T aFlags);
	inline TBitFlagsT(const TBitFlagsT& aFlags);
	inline TBitFlagsT& operator=(const TBitFlagsT& aFlags);

	inline void SetAll();
	inline void ClearAll();

	inline const TBool operator[](TInt aFlagIndex) const;
	inline TBool IsSet(TInt aFlagIndex) const;
	inline TBool IsClear(TInt aFlagIndex) const;
	inline void Set(TInt aFlagIndex);
	inline void Clear(TInt aFlagIndex);
	inline void Assign(TInt aFlagIndex, TBool aVal);
	inline void Toggle(TInt aFlagIndex);

private:
	inline T FlagMask(TInt aFlagIndex) const;

public:
	T iFlags;
	};

typedef TBitFlagsT<TUint32> TBitFlags32;
typedef TBitFlagsT<TUint16> TBitFlags16;
typedef TBitFlagsT<TUint8> TBitFlags8;
typedef TBitFlags32 TBitFlags;

template <class T>
inline TBitFlagsT<T>::TBitFlagsT() : iFlags(0) 
	{}
template <class T>
inline TBitFlagsT<T>::TBitFlagsT(T aFlags) : iFlags(aFlags) 
	{}
template <class T>
inline TBitFlagsT<T>::TBitFlagsT(const TBitFlagsT<T>& aFlags) : iFlags(aFlags.iFlags) 
	{}
template <class T>
inline TBitFlagsT<T>& TBitFlagsT<T>::operator=(const TBitFlagsT<T>& aFlags)
	{ iFlags = aFlags.iFlags; return *this; }
template <class T>
inline T TBitFlagsT<T>::FlagMask(TInt aFlagIndex) const
	{ return T(T(1)<<aFlagIndex); }
template <class T>
inline TBool TBitFlagsT<T>::IsSet(TInt aFlagIndex) const
	{ return iFlags & FlagMask(aFlagIndex); }
template <class T>
inline TBool TBitFlagsT<T>::IsClear(TInt aFlagIndex) const
	{ return !IsSet(aFlagIndex); }
template <class T>
inline void TBitFlagsT<T>::Set(TInt aFlagIndex)
	{ iFlags |= FlagMask(aFlagIndex); }
template <class T>
inline void TBitFlagsT<T>::Clear(TInt aFlagIndex)
	{ iFlags &= ~(FlagMask(aFlagIndex)); }
template <class T>
inline void TBitFlagsT<T>::Assign(TInt aFlagIndex, TBool aVal)
	{ if (aVal) Set(aFlagIndex); else Clear(aFlagIndex); }
template <class T>
inline void TBitFlagsT<T>::Toggle(TInt aFlagIndex)
	{ iFlags ^= FlagMask(aFlagIndex); }
template <class T>
inline const TBool TBitFlagsT<T>::operator[](TInt aFlagIndex) const
	{ return IsSet(aFlagIndex); }
template <class T>
inline void TBitFlagsT<T>::SetAll()
	{ iFlags = ~(T(0)); }
template <class T>
inline void TBitFlagsT<T>::ClearAll()
	{ iFlags = T(0); }


#endif
