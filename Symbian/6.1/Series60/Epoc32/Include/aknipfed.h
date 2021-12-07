// AKNIPFED.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNIPFED_H_)
#define __AKNIPFED_H_

#include <eikmfne.h>

class TInetAddr;
/**
 * The CAknIpFieldEditor class implements an edior for an IP address.
 * Based on Crystal CCknIpFieldEditor
 *
 */
class CAknIpFieldEditor : public CEikMfne 
    {
public: // public constructors
	IMPORT_C CAknIpFieldEditor();
	void ConstructL(TInetAddr& aMinimumAddress,
                    TInetAddr& aMaximumAddress,
                    TInetAddr& aInitialAddress,
                    const TInt aFlags=0);

	IMPORT_C static CAknIpFieldEditor* NewL(TInetAddr& aMinimumAddress,
                                            TInetAddr& aMaximumAddress,
                                            TInetAddr& aInitialAddress);
	IMPORT_C static CAknIpFieldEditor* NewL();
public: // Methods for getting and setting values
	IMPORT_C void SetAddress(const TInetAddr& aAddress);
	IMPORT_C TInetAddr Address() const;
	IMPORT_C virtual void SetMinimumAndMaximum(const TInetAddr& aMinimumAddress,
                                               const TInetAddr& aMaximumAddress); // only values inside the initial minimum and maximum are permitted
	IMPORT_C virtual void GetMinimumAndMaximum(TInetAddr& aMinimumAddress,
                                               TInetAddr& aMaximumAddress) const;
	IMPORT_C TInetAddr ReadIPAddress(TResourceReader& aResourceReader);
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
private: 
   void SplitAddressIntoFields(
                                const TInetAddr& aAddress,
                                TUint8 &aFieldA,
                                TUint8 &aFieldB,
                                TUint8 &aFieldC,
                                TUint8 &aFieldD) const;
	IMPORT_C virtual void CEikMfne_Reserved();

private:
    TInt iSpare;
    TInt iSpare2;
	};


#endif
