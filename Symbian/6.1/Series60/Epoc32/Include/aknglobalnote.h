/*
* ============================================================================
*  Name     : AknGlobalNote.h
*  Part of  : Avkon
*
*  Description:
*     
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef __AKNGLOBALNOTENOTIFY_H__
#define __AKNGLOBALNOTENOTIFY_H__

#include <AknNotify.h>
#include <aknnotifystd.h>


class CAknGlobalNote : public CAknNotifyBase
  {
public:	
	IMPORT_C static CAknGlobalNote* NewL();
	IMPORT_C static CAknGlobalNote* NewLC();
	IMPORT_C ~CAknGlobalNote(); 
	IMPORT_C TInt ShowNoteL(TAknGlobalNoteType aType,const TDesC& aNoteText);
	IMPORT_C TInt ShowNoteL(TRequestStatus& aStatus, TAknGlobalNoteType aType,const TDesC& aNoteText);
	IMPORT_C void CancelNoteL(TInt aNoteId);
	IMPORT_C void SetPriority(TInt aPriority);
	IMPORT_C void SetSoftkeys(TInt aId);
	IMPORT_C void SetGraphic(TInt aId, TInt aMaskId=-1);
	IMPORT_C void SetAnimation(TInt aResourceId);
	IMPORT_C void SetTone(TInt aTone);	// must be specified in avkon.hrh
private:
	CAknGlobalNote();
	void ConstructL();    
	void PrepareBufferL(TAknGlobalNoteType aType,const TDesC& aNoteText);
private:
	IMPORT_C void CAknNotifyBase_Reserved();
private:
	TInt iPriority;
	TInt iSoftkeys;
	TInt iGraphic;
	TInt iGraphicMask;
	TInt iAnimation;
	TInt iTone;
	CBufFlat *iBuffer;
	TPtrC8 iBufferPtr;
  };


#endif
