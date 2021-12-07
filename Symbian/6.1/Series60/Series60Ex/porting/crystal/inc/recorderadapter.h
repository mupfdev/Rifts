// Copyright c 2000, Nokia. All rights reserved.

#ifndef __CRECORDERADAPTER__
#define __CRECORDERADAPTER__

#include <e32std.h>


#include "audioadapter.h"

#include <MdaAudioSampleEditor.h>
#include <mda\\client\\utility.h> // for MMdaObjectStateChangeObserver

class CSoundAppUi;

/*! 
  @class CRecorderAdapter
  
  @discussion An instance of class CRecorderAdapter is an adapter object for the CMdaAudioRecorderUtility class.
  */
class CRecorderAdapter : public CBase, public MAudioAdapter, public MMdaObjectStateChangeObserver
    {
public:
/*!
  @function NewL
  
  @discussion Create a CRecorderAdapter object using two phase construction,
  and return a pointer to the created object
  @param aAppUi the User Interface
  @result pointer to new object
  */
    static CRecorderAdapter* NewL(CSoundAppUi& aAppUi);
    
/*!
  @function NewLC
  
  @discussion Create a CRecorderAdapter object using two phase construction,
  and return a pointer to the created object
  @param aAppUi the User Interface
  @result pointer to new object
  */
    static CRecorderAdapter* NewLC(CSoundAppUi& aAppUi);

/*!
  @function ~CRecorderAdapter
  
  @discussion Destroy the object and release all memory objects
  */
    ~CRecorderAdapter();

public: // from MAudioAdapter
/*!
  @function PlayL
  
  @discussion Begin playback of the audio sample. 
  */
    void PlayL();

/*!
  @function StopL
  
  @discussion Stop playback or recording of the audio sample.
              Note that this implementation of the virtual function does not leave. 
  */
    void StopL();

/*!
  @function RecordL
  
  @discussion Record using the audio utility.
  */
    void RecordL();

/*!
  @function UpdateMenuL
  
  @discussion Update the menu aMenuPane to reflect the 
              current state of the audio recorder utility.
              Note that this implementation of the virtual function does not leave. 
  @param aMenuPane the menu pane to update
  */
    void UpdateMenuL(CEikMenuPane* aMenuPane);

/** @semantics Update the application's command button area to reflect the current state of the audio utility. */
    void UpdateCBA();

/*!
  @function Identify
  
  @discussion Return an identifying string 
  @result An identification string 
  */   
    const TDesC& Identify();

public: // from MMdaObjectStateChangeObserver
/*!
  @function MoscoStateChangeEvent
  
  @discussion Handle the change of state of an audio recorder utility.
  @param aObject The audio sample object that has changed state
  @param aPreviousState The state before the change
  @aCurrentState The state after the change
  @aErrorCode if not KErrNone, that error that caused the state change
  */   
    void MoscoStateChangeEvent(CBase* aObject, TInt aPreviousState, TInt aCurrentState, TInt aErrorCode);
    
protected:
/** @semantics Check the class invariants. */
    __DECLARE_TEST; 

private:

/*!
  @function CRecorderAdapter
  
  @discussion Perform the first phase of two phase construction 
  @param aAppUi the Ui to use
  */
    CRecorderAdapter(CSoundAppUi& aAppUi);
      
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CRecorderAdapter object
  */
    void ConstructL();

private:
/** The audio recorder utility object. */
    CMdaAudioRecorderUtility* iMdaAudioRecorderUtility;

/** Reference to the application's UI object. */
    CSoundAppUi& iAppUi;
    };

#endif // __CRECORDERADAPTER__
