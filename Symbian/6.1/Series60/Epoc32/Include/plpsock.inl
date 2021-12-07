// PLPSOCK.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//////////////////////////////////////////////////////////////////////////////
//
// TPlpAddr
//
//////////////////////////////////////////////////////////////////////////////

struct SPlpAddr
    {

    TUint iInterface;
    TText8 iName[1];
    };
  
inline TPlpAddr::TPlpAddr()
//
// Default C'tor
//
    {

    SetFamily(KFamilyPlp);
    SetPort(KPlpPortAny);
    SetInterface(KPlpInterfaceAny);
    SetServiceName(TPtrC8(0,0));
    }

inline TPlpAddr::TPlpAddr(TUint aInterface, const TDesC8 &aDes, TUint aPort)
//
// C'tor which also copies a service name
//
    {

    SetFamily(KFamilyPlp);
    SetPort(aPort);
    SetInterface(aInterface);
    SetServiceName(aDes);
    }

inline void TPlpAddr::SetServiceName(const TDesC8 &aDes)
//
// Set the service name to something different
//
    {
    
    SPlpAddr* addr = (SPlpAddr*)UserPtr();

    TPtr8 ptr(addr->iName, KPlpMaxServiceName);
    ptr.Copy(aDes);
    SetUserLen(_FOFF(SPlpAddr, iName) + ptr.Length());
    }

inline TPtrC8 TPlpAddr::ServiceName() const
//
// Get a pointer to the service name
//
    {

    SPlpAddr* addr = (SPlpAddr*)UserPtr();
    return TPtrC8(addr->iName, ((TPlpAddr*)this)->GetUserLen()-_FOFF(SPlpAddr, iName) );
    }

    
inline TUint TPlpAddr::Interface() const
//
// Get the interface number
//
    {

    return ((SPlpAddr*)UserPtr())->iInterface;
    }

inline void TPlpAddr::SetInterface(TUint aInterface)
//
// Set interface number
//
    {

    ((SPlpAddr*)UserPtr())->iInterface = aInterface;
    }
