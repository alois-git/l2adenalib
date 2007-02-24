/*
 * CSPSetupGauge.h - Teh gauge.
 * Created February 10, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_S_P_SETUP_GAUGE_H_
#define _ADENA_C_S_P_SETUP_GAUGE_H_

#include <Player.h>
#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	enum E_GaugeColor
	{
		EGC_BLUE = 0,
		EGC_RED = 1,
		EGC_CYAN = 2
	};

	class CSPSetupGauge : public CServerPacket
	{
	public:

		CSPSetupGauge(E_GaugeColor color, irr::u32 time)
		: CServerPacket(), Color(color), Time(time)
		{
			Priority = EPP_HIGH;
		};

		virtual ~CSPSetupGauge() {};

		virtual bool writePacket()
		{
			if(!Writen)
			{
				w8(0x6d);

				w32(Color);
				w32(Time);
				w32(Time);
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

		E_GaugeColor Color;
		irr::u32 Time;

	};

}
}

#endif
