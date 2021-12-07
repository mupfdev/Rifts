// Periodic.cpp
//
// Copyright (c)  2000 Symbian Ltd.  All rights reserved.


/*
	Shows difference between CPeriodic and CHeartBeat
	CPeriodic uses repeated RTimer::After() requests to get
		a periodic tick - simple, but the time the tick is serviced lags
		increasingly.
		As a nuance of CPeriodic, it takes a TCallBack to service
		its requests.
	CHeartbeat uses repeated RTimer::Lock() requests: its
		requests complete in synchronization with the beating
		of the system clock.
		As a nuance of CHeartbeat, it takes an MBeating* mixin:
		the MBeating's Beat() function is called when completion
		occurs in sync, and Synchronize() is called when
		synchronization has been lost.
*/

// standard example header
#include "CommonFramework.h"

// beginning of real example

#include <e32math.h>

void RandomDelay(TInt64& aSeed, TInt /*aTimerNumber*/)
	{
	// initialize seed first time through
	if (aSeed==0)
		{
		TTime time;
		time.HomeTime();
		aSeed=time.Int64();
		}
	// ok, here we go
	TReal randomZeroToOne;
	randomZeroToOne = Math::FRand(aSeed);
	TReal realDelay;
	realDelay = randomZeroToOne * randomZeroToOne * 2000000;
	TInt32 intDelay;
	Math::Int(intDelay, realDelay);
	TTimeIntervalMicroSeconds32 delayMicroSeconds;
	delayMicroSeconds=intDelay;
	User::After(delayMicroSeconds);
	}

// A version of the RandomDelay function which is not random ! 
// The delay is fixed at 1000000us and may be useful to 
// experiment with. 
//
//
//void RandomDelay(TInt64& /* aSeed */, TInt aTimerNumber)
//	{
//	User::After(1000000);
//  _LIT(KFormatMisc,"Delay for timer %d: 1000000us\n");
//	console->Printf(KFormatMisc, aTimerNumber);
//	}


class TAppRunner
	{
public:
	TAppRunner();
	void NotifyFinished(); // notify an active object has finished
	void NotifyStarted(); // notify an active object has started
// private:
	TInt iActiveObjects; // count of active objects
	};

TAppRunner::TAppRunner()
	{
	iActiveObjects=0;
	}

void TAppRunner::NotifyStarted()
	{
	iActiveObjects++;
	}

void TAppRunner::NotifyFinished()
	{
	iActiveObjects--;
	if (iActiveObjects==0) CActiveScheduler::Stop();
	}

/*
	CPeriodicRunner class

	Constructor makes a CPeriodic and sets it off with one-second ticks.
	These are fielded by the callback function, the static Tick(TAny*),
	which simply casts the pointer to a CPeriodicRunner* and calls
	the non-static callback, DoTick().

	Processing gets behind: when the ticks left have counted down to zero,
	it should be behind by a second or two.  The destructor indicates how many
	seconds since the object's creation.
*/

class CPeriodicRunner : public CBase
	{
public:
	// construct, add CPeriodic to active scheduler, and start it
	static CPeriodicRunner* NewL(TInt aTickInterval, TInt aTotalTicks, TAppRunner& aAppRunner);
	~CPeriodicRunner(); // destruct and give statistics
protected:
	CPeriodicRunner(TInt aTickInterval, TInt aTotalTicks, TAppRunner& aAppRunner);
private:
	void ConstructL(); // second construction phase
	// functions for TCallBack protocol
	static TInt Tick(TAny* aObject); // directly called
	void DoTick(); // indirectly called
private:
	// constructor parameters
	TAppRunner& iAppRunner; // notify when started and finished
	TInt iTotalTicks; // number of ticks requested
	TInt iTickInterval; // the tick interval in microseconds
	// things set up by ConstructL
	TTime iStartTime; // when we were started
	CPeriodic* iPeriodic; // periodic timer active object
	// ticks left will be decremented as we go
	TInt iTicksLeft; // number of ticks before we expire
	TInt iTimerNumber; // indentifying number for the timer
	// seed for random delay generator
	TInt64 iDelaySeed;
	};

// protected C++ constructor
CPeriodicRunner::CPeriodicRunner(TInt aTickInterval, TInt aTotalTicks, TAppRunner& aAppRunner)
	: iAppRunner(aAppRunner), iTotalTicks(aTotalTicks), iTickInterval(aTickInterval)
	{}

// private second-phase constructor
void CPeriodicRunner::ConstructL()
	{
	iStartTime.HomeTime();
	iPeriodic=CPeriodic::NewL(0); // neutral priority
	iAppRunner.NotifyStarted();
	iTimerNumber = iAppRunner.iActiveObjects; // set idenfifying number for timer
	iTicksLeft = iTotalTicks;
	// variable (actually 1 second) delay and interval 
	iPeriodic->Start(iTickInterval,iTickInterval,TCallBack(Tick, this));
	}

