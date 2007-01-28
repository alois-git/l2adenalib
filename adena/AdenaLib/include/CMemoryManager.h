/*
 * CMemoryManager.h - Manages memory :P (new/delete overloads).
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

#ifndef _ADENA_C_MEMORY_MANAGER_H_
#define _ADENA_C_MEMORY_MANAGER_H_

#include <AdenaConfig.h>
#include <irrList.h>
//#include <CReadWriteLock.h>

namespace adena
{
namespace game_server
{

	class ADENALIB_API CMemoryManager
	{
	public:

		CMemoryManager(irr::u32 mem_grow_size = 65536);

		~CMemoryManager();

		inline void* allocate(irr::u32 size);

		inline void* reallocate(void* memory, irr::u32 size);

		inline void deallocate(void* memory);

	private:

		enum EMemState
		{
			EMS_USED = 0,
			EMS_FREE,
			EMS_LARGE
		};

		struct SMem
		{
			irr::u8* Mem;
			irr::u32 MemSize;
			EMemState State;
		};

		struct SMemList
		{
			irr::u8* Mem;
			irr::u32 MemLoc;
		};

		inline void addToMemList(SMem &mem);

		irr::u32 MemGrowSize;

		irr::core::list<SMemList> Memory;

		SMem* MemList;
		irr::u32 MemListSize;
		irr::u32 MemListUsed;

	};

}
}

#endif
