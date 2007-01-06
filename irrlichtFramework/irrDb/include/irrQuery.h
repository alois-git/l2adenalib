/*
 * irrQuery.h - A safe data base query.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_QUERY_H_INCLUDED__
#define __IRR_QUERY_H_INCLUDED__

#include <irrString.h>
#include <irrDbCompileConfig.h>

namespace irr
{
namespace db
{

	class IRRDB_API Query
	{
	public:

		/*
		 * @Param str: example - "SELECT * FROM users WHERE username = '$username';"
		 * you can then call setVar("$username", real_user_name); to fill it.
		 */
		Query(core::stringc& str);

		~Query();

		/*
		 * @param var_str: the $var to replace in the query.
		 * @param val_str: what to replace it with.
		 * This function escapes sql syntax as to prevent SQL injection.
		 */
		void setVar(core::stringc& var_str, core::stringc& val_str);

		core::stringc QueryStr;

	private:

	};

}
}

#endif
