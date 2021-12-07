// FRMCONST.H
//
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//

// 
// FOR INFORMATION ONLY (CONTAINS PANIC NUMBERS, ETC.) - NOT PART OF INTERFACE
//

#ifndef __FRMCONST_H__
#define __FRMCONST_H__

#include <w32std.h>

#if defined(_DEBUG)
	#define TInt_D(x) TInt x
	#define TBool_D(x) TBool x
	#define TPoint_D(x) TPoint x
	#define __RETURN_DEBUG(x,y) x=(y)
	#define __DEFAULT_PANIC(x) default: FormPanic(x)
	#define __DEBUG_ONLY(x,y) ,x(y)
	#define __DEBUG_ELSE(x) else {x;}
#else
	#define TInt_D(x) 
	#define TBool_D(x) 
	#define TPoint_D(x)
	#define __RETURN_DEBUG(x,y) y
	#define __DEFAULT_PANIC(x)
	#define __DEBUG_ONLY(x,y)
	#define __DEBUG_ELSE(x)
#endif

// Visible versions of control characters.
const TText KVisibleParagraphBreak = 0x00B6;		// paragraph sign (pilcrow)
const TText KVisibleLineBreak = 0x2193;				// down arrow
const TText KVisibleNonBreakSpace = 0x00B0;			// degree sign
const TText KVisiblePotentialHyphen = 0x00AC;		// not sign
const TText KVisibleNonBreakHyphen = 0x007E;		// spacing tilde
const TText KVisibleSpace = 0x00B7;					// middle dot
const TText KVisibleTab = 0x2192;					// right arrow
const TText KVisiblePicture = 0x25A3;				// white square containing small black square

// Control characters to allow or inhibit line breaks.
const TText KZeroWidthSpace = 0x200B;
const TText KZeroWidthNoBreakSpace = 0xFEFF;

