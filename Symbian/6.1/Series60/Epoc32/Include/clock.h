/*
* ==============================================================================
*  Name        : Clock.h
*  Part of     : ClkClockSrv / Clocka.dll
*  Interface   : 
*  Description : 
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef CLKCLOCKCLT_H
#define CLKCLOCKCLT_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <w32std.h>

// CONSTANTS
const TInt KNumDigitalShadowImages = 29;
const TInt KNumDigitalShadowRects = 3;

// DATA TYPES
typedef TBuf8<1024> TConstructorBuf8; // implementation class

enum TDisplayType // implementation class
    {
    EDisplayDigital,
    EDisplayAnalog,
    EDisplayAmPm
    };

enum TDigitalDisplayHorizontalTextAlignment
    {
    EDigitalDisplayHorizontalTextAlignmentLeft,
    EDigitalDisplayHorizontalTextAlignmentCenter,
    EDigitalDisplayHorizontalTextAlignmentRight
    };

enum TAnalogDisplayHandType
    {
    EAnalogDisplayHandOneRevPer12Hours,
    EAnalogDisplayHandOneRevPerHour,
    EAnalogDisplayHandOneRevPerMinute
    };

enum TClkClockClientPanic
    {
    EClkClockClientPanicAlreadyConstructed,
    EClkClockClientPanicAlreadyConstructedDigitalClock,
    EClkClockClientPanicAlreadyConstructedAnalogClock,
    EClkClockClientPanicAlreadyConstructedAmPmClock,
    EClkClockClientPanicNotYetConstructedDigitalClock,
    EClkClockClientPanicNotYetConstructedAnalogClock,
    EClkClockClientPanicNotYetFullyConstructed1,
    EClkClockClientPanicNotYetFullyConstructed2,
    EClkClockClientPanicNotYetFullyConstructed3,
    EClkClockClientPanicNotYetFullyConstructed4,
    EClkClockClientPanicNotYetFullyConstructed5,
    EClkClockClientPanicNotYetFullyConstructed6,
    EClkClockClientPanicNotYetFullyConstructed7,
    EClkClockClientPanicNotYetFullyConstructed8,
    EClkClockClientPanicNotYetFullyConstructed9,
    EClkClockClientPanicNotYetFullyConstructed10,
    EClkClockClientPanicNotYetFullyConstructed11,
    EClkClockClientPanicNotYetFullyConstructed12,
    EClkClockClientPanicIncorrectNumberOfAdditions1,
    EClkClockClientPanicIncorrectNumberOfAdditions2,
    EClkClockClientPanicNoConstructorBuf,
    EClkClockClientPanicBadSetNumAdditionsStillExpectedCall,
    //EClkClockClientPanicTooFewTextSections,
    EClkClockClientPanicTooFewHands,
    //EClkClockClientPanicTooFewHandFeatures,
    EClkClockClientPanicRectIsNotNormalized,
    EClkClockClientPanicUnexpectedError1,
    EClkClockClientPanicUnexpectedError2,
    EClkClockClientPanicUnexpectedError3,
    EClkClockClientPanicUnexpectedError4,
    EClkClockClientPanicUnexpectedError5,
    EClkClockClientPanicUnexpectedError6,
    EClkClockClientPanicUnexpectedError7,
    EClkClockClientPanicUnexpectedError8,
    EClkClockClientPanicUnexpectedError9,
    EClkClockClientPanicUnexpectedError10,
    EClkClockClientPanicUnexpectedError11,
    EClkClockClientPanicUnexpectedError12,
// Setting the colors
    EClkClockClientPanicNotYetFullyConstructedDigitalTextColor,
    EClkClockClientPanicNotYetFullyConstructedAnalogPenColor,
    //EClkClockClientPanicNotYetFullyConstructedAnalogBrushColor,
    EClkClockClientPanicNotYetFullyConstructedMsgWindowBackgroundColor,
    EClkClockClientPanicNotYetFullyConstructedMsgWindowTextColor,
    EClkClockClientPanicNotYetFullyConstructedMsgWindowBorderColor,
    EClkClockClientPanicNotYetFullyConstructedMsgWindowPlinthColor,
    EClkClockClientPanicUnexpectedErrorDigitalTextColor,
    EClkClockClientPanicUnexpectedErrorAnalogPenColor,
    //EClkClockClientPanicUnexpectedErrorAnalogBrushColor,
    EClkClockClientPanicUnexpectedErrorMsgWindowBackgroundColor,
    EClkClockClientPanicUnexpectedErrorMsgWindowTextColor,
    EClkClockClientPanicUnexpectedErrorMsgWindowBorderColor,
    EClkClockClientPanicUnexpectedErrorMsgWindowPlinthColor,
    };

// FUNCTION PROTOTYPES
GLREF_C void Panic(TClkClockClientPanic aReason);

// CLASS DECLARATION

/**
* Base class to a display addition of the clock.
* It has a data buffer to construct an animation object.
*/
class TDisplayAddition
    {
    public:    // New functions

        /**
        * Gets a constructor data buffer.
        */
        const TDesC8& Buf() const;

    protected:  // Data
        TConstructorBuf8 iBuf;
    };

