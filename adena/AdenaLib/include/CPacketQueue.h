/*
 * CPacketQueue.h - Packet queue ftw.
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

#ifndef _ADENA_C_PACKET_QUEUE_H_
#define _ADENA_C_PACKET_QUEUE_H_

#include <AdenaConfig.h>
#include <IPacket.h>
#include <irrThread.h>

namespace adena
{
namespace game_server
{

	class CPacketQueue
	{
	public:

		/*
		 * @param backlog: The max number of packets waiting to be sent before EPP_NOT_REQUIRED packets get bumped off.
		 */
		CPacketQueue(irr::u32 backlog);

		virtual ~CPacketQueue();

		void addPacket(IPacket* packet);

		/*
		 * Grabs the next packet off the queue based on the packet priority
		 */
		IPacket* getNextPacket();

	private:

		irr::u32 BackLog;
		irr::core::list<IPacket*> Queue;
		irr::core::threads::Mutex QueueMutex;

	};

}
}

#endif
