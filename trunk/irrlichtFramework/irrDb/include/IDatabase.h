/*
 * IDatabase.h - data base interface.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_I_DATA_BASE_H_INCLUDED__
#define __IRR_I_DATA_BASE_H_INCLUDED__

#include <irrString.h>
#include <IDbConParms.h>
#include <irrQuery.h>
#include <CQueryResult.h>

namespace irr
{
namespace db
{

	class IDatabase
	{
	public:

		virtual ~IDatabase() {}

		virtual core::stringc& getLastError() = 0;

		/*
		 * Returns true if connected, false if failed to connect.
		 */
		virtual bool connect(IDbConParms* con_parms) = 0;

		virtual void disconnect() = 0;

		virtual CQueryResult query(Query& q) = 0;

	private:
	};

}
}

#endif
