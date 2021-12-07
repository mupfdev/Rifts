// DTDNODE.H
// Copyright (C) Symbian LTD, 1999
//
// DTD node header
//

#if !defined(__CDTDNODE_H__)
#define __CDTDNODE_H__

#include <e32base.h>
#include "CBNFNode.h" 

// CDTDNode
//
class CDTDNode : public CBNFNode
{
public:
	inline ~CDTDNode();

	static inline CDTDNode* NewL();
	inline void AddCompletedAttributeL();

	const TDesC* CompletedAttrID();

	enum{ // attribute IDs start at -6000
		KCompletedAttrID = -6000
	};
private:
	inline CDTDNode();
};


#include "dtdnode.inl"

#endif // __CDTDNODE_H__
