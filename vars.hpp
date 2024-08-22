#pragma once

#define GUI_NAME "D3D11 Internal OAR"
#define initalize 0x00000
#define GameC "OAR Game"

#define CUSTOM_ICONS FALSE

struct Vars
{
	// GUI
	bool open = false;
	bool drawc = false;
	bool cfov = false;
	int tab = 0;

	// Cheat
	float currentfov;
};
extern Vars* vars;