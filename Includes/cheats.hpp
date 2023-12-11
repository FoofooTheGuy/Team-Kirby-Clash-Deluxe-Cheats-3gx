#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

#define		APPLES_ADDR				0x302B21EC
#define		FIREF_ADDR				0x302B220C
#define		WATERF_ADDR				0x302B2210
#define		LIGHTF_ADDR				0x302B2214
#define		RAREF_ADDR				0x302B2218
#define		TREESIZE_ADDR			0x302B2209
#define		VIGOUR_ADDR				0x302B23E8
#define		ACHIEVEMENTS_ADDR		0x302B19EC
#define		ITEMS_ADDR				0x302B2220
#define		EXP_ADDR				0x302B15A4


#define		USA_DIFFERENCE			0x1C20
#define		JAP_DIFFERENCE			0x3BE0

namespace CTRPluginFramework
{
	void assign_region();
	
	void BoughtEquimentDX(MenuEntry *entry);
	void UnlockEquipment(MenuEntry *entry);
	void UnlockEquipmentDX(MenuEntry *entry);
	void apples(MenuEntry *entry);
	void fireF(MenuEntry *entry);
	void waterF(MenuEntry *entry);
	void lightF(MenuEntry *entry);
	void rareF(MenuEntry *entry);
	void bookLVL(MenuEntry *entry);
	void TreeSizer(MenuEntry *entry);
	void infVigour(MenuEntry *entry);
	void MaxSupportItems(MenuEntry *entry);
	void Exp1000(MenuEntry *entry);
	void AllAchieve(MenuEntry *entry);
	void AchieveWirePass(MenuEntry *entry);
}
#endif