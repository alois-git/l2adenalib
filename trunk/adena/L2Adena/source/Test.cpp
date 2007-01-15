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

using namespace std;
using namespace irr;

irr::f64 _inline getConMod(irr::u32 con);
irr::f64 _fastcall getBaseHpForClass(irr::u32 class_id, irr::u32 level);

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
	parseBuff(buff, loc);*/

int main()
{
	irr::f64 basehp = getBaseHpForClass(0, 19);
	irr::f64 conmod = getConMod(43);
	cout << "Hp = " << (irr::u32)(basehp * conmod) << "\n";

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
	system("PAUSE");
	delete s;
	delete g;
	irr::net::Cleanup();
	return 0;
}

irr::f64 _inline quadEqu(irr::f64 a, irr::f64 b, irr::f64 c, irr::f64 x)
{
	return ((a * (x * x)) + (b * x) + c);
}

irr::f64 _inline cubicEqu(irr::f64 a, irr::f64 b, irr::f64 c, irr::f64 d, irr::f64 x)
{
	return ((a * (x * x * x)) + (b * (x * x)) + (c * x) + d);
}

irr::f64 _inline getConMod(irr::u32 con)
{
	return cubicEqu(0.0000048694242, 0.0000608003, 0.0148674192, 0.4381339809, con);
}

irr::f64 _fastcall getBaseHpForClass(irr::u32 class_id, irr::u32 level)
{
	static irr::f64 table[119][80];
	static bool gened = false;

	if( !((class_id < 119) && (level < 81) && (level > 0)) )
		return 0;

	if(!gened)
	{
		gened = true;
		// Generate table
		irr::u32 i;
		for(i = 0; i < 80; i++)
		{
			table[0][i] = quadEqu(0.064990671, 11.63594781, 68.27948918, i + 1); // Human fighter
			table[1][i] = quadEqu(0.15, 26.85, -270, i + 1); // Warrior
			table[2][i] = quadEqu(0.19, 34.01, -620.4, i + 1); // Gladiator
			table[3][i] = quadEqu(0.21, 37.59, -795.6, i + 1); // Warlord
			table[4][i] = quadEqu(0.135, 25.165, -210.3, i + 1); // Human Knight
			table[5][i] = quadEqu(0.18, 32.22, -604.5, i + 1); // Paladin
			table[6][i] = quadEqu(0.18, 32.22, -604.5, i + 1); // DA
			table[7][i] = quadEqu(0.125, 22.375, -170.5, i + 1); // Rogue
			table[8][i] = quadEqu(0.1598791578, 28.6558902, -477.6100288, i + 1); // TH
			table[9][i] = quadEqu(0.17, 30.43, -564.7, i + 1); // HE
			table[10][i] = quadEqu(0.085, 15.215, 85.7, i + 1); // Human Mage
		}
	}

	return table[class_id][level - 1];
}