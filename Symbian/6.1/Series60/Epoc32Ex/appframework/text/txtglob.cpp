// TXTGLOB.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#include "txtexamp.h"

#include <fldset.h>
#include <fldbase.h>
#include <fldbltin.h>
#include <flddef.h>

//
// field factory
//

class TExampleFieldFactory : public MTextFieldFactory
	// A text field factory. 
	// It creates date/time fields only.
	{
public:
	virtual CTextField* NewFieldL(TUid aFieldType);
	};

CTextField* TExampleFieldFactory::NewFieldL(TUid aFieldType)
	{
	CTextField* field = NULL; // NULL keeps GCC compiler happy 
	// Factory only produces date time fields, if aFieldType is 
	// not a date time field type, do nothing.
	if (aFieldType==KDateTimeFieldUid)
		field = (CTextField*)new(ELeave) CDateTimeField();
	return field;
	}

//
// CGlobalControl implementation
//

CGlobalControl::~CGlobalControl()
	{
	delete iTextView; // text view
	delete iLayout; // layout
	delete iGlobalText; // contained text object
	delete iCharFormatLayer; // char format layer
	delete iParaFormatLayer; // and para format layer
	}

void CGlobalControl::UpdateModelL()
	{
	// Create all constant literal descriptors used in this function, 
	// e.g. for message text
	_LIT(KPath,"C:\\globtxt.dat");
	_LIT(KText1,"Some global text.");
	_LIT(KText5, "To be, or not to be, that is the question; \
whether 'tis nobler in the mind to suffer the \
slings and arrows of outrageous fortune, or \
to stand against a sea of troubles, and by \
opposing end them."); 
	_LIT(KText6,"Word at pos %d (\"%S\") has %d characters, starts at pos %d");
	_LIT(KText2," And some more global text.");
	_LIT(KText3,"A new paragraph.");
	_LIT(KText4,"Number of characters=%d, words=%d, paras=%d");
	_LIT(KText8,"%D%M%Y%H:%T:%S %1/%2/%3");
	_LIT(KStatus0,"Initialised global text object and text view");
	_LIT(KStatus1,"InsertL() at position zero");
	_LIT(KStatus2,"InsertL() at end of document");
	_LIT(KStatus3,"Insert new paragraph, and more text");
	_LIT(KStatus5,"Inserted lots of text");
	_LIT(KStatus7,"Inserted date time field");
	_LIT(KStatus8,"Centre aligned paragraphs");
	_LIT(KStatus9,"Set bold, italic and underline (and updated the field)");
	_LIT(KStatus10,"Used StoreL() to store text and fields");
	_LIT(KStatus12,"Used RestoreL() to restore text and fields");
	_LIT(KStatus13,"Deleted lots of text");
	_LIT(KStatus14,"Paragraph and character formatting reset to default values");
	_LIT(KStatusReset,"Reset();");
	_LIT(KStatusDefault,"(Overshot!!)");

	TBufC<28>   name(KPath);

	switch (Phase())
		{
	case 0:
		{
		// Create text object, text view and layout.
		iParaFormatLayer=CParaFormatLayer::NewL(); // required para format layer
		iCharFormatLayer=CCharFormatLayer::NewL(); // required char format layer
		// Create an empty global text object
		iGlobalText=CGlobalText::NewL(iParaFormatLayer, iCharFormatLayer);
		// prerequisites for view - viewing rectangle
		iViewRect=Rect();
		iViewRect.Shrink(3,3);
		// context and device
		CWindowGc& gc=SystemGc(); // get graphics context
		CBitmapDevice *device=(CBitmapDevice*) (gc.Device()); // device
		// Create the text layout, (required by text view),
		// with the text object and a wrap width (=width of view rect)
		iLayout=CTextLayout::NewL(iGlobalText,iViewRect.Width());
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
		iGlobalText->InsertL(0,KText1);
		iFormObserver->NotifyStatus(KStatus1);
		break;
	case 2:
		// Insert some more text
		iGlobalText->InsertL(iGlobalText->LdDocumentLength(),KText2);
		iFormObserver->NotifyStatus(KStatus2);
		break;
	case 3:
		// Insert a new paragraph
		iGlobalText->InsertL(iGlobalText->LdDocumentLength(),CEditableText::EParagraphDelimiter);
		// Insert text to follow new paragraph delimiter
		iGlobalText->InsertL(iGlobalText->LdDocumentLength(),KText3);
		iFormObserver->NotifyStatus(KStatus3);
		break;
	case 4:
		{
		// Display document info in status message
		TBuf<80> message; // for formatting status messages
		message.Format(KText4,
				iGlobalText->LdDocumentLength(),
						// length up to and excluding final para mark
				iGlobalText->WordCount(), // white-space delimited words
				iGlobalText->ParagraphCount() // number paras including the final one
				);
		iFormObserver->NotifyStatus(message);
		break;
		}
	case 5:
		// Insert lots of text
		iGlobalText->InsertL(iGlobalText->LdDocumentLength(),CEditableText::EParagraphDelimiter);
		iGlobalText->InsertL(iGlobalText->LdDocumentLength(),KText5);
		iFormObserver->NotifyStatus(KStatus5);
		break;
	case 6:
		{
		// Display information about a random document position
		TBuf<80> message; // for formatting status messages
		// Print info about word at a document position
		TInt pos=iGlobalText->LdDocumentLength()/2;
		TInt startPos, length; // results of function
		iGlobalText->GetWordInfo(pos,startPos,length,EFalse,ETrue);
				// gets startPos and length, given pos
		// Insert all text into buffer from startPos (start of word at 
		// position pos) onwards
		TPtrC ptr=iGlobalText->Read(startPos,length); 
		// Print out word and word info
		message.Format(KText6, pos, &ptr, length, startPos);
		iFormObserver->NotifyStatus(message);
		break;
		}
	case 7:
		{
		// Insert date/time field into document
		TExampleFieldFactory* factory = new(ELeave) TExampleFieldFactory();
		CleanupStack::PushL(factory);
		// Set up the field factory
		iGlobalText->SetFieldFactory(factory);
		CTextField* field = iGlobalText->NewTextFieldL(KDateTimeFieldUid);
		// Format date to hour:minute:second day/month/year 
		((CDateTimeField*)field)->SetFormat(KText8); 
		iGlobalText->InsertFieldL(0,field,KDateTimeFieldUid);
		// Evaluate the field (makes contents visible)
		iGlobalText->UpdateAllFieldsL();
		// Insert new para delimiter after field
		// First get length of field we've just inserted
		TFindFieldInfo info; 
		TInt pos=0;
		TInt range=0;
		iGlobalText->FindFields(info,pos,range);
		iGlobalText->InsertL(info.iFirstFieldLen,CEditableText::EParagraphDelimiter);
		iFormObserver->NotifyStatus(KStatus7);
		// clean up
		CleanupStack::PopAndDestroy(); // factory
		break;
		}
	case 8:
		{
		// Set some paragraph formatting - applied globally
		CParaFormat* paraFormat=CParaFormat::NewLC();
		TParaFormatMask paraFormatMask;
		// Set centre alignment
		paraFormat->iHorizontalAlignment=CParaFormat::ECenterAlign; 
		paraFormatMask.SetAttrib(EAttAlignment);
		// apply formatting - pos and length are irrelevent
		iGlobalText->ApplyParaFormatL(paraFormat,paraFormatMask,0,0);
		iFormObserver->NotifyStatus(KStatus8);
		CleanupStack::PopAndDestroy();  // paraFormat
		break;
		}
	case 9:
		{
		// Set some character formatting - applied globally
		TCharFormat charFormat;
		TCharFormatMask charFormatMask;
		// Interested in underline, posture and weight
		charFormatMask.SetAttrib(EAttFontUnderline); // set underline
		charFormatMask.SetAttrib(EAttFontPosture); // and posture (for italic)
		charFormatMask.SetAttrib(EAttFontStrokeWeight); // and weight (for bold)
		// Set bold, italics and underlining
		charFormat.iFontPresentation.iUnderline=EUnderlineOn;
		charFormat.iFontSpec.iFontStyle.SetPosture(EPostureItalic); 
		charFormat.iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightBold);
		// apply formatting - pos and length are irrelevent
		iGlobalText->ApplyCharFormatL(charFormat,charFormatMask, 0,0);
		// And update the field
		iGlobalText->UpdateFieldL(0);
		iFormObserver->NotifyStatus(KStatus9);
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
		// store global text to file store
		iStreamId=iGlobalText->StoreL(*theStore);
		// close file store
		CleanupStack::PopAndDestroy(); // pop and destroy store
		// Disconnect from file server
		theFs.Close();
		iFormObserver->NotifyStatus(KStatus10);
		break;
		}
	case 11:
		// reset document, clearing it of all content
		iGlobalText->Reset();
		iFormObserver->NotifyStatus(KStatusReset);
		break;
	case 12:
		{
		// set up file store
		RFs         theFs;
		CFileStore* theStore;
		TParse      filestorename;

		theFs.Connect();
		theFs.Parse(name,filestorename);
		theStore=CDirectFileStore::OpenLC(theFs,filestorename.FullName(),EFileRead|EFileShareReadersOnly);
		if (theStore->Type()[0]!=KDirectFileStoreLayoutUid)
			User::Leave(KErrUnknown);
		// restore text and components from file store
		iGlobalText->RestoreL(*theStore,iStreamId);
		// close file store
		CleanupStack::PopAndDestroy(); // pop and destroy store
		theFs.Close();
		iGlobalText->UpdateFieldL(0);
		iFormObserver->NotifyStatus(KStatus12);
		break;
		}
	case 13:
		// Delete all text from paragraph containing a random doc position to 
		// end of document. Also delete preceding paragraph delimiter to keep 
		// paragraph count correct.
		{
		TInt pos=iGlobalText->LdDocumentLength()/2;
		iGlobalText->ToParagraphStart(pos); // pos set to start of paragraph
		pos--; // decrement so pos = preceding para delimiter
		iGlobalText->DeleteL(pos, iGlobalText->LdDocumentLength()-pos);
				// delete rest of text
		iFormObserver->NotifyStatus(KStatus13);
		break;
		}
	case 14:
		{
		// Reset all formatting back to the default
		TCharFormat charFormat;
		TCharFormatMask charFormatMask;
		CParaFormat* paraFormat=CParaFormat::NewLC();
		TParaFormatMask paraFormatMask;
		// Reset all character format attributes
		charFormatMask.SetAll();
		iGlobalText->ApplyCharFormatL(charFormat,charFormatMask,0,1);
			// format is all empty, mask is all set: thus, everything to default
		paraFormatMask.SetAll();
		iGlobalText->ApplyParaFormatL(paraFormat, paraFormatMask, 0,1);
			// ditto
		iFormObserver->NotifyStatus(KStatus14);
		CleanupStack::PopAndDestroy();  // paraFormat
		break;
		}
	case 15:
		// reset document, clearing it of all text content and fields
		iGlobalText->Reset();
		iFormObserver->NotifyStatus(KStatusReset);
		break;
	default:
		iFormObserver->NotifyStatus(KStatusDefault);
		break;
		}
	}

void CGlobalControl::Draw(const TRect& aRect) const
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

