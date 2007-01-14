/*
 * CPacketQueue.cpp - Packet queue ftw.
 * Created January 12, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CPacketQueue.h>

namespace adena
{
namespace game_server
{

CPacketQueue::CPacketQueue(irr::u32 backlog)
{

};

CPacketQueue::~CPacketQueue()
{
	QueueMutex.getLock();

	while(!Queue.empty())
	{
		(*Queue.begin())->drop();
		Queue.erase(Queue.begin());
	}

	QueueMutex.releaseLock();
};

void CPacketQueue::addPacket(IPacket *packet)
{
	QueueMutex.getLock();
	if(Queue.empty())
	{
		Queue.push_back(packet);
		QueueMutex.releaseLock();
		return;
	}

	if(packet->Priority == EPP_NOT_REQUIRED)
	{
		if(Queue.getSize() >= BackLog)
		{
			// Ignore packet
			QueueMutex.releaseLock();
			return;
		}else
		{
			// Just stick it on the back
			Queue.push_back(packet);
			QueueMutex.releaseLock();
			return;
		}
	}

	irr::core::list<IPacket*>::Iterator ittr(Queue.begin());
	for(; ittr != Queue.end(); ittr++)
	{
		if((*ittr)->Priority < packet->Priority)
		{
			Queue.insert_before(ittr, packet);
			QueueMutex.releaseLock();
			return;
		}
	}
	// Add to the end
	Queue.push_back(packet);
	QueueMutex.releaseLock();
};

IPacket* CPacketQueue::getNextPacket()
{
	QueueMutex.getLock();
	if(Queue.empty())
	{
		QueueMutex.releaseLock();
		return NULL;
	}else
	{
		irr::core::list<IPacket*>::Iterator ittr(Queue.begin());
		IPacket* ret = (*ittr);
		Queue.erase(ittr);
		QueueMutex.releaseLock();
		return ret;
	}
};

}
}
