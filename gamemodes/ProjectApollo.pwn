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
[X] [06.11.2017] MySQL System
[X] [06.11.2017] Register / Login System
[T] [-] Lobby
[X] [06.11.2017] IRC & PM System
[X] [06.11.2017] Punishable Commands
[X] [06.11.2017] Created TextDraw Include
[T] [06.11.2017] Clan system

#########################################################################################################################################################################*/
/************************ 
*        INCLUDES
*************************/ 
#include <a_samp>
#include <a_mysql>
#include <sscanf2>
#include <ocmd>
#include <streamer>
#include <dini>
#include <filemanager>
#include <banfix>
#include <xml>
#include <foreach>
#include <Desk>
#include <crashdetect>
//#include <mapload>
#include <audio>
#include <serverTD>
#include <YSF>
//Gamemodes
#include "../gamemodes/DMMode.pwn"


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
#define MAX_CLAN   100

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
	DIALOG_LOGIN,
	DIALOG_BAN
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
	pMoney,
	pSkin,
	pAdmin,
	pWarns,
	pMute,
	pClan[64],
	pClanRank,
	pClanRights,	
	pIRC,

	Cache:Player_Cache,
	bool:LoggedIn
};
new pInfo[MAX_PLAYERS][PlayerInfo];

enum ClanInfo {
	c_ID,
	cName[64],
	cLeader,
	cPos,
	cScore,
	cRank1[64],
	cRank2[64],
	cRank3[64],
	cRank4[64]
};
new cInfo[MAX_CLAN][ClanInfo];


/*************************
*        VARIABLES
*************************/ 
/* =====> [ MySQL ] <===== */
new MySQL: Database, Corrupt_Check[MAX_PLAYERS];
new DB_Query[4028];

/* =====> [ Server ] <===== */
new mode[MAX_PLAYERS];
new togmode[2] = 0;
new labeltext[600];
new blockpm[MAX_PLAYERS];

/* =====> [ Race DM ] <===== */
new Text3D:DM_Label;

/* =====> [ PlayerColor ] <===== */
new PlayerColors[200] =
{
	0xFF8C13FF, 0xC715FFFF, 0x20B2AAFF, 0xDC143CFF, 0x6495EDFF, 0xf0e68cFF, 0x778899FF, 0xFF1493FF, 0xF4A460FF,
	0xEE82EEFF, 0xFFD720FF, 0x8b4513FF, 0x4949A0FF, 0x148b8bFF, 0x14ff7fFF, 0x556b2fFF, 0x0FD9FAFF, 0x10DC29FF,
	0x534081FF, 0x0495CDFF, 0xEF6CE8FF, 0xBD34DAFF, 0x247C1BFF, 0x0C8E5DFF, 0x635B03FF, 0xCB7ED3FF, 0x65ADEBFF,
	0x5C1ACCFF, 0xF2F853FF, 0x11F891FF, 0x7B39AAFF, 0x53EB10FF, 0x54137DFF, 0x275222FF, 0xF09F5BFF, 0x3D0A4FFF,
	0x22F767FF, 0xD63034FF, 0x9A6980FF, 0xDFB935FF, 0x3793FAFF, 0x90239DFF, 0xE9AB2FFF, 0xAF2FF3FF, 0x057F94FF,
	0xB98519FF, 0x388EEAFF, 0x028151FF, 0xA55043FF, 0x0DE018FF, 0x93AB1CFF, 0x95BAF0FF, 0x369976FF, 0x18F71FFF,
	0x4B8987FF, 0x491B9EFF, 0x829DC7FF, 0xBCE635FF, 0xCEA6DFFF, 0x20D4ADFF, 0x2D74FDFF, 0x3C1C0DFF, 0x12D6D4FF,
	0x48C000FF, 0x2A51E2FF, 0xE3AC12FF, 0xFC42A8FF, 0x2FC827FF, 0x1A30BFFF, 0xB740C2FF, 0x42ACF5FF, 0x2FD9DEFF,
	0xFAFB71FF, 0x05D1CDFF, 0xC471BDFF, 0x94436EFF, 0xC1F7ECFF, 0xCE79EEFF, 0xBD1EF2FF, 0x93B7E4FF, 0x3214AAFF,
	0x184D3BFF, 0xAE4B99FF, 0x7E49D7FF, 0x4C436EFF, 0xFA24CCFF, 0xCE76BEFF, 0xA04E0AFF, 0x9F945CFF, 0xDCDE3DFF,
	0x10C9C5FF, 0x70524DFF, 0x0BE472FF, 0x8A2CD7FF, 0x6152C2FF, 0xCF72A9FF, 0xE59338FF, 0xEEDC2DFF, 0xD8C762FF,
	0xD8C762FF, 0xFF8C13FF, 0xC715FFFF, 0x20B2AAFF, 0xDC143CFF, 0x6495EDFF, 0xf0e68cFF, 0x778899FF, 0xFF1493FF,
	0xF4A460FF, 0xEE82EEFF, 0xFFD720FF, 0x8b4513FF, 0x4949A0FF, 0x148b8bFF, 0x14ff7fFF, 0x556b2fFF, 0x0FD9FAFF,
	0x10DC29FF, 0x534081FF, 0x0495CDFF, 0xEF6CE8FF, 0xBD34DAFF, 0x247C1BFF, 0x0C8E5DFF, 0x635B03FF, 0xCB7ED3FF,
	0x65ADEBFF, 0x5C1ACCFF, 0xF2F853FF, 0x11F891FF, 0x7B39AAFF, 0x53EB10FF, 0x54137DFF, 0x275222FF, 0xF09F5BFF,
	0x3D0A4FFF, 0x22F767FF, 0xD63034FF, 0x9A6980FF, 0xDFB935FF, 0x3793FAFF, 0x90239DFF, 0xE9AB2FFF, 0xAF2FF3FF,
	0x057F94FF, 0xB98519FF, 0x388EEAFF, 0x028151FF, 0xA55043FF, 0x0DE018FF, 0x93AB1CFF, 0x95BAF0FF, 0x369976FF,
	0x18F71FFF, 0x4B8987FF, 0x491B9EFF, 0x829DC7FF, 0xBCE635FF, 0xCEA6DFFF, 0x20D4ADFF, 0x2D74FDFF, 0x3C1C0DFF,
	0x12D6D4FF, 0x48C000FF, 0x2A51E2FF, 0xE3AC12FF, 0xFC42A8FF, 0x2FC827FF, 0x1A30BFFF, 0xB740C2FF, 0x42ACF5FF,
	0x2FD9DEFF, 0xFAFB71FF, 0x05D1CDFF, 0xC471BDFF, 0x94436EFF, 0xC1F7ECFF, 0xCE79EEFF, 0xBD1EF2FF, 0x93B7E4FF,
	0x3214AAFF, 0x184D3BFF, 0xAE4B99FF, 0x7E49D7FF, 0x4C436EFF, 0xFA24CCFF, 0xCE76BEFF, 0xA04E0AFF, 0x9F945CFF,
	0xDCDE3DFF, 0x10C9C5FF, 0x70524DFF, 0x0BE472FF, 0x8A2CD7FF, 0x6152C2FF, 0xCF72A9FF, 0xE59338FF, 0xEEDC2DFF,
	0xD8C762FF, 0xD8C762FF
};


/*************************
*        FORWARDS
*************************/
forward OnPlayerDataCheck(playerid, corrupt_check);
forward OnPlayerRegister(playerid);
forward SavePlayerStats(playerid);
forward ResetPlayerStats(playerid);
forward BanPlayerFromServer(playerid, pID, const reason[], ipadress[]);
forward IsPlayerBanned(playerid);
forward CheckPlayerBanIP(playerid);
forward CheckPlayerBanSerial(playerid);
forward Unban(playerid, unban_name[]);
forward Unmute();
forward LoadClan();
forward SaveClan(id);
forward CreateClan(id);

/*************************
*         NATIVES
*************************/
native gpci(playerid, serial[], len);

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
/*##############################################################################

MySQL Connections

##############################################################################*/	
	/*:::::::::::::::::::::::::: Account Connection ::::::::::::::::::::::::::*/
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
	/*:::::::::::::::::::::::::: Clan Connection ::::::::::::::::::::::::::*/
	mysql_format(Database, DB_Query, sizeof(DB_Query), "SELECT * FROM Clandata");
	mysql_pquery(Database, DB_Query, "LoadClan", "");	    
	//mysql_tquery(Database, "CREATE TABLE IF NOT EXISTS `Accounts` (`ID` int(11) NOT NULL AUTO_INCREMENT, `Username` varchar(24) NOT NULL, `Password` char(65) NOT NULL, `Salt` char(11) NOT NULL, `Score` mediumint(7), PRIMARY KEY (`ID`), UNIQUE KEY `Username` (`Username`))");
