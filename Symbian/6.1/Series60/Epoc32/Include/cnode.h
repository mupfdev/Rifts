/// cnode.h
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//
     
//This contains the definitions of CDataDelete, CDataNoDelete, CIntAttribute, CNode, and CTypedNode.
//
//CDataNoDelete is a base class to CDataDelete and are essentially a wrapper around an HBufC16.
//The node owns the data that is added to it and therefore is responsible for deleting all its data,
//hence theses two classes allow a user to have non deletable data. Internally to the node it is also 
//sometimes necessary to change the data into either deletable or non-deletable data api's are provided
//for this.
//
//CIntAttribute is wrapper around a TInt, this is provided as the nodes attribute value is a CBase* however
//it might be desirable to store integer's in here. Attribute value is owned by the node therefore the node is
//responsible for deleting it.
//
//CNode is the basis for constructing a tree. It consists of an array of child nodes, node type, a parent node,
//an array of attributes, and a data member. Internally the data member is defined as CDataNoDelete however
//to the user all the exported api's take an HBufC16*. Data is owned by the node and is destroyed by the node,
//However in certain circumstances this is not desirable hence the api's to make the data non-deletable. The
//node type is defined as a TAny* however normal usage would use the templated node - CTypedNode. The node type
//is used to identify groups of nodes. The attribute array is fairy simple and consists of AttributeType and 
//AttributeValue. AttributeType can be defined by using the templated class and should be a 32bit value. AttributeValue
//can be any object derived from CBase and the node takes ownership therefore the node delete's it.
//Basic usage should be to use the templated class in order to make use of the templated types (TNodeType,TAttributeType).
//Create a node for example:
//CTypedNode<CNode*, const TDesC*> *tree = CTypedNode<CNode*, const TDesC*>::NewL(0,0);
//add a new child:
//CNODE *TestChildNode1 = tree->AppendNodeL(aTempNodeForNodeType);
//add some data:
//TestChildNode1->SetDataL(aHBufC16);
//add an attribute:
//TestChildNode1->->AddAttributeL(aTAttributeType,aCBasePointerAttributeValue);
//Explanation of individual api's is documented below.


 

#ifndef __CNODE_H__
#define __CNODE_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

//Granularity of arrays
const TInt KGranularity = 5;

//enum of panic reasons
enum TNodePanic
	{
	ENodeBadArgument,
	ENodeNoChildren,
	ENoData,
	EAttributeFailure
	};

//node panic function
GLREF_C void Panic(TNodePanic aPanic);

//Wrapper around an HBufC16 doesn't delete data
class CDataNoDelete : public CBase
	{
public:
	CDataNoDelete(HBufC16* aData);
	virtual ~CDataNoDelete();
	HBufC16* SetData(HBufC16* aData);
	virtual void ResetDataPointer(HBufC16* aData);
	HBufC16* Data();

protected:
	HBufC16* iData;
	};

//Wrapper around an HBufC16 does delete data
class CDataDelete : public CDataNoDelete
	{
public:
	CDataDelete(HBufC16* aData);
	virtual ~CDataDelete();
	virtual void ResetDataPointer(HBufC16* aData);
	};

//Wrapper around an HBufC16 does delete data (FileName)
// After Removing referenced File 
class CFileDataDelete : public CDataNoDelete
	{
public:
	CFileDataDelete(HBufC16* aData);
	virtual ~CFileDataDelete();
	virtual void ResetDataPointer(HBufC16* aData);
private:
	void RemoveFile();
	};

//Wrapper around a TInt used for attribute values in order to allow the node to call a dtor
class CIntAttribute : public CBase
	{
public:
	inline CIntAttribute(TInt aInteger);		
	inline TInt Int() const;
private:
	CIntAttribute();
	TInt iInteger;
	};

//
// Node class
// Normal usage would be to use CTypedNode in order to use specific templated types
//

