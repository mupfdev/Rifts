// FAXSTD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#if !defined(__FaxStd_H__)
#define __FaxStd_H__

// we start off with data constants

// error codes

const TInt KFaxErrModemNotWorking (-101);
const TInt KFaxErrCannotConnect (-102);
const TInt KFaxErrCSIorCIG (-103);
const TInt KFaxErrDISorDTC (-104);
const TInt KFaxErrFrameFail (-105);
const TInt KFaxErrAtNegotiatedSpeed (-106);
const TInt KFaxErrCFR (-107);
const TInt KFaxErrMCF (-108);
const TInt KFaxErrCRP (-109);
const TInt KFaxErrNoDial (-110);
const TInt KFaxErrNoDialTone (-111);
const TInt KFaxErrBusy (-112);
const TInt KFaxErrNoAnswer (-113);
const TInt KFaxErrNoCarrier (-114);
const TInt KFaxErrRemoteCannotReceive (-115);
const TInt KFaxErrCompression (-116);
const TInt KFaxErrPageTooLong (-117);
const TInt KFaxErrDCN (-118);
const TInt KFaxErrRemoteDCN (-119);
const TInt KFaxErrHDLC (-120);
const TInt KFaxErrStopAndWait (-121);
const TInt KFaxErrTrainStop (-122);
const TInt KFaxErrReceiveTimeout (-123);
const TInt KFaxErrCannotEndData (-124);
const TInt KFaxErrEOP (-125);
const TInt KFaxErrMPS (-126);
const TInt KFaxErrNoReceiveMode (-127);
const TInt KFaxErrCannotAnswer (-128);
const TInt KFaxErrPrematureHangup (-129);
const TInt KFaxErrModemResponse (-130);
const TInt KFaxErrPrematureOK (-131);
const TInt KFaxErrNoFinalOK (-132);
const TInt KFaxErrUnknownPageCode (-133);
const TInt KFaxErrNoHangup (-134);
const TInt KFaxErrNoNegotiate (-135);
const TInt KFaxErrModemDisconnect (-136);
const TInt KFaxErrWrongModemType (-137);
const TInt KFaxErrTrainFail (-138);
const TInt KFaxTransmitterStalled (-139);
const TInt KFaxReceiverOverflow (-140);
const TInt KFaxCannotOpenPort (-141);
const TInt KFaxCannotCloseStore (-142);
const TInt KFaxCannotOpenStore (-143);
const TInt KFaxThreadError (-144);
const TInt KFaxFileSessionError (-145);
const TInt KFaxLogCreateError (-146);  // was KFaxFileCreateError till 7/10/97
const TInt KFaxFileSeekError (-147);
const TInt KFaxPDDError (-148);
const TInt KFaxLDDError (-149);
const TInt KFaxC32Error (-150);
const TInt KFaxCommsServerError (-151);
const TInt KFaxCommsPortError (-152);
const TInt KFaxCancelRequested (-153);
const TInt KFaxNoClass2Xon (-154);
const TInt KFaxConfigError (-155);
const TInt KFaxCannotAutodetect (-156);
const TInt KCannotFindFirstPage (-157);
const TInt KFaxBadInitialization (-158);
const TInt KFaxOnlyJustAutoDetected (-159);
const TInt KFaxBelowMinSpeed (-160);
const TInt KFaxPollingUnsupported (-161);
const TInt KFaxNothingToPoll (-162);
const TInt KFaxEtelServerError (-163);
					

// standard communication bytes

const TUint8 Knul (0x00);
const TUint8 Kdle (0x10);
const TUint8 Ketx (0x03);
const TUint8 Kbackspace (0x08);
const TUint8 Kreturn (0x0d);
const TUint8 Klinefeed (0x0a);
const TUint8 Kxon (0x11);
const TUint8 Kxoff (0x13);
const TUint8 Kdc2 (0x12);
const TUint8 Kcan (0x18);

// apparent clock granularity

const TInt CLK_TCK (1000000);

// maximum size of a descriptor for reading and writing T4 scan lines

// the longest possible encoded scan line is alternating black and white dots
// that's 8 bits, as single white dot = 00111 single black dot = 010
// there's a maximum of 864 such pairs in a 1728 dot scan line
// let's be generous and allow for eols and padding - 896
// this is sufficient for faxes we generate ourselves

// On the other hand, a scan line can take up to 5 seconds to transmit
// At 14400 bps, it could contain 72000 bits = 9000 bytes
// There could be internal line padding (alternate run lengths of zero)
// So this bigger figure is needed for faxes which we receive via the line

// we also use this when sending phase C data to the modem
// we also use this when receiving phase C data from the modem

const TInt KMaxT4Des (896);
const TInt KMaxFaxBuf ((KMaxT4Des + sizeof (TInt)) * 2);

// base for sizing buffers

const TInt KBufSize (512);

// A version must be specifyed when creating a session with the server

const TUint KEtelFaxMajorVersionNumber = 1;
const TUint KEtelFaxMinorVersionNumber = 0;
const TUint KEtelFaxVersionNumber = 601;

IMPORT_C TInt StartThread ();


/********************************************************************/

// fax structures
/********************************************************************/ 

// The next enumerations is bitmapped giving useful TFaxMode masks

const TUint KFaxReceive (0x01);
const TUint KFaxOffHook (0x02);
const TUint KFaxWaitForRing (0x04);
const TUint KFaxNoDial (0x06);
const TUint KFaxPoll (0x08);

enum TFaxMode
   {
   EDialAndTransmit=0,				// this is a normal fax machine type send
   EDialAndReceiveFaxBack=1,  		// this dials a fax on demand service
   EImmediateTransmit=2,	  		// for switching from voice to send
   EImmediateReceive=3,				// for switching from voice to receive
   EWaitForRingAndTransmit=4, 		// this make us into a fax on demand 
   EWaitForRingAndReceive=5,		// this is a normal fax machine type receive
   EDialAndReceivePoll=9			// this is for fax polling
   };

#endif

