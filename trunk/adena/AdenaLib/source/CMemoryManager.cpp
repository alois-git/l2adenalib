/*
 * CMemoryManager.cpp - Manages memory :P (new/delete overloads).
 * Created January 23, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CMemoryManager.h>

namespace adena
{
namespace game_server
{

CMemoryManager::CMemoryManager(irr::u32 mem_grow_size)
: MemGrowSize(mem_grow_size)
{
	SMemList s;
	s.Mem = new irr::u8[MemGrowSize];
	s.MemLoc = 0;
	Memory.push_back(s);

	MemList = new SMem[128];
	memset(MemList, 0, sizeof(SMem) * 128);

	MemListSize = 128;
	MemListUsed = 0;
};

CMemoryManager::~CMemoryManager()
{
	delete[] MemList;

	irr::core::list<SMemList>::Iterator ittr(Memory.begin());
	for(; ittr != Memory.end(); ittr++)
	{
		delete[] (*ittr).Mem;
	}
};

inline void* CMemoryManager::allocate(irr::u32 size)
{
	if(size > MemGrowSize)
	{
		// Too large.
		SMem s;
		s.Mem = new irr::u8[size];
		s.MemSize = size;
		s.State = EMS_LARGE;
		addToMemList(s);
		return s.Mem;
	}

	// Look in the free list.
	irr::u32 i;
	for(i = 0; i < MemListUsed; i++)
	{
		if( (MemList[i].MemSize >= size) && (MemList[i].State == EMS_FREE) )
		{
			// Use the free space
			MemList[i].State = EMS_USED;
			return MemList[i].Mem;
		}
	}

	// No room in the free list, add to the mem list.
	irr::core::list<SMemList>::Iterator ittr(Memory.begin());
	for(; ittr != Memory.end(); ittr++)
	{
		if((MemGrowSize - (*ittr).MemLoc) >= size)
		{
			// Ther's room, so use it.
			SMem s;
			s.Mem = ((*ittr).Mem + (*ittr).MemLoc);
			(*ittr).MemLoc += size;
			s.MemSize = size;
			s.State = EMS_USED;
			addToMemList(s);
			return s.Mem;
		}
	}

	// No room in the memory, add it.
	SMemList ml;
	ml.Mem = new irr::u8[MemGrowSize];
	ml.MemLoc = size;
	SMem s;
	s.Mem = ml.Mem;
	s.MemSize = size;
	s.State = EMS_USED;
	addToMemList(s);
	return ml.Mem;
};

inline void* CMemoryManager::reallocate(void* memory, irr::u32 size)
{
	// Find it in the list
	irr::u32 i;
	for(i = 0; i < MemListUsed; i++)
	{
		if(MemList[i].Mem == memory)
		{
			void* temp = allocate(size);
			memcpy(temp, MemList[i].Mem, MemList[i].MemSize);
			deallocate(memory);
			return temp;
		}
	}
	return NULL;
};

inline void CMemoryManager::deallocate(void* memory)
{
	// Find the mem in the mem list.
	irr::u32 i;
	for(i = 0; i < MemListUsed; i++)
	{
		if(MemList[i].Mem == memory)
		{
			if(MemList[i].State == EMS_LARGE)
			{
				delete[] MemList[i].Mem;
				memset(&MemList[i], 0, sizeof(SMem));
				return;
			}

			MemList[i].State = EMS_FREE;
			return;
		}
	}
};

inline void CMemoryManager::addToMemList(SMem &mem)
{
	if(MemListUsed >= MemListSize)
	{
		// Enlarge the list.
		SMem* temp = new SMem[MemListSize * 2];
		memcpy(temp, MemList, MemListSize);
		delete[] MemList;
		MemList = temp;
		MemListSize *= 2;
	}
	MemList[MemListUsed++] = mem;
};

}
}
