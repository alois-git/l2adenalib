/*
 * Player.cpp - Base class for a player.
 * Created January 26, 2007, by Michael 'Bigcheese' Spencer.
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

#include <Player.h>
#include <GameManager.h>
#include <Controller.h>
#include <CSPSkillUsed.h>
#include <CPCharInfo.h>
#include <CSPDeleteObj.h>
#include <CSPStatusUpdate.h>
#include <CPUserInfo.h>
#include <CSPSocial.h>
#include <CSPSystemMessage.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_Player(IOObjectSystem* obj_sys)
{
	return (COObject*)new Player(obj_sys);
}
}

irr::f64 _inline expEqu(irr::f64 a, irr::f64 b, irr::f64 x)
{
	return a * pow(b, x);
}

irr::f64 _inline quadEqu(irr::f64 a, irr::f64 b, irr::f64 c, irr::f64 x)
{
	return ((a * (x * x)) + (b * x) + c);
}

irr::f64 _inline cubicEqu(irr::f64 a, irr::f64 b, irr::f64 c, irr::f64 d, irr::f64 x)
{
	return ((a * (x * x * x)) + (b * (x * x)) + (c * x) + d);
};

irr::f64 _inline getStrMod(irr::u32 str)
{
	return expEqu(0.29136804822987894, 1.0360072426254718, str);
};

irr::f64 _inline getConMod(irr::u32 con)
{
	return cubicEqu(0.0000048694242, 0.0000608003, 0.0148674192, 0.4381339809, con);
};

irr::f64 _inline getDexMod(irr::u32 dex)
{
	return quadEqu(0.000021739130434350606, 0.008717391304358557, 0.8182608695648241, dex);
};

irr::f64 _inline getMenMod(irr::u32 men)
{
	return quadEqu(0.000076312576312354, 0.008751770451773666, 1.017893772893558, men);
};

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
			table[11][i] = quadEqu(0.125, 22.375, -73.5, i + 1); // Human Wizard
			table[12][i] = quadEqu(0.175, 31.325, -511.5, i + 1); // Sorcerer
			table[13][i] = quadEqu(0.175, 31.325, -511.5, i + 1); // Necro
			table[14][i] = quadEqu(0.1889124205, 34.15301178, -647.4902592, i + 1); // Warlock
			table[15][i] = quadEqu(0.155, 27.745, -192.9, i + 1); // Cleric
			table[16][i] = quadEqu(0.18999999996594852, 34.01000000163913, -499.50000005960464, i + 1); // B1shop (A tribute to teh best bishop ever!)
			table[17][i] = quadEqu(0.20500000001629815, 36.69499999657273, -630.8999999463558, i + 1); // Prophet
			table[18][i] = quadEqu(0.0708333333277551, 12.458833333104849, 77.91699999570847, i + 1); // Light Elf Fighter
			table[19][i] = quadEqu(0.14999999999417923, 26.84999999962747, -242.00000001490116, i + 1); // Light Elf Knight
			// TODO: Finish adding this data.
		}
		// Copy base class hp stats into higher class hp stats
		for(irr::u32 c = 0; c < 10; c++)
			memcpy(table[c], table[0], sizeof(irr::f64) * 19);
	}

	return table[class_id][level - 1];
}

irr::f64 _fastcall getBaseCpForClass(irr::u32 class_id, irr::u32 level)
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
			table[0][i] = quadEqu(0.026060606058308622, 4.6484848484396935, 27.4429697021842, i + 1); // Human fighter
			table[1][i] = quadEqu(0.11999999999534339, 21.479999999515712, -216.0, i + 1); // Warrior
			table[2][i] = quadEqu(0.17106060605146922, 30.6034848485142, -558.2370303124189, i + 1); // Gladiator
			table[3][i] = quadEqu(0.16810606059152633, 30.062348485458642, -636.2653030455112, i + 1); // Warlord
			table[4][i] = quadEqu(0.0810606060513237, 14.493484848178923, -126.05703031271696, i + 1); // Human Knight
			table[5][i] = quadEqu(0.1081060606011306, 19.322348484769464, -362.485303029418, i + 1); // Paladin
			table[6][i] = quadEqu(0.1081060606011306, 19.322348484769464, -362.485303029418, i + 1); // DA
			table[7][i] = quadEqu(0.049999999995634425, 8.950000000186265, -68.20000001043081, i + 1); // Rogue
			table[8][i] = quadEqu(0.06409090909073711, 11.447727272287011, -190.656545445323, i + 1); // TH
			table[9][i] = quadEqu(0.11909090907647624, 21.292727272957563, -395.10654547065496, i + 1); // HE
			table[10][i] = quadEqu(0.042499999992287485, 7.607469697482884, 42.848878771066666, i + 1); // Human Mage
			table[11][i] = quadEqu(0.06249999999636202, 11.187469697091728, -36.75112120062113, i + 1); // Human Wizard
			table[12][i] = quadEqu(0.08749999999417923, 15.6624696967192, -255.75112122297287, i + 1); // Sorcerer
			table[13][i] = quadEqu(0.08749999999417923, 15.6624696967192, -255.75112122297287, i + 1); // Necro
			table[14][i] = quadEqu(0.11409090908273356, 20.397727272938937, -385.55654545128345, i + 1); // Warlock
			table[15][i] = quadEqu(0.07749999999577994, 13.872469696681947, -96.45112121850252, i + 1); // Cleric
			table[16][i] = quadEqu(0.13310606059530983, 23.797348483931273, -349.43530301749706, i + 1); // B1shop (A tribute to teh best bishop ever!)
			table[17][i] = quadEqu(0.10249999999359716, 18.347469696309417, -315.45112121105194, i + 1); // Prophet
			table[18][i] = quadEqu(0.028106060599384364, 5.002348484937102, 30.774696964770555, i + 1); // Light Elf Fighter
			table[19][i] = quadEqu(0.07499999999708962, 13.424999999813735, -121.00000000745058, i + 1); // Light Elf Knight
			// TODO: Finish adding this data.
		}
		// Copy base class cp stats into higher class cp stats
		for(irr::u32 c = 0; c < 10; c++)
			memcpy(table[c], table[0], sizeof(irr::f64) * 19);
	}

	return table[class_id][level - 1];
}

irr::u32 xpToLevel(irr::u64 xp)
{
	static irr::u64 table[80] = {0, 67, 362, 1167, 2883, 6037, 11286, 19422, 31377, 48228, 71201, 101676, 141192, 191453, 254329, 331866, 426287, 539999, 675595, 835861, 1023784, 1242545, 1495542, 1786378, 2118874, 2497076, 2925249, 3407897, 3949754, 4555796, 5231245, 5981576, 6812512, 7730042, 8740421, 9850165, 11066071, 12395217, 13844951, 15422930, 17137073, 18995665, 21007197, 23180554, 25524869, 28049628, 30764650, 33680047, 36806287, 40154157, 45525117, 51262487, 57383985, 63907914, 70853087, 80700820, 91162660, 102265865, 114038590, 126509649, 146308200, 167244319, 189364870, 212717918, 237352682, 271975245, 308443154, 346827140, 387199534, 429634473, 474207973, 532695005, 606322865, 696381209, 804225264, 931275779, 1151275917, 1511274870, 2099278645};

	for(irr::u32 i = 0; i < 80; i++)
	{
		if(table[i] > xp)
			return i;
	}
	return 79;
};

Player::Player(IOObjectSystem* obj_sys)
: Pawn(obj_sys)
{
	Tick = true;
	obj_sys->regTimerFunc(this, (IOObjectSystem::timerFunc)&Player::regenHpMpCp, 5000);
};

Player::~Player()
{

};

void Player::destroy()
{
	saveToDatabase();
	CharInfo->InUse = false;
	Pawn::destroy();
};

void Player::useSkill(irr::u32 skill_id, bool ctrl, bool shift)
{
	irr::core::array<SSkill>* skills = getSkills();
	for(int i = 0; i < skills->size(); i++)
	{
		if((*skills)[i].Id == skill_id)
		{
			// Player has this skill
			broadcastPacket(new CSPSkillUsed(this, (*skills)[i]));
			break;
		}
	}
};

irr::u32 Player::getSpeed()
{
	SClassTemplate* ct = Owner->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->RUN_SPEED;
};

irr::u32 Player::getLevel()
{
	return CharInfo->Level;
};

irr::f64 Player::getMaxHp()
{
	irr::f64 basehp = getBaseHpForClass(CharInfo->ClassId, getLevel());
	basehp *= getConMod(getCON());
	return basehp;	
};

irr::f64 Player::getHp()
{
	return Hp;
};

irr::f64 Player::getMaxMp()
{
	return 0;
};

irr::f64 Player::getMp()
{
	return 0;	
};

irr::f64 Player::getMaxCp()
{
	irr::f64 basecp = getBaseCpForClass(CharInfo->ClassId, getLevel());
	basecp *= getConMod(getCON());
	return basecp;
};

irr::f64 Player::getCp()
{
	return Cp;
};

irr::u32 Player::getSTR()
{
	SClassTemplate* ct = Owner->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->STR;
};

irr::u32 Player::getCON()
{
	SClassTemplate* ct = Owner->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->CON;
};

irr::u32 Player::getDEX()
{
	SClassTemplate* ct = Owner->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->DEX;
};

irr::u32 Player::getINT()
{
	SClassTemplate* ct = Owner->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->INT;
};

irr::u32 Player::getWIT()
{
	SClassTemplate* ct = Owner->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->WIT;
};

irr::u32 Player::getMEN()
{
	SClassTemplate* ct = Owner->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->MEN;
};

irr::u32 Player::getPAttack()
{
	SClassTemplate* ct = Owner->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return (irr::f64)ct->P_ATK * ((irr::f64)(Level + 89) / 100) * getStrMod(getSTR());
};

irr::f32 Player::getAttackSpeed()
{
	return getDexMod(getDEX()) * 300;
};

irr::f32 Player::getAttackRange()
{
	return 25; // TODO: Get range from current weapon.
};

irr::f32 Player::getHpRegen()
{
	// Get base regen
	irr::u32 level = getLevel();
	irr::f32 regen = 2.0;
	if(level > 10)
	{
		regen += 0.5;
		irr::u32 add = (level - 1) / 10;
		--add;
		regen += add;
	}

	// Get movement modifier
	switch(MoveState)
	{
		case EMS_Sitting:
			regen *= 1.5;
			break;
		case EMS_Still:
			regen *= 1.1;
			break;
		case EMS_Walking:
			regen *= 1.0;
			break;
		case EMS_Moving:
			regen *= 0.7;
			break;
	}

	// Get con modifier
	regen *= getConMod(getCON());
	return regen;
};

irr::core::array<SSkill>* Player::getSkills()
{
	return &CharInfo->Skills;
};

void Player::setHp(irr::f64 hp)
{
	irr::f64 maxhp = getMaxHp();
	if(hp > maxhp)
		hp = maxhp;
	else if(hp < 0)
		hp = 0;
	if(Hp != hp)
	{
		CharInfo->hp = Hp = hp;
		HpUpdated = true;
	}
};

void Player::setCp(irr::f64 cp)
{
	irr::f64 maxcp = getMaxCp();
	if(cp > maxcp)
		cp = maxcp;
	else if(cp < 0)
		cp = 0;
	if(Cp != cp)
	{
		CharInfo->cp = Cp = cp;
		CpUpdated = true;
	}
};

void Player::setXp(irr::u64 xp)
{
	CharInfo->xp = Xp = xp;
	irr::u32 tmplvl = xpToLevel(Xp);
	
	if(tmplvl != Level)
	{
		if(tmplvl > Level)
		{
			CSPSocial* s = new CSPSocial(Id, ES_LEVEL_GAIN);
			broadcastPacket(s);
		}
		CharInfo->Level = Level = tmplvl;
		Cp = getMaxCp();
		Hp = getMaxHp();
		Mp = getMaxMp();
	}
	CPUserInfo* ui = new CPUserInfo(this);
	Owner->sendPacket(ui);
}

void Player::onSeeObj(Actor* obj)
{

};

void Player::onBeenSeen(Actor* obj)
{
	Player* p = dynamic_cast<Player*>(obj);
	if(p)
	{
		CPCharInfo* ni = new CPCharInfo(this);
		p->Owner->sendPacket(ni);
	}
};

void Player::onLoseObj(Actor* obj)
{
	if(obj == Target)
	{
		((Controller*)Owner->PController)->setTarget(0);
	}
};

void Player::onBeenLost(Actor* obj)
{
	Player* p = dynamic_cast<Player*>(obj);
	if(p)
	{
		CSPDeleteObj* ni = new CSPDeleteObj(Id);
		p->Owner->sendPacket(ni);
	}
};

irr::u32 Player::onDoAttackDmg(Actor* target)
{
	irr::u32 dmg = getPAttack() * 25;
	CSPSystemMessage* sm = new CSPSystemMessage(EMI_YOU_DID_S1_DMG);
	sm->addNumber(dmg);
	Owner->sendPacket(sm);
	target->takeDamage(this, dmg, false, false);
	PawnState = EPS_None;
	return dmg;
};

bool Player::regenHpMpCp(void* data)
{
	if(PawnState != EPS_Dead)
	{
		setHp(getHp() + getHpRegen());
		setCp(getCp() + getHpRegen()); // HpRegen and CpRegen are the same value.
	}
	return true;
};

void Player::saveToDatabase()
{
	CharInfo->x = Location.X;
	CharInfo->y = Location.Y;
	CharInfo->z = Location.Z;
	Owner->Server->Interfaces.PlayerCache->saveChar(CharInfo->CharacterId);
};

}
}
