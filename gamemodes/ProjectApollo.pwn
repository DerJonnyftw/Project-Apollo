#pragma dynamic 30000
/*#########################################################################################################################################################################

Script written by: Jonny & Andre
Script started: 05.11.2017

MODES:
0 = Lobby
1 = Deathmatch

LEGEND:
   [ ] = Open
   [T] = Progress
   [F] = Fixed
   [X] = Done

TODO LIST: https://trello.com/b/8E3in4l9/project-apollo
[T] [-] MySQL System
[T] [-] Register / Login System

#########################################################################################################################################################################*/
/************************ 
*        INCLUDES
*************************/ 
#include <a_samp>
#include <a_mysql>
#include <foreach>


/************************ 
*          MYSQL
*************************/ 
#define MYSQL_HOST "127.0.0.1"  
#define MYSQL_USER "server_1918"  
#define MYSQL_DATABASE "server_1918_Apollo"  
#define MYSQL_PASS "rknm1jif80"


/*************************
*        DEFINES
*************************/
#undef MAX_PLAYERS
#define MAX_PLAYERS (10)

/*************** 
     Colors 
****************/
#define COLOR_GREY 0xAFAFAFFF
#define COLOR_GREEN 0x33AA33FF
#define COLOR_RED 0xFF3A3AFF
#define COLOR_DRED 0xAA3333FF
#define COLOR_YELLOW 0xFFFF00FF
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLUE 0x0000BBFF
#define COLOR_LIGHTBLUE 0x33CCFFFF
#define COLOR_ORANGE 0xFF9900FF
#define COLOR_LIME 0x10F441FF
#define COLOR_MAGENTA 0xFF00FFFF
#define COLOR_NAVY 0x000080FF
#define COLOR_AQUA 0xF0F8FFFF
#define COLOR_CRIMSON 0xDC143CFF
#define COLOR_FLBLUE 0x6495EDFF
#define COLOR_BISQUE 0xFFE4C4FF
#define COLOR_BLACK 0x000000FF
#define COLOR_CHARTREUSE 0x7FFF00FF
#define COLOR_BROWN 0XA52A2AFF
#define COLOR_CORAL 0xFF7F50FF
#define COLOR_GOLD 0xB8860BFF
#define COLOR_GREENYELLOW 0xADFF2FFF
#define COLOR_INDIGO 0x4B00B0FF
#define COLOR_IVORY 0xFFFF82FF
#define COLOR_LAWNGREEN 0x7CFC00FF
#define COLOR_SEAGREEN 0x20B2AAFF
#define COLOR_LIMEGREEN 0x32CD32FF
#define COLOR_MIDNIGHTBLUE 0X191970FF
#define COLOR_MAROON 0x800000FF
#define COLOR_OLIVE 0x808000FF
#define COLOR_ORANGERED 0xFF4500FF
#define COLOR_PINK 0xFFC0CBFF
#define COLOR_SEAGREEN2 0x2E8B57FF
#define COLOR_SPRINGGREEN 0x00FF7FFF
#define COLOR_TOMATO 0xFF6347FF
#define COLOR_YELLOWGREEN 0x9ACD32FF
#define COLOR_MEDIUMAQUA 0x83BFBFFF
#define COLOR_MEDIUMMAGENTA 0x8B008BFF
#define COLOR_SERVER 0xA1DB71FF
#define COLOR_LIGHTRED 0xFF6347AA
#define COLOR_BRIGHTRED 0xFF0000AA
#define COLOR_PURPLE 0xB360FDFF
#define COLOR_PURPLE2 0xBF60FFFF
#define COLOR_YELLOW2 0xC2A355FF
#define COLOR_TWITTER 0x1DA2F0FF
#define COLOR_INFO 0x009BFF90
#define COLOR_PM 0xB0A87DFF
#define COLOR_BRONZE 0x8F5737FF
#define COLOR_SILVER 0x9C9C9CFF
#define COLOR_GOLD2 0xB97F0FFF
#define COLOR_TEAM1 0x0073FFFF
#define COLOR_TEAM2 0xFF352BFF
#define COLOR_LIMEGREEN2 0x94D317FF

/*************** 
     Dialogs 
****************/
enum
{
	DIALOG_REGISTER,
	DIALOG_LOGIN
};

/*************************
*       ENUMERATORS
*************************/ 
enum PlayerInfo
{
	p_ID,
	pName[25],
	pPass[64+1],
	pSaltedPass[11],
	pPassFails,

	pScore,

	Cache:Player_Cache,
	bool:LoggedIn
};
new pInfo[MAX_PLAYERS][PlayerInfo];


/*************************
*        VARIABLES
*************************/ 
//MySQL
new MySQL: Database, Corrupt_Check[MAX_PLAYERS];
new DB_Query[4028];

//Server
new mode[MAX_PLAYERS];


/*************************
*        FORWARDS
*************************/
forward OnPlayerDataCheck(playerid, corrupt_check);
forward OnPlayerRegister(playerid);
forward SavePlayerStats(playerid);
forward ResetPlayerStats(playerid);