/**
* Class to display a text section of digital clock.
*
*/
class TDigitalDisplayTextSection : public TDisplayAddition
    {
    public: // Constructors and destructor

        /**
        * Constructor
        * The font passed in to aFontHandle cannot be destroyed until the
        * RDigitalClock has been completely constructed,
        * including all necessary
        * calls to RDigitalClock::AddTextSectionL()
        * @param aFontHandle
        * @param aTextColor
        * @param TInt aFontHandle,
        * @param aTextColor
        * @param aLeftMargin12
        * @param aRightMargin12
        * @param aLefyMargin24
        * @param aRightMargin24
        * @param aBaseLine
        * @param aTextAlign
        */
        IMPORT_C TDigitalDisplayTextSection(
            TInt aFontHandle,
            TRgb aTextColor,
            TInt aLeftMargin12,
            TInt aRightMargin12,
            TInt aLefyMargin24,
            TInt aRightMargin24,
            TInt aBaseLine,
            CGraphicsContext::TTextAlign aTextAlign);
    };

/**
* Class to display an am/pm section of the digital clock.
*
*/
class TDigitalDisplayAmPm : public TDisplayAddition
    {
    public: // Constructors and destructor

        /**
        * Constructor
        * The font passed in to aFontHandle cannot be destroyed until the
        * RDigitalClock has been completely constructed,
        * including all necessary
        * calls to RDigitalClock::AddTextSectionL()
        * @param aFontHandle
        * @param aTextColor
        * @param TInt aFontHandle,
        * @param aTextColor
        * @param aLeftMargin
        * @param aRightMargin
        * @param aBaseLine
        * @param aTextAlign
        */
        IMPORT_C TDigitalDisplayAmPm(
            TInt aFontHandle,
            TRgb aTextColor,
            TInt aLeftMargin,
            TInt aRightMargin,
            TInt aBaseLine,
            CGraphicsContext::TTextAlign aTextAlign);
    };

/**
* Class to display a hand of the analog clock.
*
*/
class TAnalogDisplayHand : public TDisplayAddition
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        * @param aType one of EAnalogDisplayHandOneRevPer12Hours,
        *                     EAnalogDisplayHandOneRevPerHour
        *                  or EAnalogDisplayHandOneRevPerMinute.
        */
        IMPORT_C TAnalogDisplayHand(TAnalogDisplayHandType aType);

    public: // New functions

        /**
        * Adds a line data to the constructor data buffer.
        * @param aPenStyle one of ENullPen, ESolidPen, EDottedPen,
        *                   EDashedPen, EDotDashPen or EDotDotDashPen
        * @param aPenColor
        * @param aPenSize
        * @param aStartPoint
        * @param aEndPoint
        */
        IMPORT_C void AddLine(
            CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor,
                const TSize& aPenSize, const TPoint& aStartPoint,
                    const TPoint& aEndPoint);
    };