/*##############################################################################

3D Text Label's

##############################################################################*/	
	/*:::::::::::::::::::::::::: Modes ::::::::::::::::::::::::::*/
	format(labeltext, sizeof(labeltext), "{A1DB71}>> Race DM <<\n{FFFFFF}%i/50 players\n Press {A1DB71}'Z / Y' {FFFFFF}to join this Gamemode.", CountModePlayer(1));
	DM_Label = CreateDynamic3DTextLabel(labeltext, COLOR_WHITE, -2654.8694, 1397.3739, 906.4647, 10.0);
/*##############################################################################

Actors

##############################################################################*/
	CreateActor(217, -2654.8694, 1397.3739, 906.4647, 3.0255); //Race DM
/*##############################################################################

TextDraws

##############################################################################*/
	CreateServerMoneyLabel();
	CreateServerAliveLabel();
	CreateServerMoneyLabel();
	CreateServerFooterLabel();
	CreateServerLoadingLabel();
	CreateServerTopTimeLabel();
	CreateServerClanWarLabel();
	CreateServerDeathListLabel();	
	/*:::::::::::::::::::::::::: Server Function ::::::::::::::::::::::::::*/
	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	UsePlayerPedAnims();
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/	
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
	for(new i = 0; i < sizeof(cInfo); i++)
	{
		if(!cInfo[i][c_ID]) continue;
		printf("%i", i);
		SaveClan(i);
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
	/*:::::::::::::::::::::::::: CheckData ::::::::::::::::::::::::::*/
	pInfo[playerid][pPassFails] = 0;
	GetPlayerName(playerid, pInfo[playerid][pName], MAX_PLAYER_NAME);
	Corrupt_Check[playerid]++;
	mysql_format(Database, DB_Query, sizeof(DB_Query), "SELECT * FROM `Accounts` WHERE `Username` = '%e' LIMIT 1", pInfo[playerid][pName]);
	mysql_tquery(Database, DB_Query, "OnPlayerDataCheck", "ii", playerid, Corrupt_Check[playerid]);
	/*:::::::::::::::::::::::::: SetMode + Color ::::::::::::::::::::::::::*/
	mode[playerid] = 0;
	SetPVarInt(playerid, "mode", 0);
	SetPlayerColor(playerid, PlayerColors[playerid]);
	/*:::::::::::::::::::::::::: TextDraws ::::::::::::::::::::::::::*/
	CreatePlayerMoneyLabel(playerid);
	CreatePlayerSpectatorLabel(playerid);
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
	/*:::::::::::::::::::::::::: Banned ::::::::::::::::::::::::::*/
	mysql_format(Database, DB_Query, sizeof(DB_Query), "SELECT * FROM Bandata WHERE Name = '%s'", pInfo[playerid][pName]);
	mysql_pquery(Database, DB_Query, "IsPlayerBanned", "i", playerid);	
	//SetSkin
	SetPlayerSkin(playerid, pInfo[playerid][pSkin]);
	//Lobby Spawn
	if(mode[playerid] == 0)
	{
		SetPlayerPos(playerid, -2639.0715, 1406.4830, 906.4609);
		SetPlayerFacingAngle(playerid, 89.6960);
		SetCameraBehindPlayer(playerid);
		SetPlayerInterior(playerid, 3);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerScore(playerid, 1738);
	}	
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
	new string[250];
	if(pInfo[playerid][pMute] > 0)
	{
		SendClientMessage(playerid, COLOR_RED, "You are muted!");
	}
	else
	{
		if(mode[playerid] == 0)//Lobby
		{
			format(string, sizeof(string), "[%s] %s [%i]: {FFFFFF}%s", GetPlayerModeName(playerid), pInfo[playerid][pName], playerid, text);
			SendModeMessage(0, GetPlayerColor(playerid), string);
		}
	}	
	return 0;
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
	new string[128];
	if(IsPlayerInRangeOfPoint(playerid, 5.0, -2654.8694, 1397.3739, 906.4647))
	{
		if(newkeys & KEY_YES)
		{
			if(mode[playerid] > 0) return true;

			if(CountModePlayer(1) == 50)return SendClientMessage(playerid, COLOR_RED, "[ERROR] The mode is currently full!");
			if(togmode[0] == 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] This mode is currently locked!");	

			SetPlayerTime(playerid, GetPVarInt(playerid, "TimeDM_hours"), GetPVarInt(playerid, "TimeDM_minutes"));
			SetPlayerWeather(playerid, GetPVarInt(playerid, "WeatherDM"));

			SendClientMessage(playerid, COLOR_INFO, "");
            SendClientMessage(playerid, COLOR_INFO, "");
            SendClientMessage(playerid, COLOR_INFO, "INFO: {FFFFFF}Welcome to Race DM.");
            SendClientMessage(playerid, COLOR_INFO, "INFO: {FFFFFF}Type /lobby to get back to the Lobby.");
            SendClientMessage(playerid, COLOR_INFO, "INFO: {FFFFFF}The objective of Race DM is to reach the Hunter at the end of each Map and fight the other players.");
            SendClientMessage(playerid, COLOR_INFO, "INFO: {FFFFFF}If you need further help type /cmds or /ask");
            SendClientMessage(playerid, COLOR_INFO, "TIP: {FFFFFF}The best fps for Race DM is 50 - 60. Use (/fpslimit) to set your fpslimit.");
            SendClientMessage(playerid, COLOR_INFO, "");
            SendClientMessage(playerid, COLOR_INFO, "");
			/*:::::::::::::::::::::::::: Load TextDraws ::::::::::::::::::::::::::*/
			for(new i = 0; i < sizeof (Alive_TD); i++) TextDrawShowForPlayer(playerid, Alive_TD[i]);
			for(new i = 0; i < sizeof (FOOTER_TD); i++) TextDrawShowForPlayer(playerid, FOOTER_TD[i]);

			if(CountModePlayer(1) == 0)
			{
				mode[playerid] = 1;
				SetPVarInt(playerid, "mode", 1);
				SetPlayerInterior(playerid, 0);
				//SetPlayerScore(playerid, pInfo[playerid][pDMScore]);
				format(string, sizeof(string), "[JOIN] {%06x}%s {A1DB71}has joined the Gamemode - Race DM!", GetPlayerColor(playerid) >>> 8, pInfo[playerid][pName]);
 				SendModeMessage(1, COLOR_SERVER, string);						
 				//LoadNewMap(1);
 				UpdateDM();		
			}	
			else if(CountModePlayer(1) > 0)
			{
				mode[playerid] = 1;
				SetPVarInt(playerid, "mode", 1);
				SetPlayerInterior(playerid, 0);
				//SetPlayerScore(playerid, pInfo[playerid][pDMScore]);
				format(string, sizeof(string), "[JOIN] {%06x}%s {A1DB71}has joined the Gamemode - Race DM!", GetPlayerColor(playerid) >>> 8, pInfo[playerid][pName]);
 				SendModeMessage(1, COLOR_SERVER, string);				
				for (new i = 0; i < MAX_PLAYERS; i++)
				{
					//if(!IsPlayerConnected(i) || mode[i] != 1 || pInfo[i][pAlive] != 1) continue;
					//StopSpectate(playerid);
					//StartSpectate(playerid, i);
				}						
				UpdateDM();
			}			
		}
	}	
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
			new string[128];
			SHA256_PassHash(inputtext, pInfo[playerid][pSaltedPass], SaltedPass, 65);
			if(strcmp(SaltedPass, pInfo[playerid][pPass]) == 0)
			{
				/*:::::::::::::::::::::::::: Login Sccessful ::::::::::::::::::::::::::*/
				cache_set_active(pInfo[playerid][Player_Cache]);
            	cache_get_value_int(0, "ID", pInfo[playerid][p_ID]);
            	cache_get_value_int(0, "Score", pInfo[playerid][pScore]);
        		SetPlayerScore(playerid, pInfo[playerid][pScore]);
		 		cache_get_value_int(0, "Money", pInfo[playerid][pMoney]);
		 		SetPlayerMoney(playerid, pInfo[playerid][pMoney]); 
		 		cache_get_value_int(0, "Skin", pInfo[playerid][pSkin]);
		 		cache_get_value_int(0, "Admin", pInfo[playerid][pAdmin]);
		 		cache_get_value_int(0, "Warns", pInfo[playerid][pWarns]);
		 		cache_get_value_int(0, "Mute", pInfo[playerid][pMute]);
		 		cache_get_value(0, "Clan", pInfo[playerid][pClan], 64);
		 		cache_get_value_int(0, "ClanRank", pInfo[playerid][pClanRank]);
		 		cache_get_value_int(0, "ClanRights", pInfo[playerid][pClanRights]);		 		
		 		cache_get_value_int(0, "IRC", pInfo[playerid][pIRC]);       		
        		cache_delete(pInfo[playerid][Player_Cache]);
				pInfo[playerid][Player_Cache] = MYSQL_INVALID_CACHE;
				pInfo[playerid][LoggedIn] = true;
				/*:::::::::::::::::::::::::: TextDraws ::::::::::::::::::::::::::*/
				for (new i = 0; i < sizeof (MoneyLabel_TD); i++) TextDrawShowForPlayer(playerid, MoneyLabel_TD[i]);
				for (new i = 0; i < 1; i++) PlayerTextDrawShow(playerid, MoneyLabel_PTD[playerid][i]);					
				/*:::::::::::::::::::::::::: Spawn + Mode ::::::::::::::::::::::::::*/
				mode[playerid] = 0;
				SetPVarInt(playerid, "mode", 0);
				if(pInfo[playerid][pAdmin] == 0)
				{
					SendClientMessage(playerid, COLOR_GREEN, "[SYSTEM] You have successfully logged into your account!");
				}
				else if(pInfo[playerid][pAdmin] > 1)
				{
					format(string, sizeof(string), "[SYSTEM] You have successfully logged in as %s (Adminlevel: %s | %i)", pInfo[playerid][pName], GetPlayerAdminName(playerid), pInfo[playerid][pAdmin]);
					SendClientMessage(playerid, COLOR_GREEN, string);
				}				
				SpawnPlayer(playerid);
			}
			else
			{
			    new String[247];
				pInfo[playerid][pPassFails]++;
				// Add a message to admins here, later.
				if (pInfo[playerid][pPassFails] == 5)
				{
					format(String, sizeof(String), "[AdmCmd] %s has been kicked by Apollo Crews(ID: -1). (Reason: Failed to login.)", pInfo[playerid][pName]);
					SendClientMessageToAll(COLOR_RED, String);
					Kick(playerid);
				}
				else
				{
					format(String, sizeof(String), "{FF3A3A}Wrong password, try again. (%d/5)\n\n{FFFFFF}Welcome back to {A1DB71}Apollo{FFFFFF}, {A1DB71}%s{FFFFFF}.\nThis account was found in our database.\nIf this is your account, please type in your password below to login.", pInfo[playerid][pPassFails], pInfo[playerid][pName]);
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
		    	format(String, sizeof(String), "{FF3A3A}Password length should be between 5-30 characters.\n\n{FFFFFF}Welcome to {A1DB71}Apollo{FFFFFF}, {A1DB71}%s{FFFFFF}.\nThis account was not found in our database.\nPlease type in your password below to register this account.", pInfo[playerid][pName]);
				ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "{FFFFFF}Welcome to Apollo {A1DB71}[Registering..]", String, "Register", "Leave");
			}
			else
			{
				new ipadress[16];
				GetPlayerIp(playerid, ipadress, sizeof(ipadress));
				for (new i = 0; i < 10; i++)
                {
                    pInfo[playerid][pSaltedPass][i] = random(79) + 47;
	    		}
	    		pInfo[playerid][pSaltedPass][10] = 0;
		    	SHA256_PassHash(inputtext, pInfo[playerid][pSaltedPass], pInfo[playerid][pPass], 65);
				mysql_format(Database, DB_Query, sizeof(DB_Query), "INSERT INTO `Accounts` (`Username`, `Password`, `Salt`, `IP`) VALUES ('%e', '%s', '%e', '%e')", pInfo[playerid][pName], pInfo[playerid][pPass], pInfo[playerid][pSaltedPass], ipadress);
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
GetPlayerModeName(playerid)
{
	new modename[12];
	switch(mode[playerid])
	{
		case 0: modename = "Lobby";
		case 1: modename = "DM";
	}
	return modename;
}

GetServerModeName(modeID)
{
	new modename[20];
	switch(modeID)
	{
		case 1: modename = "Race DM";
	}
	return modename;
}

SendModeMessage(modeID, color, const message[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i) && mode[i] == modeID)
		{
			SendClientMessage(i, color, message);
		}
	}
	return 1;
}

