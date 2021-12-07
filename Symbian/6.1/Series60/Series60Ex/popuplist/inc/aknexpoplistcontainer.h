/*
* ============================================================================
*  Name     : CAknExPopListContainer from CCoeControl, MCoeControlObserver
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXPOPLISTCONTAINER_H
#define AKNEXPOPLISTCONTAINER_H

// INCLUDES
#include <aknview.h>
   
// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
*  CAknExPopListContainer  container control class.
*  
*/
class CAknExPopListContainer : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        
        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        virtual ~CAknExPopListContainer();

    private: // Functions from base classes

       /**
        * From CoeControl,SizeChanged.
        */
        void SizeChanged();

       /**
        * From CoeControl,CountComponentControls.
        * Returns number of component contorls.
        * @return Number of component controls.
        */
        TInt CountComponentControls() const;

       /**
        * From CCoeControl,ComponentControl.
        * Returns control.
        * @param aIndex specifies index.
        * @return pointer to component control.
        */
        CCoeControl* ComponentControl(TInt aIndex) const;

       /**
        * From CCoeControl,Draw.
        * param specifies drawing area.
        */
        void Draw(const TRect& aRect) const;

       /**
        * From CCoeControl, HandleControlEventL
        * Handles events.
        * @param Pointer to component contorol
        * @param Event type
        */
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        
    private: //data

    };

#endif  // AKNEXPOPLISTCONTAINER_H

// End of File
