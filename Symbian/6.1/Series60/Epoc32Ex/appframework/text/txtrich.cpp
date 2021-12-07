// TXTRICH.CPP
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#include "txtexamp.h"

#include <txtrich.h>

CRichControl::~CRichControl()
	{
	delete iTextView; // text view
	delete iLayout; // text layout
	delete iRichText; // contained text object
	delete iCharFormatLayer; // character format layer
	delete iParaFormatLayer; // and para format layer
	}


void CRichControl::UpdateModelL()
	{
	// Create all constant literal descriptors used in this function, 
	// e.g. for message text
	_LIT(KHamletSpeech, "To be, or not to be, that is the question; \
whether 'tis nobler in the mind to suffer the \
slings and arrows of outrageous fortune, or \
to stand against a sea of troubles, and by \
opposing end them."); 
	_LIT(KPath,"C:\\richtxt.dat");
	_LIT(KText1,"Default rich text. ");
	_LIT(KText2,"Much larger rich text.");
	_LIT(KText5,"New text has preserved formatting at insertion point. ");
	_LIT(KText7,"New text has lost formatting at insertion point. ");
	_LIT(KStatus0,"Initialised rich text object and text view");
	_LIT(KStatus1,"InsertL() at position zero");
	_LIT(KStatus2,"Inserted text with specific formatting applied");
	_LIT(KStatus3,"Underlining applied to part of paragraph");
	_LIT(KStatus4,"Deleted text, but preserved formatting ...");
	_LIT(KStatus5,"... and inserted with same format");
	_LIT(KStatus6,"Deleted text and forgot about formatting ...");
	_LIT(KStatus7,"... and inserted with format before new text");
	_LIT(KStatus8,"Added 2 new paragraphs with default formatting");
	_LIT(KStatus9,"Set alignment for second paragraph");
	_LIT(KStatus10,"Used StoreL() to store rich text and components");
	_LIT(KStatus12,"Used RestoreL() to restore rich text and components");
	_LIT(KStatusReset,"Reset();");
	_LIT(KStatusDefault,"(overshot!!)");

	TBufC<28>   name(KPath);

	switch (Phase())
		{
	case 0:
		{
		// Create text object, text view and layout.
		iParaFormatLayer=CParaFormatLayer::NewL(); // required para format layer
		iCharFormatLayer=CCharFormatLayer::NewL(); // required char format layer
		// Create an empty rich text object
		iRichText=CRichText::NewL(iParaFormatLayer, iCharFormatLayer);
		// prerequisites for view - viewing rectangle
		iViewRect=Rect();
		iViewRect.Shrink(3,3);
		// context and device
		CWindowGc& gc=SystemGc(); // get graphics context
		CBitmapDevice *device=(CBitmapDevice*) (gc.Device()); // device
		// Create the text layout, (required by text view),
		// with the text object and a wrap width (=width of view rect)
		iLayout=CTextLayout::NewL(iRichText,iViewRect.Width());
		// Create text view
		iTextView=CTextView::NewL(iLayout, iViewRect,
				device,
				device,
				&Window(),
				0, // no window group
				&iCoeEnv->WsSession()
				); // new view
		// message to say what we did
		iFormObserver->NotifyStatus(KStatus0);
		break;
		}
	case 1:
		// Insert some text
		iRichText->InsertL(0,KText1);
		iFormObserver->NotifyStatus(KStatus1);
		break;
	case 2:
		// Insert some more text with specific formatting
		{
		TCharFormat charFormat;
		TCharFormatMask charFormatMask;
		charFormatMask.SetAttrib(EAttFontHeight); // interested in font height
		charFormat.iFontSpec.iHeight=480; // (in twips) increase it from default to 1/3 inch
		TInt pos=iRichText->DocumentLength(); // insertion position = end of doc
		iRichText->SetInsertCharFormatL(charFormat, charFormatMask,pos);
			// Set formatting, when inserting at this position
		iRichText->InsertL(pos,KText2); // Insert text at this position
		iRichText->CancelInsertCharFormat(); // Cancel "insert pending" state
			// This is necessary before inserting anywhere else
		iFormObserver->NotifyStatus(KStatus2);
		break;
		}
	case 3:
		{
		// Apply underlining to text which uses a mixture of formatting.
		TCharFormat charFormat;
		TCharFormatMask charFormatMask;
		charFormatMask.SetAttrib(EAttFontUnderline); // interested in underline
		charFormat.iFontPresentation.iUnderline=EUnderlineOn; // set it on
		iRichText->ApplyCharFormatL(charFormat, charFormatMask,13,10);
				// apply this character formatting, from position 13, 10 characters
		iFormObserver->NotifyStatus(KStatus3);
		break;
		}
	case 4:
		// delete text, then insert new text at same point to 
		// demonstrate preserving the deleted text's formatting.
		iRichText->DelSetInsertCharFormatL(19,(iRichText->DocumentLength()-19));
			// delete from pos 19, for rest of document; retain formatting at pos 19
		iFormObserver->NotifyStatus(KStatus4);
		break;
	case 5:
		// ... and then insert with same format
		iRichText->InsertL(19,KText5);
			// inserted with old formatting
		iRichText->CancelInsertCharFormat(); // must cancel before inserting elsewhere
		iFormObserver->NotifyStatus(KStatus5);
		break;
	case 6:
		// delete some text ... 
		iRichText->DeleteL(19,(iRichText->DocumentLength()-19));
			// DeleteL() deletes, and forgets formatting
		iFormObserver->NotifyStatus(KStatus6);
		break;
	case 7:
		// ... then insert new text at that point to 
		// demonstrate how DeleteL() differs from DelSetInsertCharFormatL(). 
		iRichText->InsertL(19,KText7);
			// insert, inheriting current formatting from char before 10
			// (no need to cancel anything!)
		iFormObserver->NotifyStatus(KStatus7);
		break;
	case 8:
		{
		// Rich text paragraph formatting.
		// Insert another 2 paragraphs using default formatting.
		// First remove specific formatting from final paragraph delimiter,
		// otherwise new paragraphs would pick up this formatting.
		iRichText->RemoveSpecificCharFormatL(iRichText->DocumentLength()-1,1);
		iRichText->InsertL(iRichText->DocumentLength(),
			CEditableText::EParagraphDelimiter); // new para
		for (TInt count=0;count<2;count++) // insert lots of text, twice over
			{	
			iRichText->InsertL(iRichText->DocumentLength(),KHamletSpeech); 
			iRichText->InsertL(iRichText->DocumentLength(),
				CEditableText::EParagraphDelimiter); // end para
			};
		iFormObserver->NotifyStatus(KStatus8);
		break;
		}
	case 9:
		{
		CParaFormat* paraFormat=CParaFormat::NewLC();
		TParaFormatMask paraFormatMask;
		// make para 1 right-aligned (numbering starts at 0)
		TInt pos, length;
		paraFormatMask.SetAttrib(EAttAlignment); // interested in alignment
		paraFormat->iHorizontalAlignment=CParaFormat::ERightAlign; // right-align
		pos=iRichText->CharPosOfParagraph(length,1); // start of para 2
		iRichText->ApplyParaFormatL(paraFormat,paraFormatMask,pos,1);
			// apply format to entire para - even 1 char will do
		iFormObserver->NotifyStatus(KStatus9);
		CleanupStack::PopAndDestroy();  // paraFormat
		break;
		}
// Storing and restoring
	case 10:
		// set up a file store
		{
		RFs         theFs;
		CFileStore* theStore;
		TParse      filestorename;
		// Make a connection to the file server
		theFs.Connect();
		theFs.Parse(name,filestorename);
		theStore=CDirectFileStore::ReplaceLC(theFs,filestorename.FullName(),EFileRead|EFileWrite);
		theStore->SetTypeL(KDirectFileStoreLayoutUid);
		// store rich text to file store
		iStreamId=iRichText->StoreL(*theStore); 
		// close the store
		CleanupStack::PopAndDestroy(); // pop and destroy store
		// Disconnect from file server
		theFs.Close();
		iFormObserver->NotifyStatus(KStatus10);
		break;
		}
	case 11:
		// reset document, clearing it of all content
		iRichText->Reset();
		iFormObserver->NotifyStatus(KStatusReset);
		break;
	case 12:
		// open the store
		{
		RFs         theFs;
		CFileStore* theStore;
		TParse      filestorename;

		theFs.Connect();
		theFs.Parse(name,filestorename);
		theStore=CDirectFileStore::OpenLC(theFs,filestorename.FullName(),EFileRead|EFileShareReadersOnly);
		if (theStore->Type()[0]!=KDirectFileStoreLayoutUid)
			User::Leave(KErrUnknown);
		// internalize from the store
		iRichText->RestoreL(*theStore,iStreamId);
		// close the store
		CleanupStack::PopAndDestroy(); // pop and destroy store
		theFs.Close();
		iFormObserver->NotifyStatus(KStatus12);
		break;
		}
	case 13:
		//reset document
		iRichText->Reset();
		// message to say what we did
		iFormObserver->NotifyStatus(KStatusReset);
		break;
	default:
		iFormObserver->NotifyStatus(KStatusDefault);
		break;
		}
	}


void CRichControl::Draw(const TRect& aRect) const
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