SendIRCMessage(ircID, const message[])
{
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
	    if (IsPlayerConnected(i) && pInfo[i][pIRC] == ircID)
	    {
	        SendClientMessage(i, 0xA4FFFFFF, message);
	    }
	}
	return 1;
}

SendAdminMessage(color, const message[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if (IsPlayerConnected(i) && pInfo[i][pAdmin] >= 1)
		{
			SendClientMessage(i, color, message);
		}
	}
	return 1;
}

SetPlayerMoney(playerid, money)
{
	new string[30];
	pInfo[playerid][pMoney] = money;
	format(string, sizeof(string), "%s", NiceMoney(pInfo[playerid][pMoney]));
	PlayerTextDrawSetString(playerid, MoneyLabel_PTD[playerid][0], string);
	return true;
}

NiceMoney(money)
{
	new bmess[15];
	format(bmess, 15, "%d", money);
	if(money > 0)
	{
		for(new l=strlen(bmess)-3; l>0; l-=3)
		{
			if(l>0)
			{
				strins(bmess, ".", l);
			}
		}
	}
	else
	{
		for(new z=strlen(bmess)-3; z>1; z-=3)
		{
			if(z>1)
			{
				strins(bmess, ".", z);
			}
		}
	}
	return bmess;
}

CountModePlayer(modeID)
{
	new count = 0;
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i) || mode[i] != modeID)continue;
		count ++;
	}
	return count;
}

GetPlayerAdminName(playerid)
{
	new adminname[60];
	switch(pInfo[playerid][pAdmin])
	{
		case 0: adminname = "Player";
		case 1: adminname = "Trial Administrator";
		case 2: adminname = "Moderator";
		case 3: adminname = "Administrator";
		case 4: adminname = "Map Manager";
		case 5: adminname = "Head Admin";
		case 6: adminname = "Community Owner";
		default: adminname = "ERROR";
	}
	return adminname;
}

UpdateDM()
{
	DestroyDynamic3DTextLabel(DM_Label);
	if(CountModePlayer(1) == 0)
	{
		format(labeltext, sizeof(labeltext), "{A1DB71}>> Race DM <<\n{FFFFFF}%i/50 players\n Press {A1DB71}'Z / Y' {FFFFFF}to join this Gamemode.", CountModePlayer(1));
		DM_Label = CreateDynamic3DTextLabel(labeltext, COLOR_WHITE, -2654.8694, 1397.3739, 906.4647, 10.0);	
	}
	else if(CountModePlayer(1) > 0)
	{
		format(labeltext, sizeof(labeltext), "{A1DB71}>> Race DM <<\n{FFFFFF}%i/50 players\n Press {A1DB71}'Z / Y' {FFFFFF}to join this Gamemode.", CountModePlayer(1));
		DM_Label = CreateDynamic3DTextLabel(labeltext, COLOR_WHITE, -2654.8694, 1397.3739, 906.4647, 10.0);	
	}
	if(togmode[0] == 1)
	{
		format(labeltext, sizeof(labeltext), "\n\n\n{FF3A3A}[LOCKED]", CountModePlayer(1));
		DM_Label = CreateDynamic3DTextLabel(labeltext, COLOR_WHITE, -2654.8694, 1397.3739, 906.4647, 10.0);			
	}		
	return 1;
}

getAlphaRGBA(rgbacolor) return (rgbacolor & 0xFF);

stock torgba(rgbacolor, &r, &g, &b, &a)
{
	r = (rgbacolor >>> 24),
	g = ((rgbacolor >>> 16) & 0xFF),
	b = ((rgbacolor >>> 8) & 0xFF),
	a = getAlphaRGBA(rgbacolor);
}

stock toargb(argbcolor, &a, &r, &g, &b)
{
	torgba(argbcolor, a, r, g, b);
}

stock torgbacolor(r, g, b, a) return ((r << 24) | (g << 16) | (b << 8) | a);
stock toargbcolor(a, r, g, b) return ((a << 24) | (r << 16) | (g << 8) | b);

stock rgbatoargb(rgbacolor)
{
	new r, g, b, a;

	torgba(rgbacolor, r, g, b, a);

	return toargbcolor(a, r, g, b);
}

