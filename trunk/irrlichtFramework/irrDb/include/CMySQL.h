/*
 * CMySQL.h - MySQL database interface.
 * Created February 1, 2007, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_C_MY_SQL_H_INCLUDED__
#define __IRR_C_MY_SQL_H_INCLUDED__

#include <IDatabase.h>
#include <irrDbCompileConfig.h>

namespace irr
{
namespace db
{

	class IRRDB_API CMySQLConParms : public IDbConParms
	{
	public:

		CMySQLConParms();

		virtual ~CMySQLConParms();

		irr::core::stringc Ip;
		irr::u16 Port;
		irr::core::stringc Username;
		irr::core::stringc Password;
		irr::core::stringc Db;

	};

	class IRRDB_API CMySQL : public IDatabase
	{
	public:

		CMySQL();

		virtual ~CMySQL();

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
