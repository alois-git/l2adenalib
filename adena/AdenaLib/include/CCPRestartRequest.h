/*
 * CCPRestartRequest.h - Client wants to go back to char select screen.
 * Created January 15, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_C_P_RESTART_REQUEST_H_
#define _ADENA_C_C_P_RESTART_REQUEST_H_

#include <CClientPacket.h>
#include <CPCharSelect.h>
#include <Controller.h>

namespace adena
{
namespace game_server
{

	class CCPRestartRequest : public CClientPacket
	{
	public:

		CCPRestartRequest(irr::c8* in_data, Controller* c)
		: CClientPacket()
		{
			Data = in_data;
			ReadPointer++;
		};

		virtual ~CCPRestartRequest()
		{
			Data = 0;
		};

		virtual void run()
		{

		};

		virtual irr::c8* getData()
		{
			return NULL;
		};

		virtual irr::u32 getLen()
		{
			return 0;
		};

	};

}
}

#endif
