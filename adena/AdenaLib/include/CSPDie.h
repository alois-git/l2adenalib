/*
 * CSPDie.h - Ohnoes something died.
 * Created February 8, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_S_P_DIE_H_
#define _ADENA_C_S_P_DIE_H_


#include <CServerPacket.h>
#include <Player.h>
#include <NPC.h>

namespace adena
{
namespace game_server
{

	class CSPDie : public CServerPacket
	{
	public:

		CSPDie(Pawn* pawn)
		: CServerPacket(), P(pawn)
		{
			Priority = EPP_URGENT;
		};

		virtual ~CSPDie() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				Writen = true;
				w8(0x06);
				
				w32(P->Id);
				w32(0x01); // To town
				w32(0x00); // To hide away
				w32(0x00); // To castle
				w32(0x00); // To siege HQ
				w32(0x00); // Sweepable  (blue glow)
				w32(0x00); // To FIXED
			}

			return true;
		};

		virtual irr::c8* getData()
		{
			return Data;
		};

		virtual irr::u32 getLen()
		{
			return WritePointer;
		};

	private:

		Pawn* P;

	};

}
}

#endif
