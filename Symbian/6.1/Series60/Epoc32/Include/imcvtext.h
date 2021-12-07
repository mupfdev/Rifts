// IMCVTEXT.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

// string constants for IMCV
// These are needed to prevent the 'Initialised data' problem in ARM builds

#if !defined (__IMCVTEXT_H__)
#define __IMCVTEXT_H__

// The strings in this file MUST NOT BE translated....

const TInt KMaxPriorityTextLength = 18;	// "*special-delivery*" = 18 chars
const TInt KImcvDateStringLength = 32;

//priorities
const TInt KPriorityHigh	=1;
const TInt KPriorityNormal	=3; 
const TInt KPriorityLow		=5;

//Includes length of charset name ISO_8859-1
const TInt KMinimumEncodedChars = 15;

const TInt KMaxExtentionLength = 5;

//----------------------------------------------------------------------------------------
// General tokens
_LIT8(KImcvEpoc32, "EPOC32");
_LIT(KImcvIMCV, "IMCV");
_LIT8(KImcvSpace, " ");
_LIT8(KImcvCommaSpace, ", ");
_LIT8(KImcvForwardSlash, "/");
_LIT8(KImcvCRLF, "\r\n");
_LIT16(KImcvCRLF16, "\r\n");
_LIT8(KImcvStuffedDot, "\r\n.");
_LIT(KImcvDateFormat, " %S, %2d %S %04d %02d:%02d:%02d ");
_LIT(KImcvMonthNames, "JanFebMarAprMayJunJulAugSepOctNovDec");
_LIT(KImcvDayNames, "MonTueWedThuFriSatSun");
_LIT8(KImcvUnknown, "unknown");
_LIT(KImcvTimeZoneNeg, "-%02d%02d");
_LIT(KImcvTimeZonePos, "+%02d%02d");
//----------------------------------------------------------------------------------------
// Message header tokens
_LIT8(KImcvFromPrompt, "From:");
_LIT8(KImcvReplyToPrompt, "Reply-to:");
_LIT8(KImcvToPrompt, "To:");
_LIT8(KImcvCcPrompt, "Cc:");
_LIT8(KImcvBccPrompt, "Bcc:");
_LIT8(KImcvSubjectPrompt, "Subject:");
_LIT8(KImcvDatePrompt, "Date:");
_LIT8(KImcvMessageIdPrompt, "Message-ID:");
_LIT8(KImcvXMailer, "X-Mailer:");

_LIT8(KImcvPriorityPrompt, "Priority:");
_LIT8(KImcvXPriorityPrompt, "X-Priority:");
_LIT8(KImcvPrecedencePrompt, "Precedence:");
_LIT8(KImcvImportancePrompt, "Importance:");

_LIT8(KPrecedenceSpecialDelivery, "*special-delivery*");
_LIT8(KPrecedenceFirstClass, "*first-class*");
_LIT8(KPrecedenceList, "*list*");
_LIT8(KPrecedenceBulk, "*bulk*");
_LIT8(KPrecedenceJunk, "*junk*");

_LIT8(KImportanceLow, "*low*");
_LIT8(KImportanceLowest, "*Lowest*");
_LIT8(KImportanceNormal, "*normal*");
_LIT8(KImportanceHigh, "*high*");
_LIT8(KImportanceHighest, "*Highest*");

_LIT8(KImPriorityUrgent, "*urgent*");
_LIT8(KImPriorityNormal, "*normal*");
_LIT8(KImPriorityNonUrgent, "*non-urgent*");
_LIT8(KImPrioritySendHigh, "high");
_LIT8(KImPrioritySendLow, "low");
_LIT8(KImPrioritySendNormal, "normal");


_LIT8(KImcvReturnReceiptToPrompt, "Return-Receipt-To:");
_LIT8(KImcvReturnXReceiptToPrompt, "X-Return-Receipt-To:");
_LIT8(KImcvMsgDispositionTo, "Disposition-Notification-To:");
_LIT8(KImcvMsgDispositionOptions, "Disposition-Notification-Options:");

//----------------------------------------------------------------------------------------
// MIME header tokens
_LIT8(KImcvSpMimeVersion, " 1.0");
_LIT8(KImcvMimeVersion, "1.0");
_LIT8(KImcvTextPlain, " text/plain");
_LIT8(KImcvMultipartMixed, " multipart/mixed");
_LIT8(KImcvTextDirectory, " text/directory");
_LIT8(KImcvQuotedPrintable, " quoted-printable");
_LIT8(KImcvApplOctet, " application/octet-stream");
_LIT8(KImcvExe, "exe");
_LIT8(KImcvCmd, "cmd");
_LIT8(KImcv7Bit, " 7-bit");
_LIT8(KImcvBase64, " base64");
_LIT8(KImcvMime, "MIME*");
_LIT8(KImcvContent, "Content*");
_LIT8(KImcvMimeBoundaryStartEnd, "--");

_LIT8(KImcvMimePrompt, "MIME-Version:");
_LIT8(KImcvContentType, "Content-Type:");
_LIT8(KImcvContentTransferEncoding, "Content-Transfer-Encoding:");
_LIT8(KImcvContentDisposition, "Content-Disposition:");
_LIT8(KImcvContentDescription, "Content-Description:");
_LIT8(KImcvContentLocation, "Content-Location:");
_LIT8(KImcvContentId, "Content-Id:");
_LIT8(KImcvContentBase, "Content-Base:");
_LIT8(KImcvContentLanguage, "Content-Language:");
_LIT8(KImcvDefaultLanguage, " i-default");