enum TFormPanic
	{
	EFDummy=0,					//Not used

	//Used in ASSERT_ALWAYS

 	//Function calls
	EFPrintPreviewModeError=1,	//Cannot call this function with the print preview flag set.
	EFNoGroupWindowHandle=3,		//Cannot draw text cursor without group window handle
	EFNoWindowHandle=4,			//No window handle and a scroll requested, or text cursor requested 

	//Parameters errors
	EFInvalidDocument=20,		//Document handle NULL has been passed in
	EFInvalidLayout,			//A NULL layout handle has been passed in
  	EFFormatDeviceNotSet,		//The format device has not been set.
	EFImageDeviceNotSet,		//The image device has not been set.
	EFCharacterNotFormatted,	//Character should be formatted for this TextLayout functionality
	EFBadCharacterEditType,		//The character edit type was unknown or incompatible with the format changed value
	EFInvalidJumpValue,			//The horizontal scroll jump value has been set outside the allowable range (0,9999)
	EFMustFormatAllText,		//Must be formatting all text to call this function
	EFInvalidParaFormat,		//A NULL para format handle has been passed in
	EFNoCharRangeToFormat,		//Asked to format a character range which is<0
	EFNoTextLayoutContext,		//A NULL handle to a TextLayoutContext passed into draw function
	EFInconsistentLabelWidth,	//Different label margin widths for formatting and drawing in TextLayout
	EFOffsetNegative,			//Must have a non-negative value

	//Document
	EFInvalidDocPos=40,			//No or negative document position specified or > current document length

	//Drawing
	EFLineCursorBitmapNotSet,	//The function  CTextView::SetLineCursorBitmap has not been called even though a line cursor is being used.

	//Pagination
	EFDocumentToPaginateNotSet,	//No document to paginate 
 	EFInvalidNumberCharsOnPage,	//Appending zero or negative characters per page to page list
	EFPageListEmpty,			//Page list should not be empty at this point

	//Printing
	EFInvalidPageList,			//The array containing the number of characters per page has not been set or is defective
	EFInvalidPageNumber,		//A page requested that is outside the page list given.

	//Used only in ASSERT_DEBUG

	//Parameters errors
	EFInvalidParameter=100,		//Some internal parameter contains an inapproiate value (eg. pointer is NULL when shouldn't be)
	EFSearchBackward,			//Can only search forward in a paragraph
	EFInvalidLineNumber,		//Line number must be positive
 	EFNonPrintingCharacters,	//Cannot format or display non-printing characters in print or print preview mode
	EFInvalidScrollingType,		//A scrolling routine was only expecting certain type of scroll and got a different one.

	//Errors in internal format information
 	EFNoTextOnLine=120,			//A formatted line has no text on it
	EFNoTBoxesOnLine,			//A formatted line has no TBoxes on it
	EFTooFewCharsInTBoxes,		//The tboxes in a line do not contain enough characters
	EFTooFewCharsInParagraph,	//The lines on a Para do not contain enough characters
	EFLineNotInParagraph,		//There are zero or not that many lines in the paragraph
	EFNoParagraphAtTopViewRect,	//The pixel height of zero has no format at it
	EFFoundLineBeyondFormat,	//A line says that it is beyond where the format finishes
	EFFailedToFormatAbove,		//Did not format the required amount above but there was more document to use
	EFNotEnoughFormat,			//Format doesn't fill band but is not to end of document
	EFZeroHeightLine,			//A lines says it has height zero
	EFPixelNotInPara,			//The specified pixel is not in the paragraph
	EFNoFormat,					//Formmatted region shrunk to nothing or run out of format at unexpected time
	EFParaHasNoFormat,			//The Paragraph has no format in it
	EFFirstParaAboveViewRect,	//An entire para is above ViewRect when not formatting all text
	EFSelectedRangeZeroLen,		//The selected range flag is on but the selection has zero length
	EFNoFormatted,				//A call that requires the document to be formatted was made when it wasn't eg. Draw
	EFNoLabel,					//There is no (or it is not formatted) paragraph label
	EFDocHasNoLabel,			//The document has no label when one was expected
	EFCursorNotInCurrentFormat,	//The cursor is a document position that is outsid the formatted range
	EFPixelNotInFormattedLine,	//GetLineRect pixel that was asked for
 	EFPictNotInOwnBox,			//Picture found in a TBox with more than one character in it
	EFLastSegmentMisAligned,	//Illegal alignment of the last segment in a line within an un-wrapped para
	EFSegmentNotJustified,		//Trying to left align segment on last line which should be justified but isn't
	EFNoTBoxInSeg,				//A segment is returned saying it has no TBoxes
	EFTooFewTBoxesOnLine,		//More TBoxes on the line according to the segments than present in list.
	EFTooManyTBoxesOnLine,		//There are less TextBoxes on the line according to the segments than there actually are
 	EFSegmentWithNoBoxes,		//This segment has no TextBoxes
	EFUnexpectedZeroWidthTBox,	//A tbox has been found with zero width when it is not a tab or potential hyphen
	EFTBoxTooLong,				//The TBox has too many characters in it, greater than the maximum number allowed
	EFNoWrappingSegmentInMiddleOfLine,//Only the last segment on a line can have a non-wrapping width
	EFNoPixelsAboveBand,		//The top of format is at y>0 in format coordinates
	EFScrollCurtailed,			//The complete scroll should have been possible

	//Logic error during format	process
	EFInconsistentDocPos=200,		//The specified document positions are inconsistent
	EFParaNotTallEnough,		//The specified y is below the paragraph
	EFParagrahFormatExists,		//Paragraph format exists at a time when it should not
	EFNoParagrahFormat,			//Paragraph format does not exists at a time when it should
	EFParaFormatNotDestroyed,	//Paragraph format exists at, though all formating has finished
	EFNotParaStart,				//The doc pos is not at the start of a para when it should be
	EFNoParagraphSpecified,		//No paragraph (or NULL) was specified as the paragraph to insert after
	EFNoCharactersBeforeWrapWidth,	//Trying to set a wrap width when no chars had been added to the line
	EFNoParasBefore,			//Trying to merge first para in doc with one before it.
	EFDeletedTooMuch,			//Too much of the format has been deleted
	EFNoHeightToFormat,			//Asked to format a height which is <=0
	EFSelectionCannotCharEdit,	//Should not be calling HandleCharEdit when there is a selection
	EFIncorrectFormatDeletion,	//Deleting format when all the text should be formatted
	EFFormatOutOfDate,			//This function should not be called when the format is out of date
	EFFormatLabelTwice,			//The label is already formatted
	EFBackgroundFormatting,		//Background formatting should not be going on
	EFNoWrappingPointSet,		//Trying to wrap when no wrapping position has been found
	EFPotHypNotInOwnBox,		//Potentials hyphens should have there own Tbox
	EFOnlyOneLineSegment,		//Trying to split a tab gap across 2 line segments when there is only one
	EFCurrentTBoxEmpty,			//Adding characters to a current, empty TBox
	EFNoExistingTBoxes,			//Adding characters to non-existent TBox
	EFTabNotStartingTBox,		//Trying to start a Segment or mark box as Tab when not starting a new TBox
	EFPictureError,             //A picture either not in own box, or have handle to a picture not at expected position in doc. 
	EFMoreWordsThanTBoxes,		//Run out of TBox's while justifing line
	EFOutstandingTabLineFull,	//Dealing with an outstanding tab although the line is full
	EFNotStartingNewBox,		//Not starting a new box even though processing the first character	of document phrase
	EFFindingPotHypWidth,		//Finding with of potential hyphen when should have determined it previously
	EFNoTabBoxFound,			//While reformatting for screen a segment did not have a tab box in it
	EFNegativeWords,			//Negative number of words found in segment

	//Scrolling errors
	EFScrollByZero1=250,			//The request for a scroll returned zero as the ammount to scroll by
	EFScrollByZero2,			//a routine that does the scrolling is called with a value of zero or one having wrong sign
	EFScrollError,				//Algorithmic or assumption error in the scroll routine
	EFNoFormatAtTopOfBand,		//A scroll has left the start of the text at positive y
	EFScrollDownError,			//Error when scrolling text down
	EFScrollUpError,			//Error when scrolling text up

	//Out of Memory
	EFNoMemory,					//Cannot do this when in no memory mode
	EFRecoverNoMemory,			//Trying to recover from no_memory when no no_memory condition has occured

	//Cursor
	EFCursorOffDisplay,			//The cursor has been moved to a position off the screen

	//Drawing
	EFPrintOffDisplay=280,			//Tring to draw text that is totaly of the window
	EFGcNotSet,					//The routine that actually does the display has be passed a NULL Gc
	EFNotFormattedAParagraph,	//The specified paragraph handle was not found in the format
	EFDrawingSameLine,			//The draw line routine is going to redraw the same line as it has just drawn
	EFSelectionNotVisible,		//Trying to toggle the highlight on part of the screen when the selection is not visible
	EFFontNotSet,               //A call to draw text with the GDI with no font set
 	EFDrawingBorderError,       //Inconsistency in drawing paragraph borders

	//Document
	EFNoCharsRead=300,				//SenseChars returned a string of length zero
	EFDefaultTabWidthZero,		//The default tab width has been set to zero
	EFUnknownTabType,			//A tab which is not left, centre, or right was found
	EFBorderThicknessOutOfRange,//Only positive values of the TParaBorder.iThickness allowed
	EFMultiLineLabel,			//The paragraph label has more than one line in it

	//Internal Coding Errors
	EFViewInconsistentError=320,	//Inconsistent state in the DoViewL routine
	EFViewNotPositionedCorrectly,//SetViewL has put the text at the wrong vertical height
	EFCharacterShouldBePicture,	//The specified character should be a picture
	EFImpossibleClipping,		//Strange values passed to a routine that calculates the amount of clipping
	EFShouldNotLeave,			//The function call should not leave in this situation
	EFNullParagraphLayout,		//No paragraphs in format, or gone past those formatted
	EFIncorrectCursorMovement,	//Trying to move cursor using wrong function call
	EFWrapLineInconsistentError,//Inconsistent state in the WrapLineL routine
	EFPictureFrameError,		//Wrongly positioned picture frame
	EFNoPictureFrame,			//Should be current picture frame
	EFBulletError,				//Trying to extract or draw a bullet for an para without one
	EFReadingTBoxesError,		//Error in reading TBoxes
	EFSystemConstantsChanged,	//A value of a system constant has changed to a value that has broken this code

	// Line wrapping validation
	EFBadLineWrapRules = 400,

	// Miscellaneous
	EFImplementedOnlyInForm2 = 900	// This exported function is implemented only in FORM2 (the new version using TAGMA)
	};

