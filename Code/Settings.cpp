#pragma once
#include "Settings.h"
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <Windows.h>

const char* SettingsFileName = "SSA_Settings.txt";

void Settings::CreateSettingsFile()
{
	std::fstream settingsStream;
	settingsStream.open(SettingsFileName, std::ios::in | std::ios::out | std::ios::trunc);
	if (settingsStream.is_open()) {
		OutputDebugStringA("ta open");
		std::string fileout;
		fileout += "# SETTINGS FILE FOR SUPER SIMEON AUTOS\n";
		fileout += "# 0 = Disabled | 1 = Enabled\n\n";

		fileout += "# Enable lighthouse as a delivery point\n";
		fileout += "LightHouseAsDelivery=1\n\n";

		fileout += "# Enable the Del Perro Pier as a delivery point\n";
		fileout += "PierAsDelivery=1\n\n";

		fileout += "# Enable/Disable the Del Perro Pier as a delivery point during Daddy's Little Girl  (enabled(1) by default)\n";
		fileout += "PierStateDuringDLG=1\n\n";

		fileout += "# Enable or Disable Simeon as a delivery point during Armenian missions (Frankling and Lamar | Complications) (enabled (1) by default)\n";
		fileout += "SimeonStateDuringArmenian=1\n\n";

		fileout += "# Enable the lifeguard tower (Vespucci Beach) as a delivery point\n";
		fileout += "BeachAsDelivery=0\n\n";

		fileout += "# Protection for the player to not abuse the parking lot next to lifeguard tower (anti cheat)\n";
		fileout += "AntiParkingLotBeach=1\n\n";

		fileout += "# Enable Simeon as a delivery point\n";
		fileout += "SimeonAsDelivery=1\n\n";

		fileout += "# Enable Trailers as vehicles that can be delivered\n";
		fileout += "EnableTrailers=1\n\n";

		fileout += "# Enable Heli/Planes to be delivered\n";
		fileout += "EnableFlyingVehicles=1\n\n";

		fileout += "# Enable boats to be delivered\n";
		fileout += "EnableWaterVehicles=1\n\n";

		fileout += "# Display Max Amount of vehicles to be collected\n";
		fileout += "DisplayMaxAmount=1\n\n";

		fileout += "# Show help text about missing vehicles list every 30 minutes\n";
		fileout += "ShowHelpText=1\n\n";

		fileout += "# Mod Made by GordoLeal\n";
		fileout += "# Twitch.tv/GordoLeal";
		settingsStream << fileout;
	}

	settingsStream.close();
}

bool Settings::DoesSettingsFileExists()
{
	std::ifstream settingsStream;
	settingsStream.open(SettingsFileName);
	bool exists = false;
	if (settingsStream.is_open())
	{
		exists = true;
	}
	settingsStream.close();
	return exists;
}

bool stringToBool(std::string inS) {
	if (inS.at(0) == '0') {
		return false;
	}
	else if (inS.at(0) == '1') {
		return true;
	}
	else
	{
		return false;
	}
}

void Settings::ReadValuesFromSettingsFile()
{
	if (!DoesSettingsFileExists()) {

		CreateSettingsFile();
		LightHouseAsDelivery = true;
		BeachAsDelivery = false;
		SimeonAsDelivery = true;
		SimeonStateDuringArmenian = true;
		PierAsDelivery = true;
		PierStateDuringDLG = true;
		EnableTrailers = true;
		EnableFlyingVehicles = true;
		EnableWaterVehicles = true;
		DisplayMaxAmount = true;
		ShowHelpText = true;
		AntiParkingLotBeach = true;
		return;
	}

	std::fstream settFileStream;
	settFileStream.open(SettingsFileName, std::ios::out | std::ios::in);
	std::string line;
	while (std::getline(settFileStream, line))
	{
		bool End = false;
		bool readingCmd = true;
		bool foundCmd = false;
		std::string command;
		std::string value;

		for (int x = 0; x < line.size(); x++)
		{
			if (line.at(0) == '#' && line.at(0) == '\n')
			{
				break;
			}

			switch (line.at(x))
			{
			case '\n':
				End = true;
				break;
			case '=':
				readingCmd = false;
				foundCmd = true;
				break;
			default:
			{
				if (readingCmd) {
					command += line.at(x);
				}
				else
				{
					value += line.at(x);
					End = true;
				}
				break;
			}
			}

			if (End)
				break;
		}

		if (foundCmd)
		{
			bool found = false;
			if (!found && command.find("LightHouseAsDelivery") == 0)
			{
				LightHouseAsDelivery = stringToBool(value);
				found = true;
			}
			if (!found && command.find("BeachAsDelivery") == 0)
			{
				BeachAsDelivery = stringToBool(value);
				found = true;
			}
			if (!found && command.find("SimeonAsDelivery") == 0)
			{
				SimeonAsDelivery = stringToBool(value);
				found = true;
			}
			if (!found && command.find("SimeonStateDuringArmenian") == 0)
			{
				AntiParkingLotBeach = stringToBool(value);
				found = true;
			}
			if (!found && command.find("PierAsDelivery") == 0)
			{
				PierAsDelivery = stringToBool(value);
				found = true;
			}
			if (!found && command.find("EnableTrailers") == 0)
			{
				EnableTrailers = stringToBool(value);
				found = true;
			}
			if (!found && command.find("PierStateDuringDLG") == 0)
			{
				PierStateDuringDLG = stringToBool(value);
				found = true;
			}
			if (!found && command.find("EnableFlyingVehicles") == 0)
			{
				EnableFlyingVehicles = stringToBool(value);
				found = true;
			}
			if (!found && command.find("EnableWaterVehicles") == 0)
			{
				EnableWaterVehicles = stringToBool(value);
				found = true;
			}
			if (!found && command.find("DisplayMaxAmount") == 0)
			{
				DisplayMaxAmount = stringToBool(value);
				found = true;
			}
			if (!found && command.find("ShowHelpText") == 0)
			{
				ShowHelpText = stringToBool(value);
				found = true;
			}
			if (!found && command.find("AntiParkingLotBeach") == 0)
			{
				AntiParkingLotBeach = stringToBool(value);
				found = true;
			}

		}
	}
}


