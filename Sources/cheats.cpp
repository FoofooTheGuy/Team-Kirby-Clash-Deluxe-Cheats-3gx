#include "cheats.hpp"

namespace CTRPluginFramework
{
	template <typename T>
	bool autoRegion(const T& JPN, const T& USA, const T& EUR, T& out) {
		switch(Process::GetTitleID()) {
			case 0x00040000001a0000: {
				out = JPN;
				return true;
			}
			case 0x00040000001ab800: {
				out = USA;
				return true;
			}
			case 0x00040000001ab900: {
				out = EUR;
				return true;
			}
		}
		return false;
	}
	
	u32	g_apples;
	u32	g_firef;
	u32	g_waterf;
	u32	g_lightf;
	u32	g_raref;
	u32	g_tree;
	u32	g_vigour;
	u32	g_achieve;
	u32	g_items;
	u32	g_exp;

	void assign_region() {
		g_apples = APPLES_ADDR;
		g_firef = FIREF_ADDR;
		g_waterf = WATERF_ADDR;
		g_lightf = LIGHTF_ADDR;
		g_raref = RAREF_ADDR;
		g_tree = TREESIZE_ADDR;
		g_vigour = VIGOUR_ADDR;
		g_achieve = ACHIEVEMENTS_ADDR;
		g_items = ITEMS_ADDR;
		g_exp = EXP_ADDR;
		
		int Difference = 0;
		if(autoRegion(JAP_DIFFERENCE, USA_DIFFERENCE, 0, Difference)) {
			g_apples -= Difference;
			g_firef -= Difference;
			g_waterf -= Difference;
			g_lightf -= Difference;
			g_raref -= Difference;
			g_tree -= Difference;
			g_vigour -= Difference;
			g_achieve -= Difference;
			g_items -= Difference;
			g_exp -= Difference;
		}
	}
	
	void EquipmentState(u32 state) //All Equipment State Modifier
	{
		for (int i = 0; i < 88; i++)
		{
			Process::Write32(g_items + 0x1 + (i * 4), state);
		}
	}
	
	u16 get_current_apples() {
		return (*(u16 *)g_apples);
	}

	u16 get_current_fireF() {
		return (*(u16 *)g_firef);
	}

	u16 get_current_waterF() {
		return (*(u16 *)g_waterf);
	}

	u16 get_current_lightF() {
		return (*(u16 *)g_lightf);
	}

	u16 get_current_rareF() {
		return (*(u16 *)g_raref);
	}

	u8 get_current_BookLVL() {
		return (*(u8 *)g_items + 0x161);
	}
	
	void set_current_BookLVL(u8 value) {//Sets Codex as sold out and sets level
		u8 current_BookLVL;

		current_BookLVL = get_current_BookLVL();
		for (int i = 0; i < 4; i++)
		{
			Process::Write32(g_items + 0x160 + (i * 4), 0x01020000); //amount,status(sold out),level,00
			Process::Write8(g_items + 0x161 + (i * 4), value);
			current_BookLVL = get_current_BookLVL();
			
			if (current_BookLVL == 0x03)
			{
				Process::Write32(g_items + 0x160 + (i * 4), 0x01040300);
			}
		}
	}
	
	Keyboard *kb = new Keyboard("Enter value:");
	
	//entries
	void BoughtEquimentDX(MenuEntry *entry) {//Sets 'sold out & DX' state for all items.
		EquipmentState(0x401);
	}
	
	void UnlockEquipment(MenuEntry *entry) {//Sets 'Can buy' state for all items.
		u32 def = 0x300;
		EquipmentState(0x200);
		Process::Write32(g_items + 0x02, def);
		Process::Write32(g_items + 0x2E, def);
		Process::Write32(g_items + 0x5A, def);
		Process::Write32(g_items + 0x86, def);
		Process::Write32(g_items + 0xB2, def);
		Process::Write32(g_items + 0xDE, def);
		Process::Write32(g_items + 0x10A, def);
		Process::Write32(g_items + 0x136, def);
	}
	
	void UnlockEquipmentDX(MenuEntry *entry) {//Sets 'Can buy DX' state for all items.
		EquipmentState(0x201);
	}
	