void FormPanic(TFormPanic aPanic);

#if defined(TIMING_CODE)
class CWindowGc;
class RWsSession;
class CTextView;
class CTextLayout;

class TTestTimingCode
	{
public:
	enum
		{
		EFTAllCode=0,
		EFTSetViewNoBorderReadingDrawing=0x000001,
		EFTSetViewNoLabelTextDrawing=0x000002,
		EFTSetViewNoSwitchingClipRect=0x000004,
		EFTSetViewNoLabelDrawing=0x000008,
		EFTSetViewNoClearRects=0x000010,
		EFTSetViewNoWSTextDrawing=0x000020,
		EFTSetViewDontSetPenColor=0x000040,
		EFTSetViewDontSetFont=0x000080,
		EFTSetViewNoSDTextDrawing=0x000100,
		EFTNoSettingClippingRect=0x000200,
		EFTNoCopyingOfText=0x000400,
		EFTSetViewNoReadingBackText=0x000800,
//		EFTSetViewNoProcessingReadBackText,
		EFTSetViewFormatOnly=0x001000,
		EFTSetViewNoJustifying=0x002000,
		EFTSetViewFormatFirstParagraphOnly=0x004000,
		EFTSetViewFirstLineOnly=0x008000,
		EFTSetViewFormatFirstLineOnly=0x010000,
		EFTSetViewLabelOnly=0x020000,
		EFTSetViewDontDoLabel=0x040000,
		EFTSetViewDefaultParaFormat=0x080000,
//		EFTLast=EFTSetViewDefaultParaFormat,
		EFTFirst=EFTAllCode,
		EFTTotalFlags=21,
		};
	};
#endif

#endif

