/*
* ============================================================================
*  Name     : AknQueryData.h
*  Part of  : Avkon
*
*  Description:
*   Implementation of Query data classes for query dialogs
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNQUERYDATA_H
#define AKNQUERYDATA_H

#include <e32std.h>
#include <aknquerycontrol.h>

class CAknQueryDialog;

IMPORT_C TInt GetMaxTextLength(const CAknQueryControl* aControl, const TDes& aDataText, TInt aApiValue);

class MAknQueryData
	{
	public:
		virtual void SetL(CAknQueryControl* aControl, TInt aMaxLength) = 0;
		virtual void Get(CAknQueryControl* aControl) = 0;
	};

template<class T>
class TAknQueryData : public MAknQueryData
	{
	public:
		TAknQueryData(T& aData) : iData(aData) {}

		void SetL(CAknQueryControl* aControl, TInt aMaxLength);
		void Get(CAknQueryControl* aControl);

	public:
		T& iData;
	};

template<>
class TAknQueryData<TDes> : public MAknQueryData
	{
	public:
		TAknQueryData(TDes& aData) : iData(aData) {}

		void SetL(CAknQueryControl* aControl,TInt aMaxLength)
			{ aControl->SetTextL(iData); 
		      aControl->SetTextEntryLength(
				  GetMaxTextLength(aControl,iData,aMaxLength)); }
		void Get(CAknQueryControl* aControl) 
			{ aControl->GetText(iData); }
	public:
		TDes& iData;
	};

template<>
class TAknQueryData<TInt> : public MAknQueryData
	{
	public:
		TAknQueryData(TInt& aData) : iData(aData) {}

		void SetL(CAknQueryControl* aControl,TInt /*aMaxLength*/)
			{ aControl->SetNumberL(iData); }
		void Get(CAknQueryControl* aControl) 
			{ iData=aControl->GetNumber(); }
	public:
		TInt& iData;
	};

template<>
class TAknQueryData<TTime> : public MAknQueryData
	{
	public:
		TAknQueryData(TTime& aData) : iData(aData) {}

		void SetL(CAknQueryControl* aControl,TInt /*aMaxLength*/)
			{ aControl->SetTime(iData); }
		void Get(CAknQueryControl* aControl) 
			{ iData=aControl->GetTime(); }
	public:
		TTime& iData;
	};

template<>
class TAknQueryData<TTimeIntervalSeconds> : public MAknQueryData
	{
	public:
		TAknQueryData(TTimeIntervalSeconds& aData) : iData(aData) {}

		void SetL(CAknQueryControl* aControl,TInt /*aMaxLength*/)
			{ aControl->SetDuration(iData); }
		void Get(CAknQueryControl* aControl) 
			{ iData=aControl->GetDuration(); }
	public:
		TTimeIntervalSeconds& iData;
	};

template<>
class TAknQueryData<TReal> : public MAknQueryData
	{
	public:
		TAknQueryData(TReal& aData) : iData(aData) {}

		void SetL(CAknQueryControl* aControl,TInt /*aMaxLength*/)
			{ aControl->SetFloatingPointNumberL(&iData); }
		void Get(CAknQueryControl* aControl) 
			{ iData=aControl->GetFloatingPointNumberL(); }
	public:
		TReal& iData;
	};

#endif
