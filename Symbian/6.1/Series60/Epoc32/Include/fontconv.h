/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 2000
 *
 * Program          :   Font Converters
 *
 * Identification   :   Classes as described in DTN 301.056.001
 *
 * SDS Ref          :   DTN 301.056.001
 *
 * Filename         :   $Locker:  $, $Revision: 1.3 $
 *
 * Author           :   Chris Goldsmith
 *
 * History          :   
 *
 * $Log: fontconv.h,v $
 * Revision 1.3  2001/12/04 14:06:41  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.8  2000/03/29 14:28:31  chrisg
 * OR 301.121.235: Updated TUint8 to TUint16 as the indexes for the word writers should be 16 bits
 *
 * Revision 1.7  2000-03-28 15:00:06+01  joyl
 * OR 235 Word Writer font index implementation
 *
 * Revision 1.6  2000-03-24 15:49:12+00  eds
 * OR : 301.121.235 : Minor mods for Word Writer.
 *
 * Revision 1.5  2000-03-24 11:42:21+00  eds
 * OR : 301.121.235 : Added prototypes and dummy code for Word Writer font conversions.
 *
 * Revision 1.4  2000/03/20 16:30:12  joyl
 * OR 235 - Font Conversion Classes - compiles but not tested
 *
 * Revision 1.3  2000-03-20 10:14:31+00  chrisg
 * Updated to use a TDesC in MSFontToEpocFont
 *
 * Revision 1.2  2000-03-20 09:26:14+00  chrisg
 * Updated to work by Ed
 *
 * Revision 1.1  2000-03-17 14:10:54+00  chrisg
 * Initial revision
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__FONTCONV_H__)
#define __FONTCONV_H__

const TInt KMaxMsTypefaceNameLength = 20;

struct TFontLookup 
{
    TFontLookup*                    next;
    TBuf<KMaxMsTypefaceNameLength>  iMSFontName; 
    TUint16                         iMSFontIndex;
    TFontSpec                       iEpocFont;
};

class CFontConverter:public CBase
{
public:    // methods
    IMPORT_C ~CFontConverter(); // destructor
    IMPORT_C TFontSpec* MSFontToEpocFont(const TDesC     &aMSFontName) const;
    IMPORT_C TDesC*     EpocFontToMSFont(const TFontSpec &aEpocFont)   const;  
    IMPORT_C TUint16    EpocFontToMSFontIndex(const TFontSpec &aEpocFont)   const;
    IMPORT_C TPtrC8     GetMSFontTable()   const;
                      

protected: // methods
    // constructor
    CFontConverter();
    void BuildTable(const TDesC     &aMSFontName,
                    const TUint16    aMSFontIndex,
                    const TFontSpec &aEpocFont);
    void ResetTable();

private:   // methods
    // copy constructor not implemented to prevent accidental use
    CFontConverter(const CFontConverter&);

protected:      // data
    TFontSpec   *iDefaultEpocFont;
    TDesC       *iDefaultMSFont;
    TUint16      iDefaultMSFontIndex;
    TPtrC8       iMSWordFontTable;

private:        // data
    TInt        iNumberOfElements;  // length of hash table
    TFontLookup *iFontElements;     // pointer to start of table
};

class C95FontConverter:public CFontConverter
{
public:    // methods
    IMPORT_C static C95FontConverter* NewL(RFs& aFs);
    IMPORT_C static C95FontConverter* NewLC(RFs& aFs);

    IMPORT_C ~C95FontConverter(); // destructor

private:   // methods
    // constructor
    C95FontConverter();
    void ConstructL();

    // copy constructor not implemented to prevent accidental use
    C95FontConverter(const CFontConverter&);

    __DECLARE_TEST;
};

class C97FontConverter:public CFontConverter
{
public:    // methods
    IMPORT_C static C97FontConverter* NewL(RFs& aFs);
    IMPORT_C static C97FontConverter* NewLC(RFs& aFs);

    IMPORT_C ~C97FontConverter(); // destructor

private:   // methods
    // constructor
    C97FontConverter();
    void ConstructL();

    // copy constructor not implemented to prevent accidental use
    C97FontConverter(const CFontConverter&);

    __DECLARE_TEST;
};

#endif // !defined (__FONTCONV_H__)