	void apples(MenuEntry *entry) {
		kb->GetMessage() = "Enter how many gem apples you want (max 9999)";
		kb->IsHexadecimal(false);
		kb->SetMaxLength(4);
		u16 value = 0;
		if (kb->Open(value, get_current_apples()) != -1)
		{
			Process::Write16(g_apples, (value > 9999 ? 9999 : value));
		}
	}

	void fireF(MenuEntry *entry) {
		kb->GetMessage() = "Enter how many fire fragments you want (max 999)";
		kb->IsHexadecimal(false);
		kb->SetMaxLength(4);
		u16 value = 0;
		if (kb->Open(value, get_current_fireF()) != -1)
		{
			Process::Write16(g_firef, (value > 999 ? 999 : value));
		}
	}

	void waterF(MenuEntry *entry) {
		kb->GetMessage() = "Enter how many water fragments you want (max 999)";
		kb->IsHexadecimal(false);
		kb->SetMaxLength(4);
		u16 value = 0;
		if (kb->Open(value, get_current_waterF()) != -1)
		{
			Process::Write16(g_waterf, (value > 999 ? 999 : value));
		}
	}

	void lightF(MenuEntry *entry) {
		kb->GetMessage() = "Enter how many light fragments you want (max 999)";
		kb->IsHexadecimal(false);
		kb->SetMaxLength(4);
		u16 value = 0;
		if (kb->Open(value, get_current_lightF()) != -1)
		{
			Process::Write16(g_lightf, (value > 999 ? 999 : value));
		}
	}

	void rareF(MenuEntry *entry) {
		kb->GetMessage() = "Enter how many light fragments you want (max 999)";
		kb->IsHexadecimal(false);
		kb->SetMaxLength(4);
		u16 value = 0;
		if (kb->Open(value, get_current_rareF()) != -1)
		{
			Process::Write16(g_raref, (value > 999 ? 999 : value));
		}
	}

	void bookLVL(MenuEntry *entry) {
		kb->GetMessage() = "Enter the codex level you want (max 3)";
		kb->IsHexadecimal(false);
		kb->SetMaxLength(4);
		u8 value = 0;
		if (kb->Open(value, get_current_rareF()) != -1)
		{
			set_current_BookLVL((value > 3 ? 3 : value));
		}
	}
	
	void TreeSizer(MenuEntry *entry) {//Max tree size
		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			Process::Write16(g_tree, 0x0BB8);
		}
	}

	void infVigour(MenuEntry *entry) {//Infinite Vigour
		Process::Write8(g_vigour, 0x6E);
	}

	void MaxSupportItems(MenuEntry *entry) {//99 Potion & Orb
		for (int i = 0; i < 3; i++) {
			Process::Write16(g_items + 0x172 + (i * 4), 0x6303);
		}
	}
	
	void Exp1000(MenuEntry *entry) {//Add 1000 Exp
		u32 current_exp;
	
		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			Process::Read32(g_exp, current_exp);
			
			if (current_exp < 0x0F423F)
			{
				*(u16 *)g_exp += 0x3E8;
				*(u16 *)(g_exp + 0xC) += 0x3E8;
				*(u16 *)(g_exp + 0x18) += 0x3E8;
				*(u16 *)(g_exp + 0x24) += 0x3E8;
			}
			else
			{
				Process::Write32(g_exp, 0x0F423F);
			}
		}
	}
	
	void AllAchieve(MenuEntry *entry) {//Unlock All Achievements.
		if ((MessageBox("WARNING!!!\nOnce activated, there is no going back.\nContinue?", DialogType::DialogOkCancel)).SetClear(ClearScreen::None)()) {
			for (int i = 0; i < 254; i++) {
				Process::Write8(g_achieve + (i * 8), 0x04);
			}
		}
		else MessageBox("Operation cancelled")();
	}

	void AchieveWirePass(MenuEntry *entry) {//Unlock Wireless And Password Achievements.
		if ((MessageBox("WARNING!!!\nOnce activated, there is no going back.\nContinue?", DialogType::DialogOkCancel)).SetClear(ClearScreen::None)()) {
			for (int i = 0; i < 6; i++) {
				Process::Write8(g_achieve + 0x708 + (i * 8), 0x04);
				Process::Write8(g_achieve + 0x7D0, 0x04);
			}
		}
		else MessageBox("Operation cancelled")();
	}
}
