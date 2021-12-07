/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 19999
 *
 * Program          :   Common Include File for System
 *
 * Identification   :   Global Types, and defines for the File Converters
 *                      Project
 *
 * SDS Ref          :   [ADS]
 *
 * Filename         :   $Revision: 1.3 $
 *
 * Author           :   Chris Goldsmith
 *
 * History          :   
 *
 * $Log: cosyincs.h,v $
 * Revision 1.3  2001/12/04 14:06:41  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.38  2000/03/29 13:40:22  stefania
 * OR 237 - added KExcelUnicodeConversionFailed
 *
 * Revision 1.37  2000/03/20 16:57:08  joyl
 * OR 235 - Font Converters - Error Code
 *
 * Revision 1.36  2000-03-17 13:49:57+00  eds
 * 320.121.237 : Character Set Conversion using EPOC OS Dll.
 *
 * Revision 1.35  2000-02-02 14:03:31+00  ghousk
 * Added KWordComplexFile, OR 215
 *
 * Revision 1.34  1999/12/14 17:39:55  ghousk
 * Added constant KWordInvalidPassword
 *
 * Revision 1.33  1999-11-16 16:48:51+00  eds
 * Further Word Reader changes for char/para formatting.
 *
 * Revision 1.32  1999-11-15 13:16:53+00  eds
 * Word Reader changes for char/para formatting.
 *
 * Revision 1.31  1999-11-01 10:02:40+00  peterm
 * Add skip BOF reply message
 *
 * Revision 1.30  1999-10-25 20:25:45+01  peterm
 * Add shared formula code not working yet
 *
 * Revision 1.29  1999/10/19 16:05:25  peterm
 * Added KExcelDocumentProtected
 *
 * Revision 1.28  1999-10-19 11:39:17+01  stefania
 * Added KExcelInvalidPassword
 *
 * Revision 1.27  1999-10-18 18:31:51+01  peterm
 * add KErrInvalidRecord to Excel error messages
 *
 * Revision 1.26  1999-10-11 17:03:59+01  eds
 * Added password protection.
 *
 * Revision 1.25  1999/10/04 10:27:31  eds
 * Character counting moved from library to document classes.
 *
 * Revision 1.24  1999/09/30 12:54:50  eds
 * Control of Reader/Writer direction added.
 *
 * Revision 1.23  1999/09/24 16:00:04  peterm
 * Recover from RCS crash
 *
 * Revision 1.22  1999-09-24 13:33:45+01  conorm
 * Word error added
 *
 * Revision 1.21  1999-09-21 15:41:30+01  conorm
 * Word error added
 *
 * Revision 1.20  1999-09-17 14:33:59+01  chrisg
 * Added KOle2ErrTooManyPropertySets
 *
 * Revision 1.19  1999-09-14 15:33:07+01  stefania
 * Added KExcelNotSupported
 *
 * Revision 1.18  1999-09-14 15:02:01+01  chrisg
 * Updated to include new error codes for OLE2
 *
 * Revision 1.17  1999-09-07 13:13:51+01  stefania
 * Added a few more Excel error.
 *
 * Revision 1.16  1999-09-03 16:59:27+01  eds
 * Added more Word errors.
 *
 * Revision 1.15  1999-09-03 15:55:23+01  stefania
 * Added  KExcelNoCell
 *
 * Revision 1.14  1999-09-03 15:42:31+01  stefania
 * Added from KExcelLastCellReached to  KExcelInvalidSheetNumber.
 *
 * Revision 1.13  1999-09-03 14:24:21+01  eds
 * Added more Word errors.
 *
 * Revision 1.12  1999-09-02 16:09:44+01  stefania
 * typo
 *
 * Revision 1.11  1999-09-02 16:03:15+01  stefania
 * Added KOle2ErrEndOfStream
 *
 * Revision 1.10  1999-09-02 15:57:43+01  conorm
 * KWordNotSupported added
 *
 * Revision 1.9  1999-09-02 11:08:22+01  stefania
 * Added KOle2InvalidParameter
 *
 * Revision 1.8  1999-09-01 15:56:15+01  peterm
 * Add Error code 3
 *
 * Revision 1.7  1999-09-01 14:12:02+01  chrisg
 * Fixed double carriage returns (again!)
 *
 * Revision 1.6  1999/09/01 13:08:27  chrisg
 * Fixed DOS/UNIX problem
 *
 * Revision 1.5  1999/09/01 11:08:46  chrisg
 * Added Excel Error codes
 *
 * Revision 1.4  1999-09-01 11:54:23+01  conorm
 * Word Error code added
 *
 * Revision 1.3  1999-08-27 15:23:40+01  eds
 * Completed Ole2 component testing.
 *
 * Revision 1.2  1999-08-20 17:31:59+01  eds
 * Added trace class.
 *
 * Revision 1.1  1999-08-18 10:39:33+01  chrisg
 * Initial revision
 *
 * Revision 1.2  1999-08-17 12:02:20+01  chrisg
 * Updated for new partitioning of property set and root chain functionality
 *
 * Revision 1.1  1999-08-16 17:22:47+01  chrisg
 * Initial revision
 *
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__COSYINCS_H__)
#define __COSYINCS_H__