// MIME Parameter names 
_LIT8(KImcvMimeDispositionFilename, "filename");
_LIT8(KImcvMimeTypeName, "name");
_LIT8(KImcvBoundary, "boundary");
_LIT8(KImcvCharset, "charset");
_LIT8(KImcvStartPart, "start");
// Content-Disposition: types
_LIT8(KImcvInline, "inline");
_LIT8(KImcvAttachment, "attachment");
// Content-Type: types
_LIT8(KImcvMultipart, "multipart");
_LIT8(KImcvText, "text");
_LIT8(KImcvImage, "image");
_LIT8(KImcvAudio, "audio");
_LIT8(KImcvVideo, "video");
_LIT8(KImcvApplication, "application");
_LIT8(KImcvOctetStream, "octet-stream");
_LIT8(KImcvMessage, "message");
// Content-Type: Multipart types
_LIT8(KImcvMixed, "mixed");
_LIT8(KImcvRelated, "related");
_LIT8(KImcvAlternative, "alternative");
_LIT8(KImcvEncrypted, "encrypted");
_LIT8(KImcvParallel, "parallel");
_LIT8(KImcvDigest, "digest");
_LIT8(KImcvSigned, "signed");
// Content-Type: Text types
_LIT8(KImcvHtml, "html");
_LIT8(KImcvPlain, "plain");
_LIT8(KImcvDirectory, "directory");
// Content-Type: Message types
_LIT8(KImcvPartial, "partial");
_LIT8(KImcvExternal, "external-body");
_LIT8(KImcvRfc822, "rfc822");
// Content-Type: Directory types
_LIT8(KImcvProfile, "profile");
_LIT8(KImcvVCard, "vcard");
_LIT8(KImcvVCalender, "calendar");
// Content-Type: Image, Audio, Video, Application types
_LIT8(KImcvBmp, "bmp");
_LIT8(KImcvGif, "gif");
_LIT8(KImcvJpeg, "jpeg");
_LIT8(KImcvTiff, "tiff");
_LIT8(KImcvWav, "wav");
_LIT8(KImcvZip, "x-gzip");
//----------------------------------------------------------------------------------------
// UU Encoding tokens
_LIT8(KImcvUueStart, "begin ");
_LIT8(KImcvUue644, "644");
_LIT8(KImcvUueEnd, "end\r\n");
_LIT8(KImcvUueLastLine, "`\r\n");

_LIT8(KImcvXUUString, "X-UUENCODE");
//----------------------------------------------------------------------------------------
// QP Encoding tokens
_LIT8(KImcvPlainRichText, " ");
_LIT8(KImcvEndOfLine, "=\r\n");
_LIT8(KImcvQPFormatString, "=%02X\r\n");
_LIT8(KImcvQPEqualsSign, "=3D");
_LIT8(KImcvQPEncoded, "=%02X");
_LIT8(KImcvParagraph, "\006");
_LIT8(KImcvCharacterFormat, "%c");

_LIT8(KImcvEncodeCharacterList, "?");
_LIT8(KImcvEncodedWordStart, "=?");
_LIT8(KImcvEncodedWordEnd, "?=");
_LIT8(KImcvQuestionMarkString, "?");
_LIT8(KImcvB, "B");
_LIT8(KImcvQ, "Q");

_LIT8(KWildChars, "**");
_LIT8(KBasicAsciiChars,"'+,-_bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ0123456789");
_LIT8(KValidCharacters, "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ0123456789");

_LIT8(KPrintChar, "%c");
_LIT8(KPrintString, "%S");

// Filename Extentions
_LIT(KTextExtention, ".txt");
_LIT(KHtmlExtention, ".html");
_LIT(KVCardExtention, ".vcs");

// Used in CImSendMimeHeaderBase::AppendFilenameL
_LIT8(KImcvEqualsQuote, "=\"");
_LIT8(KImcvQuoteString, "\"");

_LIT(KImcvMimeText, "This is a MIME Message");


// UIDS
const TUint8 KImcvSpaceChar		= ' ';
const TUint8 KImcvCR			= '\r';
const TUint8 KImcvLF			= '\n';
const TUint8 KImcvSP			= ' ';
const TUint8 KImcvTab			= '\t';
const TUint8 KImcvAny			= '*';
const TUint8 KImcvEquals		= '=';
const TUint8 KImcvHyphen		= '-';
const TUint8 KImcvUnderScore	= '_';
const TUint8 KImcvLeftBracket	= '(';
const TUint8 KImcvRightBracket	= ')';
const TUint8 KImcvLeftChevron	= '<';
const TUint8 KImcvRightChevron	= '>';
const TUint8 KImcvDoubleQuote	= '\"';
const TUint8 KImcvDefaultChar	= '_';	// inserted into filename in place of illegal EPOC32 filename char
const TUint8 KImcvComma			= ',';
const TUint8 KImcvSemiColon		= ';';
const TUint8 KImcvColon			= ':';
const TUint8 KImcvPlus			= '+';
const TUint8 KImcvBackSlash		= '\\';
const TUint8 KImcvQuote			= '"';
const TUint8 KImcvSingleQuote	= '\'';
const TUint8 KImcvInvertedComma = '`';
const TUint8 KImcvTilde			= '~';
const TUint8 KImcvQuestionMark	= '?';
const TUint8 KImcvAt			='@';
const TUint8 KImcvFullStop		='.';
const TUint8 KImcvPercentSign	= '%';
const TUint8 KImcvExclamation	= '!';
const TUint8 KImcvESC			= 0x1B;

// Special characters previously defined in EText
	enum {
		ETextParagraphDelimiter=0x10,
		};


#endif
