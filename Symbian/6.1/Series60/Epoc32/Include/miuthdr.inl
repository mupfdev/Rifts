// MIUTHDR.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

inline void TImHeaderEncodingInfo::SetField(const TFieldList aField)
	{
	iField = aField;
	}

inline TImHeaderEncodingInfo::TFieldList TImHeaderEncodingInfo::Field() const
	{
	return iField;
	}

inline void TImHeaderEncodingInfo::SetOffset(const TInt aOffset)
	{
	iOffset = (TUint16)aOffset;
	}

inline TInt TImHeaderEncodingInfo::Offset() const
	{
	return iOffset;
	}

inline void TImHeaderEncodingInfo::SetLength(const TInt aLength)
	{
	iLength = (TUint16)aLength;
	}


inline TInt TImHeaderEncodingInfo::Length()  const
	{
	return iLength;
	}


void TImHeaderEncodingInfo::SetCharsetUid(const TUint aUid)
	{
	iCharsetUid = aUid;
	}


TUint TImHeaderEncodingInfo::CharsetUid() const
	{
	return iCharsetUid;
	}


inline void TImHeaderEncodingInfo::SetEncodingType(const TDesC8& aChar)
	{
	// If invalid, defaults to QPEncoding
	if (aChar[0] == 'b' || aChar[0] == 'B')
		iType = TImHeaderEncodingInfo::EBase64;
	else if (aChar[0] == 'q' || aChar[0] == 'Q')
		iType = TImHeaderEncodingInfo::EQP;
	else
		iType = TImHeaderEncodingInfo::ENoEncoding;
	}

inline void TImHeaderEncodingInfo::SetEncodingType(const TEncodingType aType)
	{
	iType = aType;
	}


inline TImHeaderEncodingInfo::TEncodingType TImHeaderEncodingInfo::EncodingType()  const
	{
	return iType;
	}

inline void TImHeaderEncodingInfo::SetArrayValue(const TInt aValue)
	{
	iArrayValue = (TUint16)aValue;
	}


inline TInt TImHeaderEncodingInfo::ArrayValue()  const
	{
	return iArrayValue;
	}


inline void TImHeaderEncodingInfo::SetAddSpace(const TBool atrueFalse)
	{
	iAddSpace = atrueFalse;
	}


inline  TBool TImHeaderEncodingInfo::AddSpace() const
	{
	return iAddSpace;
	}

inline void TImHeaderEncodingInfo::SetEncodedLength(const TInt aLength)
	{
	iEncodedLength = (TInt8) aLength;
	}

inline TInt TImHeaderEncodingInfo::EncodedLength() const
	{
	return iEncodedLength + (AddSpace() ? 1 : 0);
	}

//----------------------------------------------------------------------------------------

inline CDesCArray& CImHeader::ToRecipients ()
	{
	return *iTo;
	}

inline CDesCArray& CImHeader::CcRecipients ()
	{
	return *iCc;
	}
	
inline CDesCArray& CImHeader::BccRecipients()
	{
	return *iBcc;
	}

inline const CDesCArray& CImHeader::ToRecipients () const 
	{
	return *iTo;
	}

inline const CDesCArray& CImHeader::CcRecipients () const
	{
	return *iCc;
	}
	
inline const CDesCArray& CImHeader::BccRecipients() const
	{
	return *iBcc;
	}

//-------------------------------------------------------------------------------------
//---------------------------- Used for forwarding an email ---------------------------

inline CDesCArray& CImHeader::ResentToRecipients ()
	{
	return *iResentTo;
	}

inline CDesCArray& CImHeader::ResentCcRecipients ()
	{
	return *iResentCc;
	}
	
inline CDesCArray& CImHeader::ResentBccRecipients()
	{
	return *iResentBcc;
	}

inline const CDesCArray& CImHeader::ResentToRecipients () const 
	{
	return *iResentTo;
	}

inline const CDesCArray& CImHeader::ResentCcRecipients () const
	{
	return *iResentCc;
	}
	
inline const CDesCArray& CImHeader::ResentBccRecipients() const
	{
	return *iResentBcc;
	}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

inline const TUint CImHeader::RemoteSize() const
	{
	return iRemoteSize;
	}

inline void CImHeader::SetRemoteSize( TUint aRemoteSize )
	{
	iRemoteSize = aRemoteSize;
	}


