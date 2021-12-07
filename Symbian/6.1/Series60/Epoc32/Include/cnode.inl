/// cnode.inl
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//


//
// INLINED Node implementation
// for description of templated api's see CNODE.H
//

//CTOR of non-deletable data
inline CDataNoDelete::CDataNoDelete(HBufC16* aData)
	: iData(aData)
	{
	}

//DTOR doesn't delete the data member
inline CDataNoDelete::~CDataNoDelete()
	{
	}

//Accessor method to set the iData pointer to the parameter passed in
//Ownership is taken here
// Returns the previous value
inline HBufC16* CDataNoDelete::SetData(HBufC16* aData)
	{
	HBufC16* prevVal = iData;
	iData = aData;
	return prevVal;
	}

//Resets data pointer to point to aData, data is not deleted
inline void CDataNoDelete::ResetDataPointer(HBufC16 *aData)
	{
	iData = aData;
	}

//Accessor method to get the data
inline HBufC16* CDataNoDelete::Data()
	{
	return iData;
	}

//CTOR of deletable data
inline CDataDelete::CDataDelete(HBufC16* aData)
	: CDataNoDelete(aData)
	{
	}

//DTOR of deletable data...DELETES THE DATA
inline CDataDelete::~CDataDelete()
	{
	delete iData;
	}

inline void CDataDelete::ResetDataPointer(HBufC16* aData)
	{
	delete iData;
	iData = aData;
	}

//CTOR of deletable file data
inline CFileDataDelete::CFileDataDelete(HBufC16* aData)
	: CDataNoDelete(aData)
	{
	}

// DTOR of deletable file data...
// DELETES THE DATA AFTER REMOVING THE REFERENCED FILE
inline CFileDataDelete::~CFileDataDelete()
	{
	RemoveFile();
	delete iData;
	}

inline void CFileDataDelete::ResetDataPointer(HBufC16* aData)
	{
	RemoveFile();
	delete iData;
	iData = aData;
	}

inline void CFileDataDelete::RemoveFile()
	{
	// When this panics 
	// Someone somewhere has incorrectly reset this node's data
	__ASSERT_DEBUG(iData,Panic(ENoData));
	RFs fs;
	// If connect fails we can sadly do nothing to remove the file
	// it will be left lying around :-<
	if(fs.Connect() == KErrNone)
		{
		fs.Delete(iData->Des());	
		fs.Close();
		}
	}

//CTOR of wrapper for integer attributes
inline CIntAttribute::CIntAttribute(TInt aInteger)
	: iInteger(aInteger)
	{
	}

//Accessor method
inline TInt CIntAttribute::Int() const
	{
	return iInteger;
	}


//
//
//TEMPLATED FUNCTIONS SEE CNODE.H FOR DESCRIPTIONS OF API'S
//
//
template <class TNodeType, class TAttributeType>
inline CTypedNode<TNodeType, TAttributeType>* CTypedNode<TNodeType, TAttributeType>::NewL(TNodeType aType, CNode* aParent)
	{
	return (STATIC_CAST(CTypedNode*,CNode::NewL(CONST_CAST(TAny*,REINTERPRET_CAST(const TAny*,aType)),aParent)));
	}


