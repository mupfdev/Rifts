// AGMIEDIT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMIEDIT_H__
#define __AGMIEDIT_H__

#include "agmentry.h"
#include "agmupact.h"

class CAgnModel;


class TAgnInstanceEditor 
	{
public:
	inline void SetOwningModel(CAgnModel* aOwningModel) {iOwningModel=aOwningModel;};
	void DeleteInstanceL(CAgnEntry* aInstance,TAgnWhichInstances aWhichInstances);
	TAgnEntryId UpdateInstanceL(CAgnEntry* aInstance,TAgnWhichInstances aWhichInstances,TAgnEntryId aTodoPositionReferenceId);
private:
	void DoDeleteInstanceL(CAgnEntry* aEntry,TAgnWhichInstances aInstances);
	TAgnEntryId DoUpdateInstanceL(CAgnEntry* aEntry,TAgnWhichInstances aInstances,TAgnEntryId aTodoPositionReferenceId);
	void PruneExceptions(CAgnEntry* aInstance);
	TAgnEntryId CreateAndStoreExceptionL(CAgnEntry*& aInstance,CAgnEntry* aOriginalEntry,TAgnEntryId aTodoPositionReferenceId);
	TAgnEntryId SplitRepeatL(CAgnEntry*& aInstance,TAgnWhichInstances aWhichInstances,CAgnEntry* aOriginalEntry,TAgnEntryId aTodoPositionReferenceId);
	void DetachEntryFromStoreL(CAgnEntry* aEntry,const CStreamStore* aStore);
	inline CAgnModel* OwningModel() const { return (iOwningModel); };
private:
	CAgnModel* iOwningModel;
	};


#endif
