/*
* ============================================================================
*  Name     : CAknQueryControl.h
*  Part of  : Avkon
*
*  Description:
*   Implementation of Query control and List query control.
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
   
#ifndef AKNQUERYCONTROL_H
#define AKNQUERYCONTROL_H

//  INCLUDES
#include <coecntrl.h>
#include <gulbordr.h>

#include <eikedwin.h>
#include <eikseced.h>
#include <eikmfne.h>
#include <aknnumseced.h>
#include <aknnumedwin.h>
#include <eikfpne.h>

#include <eikimage.h>   
#include <eikedwob.h>

#include <aknutils.h>
#include <aknPanic.h>


//  FORWARD DECLARATIONS
class CAknQueryControl;
class TAknQueryEcsObserver;
class CAknEcsDetector;
class CAknBitmapAnimation;
class CAknTextControl;
class CAknQueryEditIndicator;
class MLAFIndex;
class MAknEditingStateIndicator;
/**
* MAknQueryControlObserver
*   Callback class for CAknQueryDialog
*/
class MAknQueryControlObserver
	{
public:
    /**
    * Enumeration for query control events
    */
	enum TQueryControlEvent
		{
		EQueryControltSizeChanging,
		EQueryControlEditorStateChanging
		};

    /**
    * Enumeration for editor validation status
    */
	enum TQueryValidationStatus
		{
		EEditorValueValid = KErrNone,
		EEditorValueTooSmall,
		EEditorValueTooLarge,
		EEditorValueNotParsed,
		EEditorEmpty
		};

public:
    /**
    * Gets called when editor sends size event
    */
	virtual TBool HandleQueryEditorSizeEventL(CAknQueryControl* aQueryControl, TQueryControlEvent aEventType)=0;
    /**
    * Gets called when editor sends state event
    */
	virtual TBool HandleQueryEditorStateEventL(CAknQueryControl* aQueryControl, TQueryControlEvent aEventType, TQueryValidationStatus aStatus)=0;
	};

/**
 * The control for a query dialog.
 *
 * Manage layout of elements in a query dialog:- the text, the image 
 * and the editors.
 *
 * @see CAknQueryDialog, CAknText
 */
