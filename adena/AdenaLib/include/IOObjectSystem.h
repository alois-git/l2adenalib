/*
 * IOObjectSystem.h - Interface for object manager.
 * Created January 13, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_I_O_OBJECT_SYSTEM_H_
#define _ADENA_I_O_OBJECT_SYSTEM_H_

#include <AdenaConfig.h>
#include <irrString.h>
#include <IOObject.h>

namespace adena
{
namespace game_server
{

	class IOObjectSystem
	{
	public:

		typedef bool (IOObject::*timerFunc) (void*);

		virtual ~IOObjectSystem() {}

		/*
		 * @param func: [IN] Function to call.
		 * @param m_seconds_from_now: [IN] Miliseconds from the current time to call this func.
		 */
		virtual void regTimerFunc(IOObject* obj, timerFunc func, irr::u32 m_seconds_from_now, void* data = 0) = 0;

		// Loads an obj and adds it to the system.
		virtual IOObject* loadObj(irr::core::stringc &obj) = 0;

		virtual IOObject* getObj(irr::u32 id) = 0;

		virtual void removeObj(irr::u32 id) = 0;

	};

}
}

#endif
