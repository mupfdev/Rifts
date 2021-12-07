/*
* ============================================================================
*  Name     : AknPopupHeadingPane.h
*  Part of  : Avkon
*
*  Description:
*   Heading pane
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNPOPUPHEADINGPANE_H
#define AKNPOPUPHEADINGPANE_H


#include <coecntrl.h>
#include <eikbtgpc.h>
#include <aknutils.h>


#include <aknappui.h>
#include <aknpopup.h>
#include <gulicon.h>


class CAknTextControl;
class CEikImage;
class CAknBitmapAnimation;

/**
 * Header control for queries
 */
class CAknPopupHeadingPane : public CCoeControl
{
    public:
        /**
        * Enumeration for different layouts
        */
        enum THeadingPaneLayout
            {
            EQueryHeadingPane,
            EListHeadingPane
            };


    public:
		IMPORT_C CAknPopupHeadingPane();
        IMPORT_C ~CAknPopupHeadingPane();
        IMPORT_C void SizeChanged();
        IMPORT_C TSize MinimumSize();
        IMPORT_C void ConstructL(TPtrC aText);
        IMPORT_C void ConstructFromResourceL(TResourceReader &aReader);

        IMPORT_C CEikLabel *Prompt() const;

        IMPORT_C void SetTextL(TPtrC aText);
        IMPORT_C void SetHeaderImageL(CEikImage *aImage);
        IMPORT_C void SetHeaderAnimationL(TInt aResourceId);		
        IMPORT_C void SetLayout( THeadingPaneLayout aLayout );

        IMPORT_C void StartAnimationL();
        IMPORT_C TInt CancelAnimation();

    public: // From CCoeControl
        virtual void ActivateL();

    private:
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt anIndex) const;
        IMPORT_C virtual void Draw(const TRect& aRect) const;

		void DoSetPromptL();
		void LayoutQueryHeadingPane();
		void LayoutListHeadingPane();
	
	private:
        TAknLayoutRect     iLayoutLine;
        TAknLayoutRect     iLayoutHeading;
        CAknTextControl*   iPrompt;
        CEikImage*         iHeaderImage;
        CAknBitmapAnimation* iAnimation;
        TInt               iHeadingLayoutRef;
        THeadingPaneLayout iLayout;
};

#endif

