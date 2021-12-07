// IMCVSEND.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

//----------------------------------------------------------------------------------------
inline LOCAL_C void AppendCRLF( TDes8& rOutputLine, TInt& rPaddingCount )
//----------------------------------------------------------------------------------------
	{
	rOutputLine.Append( TPtrC8(KImcvCRLF) );
	rPaddingCount += KImcvCRLF().Length();
	}


//----------------------------------------------------------------------------------------
inline LOCAL_C TInt AddCRLF(TDes8& rOutputLine)
//----------------------------------------------------------------------------------------
	{
	rOutputLine = KImcvCRLF;
	return 1;
	}

//----------------------------------------------------------------------------------------
inline LOCAL_C void AddCRLF( TDes8& rOutputLine, TInt& rPaddingCount )
//----------------------------------------------------------------------------------------
	{
	rOutputLine=TPtrC8(KImcvCRLF);
	rPaddingCount = KImcvCRLF().Length();
	}

//----------------------------------------------------------------------------------------
inline LOCAL_C void AddCRLFAtEndOfLine( TDes8& rOutputLine, TInt& rPaddingCount)
//----------------------------------------------------------------------------------------
	{
	TInt length = rOutputLine.Length();
	if ( length < 2 || (rOutputLine[length-2] != KImcvCR || rOutputLine[length-1] != KImcvLF) )
		{
		rOutputLine.Append( KImcvCRLF );
		rPaddingCount += 2;
		}
	}

//----------------------------------------------------------------------------------------
inline TBool IsLineCRLF( TDesC8& aOutputLine )
//----------------------------------------------------------------------------------------
	{
	TInt length = aOutputLine.Length();
	if ( length < 2 || (aOutputLine[length-2] != KImcvCR || aOutputLine[length-1] != KImcvLF) )
		return EFalse;
	return ETrue;
	}


//****************************************************************************************
//              Class CImEmailTraverser Functions
//****************************************************************************************


//----------------------------------------------------------------------------------------
inline TInt CImEmailTraverser::CurrentEntry()
//----------------------------------------------------------------------------------------
	{
	return iCurrentEntryList[0];
	}

//----------------------------------------------------------------------------------------
inline CMsvEntrySelection& CImEmailTraverser::CurrentList() const
//----------------------------------------------------------------------------------------
	{
	return *(*iSelectionList)[0];
	}

//----------------------------------------------------------------------------------------
inline TBool CImEmailTraverser::DeleteCurrentList()
//----------------------------------------------------------------------------------------
	{
	if (!LevelExists())
		return EFalse;

	delete &CurrentList();
	iSelectionList->Delete(0);
	iCurrentEntryList.Delete(0);
	return ETrue;
	}

//----------------------------------------------------------------------------------------
inline void CImEmailTraverser::AddList(CMsvEntrySelection& children)
//----------------------------------------------------------------------------------------
	{
	iSelectionList->InsertL(0, &children);
	iCurrentEntryList.InsertL(0, 0);
	}

//----------------------------------------------------------------------------------------
inline TBool CImEmailTraverser::LevelExists() const
//----------------------------------------------------------------------------------------
	{
	return iSelectionList->Count();
	}

//----------------------------------------------------------------------------------------
inline TBool CImEmailTraverser::IsBaseLevel() const
//----------------------------------------------------------------------------------------
	{
	return ThisEntry().Id()==iBaseId ? ETrue: EFalse;;
	}

//----------------------------------------------------------------------------------------
inline void CImEmailTraverser::SetBaseEntry()
//----------------------------------------------------------------------------------------
	{
	iServerEntry.SetEntry(iBaseId);
	}

//----------------------------------------------------------------------------------------
inline const TMsvEntry& CImEmailTraverser::ThisEntry() const
//----------------------------------------------------------------------------------------
	{	
	return iServerEntry.Entry();
	}


//****************************************************************************************
//              Class CImSendMimeEmail Functions
//****************************************************************************************

//----------------------------------------------------------------------------------------
inline void CImSendMimeEmail::Boundary(TDes8& rOutputLine) 
//----------------------------------------------------------------------------------------
	{
	rOutputLine.Append( (*iBoundaryArray)[0] );
	}

//----------------------------------------------------------------------------------------
inline TPtrC8 CImSendMimeEmail::Boundary()
//----------------------------------------------------------------------------------------
	{
	return (*iBoundaryArray)[0];
	}

//----------------------------------------------------------------------------------------
inline TInt CImSendMimeEmail::SendBoundaryLine(TDes8& rOutputLine, TInt& rPaddingCount)
//----------------------------------------------------------------------------------------
	{
	rOutputLine.Append(KImcvMimeBoundaryStartEnd);
	Boundary( rOutputLine );
	rPaddingCount += (*iBoundaryArray)[0].Length() + 2;
	return 1;
	}


