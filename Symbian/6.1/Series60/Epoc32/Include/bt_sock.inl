// bt_sock.inl
//
// Copyright (c) 1999-2000 Symbian Ltd.  All rights reserved.
//

//
// BT socket interface types
//


/****** BT Socket Addresses *****/

inline TAny *TBTSockAddr::BTUserPtr() const
	{
	return UserPtr()+sizeof(SBTAddr);
	}

inline TBTSockAddr::SBTAddr &TBTSockAddr::BTAddrStruct() const
	{
	return *(SBTAddr *)UserPtr();
	}

inline TPtr8 TBTSockAddr::AddressPtr() const
	{
	return BTAddrStruct().iAddress.Des();
	}


//
// L2CAP
//


/****** L2CAP Socket Addresses *****/

inline TL2CAPSockAddr& TL2CAPSockAddr::Cast(const TSockAddr &aAddr)
	{
	return *((TL2CAPSockAddr *)&aAddr);
	}

inline TUint16 TL2CAPSockAddr::Port() const
	{
	return static_cast<TUint16>(TSockAddr::Port());
	}

inline void TL2CAPSockAddr::SetPort(const TUint16 aHomePort)
	{
	TSockAddr::SetPort(aHomePort);
	}

/****** Inquiry Socket Addresses *****/

inline TInquirySockAddr& TInquirySockAddr::Cast(const TSockAddr &aAddr)
	{
	return *((TInquirySockAddr *)&aAddr);
	}

inline TUint16 TInquirySockAddr::MajorServiceClass() const
	{
	return InquiryAddrStruct().iMajorServiceClass;
	}

inline void TInquirySockAddr::SetMajorServiceClass(TUint16 aClass)
	{
	InquiryAddrStruct().iMajorServiceClass=aClass;
	}

inline TUint8 TInquirySockAddr::MajorClassOfDevice() const
	{
	return InquiryAddrStruct().iMajorDeviceClass;
	}

inline void TInquirySockAddr::SetMajorClassOfDevice(TUint8 aClass)
	{
	InquiryAddrStruct().iMajorDeviceClass=aClass;
	}

inline TUint8 TInquirySockAddr::MinorClassOfDevice() const
	{
	return InquiryAddrStruct().iMinorDeviceClass;
	}

inline void TInquirySockAddr::SetMinorClassOfDevice(TUint8 aClass)
	{
	InquiryAddrStruct().iMinorDeviceClass=aClass;
	}

inline TUint TInquirySockAddr::IAC() const
	{
	return InquiryAddrStruct().iIAC;
	}

inline void TInquirySockAddr::SetIAC(const TUint aIAC)
	{
	InquiryAddrStruct().iIAC=aIAC;
	}

inline TUint8 TInquirySockAddr::Action() const
	{
	return InquiryAddrStruct().iFlags;
	}

inline void TInquirySockAddr::SetAction(TUint8 aFlags)
	{
	InquiryAddrStruct().iFlags=aFlags;
	}

inline TInquirySockAddr::SInquiryAddr &TInquirySockAddr::InquiryAddrStruct() const
	{
	return *(SInquiryAddr*)BTUserPtr();
	}


//
// RFCOMM
//

// Remote Port Parameters class 

inline TRfcommRemotePortParams::TRfcommRemotePortParams()
	: iFlowCtrl(0),
	  iXOnChar(0),
	  iXOffChar(0),
  	  iValidMask(0)	  
	{
	}

inline TUint8 TRfcommRemotePortParams::IsValid() const
	{
	return iValidMask;
	}

inline TBool TRfcommRemotePortParams::GetBitRate(TBps& aBitRate) const
	{
	if(IsValid() & EVMBitRate)
		{
		aBitRate = iBitRate;
		return ETrue;
		}
	else
		return EFalse;
	}

