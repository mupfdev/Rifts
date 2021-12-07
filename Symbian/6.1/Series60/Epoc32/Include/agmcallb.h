// AGMCALLB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMCALLB_H__
#define __AGMCALLB_H__

#include "agmmodel.h"

class  MAgnModelStateCallBack
//
// Interface specifying callback from the model indicating its state
//
	{
public: 
	virtual void StateCallBack(CAgnEntryModel::TState aState) = 0;
	};


class MAgnProgressCallBack
//
// Interface specifying the callbacks from the model during lenghthy actions
//
	{
public:
	virtual void Progress(TInt aPercentageCompleted) = 0;
	virtual void Completed(TInt aError = KErrNone) = 0;
	};

#endif