main()
{
	print("|*************************************|");
	print("|*************************************|");
	print("|*************************************|");
	print("|** Project Apollo by Jonny & Andre **|");
	print("|*************************************|");
	print("|*************************************|");
	print("|*************************************|");
}

public OnGameModeInit()
{
	SetGameModeText("Apollo 0.0.1");

	new MySQLOpt: option_id = mysql_init_options();
	mysql_set_option(option_id, AUTO_RECONNECT, true);
	mysql_log(ALL);
	Database = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DATABASE, option_id);
	if(Database == MYSQL_INVALID_HANDLE || mysql_errno(Database) != 0)
	{
		print("[MySQL] Failed to connect. Shutting down server.");
		SendRconCommand("exit");
		return 1;
	}
    print("[MySQL] Successfully connected. Continuing..");
	mysql_tquery(Database, "CREATE TABLE IF NOT EXISTS `Accounts` (`ID` int(11) NOT NULL AUTO_INCREMENT, `Username` varchar(24) NOT NULL, `Password` char(65) NOT NULL, `Salt` char(11) NOT NULL, `Score` mediumint(7), PRIMARY KEY (`ID`), UNIQUE KEY `Username` (`Username`))");
	
	return 1;
}

public OnGameModeExit()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(pInfo[i][LoggedIn] == false) continue;
		SavePlayerStats(i);
		ResetPlayerStats(i);
	}	
	foreach(new i: Player)
    {
		if(IsPlayerConnected(i))
		{
			OnPlayerDisconnect(i, 1);
		}
	}
	mysql_close(Database);
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
   	//If player is NPC
	if(IsPlayerNPC(playerid)) return 1;
	/*:::::::::::::::::::::::::: SetPlayerMode ::::::::::::::::::::::::::*/
	mode[playerid] = 0;
	SetPVarInt(playerid, "mode", 0);

	pInfo[playerid][pPassFails] = 0;
	GetPlayerName(playerid, pInfo[playerid][pName], MAX_PLAYER_NAME);
	Corrupt_Check[playerid]++;
	mysql_format(Database, DB_Query, sizeof(DB_Query), "SELECT * FROM `Accounts` WHERE `Username` = '%e' LIMIT 1", pInfo[playerid][pName]);
	mysql_tquery(Database, DB_Query, "OnPlayerDataCheck", "ii", playerid, Corrupt_Check[playerid]);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	Corrupt_Check[playerid]++;
	mysql_format(Database, DB_Query, sizeof(DB_Query), "UPDATE `Accounts` SET `Score` = %d WHERE `ID` = %d LIMIT 1", pInfo[playerid][pScore], pInfo[playerid][p_ID]);
	mysql_tquery(Database, DB_Query);
	if(cache_is_valid(pInfo[playerid][Player_Cache]))
	{
		cache_delete(pInfo[playerid][Player_Cache]);
		pInfo[playerid][Player_Cache] = MYSQL_INVALID_CACHE;
	}
	pInfo[playerid][LoggedIn] = false;
	SavePlayerStats(playerid);
	ResetPlayerStats(playerid);
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
	if(pInfo[playerid][LoggedIn] == false) return 0;
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
	switch(dialogid)
	{
		case DIALOG_LOGIN:
		{
			if(!response) return Kick(playerid);
			new SaltedPass[65];
			SHA256_PassHash(inputtext, pInfo[playerid][pSaltedPass], SaltedPass, 65);
			if(strcmp(SaltedPass, pInfo[playerid][pPass]) == 0)
			{
				cache_set_active(pInfo[playerid][Player_Cache]);
            	cache_get_value_int(0, "ID", pInfo[playerid][p_ID]);
            	cache_get_value_int(0, "Score", pInfo[playerid][pScore]);
        		SetPlayerScore(playerid, pInfo[playerid][pScore]);
        		cache_delete(pInfo[playerid][Player_Cache]);
				pInfo[playerid][Player_Cache] = MYSQL_INVALID_CACHE;
				pInfo[playerid][LoggedIn] = true;
				SendClientMessage(playerid, COLOR_GREEN, "[SYSTEM] You have successfully logged into your account!");
				SetSpawnInfo(playerid, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				SpawnPlayer(playerid);
			}
			else
			{
			    new String[247];
				pInfo[playerid][pPassFails]++;
				// Add a message to admins here, later.
				if (pInfo[playerid][pPassFails] == 5)
				{
					format(String, sizeof(String), "[ADMIN] %s has been kicked by Apollo Crews(ID: -1). (Reason: Failed to login.)", pInfo[playerid][pName]);
					SendClientMessageToAll(COLOR_RED, String);
					Kick(playerid);
				}
				else
				{
					format(String, sizeof(String), "{FF0000}Wrong password, try again. (%d/5)\n\n{FFFFFF}Welcome back to {A1DB71}Apollo{FFFFFF}, {A1DB71}%s{FFFFFF}.\nThis account was found in our database.\nIf this is your account, please type in your password below to login.", pInfo[playerid][pPassFails], pInfo[playerid][pName]);
					ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "{FFFFFF}Welcome back to Apollo {A1DB71}[Logging in..]", String, "Login", "Leave");
				}
			}
		}
		case DIALOG_REGISTER:
		{
			if(!response) return Kick(playerid);
			if(strlen(inputtext) < 5 || strlen(inputtext) > 30)
			{
			    new String[254];
		    	format(String, sizeof(String), "{FF0000}Password length should be between 5-30 characters.\n\n{FFFFFF}Welcome to {A1DB71}Apollo{FFFFFF}, {A1DB71}%s{FFFFFF}.\nThis account was not found in our database.\nPlease type in your password below to register this account.", pInfo[playerid][pName]);
				ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "{FFFFFF}Welcome to Apollo {A1DB71}[Registering..]", String, "Register", "Leave");
			}
			else
			{
				for (new i = 0; i < 10; i++)
                {
                    pInfo[playerid][pSaltedPass][i] = random(79) + 47;
	    		}
	    		pInfo[playerid][pSaltedPass][10] = 0;
		    	SHA256_PassHash(inputtext, pInfo[playerid][pSaltedPass], pInfo[playerid][pPass], 65);
				mysql_format(Database, DB_Query, sizeof(DB_Query), "INSERT INTO `Accounts` (`Username`, `Password`, `Salt`) VALUES ('%e', '%s', '%e')", pInfo[playerid][pName], pInfo[playerid][pPass], pInfo[playerid][pSaltedPass]);
		     	mysql_tquery(Database, DB_Query, "OnPlayerRegister", "d", playerid);
		     }
		}
	}
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}
/*************************
*        FUNCTIONS
*************************/


