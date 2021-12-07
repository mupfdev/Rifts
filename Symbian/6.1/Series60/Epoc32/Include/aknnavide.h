/*
* ============================================================================
*  Name     : aknnavide.h
*  Part of  : AVKON
*
*  Description:
*     Decorator class for navigation pane controls. 
*     The class, for example, decorates navigation pane controls with navi arrows.
*     
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNNAVIDE_H
#define AKNNAVIDE_H

#include <coecntrl.h>
#include <coeccntx.h>
#include <e32std.h>
#include <coecntrl.h>

#include <aknnaviobserver.h>
#include <aknnavi.h>

class CEikScrollButton;


/**
 * Decorator class for navigation pane controls.
 * The class, for example, decorates navigation pane controls with navi arrows.
 */
class CAknNavigationDecorator :  public CCoeControl, 
                                                        public MCoeControlObserver,
                                                        public MAknNavigationDecoratorInterface
	{
public:

	enum TScrollButton 
		{
		ELeftButton =  0x0001,
		ERightButton = 0x0002
		};

    enum TControlType
        {
        ENotSpecified,
        ETabGroup,
        ENaviLabel,
        ENaviImage,
        EHintText,
        EEditorIndicator
        };

public:

    /** 
    * Creates new navigation decorator. The object takes ownership of the decorated object
    * at the beginning of the method before any leaving functions.
    *
    * @param aNavigationControlContainer container control.
    * @param aDecoratedControl control to be decorated.
    * @return Navigation decorator object that contains decorated object.
    */
	IMPORT_C static CAknNavigationDecorator* NewL(
        CAknNavigationControlContainer* aNavigationControlContainer, 
        CCoeControl* aDecoratedControl, TControlType aType = ENotSpecified);
    
    /**
    * Destructor.
    */
	IMPORT_C ~CAknNavigationDecorator();

    /**
    * Returns control inside navigation decorator object. Ownedship of the control
    * is not changed.
    *
    * @return Control that is decorated with the decorator.
    */
	IMPORT_C CCoeControl* DecoratedControl();

    /** 
    * Shows or hides navigation arrows at the both ends of the navigation pane
    * when current object is shown.
    *
    * @param aVisible boolean value if navigation arrows are shown with the decorated control.
    */
	IMPORT_C void MakeScrollButtonVisible(TBool aVisible);
    
    /** 
    * State of the visibility of navigation arrows with the object.
    *
    * @return Boolean value if navigation arrows are visible or not.
    */
	IMPORT_C TBool ScrollButtonVisible() const;
    
    /** 
    * Sets navigation arrow dimmed (and highlighted). Arrows has to be visible that the dimmed arrow
    * is shown on the screen.
    *
    * @param aButton navigation arrow to be set (ELeftButton or ERightButton)
    * @param aDimmed ETrue is the button is dimmed, EFalse if the button is set highlighted.
    */
	IMPORT_C void SetScrollButtonDimmed(TScrollButton aButton, TBool aDimmed);
    
    /**
    * Is button dimmed or highlighted.
    *
    * @param aButton navigation arrow.
    * @return ETrue if the navigation arrow is dimmed, EFalse if it is highlighted.
    */
	IMPORT_C TBool IsScrollButtonDimmed(TScrollButton aButton) const;
    
    /**
     * Set type of the decorated control.
     * @param aType type of the control.
     */
    IMPORT_C void SetControlType(TControlType aType);
    
    /**
     * Returns type of the decorated control.
     * @return control type.
     */
    IMPORT_C TControlType ControlType() const;


    void SetNaviStack(CAknNavigationControlContainer* aContainer);

protected: // from CCoeControl

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

protected: // from MCoeControlObserver

    /**
    * From MCoeControlObserver.
    * @param aControl Control that caused the event.
    * @param aEventType Type of the event.
    */
    IMPORT_C void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

private:
	IMPORT_C void ConstructL();

private:
	IMPORT_C virtual void Draw(const TRect& aRect) const;

protected:
	CCoeControl* iDecoratedControl;
	CAknNavigationControlContainer* iContainer;

private:
	TBool iNaviArrowsVisible;
	TBool iNaviArrowLeftDimmed;
	TBool iNaviArrowRightDimmed;
    TControlType iControlType;
        
    TPoint iArrowLeftPos;
    TSize iArrowLeftSize;
    TPoint iArrowRightPos;
    TSize iArrowRightSize;
	};

#endif // AKNNAVIDE_H
