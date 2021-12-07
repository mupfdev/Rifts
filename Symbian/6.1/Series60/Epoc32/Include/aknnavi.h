/*
* ============================================================================
*  Name     : aknnavi.h
*  Part of  : AVKON
*
*  Description:
*     A default control in the status pane's navigation pane.
*
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNNAVI_H
#define AKNNAVI_H

#include <coecntrl.h>
#include <coeccntx.h>
#include <aknvolumecontrol.h>

class CAknNavigationDecorator;
class CEikStatusPaneBase;
class CFbsBitmap;
 

class MAknNavigationDecoratorInterface
    {
public:
    virtual ~MAknNavigationDecoratorInterface() { }
    virtual CCoeControl* DecoratedControl()=0;
    };

class MAknNavigationContainerInterface
    {
public:
    virtual ~MAknNavigationContainerInterface() { }
    virtual CAknNavigationDecorator* CreateMessageLabelL(const TDesC& aText)=0;
    virtual CAknNavigationDecorator* CreateTabGroupL()=0;
    virtual void PushL(CAknNavigationDecorator&)=0;
    virtual void Pop()=0;
    };


 
/**
 * A default control in the status pane's navigation pane
 */
class CAknNavigationControlContainer : public CCoeControl, 
                                        public MCoeControlContext, 
                                        public MCoeControlObserver, 
                                        public MAknNavigationContainerInterface
	{
public:
    /**
    * Constructor. This object does not own the contents of the navi pane controls stack.
    */
	IMPORT_C CAknNavigationControlContainer();
    
    /**
    * Destructor. This object does not own the contents of the navi pane controls stack.
    */
	IMPORT_C ~CAknNavigationControlContainer();

    /** 
    * 2nd phase construction.
    *
    */
	IMPORT_C void ConstructL();
    
    /** 
    * Construct from resources. Created object is owned by this object until ResourceDecorator()
    * -method is called. If the application does not fetch the object, it is deleted in destructor.
    *
    * @param aReader resource reader.
    */
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
    /** 
    * Resource constructor that returns a new object to the application.
    *
    * @param aReader resource reader.
    * @return Navigation decorator object that contains navigation pane control read from resources.
    */
	IMPORT_C CAknNavigationDecorator* ConstructNavigationDecoratorFromResourceL(TResourceReader& aReader);

    /**
    * Create and return a new navigation decorator object containing tab group. 
    * The ownership of the object is transferred to the application.
    * @return Navigation decorator object that contains tab group.
    *
    */
	IMPORT_C CAknNavigationDecorator* CreateTabGroupL();
    
    /**
    * Create from resources and return a new navigation decorator object containing tab group. 
    * The ownership of the object is transferred to the application.
    *
    * @param aReader resource reader.
    * @return Navigation decorator object that contains tab group.
    */
	IMPORT_C CAknNavigationDecorator* CreateTabGroupL(TResourceReader& aReader);
    
    /**
    * Create and return a new navigation decorator object containing navigation label. 
    * The ownership of the object is transferred to the application.
    *
    * @param aText	  label text to the navigation pane.
    * @return Navigation decorator object that contains navigation label.
    */
	IMPORT_C CAknNavigationDecorator* CreateNavigationLabelL(const TDesC& aText = KNullDesC);
    
    /**
    * Create from resources and return a new navigation decorator object containing navigation label.
    * The ownership of the object is transferred to the application.
    *
    * @param aReader resource reader.
    * @return Navigation decorator object that contains navigation label.
    */
	IMPORT_C CAknNavigationDecorator* CreateNavigationLabelL(TResourceReader& aReader);
    
    /**
    * Create and return a new navigation decorator object containing navigation image. 
    * The ownership of the returned object is transferred to the application.
    * Moves ownership of aBitmap and aMaskBitmap to the navigation decorator 
    * object at the end of the method.
    *
    * @param aBitmap  image to be shown in the navigation pane.
    * @param aMaskBitmap  mask of the image to be shown in the navigation pane.
    * @return Navigation decorator object that contains navigation image.
    */
	IMPORT_C CAknNavigationDecorator* CreateNavigationImageL(const CFbsBitmap* aBitmap = NULL, const CFbsBitmap* aMaskBitmap = NULL);
    
    /**
    * Create from resources and return a new navigation decorator object containing navigation image.
    * The ownership of the returned object is transferred to the application.
    *
    * @param aReader resource reader.
    * @return Navigation decorator object that contains navigation image.
    */
	IMPORT_C CAknNavigationDecorator* CreateNavigationImageL(TResourceReader& aReader);
    
    /**
    * Create and return a new navigation decorator object containing help text. 
    * The ownership of the object is transferred to the application.
    *
    * @param aText	  help text label to be shown in the navigation pane.
    * @return Navigation decorator object that contains message label (=hint text).
    */
	IMPORT_C CAknNavigationDecorator* CreateMessageLabelL(const TDesC& aText = KNullDesC);
    
    /**
    * Create from resources and return a new navigation decorator object containing help text. 
    * The ownership of the object is transferred to the application.
    *
    * @param aReader resource reader.
    * @return Navigation decorator object that contains message label (=hint text).
    */
	IMPORT_C CAknNavigationDecorator* CreateMessageLabelL(TResourceReader& aReader);
    
    /**
    * Create volume control indicator to the navi pane. 
    * The ownership of the object is transferred to the application.
    *
    * @param aResourceId  resource file id for the volume control
    * @return Navigation decorator object that contains volume indicator.
    */
   	IMPORT_C CAknNavigationDecorator* CreateVolumeIndicatorL(TInt aResourceId);

    /**
    * Create editor indicator container control to the navi pane. 
    * The ownership of the object is transferred to the application.
    *
    * @return Navigation decorator object that contains editor indicator container.
    */
   	IMPORT_C CAknNavigationDecorator* CreateEditorIndicatorContainerL();

    /**
    * Push default content (empty navigation pane) to the navigation pane's object stack.
    * This operation also draws default content to the navigation pane.
    *
    * @param aAllowDuplicates If this is true, duplicate default navi pane 
    * contents are allowed.
    */
	IMPORT_C void PushDefaultL( TBool aAllowDuplicates = EFalse );

    /**
    * Push a navigation decorator object to the navigation pane's object stack.
    * This operation also draws the control to the navigation pane. An object
    * can be on the stack only once. If the object already exists in the stack
    * it is moved to topmost object. Ownership is not transfered.
    * Editor indicator control has priority over others. It is always at the 
    * top if it exists. In this case all other controls are pushed under
    * the editor indicator object.
    *
    * @param aNaviPaneControl	object to be added at the top of the stack.
    */
	IMPORT_C void PushL(CAknNavigationDecorator& aNaviPaneControl);
    
    /**
    * Pop topmost object from the navigation pane's object stack. If editor 
    * indicator control is topmost, it is not popped. The next control
    * is popped instead.
    * It is not possible to pop editor indicator object with this method.
    * Use Pop(CAknNavigationDecorator* aControl) or delete(aControl) instead
    * if editor indicator control is needed to be popped.
    *
    */
	IMPORT_C void Pop();
    
    /**
    * Pop (remove) certain object from the navigation pane's object stack.
    * The removed object does not need to be topmost.
    *
    * @param aControl	object to be removed from the stack.
    */
	IMPORT_C void Pop(CAknNavigationDecorator* aControl);
    
    /**
    * Return topmost object from navigation pane's object stack.
    * Editor indicator object is transparent for this operation. If editor indicators
    * exist on the navi pane, next object on the stack is returned.
    *
    * @return Navigation decorator object that is topmost in navigation pane's object stack.
    */
	IMPORT_C CAknNavigationDecorator* Top();
    
    /**
    * Replaces existing navigation decorator object in the navigation pane's object stack.
    * Any object can be on the stack only once. If the replacement object already exists 
    * in the stack, previous copy is removed from the stack. Ownership is not transfered.
    * Navi pane is redrawn if top item is changed.
    *
    * @param aToBeReplaced	an object to be replaced.
    * @param aReplacement	an object that is put to the stack instead.
    * @return error number. KErrNone if the operation succeeds. KErrNotFound if 
    * 'aToBeReplaced' object cannot be found from the stack.
    */
   	IMPORT_C TInt ReplaceL(CAknNavigationDecorator& aToBeReplaced, 
                                              CAknNavigationDecorator& aReplacement);
    
    /** 
    * Return the object constructed from resources with ConstrucFromResourcesL() -method to
    * the application. Ownership of the object is transferred to the application.
    *
    * @return Navigation decorator object that was created from resources.
    */
    IMPORT_C CAknNavigationDecorator* ResourceDecorator();

    /**
    *  This non-exported method returns reference to navi arrow bitmaps.
    *
    * @param aId Id of the bitmap.
    * @return Reference to the navi arrow bitmap.
    */
    CFbsBitmap& NaviArrowBitmap(TInt aId);

public:
    /**
    * Static method to return current color scheme.
    * @return Current color scheme value.
    */
    IMPORT_C static TInt ColorScheme();

protected: // from CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
	 * Handles a change to the control's resources of type aType
	 * which are shared across the environment, e.g. color scheme change.
	 * @param aType Event type.
	 */
    IMPORT_C virtual void HandleResourceChange(TInt aType);

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

private: // from CCoeControl
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	
private:
	CEikStatusPaneBase* iStatusPane;

    CAknNavigationDecorator* iNaviDecoratorFromResource;

	typedef CArrayPtrFlat<CAknNavigationDecorator> CAknNaviPaneStack;
	CAknNaviPaneStack* iNaviPaneControls;

    CFbsBitmap* iNaviArrowBitmap[4];

  	CFbsBitmap* iNaviWipeBitmap;
    TInt iCurrentColorScheme;
	};


#endif // AKNNAVI_H
