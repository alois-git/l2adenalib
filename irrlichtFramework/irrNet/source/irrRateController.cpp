/*
 * irrRateController.cpp - Controls data per second.
 * Created 12/8/2006, by Michael 'Bigcheese' Spencer.
 */

#include <irrRateController.h>
#include <irrThread.h>

namespace irr
{

RateController::RateController()
{
	UnitsUsedThisSecond = 0;
	UnitsPerSecond = 0;
};

RateController::~RateController()
{

};

void RateController::setUnitsPerSecond(u32 units_per_second)
{
	UnitsPerSecond = units_per_second;
	UnitsPerSecond /= 5;
};

// CLOCKS_PER_SEC
void RateController::waitForNext(u32 units_to_use)
{
	if(UnitsPerSecond == 0)
		return;

	if((UnitsUsedThisSecond + units_to_use) > UnitsPerSecond)
	{
		core::threads::sleep(200); // Sleep 1/5 of a second.
		UnitsUsedThisSecond = 0;
	}
	UnitsUsedThisSecond += units_to_use;
};

}