stock argbtorgba(argbcolor)
{
	new a, r, g, b;

	torgba(argbcolor, a, r, g, b);

	return torgbacolor(r, g, b, a);
}

stock RGBAToHex(r, g, b, a) //By Betamaster
{
	return (r<<24 | g<<16 | b<<8 | a);
}

stock static ConvertStringToHex(string[],size = sizeof(string))
{
	new stringR[10];

	strmid(stringR, string, 7, strlen(string));

	strdel(string, 7, strlen(string));
	strdel(string, 0, 1);

	strins(string, "0x", 0, size);
	strins(string, stringR, 2, size);

	new i, cur = 1, res = 0;

	for (i = strlen(string); i > 0; i--) {
    	if (string[i-1] < 58) res = res + cur * (string[i-1] - 48); else res = res + cur * (string[i-1] - 65 + 10);
	 	cur = cur * 16;
	}
 	return res;
}

stock RGBAToARGB( rgba )
    return rgba >>> 8 | rgba << 24;

stock get_rgba(color, &r, &g, &b, &a) {
	r = (color & 0xFF000000) >>> 24;
	g = (color & 0x00FF0000) >>> 16;
	b = (color & 0x0000FF00) >>> 8;
	a = (color & 0x000000FF);
}

stock make_color(r, g, b, a) {
	new color = 0;
	color |= (r & 0xFF) << 24;
	color |= (g & 0xFF) << 16;
	color |= (b & 0xFF) << 8;
	color |= (a & 0xFF);
	return color;
}
/*************************
*        CALLBACKS
*************************/
public BanPlayerFromServer(playerid, pID, const reason[], ipadress[])
{
	new string[128], string2[550], string1[550], mainstring[1000], serial[200], admin[MAX_PLAYER_NAME];
	gpci(playerid, serial, sizeof(serial));
	new year, month, day;
	new hours, minutes, seconds;

	getdate(year, month, day);
	gettime(hours, minutes, seconds);

	mysql_format(Database, DB_Query, sizeof(DB_Query), "INSERT INTO Bandata (Name, IP, Serial, Reason, Time, Date, Admin) VALUES ('%s', '%s', '%s', '%s', '%02d:%02d:%02d', '%02d.%02d.%02d', '%s')", pInfo[playerid][pName], ipadress, serial, reason, hours, minutes, seconds, year, month, day, pInfo[pID][pName]);
	printf("query: %s", DB_Query);
	mysql_pquery(Database, DB_Query);

	format(string, sizeof(string), "[AdmCmd] %s has been banned by %s, (Reason: %s)", pInfo[playerid][pName], admin, reason);
	SendClientMessageToAll(COLOR_RED, string);
	format(string1, sizeof(string1), 
	"{FFFFFF}[ {FF3A3A}Ban Information {FFFFFF}]\n{FFFFFF}Account: {FF3A3A}%s\n{FFFFFF}Admin who issued the ban: {FF3A3A}%s\n{FFFFFF}Reason: {FF3A3A}%s\n{FFFFFF}Time and Date: {FF3A3A}%02d:%02d:%02d - %02d.%02d.%02d\n{FFFFFF}IP-Address: {FF3A3A}%s\n{FFFFFF}If you were banned wrongly, please take a Screenshot of this Dialog\nand write an Ban appeal in the Forums!\n\n{FF3A3A}Project Apollo Team!",
	pInfo[playerid][pName], pInfo[pID][pName], reason, hours, minutes, seconds, day, month, year, ipadress);
	strcat(mainstring, string1);
	strdel(string1, 0, sizeof(string1));
	format(string2, sizeof(string2), "{FF3A3A}You've been banned from this Server!");
	ShowPlayerDialog(playerid, DIALOG_BAN, DIALOG_STYLE_MSGBOX, string2, mainstring, "Close", "");
	ResetPlayerStats(playerid);
	Kick(playerid);	
	return 1;
}

public IsPlayerBanned(playerid)
{
	new rows;
	cache_get_row_count(rows);
	if(rows > 0)
	{
		new string2[550], string1[550], mainstring[1000], Reason[60], Admin[MAX_PLAYER_NAME], Date[19], Time[19], IPAdress[16];
		cache_get_value_name(0, "IP", IPAdress);
		cache_get_value_name(0, "Reason", Reason);
		cache_get_value_name(0, "Time", Time);
		cache_get_value_name(0, "Date", Date);
		cache_get_value_name(0, "Admin", Admin);

		format(string1, sizeof(string1),
		"{FFFFFF}[ {FF3A3A}Ban Information {FFFFFF}]\n{FFFFFF}Account: {FF3A3A}%s\n{FFFFFF}Admin who issued the ban: {FF3A3A}%s\n{FFFFFF}Reason: {FF3A3A}%s\n{FFFFFF}Time and Date: {FF3A3A}%s | %s\n{FFFFFF}IP-Address: {FF3A3A}%s\n{FFFFFF}If you were banned wrongly, please take a Screenshot of this Dialog\nand write an Ban appeal in the Forums!\n\n{FF3A3A}Project Apollo Team!",
		pInfo[playerid][pName], Admin, Reason, Time, Date, IPAdress);
		strcat(mainstring,string1);
		strdel(string1,0,sizeof(string1));
		format(string2, sizeof(string2), "{FF3A3A}You are banned from this Server!");
		ShowPlayerDialog(playerid, DIALOG_BAN, DIALOG_STYLE_MSGBOX, string2, mainstring, "Close", "");
		format(string2, sizeof(string2), "[AdmCmd] %s has been kicked, (Reason: Banned)", pInfo[playerid][pName]);
		SendAdminMessage(COLOR_RED, string2);
		Kick(playerid);
		return 1;
	}
	new ipadress[24];
	GetPlayerIp(playerid, ipadress, sizeof(ipadress));
	mysql_format(Database, DB_Query, sizeof(DB_Query), "SELECT IP FROM Bandata WHERE IP = '%s'", ipadress);
	mysql_pquery(Database, DB_Query, "CheckPlayerBanIP", "i", playerid);
	return 1;
}

public CheckPlayerBanIP(playerid)
{
	new rows;
	cache_get_row_count(rows);
	if(rows > 0)
	{
		new string2[550], string1[550], mainstring[1000], IPAdress[16];
		cache_get_value_name(0, "IP", IPAdress);
		format(string1, sizeof(string1),
		"{FFFFFF}[ {FF3A3A}Ban Information {FFFFFF}]\n{FFFFFF}Your IP-Address is currently banned\nIP-Address: {FF3A3A}%s\n{FFFFFF}If you were banned wrongly, please take a Screenshot of this Dialog\nand write an Ban appeal in the Forums!\n\n{FF3A3A}Project Apollo Team!",
		IPAdress);
		strcat(mainstring,string1);
		strdel(string1,0,sizeof(string1));
		format(string2, sizeof(string2), "{FF3A3A}You are banned from this Server!");
		ShowPlayerDialog(playerid, DIALOG_BAN, DIALOG_STYLE_MSGBOX, string2, mainstring, "Close", "");
		format(string2, sizeof(string2), "[AdmCmd] %s has been kicked, (Reason: IP-Address Banned)", pInfo[playerid][pName]);
		SendAdminMessage(COLOR_RED, string2);
		Kick(playerid);
		return 1;	
	}
	new serial[200];
	gpci(playerid, serial, sizeof(serial));
	mysql_format(Database, DB_Query, sizeof(DB_Query), "SELECT Serial FROM Bandata WHERE Serial = '%s'", serial);
	mysql_pquery(Database, DB_Query, "CheckPlayerBanSerial", "i", playerid);
	return 1;
}

public CheckPlayerBanSerial(playerid)
{
	new rows;
	cache_get_row_count(rows);
	if(rows > 0)
	{
		new string2[550], string1[550], mainstring[1000], Serial[200];
		cache_get_value_name(0, "Serial", Serial);
		format(string1, sizeof(string1),
		"{FFFFFF}[ {FF3A3A}Ban Information {FFFFFF}]\n{FFFFFF}Your Serial is currently banned\nSerial: {FF3A3A}%s\n{FFFFFF}If you were banned wrongly, please take a Screenshot of this Dialog\nand write an Ban appeal in the Forums!\n\n{FF3A3A}Project Apollo Team!",
		Serial);
		strcat(mainstring,string1);
		strdel(string1,0,sizeof(string1));
		format(string2, sizeof(string2), "{FF3A3A}You are banned from this Server!");
		ShowPlayerDialog(playerid, DIALOG_BAN, DIALOG_STYLE_MSGBOX, string2, mainstring, "Close", "");
		format(string2, sizeof(string2), "[AdmCmd] %s has been kicked, (Reason: Serial Banned)", pInfo[playerid][pName]);
		SendAdminMessage(COLOR_RED, string2);
		Kick(playerid);
		return 1;	
	}
	return 1;
}

