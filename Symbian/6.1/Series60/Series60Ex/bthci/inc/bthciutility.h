/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __CBTHCIUTILITY_H__
#define __CBTHCIUTILITY_H__

#include <coecntrl.h>
#include <btmanclient.h>
#include <btextnotifiers.h>
#include <aknlists.h>
#include <aknglobalprogressdialog.h>
#include <bt_sock.h>

class MReporter;

/*!
  @class CBTHCIUtility

  @discussion Performs a set of sample HCI command requests.
  */

class CBTHCIUtility : public CActive
    {
public:
/*!
  @function NewL

  @discussion Create a CBTHCIUtility object
  @param aReporter Reporter used for log
  @result a pointer to the created instance of CBTHCIUtility
  */

    static CBTHCIUtility* NewL(MReporter& aReporter);

/*!
  @function NewLC

  @discussion Create a CBTHCIUtility object
  @param aReporter Reporter used for log
  @result a pointer to the created instance of CBTHCIUtility
  */

    static CBTHCIUtility* NewLC(MReporter& aReporter);

/*!
  @function ~CBTHCIUtility

  @discussion Destroy the object and release all memory objects
  */

    ~CBTHCIUtility();

/*!
  @function LocalVersionHCICommand

  @discussion Perform the Local Version HCI command request
  */
    void LocalVersionHCICommand();

/*!
  @function LocalFeaturesHCICommand

  @discussion Perform the Local Features HCI command request
  */
    void LocalFeaturesHCICommand();

/*!
  @function LocalAddressHCICommand

  @discussion Perform the Local Address HCI command request
  */
    void LocalAddressHCICommand();

protected:    // from CActive
/*!
  @function DoCancel

  @discussion Cancel any outstanding requests
  */
    void DoCancel();

/*!
  @function RunL

  @discussion Respond to an event
  */
    void RunL();

private:
/*!
  @function CBTHCIUtility

  @discussion Perform the first phase of two phase construction
  @param aReporter logs the output from this class
  */

    CBTHCIUtility(MReporter& aReporter);

/*!
  @function ConstructL

  @discussion  Perform the second phase construction of a CBTHCIUtility object
  */

    void ConstructL();

private:

    /*!
      @enum TState

      @discussion The state of the active object, determines behaviour within
      the RunL method.
      @value EIdle not expecting an asynchronous event
      @value EGettingLocalVersion expecting local version ioctl info
      @value EGettingLocalFeatures expecting local features ioctl info
      @value EGettingLocalAddress expecting local address ioctl info
      */
    enum TState
        {
        EIdle,
        EGettingLocalVersion,
        EGettingLocalFeatures,
        EGettingLocalAddress
        };

    /*! @var iState the current state of the object */
    TState iState;

    /*! @var iReporter used to log results */
    MReporter& iReporter;

    /*! @var iSocketServer handle to the socket server */
    RSocketServ iSocketServer;

    /*! @var iSock client socket handle */
    RSocket iSock;

    /*! @var iDevAddrPckg package buffer to hold device address information */
    TBTDevAddrPckg iDevAddrPckg;

    /*! @var iLocalVersionBuf package buffer to hold local version information */
    THCILocalVersionBuf iLocalVersionBuf;

    /*! @var iLocalFeaturesBuf package buffer to hold local features information */
    TPckgBuf<TUint> iLocalFeaturesBuf;

    /*! @var iInfoBuf text buffer for reporting information */
    HBufC* iInfoBuf;
    };

#endif //__CBTHCIUTILITY_H__