// construct, add CPeriodic to active scheduler, and start it
CPeriodicRunner* CPeriodicRunner::NewL(TInt aTickInterval, TInt aTotalTicks, TAppRunner& aAppRunner)
	{
	CPeriodicRunner* self=new (ELeave) CPeriodicRunner(aTickInterval, aTotalTicks, aAppRunner);
	CleanupStack::PushL(self);
    self->ConstructL();
	CleanupStack::Pop();
    return self;
	}

// destruct and give statistics
CPeriodicRunner::~CPeriodicRunner()
	{
	TTimeIntervalMicroSeconds elapsedTime;
	TTime currentTime;
	// set current time
	currentTime.HomeTime(); // set currentTime to now
	// find and show elapsed time & ticks 
	elapsedTime = currentTime.MicroSecondsFrom(iStartTime);
	// NOTE - Int64() returns a const reference.
	//        GetTInt() is a non const function - hence the need to
	//        copy the returned TInt64.
	TInt64 a = elapsedTime.Int64(); 
	_LIT(KFormat1,"Periodic timer %d finished: %dus for %d %dus ticks\n");
	console->Printf(KFormat1,iTimerNumber,a.GetTInt(),iTotalTicks,iTickInterval);
	//  cancel any outstanding request; delete owned CPeriodic object 
	iPeriodic->Cancel();
    delete iPeriodic;
	// tell app runner we've finished (if we're last, scheduler will stop)
	iAppRunner.NotifyFinished();
	}

// private
TInt CPeriodicRunner::Tick(TAny* aObject)
	{
	((CPeriodicRunner*)aObject)->DoTick(); // cast, and call non-static function
	return 1;
	}

// private
void CPeriodicRunner::DoTick()
	{
	iTicksLeft--;
	_LIT(KFormat2,"Periodic timer %d: %d ticks done\n");
	console->Printf(KFormat2, iTimerNumber, iTotalTicks - iTicksLeft);
	if(iTicksLeft==0)
		{
		delete this;
		}
	RandomDelay(iDelaySeed,iTimerNumber); // a random delay to mess up the timing
	}

/*
	CHeartbeatRunner class

	This class receives beats in sync with the system clock.  It also has a much
	nicer interface than for periodic timers - the MBeating mixin, which is nicely
	object-oriented.

	Most of the time, the Beat() function is called which trivially updates the tick
	count.  Occasionally, synchronization is lost, and the Synchronize() function
	is called instead: this must find out from the system time how many ticks should
	have been counted, and update things accordingly.

	The destructor gives the same comparisons as the CPeriodic's.  The discrepancy
	between the number of ticks and the number of seconds since construction should
	never be more than is accounted for by the last heartbeat.
*/

class CHeartbeatRunner : public CBase, public MBeating
	{
public:
	// construct, add CHeartbeat to active scheduler, and start it
	static CHeartbeatRunner* NewL(TInt aTickInterval, TInt aTotalTicks, TAppRunner& aAppRunner);
	~CHeartbeatRunner(); // destruct and give statistics
protected:
	CHeartbeatRunner(TInt aTickInterval, TInt aTotalTicks, TAppRunner& aAppRunner);
private:
	void ConstructL();
	// functions for MBeating protocol
	void Beat(); // called when beat works ok
	void Synchronize(); // called when we need to synchronize
private:
	// constructor parameters
	TAppRunner& iAppRunner; // notify when started and finished
	TInt iTotalTicks; // number of ticks requested
	TInt iTickInterval; // tick length in microseconds
	// things set up by ConstructL
	TTime iStartTime; // when we were started
	CHeartbeat* iHeartbeat; // heartbeat active object
	// ticks left decrements as we go
	TInt iTicksLeft; // number of ticks before we expire
	TInt iTimerNumber; // indentifying number for the timer
	// seed for random delay generator
	TInt64 iDelaySeed;
	};

// protected C++ constructor
CHeartbeatRunner::CHeartbeatRunner(TInt aTickInterval, TInt aTotalTicks, TAppRunner& aAppRunner)
	:iAppRunner(aAppRunner), iTotalTicks(aTotalTicks), iTickInterval(aTickInterval)
	{}

// private second-phase constructor
void CHeartbeatRunner::ConstructL()
	{
	iStartTime.HomeTime();
	iHeartbeat=CHeartbeat::NewL(0); // neutral priority
	iAppRunner.NotifyStarted();
	iTimerNumber = iAppRunner.iActiveObjects; // set idenfifying number for timer
	iTicksLeft = iTotalTicks;
	// start the heartbeat timer, beating exactly on the second
	iHeartbeat->Start(ETwelveOClock,this);
	}

