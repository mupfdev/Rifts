/*
* ============================================================================
*  Name     : AknPopupLayout.h
*  Part of  : Avkon
*
*  Description:
*     Layouts from pop-up windows. Mostly used for implementing list queries,
*     options menus, grouped soft notifications and other popup windows.
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNPOPUPLAYOUT__
#define __AKNPOPUPLAYOUT__

#include <aknutils.h>
#include <e32std.h>

struct TAknPopupWindowLayoutDef;
class CEikListBox;
class CAknPopupHeadingPane;
class CWindowGc;
class CCoeControl;
class CEikonEnv;

const TInt EAknPopupLayoutsDynamic = 0x80;

/** The purpose of AknPopupLayouts class is to provide layouts
 *  for popup windows described in European Avkon LAF
 *  document.
 *  
 *  Applications should not use this class except for building custom
 *  layouts. The default layouts looks usually much nicer.
 *
 *  Applications cannot extend this class to add new layouts, but they
 *  can override virtual methods from the class that call methods from
 *  these classes.
 *
 *  These classes are used by
 *    1) List queries CAknListQueryDialog (aknquerydialog.cpp)
 *    2) options menus CEikMenuPane and CEikMenuBar (uikon/coctlsrc/eikmenup.cpp)
 *    3) popup windows CAknPopupList (aknpopup.cpp)
 *    4) grouped soft notifications
 *
 */

