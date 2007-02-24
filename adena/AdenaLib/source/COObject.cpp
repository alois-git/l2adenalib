/*
 * COObject.cpp - Base object for all objs in l2.
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

#include <COObject.h>

namespace adena
{
namespace game_server
{

/*CMemoryManager MemoryManager(65536);

void* COObject::operator new ( size_t size )
{
	return MemoryManager.allocate(size);
};

void COObject::operator delete( void* obj )
{
	MemoryManager.deallocate(obj);
};*/

COObject::COObject(IOObjectSystem* obj_sys)
: ObjectSystem(obj_sys), Delete(false), Tick(false), RefCount(1)
{

};

COObject::~COObject()
{

};

void COObject::getRef()
{
	RefCount++;
};

void COObject::drop()
{
	RefCount--;
	if(RefCount <= 0)
		destroy();
};

void COObject::destroy()
{
	Delete = true;
};

COObject* COObject::spawn(irr::core::stringc obj)
{
	return (COObject*)ObjectSystem->loadObj(obj);
};

}
}
