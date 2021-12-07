// COMMDB.INL
//
// Comms Database and Table inline functions
//
// Written by AEW, July 1998
// Copyright (C) Symbian Ltd 1998

#ifndef __COMMDB_INL__
#define	__COMMDB_INL__

#include <commdb.h>

inline TCommDbDatabaseType CCommsDatabase::Type() const
	{
	return iType;
	}	

inline RDbNamedDatabase* CCommsDatabaseBase::Database()
	{
	return &iDatabase;
	}

inline void CCommsDbTableView::GetTableName(TDes& aTableName) const
	{
	aTableName=iTableName;
	}

#endif

