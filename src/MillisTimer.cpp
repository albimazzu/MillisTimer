#include "MillisTimer.h"




/*
 void MillisTimer::begin(const ulong &timeout, const bool &micros)

 Description:
 ------------
  * Constructor for the MillisTimer Class

 Inputs:
 -------
  * const uint8_t &timeout- Timeout in ms (or us if micros flag is set)
  * const bool &micros - Set timeout units to us

 Return:
 -------
  * void
*/
void MillisTimer::begin(const ulong &timeout, const bool &micros)
{
	us = micros;
	update(timeout);
}




/*
 bool MillisTimer::update(const ulong &timeout)

 Description:
 ------------
  * Update timer's timeout, the timer can be reinitalized if desired

 Inputs:
 -------
  * const ulong &timeout - Number of ms/us to elapse the timer
  * const bool &reset - Allows user to reinitialize timer after updating timeout

 Return:
 -------
  * void
*/
void MillisTimer::update(const ulong &timeout, const bool &reset)
{
	period = timeout;
	if (reset)
		start();
}




/*
 void MillisTimer::start()

 Description:
 ------------
  * Initializes/reinitializes timer

 Inputs:
 -------
  * void

 Return:
 -------
  * void
*/
void MillisTimer::start()
{
	if(executeOne == false)
	{		
		executeOne = true;
		if (us)
			timeBench = micros();
		else
			timeBench = millis();
	}

	enabled = true;
	
}




/*
 void MillisTimer::stop() //////////////////////Added by Alberto Mazzu

 Description:
 ------------
  * Stop the timer

 Inputs:
 -------
  * void

 Return:
 -------
  * void
*/
void MillisTimer::stop()
{
	if(enabled)
		lastElapsedTime = getElapsedTime();
	enabled = false;
	executeOne = false;
	elapsed = false;
}




/*
 void MillisTimer::reset()

 Description:
 ------------
  * Resets timer

 Inputs:
 -------
  * void

 Return:
 -------
  * void
*/
void MillisTimer::reset()
{
	elapsed = false;
	timeBench += period;
}



/*
 bool MillisTimer::fire(const bool &_reset)

 Description:
 ------------
  * Determine if enough time has elapsed - handles
  millis() and micros() rollover

 Inputs:
 -------
  * const bool &_reset - Allows user to specify if
  the timer should reset if enough time has elapsed

 Return:
 -------
  * bool - Whether or not enough time has elapsed
*/
bool MillisTimer::fire(const bool &_reset)
{
	ulong currentTime;

	if (enabled)
	{
		// Update current time in user specified units
		if (us)
			currentTime = micros();
		else
			currentTime = millis();

		// Handle overflow
		if (currentTime < timeBench)
			timeDiff = (UL_MAX - timeBench) + currentTime;
		else
			timeDiff = currentTime - timeBench;

		// Determine if enough time has passed
		if (timeDiff >= period)
		{
			elapsed = true;
			lastElapsedTime = period;
			if (_reset)
				reset();
			return true;
		}
	}	

	return false;
}


/*
 ulong MillisTimer::getElapsedTime()

 Description:
 ------------
	* Returns the elapsed time since the timer started

 Inputs:
 -------
	* void

 Return:
 -------
	* ulong - Elapsed time in ms or us
*/
ulong MillisTimer::getElapsedTime()
{
	ulong currentTime;

	if(!enabled)
		return lastElapsedTime;

	if(elapsed)
		return period;

	if (us)
		currentTime = micros();
	else
		currentTime = millis();

	if (currentTime < timeBench)
		return (UL_MAX - timeBench) + currentTime;
	else
		return currentTime - timeBench;
}