inline TInt TRfcommRemotePortParams::SetBitRate(TBps aBitRate)
	{
	switch(aBitRate)
		{
	case EBps2400:
	case EBps4800:
	case EBps7200:
	case EBps9600:
	case EBps19200:
	case EBps38400:
	case EBps57600:
	case EBps115200:
	case EBps230400:
		iValidMask|=EVMBitRate;
		iBitRate=aBitRate;
		return KErrNone;
		break;
	default:
		return KErrArgument;
		break;
		}
	}

inline TBool TRfcommRemotePortParams::GetDataBits(TDataBits& aDataBits) const
/// If Data Bits are valid, sets reference and returns True, 
/// otherwise, returns False
	{
	if(IsValid() & EVMDataBits)	
		{
		aDataBits = iDataBits;
		return ETrue;
		}
	else
		return EFalse;
	}

inline TInt TRfcommRemotePortParams::SetDataBits(TDataBits aDataBits)
	{
	iValidMask|=EVMDataBits;
	iDataBits=aDataBits;
	return KErrNone;
	}

inline TBool TRfcommRemotePortParams::GetStopBit(TStopBits& aStopBit) const
/// If Stop Bit is valid, sets reference and returns True, 
/// otherwise, returns False
	{
	if(IsValid() & EVMStopBit)
		{
		aStopBit = iStopBit;
		return ETrue;
		}
	else
		return EFalse;
	}

inline TInt TRfcommRemotePortParams::SetStopBit(TStopBits aStopBit)
	{
	iValidMask|=EVMStopBit;
	iStopBit=aStopBit;
	return KErrNone;
	}

inline TBool TRfcommRemotePortParams::GetParity(TParity& aParity) const
/// If Parity is valid, sets reference and returns True, 
/// otherwise, returns False
	{
	if(IsValid() & EVMParity)
		{
		aParity = iParity;
		return ETrue;
		}
	else
		return EFalse;
	}

inline TInt TRfcommRemotePortParams::SetParity(TParity aParity)
	{
	iValidMask|=EVMParity;
	iParity=aParity;
	return KErrNone;
	}

inline TBool TRfcommRemotePortParams::GetFlowCtrl(TUint8& aFlowCtrl) const
/// If Flow Control is valid, sets reference and returns True, 
/// otherwise, returns False
	{
	if(IsValid() & EVMFlowCtrl)
		{
		aFlowCtrl = iFlowCtrl;
		return ETrue;
		}
	else
		return EFalse;
	}

inline TInt TRfcommRemotePortParams::SetFlowCtrl(TUint8 aFlowCtrl)
	{
	iValidMask|=EVMFlowCtrl;
	iFlowCtrl=aFlowCtrl;
	return KErrNone;
	}

inline TBool TRfcommRemotePortParams::GetXOnChar(TUint8& aXOnChar) const
/// If XOn Char is valid, sets reference and returns True, 
/// otherwise, returns False
	{
	if(IsValid() & EVMXOnChar)
		{
		aXOnChar = iXOnChar;
		return ETrue;
		}
	else
		return EFalse;
	}

inline TInt TRfcommRemotePortParams::SetXOnChar(TUint8 aXOnChar)
	{
	iValidMask|=EVMXOnChar;
	iXOnChar=aXOnChar;
	return KErrNone;
	}

inline TBool TRfcommRemotePortParams::GetXOffChar(TUint8& aXOffChar) const
/// If XOff Char is valid, sets reference and returns True, 
/// otherwise, returns False
	{
	if(IsValid() & EVMXOffChar)
		{
		aXOffChar = iXOffChar;
		return ETrue;
		}
	else
		return EFalse;
	}

inline TInt TRfcommRemotePortParams::SetXOffChar(TUint8 aXOffChar)
	{
	iValidMask|=EVMXOffChar;
	iXOffChar=aXOffChar;
	return KErrNone;
	}

// RPN Transaction class

inline TRfcommRPNTransaction::TRfcommRPNTransaction():iParamMask(0)
	{
	}


// Socket Address class
inline TRfcommSockAddr& TRfcommSockAddr::Cast(const TSockAddr &aAddr)
	{
	return *((TRfcommSockAddr *)&aAddr);
	}

