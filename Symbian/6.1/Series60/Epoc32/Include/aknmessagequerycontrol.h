/*
* ============================================================================
*  Name     : aknmessagequerycontrol.h
*  Part of  : AVKON
*
*  Description:
*  Interface to control to implement message queries, 
*  to be contained within CAknMessageQueryDialog
* 
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNMESSAGEQUERYCONTROL_H
#define AKNMESSAGEQUERYCONTROL_H

#include <coecntrl.h>
#include <aknutils.h>

class CEikEdwin;
class CEikScrollBarFrame;

class CAknMessageQueryControl : public CCoeControl
	{
public: 
	CAknMessageQueryControl();
	~CAknMessageQueryControl();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    void SetMessageTextL(TDesC* aMessage);

    inline TInt Lines() const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode);

public:  // from CCoeControl
    TSize MinimumSize();
  	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt anIndex) const;
    void SizeChanged();
    virtual void ActivateL();

private:
	void CalculateNumberOfScreens();
    void UpdateScrollIndicatorL();

private:
    CEikEdwin* iEdwin;
    TInt iNumberOfLines;
    TInt iCurrentScreen;
    TInt iNumberOfScreens;

    CEikScrollBarFrame* iSBFrame;
    TInt iSpare;   // Not in use.
	};

inline TInt CAknMessageQueryControl::Lines() const
    {
    return iNumberOfLines;
    }

#endif // AKNMESSAGEQUERYCONTROL_H

// End of file
