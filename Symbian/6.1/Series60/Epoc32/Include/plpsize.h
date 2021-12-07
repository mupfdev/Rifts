/*
	PLPSIZE.H
	---------
	PLP packet sizes, can also be used by PRC.

	Rob Garrett.
*/

#if !defined(__PLPSIZE_H__)
#define __PLPSIZE_H__

#ifdef _UNICODE

#define MAX_DATACHUNK_SIZE	16384
/*
	Custom servers, RPC and some file operations have to limit the amount
	of data sent in one go, PRC does the same. 
*/

#define PLP_LINK_PDU_SIZE	2400
/*
	Maximum PDU size for PLP link protocol.
*/

#else

#define MAX_DATACHUNK_SIZE	2048
/*
	Custom servers, RPC and some file operations have to limit the amount
	of data sent in one go, PRC does the same. 
*/

#define PLP_LINK_PDU_SIZE	300
/*
	Maximum PDU size for PLP link protocol.
*/

#endif
#endif	// __PLPSIZE_H__