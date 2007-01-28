/*
 * IPacket.h - L2 protocol packet interface.
 * Created January 4, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_I_PACKET_H_
#define _ADENA_I_PACKET_H_

#include <AdenaConfig.h>

namespace adena
{

	/*
	 * The packets priority, used to decide which packets to send.
	 * If the packet queue gets above max_packet_queue_size set in the config, packets marked as EPP_NOT_REQUIRED will be removed.
	 */
	enum E_Packet_Priority
	{
		EPP_URGENT = 0,		// Move and Atk packets
		EPP_HIGH = 1,
		EPP_NORMAL = 2,
		EPP_LOW = 3,
		EPP_NOT_REQUIRED = 4// Item list updates, effect notifications, etc
	};

	class IPacket
	{
	public:

		IPacket() : RefCount(0), Crypt(true) {}

		virtual ~IPacket() {}

		virtual irr::c8* getData() = 0;

		/*
         * Returns the total size of the data returned by getData.
		 */
		virtual irr::u32 getLen() = 0;

		inline void getRef() {RefCount++;}

		inline void drop() {RefCount--; if(RefCount <= 0) delete this;}

		E_Packet_Priority Priority;

		irr::u32 RefCount;

		bool Crypt;

	protected:


	};

}

#endif
