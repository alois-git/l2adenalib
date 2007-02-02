/*
 * CSQLLite.h - SQL lite database interface.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_C_SQL_LITE_H_INCLUDED__
#define __IRR_C_SQL_LITE_H_INCLUDED__

#include <IDatabase.h>
#include <irrDbCompileConfig.h>

namespace irr
{
namespace db
{

	class IRRDB_API CSQLLiteConParms : public IDbConParms
	{
	public:
		CSQLLiteConParms();

		virtual ~CSQLLiteConParms();

		core::stringc FileName;

	private:



	};

	class IRRDB_API CSQLLite : public IDatabase
	{
	public:

		CSQLLite();

		virtual ~CSQLLite();

		virtual core::stringc& getLastError();

		/*
		 * Returns true if connected, false if failed to connect.
		 */
		virtual bool connect(IDbConParms* con_parms);

		virtual void disconnect();

		virtual CQueryResult query(Query& q);

	private:

		void* db;
		core::stringc LastError;

	};

}
}

#endif