// A few useful macros
#define MAX(x,y)      ((x)<(y))?(y):(x)
#define MIN(x,y)      ((x)<(y))?(x):(y)

#define DELETE(x)     { delete (x); (x)=0; }

#define ERROR_BASE    +600		// PFD|SYMBIAN: Have reversed sign of errors as custom errors should be positive.

IMPORT_C  const TInt TranslateCnvErrToEpocErr(TInt ConverterError);  // PFD|SYMBIAN: Utility function to map to standard Epoc error codes at entry point.

// Ole2 Error Codes - PLEASE NOTE THAT THESE REPLACE the
//                    TError type in early versions of the ADS

#define OLE_ERROR_BASE (ERROR_BASE)

const TInt KOle2InvalidChainError      = OLE_ERROR_BASE + 1;
const TInt KOle2FileOpenError          = OLE_ERROR_BASE + 2;
const TInt KOle2FileError              = OLE_ERROR_BASE + 3;
const TInt KOle2InvalidBlock           = OLE_ERROR_BASE + 4;
const TInt KOle2NoBigBlockDepot        = OLE_ERROR_BASE + 5;
const TInt KOle2InvalidRead            = OLE_ERROR_BASE + 6;
const TInt KOle2ErrInvalidPsError      = OLE_ERROR_BASE + 7;
const TInt KOle2FileCorrupt            = OLE_ERROR_BASE + 8;
const TInt KOle2LastStreamError        = OLE_ERROR_BASE + 9;
const TInt KOle2FirstStreamError       = OLE_ERROR_BASE + 10;
const TInt KOle2NoFreeHandlesError     = OLE_ERROR_BASE + 11;
const TInt KOle2RootChainError         = OLE_ERROR_BASE + 12;
const TInt KOle2InvalidFileServer      = OLE_ERROR_BASE + 13;
const TInt KOle2InvalidStreamHandle    = OLE_ERROR_BASE + 14;
const TInt KOle2InvalidParameter       = OLE_ERROR_BASE + 15;
const TInt KOle2ErrEndOfStream         = OLE_ERROR_BASE + 16; 
const TInt KOle2ErrInvalidOpen         = OLE_ERROR_BASE + 17;
const TInt KOle2ErrNoSmallBlockDepot   = OLE_ERROR_BASE + 18;
const TInt KOle2ErrNoSmallBlocks       = OLE_ERROR_BASE + 19;
const TInt KOle2ErrInvalidCreate       = OLE_ERROR_BASE + 20;
const TInt KOle2ErrInvalidWrite        = OLE_ERROR_BASE + 21;
const TInt KOle2ErrNotImplemented      = OLE_ERROR_BASE + 22;
const TInt KOle2ErrInvalidBlock        = OLE_ERROR_BASE + 23;
const TInt KOle2ErrTooManyPropertySets = OLE_ERROR_BASE + 24;

