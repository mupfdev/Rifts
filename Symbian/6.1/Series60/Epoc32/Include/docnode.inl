// DOCNODE.INL
// Copyright (C) Symbian LTD, 2000
//
// Document node inline functions
//

//*******************************************************************
// Document Node
//*******************************************************************/

inline CDocumentNode* CDocumentNode::NewL()
	{
	CTypedNode<CNode*,const TDesC*>* aNode = CTypedNode<CNode*,const TDesC*>::NewL(NULL,NULL);
	return REINTERPRET_CAST(CDocumentNode*,aNode); 
	}

inline void CDocumentNode::SetNoDeleteDataFlagL()
	{
	SetDataNoDeleteL(); // apparently this has to be able to leave.
	}

inline void CDocumentNode::AddContentDataL(HBufC16* aContentNodePtr)
	{
	SetDataL(aContentNodePtr);
	}

inline const HBufC16* CDocumentNode::ContentData()
	{
	return Data();
	}

inline void CDocumentNode::DeleteContentData()
	{
	TRAPD(err,SetDataL(NULL)); // this will delete/not delete the data according to the state of the NODELETE flag
	//ClearSetDataNoDeleteL(); // apparently this has to be able to leave.
	}


