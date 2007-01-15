/*
 * CPlayerCache.h - Interface for getting player info from the SQL database.
 * Created January 9, 2006, by Michael 'Bigcheese' Spencer.
 *
 * Copyright (C) 2007 Michael Spencer
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Michael Spencer - bigcheesegs@gmail.com
 */

#ifndef _ADENA_C_PLAYER_CACHE_H_
#define _ADENA_C_PLAYER_CACHE_H_

#include <AdenaConfig.h>
#include <irrThread.h>
#include <SCharInfo.h>
#include <irrDb.h>
#include <AVL.h>

namespace adena
{
namespace game_server
{

	struct SCharSelectIds
	{
		irr::u32 Chars;
		irr::u32 CharIds[7];
	};

	/*
	 * The player cache is used to load player data from the SQL sever and save it intermitently
	 * 
	 */
	class CPlayerCache // : public irr::core::threads::Thread
	{
	public:

		CPlayerCache(void* interfaces);

		virtual ~CPlayerCache();

		/*
		 * return: true if creation sucessfull, false if name already taken
		 */
		virtual bool createChar(SCharInfo &char_info);

		/*
		 * @param account_id: [IN] The account id of the characters to load
		 * return: SCharSelectIds with the id of the chars for that account
		 */
		virtual SCharSelectIds loadCharSelect(irr::u32 account_id);

		/*
		 * @param char_id: [IN] The id of the char
		 * return: A pointer to the selected char info, NULL on fail
		 */
		virtual SCharInfo* loadChar(irr::u32 char_id);

		/*
		 * Saves a char to the database. Should be called periodicly and when a client disconnects,
		 * or when the server chrashes
		 *
		 * @param char_id: [IN] The id of the char (not the index used in loadChar)
		 */
		virtual void saveChar(irr::u32 char_id);

		/*
		 * Delalocats all un used chars
		 * @param full_collect: [IN] if true, remove all (even if in game) chars. If false only remove chars not in game
		 */
		virtual void garbageCollect(bool full_collect = false);

	private:

		void* Interfaces;

		AVL<irr::u32, SCharInfo*> CharInfos;
		irr::core::threads::ReadWriteLock CharInfosLock;

	};

}
}

#endif
