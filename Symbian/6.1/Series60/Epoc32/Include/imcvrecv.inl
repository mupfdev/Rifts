// IMCVRECV.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.


/****************************************************************************
	Class CRfc822Token Inline functions
*****************************************************************************/

inline HBufC8* CRfc822Token::OutputLine()
	{
	return iOutputLine;
	}

inline TBool CRfc822Token::LastToken()
	{
	return iLastToken;
	}

inline void CRfc822Token::SetImRecvConvert( CImRecvConvert* aImRecvConvert )
	{
	iImRecvConvert = aImRecvConvert;
	}


/****************************************************************************
	Class CImRecvConvert Inline functions
*****************************************************************************/

inline void CImRecvConvert::SetAttachmentPathL(const TDesC& aFullPath)
	{
	// get full path to current message file = directory path
	if (iAttachmentFullPath)
		{
		delete iAttachmentFullPath;
		iAttachmentFullPath=NULL;
		}
	iAttachmentFullPath=aFullPath.AllocL();
	}

inline void CImRecvConvert::SetMsvId(TMsvId aId)
	{
	iServerEntry->SetEntry(aId);
	iPopulateMessage = (iServerEntry->Entry().iType == KUidMsvMessageEntry);
	iRootEntryId = aId;
	}

inline const TTime CImRecvConvert::Date() const
	{
	return iTimeDate;
	}

inline const TMsvPriority CImRecvConvert::Priority() const
	{
	return iImPriority;
	}

inline void CImRecvConvert::SaveAllAttachments(TBool aSave)
	{
	iSavingAttachments=aSave;
	}

inline const TInt CImRecvConvert::ReceiveError() const
	{
	return iReceiveError;
	}

inline CMsvServerEntry& CImRecvConvert::ServerEntry()
	{
	return *iServerEntry;
	}

inline const TBool CImRecvConvert::ValidCompleteHeader() const
	{
	return (iEmptyHeaderSize<(iOutputHeader->DataSize()) && iFinishedHeader);
	}

inline const CImHeader& CImRecvConvert::Header() const
	{
	return *iOutputHeader;
	}

inline const TMsvId CImRecvConvert::EntryId() const
	{
	// If we are temporarily on the null entry then return the saved entry
	if (iServerEntry->Entry().Id() == KMsvNullIndexEntryId)
		return iSavedEntryId;
	else
		return iServerEntry->Entry().Id();
	}

inline TBool CImRecvConvert::NotFinishedRfc822Header()
	{
	return iNotFinishedRfc822Header;
	}

inline CImConvertCharconv& CImRecvConvert::CharacterConverter()
	{
	return *iCharConv;
	}

/****************************************************************************
	Class CMimeParser Inline functions
*****************************************************************************/
inline void CMimeParser::StoreMimeHeaderL(CMsvStore& entryStore)
	{
	iMimeHeader->StoreL(entryStore);
	}

inline void CMimeParser::StoreMimeHeaderWithoutCommitL(CMsvStore& entryStore)
	{
	iMimeHeader->StoreWithoutCommitL(entryStore);
	}

inline void CMimeParser::RestoreMimeHeaderL(CMsvStore& entryStore)
	{
	RestoreMimeParserL(entryStore);
	}

inline TMimeContentType CMimeParser::ContentType()
	{
	return iContentType;
	}

inline TImEncodingType CMimeParser::ContentEncoding()
	{
	return iContentEncoding;
	}

inline const TBool CMimeParser::MessageIsMime() const
	{
	return isMime;
	}

inline const TDesC& CMimeParser::ContentDescription() const
	{
	return iContentDescription;
	}

inline const TPtrC CMimeParser::ContentLocation() const
	{
	return iMimeHeader->ContentLocation();
	}

inline const TPtrC8 CMimeParser::ContentId() const
	{
	return iMimeHeader->ContentID();
	}

inline const TPtrC8 CMimeParser::ContentDisposition() const
	{
	return iMimeHeader->ContentDisposition();
	}

inline const TBool CMimeParser::IsTerminatingBoundary() const
	{
	return iTerminatingBoundary;
	}

inline const TBool CMimeParser::BoundaryExists() const
	{
	return (iBoundaryLength!=0);
	}

inline const TBool CMimeParser::BoundaryFound() const
	{
	return iBoundaryFound;
	}

inline const TInt CMimeParser::MimeHeaderSize() const
	{
	return iEmptyMimeHeaderSize-iMimeHeader->Size();
	}

inline const TInt CMimeParser::ReceiveError() const
	{
	return iReceiveError;
	}

inline TBool CMimeParser::IsMessageDigest()
	{
	return (ContentType()==EMimeMultipart && ContentSubType().Compare(KImcvDigest)==0);
	}

inline TBool CMimeParser::MimeFieldsExist() const
	{
	return iMimeFieldsExist;
	}

inline void CMimeParser::ResetMimeFieldsExist()
	{
	iMimeFieldsExist=EFalse;
	}
