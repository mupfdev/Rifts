/* Copyright (c) 2001, Nokia. All rights reserved */
//
//	ShapeListManager.cpp
//


#include	"ShapeListManager.h"
#include	"rectangle.h"
#include	"circle.h"

using namespace NShapes;


EXPORT_C CShapeListManager* CShapeListManager::NewLC()
	{
	CShapeListManager*	self = new (ELeave) CShapeListManager;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
	}

EXPORT_C CShapeListManager* CShapeListManager::NewL()
	{
	CShapeListManager*	self = CShapeListManager::NewLC();
    CleanupStack::Pop(self);
    return self;
	}

EXPORT_C CShapeListManager::CShapeListManager()
    {
	//	No implementation required
    }

EXPORT_C CShapeListManager::~CShapeListManager()
    {
    iShapeList.ResetAndDestroy();
    }

EXPORT_C void CShapeListManager::ConstructL()
    {
	//	No implementation required
    }

EXPORT_C void CShapeListManager::Clear()
	{
	iNextShapeIndex = 0;	//	The first shape in the list
    iShapeList.ResetAndDestroy();
	}

EXPORT_C void CShapeListManager::AddShapeL(TShape* aShape)
    {
	User::LeaveIfError(iShapeList.Append(aShape));
    }

EXPORT_C TShape* CShapeListManager::GetNextShape()
    {
    if (iShapeList.Count() > 0) 
		{
        if (iNextShapeIndex < iShapeList.Count()) 
			{
            TShape* shape = iShapeList[iNextShapeIndex];
            ++iNextShapeIndex;
            return shape;
			}
		//	Gone past the end, so reset the index
        iNextShapeIndex = 0;
		}
    return NULL;
    }

EXPORT_C TStreamId CShapeListManager::StoreL(CStreamStore& aStore) const
    {
    RStoreWriteStream stream;

	// Create a stream within the store
    TStreamId id = stream.CreateLC(aStore);

	// Write the data to the stream
    ExternalizeL(stream); 
    stream.CommitL();

    CleanupStack::PopAndDestroy(); // the stream

    return id; // return the stream ID          
    }

EXPORT_C void CShapeListManager::ExternalizeL(RWriteStream& aStream) const
    {
    TInt count = iShapeList.Count();

    aStream.WriteInt16L((TInt16)count);

    for (TInt index = 0; index < count; ++index)
        {
        const TShape* shape = iShapeList[index];
        shape->ExternalizeL(aStream);
        }
    }

EXPORT_C void CShapeListManager::RestoreL(const CStreamStore& aStore, const TStreamId& aStreamId)
    {
    Clear();

    RStoreReadStream stream;
	// Open the stream
    stream.OpenLC(aStore, aStreamId);

	// Read the data from the stream
    InternalizeL(stream); 

    CleanupStack::PopAndDestroy(); // the stream
    }

EXPORT_C void CShapeListManager::InternalizeL(RReadStream& aStream)
    {

    TInt count = aStream.ReadInt16L();
    for (TInt index = 0; index < count; ++index)
        {
        TShape* shape = NULL;
        switch (TShape::ReadShapeTypeL(aStream))
            {
            case KRectangle :
                shape = new (ELeave) TRectangle();
                break;
            case KCircle :
                shape = new (ELeave) TCircle();
                break;
            default :
                User::Leave(KErrCorrupt);
            }
	    CleanupStack::PushL(shape);
        shape->InternalizeL(aStream);
		User::LeaveIfError(iShapeList.Append(shape));
	    CleanupStack::Pop(shape);	//	Now owned by iShapeList
        }
    }

// requirement for E32 DLLs
EXPORT_C TInt E32Dll(TDllReason)
	{
	return KErrNone;
	}
