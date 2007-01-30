/*
 * COObjectSystem.cpp - Object manager.
 * Created January 25, 2007, by Michael 'Bigcheese' Spencer.
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

#include <COObjectSystem.h>
#include <os.h>

namespace adena
{
namespace game_server
{

COObjectSystem::COObjectSystem()
: Ids(0)
{

};

COObjectSystem::~COObjectSystem()
{
	{
		AVL<irr::core::stringc, void*>::Iterator<irr::core::stringc, void*> ittr(&Librarys);
		irr::core::stringc key;
		void* item;
		if(ittr.GetFirst(key, item))
		{
			while(true)
			{
				irr::os::Library::CloseLib(item);
				if(!ittr.GetNext(key, item))
					break;
			}
		}
	}
	{
		AVL<irr::u32, IOObject*>::Iterator<irr::u32, IOObject*> ittr(&Objects);
		irr::u32 key;
		IOObject* item;
		if(ittr.GetFirst(key, item))
		{
			while(true)
			{
				delete ((COObject*)item);
				if(!ittr.GetNext(key, item))
					break;
			}
		}
	}
};

void COObjectSystem::run()
{
	AVL<irr::u32, IOObject*>::Iterator<irr::u32, IOObject*> ittr(&Objects);
	while(Running)
	{
		irr::u32 key;
		IOObject* item;
		if(ittr.GetFirst(key, item))
		{
			while(true)
			{
				if(((COObject*)item)->Delete)
				{
					removeObj(((COObject*)item)->Id);
					delete item;
				}else
				{
					irr::u32 time = irr::os::Timer::getRealTime();
					irr::u32 tdif = time - ((COObject*)item)->LastTickTime;
					((COObject*)item)->tick( (irr::f32)tdif / (irr::f32)1000 );
					((COObject*)item)->LastTickTime = time;
					irr::os::Sleep::sleep(0);
				}
				if(!ittr.GetNext(key, item))
					break;
			}
		}
	}
};

IOObject* COObjectSystem::loadObj(irr::core::stringc &obj)
{
	irr::s32 place = obj.find(".");
	irr::core::stringc package = obj.subString(0, place);
	#ifdef _DEBUG
	package += "Debug";
	#endif
	irr::core::stringc object = obj.subString(place + 1, obj.size());
	// Look in the library tree.
	void * item;
	if(Librarys.Find(package, item))
	{
		// Found it.
		irr::core::stringc func("load_");
		func += object;
		load_Obj l = (load_Obj)irr::os::Library::LoadFunc(item, func.c_str());
		if(l == 0)
			return NULL;
		IOObject* o = l((IOObjectSystem*)this);
		o->Id = Ids;
		Objects.Insert(Ids++, o);
		return o;
	}

	// Not in there, load it.
	void* lib = irr::os::Library::LoadLib(package.c_str());
	if(lib == 0)
		return NULL;
	Librarys.Insert(package, lib);
	irr::core::stringc func("load_");
	func += object;
	load_Obj l = (load_Obj)irr::os::Library::LoadFunc(lib, func.c_str());
	if(l == 0)
		return NULL;
	IOObject* o = l((IOObjectSystem*)this);
	o->Id = Ids;
	Objects.Insert(Ids++, o);
	return o;
};

IOObject* COObjectSystem::getObj(irr::u32 id)
{
	IOObject* item;
	if(Objects.Find(id, item))
	{
		return item;
	}
	return 0;
};

void COObjectSystem::removeObj(irr::u32 id)
{
	IOObject* item;
	if(Objects.Find(id, item))
	{
		Objects.Remove(id);
	}
};

}
}