public Unban(playerid, unban_name[])
{
	new rows, string[128];
	cache_get_row_count(rows);
	if(rows == 1)
	{
		mysql_format(Database, DB_Query, sizeof(DB_Query), "DELETE FROM Bandata WHERE Name = '%s'", unban_name);
		mysql_pquery(Database, DB_Query);
	    
	    format(string, sizeof(string), "[AdmCmd] You've successfully unbanned %s!", unban_name);
	    SendClientMessage(playerid, COLOR_RED, string);		
	}
	else if(rows == 0)
	{
	    format(string, sizeof(string), "Playername \"%s\" was not found!", unban_name);
	    SendClientMessage(playerid, COLOR_RED, string);
	}	
	return 1;
}

public Unmute()
{
	new string[128];
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i) || pInfo[i][pMute] == 0)continue;
		pInfo[i][pMute] --;
		SavePlayerStats(i);
		if(pInfo[i][pMute] == 0)
		{
			format(string, sizeof(string), "[AdmCmd] %s has been unmuted by the System!", pInfo[i][pName]);
			SendClientMessageToAll(COLOR_RED, string);
			return SendClientMessage(i, COLOR_RED, "You've been unmuted!");
		}

	}
	return 1;
}

/* =====> [ Saves / Loades Accounts ] <===== */
public OnPlayerDataCheck(playerid, corrupt_check)
{
	if (corrupt_check != Corrupt_Check[playerid]) return Kick(playerid);
	new String[202];
	if(cache_num_rows() > 0)
	{
		cache_get_value(0, "Password", pInfo[playerid][pPass], 65);
		cache_get_value(0, "Salt", pInfo[playerid][pSaltedPass], 11);
		pInfo[playerid][Player_Cache] = cache_save();		
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
	/*:::::::::::::::::::::::::: TextDraws ::::::::::::::::::::::::::*/
	for (new i = 0; i < sizeof (MoneyLabel_TD); i++) TextDrawShowForPlayer(playerid, MoneyLabel_TD[i]);
	for (new i = 0; i < 1; i++) PlayerTextDrawShow(playerid, MoneyLabel_PTD[playerid][i]);		
	SendClientMessage(playerid, COLOR_GREEN, "[SYSTEM] You have successfully registered, welcome aboard!"); // Change to a tutorial in the future
	format(string, sizeof(string), "[SYSTEM] %s has just registered. Total accounts registered: %d.", pInfo[playerid][pName], pInfo[playerid][p_ID]); // Make the total accounts search better in the future.
	SendClientMessageToAll(COLOR_GREEN, string);
    SetSpawnInfo(playerid, 0, 0, -2639.0715, 1406.4830, 906.4609, 89.6960, 0, 0, 0, 0, 0, 0);
    SetPlayerInterior(playerid, 3);
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
	mysql_format(Database, DB_Query, sizeof(DB_Query), "UPDATE Accounts SET Score = '%i', Money = '%i', Skin = '%i', Admin = '%i', Warns = '%i', Mute = '%i', Clan = '%s', ClanRank = '%i', ClanRights = '%i', IRC = '%i' WHERE ID ='%d'",
	pInfo[playerid][pScore], pInfo[playerid][pMoney], pInfo[playerid][pSkin], pInfo[playerid][pAdmin], pInfo[playerid][pWarns], pInfo[playerid][pMute], pInfo[playerid][pClan], pInfo[playerid][pClanRank], pInfo[playerid][pClanRights], pInfo[playerid][pIRC], pInfo[playerid][p_ID]);
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
		pInfo[playerid][pMoney] = 0;
		pInfo[playerid][pSkin] = 0;
		pInfo[playerid][pAdmin] = 0;
		pInfo[playerid][pWarns] = 0;
		pInfo[playerid][pMute] = 0;
		format(pInfo[playerid][pClan], 64, "");
		pInfo[playerid][pClanRank] = 0;
		pInfo[playerid][pClanRights] = 0;			
		/*:::::::::::::::::::::::::: Server Initialized ::::::::::::::::::::::::::*/
		mode[playerid] = 0;			
	}
	return 1;
}
/* =====> [ Saves / Loades Clans ] <===== */
public SaveClan(id)
{
	printf("Saving...");
	mysql_format(Database, DB_Query, sizeof(DB_Query), "UPDATE Clandata SET ClanName = '%s', ClanLeader = '%i', ClanPosition = '%i', ClanScore = '%i', ClanRank1 = '%s', ClanRank2 = '%s', ClanRank3 = '%s', ClanRank4 = '%s' WHERE ID ='%d'",
	cInfo[id][cName], cInfo[id][cLeader], cInfo[id][cPos], cInfo[id][cScore], cInfo[id][cRank1], cInfo[id][cRank2], cInfo[id][cRank3], cInfo[id][cRank4], cInfo[id][c_ID]);
	printf("query: %s", DB_Query);
	mysql_pquery(Database, DB_Query);	
	printf("Done.");	
	return 1;
}

public LoadClan()
{
	new rows;
	cache_get_row_count(rows);
	if(!rows)return 1;
	for(new i=0; i<rows; i++)
	{
		new id = GetFreeClanID();
 		cache_get_value_name_int(0, "ID", cInfo[id][c_ID]);
 		cache_get_value(0, "ClanName", cInfo[id][cName], 64);
 		cache_get_value_name_int(0, "ClanLeader", cInfo[id][cLeader]);
 		cache_get_value_name_int(0, "ClanPosition", cInfo[id][cPos]);
 		cache_get_value_name_int(0, "ClanScore", cInfo[id][cScore]);
 		cache_get_value(0, "ClanRank1", cInfo[id][cRank1], 64);
 		cache_get_value(0, "ClanRank2", cInfo[id][cRank2], 64);
 		cache_get_value(0, "ClanRank3", cInfo[id][cRank3], 64);
 		cache_get_value(0, "ClanRank4", cInfo[id][cRank4], 64);
 		
 		printf("<-| [CLAN] Clanname: %s | ClanID: %i", cInfo[id][cName], cInfo[id][c_ID]);
	}	
	return 1;
}

public CreateClan(id)
{
	cInfo[id][c_ID] = cache_insert_id();
	return 1;
}

GetFreeClanID()
{
	for (new i = 0; i < sizeof(cInfo); i++)
	{
	    if (cInfo[i][c_ID] == 0) return i;
	}
	return 0;
}

GetPlayerClanRangName(playerid)
{
	new rangname[64];
	for (new i = 0; i < sizeof(cInfo); i++)
	{
	    if (!cInfo[i][c_ID]) continue;
	    if (!strcmp(cInfo[i][cName], pInfo[playerid][pClan], true))
	    {
	    	switch (pInfo[playerid][pClanRank])
	    	{
	    		case 1: strmid(rangname, cInfo[i][cRank1], 0, sizeof(rangname), sizeof(rangname));
	    		case 2: strmid(rangname, cInfo[i][cRank2], 0, sizeof(rangname), sizeof(rangname));
	    		case 3: strmid(rangname, cInfo[i][cRank3], 0, sizeof(rangname), sizeof(rangname));
	    		case 4: strmid(rangname, cInfo[i][cRank4], 0, sizeof(rangname), sizeof(rangname));
	    		default: rangname = "ERROR";
	    	}
	    }
 	}
 	return rangname;
}

