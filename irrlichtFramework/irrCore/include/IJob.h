/*
 * IJob.h - A thing that needs to be done :P.
 * Created November 25, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_JOB_H_INCLUDED__
#define __IRR_JOB_H_INCLUDED__

#include <irrCore.h>

namespace irr
{
namespace core
{

	enum E_JOB_STATE
	{
		EJS_PENDING = 0, // Waiting to be ran.

		EJS_RUNNING, // Currently running.

		EJS_DONE // Done.
	};

	class IJob
	{
	public:

		virtual ~IJob() {}

		virtual void doJob() = 0;

		E_JOB_STATE JobState;
	};

}
}

#endif
