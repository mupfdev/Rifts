// C32COMM.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
 * @file c32comm.inl
 *
 * implements inline methods of RComm
 */

inline void RComm::SetSignals(TUint aSetMask, TUint aClearMask)
/**
 * Set serial port control line
 *
 * Using this inline function, either of the RS232 output lines (DTR and RTS)
 * can be set or cleared manually as needed.
 *
 * @param aSetMask   Set the handshaking lines in the mask.
 * @param aClearMask Clear the handshaking lines in the mask.
 */
	{
	SetSignalsToMark(aSetMask);
	SetSignalsToSpace(aClearMask);
	}
