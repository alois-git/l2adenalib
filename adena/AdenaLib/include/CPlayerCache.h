/*
 * CPlayerCache.h - Interface for getting player info from the SQL database.
 * Created January 9, 2006, by Michael 'Bigcheese' Spencer.
 *
 * Copyright (C) 2007 Michael Spencer
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Michael Spencer - bigcheesegs@gmail.com
 */

#ifndef _ADENA_C_PLAYER_CACHE_H_
#define _ADENA_C_PLAYER_CACHE_H_

#include <AdenaConfig.h>
#include <irrThread.h>

namespace adena
{
namespace game_server
{

	/*
	 * The player cache is used to load player data from the SQL sever and save it intermitently
	 * 
	 */
	class CPlayerCache : public irr::core::threads::Thread
	{
	public:

		CPlayerCache();

		virtual ~CPlayerCache();

		/*
		 * return: true if creation sucessfull, false if name already taken
		 */
		virtual bool createChar();

		/*
		 * @param account_id: [IN] The account id of the characters to load
		 * return: The number of chars loaded
		 * note: Accesses SQL
		 */
		virtual irr::u32 loadCharSelect(irr::u32 account_id);

		/*
		 * @param account_id: [IN] The account id of the char to load
		 * @param char_index: [IN] The index (as shown on the char select screen starting at 0) of the char to load
		 */
		virtual void loadChar(irr::u32 account_id, irr::u32 char_index);

	};

}
}

#endif
