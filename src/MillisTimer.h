#pragma once
#include "Arduino.h"




typedef unsigned long ulong;

const ulong UL_MAX = 4294967295;
const bool MILLI_SECONDS = false;
const bool MICRO_SECONDS = true;




class MillisTimer 
{
public:
	bool us = false;
	ulong timeDiff = 0;




	void begin(const ulong &timeout, const bool &micros=false);
	void update(const ulong &timeout, const bool &reset=false);
	void start();
	void stop();
	void reset();
	bool fire(const bool &_reset=true);


private:
	ulong timeBench = 0;
	ulong period    = 0;
	bool enabled    = false;
	bool executeOne = false;
};
