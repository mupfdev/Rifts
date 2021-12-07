//
// EIKSVFTY.H
//

// Standard factory definitions

#if !defined(__EIKSVFTY_H__)
#define __EIKSVFTY_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

class TAlarmInfo;
class CEikAlmControlSupervisor;

class MEikServNotifyAlert
	{
public:
	virtual void Release()=0;
	virtual TInt DisplayNotifier(const TDesC& aTitle,const TDesC& aLabel,const TDesC& aBut1,const TDesC& aBut2)=0;
	};

class MEikServAlarm
	{
public:
	virtual void Release()=0;
	virtual void ShowAlarm()=0;
	virtual void HideAlarm()=0;
	virtual TInt CurrentServerState() const=0;
	virtual void UpdateSoundPauseTimeInterval(TInt aMinutes)=0;
	virtual void UpdateForAlarmServerState(TInt aNewAlarmServerState)=0;
	virtual void UpdateAlarmInfo(const TAlarmInfo& aAlarm,const TFullName& aOwner)=0;
	virtual void StartPlayAlarmL(const TDesC& aAlarmName)=0;
	virtual void StopPlayAlarm()=0;
	};

class MEikServAlarmFactory
	{
	public:
		virtual MEikServAlarm* NewAlarmL(CEikAlmControlSupervisor& aSupervisor)=0;
	};

#endif
