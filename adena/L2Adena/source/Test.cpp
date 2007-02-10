/*
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
 */

#include <CLoginServer.h>
#include <CGameServer.h>
#include <irrNet.h>
#include <iostream>
#include <CReadFile.h>
#include <CCrypt.h>
#include <CFileSystem.h>
#include <CInProcessLoginServerLink.h>
#include <CInProcessGameServerLink.h>
#include <CSkillInfoCache.h>
#include <CL2PacketCap.h>

using namespace std;
using namespace irr;

/*static const irr::c8 key[8] = {0x94, 0x35, 0x00, 0x00, 0xa1, 0x6c,	0x54, 0x87};

u32 addPack(io::IFileSystem* fs, c8* buff, c8* file_name)
{
	io::IReadFile* rf = fs->createAndOpenFile(file_name);
	u32 size = rf->getSize();
	return rf->read(buff, size);
}

void parseBuff(c8* buff, u32 buff_len)
{
	adena::game_server::CCrypt cc((irr::c8*)key);
	u32 loc = 0;
	while(loc < buff_len)
	{
		c8 temp[65536];
		u16 pack_size = 0;
		pack_size += (unsigned char)buff[loc++];
		pack_size += ((unsigned char)(buff[loc++]) * 256);
		memcpy(temp, buff + loc, pack_size - 2);
		loc += (pack_size - 2);
		cc.decrypt(temp, pack_size - 2);
		if((temp[0] & 0xff) < 0x10)
			printf("Packet size: %d Packet type: 0x0%x\n", pack_size, (temp[0] & 0xff));
		else
			printf("Packet size: %d Packet type: 0x%x\n", pack_size, (temp[0] & 0xff));
		hexdump(temp, pack_size - 2);
	}
	cout << "Loc " << loc << " Buff len " << buff_len << "\n";
}

int main()
{
	c8 buff[65536];
	u32 loc = 0;
	io::CFileSystem fs = io::CFileSystem();
	for(int i = 1; i <= 7; i++)
	{
		loc += addPack(&fs, buff + loc, (irr::c8*)(irr::core::stringc("sp0") + i).c_str());
	}
	parseBuff(buff, loc);
	system("PAUSE");*/

int main()
{
	/*adena::utility::CL2PacketCap lpc = adena::utility::CL2PacketCap();
	lpc.run();

	system("PAUSE");*/

	adena::login_server::CLoginServer* s = new adena::login_server::CLoginServer();
	adena::game_server::CGameServer* g = new adena::game_server::CGameServer();
	adena::login_server::CInProcessGameServerLink GameLink = adena::login_server::CInProcessGameServerLink(s);
	adena::game_server::CInProcessLoginServerLink LogLink = adena::game_server::CInProcessLoginServerLink(g, &GameLink, 0);
	s->GameServerLink = &GameLink;
	g->LoginServerLink = &LogLink;
	if(s->init("login.ini"))
	{
		s->start();
		if(g->init("game.ini"))
		{
			g->start();
			s->wait();
			g->wait();
		}
		else
		{
			cout << "Failed to init game server\n";
		}
	}else
	{
		cout << "Failed to init login server\n";
	}
	delete s;
	delete g;
	irr::net::Cleanup();
	system("PAUSE");
	return 0;
}
