#ifndef CIPADDRESS___
#define CIPADDRESS___

#include <in_sock.h>

class CIpAddress : public CBase
	{
	public:
		IMPORT_C static CIpAddress*	NewL(const TDesC& aAddr);
		IMPORT_C static CIpAddress*	NewLC(const TDesC& aAddr);
		inline static CIpAddress*	NewL();
		inline static CIpAddress*	NewLC();
		IMPORT_C 					~CIpAddress();
		IMPORT_C void				SetAddrL(const TDesC& aAddr);
		IMPORT_C const TDesC&		Addr() const;
	private:
		CIpAddress();
	private:
		HBufC*				iAddr;
	};

inline CIpAddress* CIpAddress::NewL()
	{
	return NewL(KNullDesC);
	}

inline CIpAddress* CIpAddress::NewLC()
	{
	return NewLC(KNullDesC);
	}

#endif