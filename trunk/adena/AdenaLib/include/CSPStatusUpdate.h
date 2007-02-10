/*
 * CSPStatusUpdate.h - Update teh status.
 * Created February 7, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_S_P_STATUS_UDATE_H_
#define _ADENA_C_S_P_STATUS_UDATE_H_

#include <CServerPacket.h>
#include <Pawn.h>
#include <irrArray.h>

namespace adena
{
namespace game_server
{

	enum E_Status_Id
	{
		ESI_LEVEL = 0x01,
		ESI_EXP = 0x02,
		ESI_STR = 0x03,
		ESI_DEX = 0x04,
		ESI_CON = 0x05,
		ESI_INT = 0x06,
		ESI_WIT = 0x07,
		ESI_MEN = 0x08,

		ESI_CUR_HP = 0x09,
		ESI_MAX_HP = 0x0a,
		ESI_CUR_MP = 0x0b,
		ESI_MAX_MP = 0x0c,

		ESI_SP = 0x0d,
		ESI_CUR_LOAD = 0x0e,
		ESI_MAX_LOAD = 0x0f,

		ESI_P_ATK = 0x11,
		ESI_ATK_SPD = 0x12,
		ESI_P_DEF = 0x13,
		ESI_EVASION = 0x14,
		ESI_ACCURACY = 0x15,
		ESI_CRITICAL = 0x16,
		ESI_M_ATK = 0x17,
		ESI_CAST_SPD = 0x18,
		ESI_M_DEF = 0x19,
		ESI_PVP_FLAG = 0x1a,
		ESI_KARMA = 0x1b,

		ESI_CUR_CP = 0x21,
		ESI_MAX_CP = 0x22
	};

	class CSPStatusUpdate : public CServerPacket
	{
	public:

		CSPStatusUpdate(Pawn* obj)
		: CServerPacket(), P(obj)
		{
			Priority = EPP_URGENT;

			if(P->HpUpdated)
			{
				Update.push_back(ESI_CUR_HP);
				P->HpUpdated = false;
			} if(P->CpUpdated)
			{
				Update.push_back(ESI_CUR_CP);
				P->CpUpdated = false;
			}
		};

		virtual ~CSPStatusUpdate() {};

		void forceUpdate(E_Status_Id status_id)
		{
			for(irr::u32 i = 0; i < Update.size(); i++)
			{
				if(Update[i] == status_id)
					return; // Already there, don't need to force it.
			}
			Update.push_back(status_id);
		};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				Writen = true;
				w8(0x0e);

				w32(P->Id);
				w32(Update.size());
				for(irr::u32 i = 0; i < Update.size(); i++)
				{
					switch(Update[i])
					{
						case ESI_LEVEL:
							w32(ESI_LEVEL);
							w32(P->getLevel());
							break;
						case ESI_EXP:
							w32(ESI_EXP);
							w32(P->Xp);
							break;
						case ESI_CUR_HP:
							w32(ESI_CUR_HP);
							w32(P->getHp());
							break;
						case ESI_MAX_HP:
							w32(ESI_MAX_HP);
							w32(P->getMaxHp());
							break;
						case ESI_CUR_CP:
							w32(ESI_CUR_CP);
							w32(P->getCp());
							break;
						case ESI_MAX_MP:
							w32(ESI_MAX_MP);
							w32(P->getMaxMp());
							break;
					}
				}
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
		irr::core::array<E_Status_Id> Update;

	};

}
}

#endif
