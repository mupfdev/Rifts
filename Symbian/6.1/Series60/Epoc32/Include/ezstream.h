// EZLib: ZSTREAM.H
// Copyright (C) Symbian LTD 1999
//
// Declaration for CEZStream class.  
//

#ifndef __EZZSTREAM_H__
#define __EZZSTREAM_H__

#include <ezlib.h>

class CEZZStream : public CBase
	{
public:
	enum 
		{
		EStreamError = -Z_STREAM_ERROR,
		EDataError = -Z_DATA_ERROR,
		EBufError = -Z_BUF_ERROR,
		EVersionError = -Z_VERSION_ERROR,
		EUnexpected
		};
public:
	IMPORT_C void SetInput(const TDesC8& aInputData);
	IMPORT_C void SetOutput(TDes8& aOutputData);

	IMPORT_C TPtrC8 OutputDescriptor() const;
	IMPORT_C TInt TotalOut() const;
	IMPORT_C TInt TotalIn() const;
	IMPORT_C TInt32 Adler32() const;
	IMPORT_C TInt AvailIn() const;
	IMPORT_C TInt AvailOut() const;

	IMPORT_C TInt Progress(TInt aTotalLength) const;
	
protected:
	CEZZStream();

	
protected:
	z_stream iStream;

	// This pointer is reset every time SetOutput is called.  It maintains a pointer to the
	// start of the output buffer which is being written to.  We cannot use iStream.next_out,
	// because zlib will modifify this during its deflate and inflate.
	
	TUint8* iOutputPointer;
	TInt iOutputBufferLength;
	};

#endif
