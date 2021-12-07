// DTDNODE.INL
// Copyright (C) Symbian LTD, 1999
//
// DTD nodes inline functions
//



//*******************************************************************
// DTD Node
//*******************************************************************/

inline CDTDNode::CDTDNode() : CBNFNode(0)
	{
	}

inline CDTDNode::~CDTDNode()
	{
	}

inline CDTDNode* CDTDNode::NewL()
	{
	CTypedNode<TInt,const TDesC*>* aNode = CTypedNode<TInt,const TDesC*>::NewL( 0, 0 );
	return REINTERPRET_CAST(CDTDNode*,aNode);
	}

inline void CDTDNode::AddCompletedAttributeL()
	{
	AddAttributeL(CompletedAttrID(),NULL);
	}

