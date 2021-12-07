// MSVFIND.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

//**********************************
// CMsvFindOperation
//**********************************

inline const CMsvFindResultSelection& CMsvFindOperation::GetFindResult() const
	{
	return *iFindResultSel;
	}
