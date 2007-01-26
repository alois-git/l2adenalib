/*
 * CReadWriteLock.cpp - Alows multiple readers and one writer at a time.
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

#include <CReadWriteLock.h>

namespace irr
{
namespace core
{
namespace threads
{	

ReadWriteLock::ReadWriteLock()
: RWLock(PTHREAD_RWLOCK_INITIALIZER)
{

};

ReadWriteLock::~ReadWriteLock()
{
	pthread_rwlock_destroy(&RWLock);
};

void ReadWriteLock::readLock()
{
	pthread_rwlock_rdlock(&RWLock);
};

void ReadWriteLock::writeLock()
{
	pthread_rwlock_wrlock(&RWLock);
};

void ReadWriteLock::unlock()
{
	pthread_rwlock_unlock(&RWLock);
};

}
}
}
