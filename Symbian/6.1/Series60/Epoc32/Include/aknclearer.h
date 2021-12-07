#ifndef AKNCLEARER_H
#define AKNCLEARER_H

#include <coecntrl.h>
#include <eikenv.h>

class CAknScreenClearerBase : public CCoeControl
	{
public:
	IMPORT_C void HandleStatusPaneSizeChangeL();
protected:
	IMPORT_C ~CAknScreenClearerBase();
	IMPORT_C void ConstructL(RWindowGroup& aParent, TInt aOrdinalPos, TBool aBlankAppStatusPane);
private:	// from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
private:
	void SetShapeL();
private:
	CFbsBitmap* iNaviWipe;
	TBitFlags iFlags;
	};


/**
 * This class is for use inside applications for screen blanking
 */
class CAknLocalScreenClearer : public CAknScreenClearerBase
	{
public:
	IMPORT_C static CAknLocalScreenClearer* NewLC();
	IMPORT_C static CAknLocalScreenClearer* NewLC(TBool aBlankAppStatusPane);
	IMPORT_C static CAknLocalScreenClearer* NewL(TBool aBlankAppStatusPane);
	};


#endif
