/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 1999
 *
 * Program          :   EXCELCOMM.DLL
 *
 * Identification   :   CFontFormat class
 *
 * SDS Ref          :   [EXCEL_SDS]
 *
 * Filename         :   $Header: F:\\CVS/connectivity_mrouter/connmiscplug-ins/ConArc_Plugins/SheetcnvCommon/ewcofont.h,v 1.3 2001/12/04 14:06:43 BijalShah Exp $
 *
 * Author           :   Stefania Alborghetti
 *
 * History          :   
 *
 * $Log: ewcofont.h,v $
 * Revision 1.3  2001/12/04 14:06:43  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.8  2000/03/20 16:27:09  stefania
 * OR 235: Now font names are processed by fontconv.dll
 *
 * Revision 1.7  1999/10/22 09:00:14  stefania
 * Changed names of WriteFONTRecord*.
 *
 * Revision 1.6  1999-10-15 16:58:22+01  stefania
 * Removed EFontType, not needed after all.
 *
 * Revision 1.5  1999-10-15 16:48:01+01  stefania
 * Added CFontFormat::EFontType.
 *
 * Revision 1.4  1999/10/15 12:18:00  stefania
 * Changed return of Write functions from TInt to void.
 *
 * Revision 1.3  1999/10/14 10:32:43  stefania
 * Added CColorPalette.
 *
 * Revision 1.2  1999/10/05 15:24:09  stefania
 * Added CWriteBiffFactory and iBiffFactory.
 *
 * Revision 1.1  1999-10-01 09:26:11+01  stefania
 * Initial revision
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__EWCO_FONT_H__)
#define __EWCO_FONT_H__

#include "ewcohash.h"
#include <e32base.h>
#include <e32std.h> 

#include "excoepoc.h"

class CPalette;
class CCharFormatLayer;
class CWriteBiffFactory;
class CFontConverter;
class CWriteBiffFONT;

//
//Color palette
//
class CColorPalette : public CBase
{
public:
    //Construction, Destruction
    IMPORT_C static CColorPalette* NewL( const CWriteBiffFactory* aBiffFactory );
    IMPORT_C ~CColorPalette( ) { DELETE( iPalette ); }
public:
    //Interface
    IMPORT_C void WriteBIFFPalette(const COle2StreamPackage* aStream) const;
    IMPORT_C TInt PaletteIndex( TRgb& aRgb ) const;
private:
    //Construction
    void ConstructL( );
    CColorPalette( const CWriteBiffFactory* aBiffFactory ) { iBiffFactory = aBiffFactory; }
private:
    //Data
    const CWriteBiffFactory* iBiffFactory;  //Factory of BIFF records
    CPalette*                iPalette;      //Color palette
};


//Implement algorithm for converting from EPOC
//font format to Excel font format
class CFontFormat : public CBase
{
public:
    //first index of non default font records
    static const TInt16 KFirstFontIndex;
public:
    //Construction, Destruction
    static CFontFormat* NewL(  const CWriteBiffFactory* aBiffFactory, CColorPalette* aPalette, RFs& aFs );
    static CFontFormat* NewLC( const CWriteBiffFactory* aBiffFactory, CColorPalette* aPalette, RFs& aFs );
    ~CFontFormat( );
public:
    //Interface
    void    WriteFONTRecordsL( const CCharFormatLayer* aCharFormatLayer,
                                    const COle2StreamPackage* aStream );
    TInt16  AddFONTRecordL( const CCharFormatLayer* aCharFormatLayer,
                                    const COle2StreamPackage* aStream );
private:
    //Construction
    CFontFormat(const CWriteBiffFactory* aBiffFactory, CColorPalette* aPalette, RFs& aFs ) 
    { iBiffFactory = aBiffFactory; iPalette = aPalette; iFs = aFs; }
    void ConstructL( ); 
private:
    const CWriteBiffFactory*         iBiffFactory;   //Factory of BIFF records
    CColorPalette*                   iPalette;       //Color palette
    CArrayFixSeg<CWriteBiffFONT*>*   iRecords;       //list of font records 
    CFontConverter*                  iFontConverter; //Font converter, OR 235
    RFs                              iFs;            //File server
};

#endif //__EWCO_FONT_H__