template <class TNodeType, class TAttributeType>
inline CTypedNode<TNodeType, TAttributeType>::CTypedNode(TNodeType aType, CNode* aParent)
	: CNode(CONST_CAST(TAny*,REINTERPRET_CAST(const TAny*,aType)),aParent)
	{}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::DeleteChildNode(CNode* aNode)
	{
	CNode::DeleteChildNode(aNode);
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::DeleteAllChildNodes()
	{
	CNode::DeleteAllChildNodes();
	}

template <class TNodeType, class TAttributeType>
inline CTypedNode<TNodeType, TAttributeType>& CTypedNode<TNodeType, TAttributeType>::AppendNodeL(TNodeType aType)
	{
	return (STATIC_CAST(CTypedNode& , CNode::AppendNodeL(CONST_CAST(TAny*,REINTERPRET_CAST(TAny*,aType)))));
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::AppendNodeToThisNodeL(CNode* aNode)
	{
	CNode::AppendNodeToThisNodeL(aNode);
	}

template <class TNodeType, class TAttributeType>
inline CTypedNode<TNodeType, TAttributeType>* CTypedNode<TNodeType, TAttributeType>::NextChild(const CNode* aNode) const
	{
	return (STATIC_CAST(CTypedNode*,CNode::NextChild(aNode)));
	}

template <class TNodeType, class TAttributeType>
inline CTypedNode<TNodeType, TAttributeType>* CTypedNode<TNodeType, TAttributeType>::PrevChild(const CNode& aNode) const
	{
	return (STATIC_CAST(CTypedNode*,CNode::PrevChild(aNode)));
	}

template <class TNodeType, class TAttributeType>
inline CTypedNode<TNodeType, TAttributeType>* CTypedNode<TNodeType, TAttributeType>::Parent() const
	{
	return (STATIC_CAST(CTypedNode*,CNode::Parent()));
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::ReparentL(CNode* aParent)
	{
	CNode::ReparentL(aParent);
	}

template <class TNodeType, class TAttributeType>
inline CTypedNode<TNodeType, TAttributeType>* CTypedNode<TNodeType, TAttributeType>::NextSibling() const
	{
	return (STATIC_CAST(CTypedNode*,CNode::NextSibling()));
	}

template <class TNodeType, class TAttributeType>
inline CTypedNode<TNodeType, TAttributeType>* CTypedNode<TNodeType, TAttributeType>::PrevSibling() const
	{
	return (STATIC_CAST(CTypedNode*,CNode::PrevSibling()));
	}

template <class TNodeType, class TAttributeType>
inline TInt CTypedNode<TNodeType, TAttributeType>::NumberImmediateChildren() const
	{
	return (CNode::NumberImmediateChildren());
	}

template <class TNodeType, class TAttributeType>
inline const CTypedNode<TNodeType, TAttributeType>& CTypedNode<TNodeType, TAttributeType>::Root() const
	{
	return (STATIC_CAST(const CTypedNode&,CNode::Root()));
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::SetDataL(HBufC16 *aData)
	{
	CNode::SetDataL(aData);
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::SetDataNoDeleteL()
	{
	CNode::SetDataNoDeleteL();
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::ClearSetDataNoDeleteL()
	{
	CNode::ClearSetDataNoDeleteL();
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::SetFileDataL(HBufC16 *aData)
	{
	CNode::SetFileDataL(aData);
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::ResetDataPointer(HBufC16* aData)
	{
	CNode::ResetDataPointer(aData);
	}

template <class TNodeType, class TAttributeType>
inline HBufC16* CTypedNode<TNodeType, TAttributeType>::Data() const
	{
	return (CNode::Data());
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::DeleteAttribute(TAttributeType aAttributeType)
	{
	CNode::DeleteAttribute(CONST_CAST(TAny*, REINTERPRET_CAST(const TAny*,aAttributeType)));
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::DeleteAllAttributes()
	{
	CNode::DeleteAllAttributes();
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::RemoveAttributeNoDelete(TAttributeType aAttributeType)
	{
	CNode::RemoveAttributeNoDelete(CONST_CAST(TAny*,REINTERPRET_CAST(const TAny*,aAttributeType)));
	}

template <class TNodeType, class TAttributeType>
inline TInt CTypedNode<TNodeType, TAttributeType>::AttributeCount() const
	{
	return(CNode::AttributeCount());
	}

template <class TNodeType, class TAttributeType>
inline TAttributeType CTypedNode<TNodeType, TAttributeType>::AttributeTypeByIndex(TInt aIndex) const
	{
	return(REINTERPRET_CAST(TAttributeType, CNode::AttributeTypeByIndex(aIndex)));
	}

template <class TNodeType, class TAttributeType>
inline CBase* CTypedNode<TNodeType, TAttributeType>::AttributeByIndex(TInt aIndex) const
	{
	return(CNode::AttributeByIndex(aIndex));
	}

template <class TNodeType, class TAttributeType>
inline CBase* CTypedNode<TNodeType, TAttributeType>::AttributeByIndex(TInt aIndex,TAttributeType& aType) const
	{
	TAny* type;
	CBase* ret=CNode::AttributeByIndex(aIndex,type);
	aType=REINTERPRET_CAST(TAttributeType, type);
	return ret;
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::AddAttributeL(TAttributeType aAttributeType, CBase* aAttributeValue)
	{
	CNode::AddAttributeL(CONST_CAST(TAny*, REINTERPRET_CAST(const TAny*,aAttributeType)),aAttributeValue);
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::AddDataAndAttributeL(HBufC16 *aData, TAttributeType aAttributeType, CBase* aAttributeValue)
	{
	CNode::AddDataAndAttributeL(aData,CONST_CAST(TAny*, REINTERPRET_CAST(const TAny*,aAttributeType)),aAttributeValue);
	}

template <class TNodeType, class TAttributeType>
inline CTypedNode<TNodeType, TAttributeType>* CTypedNode<TNodeType, TAttributeType>::Child(TInt aByIndex) const
	{
	return (REINTERPRET_CAST(CTypedNode*,CNode::Child(aByIndex)));
	}

template <class TNodeType, class TAttributeType>
inline CBase* CTypedNode<TNodeType, TAttributeType>::Attribute(TAttributeType aAttributeType) const
	{
	return (CNode::Attribute(CONST_CAST(TAny*, REINTERPRET_CAST(const TAny*,aAttributeType))));
	}

template <class TNodeType, class TAttributeType>
inline TBool CTypedNode<TNodeType, TAttributeType>::AttributeExists(TAttributeType aAttributeType) const
	{
	return (CNode::AttributeExists(CONST_CAST(TAny*, REINTERPRET_CAST(const TAny*,aAttributeType))));
	}

template <class TNodeType, class TAttributeType>
inline TNodeType CTypedNode<TNodeType, TAttributeType>::Type() const
	{
	return (REINTERPRET_CAST(TNodeType,CNode::Type()));
	}

template <class TNodeType, class TAttributeType>
inline void CTypedNode<TNodeType, TAttributeType>::SetType(TNodeType aType)
	{
	CNode::SetType(CONST_CAST(TAny*,REINTERPRET_CAST(const TAny* ,aType)));
	}

