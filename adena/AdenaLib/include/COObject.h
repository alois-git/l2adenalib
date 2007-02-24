/*
 * COObject.h - Base object for all objs in l2.
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

#ifndef _ADENA_C_O_OBJECT_H_
#define _ADENA_C_O_OBJECT_H_

#include <IOObject.h>
#include <irrString.h>
#include <IOObjectSystem.h>
#include <CMemoryManager.h>
#include <os.h>

#ifdef _IRR_WINDOWS_
#define REG_EXPORT _declspec(dllexport)
#else
#define REG_EXPORT
#endif

namespace adena
{
namespace game_server
{

	//extern CMemoryManager MemoryManager;

	/*
	 * COObject is the root of all objects in the game
	 */
	class ADENALIB_API COObject : public IOObject
	{
	friend class COObjectSystem;
	public:

		//inline void* operator new ( size_t size );

		//inline void operator delete ( void* obj );

		COObject(IOObjectSystem* obj_sys);

		virtual ~COObject();

		void getRef();

		void drop();

		virtual void destroy();

		/*
		 * @param : obj - string with the obj to load (ex "Core.Adena").
		 */
		COObject* spawn(irr::core::stringc obj);

		virtual void tick(irr::f32 delta_time) {}

		// Last time in miliseconds that the object was ticked.
		irr::u32 LastTickTime;
		bool Tick;

	protected:

		IOObjectSystem* ObjectSystem;

	private:

		irr::s32 RefCount;
		bool Delete;

	};

}
}

#endif
