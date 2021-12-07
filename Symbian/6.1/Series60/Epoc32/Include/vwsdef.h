// VWSDEF.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#ifndef __VWSDEF_H__
#define __VWSDEF_H__

#include <e32std.h>

#ifdef ASSERT
#ifdef _DEBUG
#undef ASSERT
// Redefine assert to be a little more useful to us, i.e. to include file & line number
#define __ASSERT_FILE__(s) _LIT(KPanicFileName,s)
#define __ASSERT_PANIC__(l) User::Panic(KPanicFileName().Right(12),l)
#define ASSERT(x) { __ASSERT_FILE__(__FILE__); __ASSERT_DEBUG(x, __ASSERT_PANIC__(__LINE__) ); }
#endif
#endif

/**
 * The TVwsViewId class identifies a view using a unique application and view id. The application id is required
 * so that an app can be started if it is not running.
 *
 * @internal
 * Internal to Symbian
 */
class TVwsViewId
	{
public:
	inline TVwsViewId();
	inline TVwsViewId(const TVwsViewId& aUid);
	inline TVwsViewId(TUid aAppUid,TUid aViewUid);
	inline TBool operator==(const TVwsViewId& aUid) const;
	inline TBool operator!=(const TVwsViewId& aUid) const;
public:
	TUid iAppUid;
	TUid iViewUid;
	};

#define KNullViewId TVwsViewId(KNullUid,KNullUid)


/**
 * The TVwsViewIdAndMessage class identifies a view and encapsulates a message to be read by the view when it is
 * activated.
 *
 * @internal
 * Internal to Symbian
 */
class TVwsViewIdAndMessage
	{
public:
	inline TVwsViewIdAndMessage();
	inline TVwsViewIdAndMessage(const TVwsViewId& aId);
	inline TVwsViewIdAndMessage(const TVwsViewId& aId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
public:
	TVwsViewId iViewId;
	TUid iCustomMessageId;
	TInt iCustomMessageLength;
	TPtrC8 iCustomMessage;
	};


/**
 * The TVwsViewEvent class encapsulates the attributes of a view server event. These are the event type, the ids of
 * the two views associated with the event and the attributes of any message which can go with the event.
 *
 * @internal
 * Internal to Symbian
 */
class TVwsViewEvent
	{
public:
	enum TVwsViewEventType
		{
		EVwsActivateView,
		EVwsDeactivateView,
		EVwsScreenDeviceChanged,
		EVwsDeactivationNotification,
		EVwsActivationNotification
		};
public:
	inline TVwsViewEvent();
	inline TVwsViewEvent(TVwsViewEventType aEventType);
	inline TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId);
	inline TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId,const TVwsViewId& aViewTwoId);
	inline TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId,const TVwsViewId& aViewTwoId,TUid aCustomMessageId,TInt aCustomMessageLength);
public:
	TVwsViewEventType iEventType;
	TVwsViewId iViewOneId;
	TVwsViewId iViewTwoId;
	TUid iCustomMessageId;
	TInt iCustomMessageLength;
	};


//
// Typedefs.
//

typedef TPckgBuf<TVwsViewIdAndMessage> TVwsViewIdAndMessageBuf;
typedef TPckgBuf<TVwsViewEvent> TVwsViewEventBuf;


//
// Inlines
//

inline TVwsViewId::TVwsViewId()
	: iAppUid(KNullUid), iViewUid(KNullUid) {}

inline TVwsViewId::TVwsViewId(const TVwsViewId& aUid)
	: iAppUid(aUid.iAppUid), iViewUid(aUid.iViewUid) {}

inline TVwsViewId::TVwsViewId(TUid aAppUid,TUid aViewUid)
	: iAppUid(aAppUid), iViewUid(aViewUid) {}

inline TBool TVwsViewId::operator==(const TVwsViewId& aUid) const
	{
	return (aUid.iAppUid==iAppUid && aUid.iViewUid==iViewUid);
	}

inline TBool TVwsViewId::operator!=(const TVwsViewId& aUid) const
	{
	return (aUid.iAppUid!=iAppUid || aUid.iViewUid!=iViewUid);
	}


inline TVwsViewIdAndMessage::TVwsViewIdAndMessage()
	: iViewId(TVwsViewId()), iCustomMessageLength(0)
	{
	iCustomMessageId.iUid=0;
	iCustomMessage.Set(KNullDesC8);
	}

inline TVwsViewIdAndMessage::TVwsViewIdAndMessage(const TVwsViewId& aId)
	: iViewId(aId), iCustomMessageLength(0)
	{
	iCustomMessageId.iUid=0;
	iCustomMessage.Set(KNullDesC8);
	}

inline TVwsViewIdAndMessage::TVwsViewIdAndMessage(const TVwsViewId& aId,TUid aCustomMessageId,const TDesC8& aCustomMessage)
	: iViewId(aId), iCustomMessageId(aCustomMessageId)
	{
	iCustomMessageLength=aCustomMessage.Length();
	iCustomMessage.Set(aCustomMessage);
	}


inline TVwsViewEvent::TVwsViewEvent() {}

inline TVwsViewEvent::TVwsViewEvent(TVwsViewEventType aEventType)
	: iEventType(aEventType),iViewOneId(),iViewTwoId(),iCustomMessageId(KNullUid),iCustomMessageLength(0) {}

inline TVwsViewEvent::TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId)
	: iEventType(aEventType),iViewOneId(aViewOneId),iViewTwoId(),iCustomMessageId(KNullUid),iCustomMessageLength(0) {}

inline TVwsViewEvent::TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId,const TVwsViewId& aViewTwoId)
	: iEventType(aEventType),iViewOneId(aViewOneId),iViewTwoId(aViewTwoId),iCustomMessageId(KNullUid),iCustomMessageLength(0) {}

inline TVwsViewEvent::TVwsViewEvent(TVwsViewEventType aEventType,const TVwsViewId& aViewOneId,const TVwsViewId& aViewTwoId,TUid aCustomMessageId,TInt aCustomMessageLength)
	: iEventType(aEventType),iViewOneId(aViewOneId),iViewTwoId(aViewTwoId),iCustomMessageId(aCustomMessageId),iCustomMessageLength(aCustomMessageLength) {}


#endif