// Sets iState to EEndBoundary or EEndOfEmail
// returns true if entry found
//----------------------------------------------------------------------------------------
inline TBool CImSendMimeEmail::Down(TMsvEntry& rEntry)
//----------------------------------------------------------------------------------------
	{
	TInt ret = iEmailTraverser->DownLevelL() ? ETrue:EFalse;

	if (ret)
		rEntry = iEmailTraverser->ThisEntry();
	return ret;
	}

//----------------------------------------------------------------------------------------
inline void CImSendMimeEmail::GetNextEntryL(TMsvEntry& rEntry)
//----------------------------------------------------------------------------------------
	{
	if ( (iState!=EEndBoundary && iState!=ELineAfterEndBoundary) && Down(rEntry) )
		iState=EBoundary;
	else if ( iEmailTraverser->NextEntryL(rEntry) )
		iState=EBoundary;
	else if (iEmailTraverser->UpLevelL() )
		{
		if (iServerEntry.Entry().iType==KUidMsvMessageEntry && !(iEmailTraverser->IsBaseLevel()))
			{
			// Embedded non-mime message
			iState=EEndBoundary;
			GetNextEntryL(rEntry);
			}
		else
			iState=EEndBoundary;
		}
	else
		iState=KImCvFinished;
	}


//----------------------------------------------------------------------------------------
inline TPtrC8 CImSendMimeEmail::SetBoundaryL(TBool aMultipart)
//----------------------------------------------------------------------------------------
	{
	if (!aMultipart)
		return TPtrC8();

	CreateBoundaryL();
	return (*iBoundaryArray)[0];
	}

//----------------------------------------------------------------------------------------
inline TBool CImSendMimeEmail::CheckForEmbeddedEmailL(const TMsvEntry& aEntry) const
//----------------------------------------------------------------------------------------
	{
	return (aEntry.iType==KUidMsvMessageEntry);
	}

//----------------------------------------------------------------------------------------
inline TBool CImSendMimeEmail::CheckForMultipartEmailL(TMsvEntry& rEntry, TImEmailFolderType& aFolder)
//----------------------------------------------------------------------------------------
	{
	TMsvEmailEntry emailEntry = (TMsvEmailEntry)rEntry;

	aFolder = emailEntry.MessageFolderType();
	if (aFolder==EFolderTypeMixed || aFolder==EFolderTypeDigest || 
		aFolder==EFolderTypeAlternative || aFolder==EFolderTypeRelated ) 
		return ETrue;
		
	if ( ! Down(emailEntry) )
		return EFalse;

	if ( iEmailTraverser->CurrentList().Count()==1 && 
				iEmailTraverser->ThisEntry().iType==KUidMsvFolderEntry )
		{
		aFolder = ((TMsvEmailEntry&)iEmailTraverser->ThisEntry()).MessageFolderType();
		iEmailTraverser->UpLevelL();
		return ETrue;
		}
	
	iEmailTraverser->UpLevelL();
	return EFalse;
	}

//****************************************************************************************
//              Class CImSendRfc822Header Functions
//****************************************************************************************

//----------------------------------------------------------------------------------------
inline TInt CImSendRfc822Header::XMailerL(TDes8& rOutputLine)
//----------------------------------------------------------------------------------------
	{
	rOutputLine = KImcvXMailer;
	rOutputLine.Append(*iProductName);
	return 1;
	}

//----------------------------------------------------------------------------------------
inline TInt CImSendRfc822Header::MessageIdL( TDes8& rOutputLine )
//----------------------------------------------------------------------------------------
	{
	if ( !iHeader->ImMsgId().Length() )
		return 1;

	PrepareBufferL( TPtrC8(KImcvMessageIdPrompt), iHeader->ImMsgId());
	return SendOutput( rOutputLine );
	}

//----------------------------------------------------------------------------------------
inline TInt CImSendRfc822Header::ToL(TDes8& rOutputLine)
//----------------------------------------------------------------------------------------
	{
	return DoRecipientsL(rOutputLine, TPtrC8(KImcvToPrompt), iHeader->ToRecipients());
	}

//----------------------------------------------------------------------------------------
inline TInt CImSendRfc822Header::CcL(TDes8& rOutputLine)
//----------------------------------------------------------------------------------------
	{
	return DoRecipientsL(rOutputLine, TPtrC8(KImcvCcPrompt), iHeader->CcRecipients());
	}

