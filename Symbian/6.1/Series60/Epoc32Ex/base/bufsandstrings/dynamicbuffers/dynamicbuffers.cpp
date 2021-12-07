// DynamicBuffers.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "CommonFramework.h"

//
// Common literal text
//
_LIT(KTxtNewLine,"\n");

LOCAL_C void writeBuf(CBufBase* aBuf);
LOCAL_C void standardBufferStuffL(CBufBase* aBuf);
LOCAL_C void showExpandL();
LOCAL_C void waitForKey();
//
// do the example
//
LOCAL_C void doExampleL()
    {
	//
	// do flat buffer demonstration
	//
	_LIT(KTxtFlatBufDemo,"Flat buffer demonstration\n");
	console->Printf(KTxtFlatBufDemo);
	CBufFlat* flatBuf=CBufFlat::NewL(4);
	CleanupStack::PushL(flatBuf);
	flatBuf->SetReserveL(32);
	_LIT(KTxtFlatBufCapacity,"flat buffer capacity=%d\n");
	console->Printf(KTxtFlatBufCapacity,flatBuf->Capacity());
	standardBufferStuffL(flatBuf);
	CleanupStack::PopAndDestroy();
	waitForKey();
	//
	// do segmented buffer demonstration
	//
	_LIT(KTxtSegBufDemo,"Segmented buffer demonstration\n");
	console->Printf(KTxtSegBufDemo);
	CBufSeg* segBuf=CBufSeg::NewL(4);
	CleanupStack::PushL(segBuf);
	standardBufferStuffL(segBuf);
	CleanupStack::PopAndDestroy();
	waitForKey();
	//
	// show ExpandL() and ResizeL()
	//
	showExpandL();
	}


LOCAL_C void standardBufferStuffL(CBufBase* aBuf)
	{
	//
	// insert text into buffer (6 UNICODE chars)
	//
	_LIT(KTxtHello,"Hello!");
	aBuf->InsertL(0,(TAny*)(&KTxtHello)->Ptr(),(&KTxtHello)->Size());
	writeBuf(aBuf);
	//
	// append more text into buffer (another 6 UNICODE chars)
	//
	// NOTE Unicode build differences.
	//
	_LIT(KTxtWorld," world");
	aBuf->InsertL(10,(TAny*)(&KTxtWorld)->Ptr(),(&KTxtWorld)->Size());
	writeBuf(aBuf);
	//
	// read the 5 characters starting at character
	// position 3 from the buffer into a descriptor.
	//
	// NOTE Unicode build differences.
	//
	TBuf<5> des;
	aBuf->Read(6,(TAny*)des.Ptr(),des.Size());
	_LIT(KTxtRead,"read: %S\n");
	console->Printf(KTxtRead,&des);
	//
	// [over]write 5 characters at character position 6
	//
	// NOTE Unicode build differences.
	//
	_LIT(KTxtFolks,"folks");
	aBuf->Write(12,(TAny*)(&KTxtFolks)->Ptr(),(&KTxtFolks)->Size());
	writeBuf(aBuf);
	//
	// delete characters
	//
	TInt startpos = 5;
	TInt length   = 6;
	startpos <<= 1;
	length   <<= 1;
	aBuf->Delete(startpos,length);
	writeBuf(aBuf);
	//
	// compress
	//
	aBuf->Compress();
	writeBuf(aBuf);
	}

LOCAL_C void writeBuf(CBufBase* aBuf)
	{
	//
	// print, segment by segment
	//
	_LIT(KTxtBuffer,"buffer:");
	console->Printf(KTxtBuffer);
	TInt  bufpos=0;
	TPtrC8 bufptr=aBuf->Ptr(bufpos);
	while (bufptr.Length()>0)
		{
		//
		// write out this segment of the buffer.
		// Note that the descriptor 'display' is built differently
		// for Unicode; it also assumes an even number of bytes;
		// this is valid because the granularity of the buffer is 4.
		//
		TPtrC display;
		display.Set((TUint16*)bufptr.Ptr(),(bufptr.Length()>>1));
		_LIT(KFormat1," [%d,%d] %S");
		console->Printf(KFormat1, bufpos, bufptr.Length(), &display);
		//
		// update position within the buffer
		// and the pointer-descriptor.
		//
		bufpos+=bufptr.Length();       // update position
		bufptr.Set(aBuf->Ptr(bufpos)); // should be the next segment
		}
	console->Printf(KTxtNewLine);
	}

	

LOCAL_C void showExpandL()
	{
	_LIT(KTxtShowExpand,"Showing ExpandL()\n");
	console->Printf(KTxtShowExpand);
	//
	// allocate the segmented buffer with 
	// a granularity of 4
	//
	CBufBase* buf=CBufSeg::NewL(4);
	CleanupStack::PushL(buf);
	//
	// insert text into buffer (12 UNICODE chars)
	//
	_LIT(KTxtHelloWorld,"Hello world!");
	buf->InsertL(0,(TAny*)(&KTxtHelloWorld)->Ptr(),(&KTxtHelloWorld)->Size());
	//
	// reserve space for (or 16 16-bit chars (32 bytes))
	//
	buf->ExpandL(12,32); // expand by 32 - may fail
	_LIT(KTxtBufExpanded,"Buffer expanded with uninitialized space: ");
	console->Printf(KTxtBufExpanded);
	writeBuf(buf);
	//
	// now insert 16 16-bit characters
	// one at time.
	//
	// This is CLEARLY INEFFICIENT but shows
	// how successive calls to Write() can be done
	// without risk of failing for lack of memory.
	//
	_LIT(KTxtAtoP,"abcdefghijklmnop");
	TBufC<16> source(KTxtAtoP);
	for (TInt i=0; i<16; i++)
		{
		buf->Write((i+6)<<1,(TAny*)&source[i],2);
		}
	_LIT(KTxtExpandedFilled,"expanded space filled: ");
	console->Printf(KTxtExpandedFilled);
	writeBuf(buf);
	//
	// now adjust size down to 18
	//
	buf->ResizeL(18);
	_LIT(KTxtResized,"resized:");
	console->Printf(KTxtResized);
	writeBuf(buf);
	//
	// destroy buffer
	//
	CleanupStack::PopAndDestroy();
	}

LOCAL_C void waitForKey()
	{
	_LIT(KTxtPressAnyKey,"[press any key]");
	console->Printf(KTxtPressAnyKey);
	console->Getch();
	console->Printf(KTxtNewLine);
	}
