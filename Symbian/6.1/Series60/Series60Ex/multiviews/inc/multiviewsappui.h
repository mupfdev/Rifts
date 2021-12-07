/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __MULTIVIEWS_APPUI_H__
#define __MULTIVIEWS_APPUI_H__

#include <aknViewAppUi.h>

class CMultiViewsView1;
class CMultiViewsView2;

/*! 
  @class CMultiViewsAppUi
  
  @discussion An instance of class CMultiViewsAppUi is the UserInterface part of the AVKON
  application framework for the MultiViews example application
  */
class CMultiViewsAppUi : public CAknViewAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CMultiViewsAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
/*! @var iAppView1 The application view 1 */
    CMultiViewsView1* iAppView1;

/*! @var iAppView2 The application view 2 */
    CMultiViewsView2* iAppView2;
    };


#endif // __MULTIVIEWS_APPUI_H__

