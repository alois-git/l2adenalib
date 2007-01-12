/*
 * CQueryResult.h - Query result.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_C_QUERY_RESULT_H_INCLUDED__
#define __IRR_C_QUERY_RESULT_H_INCLUDED__

#include <irrString.h>
#include <irrArray.h>
#include <AVL.h>
#include <irrDbCompileConfig.h>

namespace irr
{
namespace db
{

	class IRRDB_API CQueryResultRow
	{
	public:

		CQueryResultRow();

		~CQueryResultRow();

		u32 getColumns();

		core::stringc operator [](core::stringc str);

		AVL<core::stringc, core::stringc> Data;

		u32 ColumnCount;

	};

	class IRRDB_API CQueryResult
	{
	public:

		CQueryResult();

		~CQueryResult();

		u32 getRows();

		CQueryResultRow operator [](u32 idx);

		core::array<CQueryResultRow> Rows;

		u32 RowCount;

	};

}
}

#endif