class CNode : public CBase 
	{
public:
	IMPORT_C ~CNode();

	//NewL parameters aType to indentify the type of node, CNode* to set the parent of this node
	IMPORT_C static CNode* NewL(TAny* aType,CNode* aParent);

	//Deletes a child node which is passed in as a parameter
	IMPORT_C void DeleteChildNode(CNode* aNode);

	//Deletes all the child nodes haging of this node
	IMPORT_C void DeleteAllChildNodes();

	//Creates a new node and adds it to the childlist, reference to new node is returned. Can leave if it can't allocate memory for a new node
	//Type of node is the parameter
	IMPORT_C CNode& AppendNodeL(TAny* aType = 0);

	//Appends a node which is passed in as a parameter to this node, so its added to the childlist
	IMPORT_C void AppendNodeToThisNodeL(CNode* aNode);

	//Sets the data in the node to the parameter that is passed in. It's deletable and the node will delete it in dtor
	//Push aDataNowNodeOwns onto the CleanupStack before calling then pop off on return
	IMPORT_C void SetDataL(HBufC16* aDataNowNodeOwns);

	//returns the data stored in the node, which is returned as an HBufC16*
	IMPORT_C HBufC16* Data() const;

	//WARNING this function can leave as it deletes the wrapper object and then creates
	//a new non deletable wrapper object and sets the data pointer inside the new object
	//IF THIS LEAVES YOU WILL LOSE YOUR DATA
	IMPORT_C void SetDataNoDeleteL();

	//WARNING this function can leave as it deletes the wrapper object and then creates
	//a new deletable wrapper object then sets the pointer in the new object
	IMPORT_C void ClearSetDataNoDeleteL();

	// Sets the data in the node to the FileName parameter that is passed in. 
	// It's deletable and the node will delete it, and the file it refers to in dtor
	// Push aDataLocationNowNodeOwns onto the CleanupStack before calling then pop off on return
	IMPORT_C void SetFileDataL(HBufC16* aFileDataLocationNowNodeOwns);

	//Resets the data pointer to point to aData parameter will delete the data that is owned by the node
	IMPORT_C void ResetDataPointer(HBufC16* aData);

	//returns a reference to the absolute root of the tree
	IMPORT_C const CNode& Root() const;

	//returns a child node which is stored in the array of children. The child node is accessed by the index that is the parameter.
	IMPORT_C CNode* Child(TInt aByIndex) const;

	//Returns either the first child of this node if the parameter is NULL. Or it returns the next chld in the array after
	//the child passed in as a parameter
	IMPORT_C CNode* NextChild(const CNode* aNode = NULL) const;

	//returns the previous child to the child passed in as a parameter. The node parameter is a reference because its the child previous
	//to the node passed in which obviously must exist
	IMPORT_C CNode* PrevChild(const CNode& aNode) const;

	//Returns the parent of this node
	IMPORT_C CNode* Parent() const;

	//WARNING this function can leave as it calls AppendNodeToThisNode. The aParent parameter is the node to which you would like to make
	//the parent of 'this' node.
	//It removes itself from the childlist of it's current parent
	IMPORT_C void ReparentL(CNode* aParent);

	//Returns the next sibling which means in effect that it asks for the next child of its parent.
	//Sibling means brother or sister.
	IMPORT_C CNode* NextSibling() const;

	//Returns the previous sibling which means in effect that it asks for the previous child of its parent.
	//Sibling means brother or sister.
	IMPORT_C CNode* PrevSibling() const;

	//returns the number of children that this node has
	IMPORT_C TInt NumberImmediateChildren() const;

	//Deletes the attribute of which is of aAttributeType (the parameter)
	//WARNING Attribute values of nodes will be deleted as the node owns them if you don't want it deleted then use a wrapper
	IMPORT_C void DeleteAttribute(TAny* aAttributeType);

	//Deletes all the attributes of this node
	//WARNING Attribute values of nodes will be deleted as the node owns them if you don't want it deleted then use a wrapper
	IMPORT_C void DeleteAllAttributes();

	//remove an attribute without deleting it, this is done by simply setting the attributeValue pointer to NULL
	//WARNING you are now responsiblefor the destruction of this attribute value
	IMPORT_C void RemoveAttributeNoDelete(TAny* aAttributeType);

	// Returns the number of attributes that this node has
	IMPORT_C TInt AttributeCount() const;

	//Returns the type of attribute (AttributeType) at a given index...NOT the attributeValue
	IMPORT_C TAny* AttributeTypeByIndex(TInt aIndex) const; 

	//Returns the value of an attribute (AttributeValue) at a given index...NOT the attributeType
	IMPORT_C CBase* AttributeByIndex(TInt aIndex) const;
	IMPORT_C CBase* AttributeByIndex(TInt aIndex,TAny*& aType) const;

	//Adds an attribute, parameters are the type of attribute and its value
	//WARNING node takes ownership of aAttributeValue
	////Push aAttributeValue onto the CleanupStack before calling then pop off on return
	IMPORT_C void AddAttributeL(TAny* AttributeType, CBase* aAttributeValue);

	//Adds data to the node and also adds an attribute, parameters are the Data to be added, the type of attribute and its value
	//WARNING node takes ownership of aData and aAttributeValue
	////Push aAttributeValue and aData onto the CleanupStack before calling then pop off on return
	IMPORT_C void AddDataAndAttributeL(HBufC16 *aData, TAny* AttributeType, CBase* aAttributeValue);

	//Returns an attribute value for the given AttributeType(the parameter)
	IMPORT_C CBase* Attribute(TAny* AttributeType) const;

	//Returns TRUE if the attribute of the given type exists
	IMPORT_C TBool AttributeExists(TAny* aAttributeType) const;

	//Returns the node type
	IMPORT_C TAny* Type() const;

	//Sets the node type to be aType (the parameter)
	IMPORT_C void SetType(TAny* aType);


protected:
	//ctor
	CNode(TAny* aType, CNode* aParent);

	//internal finds a child which is passed in as a parameter
	TInt FindChild(const CNode* aNode) const;

	HBufC16* SetupDeletableOrNonDeleteableDataLC();
	void AdjustBasePointers();
private:
	// Reserved for future expansion
	virtual void Reserved1();			
	virtual void Reserved1() const;

protected:
	//the Type of Node
	TAny* iType;

	//This Nodes parent
	CNode *iParent;

	// stores attribute type and value. iTypes must be Flat array
	CArrayPtrFlat<CBase> iValues;
	CArrayPtrFlat<TAny> iTypes;

	TInt32* iTypesBasePtr;
	CDataNoDelete* iDataValue;
//
	//An array of child nodes
	CArrayPtr<CNode> *iChildList;
private:
	TAny*	iReserved;						// Reserved for future expansion
	};


