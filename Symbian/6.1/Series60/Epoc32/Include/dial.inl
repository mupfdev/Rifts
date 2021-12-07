// DIAL.INL
// Written by Michael Phan, October 1997
// Copyright (C) Psion Software PLC 1997
//

inline  void TDialLocation::ClearDialLocationFlags (TUint aFlags)
    {
    iFlags &= ~aFlags;
    }
inline   TBool TDialLocation::IsReturnPhoneNumberWithPlusFormat() const
    {
    return(iFlags & KReturnPhoneNumberWithPlusFormat);
    }