/*************************
*        COMMANDS
*************************/
/*:::::::::::::::::::::::::: Admin Commands ::::::::::::::::::::::::::*/
ocmd:setadmin(playerid, params[])
{
	new pID, string[128], adminLevel, currentLevel;
	if(pInfo[playerid][pAdmin] < 5)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "ui", pID, adminLevel))return SendClientMessage(playerid, COLOR_RED, "[Command] /setadmin [Playername/ID] [Adminlevel]");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	if(pInfo[pID][pAdmin] == adminLevel)return SendClientMessage(playerid, COLOR_RED,"[ERROR] The player already has this Adminlevel!");
	if(adminLevel < 0 || adminLevel > 6)return SendClientMessage(playerid, COLOR_RED, "[ERROR] Invalid level! (0 - 6)!");
	if(pInfo[pID][pAdmin] >= pInfo[pID][pAdmin])return SendClientMessage(playerid, COLOR_RED, "[ERROR] You cannot perform this command on a higher or equal leveled admin!");
	currentLevel = pInfo[pID][pAdmin];
	pInfo[pID][pAdmin] = adminLevel;
	if(currentLevel == 0)
	{
		format(string, sizeof(string), "Your admin level has been set to (%s | %i). Welcome to the Team!", GetPlayerAdminName(pID), adminLevel);
		SendClientMessage(pID, COLOR_ORANGE, string);
		format(string, sizeof(string), "[AdmCmd] %s's admin level has been set to (%s | %i)", pInfo[pID][pName], GetPlayerAdminName(pID), adminLevel);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	}
	else
	{
		format(string, sizeof(string), "%s has %s you to admin level (%s | %i).", pInfo[pID][pName], ((currentLevel < pInfo[pID][pAdmin]) ? ("promoted") : ("demoted")), GetPlayerAdminName(pID), adminLevel);
		SendClientMessage(pID, COLOR_RED, string);
		format(string, sizeof(string), "[AdmCmd] You've %s %s to admin level (%s | %i)", ((currentLevel < pInfo[pID][pAdmin]) ? ("promoted") : ("demoted")), pInfo[pID][pName], GetPlayerAdminName(pID), adminLevel);
		SendClientMessage(playerid, COLOR_RED, string);		
	}
	SavePlayerStats(pID);
	return 1;
}

ocmd@2:a,achat(playerid,params[])
{
	new string[128];
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "s", string))return SendClientMessage(playerid, COLOR_RED, "[Command] /achat [Text]");
	format(string, sizeof(string), "[%s] [%s (%i)] | %s [%i]: %s", GetPlayerModeName(playerid), GetPlayerAdminName(playerid), pInfo[playerid][pAdmin], pInfo[playerid][pName], playerid, string);
	SendAdminMessage(COLOR_ORANGERED, string);
	return 1;
}

ocmd:eng(playerid, params[])
{
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	SendClientMessageToAll(COLOR_RED, "[ANNOUNCEMENT] {FFFFFF}English only in mainchat. Use /pm or /setirc [IRC] -> /i to chat in diffrent languages.");
	return 1;
}

ocmd@2:ann,announce(playerid, params[])
{
	new string[500];
	if(pInfo[playerid][pAdmin] < 3)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "s", string))return SendClientMessage(playerid, COLOR_RED, "[Command] /announce [Text]");
	format(string, sizeof(string), "[ANNOUNCEMENT] {FFFFFF}%s", string);
	SendClientMessageToAll(COLOR_RED, string);
	return 1;
}

ocmd:kick(playerid, params[])
{
	new pID, string[128], reason[128];
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "us", pID, reason))return SendClientMessage(playerid, COLOR_RED, "[Command] /kick [Playername/ID] [Reason]");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	format(string, sizeof(string), "[AdmCmd] %s has been kicked by %s´. (Reason: %s)", pInfo[pID][pName], pInfo[playerid][pName], reason);
	SendClientMessageToAll(COLOR_RED, string);
	Kick(pID);
	return 1;
}

ocmd:ban(playerid, params[])
{
	new pID, reason[128];
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "us", pID, reason))return SendClientMessage(playerid, COLOR_RED, "[Command] /ban [Playername/ID] [Reason]");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	new ipadress[24];
	GetPlayerIp(pID, ipadress, sizeof(ipadress));
	BanPlayerFromServer(pID, playerid, reason, ipadress);	
	return 1;
}

ocmd:unban(playerid, params[])
{
	new name[MAX_PLAYER_NAME];
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "s", name))return SendClientMessage(playerid, COLOR_RED, "[Command] /unban [Playername]");
	mysql_format(Database, DB_Query, sizeof(DB_Query), "SELECT * FROM Bandata WHERE Name = '%s'", name);
	mysql_pquery(Database, DB_Query, "Unban", "is", playerid, name);
	return 1;
}

ocmd:mute(playerid, params[])
{
	new pID, string[128], reason[128], minutes;
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "uis", pID, minutes, reason))return SendClientMessage(playerid, COLOR_RED, "[Command] /mute [Playername/ID] [Minutes] [Reason]");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	if(pInfo[pID][pMute] > 0)return SendClientMessage(playerid, COLOR_RED, "[ERROR] Player is already muted!");
	pInfo[pID][pMute] = minutes;
	format(string, sizeof(string), "[AdmCmd] %s has been muted for %i minutes by %s. (Reason: %s)", pInfo[pID][pName], minutes, pInfo[playerid][pName], reason);
	SendClientMessageToAll(COLOR_RED, string);
	SavePlayerStats(pID);
	return 1;
}

ocmd:unmute(playerid, params[])
{
	new pID, string[128];
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "uis", pID))return SendClientMessage(playerid, COLOR_RED, "[Command] /unmute [Playername/ID]");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	if(pInfo[pID][pMute] == 0)return SendClientMessage(playerid, COLOR_RED, "[ERROR] Player is not muted!");
	pInfo[pID][pMute] = 0;
	format(string, sizeof(string), "[AdmCmd] %s has been unmuted by %s", pInfo[pID][pName], pInfo[playerid][pName]);
	SendClientMessageToAll(COLOR_RED, string);
	SavePlayerStats(pID);		
	return 1;
}

ocmd:warn(playerid, params[])
{
	new pID, string[128], reason[128], ipadress[24];
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "us", pID, reason))return SendClientMessage(playerid, COLOR_RED, "[Command] /warn [Playername/ID] [Reason]");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	pInfo[pID][pWarns] ++;
	SavePlayerStats(pID);
	format(string, sizeof(string), "[AdmCmd] %s has been warned %i/5 by %s, (Reason: %s)", pInfo[pID][pName], pInfo[pID][pWarns], pInfo[playerid][pName], reason);
	SendClientMessageToAll(COLOR_RED, string);
	if(pInfo[pID][pWarns] >= 5)
	{
		format(string, sizeof(string), "[AdmCmd] %s has been banned by the Warnsystem, (Reason: %s)", pInfo[pID][pName], reason);
		SendClientMessageToAll(COLOR_RED, string);	
		GetPlayerIp(playerid, ipadress, sizeof(ipadress));
		format(reason, sizeof(reason), "5 Warnings");
		BanPlayerFromServer(pID, -1, reason, ipadress);
	}
	return 1;
}

ocmd:delwarn(playerid, params[])
{
	new pID, string[128];
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "u", pID))return SendClientMessage(playerid, COLOR_RED, "[Command] /delwarn [Playername/ID]");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	if(pInfo[pID][pWarns] <= 0)return SendClientMessage(playerid, COLOR_RED, "[ERROR] Player has no warns!");
	pInfo[pID][pWarns] --;
	format(string, sizeof(string), "%s has has removed one warn, (%i/5)", pInfo[playerid][pName], pInfo[pID][pWarns]);
	SendClientMessage(playerid, COLOR_RED, string);
	format(string, sizeof(string), "[AdmCmd] You've removed one warn from %s, (%i/5)", pInfo[pID][pName], pInfo[pID][pWarns]);
	SendClientMessage(playerid, COLOR_RED, string);	
	SavePlayerStats(pID);
	return 1;
}

ocmd:warnmute(playerid, params[])
{
	new pID, string[128], reason[128], ipadress[24], minutes;
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "uis", pID, minutes, reason))return SendClientMessage(playerid, COLOR_RED, "[Command] /warnmute [Playername/ID] [Minutes] [Reason]");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	pInfo[pID][pWarns] ++;
	format(string, sizeof(string), "[AdmCmd] %s has been warned %i/5 by %s, (Reason: %s)", pInfo[pID][pName], pInfo[pID][pWarns], pInfo[playerid][pName], reason);
	SendClientMessageToAll(COLOR_RED, string);
	if(pInfo[pID][pWarns] >= 5)
	{
		format(string, sizeof(string), "[AdmCmd] %s has been banned by the Warnsystem, (Reason: %s)", pInfo[pID][pName], reason);
		SendClientMessageToAll(COLOR_RED, string);	
		GetPlayerIp(playerid, ipadress, sizeof(ipadress));
		format(reason, sizeof(reason), "5 Warnings");
		BanPlayerFromServer(pID, -1, reason, ipadress);		
	}
	else if(pInfo[pID][pWarns] < 5)
	{
		pInfo[pID][pMute] = minutes;
		format(string, sizeof(string), "[AdmCmd] %s has been muted for %i minutes by %s, (Reason: %s)", pInfo[pID][pName], minutes, pInfo[playerid][pName], reason);
		SendClientMessageToAll(COLOR_RED, string);		
	}
	SavePlayerStats(pID);
	return 1;
}

