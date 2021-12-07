// Copyright c 2000, Nokia. All rights reserved.

#ifndef __SOUNDVIEW_H__
#define __SOUNDVIEW_H__

#include <coecntrl.h>
#include <coeccntx.h>

class CEikLabel;
class CSoundDocument;

/** An instance of CSoundView is the application view object. */

class CSoundView : public CCoeControl, public MCoeControlBrushContext
    {
public:
    /** @semantics Perform the second phase of two phase construction.*/
    void ConstructL();

    /** @stereotype destructor
     * @semantics Destroy the object.*/
    ~CSoundView();

    /** @semantics Display a string identifying the current audio utility */
    void NotifyStatusL(const TDesC& aMessage);

    /** @semantics Draw the view */
    void Draw(const TRect& /*aRect*/) const;

protected:
    /** @semantics Count the number of component controls that the application 
     * view owns.*/
    TInt CountComponentControls() const;

    /** @semantics Return a pointer to the 'aIndex'th component control.*/
    CCoeControl* ComponentControl(TInt aIndex) const;

    /** @semantics Respond to size changed.*/
    void SizeChanged(); 

protected:
    __DECLARE_TEST; // for invariant checking

private:

    /** The label for displaying the current sound utility identifier. */
    CEikLabel* iLabel;
    };

#endif // __SOUNDVIEW_H__

