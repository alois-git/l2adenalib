/*
 * irrRateController.h - Controls data per second.
 * Created 12/8/2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_RATECONTROLLER_H_INCLUDED__
#define __IRR_RATECONTROLLER_H_INCLUDED__

#include <irrTypes.h>
#include <irrNetTypes.h>
#include <time.h>

namespace irr
{

	class IRRNET_API RateController
	{
	public:

		RateController();

		~RateController();

		void setUnitsPerSecond(u32 units_per_second);

		void waitForNext(u32 units_to_use);

	private:

		u32 UnitsPerSecond;
		u32 UnitsUsedThisSecond;

	};

}

#endif
