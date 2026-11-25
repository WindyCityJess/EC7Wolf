#ifndef __MISTER_H__
#define __MISTER_H__

// MiSTer hybrid core: the game runs on the ARM, the ECWolf FPGA core shows
// the picture at 15kHz and provides audio and input. SDL's "mister" drivers
// (hybrid/sdl2 in the ECWolf_MiSTer repository) do most of the work; this is
// what is specific to the game. After ItsDanik's ecwolf src/mister/mister.cpp
// (GPL-2.0-or-later), trimmed for EC7Wolf.

struct WadStuff;

// Joystick buttons as SDL sees them: the buttons of the core's "J1," list
// (ECWolf.sv) in order, then the buttons the SDL driver adds
enum
{
	MISTER_JOY_CORE_OK = 8,
	MISTER_JOY_CORE_BACK = 9,
	MISTER_JOY_MENU_OK = 28,
	MISTER_JOY_MENU_BACK = 29
};
#define MISTER_JOY_OK_MASK ((1 << MISTER_JOY_CORE_OK) | (1 << MISTER_JOY_MENU_OK))
#define MISTER_JOY_BACK_MASK ((1 << MISTER_JOY_CORE_BACK) | (1 << MISTER_JOY_MENU_BACK))

// OSD option Resolution: the size of the screen the core is to show, 320 or
// 640 pixels in each of 200 or 240 lines. The picture is 4:3 at every size
void MiSTer_Resolution(unsigned &width, unsigned &height);
// Follows the Resolution option: true if the size of the screen has just
// changed and what is on it has to be drawn again
bool MiSTer_UpdateResolution();

// The game to start (MH_PickGame()) of the ones ECWolf found, by their
// iwadinfo Autoname: the menu entry's, or the player's pick from a list.
// Returns the index, -1 to quit (after a message when none is there)
int MiSTer_PickIWad(WadStuff *wads, const char *const *autonames, int numwads);
// Shows the error on the screen until the player leaves the core
void MiSTer_ShowError(const char *message);
// Exit code of the process after the player quit: the launcher starts the
// game again (back to the game list) or returns to the MiSTer menu
int MiSTer_ExitCode();

// The OSD's Cheats page (core/ECWolf.sv): God Mode (bit 35), and the triggers "Give Weapons/Ammo/Keys" (T56) and
// "Next Level" (T57), bits of MiSTer_CheatTriggers() set once each time the player selects them
// OSD options Mouse Sensitivity (bits 24..27) and Stick Sensitivity (28..31), in percent (100 = as the game has it)
int MiSTer_MouseSensitivity();
int MiSTer_StickSensitivity();
int MiSTer_GodMode();
enum { MISTER_CHEAT_GIVEALL = 1, MISTER_CHEAT_NEXTLEVEL = 2 };
int MiSTer_CheatTriggers();

#endif
