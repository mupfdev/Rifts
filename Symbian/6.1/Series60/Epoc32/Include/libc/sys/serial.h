#ifndef _SYS_SERIAL_H_
#define _SYS_SERIAL_H_

#if defined (__WINS__)
#define COMMS_PDD_NAME _L("ECDRV")
#define COMMS_LDD_NAME _L("ECOMM")
#endif

#ifdef __cplusplus
extern "C" {
#endif

//notifications
#define	KNotifyBreakInt				0x01
#define	KNotifyCD					0x02
#define	KNotifyCTS					0x04
#define	KNotifyDataAvailable		0x08
#define	KNotifyDSR					0x10
#define	KNotifyFramingError			0x20
#define	KNotifyOutputEmpty			0x40
#define	KNotifyOverrunError			0x80
#define	KNotifyParityError			0x100
#define	KNotifyRI					0x200


//enums, #defines and struct for serial port settings
enum DataBits {DBits5,DBits6,DBits7,DBits8};

enum StopBits {Stop1,Stop2};

enum Parity {ParityNone,ParityEven,ParityOdd,ParityMark,ParitySpace};

enum Bps
	{
	Bps50,Bps75,Bps110,Bps134,Bps150,Bps300,Bps600,Bps1200,
	Bps1800,Bps2000,Bps2400,Bps3600,Bps4800,Bps7200,Bps9600,
	Bps19200,Bps38400,Bps57600,Bps115200,Bps230400,Bps460800,
	Bps576000,Bps1152000,Bps4000000,
	BpsSpecial=0x80000000
	};

enum Fifo {FifoEnable,FifoDisable};

enum Sir {SIREnable,SIRDisable};
//

#define ConfigMaxTerminators 4
//
#define ConfigObeyXoff 0x01
#define ConfigSendXoff 0x02
#define ConfigObeyCTS 0x04
#define ConfigFailCTS 0x08
#define ConfigObeyDSR 0x10
#define ConfigFailDSR 0x20
#define ConfigObeyDCD 0x40
#define ConfigFailDCD 0x80
#define ConfigFreeRTS 0x100
#define ConfigFreeDTR 0x200
#define ConfigWriteBufferedComplete 0x80000000
//
#define ConfigParityErrorFail 0
#define ConfigParityErrorIgnore 0x01
#define ConfigParityErrorReplaceChar 0x02
#define ConfigXonXoffDebug 0x80000000
//
#define SignalCTS 0x01
#define SignalDSR 0x02
#define SignalDCD 0x04
#define SignalRNG 0x08
#define SignalRTS 0x10
#define SignalDTR 0x20

#define ConfigSIRPulseWidthMaximum 0x01
#define ConfigSIRPulseWidthMinimum 0x02
//


typedef struct
	{
	enum Bps iRate;
	enum DataBits iDataBits;
	enum StopBits iStopBits;
	enum Parity iParity;
	unsigned int iHandshake;
	unsigned int iParityError;
	unsigned int iFifo;
	int iSpecialRate;
	int iTerminatorCount;
	char iTerminator[ConfigMaxTerminators];
	char iXonChar;
	char iXoffChar;
	char iParityErrorChar;
	enum Sir iSIREnable;
	unsigned int iSIRSettings;
	} SerialConfig;

#ifdef __cplusplus
}
#endif

#endif
