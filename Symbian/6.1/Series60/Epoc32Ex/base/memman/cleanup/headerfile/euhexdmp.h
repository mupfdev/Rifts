// EUHEXDMP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

_LIT(KTxtTwoSpaces,"  ");
_LIT(KTxtThreeSpaces,"   ");
_LIT(KTxtTwoSpaceStar,"   * ");
_LIT(KTxtOneSpaceStar," *");
_LIT(KFormat1,"%S\n");

inline void hexDump(const TDesC8& aBuffer,TInt32& aAddress,TInt32& aOffset,TDes& aOutput)
	{
	TBuf<35> hexView;
	TBuf<16> charView;
	TBuf<8> hexAddress;
	TBuf<2> hexChar;

	// calculate number of leading spaces due to 16-bit boundaries
	TInt numLeadingSpaces = aAddress % 16;

	for (TInt count=0; count<16; count++)
		{
			// print space between quartets of hex values
			if (count==4 || count==8 || count==12) hexView.Append(' ');

			// display the character/hex-val or a space depending on 16-bit boundary
			if (count < (numLeadingSpaces))	
				{
				hexView.AppendFormat(KTxtTwoSpaces);
				charView.Append(' ');
				}
			else
				{
				TInt curChar = (count - numLeadingSpaces) + aOffset;
						// calculate which element of the descriptor to display
				if (curChar < aBuffer.Size())		// check to see if end of buffer has been exceeded
					{
					// Ensure hex-format of number is 2 chars long
					hexChar.Zero();
					hexChar.AppendNumUC(aBuffer[curChar],EHex);
					if (hexChar.Length() < 2) hexView.Append('0');
					hexView.Append(hexChar);

					if (aBuffer[curChar] > 31 && aBuffer[curChar] != 127) charView.Append(aBuffer[curChar]);
					else charView.Append('.');
					}
				else
					{
					hexView.AppendFormat(KTxtTwoSpaces);
					charView.Append(' ');
					}
				}
		}

	// Set the length of aOutput to zero (ie. reset the output buffer)
	aOutput.Zero();

	// calculate the 16-bit block address to display
	TInt32 prtAddress = aAddress - numLeadingSpaces;
	hexAddress.AppendNumUC(prtAddress,EHex);
	for (TInt preZeroCount=0; preZeroCount < (8-hexAddress.Length()); preZeroCount++)
		aOutput.Append('0');
	aOutput.Append(hexAddress);
	aOutput.AppendFormat(KTxtThreeSpaces);
	
	// display hex-values and characters
	aOutput.Append(hexView);
	aOutput.AppendFormat(KTxtTwoSpaceStar);
	aOutput.Append(charView);
	aOutput.AppendFormat(KTxtOneSpaceStar);

	// update the address and offset for the descriptor
	aAddress += 16 - numLeadingSpaces;
	aOffset += 16 - numLeadingSpaces;
	}
	
void printBuffer(TInt32 aAddress,const TDesC8& aBuffer)
	{
	TInt32 offset = 0;
	TBuf<80> outputLine;
	while (offset < aBuffer.Size())
		{
		hexDump(aBuffer,aAddress,offset,outputLine);
		console->Printf(KFormat1, &outputLine);
		}
	}
