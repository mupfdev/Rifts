// CNTDBOBS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__CNTDBOBS_H__)
#define __CNTDBOBS_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif

#if !defined(__D32DBMS_H__)
#include <d32dbms.h>
#endif

/**
 * Change event type.
 *
 * For events which update, delete or add a contact item, the ID of the
 * item affected is contained in the <code>TContactDbObserverEvent</code>
 * struct.
 */
enum TContactDbObserverEventType
	{
	EContactDbObserverEventNull,			/** Null event type.*/
	EContactDbObserverEventUnused,			/** Not currently used.*/
	EContactDbObserverEventContactChanged,	/** A contact item (not a template, group or own card) has been changed.*/
	EContactDbObserverEventContactDeleted,	/** A contact item (not a template, group or own card) has been deleted.*/
	EContactDbObserverEventContactAdded,	/** A contact item (not a template or group) has been added.*/
	EContactDbObserverEventUnknownChanges,	/** Unknown change event type.*/
	EContactDbObserverEventRecover,			/** Recover from a damaged database.*/
	EContactDbObserverEventRollback,		/** Rollback from a change to the database.*/
	EContactDbObserverEventTablesClosed,	/** Database tables closed.*/
	EContactDbObserverEventTablesOpened,	/** Database tables opened.*/
	EContactDbObserverEventTemplateChanged, /** A contact card template has changed.*/
	EContactDbObserverEventTemplateDeleted, /** A contact card template has been deleted.*/
	EContactDbObserverEventTemplateAdded,	/** A contact card template has been added.*/
	EContactDbObserverEventCurrentItemDeleted,		/** The database's current item has been deleted.*/
	EContactDbObserverEventCurrentItemChanged,		/** The database's current item has changed.*/
	EContactDbObserverEventOwnCardChanged,	/** The database's own card has changed.*/
	EContactDbObserverEventPreferredTemplateChanged,/** The database's preferred template has been set. (See
														<code>CContactDatabase::SetPrefTemplateL()</code>).*/
	EContactDbObserverEventOwnCardDeleted,	/** An own card has been deleted from the database.*/
	EContactDbObserverEventGroupAdded,		/** A contact item group has been added.*/
	EContactDbObserverEventGroupChanged,	/** A contact item group has been updated.*/
	EContactDbObserverEventGroupDeleted,	/** A contact item group has been deleted from the database.*/
	EContactDbObserverEventCurrentDatabaseChanged,	/** The current database has changed.*/
	EContactDbObserverEventSpeedDialsChanged, 
	EContactDbObserverEventSortOrderChanged
	};

struct TContactDbObserverEvent
	{
	TContactDbObserverEventType iType;
	TContactItemId iContactId;
	TUint iConnectionId;
	};

/**
 * Specifies the mixin protocol for an observer to handle changes to a
 * contact database.
 *
 * It should be inherited by classes which implement this protocol.It
 * specifies a single pure virtual function which should be implemented
 * by the observer class to test the type of the change event (see the
 * <code>TContactDbObserverEventType</code> enum) and handle it.A contact
 * database observer pointer is passed to the <code>NewL()</code>
 * function for the <code>CContactChangeNotifier</code> class.
 *
 * @since 5.0
 * @lib ""
 */
class MContactDbObserver
	{
public:
	/**
	  * Tests the contact database observer event type and handles it.
	  *
	  * The ID of a contact affected by the change event, if relevant, can be
	  * retrieved via <code>TContactDbObserverEvent::iContactId</code>.
	  *
	  * @param     "TContactDbObserverEvent aEvent"
	  *            Provides information about the change event.
	  */
	virtual void HandleDatabaseEventL(TContactDbObserverEvent aEvent)=0;
	};

#endif
