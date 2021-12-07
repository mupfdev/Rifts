/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTAttributeValueLister.h"

_LIT(KIndentation, "  ");

TBTAttributeValueLister::TBTAttributeValueLister(MReporter& aReporter)
:   iReporter(aReporter), iIndentationLevel(0)
    {
    // No implementation required
    }

void TBTAttributeValueLister::VisitAttributeValueL(CSdpAttrValue& aValue, TSdpElementType aType)
    {
    TBuf<48> buf; 
    iReporter.Print(KIndentation);
    for (TInt i = 0; i < iIndentationLevel; ++i)
        {
        iReporter.Print(KIndentation);
        }
	switch(aType)
		{
		case ETypeUint:
            buf.Format(_L("UInt: 0x%x"), aValue.Uint());
            iReporter.PrintLine(buf);
            break;

		case ETypeInt:
            buf.Format(_L("Int: 0x%x"),aValue.Int());
            iReporter.PrintLine(buf);
			break;

		case ETypeBoolean:
            iReporter.Print(_L("Bool: "));
            if (aValue.Bool())
                {
                iReporter.PrintLine(_L("True"));
                }
            else
                {
                iReporter.PrintLine(_L("False"));
                }
			break;

		case ETypeUUID:
            {
            iReporter.Print(_L("UUID: "));
            const TPtrC8& uuid = aValue.UUID().ShortestForm();
            buf.Append(_L("0x"));
            // maximum length of uuid is 16 bytes (= 32 hex characters)
            for (TInt j = 0; j < uuid.Length(); ++j)
                {
                buf.AppendNumFixedWidth(uuid[j], EHex, 2);
                }
            iReporter.PrintLine(buf);
            }
			break;

		case ETypeDES:
            iReporter.PrintLine(_L("DES"));
            break;

		case ETypeString:
            iReporter.Print(_L("\""));
            Print(aValue.Des());
            iReporter.PrintLine(_L("\""));
			break;

		case ETypeDEA:
            iReporter.PrintLine(_L("DEA"));
            break;

		case ETypeURL:
            iReporter.Print(_L("URL: "));
            Print(aValue.Des());
            iReporter.PrintNewLine();
			break;

        case ETypeEncoded:
            iReporter.PrintLine(_L("Encoded Value"));
			break;

        case ETypeNil:
            iReporter.PrintLine(_L("Nil"));
			break;

        default:
            iReporter.PrintLine(_L("Not Recognised"));
			break;
		}
    }

void TBTAttributeValueLister::Print(const TDesC8& aStr)
    {
    const TInt bufSize = 32;
    TBuf<bufSize> buf;
    TInt len = aStr.Length();
    for (int i = 0; i < len; i += bufSize)
        {
        buf.Copy(aStr.Mid(i, (len - i > bufSize) ? bufSize : (len - i)));
        iReporter.Print(buf);
        }
    }

void TBTAttributeValueLister::StartListL(CSdpAttrValueList& /*aList*/)
    {
    ++iIndentationLevel;
    }

void TBTAttributeValueLister::EndListL()
    {
    --iIndentationLevel;
    }


