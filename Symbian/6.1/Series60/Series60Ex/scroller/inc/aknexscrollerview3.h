/*
* ============================================================================
*  Name     : CAknExScrollerView3 from CAknView
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSCROLLERVIEW3_H
#define AKNEXSCROLLERVIEW3_H

// INCLUDES
#include <aknview.h>
#include <aknform.h>

// FORWARD DECLARATIONS
class CAknExScrollerContainer3;


// CONSTANTS
// UID of view
const TUid KViewId3 = {3};

// CLASS DECLARATION

class CAknExScrollerView3Form : public CAknForm
    {
    public:  // Constructor and destructor  
        /**
        * Two-phased constructor.
        */
        static CAknExScrollerView3Form* NewL();

        /**
        * Destructor.
        */
        virtual ~CAknExScrollerView3Form();

    public :
        // From MEikMenuObserver
        void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane ) ;

    private:  // Constructor
        /**
        * Default constructor.
        */
        CAknExScrollerView3Form();

        /**
        * Second-phase constructor.
        */
        void ConstructL();
    
    private:  // New functons
        /**
        * Set form data.
        */
        void SetFormData();
    
    private:  // Functions from base class
        /**
        * From CEikDialog 
        * Set default field value to member data.
        */
        void PostLayoutDynInitL();

        /**
        * From CAknForm 
        * Show save query. If user answers "No" to this query.
        * return field value to the value which is before editing.
        */
        TBool QuerySaveChangesL();

    private:
        TBuf<EAknExScrollerInt256> iEdwinData1;
        TInt                       iNumberData;
        TBuf<EAknExScrollerInt256> iEdwinData2;
        TBuf<EAknExScrollerInt256> iEdwinData3;
        TBuf<EAknExScrollerInt256> iEdwinData4;
        TBuf<EAknExScrollerInt256> iEdwinData5;
        TBuf<EAknExScrollerInt256> iEdwinData6;
        TBuf<EAknExScrollerInt256> iEdwinData7;
        TBuf<EAknExScrollerInt256> iEdwinData8;
        TBuf<EAknExScrollerInt256> iEdwinData9;
        TBuf<EAknExScrollerInt256> iEdwinData10;
        TBuf<EAknExScrollerInt256> iEdwinData11;
        TBuf<EAknExScrollerInt256> iEdwinData12;
        TBuf<EAknExScrollerInt256> iEdwinData13;
        TBuf<EAknExScrollerInt256> iEdwinData14;
        TBuf<EAknExScrollerInt256> iEdwinData15;
        TBuf<EAknExScrollerInt256> iEdwinData16;

    };

/**
*  CAknExScrollerView3 view class.
* 
*/
class CAknExScrollerView3 : public CAknView
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExScrollerView3();

        /**
        * EPOC default constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExScrollerView3();


    public: // From CAknView
        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */
        TUid Id() const;

        /**
        * From CAknView, HandleCommandL.
        * handles the commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );


    private:
        /**
        * From CAknView, DoActivateL.
        * Creates the Container class object.
        * @param aPrevViewId aPrevViewId is not used.
        * @param aCustomMessageId aCustomMessageId is not used.
        * @param aCustomMessage aCustomMessage is not used.
        */
        void DoActivateL( const TVwsViewId& aPrevViewId,
                          TUid aCustomMessageId,
                          const TDesC8& aCustomMessage );

        /**
        * From CAknView, DoDeactivate.
        * Deletes the Container class object.
        */
        void DoDeactivate();


    private: // Data
        CAknExScrollerContainer3* iContainer;  // Component container
        CAknExScrollerView3Form*  iForm;       // Form

    };

#endif // AKNEXSCROLLERVIEW3_H

// End of File
