/*************************************************************
 * Copyright (c) 2015 Marcel Herd
 *
 * Distributed under the MIT License.
 *
 * The full license can be reviewed in the LICENSE file, 
 * distributed with this software.
 *************************************************************/

 /**
 * This file defines the gamemode of SAMP-Race.
 */
 
#include <time>
#include <string>
 
#include <a_samp>
#include <a_mysql>
#include <a_bcrypt>

#include "../modules/util"
#include "../modules/constants"
#include "../modules/log"
#include "../modules/persistence/model/player"
#include "../modules/persistence/model/admin"
#include "../modules/persistence/database"
#include "../modules/authentication"

main()
{
	Log("SAMP-Race loaded.", LOG_LEVEL:INFO);
}

public OnGameModeInit()
{
	SetGameModeText(GAME_MODE);
	DatabaseInit();
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	return 1;
}

public OnGameModeExit()
{
	DatabaseExit();
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

public OnPlayerConnect(playerid)
{
	GetPlayerName(playerid, Name[playerid], sizeof(Name));
	GetPlayerIp(playerid, IP[playerid], sizeof(IP));
	
	new joinMessage[45];
	format(joinMessage, sizeof(joinMessage), "User %s (%s) connected.", Name[playerid], IP[playerid]);
	Log(joinMessage, LOG_LEVEL:INFO);
	
	format(joinMessage, sizeof(joinMessage), "%s connected.", Name[playerid]);
	SendClientMessageToAll(COLOR_RED, joinMessage);
	
	HandlePlayerAuthentication(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	new reasonString[16];
	switch (reason)
	{
		case 0: reasonString = "Timeout";
		case 1: reasonString = "Quit";
		case 2: reasonString = "Kicked";
	}

	new leaveMessage[60];
	format(leaveMessage, sizeof(leaveMessage), "User %s (%s) disconnected. (%s)", Name[playerid], IP[playerid], reasonString);
	Log(leaveMessage, LOG_LEVEL:INFO);
	
	format(leaveMessage, sizeof(leaveMessage), "%s disconnected. (%s)", Name[playerid], reasonString);
	SendClientMessageToAll(COLOR_RED, leaveMessage);
	
	return 1;
}

public OnPlayerSpawn(playerid)
{
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	return 0;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case DIALOG_LOGIN:
		{
			if (!response) return Kick(playerid); // Quit button pressed
			HandlePlayerLogin(playerid, inputtext);
			return 1;
		}
		case DIALOG_REGISTRATION:
		{
			if (!response) return Kick(playerid); // Quit button pressed
			if ((strlen(inputtext) < MIN_PASSWORD_LENGTH) || (strlen(inputtext) > MAX_PASSWORD_LENGTH))
			{
				new dialogMessage[128];
				format(dialogMessage, sizeof(dialogMessage), "{FF0000}ERROR: Password must be between %i and %i characters\n{FFFFFF}Enter a password below to register:", 
					MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
				ShowPlayerDialog(playerid, DIALOG_REGISTRATION, DIALOG_STYLE_INPUT, "Welcome to our server", dialogMessage, "Register", "Quit");
				return 1;
			}
			bcrypt_hash(inputtext, BCRYPT_COST, "HandlePlayerRegistration", "d", playerid);
			return 1;
		}
	}
	
	return 0;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}
