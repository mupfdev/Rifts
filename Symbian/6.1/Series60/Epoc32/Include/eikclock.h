/*
* ============================================================================
*  Name     : eikclock.h
*  Part of  : EikCtl
*
*  Description:
*     Clock control I/F of application side
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef CEIKCLOCK_H
#define CEIKCLOCK_H


// INCLUDES
#include <coecntrl.h>
#include <e32std.h>

// DATA TYPES
enum TEikClockFormat
    {
    EEikClockAnalog,
    EEikClockDigital,
    EEikClockAmPm
    };

//  FORWARD DECLARATION
class CEikLocaleConformantClock;

// CLASS DECLARATION

/**
* Clock control I/F of application side.
*/
class MEikClockContainer
    {
    public: // New functions

        /**
        * Gets a state whether the clock control is visible or not.
        * @param aClock a objective CEikLocaleConformantClock.
        * @return a answer of whether the clock control is visible or not.
        */
        virtual TBool ClockIsVisible(
            const CEikLocaleConformantClock& aClock) const=0;

        /**
        * Gets a position and size of the clock control.
        * @param aPosition returned a position with this.
        * @param aSize returned a size with this.
        * @param aClock a objective CEikLocaleConformantClock.
        * @param aMinimumSize 
        *       a size handed to a objective CEikLocaleConformantClock.
        */
        virtual void GetClockPositionAndSize(TPoint& aPosition, TSize& aSize,
         const CEikLocaleConformantClock& aClock, const TSize& aMinimumSize)=0;

    };

/**
*  Clock control of Clock application.
*  
*/
class CEikClock : public CCoeControl, public MEikClockContainer
    {
    public: // Constructors and destructor
        
        /**
        * Symbian OS default constructor.
        */
        IMPORT_C CEikClock();
        
        /*
        * Constructor.
        * @param aHomeTime ETrue means this clock shows the home time.
        *                  EFalse menas this clock shows the time
        *                   being independent of home time.
        */
        IMPORT_C CEikClock(TBool aHomeTime);

        /**
        * Destructor.
        */
        IMPORT_C ~CEikClock();
        
    public: // New functions

        /**
        * Construct clock from resource.
        * @param aResoureceReader
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);

    public: // Functions from base classes
        
        /**
        * From CoeControl Activate the clock
        */
        IMPORT_C void ActivateL();
        
        /**
        * From CoeControl Calculate the minimum size for the control.
        */
        IMPORT_C TSize MinimumSize();
        
        /**
        * From CoeControl Make the clock (in)visible.
        */
        IMPORT_C void MakeVisible(TBool aVisible);
                    
        /**
        * From MEikClockContainer Determine whether the clock is visible.
        */
        TBool ClockIsVisible(
                    const CEikLocaleConformantClock& aClock) const;
        
        /**
        * From MEikClockContainer Return the clock position.
        */
        void GetClockPositionAndSize(TPoint& aPosition,
                        TSize& aSize, const CEikLocaleConformantClock& aClock,
                                            const TSize& aMinimumSize);

    public: // New functions

        /**
        * Ges the clock format.
        * @return Clock format ( EEikClockAnagolg,
        *                   EEikClockDigital, EEikClockAmPm )
        */
        IMPORT_C TEikClockFormat Format() const;
        
        /**
        * Change the clock format if necessary.
        * Only can do between Analog and Digital.
        * @param aFormat
        */
        IMPORT_C void SetFormatL(TEikClockFormat aFormat);
        
        /**
        * Set the clocks time
        * @param aUniversalTimeOffset
        */
        IMPORT_C void SetTimeOffset(TTimeIntervalSeconds aUniversalTimeOffset);

        /*
        * Get a minimum size of individual clock
        * @param aIndicidual ETrue means to get individual size
        *                    EFalse menas to do same as MinimumSize().
        */
        IMPORT_C TSize MinimumSize(TBool aIndividual);

    protected:  // Functions from base classes

        /**
        * From CoeControl Set the clocks position.
        */
        void PositionChanged();
        
        /**
        * From CoeControl Adjust the control for a diffirent size.
        */
        void SizeChanged();
        
    private:    // New functions
    
        /**
        * Callback every interval time.
        * @param aThis This class.
        * @return TInt Error code.
        */
        static TInt TimerCallback(TAny* aThis);
        
    private: // Functions from base classes
        
        /**
        * From CoeControl Draw the clock without drawing any background.
        */
        void Draw(const TRect& aRect) const;

   private:    // Data
        TBool                       iHomeTime;
        CEikLocaleConformantClock*  iClock;
        CPeriodic*                  iTimer; 
		TInt iSpare;				// Reserved for future use
    };

#endif // CEIKCLOCK_H
// End of file
