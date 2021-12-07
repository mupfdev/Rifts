/* Copyright (c) 2001, Nokia. All rights reserved */
//
// ShapeListManager.h
//
/*!
	@header ShapeListManager
	
*/

#ifndef __SHAPELISTMANAGER_H
#define __SHAPELISTMANAGER_H

#include <e32std.h>
#include <w32std.h>

#include "shape.h"


/*!
  @class	CShapeListManager
  @discussion	An instance of this class is an engine that manages a list
  of shapes..
  */
class CShapeListManager : public CBase
	{
public:
/*!
  @function	NewLC
  @abstract	Creates a new instance of the engine.
  @result	Returns the engine
  */
	IMPORT_C static CShapeListManager* NewLC();
/*!
  @function	NewL
  @abstract	Creates a new instance of the engine.
  @result	Returns the engine
  */
	IMPORT_C static CShapeListManager* NewL();

/*!
  @function	~CShapeListManager
  @abstract	Destroys the instance, and release all associated resources. 
  */
    IMPORT_C ~CShapeListManager();

/*!
  @function	Clear
  @abstract	Clears the list of shapes. 
  */
	IMPORT_C void Clear();

/*!
  @function	AddShape
  @abstract	Adds a shape to the list
  @param aShape the object to add to the list. 
  */
    IMPORT_C void AddShapeL(NShapes::TShape* aShape);

/*!
  @function	GetNextShape
  @abstract	Returns the next shape in the list and increments the next shape index. 
  If there is no such shape, then it returns NULL, and resets the next shape index.
  */
    IMPORT_C NShapes::TShape* GetNextShape();

/*!
  @function	StoreL
  @abstract	Stores the instance to the specified store
  @param aStore the store to stream the object to
  @result Returns the id of the store within the stream.
  */
    IMPORT_C TStreamId StoreL(CStreamStore& aStore) const;

/*!
  @function	ExternalizeL
  @abstract	Stores the instance to the specified stream
  @param aStream the stream to stream the object to
  */
    IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

/*!
  @function	RestoreL
  @abstract	Restores the instance from the specified stream within the specified store
  @param aStore the store containing the data
  @param aStreamId the id of the stream within the store
  */
    IMPORT_C void RestoreL(const CStreamStore& aStore, const TStreamId& aStreamId);

/*!
  @function	InternalizeL
  @abstract	Restores the instance from the specified stream
  @param aStream the stream to stream the object from
  */
    IMPORT_C void InternalizeL(RReadStream& aStream);

protected:
/*!
  @function	CShapeListManager
  @abstract	Performs any first stage construction
  */
    IMPORT_C CShapeListManager();

/*!
  @function	ConstructL
  @abstract	Performs any second stage construction
  */
    IMPORT_C void ConstructL();

private:
	/*! @var iNextShapeIndex	The index of the next shape	*/
    TInt iNextShapeIndex;

	/*! @var iShapeList	The list of shapes	*/
    RPointerArray<NShapes::TShape> iShapeList;
	};

#endif	//	__SHAPELISTMANAGER_H