// Word Error Codes - Please make sure that WORD_ERROR_BASE 
//                  - does not overlap with  Ole error codes

#define WORD_ERROR_BASE (ERROR_BASE + 50)

const TInt KWordFileInvalid         = WORD_ERROR_BASE + 1;
const TInt KWordNotSupported        = WORD_ERROR_BASE + 2;
const TInt KWordBadSegment          = WORD_ERROR_BASE + 3;
const TInt KWordInputBufferFull     = WORD_ERROR_BASE + 4;
const TInt KWordBadMainStream       = WORD_ERROR_BASE + 5;
const TInt KWordBadTableStream      = WORD_ERROR_BASE + 6;
const TInt KWordBadFileName         = WORD_ERROR_BASE + 7;
const TInt KWordLookupOutOfRange    = WORD_ERROR_BASE + 8;
const TInt KWordWrongDirection      = WORD_ERROR_BASE + 9;
const TInt KWordInternalStateError  = WORD_ERROR_BASE + 10;
const TInt KWordStepCompleted       = WORD_ERROR_BASE + 11;
const TInt KWordEncrypted           = WORD_ERROR_BASE + 12;
const TInt KWordInvalidDesign       = WORD_ERROR_BASE + 13;
const TInt KWordInvalidChpxSprm     = WORD_ERROR_BASE + 14;
const TInt KWordInvalidPassword     = WORD_ERROR_BASE + 15;
const TInt KWordComplexFile         = WORD_ERROR_BASE + 16;
const TInt KWordUnicodeConversionFailed = WORD_ERROR_BASE + 17;

#define EXCEL_ERROR_BASE (ERROR_BASE + 100)

const TInt KErrInvalidSubStream          = EXCEL_ERROR_BASE + 1;
const TInt KErrInvalidIndex              = EXCEL_ERROR_BASE + 2;
const TInt KErrInvalidToken              = EXCEL_ERROR_BASE + 3;
const TInt KExcelLastCellReached         = EXCEL_ERROR_BASE + 4;
const TInt KExcelLastRowReached          = EXCEL_ERROR_BASE + 5;
const TInt KExcelLastSheetReached        = EXCEL_ERROR_BASE + 6;
const TInt KExcelInvalidSheetNumber      = EXCEL_ERROR_BASE + 7;
const TInt KExcelNoCell                  = EXCEL_ERROR_BASE + 8;
const TInt KExcelInternalFailure         = EXCEL_ERROR_BASE + 9;
const TInt KExcelRecordCorrupt           = EXCEL_ERROR_BASE + 10;
const TInt KExcelDocumentCorrupt         = EXCEL_ERROR_BASE + 11;
const TInt KExcelNotSupported            = EXCEL_ERROR_BASE + 12;
const TInt KExcelIdNotFound              = EXCEL_ERROR_BASE + 13;
const TInt KErrInvalidArgumentCount      = EXCEL_ERROR_BASE + 14;
const TInt KErrInvalidRecord             = EXCEL_ERROR_BASE + 15; 
const TInt KExcelInvalidPassword         = EXCEL_ERROR_BASE + 16;
const TInt KExcelDocumentProtected       = EXCEL_ERROR_BASE + 17;
const TInt KErrSaveFormula               = EXCEL_ERROR_BASE + 18;
const TInt KExcelSkip                    = EXCEL_ERROR_BASE + 19;
const TInt KExcelUnicodeConversionFailed = EXCEL_ERROR_BASE + 20;


// Font Conversion Error Codes - Please make sure that FONT_ERROR_BASE 
//                  - does not overlap with  Excel error codes
 
#define FONT_ERROR_BASE (ERROR_BASE + 150)

const TInt KFontInternalFailure     = FONT_ERROR_BASE + 1;

#define LAST_ERROR_DELIMITER (ERROR_BASE + 200)


#endif // !defined (__COSYINCS_H__)
