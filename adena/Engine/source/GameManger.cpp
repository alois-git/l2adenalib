/*
 * GameManager.cpp - Basicly manages the game play of the server.
 * Created January 25, 2007, by Michael 'Bigcheese' Spencer.
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

#include <GameManager.h>
#include <Controller.h>
#include <CPCharInfo.h>
#include <CSPSystemMessage.h>
#include <irrThread.h>
#include <NPC.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_GameManager(IOObjectSystem* obj_sys)
{
	return (COObject*)new GameManager(obj_sys);
}
}

class NPCLoaderThread : public irr::core::threads::Thread
{
public:
	NPCLoaderThread(irr::db::IDatabase* db, World* w, CNPCCache* npcc): Db(db), W(w), NPCC(npcc) {};
	~NPCLoaderThread(){};

	virtual void run()
	{
		printf("Loading NPCs...\n");
		irr::db::Query q(irr::core::stringc("SELECT * FROM spawnlist")); // 37,000 entries :O
		irr::db::CQueryResult qr = Db->query(q);
		for(irr::u32 i = 0; i < qr.RowCount; i++)
		{
			NPC* n = (NPC*)W->spawn("Engine.NPC");
			n->NPCInfo = NPCC->getNPC(atoi(qr[i]["npc_templateid"].c_str()));
			n->SpawnLoc.X = atoi(qr[i]["locx"].c_str());
			n->SpawnLoc.Y = atoi(qr[i]["locy"].c_str());
			n->SpawnLoc.Z = atoi(qr[i]["locz"].c_str());
			n->SpawnHeading = atoi(qr[i]["heading"].c_str());
			n->RespawnDelay = atoi(qr[i]["respawn_delay"].c_str());
			n->Hp = n->NPCInfo->Hp;
			n->Mp = n->NPCInfo->Mp;
			n->respawn();
			W->newObj(n);
		}
		printf("NPCs loaded.\n");
		delete this;
	};

	irr::db::IDatabase* Db;
	World* W;
	CNPCCache* NPCC;
};

GameManager::GameManager(IOObjectSystem* obj_sys)
: COObject(obj_sys), Mut(0)
{
	ControllerClass = "Engine.Controller";
	PlayerClass = "Engine.Player";
	L2World = (World*)spawn("Engine.World");
};

GameManager::~GameManager()
{
	L2World->destroy();
};

void GameManager::init(SGameServerInterfaces* interfaces)
{
	Interfaces = interfaces;
	NPCLoaderThread* nlt = new NPCLoaderThread(Interfaces->DataBase, L2World, Interfaces->NPCCache);
	nlt->run(); // TODO: Change back to start.
	Mut = (Mutator*)spawn("Engine.MutAutoSkill");
};

void GameManager::tick(irr::f32 delta_time)
{

};

void GameManager::broadcastPacket(IPacket* packet)
{
	packet->getRef();
	if(((CServerPacket*)packet)->writePacket())
	{
		irr::core::list<Player*>::Iterator ittr(PlayerList.begin());
		for(; ittr != PlayerList.end(); ittr++)
		{
			(*ittr)->Owner->sendPacket(packet);
		}
	}
	packet->drop();
};

Player* GameManager::playerEnterWorld(SCharInfo* char_info, IGameServerClient* owner)
{
	Controller* c = (Controller*)spawn(ControllerClass);
	owner->PController = c;
	c->Owner = owner;
	Player* p = (Player*)spawn(PlayerClass);
	p->Owner = owner;
	p->CharInfo = owner->CharInfo;
	p->Location.X = p->CharInfo->x;
	p->Location.Y = p->CharInfo->y;
	p->Location.Z = p->CharInfo->z;
	p->Location.Z = owner->Server->Interfaces.GeoData->getHeight(p->Location);
	p->Hp = p->CharInfo->hp;
	p->Cp = p->CharInfo->cp;
	p->Mp = p->CharInfo->mp;
	p->Xp = p->CharInfo->xp;
	p->Sp = p->CharInfo->sp;
	p->Level = p->CharInfo->Level;
	PlayerList.push_back(p);
	c->posses(p);
	char_info->InUse = true;

	L2World->newObj(p);
	Mut->playerEnterWorld(p);

	CSPSystemMessage* sm = new CSPSystemMessage(irr::core::stringc("Welcome to l2adena - v") + ADENA_VERSION);
	owner->sendPacket(sm);

	return p;
};

void GameManager::playerLeaveWorld(Player* player)
{
	Mut->playerLeaveWorld(player);
	L2World->removeObj(player);
	player->drop();
};

}
}
