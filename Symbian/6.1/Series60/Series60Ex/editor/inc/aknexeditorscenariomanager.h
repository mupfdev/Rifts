/*
* ============================================================================
*  Name     : CAknExEditorScenarioManager from AknExEditorScenarioManager.h
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXEDITORSCENARIOMANAGER_H
#define AKNEXEDITORSCENARIOMANAGER_H

// CONSTANTS
const TInt KScenarioNotFound    = -1;
const TInt KTitleBufLength      = 64;

// FORWARD DECLARATIONS
class TUid;

// CLASS DECLARATION

/**
*  CAknExEditorScenarioManager
*
*/
class CAknExEditorScenarioManager
    {
    public:  // Constructors and destructor
        
        /**
        * C++ default constructor.
        */
        CAknExEditorScenarioManager();

        /**
        * Two-phased constructor.
        */
        static CAknExEditorScenarioManager* NewL();
        
        /**
        * Destructor.
        */
        virtual ~CAknExEditorScenarioManager();

    public: // New functions
        
        /**
        * Get next view to specified view.
        * @param aUid Uid of the view.
        * @return Returns UID of the next view to specified view.
        */
        TUid NextViewTo(TUid aUid);

        /**
        * Get previous view to specified view.
        * @param aUid Uid of the view.
        * @return Returns UID of the previous view to specified view.
        */
        TUid PrevViewTo(TUid aUid);

        /**
        * Get UID of the view in first scenario.
        * @return Returns UID of the view.
        */
        TUid FirstViewId();

        /**
        * Get UID of the view in last scenario.
        * @return Returns UID of the view.
        */
        TUid LastViewId();

        /**
        * Get title of specified view.
        * @param aUid Uid of the view.(input)
        * @param aTitle Title of the view.(output)
        */
        void GetTitle(TUid aUid, TBuf<64>* aTitle);


    private:

        /**
        * By default EPOC constructor is private.
        */
        void ConstructL();

    private:
        TInt    iScenario[100]; // data
        TInt    iScenarioCount; // count of scenario
    };

#endif      // AKNEXEDITORSCENARIOMANAGER_H
            
// End of File