class AknPopupLayouts
    {
public: 
    /** 
     *	If you ever want to add new items here, do not -- instead derive from
     * popuplist or list query and override SetupWindowLayout().
     * (or if you can modify avkon, then add them here to make it easier for apps to use
     * the new layout..)
     * There's example at aknGMSstylegrid.cpp how to make new popup window without avkon
     * modifications.
     */
    enum TAknPopupLayouts
	{
	// these are the standard popup windows
	EMenuWindow, // CAknSinglePopupMenuStyleListBox
	EMenuGraphicWindow, // CAknSingleGraphicPopupMenuStyleListBox
	EMenuGraphicHeadingWindow, // CAknSingleGraphicHeadingPopupMenuStyleListBox, CAknSingleHeadingPopupMenuStyleListBox
	EMenuDoubleWindow, // CAknDoublePopupMenuStyleListBox
	EMenuDoubleLargeGraphicWindow, // CAknDoubleLargeGraphicPopupMenuStyleListBox
	EPopupSNotePopupWindow,
	
	// these are versions of the popup windows which does not resize
	// themselves if you insert items. (they're full size from the
	// beginning)
	EDynMenuWindow = EMenuWindow + 0x80,
	EDynMenuGraphicWindow,
	EDynMenuGraphicHeadingWindow,
	EDynMenuDoubleWindow,
	EDynMenuDoubleLargeGraphicWindow,
	};

public: // interface for controls
    

   /** 
    * Implementation of SizeChanged() for a popup window control with a list inside
    *
    * This method calls setrect() on heading, listbox and window owning control
    * and expects the window owning control has listbox and heading in
    * its componentcontrols...
    */
    IMPORT_C static void HandleSizeChanged(TAknPopupWindowLayoutDef &aDef, 
				  TAknPopupLayouts aLayout,
				  CAknPopupHeadingPane *aHeadingOrNull,
				  CEikListBox *aListBox,
				  CCoeControl *aWindowOwningControl);
   /** 
    * Implementation of Draw() for a popup window control with a list inside
    */    
    IMPORT_C static void HandleDraw(CEikonEnv* aEikEnv,
			   CWindowGc &aGc,
			   const TAknPopupWindowLayoutDef &aDef, 
			   CEikListBox *aListBox,
			   CAknPopupHeadingPane *aHeadingOrNull);


public: // interface for adding heading
   /** 
    * Adds a heading to popup window
    */
    IMPORT_C static void ModifyWindowGraphicForHeading(TAknPopupWindowLayoutDef &aDef);

public: // The implementation of different popup window styles.
   /** 
    * Calculates layout of popup_menu_window from LAF specification
    */
    IMPORT_C static void CalcPopupMenuWindow(TAknPopupWindowLayoutDef &aDef, 
					     TRect aClientRect, 
					     TInt aNumberOfLinesInListBox);
   /** 
    * Calculates layout of popup_menu_graphic_window from LAF specification
    */
    IMPORT_C static void CalcPopupMenuGraphicWindow(TAknPopupWindowLayoutDef &aDef,
						    TRect aClientRect, 
						    TInt aNumberOfLinesInListBox);
   /** 
    * Calculates layout of popup_menu_graphic_heading_window from LAF specification
    */
    IMPORT_C static void CalcPopupMenuGraphicHeadingWindow(TAknPopupWindowLayoutDef &aDef,
							   TRect aClientRect, 
							   TInt aNumberOfLinesInListBox);
   /** 
    * Calculates layout of popup_menu_double_window from LAF specification
    */
    IMPORT_C static void CalcPopupMenuDoubleWindow(TAknPopupWindowLayoutDef &aDef,
						   TRect aClientRect, 
						   TInt aNumberOfLinesInListBox);
   /** 
    * Calculates layout of popup_menu_double_large_graphic_window from LAF specification
    */
    IMPORT_C static void CalcPopupMenuDoubleLargeGraphicWindow(TAknPopupWindowLayoutDef &aDef,
							       TRect aClientRect, 
							       TInt aNumberOfLinesInListBox);
   /** 
    * Calculates layout of popup_snote_window from LAF specification
    */
    IMPORT_C static void CalcPopupSNoteGroupWindow(TAknPopupWindowLayoutDef &aDef, 
						   TRect aClientRect, 
						   TInt aNumberOfLinesInListBox);

    /**
     * Setup a border for the window
     */
    IMPORT_C static void SetupMenuPopupWindow(TAknPopupWindowLayoutDef &aDef, 
					      TInt aNumberOfLinesInListBox, 
					      TBool aHeading);
    /**
     * Setup a border for the window
     */
    IMPORT_C static void SetupPopupMenuGraphicWindow(TAknPopupWindowLayoutDef &aDef, 
						     TInt aNumberOfLinesInListBox,
						     TBool aHeading);
    /**
     * Setup a border for the window
     */
    IMPORT_C static void SetupPopupMenuGraphicHeadingWindow(TAknPopupWindowLayoutDef &aDef, 
							    TInt aNumberOfLinesInListBox, 
							    TBool aHeading);
    /**
     * Setup a border for the window
     */
    IMPORT_C static void SetupPopupMenuDoubleWindow(TAknPopupWindowLayoutDef &aDef, 
						    TInt aNumberOfLinesInListBox, 
						    TBool aHeading);    
    /**
     * Setup a border for the window
     */
    IMPORT_C static void SetupImageSelectionMenuPopupWindow(TAknPopupWindowLayoutDef &aDef,
							    TInt num, 
							    TBool heading);
    /**
     * Setup a border for the window
     */
    IMPORT_C static void SetupPopupSNoteGroupWindow(TAknPopupWindowLayoutDef &aDef,
						    TInt num,
						    TBool heading);

    
public: // interface to setup listbox and popup heading pane. (used by HandleSizeChanged)
    IMPORT_C static void HandleSizeAndPositionOfComponents(const TAknPopupWindowLayoutDef &aDef, 
						  CCoeControl *aContentInsidePopup,
						  CAknPopupHeadingPane *aHeadingOrNull);
    IMPORT_C static void SetupDefaults(TAknPopupWindowLayoutDef &aDef);
public: // Utilities
    /**
     * Access to different coordinate transformations needed to setup popup windows
     */
    IMPORT_C static TRect WindowRect(TAknPopupWindowLayoutDef &aDef);
    /**
     * Access to different coordinate transformations needed to setup popup windows
     */
    IMPORT_C static TRect MenuRect(TAknPopupWindowLayoutDef &aDef);
    /**
     * Check integer range
     */
    IMPORT_C static void CheckRange(TInt &aValue, TInt aMin, TInt aMax);
    /**
     * Helper for building popup window layout
     */
    IMPORT_C static void MenuPopupWindowGraphics(TAknPopupWindowLayoutDef &aDef);
    };

/** TAknPopupWindowLayoutDef
 * collects all LAF specification lines that are needed for popup windows
 *
 */

struct TAknPopupWindowLayoutDef
    {
    EXPORT_C TAknPopupWindowLayoutDef();
    TAknLayoutRect iListRect;
    TAknLayoutRect iHeadingRect;
    
    TAknLayoutRect iCover;
    TAknLayoutRect iSecond;
    TAknLayoutRect iFirst;
    TAknLayoutRect iOutline;
    TAknLayoutRect iInside;
    
    TAknLayoutRect iVertLineExt1;
    TAknLayoutRect iVertLineExt2;

    // the window position relative to clientrect
    TRect iWindowRect;

    // popup_menu_window position relative to iWindowPos
    TPoint iPopupMenuWindowOffset;
    TInt iMaximumHeight;
    };

#endif



