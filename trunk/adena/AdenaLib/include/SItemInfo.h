/*
 * SItemInfo.h - Item info.
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

#ifndef _ADENA_C_ITEM_CACHE_H_
#define _ADENA_C_ITEM_CACHE_H_

#include <AdenaConfig.h>

namespace adena
{
namespace game_server
{

	enum E_ItemType
	{
		EIT_Armor = 0,
		EIT_Weapon,
		EIT_ETCItem
	};

	enum E_BodyPart
	{
		EBP_Head = 0,
		EBP_Chest,
		EBP_Legs,
		EBP_Gloves,
		EBP_Feet,
		EBP_Underwear,
		EBP_FullArmor,
		EBP_Ear,
		EBP_Finger,
		EBP_Neck,

		EBP_RHand,
		EBP_LHand,

		EBP_None
	};

	enum E_ArmorType
	{
		EAT_Light = 0,
		EAT_Heavy,
		EAT_Robe,
		EAT_None
	};

	enum E_WeaponType
	{
		EWT_Sword = 0,
		EWT_BigSword,
		EWT_Blunt,
		EWT_Dagger,
		EWT_Bow,
		EWT_Pole,
		EWT_Fist,
		EWT_DualFist,
		EWT_ETC,
		EWT_None
	};

	enum E_ETCItemType
	{
		EEIT_None = 0,
		EEIT_Arrow,
		EEIT_Pot,
		EEIT_Quest,
		EEIT_SpellBook,
		EEIT_Scroll,
		EEIT_Material,
		EEIT_Recipe,
		EEIT_PetCollar,
		EEIT_CastleGaurd,
		EEIT_Seed,
		EEIT_Shot
	};

	enum E_ConsumeType
	{
		ECT_Normal = 0,
		ECT_Stackable,
		ECT_Asset
	};

	enum E_ItemGrade
	{
		EIG_None = 0,
		EIG_d,
		EIG_c,
		EIG_b,
		EIG_a,
		EIG_s
	};

	struct SItemInfo
	{
		E_ItemType ItemType;
		irr::u32 ItemId;
		E_BodyPart BodyPart;
		bool Crystallizable;
		irr::s32 Weight;
		E_ItemGrade ItemGrade;
		irr::u32 Price;
		irr::u32 CrystalCount;
		bool Sellable;
		union
		{
			struct
			{
				E_ArmorType ArmorType;
				irr::u32 Pdef;
				irr::u32 Mdef;
			} Armor;

			struct
			{
				irr::u32 SoulShots;
				irr::u32 SpirtShots;
				irr::u32 PDam;
				irr::u32 RandDam;
				E_WeaponType WeaponType;
				irr::u32 Critical;
				irr::f32 HitMod;
				irr::s32 AvoidMod;
				irr::u32 ShieldDef;
				irr::u32 ShieldDefRate;
				irr::u32 AtkSpeed;
				irr::u32 MpConsume;
				irr::u32 MDam;
			} Weapon;

			struct
			{
				E_ETCItemType ItemType;
				E_ConsumeType ConsumeType;
			} ETCItem;
		};
	};

}
}

#endif
