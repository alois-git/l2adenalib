/*
 * CMySQL.cpp - MySQL database interface.
	* Created February 1, 2007, by Michael 'Bigcheese' Spencer.
 */

#include <CMySQL.h>

#ifdef _IRR_WINDOWS_
#include <winsock2.h>
#endif
#include <mysql/include/mysql.h>

namespace irr
{
namespace db
{

CMySQLConParms::CMySQLConParms()
{

};

CMySQLConParms::~CMySQLConParms()
{

};

CMySQL::CMySQL()
{
	db = malloc(sizeof(MYSQL));
	mysql_init((MYSQL*)db);
};

CMySQL::~CMySQL()
{
	free(db);
};

core::stringc& CMySQL::getLastError()
{
	return LastError;
};

bool CMySQL::connect(IDbConParms* con_parms)
{
	CMySQLConParms* cp = (CMySQLConParms*)con_parms;
	if(mysql_real_connect((MYSQL*)db, cp->Ip.c_str(), cp->Username.c_str(), cp->Password.c_str(), cp->Db.c_str(), cp->Port, 0, 0))
	{
		return true;
	}

	LastError = mysql_error((MYSQL*)db);
	return false;
};

void CMySQL::disconnect()
{
	mysql_close((MYSQL*)db);
};

CQueryResult CMySQL::query(Query& q)
{
	MYSQL_RES *res; /* To be used to fetch information into */
	MYSQL_ROW row;
	MYSQL_FIELD *fields;

	CQueryResult qr = CQueryResult();
	qr.RowCount = 0;

	irr::s32 ret = mysql_real_query((MYSQL*)db, q.QueryStr.c_str(), q.QueryStr.size());
	irr::s32 num_rows = mysql_affected_rows((MYSQL*)db);
	res = mysql_store_result((MYSQL*)db);
	if(res)
	{
		irr::s32 num_fields = mysql_num_fields(res);
		fields = mysql_fetch_fields(res);
		while ((row = mysql_fetch_row(res)))
		{
			CQueryResultRow r = CQueryResultRow();
			for(irr::u32 i = 0; i < num_fields; i++)
			{
				r.Data.Insert(fields[i].name, row[i]);
			}
			qr.RowCount++;
			qr.Rows.push_back(r);
		}
		mysql_free_result(res);
	}

	return qr;
};

}
}
