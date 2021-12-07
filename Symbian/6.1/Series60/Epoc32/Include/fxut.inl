// FXUT.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

//////////////////////////////////////////////////////////////////////////////////
//
// class TFaxSessionProgress
//

inline TInt16 CFaxRecipient::SendingPage() const
	{
	return iSendingPage;
	}

inline void CFaxRecipient::SetSendingPage(TInt16 aPage)
	{
	iSendingPage = aPage;
	}

//////////////////////////////////////////////////////////////////////////////////
//
// class TMsvFaxEntry
//

inline TInt16 TMsvFaxEntry::SendingPage() const
	{
	__ASSERT_DEBUG(SendingState() != EFaxSendingStatePreparing, User::Invariant()); // Can't call this when fax is being prepared

	// Return msig word
	return (TInt16)((iMtmData1 & 0xffff<<16) >> 16);
	}

inline void TMsvFaxEntry::SetSendingPage(TInt16 aPage)
	{
	__ASSERT_DEBUG(SendingState() != EFaxSendingStatePreparing, User::Invariant()); // Can't call this when fax is being prepared

	// Set msig word
	iMtmData1 = (iMtmData1 & 0xffff) | (aPage << 16);
	}

inline TInt16 TMsvFaxEntry::TotalPages() const
	{
	__ASSERT_DEBUG(SendingState() != EFaxSendingStatePreparing, User::Invariant()); // Can't call this when fax is being prepared

	// Return lsig word
	return (TInt16)(iMtmData1 & 0xffff);
	}

inline void TMsvFaxEntry::SetTotalPages(TInt16 aTotal)
	{
	__ASSERT_DEBUG(SendingState() != EFaxSendingStatePreparing, User::Invariant()); // Can't call this when fax is being prepared

	// Set lsig word only
	iMtmData1 = (iMtmData1 & 0xffff<<16) | aTotal;
	}

inline TInt16 TMsvFaxEntry::SendingRecipient() const
	{
	// Return msig word
	return (TInt16)((iMtmData3 & 0xffff<<16) >> 16);
	}

inline void TMsvFaxEntry::SetSendingRecipient(TInt16 aRecipient)
	{
	// Set msig word
	iMtmData3 = (iMtmData3 & 0xffff) | (aRecipient << 16);
	}

inline TInt16 TMsvFaxEntry::TotalRecipients() const
	{
	// Return lsig word
	return (TInt16)(iMtmData3 & 0xffff);
	}

inline void TMsvFaxEntry::SetTotalRecipients(TInt16 aTotal)
	{
	// Set lsig word only
	iMtmData3 = (iMtmData3 & 0xffff<<16) | aTotal;
	}

inline TFaxResolution TMsvFaxEntry::Resolution() const
	{
	// Bit 0 indicates fine resolution if set
	return iMtmData2 & EMsvFineResolution ? EFaxFine : EFaxNormal;
	}

inline void TMsvFaxEntry::SetResolution(TFaxResolution aResolution)
	{
	// Bit 0 indicates fine resolution if set, normal if not
	if (aResolution == EFaxNormal)
		iMtmData2 &= ~EMsvFineResolution;
	else
		iMtmData2 |= EMsvFineResolution;
	}

inline TInt8 TMsvFaxEntry::RenderingComplete() const
	{
	__ASSERT_DEBUG(SendingState() == EFaxSendingStatePreparing, User::Invariant()); // Only call this when fax is being prepared
	return (TInt8)iMtmData1;
	}

inline void TMsvFaxEntry::SetRenderingComplete(TInt8 aComplete)
	{
	__ASSERT_DEBUG(SendingState() == EFaxSendingStatePreparing, User::Invariant()); // Only call this when fax is being prepared
	__ASSERT_DEBUG(aComplete <= 100, User::Invariant()); // This should be a percentage
	iMtmData1 = aComplete;
	}

//////////////////////////////////////////////////////////////////////////////////
//
// class TMTMFaxSettings
//

inline TBool TMTMFaxSettings::ProgressInEntry() const
	{
	return (iFlags & EFaxNoProgressInEntry) != EFaxNoProgressInEntry;
	}

inline void TMTMFaxSettings::SetProgressInEntry(TBool aProgress)
	{
	iFlags = (iFlags & ~EFaxNoProgressInEntry) | (aProgress ? KFaxSettingsClearFlag : EFaxNoProgressInEntry);
	}

inline TBool TMTMFaxSettings::PartialResend() const
	{
	return (iFlags & EFaxNoPartialResend) != EFaxNoPartialResend;
	}

inline void TMTMFaxSettings::SetPartialResend(TBool aResend)
	{
	iFlags = (iFlags & ~EFaxNoPartialResend) | (aResend ? KFaxSettingsClearFlag : EFaxNoPartialResend);
	}

inline TBool TMTMFaxSettings::UnRenderOnSend() const
	{
	return (iFlags & EFaxNoUnRenderOnSend) != EFaxNoUnRenderOnSend;
	}

inline void TMTMFaxSettings::SetUnRenderOnSend(TBool aUnRender)
	{
	iFlags = (iFlags & ~EFaxNoUnRenderOnSend) | (aUnRender ? KFaxSettingsClearFlag : EFaxNoUnRenderOnSend);
	}

inline TBool TMTMFaxSettings::WatcherEnabled() const
	{
	return (iFlags & EFaxWatcherDisabled) != EFaxWatcherDisabled;
	}

inline void TMTMFaxSettings::SetWatcherEnabled(TBool aEnabled)
	{
	iFlags = (iFlags & ~EFaxWatcherDisabled) | (aEnabled ? KFaxSettingsClearFlag : EFaxWatcherDisabled);
	}

inline TBool TMTMFaxSettings::SentFaxesReadOnly() const
	{
	return (iFlags & EFaxSentFaxesNotReadOnly) != EFaxSentFaxesNotReadOnly;
	}

inline void TMTMFaxSettings::SetSentFaxesReadOnly(TBool aReadOnly)
	{
	iFlags = (iFlags & ~EFaxSentFaxesNotReadOnly) | (aReadOnly ? KFaxSettingsClearFlag : EFaxSentFaxesNotReadOnly);
	}
