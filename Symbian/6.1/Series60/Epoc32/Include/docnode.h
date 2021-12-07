// DOCNODE.H
// Copyright (C) Symbian LTD, 2000
//
// Tree nodes header
//


#ifndef __CDOCNODE_H__
#define __CDOCNODE_H__

#include <e32base.h>
#include <cnode.h>

// CDocumentNode
//
class CDocumentNode : public CTypedNode<CNode*,const TDesC*> 
{
public:
	inline ~CDocumentNode();
	static inline CDocumentNode* NewL();

	inline void AddContentDataL(HBufC16*); // HBufC16 to match tree conventions
	inline const HBufC16* ContentData();
	inline void DeleteContentData();

	inline void SetNoDeleteDataFlagL();

private:
	inline CDocumentNode();
};

#include "docnode.inl"

#endif // __CDOCNODE_H__