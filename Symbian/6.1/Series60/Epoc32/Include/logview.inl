// LOGVIEW.INL
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

//**********************************
// CLogView
//**********************************

inline const CLogEvent& CLogView::Event() const
	{
	return *iEvent;
	}

inline TBool CLogView::IsValid() const
	{
	return iValid;
	}

//**********************************
// CLogViewRecent
//**********************************

inline TLogRecentList CLogViewRecent::RecentList() const
	{
	return iCurrentList;
	}

//**********************************
// CLogViewDuplicate
//**********************************

inline TLogId CLogViewDuplicate::Source() const
	{
	return iSourceId;
	}
