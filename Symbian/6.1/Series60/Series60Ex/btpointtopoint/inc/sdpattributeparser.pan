/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __SDP_ATTRIBUTE_PARSER_PAN__
#define __SDP_ATTRIBUTE_PARSER_PAN__

/** BTPointToPoint application panic codes */
enum TSdpAttributeParserPanics 
    {
    ESdpAttributeParserInvalidCommand = 1,
    ESdpAttributeParserNoValue,
    ESdpAttributeParserValueIsList,
    ESdpAttributeParserValueTypeUnsupported
    };

inline void Panic(TSdpAttributeParserPanics aReason)
    { 
    User::Panic(_L("SAP"), aReason);
    }


#endif // __SDP_ATTRIBUTE_PARSER_PAN__
