// EIKSSND.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSSND_H__)
#define __EIKSSND_H__

#include <e32base.h>
#include <s32file.h>
#include <mda\common\controller.h>

typedef TUid TBaSystemSoundUid;
typedef TFileName TBaSystemSoundName;

#define KSystemSoundDefaultVolume	1
#define KSystemSoundDefaultPriority	0

//this dll may use uids 48aa to 48ca
const TBaSystemSoundUid KSystemSoundRingUID		= {0x100048AB};
const TBaSystemSoundUid KSystemSoundAlarmUID	= {0x100048AC};
const TBaSystemSoundUid KSystemSoundMessageUID	= {0x100048AD};

const TBaSystemSoundUid KUidSystemSoundError={0x1000609E};
const TBaSystemSoundUid KUidSystemSoundEvent={0x1000609F};

/**
 * Logical sound wrapper
 */
class TBaSystemSoundType
	{
public:
	IMPORT_C TBaSystemSoundType();
	IMPORT_C TBaSystemSoundType(TBaSystemSoundUid aMajor,TUid aMinor=KNullUid);
public:
	inline TBool IsNull() const;
	IMPORT_C TBool operator==(const TBaSystemSoundType& aType) const;
public:
	TBaSystemSoundUid iMajor;
	TUid iMinor;
	};

/**
 * The class to contain the information for a system sound.  A sound may be any of
 * a file, a tone or a fixed sequence
 */
class TBaSystemSoundInfo
	{
public:
	class TTone
		{
	public:
		inline TTone();
		inline TTone(TInt aFrequency,TTimeIntervalMicroSeconds32 aDuration);
	public:
		TBool IsNull() const;
	public:
		void InternalizeL(RReadStream& aStream);
		void ExternalizeL(RWriteStream& aStream) const;
	public:
		TInt iFrequency;
		TTimeIntervalMicroSeconds32 iDuration;
		};
public:
	enum TSoundCategory
		{
		ENull,
		EFile,
		ESequence,
		ETone
		};
public:
	IMPORT_C TBaSystemSoundInfo();
	IMPORT_C TBaSystemSoundInfo(const TBaSystemSoundType& aType,const TBaSystemSoundName& aName,
							TInt aVolume=KSystemSoundDefaultVolume,TInt aPriority=KSystemSoundDefaultPriority);
	IMPORT_C TBaSystemSoundInfo(const TBaSystemSoundType& aType,TInt aFixedSequence,
							TInt aVolume=KSystemSoundDefaultVolume,TInt aPriority=KSystemSoundDefaultPriority);
	IMPORT_C TBaSystemSoundInfo(const TBaSystemSoundType& aType,TTone aTone,
							TInt aVolume=KSystemSoundDefaultVolume,TInt aPriority=KSystemSoundDefaultPriority);
public:
	IMPORT_C TSoundCategory SoundCategory() const;
	inline TInt FixedSequenceNumber() const;
	inline TBaSystemSoundName FileName() const;
	inline TTone Tone() const;
	IMPORT_C void SetFixedSequenceNumber(TInt aNumber);
	IMPORT_C void SetFileName(const TBaSystemSoundName& aFileName);
	IMPORT_C void SetTone(const TTone& aTone);
public:
	TBaSystemSoundType iType;
	TInt iVolume;
	TInt iPriority;
private:
	TBaSystemSoundName iName;
	TInt iFixedSequence;
	TTone iTone;
	};

/**
 * Utility class to handle system sounds.  Sounds identified by 2 uids can be set or retrieved
 */
class BaSystemSound
	{
public:
	IMPORT_C static TInt GetSound(RFs& aFsSession,const TBaSystemSoundType& aType,TBaSystemSoundInfo& aInfo);
	IMPORT_C static void SetSoundL(RFs& aFsSession,const TBaSystemSoundInfo& aInfo);
	IMPORT_C static TFileName SystemSoundFile();
private:
	TBaSystemSoundName static DefaultSound(TBaSystemSoundUid aSSUid);
	};