//----------------------------------------------------------------------------------------
inline TInt CImSendRfc822Header::BccL(TDes8& rOutputLine)
//----------------------------------------------------------------------------------------
	{
	return DoRecipientsL(rOutputLine, TPtrC8(KImcvBccPrompt), iHeader->BccRecipients());
	}

//----------------------------------------------------------------------------------------
inline TInt CImSendRfc822Header::FromL( TDes8& rOutputLine )
//----------------------------------------------------------------------------------------
	{
	PrepareBufferL( TPtrC8(KImcvFromPrompt), iHeader->From());
	return SendOutput( rOutputLine );
	}

//----------------------------------------------------------------------------------------
inline TInt CImSendRfc822Header::ReplyToL( TDes8& rOutputLine )
//----------------------------------------------------------------------------------------
	{
	if ( !iHeader->ReplyTo().Length() )
		return 1;

	PrepareBufferL( TPtrC8(KImcvReplyToPrompt), iHeader->ReplyTo() );
	return SendOutput( rOutputLine );
	}

//----------------------------------------------------------------------------------------
inline TInt CImSendRfc822Header::SubjectL( TDes8& rOutputLine )
//----------------------------------------------------------------------------------------
	{
	PrepareBufferL( TPtrC8(KImcvSubjectPrompt), iHeader->Subject() );
	return SendOutput( rOutputLine );	
	}


//----------------------------------------------------------------------------------------
inline TInt CImSendRfc822Header::ReturnReceiptsL(TDes8& rOutputLine)
//----------------------------------------------------------------------------------------
	{
	// SendReturnReceiptFieldsL() will always return one choice. 
	// In future it can be changed to add more fields 

	TPtrC address;
	if ( iHeader->ReceiptAddress().Length() )
		address.Set(iHeader->ReceiptAddress());
	else if ( iHeader->ReplyTo().Length() )
		address.Set(iHeader->ReplyTo());
	else
		return 1; // No valid a address

	CDesC8Array* receiptsFields=new (ELeave)CDesC8ArrayFlat(KArrayAllocationNumber);
	CleanupStack::PushL(receiptsFields);
	CImcvUtils::SendReturnReceiptFieldsL(*receiptsFields);
	TInt count=receiptsFields->Count();
	for (TInt i=0;i<count;i++)
		PrepareBufferL((*receiptsFields)[i], address);

	CleanupStack::PopAndDestroy(); //receiptsFields
	return SendOutput( rOutputLine );
	}

//----------------------------------------------------------------------------------------
inline const TImEmailTransformingInfo& CImSendRfc822Header::TransformingInfo() const
//----------------------------------------------------------------------------------------
	{
	return iTransformingInfo;
	}



//****************************************************************************************
//              Class CImSendMimeHeader Functions
//****************************************************************************************


//----------------------------------------------------------------------------------------
inline TInt CImSendMimeHeader::BlankLine(TDes8& rOutputLine) const
//----------------------------------------------------------------------------------------
	{
	rOutputLine = KNullDesC8;
	return 1;
	}

//----------------------------------------------------------------------------------------
inline TInt CImSendMimeHeader::MimeVersion(TDes8& rOutputLine) const
//----------------------------------------------------------------------------------------
	{
	rOutputLine = KImcvMimePrompt;
	rOutputLine.Append(KImcvSpMimeVersion);
	return 1;
	}

