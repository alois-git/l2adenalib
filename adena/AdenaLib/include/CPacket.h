/*
 * CPacket.h - L2 packet.
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

#ifndef _ADENA_C_PACKET_H_
#define _ADENA_C_PACKET_H_

#include <IPacket.h>
#include <irrThread.h>
#include <irrString.h>

#define GROW_SIZE 128

namespace adena
{

	class ADENALIB_API CPacket : public irr::core::threads::Thread, public IPacket
	{
	public:

		CPacket();

		virtual ~CPacket();

		virtual void run() {}

		virtual irr::c8* getData() = 0;

		/*
         * Returns the total size of the array returned by getData.
		 */
		virtual irr::u32 getLen() = 0;

		/*
		 * Writes one byte to data. (Little endian)
		 * byte[0] = val[0]
		 */
		void w8(irr::s32 val);

		/*
		 * Writes two bytes to data. (Little endian)
		 * byte[0] = val[0]
		 * byte[1] = val[1]
		 */
		void w16(irr::s32 val);

		/*
		 * Writes four bytes to data. (Little endian)
		 * byte[0] = val[0]
		 * byte[1] = val[1]
 		 * byte[2] = val[2]
		 * byte[3] = val[3]
		 */
		void w32(irr::s32 val);

		void w64(irr::s64 val);

		void wf(irr::f64 val);

		/*
		 * Writes a ASCII null terminated string to data.
		 */
		void wStr(irr::core::stringc &str);

		/*
		 * Writes a unicode (two byte) null termininated string to data.
		 */
		void wStrW(irr::core::stringc &str);

		/*
		 * Copys from in_data to data size data_len.
		 */
		void wArray(irr::c8* in_data, irr::u32 data_len);

		/*
		 * Reads one byte from data. (Little endian)
		 */
		irr::s32 r8();

		/*
		 * Reads two byte from data. (Little endian)
		 */
		irr::s32 r16();

		/*
		 * Reads four byte from data. (Little endian)
		 */
		irr::s32 r32();

		/*
		 * Reads a ASCII null terminated string to str.
		 */
		void rStr(irr::core::stringc &str);

		/*
		 * Reads a unicode (two byte) null termininated string to str.
		 */
		void rStrW(irr::core::stringc &str);

		/*
		 * Copys from data to out_data size data_len.
		 */
		void rArray(irr::c8* out_data, irr::u32 data_len);

	protected:

		/*
		 * Resizes data to new_size.
		 */
		void resize(irr::u32 new_size);

		/*
		 * Adds 4 bytes for a check sum and then pads the packet to a multiple of 8 bytes.
		 */
		void blowfishPad();

		irr::c8* Data;
		irr::u32 DataLen;
		irr::u32 WritePointer;
		irr::u32 ReadPointer;

	};

}

#endif