ocmd:togmode(playerid, params[])
{
	new modeID, string[128];
	if(pInfo[playerid][pAdmin] < 3)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "i", modeID))
	{
		SendClientMessage(playerid, COLOR_RED, "1 - Race DM");
		return SendClientMessage(playerid, COLOR_RED, "[Command] /togmode [ModeID]");
	}
	if(modeID < 1 || modeID > 3)return SendClientMessage(playerid, COLOR_RED, "[ERROR] Invalid Gamemode!");
    if(togmode[modeID-1] == 1) 
    {
		togmode[modeID-1] = 0;
	    format(string, sizeof(string), "[ANNOUNCEMENT] {FFFFFF}An admin has unlocked the Gamemode %s", GetServerModeName(modeID));
	    SendClientMessageToAll(COLOR_RED, string);
	    UpdateDM();
	} 
	else if(togmode[modeID-1] == 0) 
	{
	    togmode[modeID-1] = 1;
	    format(string, sizeof(string), "[ANNOUNCEMENT] {FFFFFF}An admin has locked the Gamemode %s", GetServerModeName(modeID));
	    SendClientMessageToAll(COLOR_RED, string);
	    UpdateDM();	    
	}
	return 1;
}

ocmd:forcelobby(playerid, params[])
{
	new pID, string[128], reason[128];
	if(pInfo[playerid][pAdmin] < 1) return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	if(sscanf(params, "us", pID, reason))return SendClientMessage(playerid, COLOR_RED, "[Command] /forcelobby [Playername/ID] [Reason]");
	if(mode[pID] == 0)return SendClientMessage(playerid, COLOR_RED, "[ERROR] Player is already in the Lobby!");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	format(string, sizeof(string), "[AdmCmd] %s has been forced to the Lobby. (Reason: %s)", pInfo[pID][pName], reason);
	SendClientMessageToAll(COLOR_RED, string);
	mode[pID] = 0;
	SetPVarInt(playerid, "mode", 0);
	SetPlayerPos(pID, -2639.0715, 1406.4830, 906.4609);
	SetPlayerFacingAngle(pID, 89.6960);
	SetCameraBehindPlayer(pID);
	SetPlayerInterior(pID, 3);
	SetPlayerVirtualWorld(pID, 0);
	SetPlayerScore(playerid, 1738);
	for (new i = 0; i < sizeof (FOOTER_TD); i++) TextDrawHideForPlayer(pID, FOOTER_TD[i]);
	for (new i = 0; i < sizeof (Alive_TD); i++) TextDrawHideForPlayer(pID, Alive_TD[i]);
	UpdateDM();
	return 1;
}

ocmd:clearchat(playerid, params[])
{
    if(pInfo[playerid][pAdmin] < 1) return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	new string[128];
	for (new i = 0; i < 100; i++)
	{
	    SendClientMessageToAll(-1, "");
	}
	format(string, sizeof(string), "[AdmCmd] %s has cleared the chat.", pInfo[playerid][pName]);
	SendClientMessageToAll(COLOR_RED, string);
	return 1;
}

ocmd:ip(playerid, params[])
{
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	new ip[16], string[128], pID;
	if(sscanf(params, "u", pID))return SendClientMessage(playerid, COLOR_RED, "[Command] /ip [Playername/ID]");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	GetPlayerIp(playerid, ip, sizeof(ip));
	SendClientMessage(playerid, COLOR_RED, "|____________________ IP Adress Check ____________________|");
	format(string, sizeof(string), "Username: {FFFFFF}%s", pInfo[pID][pName]);
	SendClientMessage(playerid, COLOR_RED, string);	
	format(string, sizeof(string), "IP: {FFFFFF}%s", ip);
	SendClientMessage(playerid, COLOR_RED, string);
	SendClientMessage(playerid, COLOR_RED, "|________________________________________________________|");
	return 1;
}