inline const TUint16 CImHeader::Version() const
	{
	return iVersion;
	}

inline void CImHeader::SetVersion( TUint16 aVersion )
	{
	iVersion = aVersion;
	}

inline CArrayFix<TImHeaderEncodingInfo>& CImHeader::EncodingInfo()
	{
	return *iEncodingInfo;
	}

inline const CArrayFix<TImHeaderEncodingInfo>& CImHeader::EncodingInfo() const
	{
	return *iEncodingInfo;
	}

//////////////////////////////////////////////////////////////
//															//
//////////////////////////////////////////////////////////////


inline TBool TMsvEmailEntry::Encrypted() const
	{
	return iMtmData1&KMsvEmailEntryEncryptedFlag;
	}

inline void TMsvEmailEntry::SetEncrypted(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryEncryptedFlag) | (aFlag?KMsvEmailEntryEncryptedFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::Signed() const
	{
	return iMtmData1&KMsvEmailEntrySignedFlag;
	}

inline void TMsvEmailEntry::SetSigned(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntrySignedFlag) | (aFlag?KMsvEmailEntrySignedFlag:KMsvEmailEntryClearFlag);
	}

///
inline TBool TMsvEmailEntry::MHTMLEmail() const
	{
	return iMtmData1&KMsvEmailEntryMHTMLFlag;
	}

inline void TMsvEmailEntry::SetMHTMLEmail(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryMHTMLFlag) | (aFlag?KMsvEmailEntryMHTMLFlag:KMsvEmailEntryClearFlag);
	}

///
inline TBool TMsvEmailEntry::BodyTextComplete() const
	{
	return iMtmData1 & KMsvEmailEntryBodyTextCompleteFlag;
	}

inline void TMsvEmailEntry::SetBodyTextComplete(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryBodyTextCompleteFlag) | (aFlag?KMsvEmailEntryBodyTextCompleteFlag:KMsvEmailEntryClearFlag);
	}

///
inline TBool TMsvEmailEntry::VCard() const
	{
	return iMtmData1&KMsvEmailEntryVCardFlag;
	}

inline void TMsvEmailEntry::SetVCard(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryVCardFlag) | (aFlag?KMsvEmailEntryVCardFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::VCalendar() const
	{
	return iMtmData1&KMsvEmailEntryVCalendarFlag;
	}

inline void TMsvEmailEntry::SetVCalendar(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryVCalendarFlag) | (aFlag?KMsvEmailEntryVCalendarFlag:KMsvEmailEntryClearFlag);
	}

//

inline TBool TMsvEmailEntry::Receipt() const
	{
	return iMtmData1&KMsvEmailEntryReceiptFlag;
	}

inline void TMsvEmailEntry::SetReceipt(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryReceiptFlag) | (aFlag?KMsvEmailEntryReceiptFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::UnreadIMAP4Flag() const
	{
	return iMtmData1&KMsvEmailEntryIMAP4UnreadFlag;
	}

inline void TMsvEmailEntry::SetUnreadIMAP4Flag(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4UnreadFlag) | (aFlag?KMsvEmailEntryIMAP4UnreadFlag:KMsvEmailEntryClearFlag);
	}

inline TBool TMsvEmailEntry::SeenIMAP4Flag() const
	{
	return iMtmData1&KMsvEmailEntryIMAP4SeenFlag;
	}

inline void TMsvEmailEntry::SetSeenIMAP4Flag(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4SeenFlag) | (aFlag?KMsvEmailEntryIMAP4SeenFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::AnsweredIMAP4Flag() const
	{
	return iMtmData1&KMsvEmailEntryIMAP4AnsweredFlag;
	}

inline void TMsvEmailEntry::SetAnsweredIMAP4Flag(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4AnsweredFlag) | (aFlag?KMsvEmailEntryIMAP4AnsweredFlag:KMsvEmailEntryClearFlag);
	}



inline TBool TMsvEmailEntry::FlaggedIMAP4Flag() const
	{
	return iMtmData1&KMsvEmailEntryIMAP4FlaggedFlag;
	}

