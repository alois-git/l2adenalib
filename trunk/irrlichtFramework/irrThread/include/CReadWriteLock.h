/*
 * CReadWriteLock.h - Alows multiple readers and one writer at a time.
 * Created January 15, 2007, by Michael 'Bigcheese' Spencer.
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
 */

#ifndef __IRR_C_READ_WRITE_LOCK_H_INCLUDED__
#define __IRR_C_READ_WRITE_LOCK_H_INCLUDED__

#include <irrCore.h>
#include <irrThreadCompile.h>
#include <pthread.h>

namespace irr
{
namespace core
{
namespace threads
{	

	class IRRTHREAD_API ReadWriteLock
	{
	public:

		ReadWriteLock();

		~ReadWriteLock();

		void readLock();

		void writeLock();

		void unlock();

	private:

		pthread_rwlock_t RWLock;

	};

}
}
}

#endif