ocmd:serial(playerid, params[])
{
	if(pInfo[playerid][pAdmin] < 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	new serial[30], string[128], pID;
	if(sscanf(params, "u", pID))return SendClientMessage(playerid, COLOR_RED, "[Command] /serial [Playername/ID]");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	gpci(pID, serial, sizeof(serial));
	SendClientMessage(playerid, COLOR_RED, "|____________________ Serial Check ____________________|");
	format(string, sizeof(string), "Username: {FFFFFF}%s", pInfo[pID][pName]);
	SendClientMessage(playerid, COLOR_RED, string);	
	format(string, sizeof(string), "Serial: {FFFFFF}%s", serial);
	SendClientMessage(playerid, COLOR_RED, string);
	SendClientMessage(playerid, COLOR_RED, "|____________________________________________________|");
	return 1;
}

ocmd:setmoney(playerid, params[])
{
	if(pInfo[playerid][pAdmin] < 3) return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	new pID, money, string[128];
	if(sscanf(params, "ui", pID, money)) return SendClientMessage(playerid, COLOR_RED, "[Command] /setmoney [Playername/ID] [Amount]");
	if(!IsPlayerConnected(pID)) return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	pInfo[pID][pMoney] += money;
	SetPlayerMoney(pID, pInfo[pID][pMoney]);
	format(string, sizeof(string), "An admin has added +$%s to your Account.", NiceMoney(money));
	SendClientMessage(pID, COLOR_ORANGE, string);
	format(string, sizeof(string), "[AdmCmd] You have added +$%s to %s's Account.", NiceMoney(money), pInfo[pID][pName]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	SavePlayerStats(pID);
	return 1;
}

ocmd:createclan(playerid, params[])
{
	new year, month, day, hour, minute, second;
	getdate(year, month, day);
	gettime(hour, minute, second);
	new pID, clanName[64], string[128];
	new id = GetFreeClanID();
	if(sscanf(params, "us", pID, clanName))return SendClientMessage(playerid, COLOR_RED, "[Command] /createclan [Playername/ID] [ClanName]");
	if(!IsPlayerConnected(pID)) return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	if(strlen(clanName) < 1)return SendClientMessage(playerid, COLOR_RED, "[Command] /createclan [ClanName]");
	strmid(cInfo[id][cName], clanName, 0, sizeof(clanName), sizeof(clanName));
	strmid(pInfo[pID][pClan], cInfo[id][cName], 0, 64, 64);
	pInfo[pID][pClanRank] = 4;
	pInfo[pID][pClanRights] = 1;
	cInfo[id][cLeader] = pInfo[pID][p_ID];
    cInfo[id][cPos] = -1;
    cInfo[id][cScore] = 0;
    strmid(cInfo[id][cRank1], "Member", 0, 64, 64);
	strmid(cInfo[id][cRank2], "Special Member", 0, 64, 64);
	strmid(cInfo[id][cRank3], "CoLeader", 0, 64, 64);
	strmid(cInfo[id][cRank4], "Leader", 0, 64, 64);
	mysql_format(Database, DB_Query, sizeof(DB_Query), "INSERT INTO Clandata (ClanName, ClanLeader, ClanPosition, ClanScore, ClanRank1, ClanRank2, ClanRank3, ClanRank4, CreatedTime, CreatedDate) VALUES ('%s', '%i', '-1', '0', 'Member', 'Special Member', 'CoLeader', 'Leader', '%02d:%02d:%02d', '%02d.%02d.%02d')", clanName, pInfo[pID][p_ID], hour, minute, second, year, month, day);
	printf("query: %s", DB_Query);
	mysql_tquery(Database, DB_Query, "CreateClan", "i", id);  
	format(string, sizeof(string), "[AdmCmd] %s has created a new clan, (Clan Leader: %s | Clan name: %s)", pInfo[playerid][pName], pInfo[pID][pName], clanName);
	SendAdminMessage(COLOR_RED, string);
	SavePlayerStats(pID);	    
	return 1;
}

ocmd:setclanleader(playerid, params[])
{
	if(pInfo[playerid][pAdmin] < 3) return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not an Admin!");
	new clanID, pID, string[128];
	if(sscanf(params, "ui", pID, clanID))return SendClientMessage(playerid, COLOR_RED, "[Command] /setclanleader [Playername/ID] [ClanID]");
	if(!IsPlayerConnected(pID)) return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	if(strlen(pInfo[pID][pClan]) > 0)return SendClientMessage(playerid, COLOR_RED, "[ERROR] Player is already in a clan!");
    for(new i = 0; i < sizeof(cInfo); i++)
    {
        if(!cInfo[i][c_ID] || clanID != cInfo[i][c_ID]) continue;
		format(string, sizeof(string), "Clan | %s gave you the Leaders rights for the clan, (%s).", pInfo[playerid][pName], cInfo[i][cName]);
		SendClientMessage(pID, 0x57D491FF, string);
		format(string, sizeof(string), "[AdmCmd] You gave %s Leader rights for the clan, (%s).", pInfo[pID][pName], cInfo[i][cName]);
		SendClientMessage(playerid, COLOR_RED, string);
		strmid(pInfo[pID][pClan], cInfo[i][cName], 0, 64, 64);
		pInfo[pID][pClanRank] = 4;
		pInfo[pID][pClanRights] = 1;
		SavePlayerStats(pID);
		SaveClan(i);
		return 1;
    }
	return SendClientMessage(playerid, COLOR_RED, "[ERROR] Clan was not Found!");	
}
/*:::::::::::::::::::::::::: User Commands ::::::::::::::::::::::::::*/
ocmd@2:cmds,help(playerid, params[])
{
	SendClientMessage(playerid, COLOR_RED, "|____________________[ Command List ]____________________|");
    SendClientMessage(playerid, COLOR_INFO, "CMD: {FFFFFF}/shop, /nextmap, /lobby, /skin, /blockpm, /pm");
    SendClientMessage(playerid, COLOR_INFO, "CMD: {FFFFFF}/setirc, /i(rc), /g(lobal), /c, /namecolor");
    SendClientMessage(playerid, COLOR_INFO, "CMD: {FFFFFF}/removenamecolor, /searchmap, /stats, /donate");
    SendClientMessage(playerid, COLOR_INFO, "CMD: {FFFFFF}/topclans, /admins, /report, /carcolor");
    SendClientMessage(playerid, COLOR_RED, "|_______________________________________________________|");
    return 1;
}

ocmd:lobby(playerid, params[])
{
	if(mode[playerid] == 0)
	{
		SendClientMessage(playerid, COLOR_RED, "[ERROR] You're already in the Lobby!");
		return 1;
	}
	else if(mode[playerid] == 1)
	{
		//DMAlive --;
		mode[playerid] = 0;
		SetPVarInt(playerid, "mode", 0);
		SetPlayerPos(playerid, -2639.0715, 1406.4830, 906.4609);
		SetPlayerFacingAngle(playerid, 89.6960);
		SetCameraBehindPlayer(playerid);
		SetPlayerInterior(playerid, 3);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerScore(playerid, 1738);
		for(new i = 0; i < sizeof (DMLoad_TD); i++) TextDrawHideForPlayer(playerid, DMLoad_TD[i]);
		for(new i = 0; i < sizeof (FOOTER_TD); i++) TextDrawHideForPlayer(playerid, FOOTER_TD[i]);
		for(new i = 0; i < sizeof (Alive_TD); i++) TextDrawHideForPlayer(playerid, Alive_TD[i]);
		for(new i = 0; i < sizeof (TopTime_TD); i++) TextDrawHideForPlayer(playerid, TopTime_TD[i]);
		UpdateDM();	
		return 1;
	}
	return 1;
}

ocmd:skin(playerid, params[])
{
	new skinID, string[128];
	if(sscanf(params, "i", skinID))return SendClientMessage(playerid, COLOR_RED, "[Command] /skin [SkinID]");
	if(skinID > 311)return SendClientMessage(playerid, COLOR_RED, "[ERROR] Please select a skin between 0 - 311");
	SetPlayerSkin(playerid, skinID);
	pInfo[playerid][pSkin] = skinID;
	SavePlayerStats(playerid);
	format(string, sizeof(string), "Skin has been set to %i", skinID);
	SendClientMessage(playerid, COLOR_ORANGE, string);
	return 1;
}

ocmd:blockpm(playerid, params[])
{
	if(blockpm[playerid] == 0)
	{
		blockpm[playerid] = 1;
		SendClientMessage(playerid, COLOR_ORANGE, "Privat Messages blocked!");
	}
	else if(blockpm[playerid] == 1)
	{
		blockpm[playerid] = 0;
		SendClientMessage(playerid, COLOR_ORANGE, "Privat Messages unblocked!");
	}
	return 1;
}

ocmd:pm(playerid, params[])
{
	new pID, string[128], text[128];
	if(sscanf(params, "us", pID, text))return SendClientMessage(playerid, COLOR_RED, "[Command] /pm [Playername/ID] [Text]");
	if(pID == playerid)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You can't pm your self!");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	if(blockpm[pID] == 1)return SendClientMessage(playerid, COLOR_RED, "[ERROR] This player blocked his Privat Messages!");
	format(string, sizeof(string), "[PM] to %s [%i]: %s", pInfo[pID][pName], pID, text);
	SendClientMessage(playerid, COLOR_PM, string);
	format(string, sizeof(string), "[PM] from %s [%i]: %s", pInfo[playerid][pName], playerid, text);
	SendClientMessage(pID, COLOR_PM, string);	
	return 1;
}

ocmd:setirc(playerid, params[])
{
	new IRC, string[128];
	if(sscanf(params, "i", IRC))return SendClientMessage(playerid, COLOR_RED, "[Command] /setirc [IRC]");
	if(pInfo[playerid][pIRC] == IRC)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're already in this IRC Channel!");
	pInfo[playerid][pIRC] = IRC;
	SavePlayerStats(playerid);
	format(string, sizeof(string), "[IRC] %s has joined the IRC - %i", pInfo[playerid][pName], IRC);
	SendIRCMessage(IRC, string);
	return 1;
}

ocmd@2:i,irc(playerid, params[])
{
	new text[128], string[128];
	if(sscanf(params, "s", text))return SendClientMessage(playerid, COLOR_RED, "[Command] /irc [Text]");
	if(pInfo[playerid][pIRC] == 0)return SendClientMessage(playerid, COLOR_RED, "[ERROR] You're not in the IRC!");
	format(string, sizeof(string), "[%s] IRC [%i] | %s [%i]: %s", GetPlayerModeName(playerid), pInfo[playerid][pIRC], pInfo[playerid][pName], playerid, text);
	SendIRCMessage(pInfo[playerid][pIRC], string);
	return 1;
}

ocmd@2:g,global(playerid, params[])
{
	new string[264], text[128];
	if(pInfo[playerid][pMute] > 0)return SendClientMessage(playerid, COLOR_RED, "You are muted!");
	if(sscanf(params, "s", text))return SendClientMessage(playerid, COLOR_RED, "[Command]: /global [Text]");
	format(string, sizeof(string), "{%06x}[G] %s [%i]: {FFFFFF}%s",
	GetPlayerColor(playerid) >>> 8, pInfo[playerid][pName], playerid, text);
	SendClientMessageToAll(GetPlayerColor(playerid), string);
	return 1;
}

ocmd:c(playerid, params[])
{
	if(!strlen(pInfo[playerid][pClan]))return SendClientMessage(playerid, COLOR_RED, "[ERROR] You are not in a clan!");
	new string[128], text[128];
	if (sscanf(params, "s", text))return SendClientMessage(playerid, COLOR_RED, "[Command] /c [Text]");
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(!IsPlayerConnected(i) || strlen(pInfo[playerid][pClan]) < 1) continue;
	    if(strcmp(pInfo[i][pClan], pInfo[playerid][pClan], true) == 0)
	    {
	        format(string, sizeof(string), "[%s] Clan | (%s) %s [%i]: %s",
			GetPlayerModeName(playerid), GetPlayerClanRangName(playerid), pInfo[playerid][pName], playerid, text);
	        SendClientMessage(i, 0x57D491FF, string);
	    }
	}
	return 1;
}

ocmd:report(playerid, params[])
{
	new string[128], reason[128], pID;
	if(sscanf(params, "us", pID, reason))return SendClientMessage(playerid, COLOR_RED, "[Command] /report [Playername/ID] [Reason]");
	if(!IsPlayerConnected(pID))return SendClientMessage(playerid, COLOR_RED, "[ERROR] Wrong ID or the player is not connected!");
	format(string, sizeof(string), "[REPORT] [%s] %s [%i] has reported %s [%i], (Reason: %s)", GetPlayerModeName(playerid), pInfo[playerid][pName], playerid, pInfo[pID][pName], pID, reason);
	SendAdminMessage(COLOR_RED, string);
	format(string, sizeof(string), "[REPORT] You've reported %s [%i], (Reason: %s)", pInfo[pID][pName], pID, reason);
	SendClientMessage(playerid, COLOR_ORANGE, string);
	SendClientMessage(playerid, COLOR_ORANGE, "[REPORT] Thank you for your report! An admin will take care of it shortly!");
	return 1;
}