//----------------------------------------------------------------------------------------
inline TBool CImSendMimeHeader::ContentType(TDes8& rOutputLine) const
//----------------------------------------------------------------------------------------
	{
	TBool isText = EFalse;
	rOutputLine = KImcvContentType;
	rOutputLine.Append(KImcvSpace);

	if (((TMsvEmailEntry&)iEntry).VCard())
		{
		rOutputLine.Append(KImcvText);
		rOutputLine.Append( KImcvForwardSlash );
		rOutputLine.Append(KImcvDirectory);
		rOutputLine.Append( KImcvSemiColon );
		rOutputLine.Append( KImcvSpace );
		rOutputLine.Append( KImcvProfile );
		rOutputLine.Append( KImcvEquals );
		rOutputLine.Append( KImcvVCard );
		isText=ETrue;
		}
	else if (((TMsvEmailEntry&)iEntry).VCalendar())
		{
		rOutputLine.Append(KImcvText);
		rOutputLine.Append( KImcvForwardSlash );
		rOutputLine.Append(KImcvVCalender);
		isText=ETrue;
		}
	else if (iEntry.iType == KUidMsvEmailHtmlEntry)
		{
		rOutputLine.Append(KImcvText);
		rOutputLine.Append( KImcvForwardSlash );
		rOutputLine.Append(KImcvHtml);
		isText=ETrue;
		}
	else if ( iMimeHeader->ContentType().Length() )
		{
		TPtrC8 contentType = iMimeHeader->ContentType();
		rOutputLine.Append( contentType );	

		TPtrC8 contentSubType = iMimeHeader->ContentSubType();
		if ( contentSubType.Length() )
			{
			rOutputLine.Append( KImcvForwardSlash );
			rOutputLine.Append( iMimeHeader->ContentSubType() );
			}

		isText = contentType.CompareF(KImcvText) ? EFalse : ETrue;
		}
	else if (iEntry.iType == KUidMsvAttachmentEntry)
		rOutputLine.Append( KImcvApplOctet );	
	else if (iEntry.iType==KUidMsvEmailTextEntry || (!iIsMultipart && !iEntry.Attachment()))
		{
		rOutputLine.Append(KImcvText);
		rOutputLine.Append( KImcvForwardSlash );
		rOutputLine.Append(KImcvPlain);
		isText=ETrue;
		}
	else
		{
		rOutputLine.SetLength(0);
		return EFalse;
		}

	if (isText)
		{
		rOutputLine.Append( KImcvSemiColon );
		rOutputLine.Append( KImcvSpace );
		rOutputLine.Append( KImcvCharset );
		rOutputLine.Append( KImcvEquals );
		rOutputLine.Append( GetCharsetString() );
		}
	else if ( iBoundaryString.Length() )
		rOutputLine.Append(KImcvSemiColon); // boundary to follow

	return ETrue;
	}

//----------------------------------------------------------------------------------------
inline TBool CImSendMimeHeader::TransferEncoding(TDes8& rOutputLine) const
//----------------------------------------------------------------------------------------
	{
	TPtrC8 encodingType = EncodingType();

	if (iEntry.iType!=KUidMsvFolderEntry && encodingType.Length())
		{
		rOutputLine = KImcvContentTransferEncoding;
		rOutputLine.Append(encodingType);
		return ETrue;
		}

	return EFalse;
	}

//----------------------------------------------------------------------------------------
inline TInt CImSendMimeHeader::ContentLanguage(TDes8& rOutputLine) const
//----------------------------------------------------------------------------------------
	{
	rOutputLine = KImcvContentLanguage;
	rOutputLine.Append(KImcvDefaultLanguage);
	return 1;
	}

//----------------------------------------------------------------------------------------
inline TBool CImSendMimeHeader::Description( TDes8& rOutputLine ) const
//----------------------------------------------------------------------------------------
	{
	TPtrC8 description = iMimeHeader->ContentDescription();

	if ( !description.Length() )
		return EFalse;

	rOutputLine = KImcvContentDescription;
	rOutputLine.Append(KImcvSpace);
	rOutputLine.Append( description );
	return ETrue;
	}


//----------------------------------------------------------------------------------------
inline TInt CImSendMimeHeader::Boundary(TDes8& rOutputLine) const
//----------------------------------------------------------------------------------------
	{
	rOutputLine.Append(KImcvSpace);
	rOutputLine.Append(KImcvSpace);
	rOutputLine.Append(KImcvBoundary);
	rOutputLine.Append(KImcvEquals);
	rOutputLine.Append(KImcvQuote);
	rOutputLine.Append(iBoundaryString);
	rOutputLine.Append(KImcvQuote);
	return 1;
	}

//----------------------------------------------------------------------------------------
inline TBool CImSendMimeHeader::Disposition( TDes8& rOutputLine, TInt& rAdvance)
//----------------------------------------------------------------------------------------
	{
	rAdvance++;
	if (iEntry.iType == KUidMsvFolderEntry)
		return EFalse;

	if(iLine==EFirstLine)
		{
		TPtrC8 disposition = iMimeHeader->ContentDisposition();
		
		// Three cases : (2)disposition explicitly attachment,
		// (3) Non Multipart message with attachment flag set.

		if ( iEntry.iType==KUidMsvAttachmentEntry || 
			 disposition==KImcvAttachment ||
			 (!iIsMultipart && iEntry.iType!=KUidMsvMessageEntry && iEntry.Attachment()) )
			{
			rOutputLine = KImcvContentDisposition;
			rOutputLine.Append(KImcvSpace);
			rOutputLine.Append(KImcvAttachment);
			rOutputLine.Append(KImcvSemiColon);
			iLine++;
			rAdvance--;
			return ETrue;
			}
		else if (iEntry.iType==KUidMsvEmailTextEntry )
			{
			rOutputLine = KImcvContentDisposition;
			rOutputLine.Append(KImcvSpace);
			rOutputLine.Append(KImcvInline);
			return ETrue;
			}
		}
	else if (iFilename.Length())
		{
		rOutputLine.Append(KImcvTab);
		rOutputLine.Append(KImcvMimeDispositionFilename);
		AppendFilenameL( rOutputLine );
		return ETrue;
		}

	iLine=0;
	return EFalse;
	}