class CAknQueryControl : public CCoeControl , public MEikEdwinObserver , public MEikEdwinSizeObserver , public MCoeControlObserver
    {
	public:
        /**
        * Enumeration for indexing into control flags, which
		* determine the control behaviour relative to a number
		* of things, e.g. emergency control handling, displaying of 
		* edit indicator, enabling of predictive text, etc
        */
        enum TQueryControlFlagBitIndices
            {
            EEmergencyCallsEnabledByAPI,
            EEmergencyCallsDisabledByAPI,
            EPredictiveTextEntryPermitted,
            EEditorIndicatorOff
            };

		/**
         * Layout for queries can be done
		 * using the following methods. Each
		 * method is specified in a LAF section
		 */
		enum TLayoutMethod 
			{
			EConfQueryLayoutM,             ///LAYOUT according to LAF specs for conf queries
			EDataQueryLayoutM,             ///LAYOUT according to LAF specs for data queries
			ECodeQueryLayoutM,             ///LAYOUT accoridng to LAF specs for code queries
			ETimeQueryLayoutM,             ///LAYOUT according to LAF specs for time queries
			EDateQueryLayoutM,             ///LAYOUT according to LAF specs for date queries
			ECombinedCodeDataQueryLayoutM  ///LAYOUT according to LAF specs for combined code and data queries
			};

	public:  // Constructors and destructor

        /**
         * C++ Constructor.
         */
	    IMPORT_C CAknQueryControl();

        /**
         * C++ Destructor.
         */
	    IMPORT_C virtual ~CAknQueryControl();

        /**
         * Second phase constructor: loads contents of array from resources.
         *
         * @param aRea      resource reader pointed to a 
         *                  query resource.
         */
	    IMPORT_C void ConstructFromResourceL(TResourceReader& aRes);

    public: // New functions

        /**
        * Set observer for query control.
        *
        * @param aQueryControlObserver  Pointer to oberver class 
        */
	    IMPORT_C void SetQueryControlObserver(MAknQueryControlObserver* aQueryControlObserver);

        /**
        * Read prompt text from resource and call SetPrompt if there was text for prompt.
        *
        * @param aRes   resource reader pointed to a query resource
        */
	    IMPORT_C virtual void ReadPromptL(TResourceReader& aRes);

        /**
        * Set prompt text for query. This call WrapToStringL.
        *
        * @param aDesC  Text for prompt
        */
	    IMPORT_C virtual void SetPromptL(const TDesC& aDesC);

        /**
        * Get text from text, secret text, numeric secret text snd phonenumber editor.
        * 
        * @param aDes   Address of variable where text returned.
        */
	    IMPORT_C void GetText(TDes& aDes) const;

        /**
        * Get time from date or time editors
        * 
        * @return Returns data from editor.
        */
	    IMPORT_C TTime GetTime() const;

        /**
        * Get number from number editor.
        * 
        * @return Returns number from editor
        */
		IMPORT_C TInt GetNumber() const;

        /**
        * Get number from floating point editor.
        * 
        * @return Returns number from editor
        */
        IMPORT_C TReal GetFloatingPointNumberL() const;

        /**
        * Get duration from duration editor
        * 
        * @return Return duration from editor.
        */
	    IMPORT_C TTimeIntervalSeconds GetDuration() const;

        /**
        * Set text to text and phonenumber editor.
        * 
        * @param aDesC Text for editor
        */
	    IMPORT_C void SetTextL(const TDesC& aDesC);

        /**
        * Set date of time to editor
        * 
        * @param aTime Time or date to editor.
        */
	    IMPORT_C void SetTime(TTime& aTime);

        /**
        * Set duration to duration editor
        * 
        * @param aDuration  Duration to editor
        */
	    IMPORT_C void SetDuration(TTimeIntervalSeconds& aDuration);

        /**
        * Set number to number editor
        * @param aNumber    Number to editor
        *
        */
	    IMPORT_C void SetNumberL(TInt aNumber);

         /**
        * Set number to floating point editor
        * @param aNumber    Number to editor
        *
        */
        IMPORT_C void SetFloatingPointNumberL(const TReal* aNumber);

        /**
        * Set max length of text to text editor. This will override length from resource
        * @param aLength    Max length of text in editor
        * 
        */
        IMPORT_C void SetTextEntryLength(TInt aLength);

		/**
		* Return the max length of the text in the text editor
		* @return max text length
		*/
		IMPORT_C TInt GetTextEntryLength() const;

        /**
        * Set minimum and maximum time or date to editor
        * @param aMinimum   Minimum value 
        * @param aMaximum   Maximum value
        * 
        */
        IMPORT_C void SetMinimumAndMaximum(const TTime& aMinimum, const TTime& aMaximum);

        /**
        * Set minimum and maximum duration to editor
        * @param aMinimumDuration   Minimum value
        * @param aMaximumDuration   Maximum value
        */
        IMPORT_C void SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration);

        /**
        * Set minimum and maximum number to editor
        * @param aMinimumValue   Minimum value
        * @param aMaximumValue   Maximum value
        */
        IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue);

		/**
		* Set the number of lines in the editor.
		*
		* @param aNum Number of lines in the editor
		*/
		IMPORT_C void SetNumberOfEditorLines(TInt aNum);

        /**
        * Set minimum and maximum number to floating point editor
        * @param aMinimumValue   Minimum value
        * @param aMaximumValue   Maximum value
        */
        IMPORT_C void SetMinimumAndMaximum(const TReal& aMinimumValue, const TReal& aMaximumValue);
        /**
        * Get text length from editor.
        * 
        * @return Length of text from editor
        */
	    IMPORT_C TInt GetTextLength() const;

        /**
        * Get number of editor lines
        * 
		* @deprecated Use NbrOfEditorLines instead
		*
        * @return Number of editor lines
        */
	    IMPORT_C TInt GetNbrOfLines() const;

		/**
		* Return number of editor lines
		*
		* @return Number lines in the editor
		*/

		IMPORT_C TInt NbrOfEditorLines() const;


        /**
        * Return number of prompt lines
        * 
        * @return Number of lines in the prompt
        */
	    IMPORT_C TInt NbrOfPromptLines() const;

        /**
        * Get pointer to query controls control (editor)
        *
        * @param aLayout    Controls layout (for one line queries use
        *                   EDataLayout, ECodeLayout... and for
        *                   multiline queries use
        *                   EMultiDataFirstEdwin, EMultiDataSecondEdwin...)
        * @return           Pointer to control, NULL if not found 
        */
		IMPORT_C virtual CCoeControl* ControlByLayoutOrNull(TInt aLayout);

        /**
        * Sets and overrides other image or animation
        * Takes ownership of aImage
        */
        IMPORT_C void SetImageL(CEikImage* aImage);

        /**
        * Sets and overrides other image or animation
        */
        IMPORT_C void SetImageL(const TDesC& aImageFile,
                                TInt aBmpId, TInt aBmpMaskId);
		/**
        * Sets and overrides other animation
        * 
        */
		IMPORT_C void SetAnimationL(TInt aResource);

		/**
        * starts animation if one present
        * 
        */
		IMPORT_C void StartAnimationL();

        /**
        * stops animation if one present
        * 
        * @return error code
        */
		IMPORT_C TInt CancelAnimation();

		/**
		* This cancels the query.  Used when the query control has to get abandon the query
		* for some reason
		*/
		void CancelQueryL();

		/**
		*	@return true if the content of the editor is valid, false otherwise
		*/
		TBool EditorContentIsValidL() const;

		/**
		* This transfers CAknQueryControl's flags set by the dialog and then uses them.
		* The method must be called after all the contained controls are constructed;
		* Inside PreLayoutDynamicInitL is recommended.
		* 
		* @param flag pattern to set and then act on.
		*/
		void SetAndUseFlagsL( TBitFlags16 aFlags );

    public: // Functions from CCoeControl
    
        /**
        * From CCoeControl  Handle key events. When a key event occurs, 
        *                   CONE calls this function for each control on the control stack, 
        *                   until one of them returns EKeyWasConsumed to indicate that it processed the key event.  
        * @param aKeyEvent  The key event.
        * @param aType      The type of the event: EEventKey, EEventKeyUp or EEventKeyDown.
        * @return           Indicates whether or not the key event was used by this control.
        */
	    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * From CCoeControl  Give the control a mimimum size. 
        * 
        * @return           The minimum size required by the control.
        */
	    IMPORT_C TSize MinimumSize();

        /**
        * From CCoeControl  Added to pass-through focus-loss warnings.
		*					if not ready, this will leave.
        * @return           Indicates whether or not the key event was used by this control.
        */
		void PrepareForFocusLossL();

        /**
        * From CCoeControl  Added to pass-through focus-loss warnings.
		*					if not ready, this will leave.
        * @return           Indicates whether or not the key event was used by this control.
        */
		void FocusChanged(TDrawNow aDrawNow);
        
        /**
        * From MEikEdwinObserver
        *
        * @param aEdwin     Editor who sent the event
        * @param aEventType Type of the event
        */
        IMPORT_C void HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType);

    public:// Functions from MEikEdwinSizeObserver

        /**
        * From MEikEdwinObserver
        *
        * @param aEdwin                 Editor who's size has changed
        * @param aEventType             Type of the size event
        * @param aDesirableEdwinSize    Desirable size of the edwin
        */
        IMPORT_C TBool HandleEdwinSizeEventL(CEikEdwin* aEdwin, TEdwinSizeEvent aEventType, TSize aDesirableEdwinSize);

    public:// Functions from MCoeControlObserver

        /**
        * From MCoeControlObserver
        * @param aControl   Control who caused the event
        * @param aEventType Type of the event
        */
        IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

	public:
		/**
        * @return Layout indication
		*
		* At the moment the layout is a good indication of the query type (PIN,number,etc)
		* The query dialog uses this information to determine query type in order to
		* process key events in a way dependent on the query type. These key events
		* can't be processes by the control directly because they involve actions only
		* the dialog can perform
		*/
		inline TInt QueryType() const { return iQueryType; } 

		/**
		* Return window layout depending on Layout 
		* Window layout is done by the dialog
		*/
		virtual TAknWindowLineLayout WindowLayout() const;
	
	public:// Functions from CCoeControl
        /**
        * From CCoeControl  Count number of controls contained in a compound control.  
        *  
        * @return           The number of component controls contained by this control.           
        */
	    TInt CountComponentControls() const;

        /**
        * From CCoeControl  Get the components of a compound control.
        *                   It returns one of the control's component controls, identified by aIndex.
        * @param anIndex    The index of the control to get.        
        * @return           The component control with an index of aIndex.
        */
        CCoeControl* ComponentControl(TInt anIndex) const;

	public:
		/**
		 * Manage indexes into LAF tables
		 */
		class TIndex 
		{	
		public:		
			TIndex(TInt aNumberOfPromptLines);	
		
		public:	
			TInt PromptLine() const;	
			
		public:	
			TInt DQPWindowTextsLine2(TInt aLineNum) const;	
			TInt PNWindow() const;	
			TInt PQDWindow(TInt aLineNum) const;	
			
		private:	
			void SelfTest() const;	

		private:	
			TInt  iNumberOfPromptLines;	
		};	

	protected:
		/**
        * From CCoeControl  Respond to size changed. This function is called by CONE whenever SetExtentL(), 
        *                   SetSizeL(), SetRectL(), SetCornerAndSizeL(), or SetExtentToWholeScreenL() 
        *                   are called on the control.   
        */
	    void SizeChanged();

        /**
        * From CCoeControl  Draw a control.  
        *
        * @param aRect      The region of the control to be redrawn.   
        */
        void Draw(const TRect& aRect) const;

        /**
        * From MObjectProvider
        */
        TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

		/**
        * Perform layout by calling SizeChanged 
        *   
        */
		void Layout();

	protected:
		/**
		 * Determine the line widths for the prompt, depends on layout
		 */
		virtual void SetLineWidthsL();

		/**
		 * After having read the query type from resource. This method is
		 * called in CostructFromResourceL()
		 *
		 * @see ConstructFromResourceL()
		 */
		virtual void ConstructQueryL(TResourceReader& aRes);

		/**
		 * Layout rectangle (shift up and left by margins)
		 */
		virtual TRect LayoutRect();

		/**
		 * Return the rect that is used by the dialog for layout
		 * This can be determined using LAF values and is equal to 
		 * TPoint(0,0) plus the control size plus the margins
		 */
		TRect DialogRect() const;

		/**
		 * Return the size of the dialog. This can be determined
		 * using LAF values and is equal to the control size plus
		 * the margins.
		 */
		TSize DialogSize() const;

	protected:
		/**
		 * Layout the query prompt
		 */
		virtual void LayoutPrompt(const TLayoutMethod& aLayoutM);

		/**
		 * Layout the image or the animation
		 */
		virtual void LayoutImageOrAnim(const TLayoutMethod& aLayoutM);
		
		/**
		 * Layout the text editor
		 */
		virtual void LayoutEditor(const TLayoutMethod& aLayoutM);

		/**
		 * Layout the editor frame
		 */
		virtual void LayoutEditorFrame(const TLayoutMethod& aLayoutM);

		/**
		 * Layout the editor state indicator icons
		 */
		virtual void LayoutEditorIndicator(const TLayoutMethod& aLayoutM);
	
	private:

		/**
		* Draw editor frame and shadows
		*/
		void DrawEditorFrame(CWindowGc& aGc,TRect& aRect) const;

		/**
		* This transfers CAknQueryControl's flags set by the dialog
		* 
		* @param flag pattern to set 
		*
		*/
		void SetFlags( TBitFlags16 aFlags );

		/** 
		* This acts on the Query control flags that are set from CAknQueryDialog
		*
		*/
		void DeployFlagsL();

		/**
		* Call CAknTextControl::ParseTextL
		*
		*/
		void DoSetPromptL();

    protected:
        /// Control for prompt text
        CAknTextControl*  iPrompt;
		/// Editor indicator icons 
        CAknQueryEditIndicator*  iEditIndicator;
        /// Edwin editor
        CEikEdwin*               iEdwin;
        /// Date editor
        CEikDateEditor*          iDateEdwin;
        /// Time editor
        CEikTimeEditor*          iTimeEdwin;
        /// Duration editor
        CEikDurationEditor*      iDurationEdwin;
        /// Secret editor
        CEikSecretEditor*        iSecretEd;
        /// Integer editor
		CAknIntegerEdwin*        iNumberEdwin; 
        /// Numeric secret editor
        CAknNumericSecretEditor* iPinEdwin;
		// Floating point editor
        CEikFloatingPointEditor* iFloatingPointEditor;
        // Image
        CEikImage*               iImage;
        /// Control id
        TInt                     iControl;
        // Layoutrect for Mfne
		TAknLayoutRect           iLayoutMfne;
        // Emergency call detector
		CAknEcsDetector*         iEcsDetector;
        // Emergency call observer
		TAknQueryEcsObserver*    iEcsObserver;
        // Flags for emergency call support and other things
		TBitFlags16              iFlags;
		TUint16					 iSpare_1; // padding
        // Animation
		CAknBitmapAnimation*     iAnimation;
        // Pointer to query control observer
	    MAknQueryControlObserver* iQueryControlObserver;
        // Query type
        TInt                      iQueryType;
        // Layout rect for editor's vertical shadow
		TAknLayoutRect            iEditorVerShadow;
        // Layout rect for editor's horizontal shadow
        TAknLayoutRect            iEditorHorShadow;
        // Layout rect for editor's frame
		TAknLayoutRect            iEditorFrame;
	
		TInt       iNumberOfEditorLines; ///Maximum number of lines in the editor

		TBool      iHasEditor;   //False for confirmation queries (default), 
								 //true for all other queries 

		CArrayFixFlat<TInt>* iLineWidths; ///Widths of prompt lines (in pixels)    
	};

#endif  
