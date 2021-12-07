// S32MEM.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class RMemWriteStream
inline RMemWriteStream::RMemWriteStream(const MExternalizer<TStreamRef>& anExter)
	: RWriteStream(anExter)
	{}

// Class RDesWriteStream
inline RDesWriteStream::RDesWriteStream(const MExternalizer<TStreamRef>& anExter)
	: RWriteStream(anExter)
	{}

// Class RBufWriteStream
inline RBufWriteStream::RBufWriteStream(const MExternalizer<TStreamRef>& anExter)
	: RWriteStream(anExter)
	{}
inline void RBufWriteStream::Append(CBufBase& aBuf)
	{Insert(aBuf,aBuf.Size());}

