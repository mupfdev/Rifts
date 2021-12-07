/*
* ============================================================================
*  Name     : CAknExMenuOkContainer from CCoeControl, MCoeControlObserver
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXMNEUOKCONTAINER_H
#define AKNEXMNEUOKCONTAINER_H

// INCLUDES
#include <aknview.h>
#include <eikedwin.h>
   
// FORWARD DECLARATIONS
class CAknExMenuOkView;

// CLASS DECLARATION

/**
*  CAknExMenuOkContainer  container control class.
*  
*/
class CAknExMenuOkContainer : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        
        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        * @param aParent Pointer of parent view for container.
        */
        void ConstructL(const TRect& aRect, CAknExMenuOkView* aParent);

        /**
        * Destructor.
        */
        virtual ~CAknExMenuOkContainer();

    public: // New functions

    public: // Functions from base classes

    private: // Functions from base classes CoeControl

       /**
        * From CoeControl,SizeChanged.
        */
        void SizeChanged();

       /**
        * From CoeControl,CountComponentControls.
        * @return Nbr of controls inside this container.
        */
        TInt CountComponentControls() const;

       /**
        * From CCoeControl,ComponentControl.
        * @param Index number of the control.
        * @return Pointer of controls inside this container.
        */
        CCoeControl* ComponentControl(TInt aIndex) const;

        /**
         * From CCoeControl, Handles key event.
         * @param aKeyEvent The key event.
         * @param aType The type of the event.
         * @return Indicates whether or not the key event was
         *           used by this control.
         */
         TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                    TEventCode aType);

       /**
        * From CCoeControl,Draw.
        * @param Specified area for drawing
        */
        void Draw( const TRect& aRect ) const;

    private: // Functions from base classes MCoeControlObserver
        /**
        * From MCoeControlObserver Handles an event of type aEventType
        * @param aControl Pointer to component control
        * @param aEventType Event code
        */
        // event handling section
        // e.g Listbox events
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        
    private: //data
        CEikEdwin*      iUpperText;
        CEikEdwin*      iLowerText;

        // pointer to the view
        CAknExMenuOkView*    iParent;
    };

#endif    // AKNEXMNEUOKCONTAINER_H

// End of File
