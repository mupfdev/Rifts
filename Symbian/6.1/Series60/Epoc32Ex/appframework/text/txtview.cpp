// TXTVIEW.CPP
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#include "txtexamp.h"

#include <txtrich.h>

CViewControl::~CViewControl()
	{
	delete iTextView; // text view
	delete iLayout; // text layout
	delete iRichText; // contained text object
	delete iCharFormatLayer; // char format layer
	delete iParaFormatLayer; // para format layer
	delete iBitmap; // line cursor character bitmap
	}

void CViewControl::UpdateModelL()
	{
	// Create all constant literal descriptors used in this function, 
	// e.g. for message text

	_LIT(KText1, "To be, or not to be, that is the question; \
whether 'tis nobler in the mind to suffer the \
slings and arrows of outrageous fortune, or \
to stand against a sea of troubles, and by \
opposing end them."); 
	_LIT(KText4,"Format band set. Num formatted lines=%d");
	_LIT(KText5,"Format band unset. Num formatted lines=%d");
	_LIT(KPathAndFile,"\\system\\apps\\txtshell\\cursors.mbm");
	_LIT(KCDrive,"C:");
	_LIT(KZDrive,"Z:");
	_LIT(KStatus0,"Initialised - with grey fill colour");
	_LIT(KStatus1,"Added lots of text");
	_LIT(KStatus2,"Selected first paragraph");
	_LIT(KStatus3,"Formatted the selected text (and cancelled selection)");
	_LIT(KStatus6,"Set 20 pixel line cursor margin and 2 cursors");
	_LIT(KStatus7,"Reset the view rectangle - old wrapping still applies");
	_LIT(KStatus8,"Text wrapping set to new view rectangle");
	_LIT(KStatus9,"View rectangle and wrap width reset");
	_LIT(KStatus10,"Horizontal scroll left");
	_LIT(KStatus11,"Scrolling DOWN, blank space NOT scrolled");
	_LIT(KStatus12,"Back to top and horizontal scroll right");
	_LIT(KStatus13,"Reset();");
	_LIT(KStatusDefault,"(overshot!!)");

	
	switch (Phase())
		{
	case 0:
		{
		// Preparation for following cases:
		TCharFormat charFormat;
		TCharFormatMask charFormatMask;
		iUpdateModelDoesRedraw=ETrue; 
			// NextPhaseL() should call DrawNow() for the first case only
		// Create rich text object to be displayed in the text view
		iParaFormatLayer=CParaFormatLayer::NewL(); // required para format
		iCharFormatLayer=CCharFormatLayer::NewL(); // required char format
				// empty text objects
		iRichText=CRichText::NewL(iParaFormatLayer, iCharFormatLayer);
		// prerequisites for view - viewing rectangle
		iViewRect=Rect();
		iViewRect.Shrink(3,3);
		// context and device
		CWindowGc& gc=SystemGc(); // get graphics context
		CBitmapDevice* device=(CBitmapDevice*) (gc.Device()); // device
		// Construct the layout object used by the text view,
		// specifying wrap width (= width of viewing rectangle)
		iLayout=CTextLayout::NewL(iRichText,iViewRect.Width());
		// Construct text view
		iTextView=CTextView::NewL(iLayout, iViewRect,
			device,
			device,
			&Window(),
			&iCoeEnv->RootWin(), // window group, needed for cursor
			&iCoeEnv->WsSession()
			); // new view
		// Set paragraph fill color and font height.
		// For visibility, set font height to 10 point.
		charFormatMask.SetAttrib(EAttFontHeight); 
			// height attribute only is relevant
		charFormat.iFontSpec.iHeight=200; // set to 10 point (200 twips)
		iRichText->ApplyCharFormatL(charFormat,charFormatMask,0,0);
		// Apply grey paragraph fill colour 
		CParaFormat* paraFormat=CParaFormat::NewL();
		TParaFormatMask paraFormatMask;
		paraFormat->iFillColor=TRgb(204,204,204); // Light grey
		paraFormatMask.SetAttrib(EAttFillColor);
			// fill colour attribute only is relevant
		iRichText->ApplyParaFormatL(paraFormat,paraFormatMask,0,0);
		iTextView->FormatTextL();
		iFormObserver->NotifyStatus(KStatus0);
		delete paraFormat;
		break;
		}
	case 1:
		{
		// insert lots of text
		for (TInt count=0;count<5;count++) // insert a paragraph, *5
			{	
			iRichText->InsertL(iRichText->DocumentLength(),KText1); // text
			iRichText->InsertL(iRichText->DocumentLength(),
				CEditableText::EParagraphDelimiter); // end para
			};
		TCursorSelection selection(0, iRichText->DocumentLength());
			// start and length of the inserted block
		iTextView->HandleInsertDeleteL(selection, 0); 
			// zero deleted characters 
		iFormObserver->NotifyStatus(KStatus1);
		break;
		}
	case 2:
		{
		// Select the first paragraph
		TInt pos=1;
		TUint scanMask=CPlainText::EScanToUnitEnd;
		iRichText->ScanParas(pos,scanMask);
			// get end position of current para
		// move cursor to end of para and select it
		iTextView->SetDocPosL(pos,ETrue); // ETrue = select the range
		iFormObserver->NotifyStatus(KStatus2);
		break;
		}
	case 3:
		{
		// Apply italics to the selected region
		TCursorSelection cursorSelection;
		TCharFormat charFormat;
		TCharFormatMask charFormatMask;
		// Set italics
		charFormat.iFontSpec.iFontStyle.SetPosture(EPostureItalic); 
		charFormatMask.SetAttrib(EAttFontPosture); 
			// font posture attribute only is relevant
		cursorSelection=iTextView->Selection(); // get range of selection
		TInt lowerPos=cursorSelection.LowerPos();
		TInt length=cursorSelection.Length();
		// Apply formatting to range
		iRichText->ApplyCharFormatL(charFormat,charFormatMask,lowerPos,length);
		iTextView->HandleRangeFormatChangeL(cursorSelection); // reformat from here
		iTextView->CancelSelectionL(); // remove selection and redraw
		iFormObserver->NotifyStatus(KStatus3);
		break;
		}
	case 4:
		{
		TBuf<80> message;
		// Set formatting to the band only and display the number of formatted lines.
		iLayout->SetAmountToFormat(CTextLayout::EFFormatBand);
		iTextView->HandleGlobalChangeL(); // global layout change 
		message.Format(KText4,iLayout->NumFormattedLines());
		iFormObserver->NotifyStatus(message);
		break;
		}
	case 5:
		{
		TBuf<80> message;
		// Set formatting to the whole document, then display the number of 
		// formatted lines.
		iLayout->SetAmountToFormat(CTextLayout::EFFormatAllText);
		iTextView->HandleGlobalChangeL(); // global layout change 
		message.Format(KText5,iLayout->NumFormattedLines());
		iFormObserver->NotifyStatus(message);
		break;
		}
	case 6:
		{
		// Set line cursor margin and line cursor bitmap
		iTextView->SetMarginWidths(0,20); // zero label margin, 20 pixel line cursor margin
		iTextView->DrawL(iViewRect); // update the view (SetMarginWidths() doesn't redraw)
		// Load in bitmap to represent line cursor.
		iBitmap=new(ELeave) CFbsBitmap();
		TBufC<40> pathandfile(KPathAndFile);
		TParse    bitmapFileName;
		TBufC<2>  c_drive(KCDrive);
		TBufC<2>  z_drive(KZDrive);

	    bitmapFileName.Set(pathandfile,&c_drive,NULL);
		
		if (iBitmap->Load(bitmapFileName.FullName()))
			{
			bitmapFileName.Set(pathandfile,&z_drive,NULL);
			iBitmap->Load(bitmapFileName.FullName());
			iTextView->SetLineCursorBitmap(iBitmap);
			iTextView->SetCursorVisibilityL(TCursor::EFCursorVisible,
				TCursor::EFCursorFlashing); 
			// both cursors now visible - flashing text cursor
			iFormObserver->NotifyStatus(KStatus6);
			}
		break;
		}
	case 7:
		{
		// Reset the view rectangle.
		// Before doing this, clear the existing one,
		// (the view should really be implemented as a control, in a container control,
		// and then the background would get cleared nicely by the container).
		ActivateGc();
		SystemGc().Clear(iViewRect);
		DeactivateGc();
		// Shrink the view rectangle by 40 pixels both directions
		iViewRect.Shrink(40,40);
		iTextView->SetViewRect(iViewRect);
		iTextView->DrawL(iViewRect); // Redraw the completely revamped view 
			// (SetViewRect() does not do a redraw)
		iFormObserver->NotifyStatus(KStatus7);
		break;
		}
	case 8:
		{
		// Wrap text to new view rectangle.
		// New wrap width = new view rect width minus total margin width.
		// First calculate the total margin width.
		TInt labelMarginWidth;
		TInt lineCursorMarginWidth;
		iTextView->MarginWidths(labelMarginWidth,lineCursorMarginWidth);
		iLayout->SetWrapWidth(iViewRect.Width()-(labelMarginWidth+lineCursorMarginWidth));
		iLayout->ForceNoWrapping(EFalse); // Ensure wrapping on
		iTextView->HandleGlobalChangeL();
		iFormObserver->NotifyStatus(KStatus8);
		break;
		}
	case 9:
		{
		// Reset view rectangle back to old dimensions and set wrapping
		// width accordingly
		TInt labelMarginWidth;
		TInt lineCursorMarginWidth;
		iTextView->MarginWidths(labelMarginWidth,lineCursorMarginWidth);
		iViewRect.Grow(40,40);
			// Increase view rectangle by 40 pixels both directions
		iTextView->SetViewRect(iViewRect);
		iLayout->SetWrapWidth(iViewRect.Width()-(labelMarginWidth+lineCursorMarginWidth));
		iTextView->HandleGlobalChangeL();
		iFormObserver->NotifyStatus((KStatus9));
		break;
		}
	case 10:
		// Horizontal scrolling
		iTextView->SetHorizontalScrollJump(40); // scroll jump is 40 pixels
		iTextView->ScrollDisplayL(TCursorPosition::EFLeft,CTextLayout::EFAllowScrollingBlankSpace); 
			// scroll to the left (scrolling blank space is allowed)
		iFormObserver->NotifyStatus(KStatus10);
		break;
	case 11:
		{
		// Vertical scrolling
		iFormObserver->NotifyStatus(KStatus11);
		TInt pixelsScrolled;
		// Scroll down to the bottom of the document, 
		do
			pixelsScrolled=iTextView->ScrollDisplayL(TCursorPosition::EFLineDown,
				CTextLayout::EFDisallowScrollingBlankSpace);
		while (pixelsScrolled);
		break;
		}
	case 12:
		{
		// Horizontal scroll back to left margin and to top of doc
		iFormObserver->NotifyStatus(KStatus12);
		TInt pixelsScrolled;
		do
			pixelsScrolled=iTextView->ScrollDisplayL(TCursorPosition::EFLineUp);		
		while (pixelsScrolled);
		iTextView->ScrollDisplayL(TCursorPosition::EFRight); 
			// scroll right (horizontal scroll jump value=40 pixels)
		break;
		}
	case 13:
		{
		// Reset document. 
		iRichText->Reset(); // change whole document!
		iTextView->FormatTextL(); // so format the whole lot
		iTextView->DrawL(iViewRect); // and draw it afresh
		iFormObserver->NotifyStatus(KStatus13);
		break;
		}
	default:
		iFormObserver->NotifyStatus(KStatusDefault);
		break;
		}
	}

void CViewControl::Draw(const TRect& aRect) const
	{
	// draw surround
	CGraphicsContext& gc=SystemGc(); // context to draw into
	TRect rect=Rect(); // screen boundary
	gc.DrawRect(rect); // outline screen boundary
	rect.Shrink(1,1);
	gc.SetPenColor(KRgbWhite);
	gc.DrawRect(rect);
	rect.Shrink(1,1);
	gc.SetPenColor(KRgbBlack);
	gc.DrawRect(rect);
	// draw editable text - will work unless OOM
	TInt err;
	TRAP(err,iTextView->DrawL(aRect));
	}