/**
 * An array to contain the set of system sounds for a TBaSystemSoundUid
 * @internal
 * Internal to Symbian
 */
class CBaSystemSoundArray: public CBase
	{
public:
	CBaSystemSoundArray();
	~CBaSystemSoundArray();
public:
	IMPORT_C static CBaSystemSoundArray* NewL();
	IMPORT_C static CBaSystemSoundArray* NewLC();
	IMPORT_C void RestoreL(RFs& aFsSession,TBaSystemSoundUid aSSUid);
	IMPORT_C TInt Count() ;
	IMPORT_C TBaSystemSoundInfo At(TInt aIndex);
public:
	TInt FindUid(TUid aUid,TBaSystemSoundInfo& aInfo);
	void SetSoundL(const TBaSystemSoundInfo& aInfo); 
	void StoreL(RFs& aFsSession);
	void RestoreL(RFs& aFsSession,TBaSystemSoundUid aSSUid,const TDesC& aFileName);
private:
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TBaSystemSoundUid iUid;
	CArrayFixFlat<TBaSystemSoundInfo> iSystemSounds;
	};

/**
 * Utility class to bundle up priority, priority preference and device specific data
 * Only intended to be used in conjunction with TBaSystemSoundInfo::iPriority
 *
 * Layout of class is
 * bits 31 -> 16:	Device specific priority preference data
 * bits 15 -> 8:	Standard Epoc TMdaPriorityPreference setting
 * bits 7 -> 0:		Priority value stored as a TInt8.  Maximum range possible is -256 -> +255
 *					Note that MediaSvr currently defines a narrower range than this
 *
 */
class TBaSoundPriorityBase
	{
public:
	inline TInt Int() const;
	inline TInt Priority() const;
	IMPORT_C TMdaPriorityPreference PriorityPreference() const;
protected:
	inline TBaSoundPriorityBase();
	void Set(TInt aPriority,TMdaPriorityPreference aPriorityPreference=EMdaPriorityPreferenceTimeAndQuality);
protected:
	TInt iPriority;
	};

/**
 * Encode TBaSystemSoundInfo::iPriority before persisting a sound preference
 */
class TBaSoundPriorityEncoder : public TBaSoundPriorityBase
	{
public:
	IMPORT_C TBaSoundPriorityEncoder(TInt aPriority,TMdaPriorityPreference aPriorityPreference=EMdaPriorityPreferenceTimeAndQuality);
	};

/**
 * Decode a restored TBaSystemSoundInfo::iPriority
 */
class TBaSoundPriorityDecoder : public TBaSoundPriorityBase
	{
public:
	inline TBaSoundPriorityDecoder(TInt aVal);
	};


inline TBool TBaSystemSoundType::IsNull() const
	{return iMajor==KNullUid && iMinor==KNullUid;}

inline TBaSystemSoundInfo::TTone::TTone()
	: iFrequency(0), iDuration(0)
	{}
inline TBaSystemSoundInfo::TTone::TTone(TInt aFrequency,TTimeIntervalMicroSeconds32 aDuration)
	: iFrequency(aFrequency), iDuration(aDuration)
	{}

inline TInt TBaSystemSoundInfo::FixedSequenceNumber() const
	{return iFixedSequence;}
inline TBaSystemSoundName TBaSystemSoundInfo::FileName() const
	{return iName;}
inline TBaSystemSoundInfo::TTone TBaSystemSoundInfo::Tone() const
	{return iTone;}

inline TBaSoundPriorityBase::TBaSoundPriorityBase()
	{}
inline TInt TBaSoundPriorityBase::Int() const
	{return iPriority;}
inline TInt TBaSoundPriorityBase::Priority() const
	{return (TInt8)iPriority;}

inline TBaSoundPriorityDecoder::TBaSoundPriorityDecoder(TInt aVal)
	{iPriority=aVal;}

#endif