// construct, add CHeartbeat to active scheduler, and start it
CHeartbeatRunner* CHeartbeatRunner::NewL(TInt aTickInterval, TInt aTotalTicks, TAppRunner& aAppRunner)
	{
	CHeartbeatRunner* self=new (ELeave) CHeartbeatRunner(aTickInterval, aTotalTicks, aAppRunner);
	CleanupStack::PushL(self);
    self->ConstructL();
	CleanupStack::Pop();
    return self;
	}

// destruct and give statistics
CHeartbeatRunner::~CHeartbeatRunner()
	{
	TTimeIntervalMicroSeconds elapsedTime;
	TTime currentTime;
	currentTime.HomeTime(); // set current time to now
	// find and show elapsed time & ticks 
	elapsedTime = currentTime.MicroSecondsFrom(iStartTime); 
	TInt64 a = elapsedTime.Int64(); // Int64() returns a const reference to TInt64
	_LIT(KFormat3,"Heartbeat timer %d finished: %dus for %d %dus ticks\n");
	console->Printf(KFormat3,iTimerNumber,a.GetTInt(),iTotalTicks,iTickInterval);
	//  cancel any outstanding request; delete owned CPeriodic object 
	iHeartbeat->Cancel();
    delete iHeartbeat;
	// tell app runner we've finished (if last, scheduler will stop)
	iAppRunner.NotifyFinished();
	}

// private
void CHeartbeatRunner::Beat()
	{
	iTicksLeft--;
	if(iTicksLeft<=0)
		delete this;
	else
		RandomDelay(iDelaySeed,iTimerNumber); // a random delay to mess up the timing
	}

// private
void CHeartbeatRunner::Synchronize()
	{
	TInt ticksMissed = 0;
		 // what time in microseconds should be for this tick
	TTime desiredTime = iStartTime + TTimeIntervalMicroSeconds((iTotalTicks - iTicksLeft) * iTickInterval);
	TTime currentTime; // set current time to now
	currentTime.HomeTime();
	TTimeIntervalMicroSeconds missedTime = currentTime.MicroSecondsFrom(desiredTime);
	// Calculate the ticks missed (quickly!)
	TInt64 missedTimeInt = missedTime.Int64(); // convert the missed time interval to an Int64
	ticksMissed = (missedTimeInt / iTickInterval).GetTInt();
	// The following loop increments the ticks missed by the same amount, but takes much longer
	// while (desiredTime < currentTime)
	//	{
	//	desiredTime = desiredTime - TTimeIntervalMicroSeconds(iTickInterval);
	//	ticksMissed++;
	//	}
	_LIT(KFormat4,"Ticks done %d\n");
	console->Printf(KFormat4, (iTotalTicks -iTicksLeft));
	
	iTicksLeft = iTicksLeft - ticksMissed;
	TTimeIntervalMicroSeconds elapsedTime;
	elapsedTime = currentTime.MicroSecondsFrom(iStartTime); // find and show elapsed time & ticks 
	_LIT(KFormat5,"Elapsed time: %d\n");
	console->Printf(KFormat5, elapsedTime);
	
	_LIT(KFormat6,"Synchronize heartbeat timer %d: ticks missed %d: left %d: done now %d\n");
	console->Printf(KFormat6,
		            iTimerNumber,
					ticksMissed,
					iTicksLeft,
					((iTotalTicks - iTicksLeft) <= iTotalTicks) ? iTotalTicks - iTicksLeft : iTotalTicks
				   );
	// iTicksLeft can be less than zero
	if(iTicksLeft<=0)
		{
		delete this;
		}
	}

/*
	TAppRunner class

	Encapsulates logic for stopping the active scheduler
*/


// do the example

void doExampleL()
    {
	// make and install the active scheduler
	CActiveScheduler*  scheduler = new (ELeave) CActiveScheduler;
	CleanupStack::PushL(scheduler); // push to clean-up stack
	CActiveScheduler::Install(scheduler); // install as active scheduler

	TAppRunner appRunner; // to control stopping the scheduler
	TInt TickInterval = 1000000; // set tick interval to 1 second (it's fixed for CHeartbeat)

	// run each kind of timer for increasing numbers of ticks
	// was 10/40/10
	for (TInt ticks=4; ticks<=6; ticks+=2)
		{
		  // create periodic timer
		  //
		  // Comment next two lines out if you just want to see heart beat runner
		CPeriodicRunner* periodic=CPeriodicRunner::NewL(TickInterval, ticks, appRunner);
		periodic = NULL; // statement has no effect, but stops compiler warning
		
		  // create hearbeat
		  //
		  // Comment next two lines out if you just want to see periodic timer
		CHeartbeatRunner* beater=CHeartbeatRunner::NewL(TickInterval, ticks, appRunner);
		beater = NULL;  // statement has no effect, but stops compiler warning
		
		}

	CActiveScheduler::Start();
	CleanupStack::PopAndDestroy(); // scheduler
	}