/**
*  Client side class for each instance of an animated object.
*  It has utilities.
*/
class RAnimWithUtils : public RAnim
    {
    public: // Functions from base classes

        /**
        * From RAnim Free
        * resources belonging to an animation object.
        * Issue a command which will be passed
        * to the matching server side function.
        */
        IMPORT_C void Close();

    protected: // Constructors and destructor

        /**
        * Constructor
        * @param aAnimDll
        * @param aWindow
        */
        RAnimWithUtils(RAnimDll& aAnimDll, const RWindowBase& aWindow);

    protected:  // New functions

        /**
        * Appends a data to the constructor data buffer.
        * @param aData data to construct a animation object
        */
        void AppendToConstructorBufL(const TDesC8& aData);

        /**
        * Sends the constructor data buffer if all additions are added to it.
        * @param aAnimatedObjectType
        */
        void SendConstructorBufIfCompleteL(TInt aAnimatedObjectType);

        /**
        * Sends the constructor data buffer.
        * @param aAnimatedObjectType
        */
        void SendConstructorBufL(TInt aAnimatedObjectType);

        /**
        * Asks if the constructor buffer exists.
        * @return   ETrue means the constructor buffer exists.
        *           EFalse means the constructor buffer does not exist.
        */
        TBool ConstructorBufExists() const;

        /**
        * Asks if the constructor buffer has been sent already.
        * @return   ETrue means the constructor buffer has been sent.
        *           EFalse means the constructor buffer has not been sent.
        */
        TBool ConstructorBufAlreadySent() const;

        /**
        * Gets the constructor buffer.
        * @return a constructor buffer.
        */
        TConstructorBuf8& ConstructorBuf() const;

        /**
        * Sets the number of displayed addtions of the clock.
        * @param aNumAdditionsStillExpected A number of displayed addtions.
        */
        void SetNumAdditionsStillExpected(TInt aNumAdditionsStillExpected);

    private:    // Data
        // on the heap as it is only required for construction
        TConstructorBuf8* iConstructorBuf;
        TBool iConstructorBufAlreadySent;
        const RWindowBase& iWindow;
        TInt iNumAdditionsStillExpected;
    };

/**
* Client side class of a animated time object.
*
*/
class RTimeDevice : public RAnimWithUtils
    {
    public: // New functions

        /**
        * Sets a time object's visiblity.
        * can only be called after full construction
        * - by default clocks are invisible
        * @param aVisible   ETrue means it is visible.
        *                   EFalse means it isn't visible.
        */
        IMPORT_C void SetVisible(TBool aVisible);

        /**
        * Sets the potition and the zize.
        * can only be called after full construction
        * @param aPosition
        * @param aSize
        */
        IMPORT_C void SetPositionAndSize(
            const TPoint& aPosition, const TSize& aSize);

        /**
        * Sets the potition.
        * can only be called after full construction
        * @param aPosition
        */
        IMPORT_C void SetPosition(const TPoint& aPosition);

        /**
        * Sets the zize.
        * can only be called after full construction
        * @param aSize
        */
        IMPORT_C void SetSize(const TSize& aSize);

        /**
        * Updates the displayed time object.
        * can only be called after full construction
        */
        IMPORT_C void UpdateDisplay();

        /**
        * Draws the displayed time object.
        * can only be called after full construction
        */
        IMPORT_C void Draw();

    protected: // Constructors and destructor

        /**
        * Constructor
        * @param aAnimDll
        * @param aWindow
        */
        RTimeDevice(RAnimDll& aAnimDll, const RWindowBase& aWindow);

    protected:  // New functions

        /**
        * Appends a display type to the constructor data buffer.
        * @param aType one of EDisplayDigital or EDisplayAnalog
        */
        void AppendDisplayTypeL(TDisplayType aType);

        /**
        * Appends a digital display data to the constructor data buffer.
        * @param aPosition
        * @param aSize
        * @param aBackgroundColor
        * @param aWithShadow
        * @param aWithAmPm
        * @param aNumTextSections
        */
        void AppendDigitalDisplayConstructorArgsL(
            const TPoint& aPosition, const TSize& aSize,
                TRgb aBackgroundColor, TBool aWithShadow,
                    TBool aWithAmPmTInt, TInt aNumTextSections);

        /**
        * Appends a analog display data to the constructor data buffer.
        * @param aPosition
        * @param aSize
        * @param aCenterPosition
        * @param aFaceHandle
        * @param aCenterHandle
        * @param aNumHands
        * @param aDate
        */
        void AppendAnalogDisplayConstructorArgsL(
            const TPoint& aPosition, const TSize& aSize,
                const TPoint& aCenterPosition,
                    TInt aFaceHandle, TInt aCenterHandle,
                        TInt aNumHands, TBool aHasDate);

        /**
        * Appends an am/pm display data to the constructor data buffer.
        * @param aPosition
        * @param aSize
        * @param aFontHandle
        * @param aTextColor
        * @param aLeftMargin
        * @param aRightMargin
        * @param aBaseLine
        * @param aTextAlign
        */
        void AppendAmPmDisplayConstructorArgsL(
            const TPoint& aPosition, const TSize& aSize,
            TInt aFontHandle, TRgb aTextColor,
            TInt aLeftMargin, TInt aRightMargin,
            TInt aBaseLine, CGraphicsContext::TTextAlign aTextAlign);
    };