inline void TMsvEmailEntry::SetFlaggedIMAP4Flag(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4FlaggedFlag) | (aFlag?KMsvEmailEntryIMAP4FlaggedFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::DeletedIMAP4Flag() const
	{
	return iMtmData1&KMsvEmailEntryIMAP4DeletedFlag;
	}

inline void TMsvEmailEntry::SetDeletedIMAP4Flag(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4DeletedFlag) | (aFlag?KMsvEmailEntryIMAP4DeletedFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::DraftIMAP4Flag() const
	{
	return iMtmData1&KMsvEmailEntryIMAP4DraftFlag;
	}

inline void TMsvEmailEntry::SetDraftIMAP4Flag(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4DraftFlag) | (aFlag?KMsvEmailEntryIMAP4DraftFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::RecentIMAP4Flag() const
	{
	return iMtmData1&KMsvEmailEntryIMAP4RecentFlag;
	}

inline void TMsvEmailEntry::SetRecentIMAP4Flag(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4RecentFlag) | (aFlag?KMsvEmailEntryIMAP4RecentFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::Mailbox() const
	{
	return iMtmData1&KMsvEmailEntryIMAP4MailboxFlag;
	}

inline void TMsvEmailEntry::SetMailbox(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4MailboxFlag) | (aFlag?KMsvEmailEntryIMAP4MailboxFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::Orphan() const
	{
	return iMtmData1&KMsvEmailEntryOrphanFlag;
	}

inline void TMsvEmailEntry::SetOrphan(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryOrphanFlag) | (aFlag?KMsvEmailEntryOrphanFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::ValidUID() const
	{
	return iMtmData1&KMsvEmailEntryIMAP4ValidUIDFlag;
	}

inline void TMsvEmailEntry::SetValidUID(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4ValidUIDFlag) | (aFlag?KMsvEmailEntryIMAP4ValidUIDFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::Subscribed() const
	{
	return iMtmData1&KMsvEmailEntryIMAP4SubscribedFlag;
	}

inline void TMsvEmailEntry::SetSubscribed(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4SubscribedFlag) | (aFlag?KMsvEmailEntryIMAP4SubscribedFlag:KMsvEmailEntryClearFlag);
	}


inline TBool TMsvEmailEntry::LocalSubscription() const
	{
	return iMtmData1&KMsvEmailEntryIMAP4LocalSubFlag;
	}

inline void TMsvEmailEntry::SetLocalSubscription(TBool aFlag)
	{
	iMtmData1 = (iMtmData1 & ~KMsvEmailEntryIMAP4LocalSubFlag) | (aFlag?KMsvEmailEntryIMAP4LocalSubFlag:KMsvEmailEntryClearFlag);
	}


inline TUint32 TMsvEmailEntry::UID() const
	{
	return (TUint32)iMtmData2;	// hide the casting away from the caller
	}

inline void TMsvEmailEntry::SetUID(TUint32 aUID)
	{
	iMtmData2 = (TInt32) aUID;	// hide the casting away from the user
	}

inline TInt TMsvEmailEntry::RemoteFolderEntries() const
	{
	return iMtmData3&KMsvRemoteFolderEntriesMask;
	}

inline void TMsvEmailEntry::SetRemoteFolderEntries(TInt aEntries)
	{
 	iMtmData3 = (TInt32) ((iMtmData3 & ~KMsvRemoteFolderEntriesMask) | (aEntries & KMsvRemoteFolderEntriesMask));
	}

//////////////////////////////////////////////////////////////
//				CImMimeHeader inlines						//
//////////////////////////////////////////////////////////////


inline const CDesC8Array& CImMimeHeader::ContentTypeParams() const 
	{
	return *iContentTypeParams;
	}


inline const CDesC8Array& CImMimeHeader::ContentDispositionParams() const
	{
	return *iContentDispositionParams;
	}


inline const CDesC8Array& CImMimeHeader::XTypeParams() const
	{
	return *iXTypeParams;
	}



inline CDesC8Array& CImMimeHeader::ContentTypeParams()
	{
	return *iContentTypeParams;
	}


inline CDesC8Array& CImMimeHeader::ContentDispositionParams()
	{
	return *iContentDispositionParams;
	}


inline CDesC8Array& CImMimeHeader::XTypeParams()
	{
	return *iXTypeParams;
	}


inline const TUint16 CImMimeHeader::Version() const
	{
	return iVersion;
	}

inline void CImMimeHeader::SetVersion( TUint16 aVersion )
	{
	iVersion = aVersion;
	}