//CTypedNode is derived from CNode and is a thin template. TNodeType you should define as a 32 bit value
//TAttributeType should be defined as a 32 bit value
//FOR EXPLANATION OF API'S SEE ABOVE 
template <class TNodeType, class TAttributeType>
class CTypedNode : public CNode 
	{
public:
	inline static CTypedNode* NewL(TNodeType aType,CNode* aParent);
	inline void DeleteChildNode(CNode* aNode);
	inline void DeleteAllChildNodes();
	inline CTypedNode<TNodeType,TAttributeType>& AppendNodeL(TNodeType aType);
	inline void AppendNodeToThisNodeL(CNode* aNode);
	inline void SetDataL(HBufC16* aDataNowNodeOwns);
	inline void SetDataNoDeleteL();
	inline void ClearSetDataNoDeleteL();
	inline void SetFileDataL(HBufC16* aFileDataLocationNowNodeOwns);
	inline void ResetDataPointer(HBufC16* aData);
	inline HBufC16* Data() const;
	inline const CTypedNode& Root() const;
	inline CTypedNode* Child(TInt aByIndex) const;
	inline CTypedNode* NextChild(const CNode* aNode = NULL) const;
	inline CTypedNode* PrevChild( const CNode& aNode) const;
	inline CTypedNode* Parent() const;
	inline void ReparentL(CNode* aParent);
	inline CTypedNode* NextSibling() const;
	inline CTypedNode* PrevSibling() const;
	inline TInt NumberImmediateChildren() const;
	inline void DeleteAttribute(TAttributeType aAttributeType);
	inline void DeleteAllAttributes();
	inline void RemoveAttributeNoDelete(TAttributeType aAttributeType);
	inline TInt AttributeCount() const; // Returns the number of attributes
	inline TAttributeType AttributeTypeByIndex(TInt aIndex) const; 
	inline CBase* AttributeByIndex(TInt aIndex) const; 
	inline CBase* AttributeByIndex(TInt aIndex,TAttributeType& aType) const; 
	inline void AddAttributeL(TAttributeType aAttributeType, CBase* aAttributeValue);
	inline void AddDataAndAttributeL(HBufC16 *aData, TAttributeType aAttributeType, CBase* aAttributeValue);
	inline CBase* Attribute(TAttributeType aAttributeType) const;
	inline TBool AttributeExists(TAttributeType aAttributeType) const;
	inline TNodeType Type() const;
	inline void SetType(TNodeType aType);
protected:
	CTypedNode(TNodeType aType, CNode* aParent);
	};
#include "cnode.inl"
#endif
