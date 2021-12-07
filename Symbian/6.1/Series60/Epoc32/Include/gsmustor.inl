#include <s32file.h>

inline TInt TSAREntry::Reference() const
	{
	return iReference;
	}

inline void TSAREntry::SetReference(TInt aReference)
	{
	iReference=aReference;
	}

inline TInt TSAREntry::Total() const
	{
	return iTotal;
	}

inline void TSAREntry::SetTotal(TInt aTotal)
	{
	iTotal=aTotal;
	}

inline TInt TSAREntry::Count() const
	{
	return iCount;
	}

inline void TSAREntry::SetCount(TInt aCount)
	{
	iCount=aCount;
	}

inline TBool TSAREntry::IsComplete() const
	{
	return iCount==iTotal;
	}

inline TInt TSAREntry::Data1() const
	{
	return iData1;
	}

inline void TSAREntry::SetData1(TInt aData)
	{
	iData1=aData;
	}

inline TInt TSAREntry::Data2() const
	{
	return iData2;
	}

inline void TSAREntry::SetData2(TInt aData)
	{
	iData2=aData;
	}

inline TInt TSAREntry::Data3() const
	{
	return iData3;
	}

inline void TSAREntry::SetData3(TInt aData)
	{
	iData3=aData;
	}

inline TInt TSAREntry::Data4() const
	{
	return iData4;
	}

inline void TSAREntry::SetData4(TInt aData)
	{
	iData4=aData;
	}

inline TPtrC TSAREntry::Description1() const
	{
	return iDescription1;
	}

inline void TSAREntry::SetDescription1(const TDesC& aDescription)
	{
	iDescription1=aDescription;
	}

inline TPtrC TSAREntry::Description2() const
	{
	return iDescription2;
	}

inline void TSAREntry::SetDescription2(const TDesC& aDescription)
	{
	iDescription2=aDescription;
	}

inline const TTime& TSAREntry::Time() const
	{
	return iTime;
	}

inline void TSAREntry::SetTime(const TTime& aTime)
	{
	iTime=aTime;
	}

inline TStreamId TSAREntry::DataStreamId() const
	{
	return iDataStreamId;
	}

inline void TSAREntry::SetDataStreamId(TStreamId aStreamId)
	{
	iDataStreamId=aStreamId;
	}

inline TBool TSAREntry::IsDeleted() const
	{
	return iFlags&ESAREntryIsDeleted;
	}

inline void TSAREntry::SetIsDeleted(TBool aIsDeleted)
	{
	iFlags=aIsDeleted?iFlags|ESAREntryIsDeleted: iFlags&(~ESAREntryIsDeleted);
	}

inline TBool TSAREntry::IsAdded() const
	{
	return iFlags&ESAREntryIsAdded;
	}

inline void TSAREntry::SetIsAdded(TBool aIsAdded)
	{
	iFlags=aIsAdded?iFlags|ESAREntryIsAdded: iFlags&(~ESAREntryIsAdded);
	}

inline RFs& Fs();
