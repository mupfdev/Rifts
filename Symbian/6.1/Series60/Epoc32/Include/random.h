//
// random.h
// 
// (c) 1999 Symbian Ltd

#ifndef __RANDOM_H__
#define __RANDOM_H__

class TRandom

	{
	public:
		IMPORT_C static void Random(TDes8& aDestination);
#ifdef BOGUS_RANDOM
		IMPORT_C static void Reset(void);
	private:
		static TInt xn;
#endif // BOGUS_RANDOM
#ifdef IMPL_RANDOM
		//static HBufC8* buffer;
		//static TUint8* buffer;
		//static TInt pos;
#endif // IMPL_RANDOM
	};

class RRandomSession:public RSessionBase

	{
public:
	IMPORT_C RRandomSession(void);
	IMPORT_C TInt GetRandom(TDes8& aDestination);
	IMPORT_C void ConnectL(void);
	};

#endif // __RANDOM_H__