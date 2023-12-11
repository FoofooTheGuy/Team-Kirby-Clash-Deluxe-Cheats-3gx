#include <3ds.h>
#include "cheats.hpp"
#include "csvc.h"
#include <CTRPluginFramework.hpp>

#include <vector>

namespace CTRPluginFramework
{
    // This patch the NFC disabling the touchscreen when scanning an amiibo, which prevents ctrpf to be used
    static void    ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern =
        {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
        };

        Result  res;
        Handle  processHandle;
        s64     textTotalSize = 0;
        s64     startAddress = 0;
        u32 *   found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if(R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)))
            goto exit;

        found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

        if (found != nullptr)
        {
            original = found[13];
            patchAddress = (u32 *)PA_FROM_VA((found + 13));
            found[13] = 0xE1A00000;
        }

        svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
exit:
        svcCloseHandle(processHandle);
    }
	
	static MenuEntry *EntryWithHotkey(MenuEntry *entry, const std::vector<Hotkey> &hotkeys)
    {
        if (entry != nullptr)
        {
            for (const Hotkey &hotkey : hotkeys)
                entry->Hotkeys += hotkey;
        }

        return (entry);
    }
	
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

    // This function is called before main and before the game starts
    // Useful to do code edits safely
    void    PatchProcess(FwkSettings &settings)
    {
        ToggleTouchscreenForceOn();
    }

    // This function is called when the process exits
    // Useful to save settings, undo patchs or clean up things
    void    OnProcessExit(void)
    {
        ToggleTouchscreenForceOn();
    }

    void InitMenu(PluginMenu *menu)
    {
		MenuFolder *Equip = new MenuFolder("Equipment Unlockers", "Equipment = Weapons & Armour");
			Equip->Append(new MenuEntry("All Equipment is Bought and DX", BoughtEquimentDX, "Makes every item Bought & DX (Fully Upgraded).")),
			Equip->Append(new MenuEntry("All Equipment can be Bought", UnlockEquipment, "Can buy every item.")),
			Equip->Append(new MenuEntry("All Equipment can be Bought as DX", UnlockEquipmentDX, "Can buy every DX item.")),
		menu->Append(Equip);
		menu->Append(new MenuEntry("Set Gem Apples", nullptr, apples, "Maximum: 9999")),//max 9999
		menu->Append(new MenuEntry("Set Fire Fragments", nullptr, fireF, "Maximum: 999")),//fragments max 999
		menu->Append(new MenuEntry("Set Water Fragment", nullptr, waterF, "Maximum: 999")),
		menu->Append(new MenuEntry("Set Light Fragment", nullptr, lightF, "Maximum: 999")),
		menu->Append(new MenuEntry("Set Rare Fragment", nullptr, rareF, "Maximum: 999")),
		menu->Append(new MenuEntry("Set Codex Level", nullptr, bookLVL, "Maximum: 3")),//max 3
		menu->Append(EntryWithHotkey(new MenuEntry("Max Tree Size", TreeSizer), { Hotkey(Key::X, "Set the Gem Apple Tree to it's maximum size") })),
		menu->Append(new MenuEntry("Infinite Vigour", infVigour, "Infinite Vigour while on")),
		menu->Append(new MenuEntry("Infinite Potions & EXP Orbs", MaxSupportItems, "Infinite Potions and EXP Orbs (x99) while on")),
		menu->Append(EntryWithHotkey(new MenuEntry("+ 1000 Exp", Exp1000), { Hotkey(Key::Y, "Add 1000 Exp to each role") })),
		menu->Append(new MenuEntry("Complete Every Achievement", nullptr, AllAchieve, "WARNING!!!\nOnce activated, there is no going back.")),
		menu->Append(new MenuEntry("Complete Wireless & Password Achievements", nullptr, AchieveWirePass, "WARNING!!!\nOnce activated, there is no going back."));
    }
	
	std::string GetRegionName() {
		std::string region = "INVALID";
		(void)autoRegion(std::string("JAP"), std::string("USA"), std::string("EUR"), region);
		return region;
	}
	
    int main(void)
    {
		if(strcmp(GetRegionName().c_str(), "INVALID") == 0) {
			Sleep(Seconds(5));
			MessageBox("Game not supported!\nreturning to the home menu...")();
			Process::ReturnToHomeMenu();
			return 0;
		}
		
        PluginMenu *menu = new PluginMenu("Team Kirby:CD Cheats " << GetRegionName(), 1, 2, 2, "This is a rewrite of the plugin, originally made by Slattz, to modern CTRPF.");
		
		assign_region();
		
        // Synnchronize the menu with frame event
        menu->SynchronizeWithFrame(true);

        // Init our menu entries & folders
        InitMenu(menu);

        // Launch menu and mainloop
        menu->Run();

        delete menu;

        // Exit plugin
        return (0);
    }
}