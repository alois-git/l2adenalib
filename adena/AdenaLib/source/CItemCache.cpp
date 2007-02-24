/*
 * CItemCache.cpp - Items ftw.
 * Created February 20, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CItemCache.h>
#include <CDbRandInstance.h>

namespace adena
{
namespace game_server
{

CItemCache::CItemCache()
{

};

CItemCache::~CItemCache()
{

};

CItemCache* CItemCache::getInstance()
{
	static CItemCache* ic = 0;

	if(!ic)
	{
		ic = new CItemCache();
		ic->init(CDbRandInstance::getDbInstance());
	}

	return ic;
};

void CItemCache::init(irr::db::IDatabase* db)
{
	printf("Loading item info...\n");
	{
		// Load armor
		printf("	Armor...\n");
		irr::db::Query q(irr::core::stringc("SELECT * FROM armor"));
		irr::db::CQueryResult qr = db->query(q);

		for(irr::u32 i = 0; i < qr.RowCount; i++)
		{
			SItemInfo* ii = new SItemInfo;

			ii->ItemType = EIT_Armor;
			ii->ItemId = atoi(qr[i]["item_id"].c_str());

			if(qr[i]["body_part"] == "head")
				ii->BodyPart = EBP_Head;
			else if(qr[i]["body_part"] == "chest")
				ii->BodyPart = EBP_Chest;
			else if(qr[i]["body_part"] == "legs")
				ii->BodyPart = EBP_Legs;
			else if(qr[i]["body_part"] == "gloves")
				ii->BodyPart = EBP_Gloves;
			else if(qr[i]["body_part"] == "feet")
				ii->BodyPart = EBP_Feet;
			else if(qr[i]["body_part"] == "underwear")
				ii->BodyPart = EBP_Underwear;
			else if(qr[i]["body_part"] == "fullarmor")
				ii->BodyPart = EBP_FullArmor;
			else if(qr[i]["body_part"] == "rear,lear")
				ii->BodyPart = EBP_Ear;
			else if(qr[i]["body_part"] == "rfinger,lfinger")
				ii->BodyPart = EBP_Finger;
			else if(qr[i]["body_part"] == "neck")
				ii->BodyPart = EBP_Neck;
			else
				ii->BodyPart = EBP_None;

			qr[i]["crystallizable"] == "true" ? ii->Crystallizable = true : ii->Crystallizable = false;
			ii->Weight = atoi(qr[i]["weight"].c_str());

			if(qr[i]["crystal_type"] == "none")
				ii->ItemGrade = EIG_None;
			else if(qr[i]["crystal_type"] == "d")
				ii->ItemGrade = EIG_d;
			else if(qr[i]["crystal_type"] == "c")
				ii->ItemGrade = EIG_c;
			else if(qr[i]["crystal_type"] == "b")
				ii->ItemGrade = EIG_b;
			else if(qr[i]["crystal_type"] == "a")
				ii->ItemGrade = EIG_a;
			else if(qr[i]["crystal_type"] == "s")
				ii->ItemGrade = EIG_s;

			ii->Price = atoi(qr[i]["price"].c_str());
			ii->CrystalCount = atoi(qr[i]["crystal_count"].c_str());
			qr[i]["sellable"] == "true" ? ii->Sellable = true : ii->Sellable = false;

			if(qr[i]["armor_type"] == "light")
				ii->Armor.ArmorType = EAT_Light;
			else if(qr[i]["armor_type"] == "heavy")
				ii->Armor.ArmorType = EAT_Heavy;
			else if(qr[i]["armor_type"] == "magic")
				ii->Armor.ArmorType = EAT_Robe;
			else
				ii->Armor.ArmorType = EAT_None;

			ii->Armor.Pdef = atoi(qr[i]["p_def"].c_str());
			ii->Armor.Mdef = atoi(qr[i]["m_def"].c_str());

			ItemInfo.Insert(ii->ItemId, ii);
		}
	}
	{
		// Load weapons
		printf("	Weapons...\n");
		irr::db::Query q(irr::core::stringc("SELECT * FROM weapon"));
		irr::db::CQueryResult qr = db->query(q);

		for(irr::u32 i = 0; i < qr.RowCount; i++)
		{
			SItemInfo* ii = new SItemInfo;

			ii->ItemType = EIT_Weapon;
			ii->ItemId = atoi(qr[i]["item_id"].c_str());

			if(qr[i]["body_part"] == "rhand")
				ii->BodyPart = EBP_RHand;
			else if(qr[i]["body_part"] == "lhand")
				ii->BodyPart = EBP_LHand;
			else
				ii->BodyPart = EBP_None;

			qr[i]["crystallizable"] == "true" ? ii->Crystallizable = true : ii->Crystallizable = false;
			ii->Weight = atoi(qr[i]["weight"].c_str());

			if(qr[i]["crystal_type"] == "none")
				ii->ItemGrade = EIG_None;
			else if(qr[i]["crystal_type"] == "d")
				ii->ItemGrade = EIG_d;
			else if(qr[i]["crystal_type"] == "c")
				ii->ItemGrade = EIG_c;
			else if(qr[i]["crystal_type"] == "b")
				ii->ItemGrade = EIG_b;
			else if(qr[i]["crystal_type"] == "a")
				ii->ItemGrade = EIG_a;
			else if(qr[i]["crystal_type"] == "s")
				ii->ItemGrade = EIG_s;

			ii->Price = atoi(qr[i]["price"].c_str());
			ii->CrystalCount = atoi(qr[i]["crystal_count"].c_str());
			qr[i]["sellable"] == "true" ? ii->Sellable = true : ii->Sellable = false;

			ii->Weapon.SoulShots = atoi(qr[i]["soulshots"].c_str());
			ii->Weapon.SpirtShots = atoi(qr[i]["spiritshots"].c_str());
			ii->Weapon.PDam = atoi(qr[i]["p_dam"].c_str());
			ii->Weapon.RandDam = atoi(qr[i]["rnd_dam"].c_str());

			if(qr[i]["weaponType"] == "sword")
				ii->Weapon.WeaponType == EWT_Sword;
			else if(qr[i]["weaponType"] == "bigsword")
				ii->Weapon.WeaponType == EWT_BigSword;
			else if(qr[i]["weaponType"] == "blunt")
				ii->Weapon.WeaponType == EWT_Blunt;
			else if(qr[i]["weaponType"] == "dagger")
				ii->Weapon.WeaponType == EWT_Dagger;
			else if(qr[i]["weaponType"] == "bow")
				ii->Weapon.WeaponType == EWT_Bow;
			else if(qr[i]["weaponType"] == "pole")
				ii->Weapon.WeaponType == EWT_Pole;
			else if(qr[i]["weaponType"] == "fist")
				ii->Weapon.WeaponType == EWT_Fist;
			else if(qr[i]["weaponType"] == "dualfist")
				ii->Weapon.WeaponType == EWT_DualFist;
			else if(qr[i]["weaponType"] == "etc")
				ii->Weapon.WeaponType == EWT_ETC;
			else
				ii->Weapon.WeaponType == EWT_None;

			ii->Weapon.Critical = atoi(qr[i]["critical"].c_str());
			ii->Weapon.HitMod = atof(qr[i]["hit_modify"].c_str());
			ii->Weapon.AvoidMod = atoi(qr[i]["avoid_modify"].c_str());
			ii->Weapon.ShieldDef = atoi(qr[i]["shield_def"].c_str());
			ii->Weapon.ShieldDefRate = atoi(qr[i]["shield_def_rate"].c_str());
			ii->Weapon.AtkSpeed = atoi(qr[i]["atk_speed"].c_str());
			ii->Weapon.MpConsume = atoi(qr[i]["mp_consume"].c_str());
			ii->Weapon.MDam = atoi(qr[i]["m_dam"].c_str());

			ItemInfo.Insert(ii->ItemId, ii);
		}
	}
	{
		// Load etcitems
		printf("	etc Items...\n");
		irr::db::Query q(irr::core::stringc("SELECT * FROM etcitem"));
		irr::db::CQueryResult qr = db->query(q);

		for(irr::u32 i = 0; i < qr.RowCount; i++)
		{
			SItemInfo* ii = new SItemInfo;
			ii->ItemType = EIT_ETCItem;
			ii->ItemId = atoi(qr[i]["item_id"].c_str());
			ii->BodyPart = EBP_None;

			qr[i]["crystallizable"] == "true" ? ii->Crystallizable = true : ii->Crystallizable = false;
			ii->Weight = atoi(qr[i]["weight"].c_str());

			if(qr[i]["crystal_type"] == "none")
				ii->ItemGrade = EIG_None;
			else if(qr[i]["crystal_type"] == "d")
				ii->ItemGrade = EIG_d;
			else if(qr[i]["crystal_type"] == "c")
				ii->ItemGrade = EIG_c;
			else if(qr[i]["crystal_type"] == "b")
				ii->ItemGrade = EIG_b;
			else if(qr[i]["crystal_type"] == "a")
				ii->ItemGrade = EIG_a;
			else if(qr[i]["crystal_type"] == "s")
				ii->ItemGrade = EIG_s;

			ii->Price = atoi(qr[i]["price"].c_str());
			ii->CrystalCount = atoi(qr[i]["crystal_count"].c_str());
			qr[i]["sellable"] == "true" ? ii->Sellable = true : ii->Sellable = false;

			if(qr[i]["item_type"] == "none")
				ii->ETCItem.ItemType == EEIT_None;
			else if(qr[i]["item_type"] == "arrow")
				ii->ETCItem.ItemType == EEIT_Arrow;
			else if(qr[i]["item_type"] == "potion")
				ii->ETCItem.ItemType == EEIT_Pot;
			else if(qr[i]["item_type"] == "quest")
				ii->ETCItem.ItemType == EEIT_Quest;
			else if(qr[i]["item_type"] == "spellbook")
				ii->ETCItem.ItemType == EEIT_SpellBook;
			else if(qr[i]["item_type"] == "scroll")
				ii->ETCItem.ItemType == EEIT_Scroll;
			else if(qr[i]["item_type"] == "material")
				ii->ETCItem.ItemType == EEIT_Material;
			else if(qr[i]["item_type"] == "recipe")
				ii->ETCItem.ItemType == EEIT_Recipe;
			else if(qr[i]["item_type"] == "petcollar")
				ii->ETCItem.ItemType == EEIT_PetCollar;
			else if(qr[i]["item_type"] == "castlegaurd")
				ii->ETCItem.ItemType == EEIT_CastleGaurd;
			else if(qr[i]["item_type"] == "seed")
				ii->ETCItem.ItemType == EEIT_Seed;
			else if(qr[i]["item_type"] == "shot")
				ii->ETCItem.ItemType == EEIT_Shot;
			else
				ii->ETCItem.ItemType == EEIT_None;

			if(qr[i]["consume_type"] == "stackable")
				ii->ETCItem.ConsumeType == ECT_Stackable;
			else if(qr[i]["consume_type"] == "asset")
				ii->ETCItem.ConsumeType == ECT_Asset;
			else
				ii->ETCItem.ConsumeType == ECT_Normal;

			ItemInfo.Insert(ii->ItemId, ii);
		}
	}
	printf("Item info loaded.\n");
};

SItemInfo* CItemCache::getItemInfo(irr::u32 item_id)
{
	SItemInfo* ii;
	if(ItemInfo.Find(item_id, ii))
	{
		return ii;
	}
	return 0;
};

}
}