/*************************
*        CALLBACKS
*************************/
/*:::::::::::::::::::::::::: Saves / Loades Accounts ::::::::::::::::::::::::::*/
public OnPlayerDataCheck(playerid, corrupt_check)
{
	if (corrupt_check != Corrupt_Check[playerid]) return Kick(playerid);
	new String[202];
	if(cache_num_rows() > 0)
	{
		cache_get_value(0, "Password", pInfo[playerid][pPass], 65);
		cache_get_value(0, "Salt", pInfo[playerid][pSaltedPass], 11);
		pInfo[playerid][Player_Cache] = cache_save();
		mode[playerid] = 0;
		SetPVarInt(playerid, "mode", 0);		
		format(String, sizeof(String), "{FFFFFF}Welcome back to {A1DB71}Apollo{FFFFFF}, {A1DB71}%s{FFFFFF}.\nThis account was found in our database.\nIf this is your account, please type in your password below to login.", pInfo[playerid][pName]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "{FFFFFF}Welcome back to Apollo {A1DB71}[Logging in..]", String, "Login", "Leave");
	}
	else
	{
		format(String, sizeof(String), "{FFFFFF}Welcome to {A1DB71}Apollo{FFFFFF}, {A1DB71}%s{FFFFFF}.\nThis account was not found in our database.\nPlease type in your password below to register this account.", pInfo[playerid][pName]);
		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "{FFFFFF}Welcome to Apollo {A1DB71}[Registering..]", String, "Register", "Leave");
	}
	return 1;
}

public OnPlayerRegister(playerid)
{
	new string[86];
	mode[playerid] = 0;
	SetPVarInt(playerid, "mode", 0);
	pInfo[playerid][p_ID] = cache_insert_id();
	SendClientMessage(playerid, COLOR_GREEN, "[SYSTEM] You have successfully registered, welcome aboard!"); // Change to a tutorial in the future
	format(string, sizeof(string), "[SYSTEM] %s has just registered. Total accounts registered: %d.", pInfo[playerid][pName], pInfo[playerid][p_ID]); // Make the total accounts search better in the future.
	SendClientMessageToAll(COLOR_GREEN, string);
	SetSpawnInfo(playerid, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
    pInfo[playerid][LoggedIn] = true;
    return 1;
}

public SavePlayerStats(playerid)
{
	printf("SavePlayer for %d.", playerid);
	printf("Loggedin: %d", pInfo[playerid][LoggedIn]);
	pInfo[playerid][LoggedIn]++;
	if(!pInfo[playerid][LoggedIn]) return 1;
	printf("Saving...");
	mysql_format(Database, DB_Query, sizeof(DB_Query), "UPDATE Accounts SET Score = '%i' WHERE ID ='%d'",
	pInfo[playerid][pScore], pInfo[playerid][p_ID]);
	printf("query: %s", DB_Query);
	mysql_pquery(Database, DB_Query);		
	printf("Done.");	
	return 1;
}

public ResetPlayerStats(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
	    /*:::::::::::::::::::::::::: Player Initialized ::::::::::::::::::::::::::*/
		pInfo[playerid][p_ID] = 0;
		pInfo[playerid][LoggedIn] = false;
		pInfo[playerid][pScore] = 0;
		/*:::::::::::::::::::::::::: Server Initialized ::::::::::::::::::::::::::*/
		mode[playerid] = 0;			
	}
	return 1;
}

/*************************
*        COMMANDS
*************************/