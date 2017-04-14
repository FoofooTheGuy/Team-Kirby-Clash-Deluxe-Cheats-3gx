#include "cheats.h"

#define ENTRY_COUNT 300

typedef struct s_menu
{
    int         count;
    int         status;
    u32         f[ENTRY_COUNT];
    u32         s[ENTRY_COUNT];
    int         a[ENTRY_COUNT];
    const char  *t[ENTRY_COUNT];
    const char  *n[ENTRY_COUNT];
    void        (*fp[ENTRY_COUNT])();
}             t_menu;


typedef void    (*FuncPointer)(void);
extern t_menu menu;



void    new_super_unselectable_entry(char *str, FuncPointer function)
{
    int index;

    index = menu.count;
    if (index >= 300)
        return;
    new_unselectable_entry(str);
    menu.f[index] |= BIT(0) | BIT(1);
    menu.fp[index] = function;
}

char	*builder_name = "Slattz";

void with_note_common(const char *name, const char *note, void (*cheatfunction)(void), int type)
{
    int     index;

    if (type == 0)
        index = new_entry((char *)name, cheatfunction);
    else if (type == 1)
        index = new_radio_entry((char *)name, cheatfunction);
    else if (type == 2)
        index = new_spoiler((char *)name);
    else return;
    set_note(note, index);
}

inline void new_entry_with_note(const char *name, const char *note, void (*cheatfunction)(void))
{
    with_note_common(name, note, cheatfunction, 0);
}

inline void new_radio_entry_with_note(const char *name, const char *note, void (*cheatfunction)(void))
{
    with_note_common(name, note, cheatfunction, 1);
}

inline void new_spoiler_with_note(const char *name, const char *note)
{
    with_note_common(name, note, NULL, 2);
}

char    apples_level_buffer[40] = "Current Apples: ";
char    fireF_level_buffer[40] = "Current Fire Fragments: ";
char    waterF_level_buffer[40] = "Current Water Fragsments: ";
char    lightF_level_buffer[40] = "Current Light Fragsments: ";
char    rareF_level_buffer[40] = "Current Rare Fragsments: ";
int     g_increase_menu_index1 = 0;
int     g_decrease_menu_index1 = 0;
int     g_increase_menu_index2 = 0;
int     g_decrease_menu_index2 = 0;
int     g_increase_menu_index3 = 0;
int     g_decrease_menu_index3 = 0;
int     g_increase_menu_index4 = 0;
int     g_decrease_menu_index4 = 0;
int     g_increase_menu_index5 = 0;
int     g_decrease_menu_index5 = 0;

static inline void  smenu(void)
{
    new_spoiler("Apple Codes");
        new_unselectable_entry(apples_level_buffer);
        g_increase_menu_index1 = new_entry("+ 1", increase_apples);
        g_decrease_menu_index1 = new_entry("- 1", decrease_apples);
        new_entry("Max Apples", max_apples);
    exit_spoiler();
    new_spoiler("Fire Fragment Codes");
        new_unselectable_entry(fireF_level_buffer);
        g_increase_menu_index2 = new_entry("+ 1", increase_fireF);
        g_decrease_menu_index2 = new_entry("- 1", decrease_fireF);
        new_entry("Max Fire Fragments", max_fireF);
    exit_spoiler();
    new_spoiler("Water Fragment Codes");
        new_unselectable_entry(waterF_level_buffer);
        g_increase_menu_index3 = new_entry("+ 1", increase_waterF);
        g_decrease_menu_index3 = new_entry("- 1", decrease_waterF);
        new_entry("Max Water Fragments", max_waterF);
    exit_spoiler();
    new_spoiler("Light Fragment Codes");
        new_unselectable_entry(lightF_level_buffer);
        g_increase_menu_index4 = new_entry("+ 1", increase_lightF);
        g_decrease_menu_index4 = new_entry("- 1", decrease_lightF);
        new_entry("Max Light Fragments", max_lightF);
    exit_spoiler();
    new_spoiler("Rare Fragment Codes");
        new_unselectable_entry(rareF_level_buffer);
        g_increase_menu_index5 = new_entry("+ 1", increase_rareF);
        g_decrease_menu_index5 = new_entry("- 1", decrease_rareF);
        new_entry("Max Rare Fragments", max_rareF);
    exit_spoiler();
}

void    my_menus(void)
{
    u32 tid;
    
    set_hid_address(0x10002000); //This is in order to unlock the advanced HID capabilities such as Touchscreen and the stick (No N3DS hid for the moment)
    tid = get_tid_low();
	
    if (tid == 0x1ab900)
    {
		assign_region(EUR);
		new_unselectable_entry("Kirby Crash Deluxe Cheats v1.0 EUR");
    }
	
	else if (tid == 0x1ab800)
    {
		assign_region(USA);
		new_unselectable_entry("Kirby Crash Deluxe Cheats v1.0 USA");
    }
	
	/*else if (tid == 0x1abX00)
    {
		assign_region(JAP);
		new_unselectable_entry("Kirby Crash Deluxe Cheats v1.0 JAP");
    }*/
	
	
	else
	{
		new_unselectable_entry("You're Using An Incorrect TitleID!");			
		new_unselectable_entry("This plugin only supports the");
		new_unselectable_entry("Following TitleIDs:");
		new_unselectable_entry("00040000001ab900 (EUR)");
		new_unselectable_entry("00040000001ab800 (USA)");
		//new_unselectable_entry("0004000000054100 (JAP)");
		
        return;
    }
    smenu();
}