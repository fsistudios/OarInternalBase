#include <Windows.h>
#include "vars.hpp"
#include "Unreal/4.27.2-18319896+++UE4+Release-4.27-OAR/CppSDK/SDK.hpp"
#include "Unreal/4.27.2-18319896+++UE4+Release-4.27-OAR/CppSDK/PropertyFixup.hpp"
#include "Unreal/4.27.2-18319896+++UE4+Release-4.27-OAR/CppSDK/UnrealContainers.hpp"

#include <stdio.h>

// if _C at end of name it cant be accessed, (blueprint)

Vars* vars = new Vars();

extern DWORD D3DThread();

uint64_t game_base = 0;
SDK::UWorld* world = 0;
SDK::UObject* objects = 0;
SDK::FString* names = 0;
SDK::UGameInstance* game_instance = 0;
SDK::AWorldSettings* worldsettings = 0;
SDK::UPlayer* player = 0;
SDK::APlayerController* playercontroller = 0;
SDK::APlayerController* playerassignedcontroller = 0;

UC::int32 controllerid;

namespace offset
{
	uintptr_t OarInternalBase = 0x0;
}

namespace functions
{
	// Shit not working
	void SetFire(int firetype)
	{
		playercontroller->StartFire(firetype);
	}
}

namespace mod
{
	void CreateConsole()
	{
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		SetConsoleTitle("Internal OAR Hook Console");
		system("color d");
		FILE* f;
		freopen_s(&f, "CONOUT$", "w", stdout);
	}

	void Log(const char* msg, const char* name, uintptr_t addr)
	{
		printf("[ LOG ] Message: %s: | %s | 0x%llX\n", msg, name, addr);
	}

	void initc()
	{
		CreateConsole();
		system("cls");
		Log("This message is from the cheat itself (0x0)", "OAR Internal", offset::OarInternalBase);
		Log("Made by FSI211, any other is fake.", "OAR Internal Info", offset::OarInternalBase);
		Log("More cheats or ask for features: https://discord.gg/kKXZmnHSWU", "OAR Internal (FSI Studios Server) Discord", offset::OarInternalBase);
		Log("Enough yapping, enjoy the cheat bro :)", "OAR Internal", offset::OarInternalBase);
		printf("-------------------------------------------------------------------------------------------------------------------\n");
		Log("Press insert in game for mod menu", "OAR Internal", offset::OarInternalBase);
		Log("Objects at: ", "OAR Game", SDK::Offsets::GObjects);
		Log("World at: ", "OAR Game", SDK::Offsets::GWorld);
		Log("Names at: ", "OAR Game", SDK::Offsets::GNames);
		Log("Initalizing gamebase: ", "OAR Game", game_base);

		game_base = (uint64_t)GetModuleHandle(0);

		Log("Inited gamebase successfully", "OAR Game", game_base);
		Log("Initalizing world: ", "OAR Game", SDK::Offsets::GWorld);

		// world = *(SDK::UWorld**)(game_base + 0x4C233F0);
		world = world->GetWorld();

		Log("Inited world successfully", "OAR Game", SDK::Offsets::GWorld);
		Log("Initalizing gameinstance: ", "OAR Game", (uintptr_t)game_instance);

		game_instance = world->OwningGameInstance;

		Log("Inited gameinstance successfully", "OAR Game", (uintptr_t)game_instance);
		Log("Initalizing objects: ", "OAR Game", SDK::Offsets::GObjects);

		// objects = *(SDK::UObject**)(game_base + 0x4ADBA50); 
		objects = *(SDK::UObject**)(game_base + SDK::Offsets::GObjects);

		Log("Inited objects successfully", "OAR Game", SDK::Offsets::GObjects);

		Log("Getting game settings: ", "OAR Game", (uintptr_t)worldsettings);

		worldsettings = world->K2_GetWorldSettings();

		Log("Got game settings successfully", "OAR Game", (uintptr_t)worldsettings);

		Log("Getting names: ", "OAR Game", SDK::Offsets::GNames);

		// names = *(SDK::UObject**)(game_base + 0x4A9F700); 
		names = *(SDK::FString**)(game_base + SDK::Offsets::GNames); 

		Log("Got names successfully: ", "OAR Game", SDK::Offsets::GNames);

		player = *(SDK::UPlayer**)(game_base + 0x0020);

		Log("Player offset: ", "OAR Game", (uintptr_t)player);

		playerassignedcontroller = *(SDK::APlayerController**)(game_base + 0x0030);

		Log("PlayerAssignedController offset: ", "OAR Game", (uintptr_t)playercontroller);

		playercontroller = *(SDK::APlayerController**)(game_base + 0x02D8);

		Log("PlayerController offset: ", "OAR Game", (uintptr_t)playercontroller);

		Log("Ready to cheat :)", "OAR Game", offset::OarInternalBase);
	}
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hMod);
		CloseHandle(CreateThread(0, 0, (PTHREAD_START_ROUTINE)D3DThread, 0, 0, 0));
		CloseHandle(CreateThread(0, 0, (PTHREAD_START_ROUTINE)mod::initc, 0, 0, 0));
	}
	return TRUE;
}
