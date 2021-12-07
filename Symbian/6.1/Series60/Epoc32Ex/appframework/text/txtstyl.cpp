// TXTSTYL.CPP
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#include "txtexamp.h"

#include <txtrich.h>

CStyleControl::~CStyleControl()
	{
	delete iTextView; // text view
	delete iLayout; // layout
	delete iRichText; // contained text object
	delete iNormalCharFormatLayer; // char format layer
	delete iNormalParaFormatLayer; // para format layer
	}

void CStyleControl::CreateNormal()
	{
	// Create the "Normal" style 
	// = the global format layers upon which all styles will be based.
	// Use default formatting except for an increased left margin and line spacing.
	CParaFormat* paraFormat=CParaFormat::NewLC();
	TParaFormatMask paraFormatMask;
	paraFormat->iLeftMarginInTwips=360;
	paraFormatMask.SetAttrib(EAttLeftMargin);
	paraFormat->iLineSpacingInTwips=300;
	paraFormatMask.SetAttrib(EAttLineSpacing);
	// Create the normal (global) style
	iNormalParaFormatLayer=CParaFormatLayer::NewL(paraFormat,paraFormatMask);
	CleanupStack::PopAndDestroy();  // paraFormat
	TCharFormat charFormat;
	TCharFormatMask charFormatMask;
	charFormatMask.SetAttrib(EAttFontHeight);
	iNormalCharFormatLayer=CCharFormatLayer::NewL(charFormat,charFormatMask); 
	}

void CStyleControl::CreateStyles()
	{
	// Create two new styles, with names "Warning" and "ListBullet", 
	// add some appropriate formatting and append them to a style list.
	_LIT(KStyle,"Warning");
	_LIT(KStyleTwo,"ListBullet");
	CParaFormat* paraFormat=CParaFormat::NewLC();
	TParaFormatMask paraFormatMask;
	TCharFormat charFormat;
	TCharFormatMask charFormatMask;
	// Style 1 - "Warning style"
	iStyleOne=CParagraphStyle::NewL(
		*iNormalParaFormatLayer,*iNormalCharFormatLayer); // Base it on the "normal" layers

	// Enclose text in a paragraph border
	TParaBorder paraBorder;
	paraBorder.iLineStyle=TParaBorder::ESolid;
	paraBorder.iThickness=4; // border width
	paraBorder.iColor=KRgbGray; // set border color to gray
	paraBorder.iAutoColor=EFalse; // iColor overrides text color
	paraFormat->SetParaBorderL(CParaFormat::EParaBorderTop,paraBorder);
	paraFormat->SetParaBorderL(CParaFormat::EParaBorderBottom,paraBorder);
	paraFormat->SetParaBorderL(CParaFormat::EParaBorderLeft,paraBorder);
	paraFormat->SetParaBorderL(CParaFormat::EParaBorderRight,paraBorder);
	paraFormatMask.SetAttrib(EAttTopBorder);
	paraFormatMask.SetAttrib(EAttBottomBorder);
	paraFormatMask.SetAttrib(EAttRightBorder);
	paraFormatMask.SetAttrib(EAttLeftBorder);
	iStyleOne->SetL(paraFormat,paraFormatMask); 
	// Make it bold.
	// First, get handle to style 1's character format layer
	CCharFormatLayer* charStyleFormatLayer = iStyleOne->CharFormatLayer(); 
	charFormat.iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightBold);
	charFormatMask.SetAttrib(EAttFontStrokeWeight);
	// Set the style's character format layer
	charStyleFormatLayer->SetL(charFormat,charFormatMask);
	// Finally, set its name to "Warning"
	iStyleOne->iName=KStyle;

	// Style 2 - "listbullet"
	paraFormat->Strip(); // Clear paraformat ready for new style
	paraFormatMask.ClearAll(); // Clear mask
	iStyleTwo=CParagraphStyle::NewL(
		*iNormalParaFormatLayer,*iNormalCharFormatLayer);  // Base it on the "normal" layers
	paraFormat->iBullet=new(ELeave)TBullet;	
	paraFormat->iBullet->iHeightInTwips=480; // Size of bullet point character=480 twips
	paraFormat->iBullet->iHangingIndent=ETrue; // Indent the rest of the paragraph from the bullet
	paraFormatMask.SetAttrib(EAttBullet);
	iStyleTwo->SetL(paraFormat,paraFormatMask); 
	// Finally, set its name to "ListBullet"
	iStyleTwo->iName=KStyleTwo;

	// Create style table and insert styles.
	iStyleList=CStyleList::NewL();
	RParagraphStyleInfo info1(iStyleOne);
	RParagraphStyleInfo info2(iStyleTwo);
	iStyleList->AppendL(&info1);
	iStyleList->AppendL(&info2);
	// Create rich text object based on normal layers, with the style table.
	iRichText=CRichText::NewL(iNormalParaFormatLayer,iNormalCharFormatLayer,*iStyleList);
	CleanupStack::PopAndDestroy();  // paraFormat
}

