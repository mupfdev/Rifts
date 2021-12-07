/*
* ============================================================================
*  Name     : AknProgressTimer.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AknProgressTimer.h: interface for the CAknProgressTimer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AKNPROGRESSTIMER__
#define __AKNPROGRESSTIMER__

#include <e32base.h>

struct TTimerModel
  {
  TInt iFinalValue;
  TInt iHundreths;
  TInt iIncrement;
  TBool iRunning;
  };
class CAknNoteControl;

class CAknProgressTimer : public CTimer  
  {
 public:
	CAknProgressTimer();
	virtual ~CAknProgressTimer();
  void ConstructL(TTimerModel* aModel,CAknNoteControl* aContainer,TCallBack aCallBack);
  void AdjustRunningState();
private:
  void Queue();
  void RunL();
private:
  TTimerModel* iModel;
  CAknNoteControl* iContainer;
  TCallBack iCallBack;
  };

#endif 
