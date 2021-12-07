/*
* ============================================================================
*  Name     : aknindicatorcontainer.h
*  Part of  : AVKON
*
*  Description:
*       A default control in the status pane's small indicator pane.
*       Editor indicators uses also same control in the navigation pane and
*       in queries.
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNINDICATORCONTAINER_H
#define AKNINDICATORCONTAINER_H

//  INCLUDES
#include <coecntrl.h>
#include <eikspane.h>

class CIncallStatusBubble;
class CAknIndicator;
class CAknIndicatorContainerExtension;

/**
 * A default control in the status pane's small indicator pane.
 */
class CAknIndicatorContainer : public CCoeControl, public MEikStatusPaneObserver
	{
public:
    
    enum TLayoutOrientation
        {
        EVertical,
        EHorizontal
        };

    enum TIndicatorAlignment
        {
        ELeft,
        ERight
        };
    
    enum TIndicatorContext
        {
        EUniversalIndicators = 0,
        ENaviPaneEditorIndicators,
        EQueryEditorIndicators,
        EFindIndicators
        };

public:
    /**
    * Constructor. Creates EUniversalIndicators object.
    */
    IMPORT_C CAknIndicatorContainer();

    /**
    * Constructor. Creates EUniversalIndicators, ENaviPaneEditorIndicators or
    * EQueryEditorIndicators object.
    *
    * @param aIndicatorContext Indicator container context.
    */
    IMPORT_C CAknIndicatorContainer(TInt aIndicatorContext);

    /**
    * Destructor.
    */
    IMPORT_C ~CAknIndicatorContainer();

    /**
    * 2nd phase constructor.
    */
    IMPORT_C void ConstructL();
    
    /**
    * Sets indicator state. The state can be one of the following: EAknIndicatorStateOff,
	* EAknIndicatorStateOn or EAknIndicatorStateAnimate. Editor indicators
    * do not support animation.
    *
    * @param aIndicatorId ID of the indicator to be modified.
    * @param aState A state to be set to the indicator.
    * @param aDrawNow A flag to indicate if the indicator is redrawn with this call.
    */
    IMPORT_C void SetIndicatorState(TUid aIndicatorId, TInt aState, TBool aDrawNow = ETrue);

    /** 
    * Return a current state of the indicator.
    *
    * @param aIndicatorId ID of the indicator.
    * @return Current state of the indicator.
    */
    IMPORT_C TInt IndicatorState(TUid aIndicatorId);
    
    /** 
    * Sets value to the message length indicator 
    * (EAknNaviPaneEditorIndicatorMessageLength).
    *
    * @param aIndicatorId ID of the indicator to be modified.
    * @param aString Value of the indicator.
    */
    IMPORT_C void SetIndicatorValueL(TUid aIndicatorId, const TDesC& aString);

    /** 
    * Sets value to the incall status bubble indicator on the top of the status pane.
    *
    * @param aFlags Mode of the bubble.
    */
    IMPORT_C void SetIncallBubbleFlags(const TInt& aFlags);
    
    /** 
    * Constructs the object from resource.
    *
    * @param aReader Resource reader.
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    /** 
    * Return the context of the indicator.
    *
    * @return context of the indicator.
    */
    IMPORT_C TInt IndicatorContext() const;


public: // From MEikStatusPaneObserver
    /**
    * From MEikStatusPaneObserver. The MEikStatusPaneObserver interface allows
    * a status pane observer to pick up changes in the size or position of 
    * the status pane. Such events will be as a result of layout changes which 
    * cause an actual change in the status pane rectangle.
    */
    IMPORT_C void HandleStatusPaneSizeChange();
    
protected: // From CCoeControl

    /**
	 * Handles a change to the control's resources of type aType
	 * which are shared across the environment, e.g. color scheme change.
     * Responds fade events and fades incall status bubble window group.
	 * @param aType Event type.
	 */
   	IMPORT_C virtual void HandleResourceChange(TInt aType);

    /**
    * From CCoeControl. Handle the size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
    * From CCoeControl. Returns number of controls inside the context pane control.
    * @return Number of component controls.
    */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
    * From CCoeControl. Returns a control determined by control id.
    * @param anIndex Index of a control to be returned.
    * @return Pointer to control
    */
    IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
    
private: // From CCoeControl
    IMPORT_C virtual void Draw(const TRect& aRect) const;

private:
    virtual void Reserved_1();  
    void PrioritizeIndicatorsL();
    
   	static TInt TickerCallback(TAny* aThis);
    TInt DoTick();

    void IncallBubbleSizeChanged(TBool aAllowIdleStateBubble);

    /**
    * Returns autolock state. 
    *
    * @return Return 1 if autolock application is in the front, 0 otherwise.
    */
    TInt AutolockState();
private:
    
   	typedef CArrayPtrFlat<CAknIndicator> CAknIndicatorQueue;
    CAknIndicatorQueue* iIndicators;
    TLayoutOrientation iLayoutOrientation;
    TLayoutOrientation iPreviousLayoutOrientation;
    
    TIndicatorAlignment iAlignment;
    
    TInt iIndicatorsShown;
    TInt iAnimatedIndicatorsShown;
    CAknIndicatorContainerExtension* iExtension; 
    TInt iIndicatorContext;
    
   	CPeriodic* iTicker;
    TBool iSpare2;  // Reserved for future use.
    TInt iSynchronizingValue;
    
    CIncallStatusBubble* iIncallBubble;
    };


#endif // AKNINDICATORCONTAINER_H

// End of File