//----------------------------------------------------------------------------------------
inline const TPtrC8 CImSendMimeHeader::EncodingType() const
//----------------------------------------------------------------------------------------
	{
	switch (iEncodingType)
		{
		case EEncodingTypeBASE64:
			return TPtrC8(KImcvBase64);
		case EEncodingTypeQP:
			return TPtrC8(KImcvQuotedPrintable);
		case EEncodingTypeUU:
			return TPtrC8(KImcvXUUString);
		default:
			return TPtrC8(KImcv7Bit);
		}
	}

//----------------------------------------------------------------------------------------
inline TUint CImSendMimeHeader::CharsetUid() const
//----------------------------------------------------------------------------------------
	{
	return iCharsetUid;
	}


//****************************************************************************************
//              Class CImSendRichText Functions
//****************************************************************************************

//----------------------------------------------------------------------------------------
inline TBool CImSendRichText::IsBreakable( TChar ch ) const
//----------------------------------------------------------------------------------------
	{
	return (ch==' '|| ch=='\t' || ch==CEditableText::EParagraphDelimiter 
				   || ch==CEditableText::ENonBreakingSpace );
	}

//----------------------------------------------------------------------------------------
inline TInt CImSendRichText::Size() const
//----------------------------------------------------------------------------------------
	{
	return iBodySize;
	}

//----------------------------------------------------------------------------------------
inline TBool CImSendRichText::IsEOL( TChar ch ) const
//----------------------------------------------------------------------------------------
	{
	return (ch==CEditableText::EParagraphDelimiter
		 || ch==CEditableText::ELineBreak
		 || ch==CEditableText::EPageBreak);
	}

//----------------------------------------------------------------------------------------
inline TBool CImSendRichText::IsPlain( TChar aChar ) const
//----------------------------------------------------------------------------------------
	{
	return (((aChar >= '!') && (aChar <= KImcvSemiColon)) 
					|| ((aChar >= KImcvRightChevron) && (aChar <= KImcvTilde)));
	};

//----------------------------------------------------------------------------------------
inline TUint8 CImSendRichText::ReplacementChar( TChar aControlChar ) const
//----------------------------------------------------------------------------------------
	{
	if (aControlChar==CEditableText::ETabCharacter)
		return KImcvTab;

	if (aControlChar==CEditableText::ENonBreakingHyphen)
		return KImcvHyphen;

	if (aControlChar==CEditableText::ENonBreakingSpace)
		return KImcvSP;

	return 0;
	}

//----------------------------------------------------------------------------------------
inline int CImSendRichText::ConvertLineBreaks( TDes& aSource, TBool aLineBreak) const
//----------------------------------------------------------------------------------------
	{ 		
	// Need to get rid of 16 bit richtext control characters before moving to 8bit buffer
	// Therefore convert to the old para delimiter, convert to CRLF later in EncodeRichText.
	// Its horrible, but what can you do.

	TInt padding=0;
	TInt len=aSource.Length();
	TUint8 repChar;
	for (TInt i=0; i<len; i++)
		{
		repChar=ReplacementChar(aSource[i]);
		if (repChar)
			aSource[i]=repChar;
		else if ( IsEOL(aSource[i]) )
			{
			aSource[i]=KImcvCR;
			aSource.SetLength(i+2);
			aSource[i+1]=KImcvLF;
			padding+=1;
			if (aLineBreak)
				break;
			}
		} 
	return padding;
	};

//****************************************************************************************
//              Class CImSendFile Functions
//****************************************************************************************


//----------------------------------------------------------------------------------------
inline TInt CImSendFile::Size() const
//----------------------------------------------------------------------------------------
	{
	return iAttachmentInfo.iSize;
	}

//****************************************************************************************
//              Class CImCalculateMsgSize Functions
//****************************************************************************************

//----------------------------------------------------------------------------------------
inline TInt CImCalculateMsgSize::MessageSize() const
//----------------------------------------------------------------------------------------
	{
	return iSize;
	}

//----------------------------------------------------------------------------------------
inline void CImCalculateMsgSize::Progress(TInt& rCurrentSize, TInt& rTotalSize)
//----------------------------------------------------------------------------------------
	{
	rCurrentSize=iSize;
	rTotalSize=iTotal;
	}
