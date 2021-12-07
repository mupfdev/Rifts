/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __MULTIVIEWS_VIEW2_H__
#define __MULTIVIEWS_VIEW2_H__


#include <aknview.h>

class CMultiViewsContainer2;

/*! 
  @class CMultiViewsView2
  
  @discussion An instance of the Application View object for the MultiViews 
  example application
*/
class CMultiViewsView2: public CAknView
    {
public:

/*!
  @function NewL
   
  @discussion Create a CMultiViewsView2 object
  @result a pointer to the created instance of CMultiViewsView2
*/
    static CMultiViewsView2* NewL();

/*!
  @function NewLC
   
  @discussion Create a CMultiViewsView2 object
  @result a pointer to the created instance of CMultiViewsView2
*/
    static CMultiViewsView2* NewLC();


/*!
  @function ~CMultiViewsView2
  
  @discussion Destroy the object and release all memory objects
*/
    ~CMultiViewsView2();


public: // from CAknView

/*!
  @function Id
  
  @discussion Identity of this view to the system
  @result the ID of view
*/
    TUid Id() const;

/*!
  @function HandleCommandL
  
  @discussion Handles the commands
  @param aCommand Command to be handled
*/
    void HandleCommandL(TInt aCommand);

/*!
  @function DoActivateL
  
  @discussion Create the Container class object
  @param aPrevViewId The id of the previous view
  @param aCustomMessageId message identifier
  @param aCustomMessage custom message provided when the view is changed
*/
  void DoActivateL(const TVwsViewId& aPrevViewId,
                   TUid aCustomMessageId,
                   const TDesC8& aCustomMessage);

/*!
  @function DoDeactivate
  
  @discussion Remove the container class instance from the App UI's stack and
  deletes the instance
*/
  void DoDeactivate();

private:

/*!
  @function CMultiViewsView2
  
  @discussion Perform the first phase of two phase construction 
*/
    CMultiViewsView2();

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CMultiViewsView2 object
*/
    void ConstructL();

private:

    /*! @var iContainer container for this view */
    CMultiViewsContainer2* iContainer;

    /*! @var iIdentifier identifier for this view */
    TUid iIdentifier;
    };


#endif // __MULTIVIEWS_VIEW2_H__
