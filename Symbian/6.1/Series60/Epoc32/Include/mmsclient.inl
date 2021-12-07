/*
* ============================================================================
*  Name     : CMmsClientMtm from mmsclient.inl
*  Part of  : mmsengine\clientmtm
*
*  Description:
*     Inline functions for CMmsClientMtm
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

inline TUid CMmsClientMtm::Type() const
    {
    return CBaseMtm::Type();
    }

inline CMsvSession& CMmsClientMtm::Session()
    {
    return CBaseMtm::Session();
    }

inline void CMmsClientMtm::SetCurrentEntryL( CMsvEntry * aEntry )
    {
    CBaseMtm::SetCurrentEntryL( aEntry );
    }

inline void CMmsClientMtm::SwitchCurrentEntryL( TMsvId aId )
    {
    CBaseMtm::SwitchCurrentEntryL( aId );
    }

inline CMsvEntry& CMmsClientMtm::Entry() const
    {
    return CBaseMtm::Entry();
    }

inline TBool CMmsClientMtm::HasContext() const
    {
    return CBaseMtm::HasContext();
    }

inline CRichText& CMmsClientMtm::Body()
    {
    return CBaseMtm::Body();
    }

inline const CRichText& CMmsClientMtm::Body() const
    {
    return CBaseMtm::Body();
    }

inline const CDesCArray& CMmsClientMtm::AddresseeList()
    {
    return CBaseMtm::AddresseeList();
    }
           
// End of File