/**
* Client side class of an animated clock object.
*
*/
class RClockAnim : public RTimeDevice
    {
    public: // New functions

        /**
        * Sets the univeral time offset.
        * can only be called after full construction
        * @param aUniversalTimeOffset
        */
        IMPORT_C void SetUniversalTimeOffset(
            TTimeIntervalSeconds aUniversalTimeOffset);

    protected: // Constructors and destructor

        /**
        * Constructor
        * @param aAnimDll
        * @param aWindow
        */
        RClockAnim(RAnimDll& aAnimDll, const RWindowBase& aWindow);

        /*
        * Appends a univeral time offset to the constructor data buffer.
        * @param aUniversalTimeOffset
        */
        void AppendClockConstructorArgsL(
            TTimeIntervalSeconds aUniversalTimeOffset);
    };

/**
*  Digital clock class on the client side.
*
*/
class RDigitalClock : public RClockAnim
    {
    public: // Constructors and destructor

        /**
        * Constructor
        * @param aAnimDll
        * @param aWindow
        */
        IMPORT_C RDigitalClock(RAnimDll& aAnimDll,
                                const RWindowBase& aWindow);

        /**
        * Default Symbian OS constructor.
        * @param aUniversalTimeOffset
        * @param aPosition
        * @param aSize
        * @param aBackgroundColor
        * @param aWithShadow
        * @param aWithAmPm
        * @param aNumTextSections
        */
        IMPORT_C void ConstructL(
            TTimeIntervalSeconds aUniversalTimeOffset,
            const TPoint& aPosition,
            const TSize& aSize,
            TRgb aBackgroundColor,
            TBool aWithShadow,
            TBool aWithAmPm,
            TInt aNumTextSections);

    public: // New functions

        /**
        * Adds a text section to the constructor data buffer.
        * @param aTextSection
        */
        IMPORT_C void AddTextSectionL(
            const TDigitalDisplayTextSection& aTextSection);

        /**
        * Adds an am/pm section to the constructor data buffer.
        * @param anAmPm
        */
        IMPORT_C void AddAmPmL(const TDigitalDisplayAmPm& anAmPm);

        /**
        * Adds a shadow image the constructor data buffer.
        * @param aImageHandle
        */
        IMPORT_C void AddImageL(TInt aImageHandle);

        /**
        * Adds a shadow rect to the constructor data buffer.
        * @param aPosition
        * @param aSize
        */
        IMPORT_C void AddRectL(const TPoint& aPosition,
                                        const TSize& aSize);

        /**
        * Sets the background color and the shadoe color.
        * can only be called after full construction
        * @param aBackgroundColor
        * @param aShadowColor   (This is not used now.)
        */
        IMPORT_C void SetBackgroundColor(
            TRgb aBackgroundColor, TRgb aShadowColor);

        /**
        * Sets the text color.
        * @param aTextColor
        * @param aShadowColor   // Change at the next APIs freeze.
        */
        IMPORT_C void SetTextColor(TRgb aTextColor/*, TRgb aShadowColor*/);
    };

