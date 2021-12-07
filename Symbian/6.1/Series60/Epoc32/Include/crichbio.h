/*
* ============================================================================
*  Name     : CRichBio from CRichBio.h
*  Part of  : RICHBIO
*
*  Description:
*     A UI control used by Smart Messaging Viewers.
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef _CRICHBIO_H_
#define _CRICHBIO_H_

// INCLUDES

#include <coecntrl.h>           // CCoeControl
#include <badesca.h>            // CDesC16ArrayFlat
#include <txtfrmat.h>           // TCharFormat
#include <MsgEditor.hrh>        // TMsgCursorLocation

// DATA TYPES

enum TRichBioMode
    {
    ERichBioModeEditorBase,
    ERichBioModeStandard
    };

// FORWARD DECLARATIONS

class CEikRichTextEditor;
class CMsgExpandableControlEditor;

/**
 * A UI control used by Smart Messaging Viewers.
 * This control owns editor, which is capable of viewing rich text content.
 * NOTE! This is only intended for use with the Smart Message Viewers.
 */
class CRichBio : public CCoeControl
    {
    public: // construction

        /**
         * Two-phased constructor. Constructs the complete object.
         * The parent control has to have a container window at this stage.
         * @param aParent The parent control.
         * @param aMode Either ERichBioModeEditorBase or ERichBioModeStandard
         *        It affects the way scrolling is done.
         * @return a pointer to the created object.
         */
        IMPORT_C static CRichBio* NewL( const CCoeControl* aParent,
            TRichBioMode aMode );

        /**
         * Constructor.
         * ConstructL must be called after this at some point.
         * @param aMode Either ERichBioModeEditorBase or ERichBioModeStandard
         *        It affects the way scrolling is done.
         */
        IMPORT_C CRichBio( TRichBioMode aMode );

        /**
         * Second phase constructor.
         * The parent control has to have a container window at this stage.
         * @param aParent The parent control, which has container window.
         */
        IMPORT_C void ConstructL( const CCoeControl* aParent );

    public: // destruction

        /**
         * Destructor
         */
        ~CRichBio();

    public: // own methods

        /**
         * Adds a label and value pair.
         * The client does not need to check the length. This function can
         * take care of strings that are too long.
         * @param aLabel text to displayed in label text format.
         * @param aValue text to displayed in text format.
         */
        IMPORT_C void AddItemL(const TDesC& aLabel, const TDesC& aValue);

        /**
         * This is needed for scrolling with Editor Base.
         * @return TRect Returns the rect of the "current" line.
         */
        IMPORT_C TRect CurrentLineRect();

        /**
         * For accessing the richtext editor.
         * Don't call it before the ConstructL has been called.
         * @return Reference to the CEikRichTextEditor
         * @exception Panics if the iEditor is NULL.
         */
        IMPORT_C CEikRichTextEditor& Editor();

        /**
         * Is the editor base mode on.
         * @return ETrue if it is in Editor Base mode.
         */
        IMPORT_C TBool IsEditorBaseMode() const;

        /**
         * Empties the data contents.
         */
        IMPORT_C void Reset();

        /**
        * Inquire the controls preferred size.
        * @param aSize Control may set it's preferred size to
        * the variable.
        */
        IMPORT_C void SetAndGetSizeL( TSize& aSize );

        /**
        * Get the richtext virtual length.
        * @return text length in rich text.
        */
        IMPORT_C TInt VirtualHeight();

        /**
        * Get current cursor position.
        * Even in the viewer mode control contains a hidden cursor.
        * This method return it's position.
        * @return a position of the hidden cursor
        * relative to the virtual length.
        */
        IMPORT_C TInt VirtualVisibleTop();

        /**
        * Find out if the cursor is at the certain position.
        * @param aLocation indicates either that the cursor is at the topmost
        * position of the control or at the bottom most position.
        * @return ETrue if the cursor is at the specified position, EFalse otherwise.
        */
        IMPORT_C TBool IsCursorLocation(TMsgCursorLocation aLocation) const;

    public: // from CCoeControl

        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    private: // Own helper methods.

        void ApplyLabelFormat(TCharFormat& aFormat, TCharFormatMask& aMask);

        void ApplyValueFormat(TCharFormat& aFormat, TCharFormatMask& aMask);

        void ApplyFormat(TCharFormat& aFormat, TCharFormatMask& aMask, TBool aIsLabel);

        void AddItemToRichTextL(const TDesC& aLabel, const TDesC& aValue);

        void AppendTextL( const TDesC& aText,
            const TCharFormat& aFormat,
            const TCharFormatMask& aMask );

        const TDesC& FindLineFeedSeparatedTextLC( const TDesC& aText,
            const TInt aStartPosition );

        TBool CacheExists();

        void LoadFromCacheL();

        void CacheItemL(const TDesC& aLabel, const TDesC& aValue);

        static void Panic( TInt aPanic );

    private:

        /**
         * Default constructor prohibited
         */
        CRichBio();

        /**
         * Copy constructor hidden away.
         */
        CRichBio(const CRichBio& aSource);

        /**
         * Assignment operator hidden away.
         */
        const CRichBio& operator=(const CRichBio& aSource);

    private: // from CCoeControl

        void Draw(const TRect& aRect) const;

        TInt CountComponentControls() const;

        CCoeControl* ComponentControl(TInt aIndex) const;

        void SizeChanged();

    private:

        /// Introduce inner class.
        class CEdwinSizeObserver;

        /// Declare inner class friend.
        friend class CEdwinSizeObserver;

        /// Pointer to the editor size observer.
        CEdwinSizeObserver* iEdwinSizeObserver;

        /// Editor control
        CMsgExpandableControlEditor* iEditor;

        /// Control's virtual height is stored to this member.
        TInt iVirtualHeight;

        // startup cache for data
        CDesC16ArrayFlat* iLabelCache;

        // startup cache for data
        CDesC16ArrayFlat* iValueCache;

        // Editor Base mode on or off.
        const TRichBioMode iMode;

        TBool iIsFirstItem;
    private:
        friend class T_RichBioTestSuite;
    };

#endif //_CRICHBIO_H_

// end of file