void CStyleControl::UpdateModelL()
	{
	// Create all constant literal descriptors used in this function, 
	// e.g. for message text
	_LIT(KText1,"Some text using normal style");
	_LIT(KText2,"Text in warning style - based on normal");
	_LIT(KText3,"Text in list bullet style");
	_LIT(KText4,"Some more text in list bullet style");
	_LIT(KText5,"Some text in italics");
	_LIT(KStatus0,"Initialised styles and view");
	_LIT(KStatus1,"Normal");
	_LIT(KStatus2,"Warning style");
	_LIT(KStatus3,"List bullet style");
	_LIT(KStatus4,"Character and paragraph formatting applied to styled text");
	_LIT(KStatus5,"All specific formatting removed from third paragraph");
	_LIT(KStatus6,"Inserted some normal text with specific formatting");
	_LIT(KStatus7,"Applied a style (warning) to text, retaining specific formatting");
	_LIT(KStatus8,"Reset();");
	_LIT(KStatusDefault,"(overshot!!)");

	switch (Phase())
		{
	// Apply paragraph styles
	case 0:
		{
	 	// Create the global format layers on which all styles are based.
		CreateNormal();	
		// Create text object and styles.
		CreateStyles();	
		// Prerequisites for view - viewing rectangle
		iViewRect=Rect();
		iViewRect.Shrink(3,3);
		// context and device
		CWindowGc& gc=SystemGc(); // get graphics context
		CBitmapDevice* device=(CBitmapDevice*) (gc.Device()); // device
		// layout
		iLayout=CTextLayout::NewL(iRichText,iViewRect.Width()); // new layout
			// construct layout, giving width of viewing rectangle
		// text view
		iTextView=CTextView::NewL(iLayout, iViewRect,
			device,
			device,
			&Window(),
			0, // no window group
			&iCoeEnv->WsSession()
			);
		iFormObserver->NotifyStatus(KStatus0);
		break;
		}
	case 1:
		// Insert a paragraph using the "normal" (default) formatting.
		iRichText->InsertL(0,KText1);
		iRichText->InsertL(iRichText->DocumentLength(),
			CEditableText::EParagraphDelimiter); 
		iFormObserver->NotifyStatus(KStatus1);
		break;
	case 2:
		{
		// Insert a paragraph in "warning" style
		TInt length;
		TInt startPos;
   		iRichText->InsertL(iRichText->DocumentLength(),KText2);
		iRichText->InsertL(iRichText->DocumentLength(),
			CEditableText::EParagraphDelimiter); 
		// Get start position of second paragraph
		startPos=iRichText->CharPosOfParagraph(length,1); // Not interested in length
		// Apply warning style to second paragraph - single character is enough
		iRichText->ApplyParagraphStyleL(*iStyleList->At(0).iStyle,startPos,1,
			CParagraphStyle::ERetainAllSpecificFormats);
		iFormObserver->NotifyStatus(KStatus2);
		break;
		}
	case 3:
	// Insert two paragraphs in list bullet style
		{
		TInt length;
		TInt startPos;
		// Insert some text in bullet point style
		iRichText->InsertL(iRichText->DocumentLength(),KText3);
		iRichText->InsertL(iRichText->DocumentLength(),
			CEditableText::EParagraphDelimiter); 
				// end para
		iRichText->InsertL(iRichText->DocumentLength(),KText4);
		iRichText->InsertL(iRichText->DocumentLength(),
			CEditableText::EParagraphDelimiter);
				// end para
		// Get start position and length of third paragraph
		startPos=iRichText->CharPosOfParagraph(length,2); // Interested in length
		// Apply list bullet style to 3rd and 4th paragraphs, 
		// from start of para 2, for length of para2 + 1 characters.
		iRichText->ApplyParagraphStyleL(*iStyleList->At(1).iStyle,startPos,length+1,
			CParagraphStyle::ERetainAllSpecificFormats);
		iFormObserver->NotifyStatus(KStatus3);
		break;
		}
	case 4:
		// Apply character and paragraph formatting 
		// (underlining and right alignment) over a style
		{
		TInt startPos, length;
		// Get start pos and length of third paragraph
		startPos=iRichText->CharPosOfParagraph(length,2); 
		// set underlining
		TCharFormat charFormat;
		TCharFormatMask charFormatMask;
		charFormat.iFontPresentation.iUnderline=EUnderlineOn; 
		charFormatMask.SetAttrib(EAttFontUnderline); // interested in underlining
		// Apply character formatting, from start of para for para length 
		// minus one char (don't want trailing paragraph delimiter underlined)
		iRichText->ApplyCharFormatL(charFormat, charFormatMask,startPos,length-1);
		CParaFormat* paraFormat=CParaFormat::NewL();
		TParaFormatMask paraFormatMask;
		paraFormat->iHorizontalAlignment=CParaFormat::ERightAlign; 
		paraFormatMask.SetAttrib(EAttAlignment);
		// Apply right alignment to first paragraph. A single character is enough
		iRichText->ApplyParaFormatL(paraFormat, paraFormatMask,startPos,1);
		iFormObserver->NotifyStatus(KStatus4);
		delete paraFormat;
		break;
		}
	case 5:
		// Remove all specific formatting from third para
		{
		TInt startPos, length;
		startPos=iRichText->CharPosOfParagraph(length,2); 
		// Remove all specific character formatting from the paragraph 
		iRichText->RemoveSpecificCharFormatL(startPos,length);
		// Remove all specific para formatting from the paragraph
		iRichText->RemoveSpecificParaFormatL(startPos,2);
		iFormObserver->NotifyStatus(KStatus5);
		break;
		}
	case 6:
		// Insert text in italics at the end of the document
		{
		TCharFormat charFormat;
		TCharFormatMask charFormatMask;
		charFormat.iFontSpec.iFontStyle.SetPosture(EPostureItalic);	
		charFormatMask.SetAttrib(EAttFontPosture); // interested in italic
		// Set formatting for all text inserted at this position.
		iRichText->SetInsertCharFormatL(charFormat,charFormatMask,iRichText->DocumentLength());
		iRichText->InsertL(iRichText->DocumentLength(),KText5);
		iRichText->CancelInsertCharFormat(); // "Insert pending" state cancelled
		iRichText->InsertL(iRichText->DocumentLength(),
			CEditableText::EParagraphDelimiter); // add a para delimiter at end of paragraph
		iFormObserver->NotifyStatus(KStatus6);
		break;
		}
	case 7:
		{
		// Apply a style to text added in previous case; retain all its specific formatting.
		TInt startPos, length;
		// Get any document position in the 5th paragraph. Not interested in length.
		startPos=iRichText->CharPosOfParagraph(length,4);
		iRichText->ApplyParagraphStyleL(*iStyleList->At(0).iStyle,startPos,1,
			CParagraphStyle::ERetainAllSpecificFormats);
		iFormObserver->NotifyStatus(KStatus7);
		break;
		}
	case 8:
		//reset document
		iRichText->Reset();
		// message to say what we did
		iFormObserver->NotifyStatus(KStatus8);
		break;
	default:
		iFormObserver->NotifyStatus(KStatusDefault);
		break;
		}
	}

void CStyleControl::Draw(const TRect& aRect) const
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
	TRAP(err,iTextView->FormatTextL());
	if (err) return;
	TRAP(err,iTextView->DrawL(aRect));
	}