/**
*  Analog clock class on the client side.
*
*/
class RAnalogClock : public RClockAnim
    {
    public: // Constructors and destructor

        /**
        * Constructor
        * @param aAnimDll
        * @param aWindow
        */
        IMPORT_C RAnalogClock(RAnimDll& aAnimDll,
                            const RWindowBase& aWindow);

        /**
        * Default Symbian OS constructor.
        * The bitmap(s) passed to aFaceHandle and aCenterHandle in these
        * ConstructL functions cannot be destroyed
        * until the RAnalogClock has been completely constructed.
        * @param aUniversalTimeOffset
        * @param aPosition
        * @param aSize
        * @param aCenterPosition
        * @param aFaceHandle
        * @param aCenterHandle
        * @param aNumHands
        * @param aHasDate
        */
        IMPORT_C void ConstructL(
            TTimeIntervalSeconds aUniversalTimeOffset,
            const TPoint& aPosition,
            const TSize& aSize,
            const TPoint& aCenterPosition,
            TInt aFaceHandle,
            TInt aCenterHandle,
            TInt aNumHands,
            TBool aHasDate);

    public: // New functions

        /**
        * Adds a hand data to the constructor data buffer.
        * @param aHand
        */
        IMPORT_C void AddHandL(const TAnalogDisplayHand& aHand);

        /**
        * Adds a date data to the constructor data buffer.
        * @param aPosition
        * @param aSize
        * @param aFontHandle
        * @param aTextColor
        * @paramt aLeftMargin
        * @param aRightMargin
        * @param aBaseLine
        * @param aTextAlign
        */
        IMPORT_C void AddDateL(
                const TPoint aPosition,
                const TSize aSize,
                TInt aFontHandle,
                TRgb aTextColor,
                TInt aLeftMargin,
                TInt aRightMargin,
                TInt aBaseLine,
                CGraphicsContext::TTextAlign aTextAlign);

        /**
        * Sets the text color.
        * @param aTextColor
        */
        IMPORT_C void SetTextColor(TRgb aTextColor);

        /**
        * Sets the pen color.
        * @param aPenColor
        */
        IMPORT_C void SetPenColor(const TRgb aPenColor);

    };

/**
*  AmPm clock class on the client side.
*
*/
class RAmPmClock : public RClockAnim
    {
    public: // Constructors and destructor

        /**
        * Constructor
        * @param aAnimDll
        * @param aWindow
        */
        IMPORT_C RAmPmClock(RAnimDll& aAnimDll, const RWindowBase& aWindow);

        /**
        * Default Symbian OS constructor.
        * @param aUniversalTimeOffset
        * @param aPosition
        * @param aSize
        * @param aFontHandle
        * @param aTextColor
        * @param aLeftMargin
        * @param aRightMargin
        * @param aBaseLine
        * @param aTextAlign
        */
        IMPORT_C void ConstructL(
            TTimeIntervalSeconds aUniversalTimeOffset,
            const TPoint& aPosition,
            const TSize& aSize,
            TInt aFontHandle,
            TRgb aTextColor,
            TInt aLeftMargin,
            TInt aRightMargin,
            TInt aBaseLine,
            CGraphicsContext::TTextAlign aTextAlign);

        /**
        * Sets the text color.
        * @param aTextColor
        */
        //next IMPORT_C void SetTextColor(TRgb aTextColor);
    };

/**
*   message-window class
*   Imported from clock module directly. Changed the parent class only.
*/
class RMessageWindow : public RAnimWithUtils
    {
    public:
        enum
            {
            EMaxTextLength=80
            };
    public:
        IMPORT_C RMessageWindow(RAnimDll& aAnimDll, const RWindowBase& aWindow);
        IMPORT_C void ConstructL(TInt aBaselineOffset,
            TInt aFontHandle, TRgb aBackgroundColor, TRgb aTextColor);
        IMPORT_C void ConstructL(TInt aBaselineOffset,
            TInt aFontHandle, TRgb aBackgroundColor, TRgb aTextColor, TRgb aBorderColor);
        IMPORT_C void StartDisplay(TBool aFlash,
            TTimeIntervalMicroSeconds32 aInitialDelay, const TDesC& aText);
        IMPORT_C void StartDisplay(TBool aFlash, TTimeIntervalMicroSeconds32 aInitialDelay,
            TTimeIntervalMicroSeconds32 aDuration, const TDesC& aText);
        IMPORT_C void CancelDisplay();
        IMPORT_C void GetBorders(TMargins& aBorders);
        IMPORT_C void SetBackgroundColor(TRgb aBackgroundColor);
        IMPORT_C void SetTextColor(TRgb aTextColor);
        IMPORT_C void SetBorderColor(TRgb aBorderColor);
        IMPORT_C void SetPlinthColors(TRgb aTl,TRgb aBr);
    };

#endif  // CLKCLOCKCLT_H

