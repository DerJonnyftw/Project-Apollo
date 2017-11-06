#include <a_samp>

#if !defined _sscanf2_included
    #include <sscanf2>
#endif

#if !defined _streamer_included
    #include <streamer>
#endif

#if !defined _filemanager_included
    #include <filemanager>
#endif

#if !defined _xml_included
	#include <xml>
#endif

#if !defined _foreach_included
	#include <foreach>
#endif

#if !defined _crashdetect_included
	#include <crashdetect>
#endif

#if !defined _audio_included
	#include <audio>
#endif

#if defined MAX_PLAYERS
#undef MAX_PLAYERS
#define MAX_PLAYERS 20
#endif

#define GetDynamicObjectVirtualWorld(%1) \
    Streamer_GetIntData(STREAMER_TYPE_OBJECT, %1, E_STREAMER_WORLD_ID)


#define GetMapName() 			LoadInfo[MapName]
#define GetAuthorName() 		LoadInfo[Author]


enum lData {
	MapName[264],
	Author[128],
	LastMap,
	MaxMaps,
	lTimerID,
}

enum lDataTrain {
	MapName[264],
	Author[128],
	LastMap,
	MaxMaps,
	lTimerID,
}

enum lSpawnData {
	model,
	Float:sx,
	Float:sy,
	Float:sz,
	Float:sr
}

enum lSpawnDataTrain {
	model,
	Float:sx,
	Float:sy,
	Float:sz,
	Float:sr
}

enum pickupData {
	model,
	Float:pickX,
	Float:pickY,
	Float:pickZ,
	p_type,
	p_veh
}

enum pickupDataTrain {
	model,
	Float:pickX,
	Float:pickY,
	Float:pickZ,
	p_type,
	p_veh
}

// Variablen

// Dm Racing 
new LoadInfo[lData],
	sInfo[300][lSpawnData],
	pickInfo[500][pickupData],
	Text3D:textlabelDM[300],
	SphereDM[300],
	tlindexDM = 0,
	sIndexDM = 0,
	vehDM[300],
	vehindexDM = 0,
	worldsDM[664];

// Training mode
new LoadInfoTrain[MAX_PLAYERS][lDataTrain],
	sInfoTrain[MAX_PLAYERS][100][lSpawnDataTrain],
	pickInfoTrain[MAX_PLAYERS][300][pickupDataTrain],
	Text3D:textlabelTrain[MAX_PLAYERS][300],
	SphereTrain[MAX_PLAYERS][300],
	tlindexTrain[MAX_PLAYERS] = 0,
	sIndexTrain[MAX_PLAYERS]  = 0,
	vehTrain[MAX_PLAYERS][100],
	vehindexTrain[MAX_PLAYERS] = 0, 
	maxobjectTrain[MAX_PLAYERS] = 0,
	firstobjTrain[MAX_PLAYERS] = 0;

new dm_object[10000];
new dm_marker[10000];
new dm_object_count = 0;
new dm_marker_count = 0;


static VehicleName[212][20 char] = {
	{!"Landstalker"},{!"Bravura"},{!"Buffalo"},{!"Linerunner"},{!"Perrenial"},{!"Sentinel"},{!"Dumper"},
	{!"Firetruck"},{!"Trashmaster"},{!"Stretch"},{!"Manana"},{!"Infernus"},{!"Voodoo"},{!"Pony"},{!"Mule"},
	{!"Cheetah"},{!"Ambulance"},{!"Leviathan"},{!"Moonbeam"},{!"Esperanto"},{!"Taxi"},{!"Washington"},
	{!"Bobcat"},{!"Mr Whoopee"},{!"BF Injection"},{!"Hunter"},{!"Premier"},{!"Enforcer"},{!"Securicar"},
	{!"Banshee"},{!"Predator"},{!"Bus"},{!"Rhino"},{!"Barracks"},{!"Hotknife"},{!"Trailer 1"},{!"Previon"},
	{!"Coach"},{!"Cabbie"},{!"Stallion"},{!"Rumpo"},{!"RC Bandit"},{!"Romero"},{!"Packer"},{!"Monster"},
	{!"Admiral"},{!"Squalo"},{!"Seasparrow"},{!"Pizzaboy"},{!"Tram"},{!"Trailer 2"},{!"Turismo"},
	{!"Speeder"},{!"Reefer"},{!"Tropic"},{!"Flatbed"},{!"Yankee"},{!"Caddy"},{!"Solair"},{!"Berkley's RC Van"},
	{!"Skimmer"},{!"PCJ-600"},{!"Faggio"},{!"Freeway"},{!"RC Baron"},{!"RC Raider"},{!"Glendale"},{!"Oceanic"},
	{!"Sanchez"},{!"Sparrow"},{!"Patriot"},{!"Quad"},{!"Coastguard"},{!"Dinghy"},{!"Hermes"},{!"Sabre"},
	{!"Rustler"},{!"ZR-350"},{!"Walton"},{!"Regina"},{!"Comet"},{!"BMX"},{!"Burrito"},{!"Camper"},{!"Marquis"},
	{!"Baggage"},{!"Dozer"},{!"Maverick"},{!"News Chopper"},{!"Rancher"},{!"FBI Rancher"},{!"Virgo"},{!"Greenwood"},
	{!"Jetmax"},{!"Hotring"},{!"Sandking"},{!"Blista Compact"},{!"Police Maverick"},{!"Boxville"},{!"Benson"},
	{!"Mesa"},{!"RC Goblin"},{!"Hotring Racer A"},{!"Hotring Racer B"},{!"Bloodring Banger"},{!"Rancher"},
	{!"Super GT"},{!"Elegant"},{!"Journey"},{!"Bike"},{!"Mountain Bike"},{!"Beagle"},{!"Cropdust"},{!"Stunt"},
	{!"Tanker"}, {!"Roadtrain"},{!"Nebula"},{!"Majestic"},{!"Buccaneer"},{!"Shamal"},{!"Hydra"},{!"FCR-900"},
	{!"NRG-500"},{!"HPV1000"},{!"Cement Truck"},{!"Tow Truck"},{!"Fortune"},{!"Cadrona"},{!"FBI Truck"},
	{!"Willard"},{!"Forklift"},{!"Tractor"},{!"Combine"},{!"Feltzer"},{!"Remington"},{!"Slamvan"},
	{!"Blade"},{!"Freight"},{!"Streak"},{!"Vortex"},{!"Vincent"},{!"Bullet"},{!"Clover"},{!"Sadler"},
	{!"Firetruck LA"},{!"Hustler"},{!"Intruder"},{!"Primo"},{!"Cargobob"},{!"Tampa"},{!"Sunrise"},{!"Merit"},
	{!"Utility"},{!"Nevada"},{!"Yosemite"},{!"Windsor"},{!"Monster A"},{!"Monster B"},{!"Uranus"},{!"Jester"},
	{!"Sultan"},{!"Stratum"},{!"Elegy"},{!"Raindance"},{!"RC Tiger"},{!"Flash"},{!"Tahoma"},{!"Savanna"},
	{!"Bandito"},{!"Freight Flat"},{!"Streak Carriage"},{!"Kart"},{!"Mower"},{!"Duneride"},{!"Sweeper"},
	{!"Broadway"},{!"Tornado"},{!"AT-400"},{!"DFT-30"},{!"Huntley"},{!"Stafford"},{!"BF-400"},{!"Newsvan"},
	{!"Tug"},{!"Trailer 3"},{!"Emperor"},{!"Wayfarer"},{!"Euros"},{!"Hotdog"},{!"Club"},{!"Freight Carriage"},
	{!"Trailer 3"},{!"Andromada"},{!"Dodo"},{!"RC Cam"},{!"Launch"},{!"Police Car (LSPD)"},{!"Police Car (SFPD)"},
	{!"Police Car (LVPD)"},{!"Police Ranger"},{!"Picador"},{!"S.W.A.T. Van"},{!"Alpha"},{!"Phoenix"},{!"Glendale"},
	{!"Sadler"},{!"Luggage Trailer A"},{!"Luggage Trailer B"},{!"Stair Trailer"},{!"Boxville"},{!"Farm Plow"},
	{!"Utility Trailer"}
};

// forwards
forward @Countdown(time);
forward OnPlayerFinishRace(playerid);
forward CreateGameModeObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:scale, bool:collisions, interiorID, gamemode_id);
forward CreateGameModeMarker(Float:X, Float:Y, Float:Z, m_type[], m_color[]);

#if !defined _ALS_
    forward public _ALS_();
    _ALS_()<_ALS_:unhooked>{}
    _ALS_()<_ALS_:hooked>{}
    _ALS_()<>{}
#endif

public OnGameModeInit()
{
    state _ALS_:hooked;
	SetObjectsDefaultCameraCol(true);

	// Audio Client
	Audio_SetPack("default_pack", true);

	// Streamer
	Streamer_TickRate(15);
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, 900);
	// Streamer_ToggleErrorCallback(true);

	InitalizeMaps();

	for (new i = 0; i < 89; i++) {
		format(worldsDM, sizeof(worldsDM), "%s, %i", worldsDM, i);
	}

    return H_OnGameModeInit();
}

forward H_OnGameModeInit();
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
public H_OnGameModeInit() <_ALS_:unhooked> return 1;
public H_OnGameModeInit() <> return 1;
#define OnGameModeInit(%0) H_OnGameModeInit(%0)<_ALS_:hooked>

stock LoadRandomMap()
{
	new rand, item[128], type, i = 1, loadstr[300];
	new dir:dHandle = dir_open("./scriptfiles/racemaps/");

	rand = 0 + random(LoadInfo[MaxMaps]);

	while (dir_list(dHandle, item, type) && i != rand)
	{
		if (item[0] == '.') continue;

		format(loadstr, sizeof(loadstr), "/racemaps/%s", item);
		i++;
	}
	
	dir_close(dHandle);
	return LoadMap(loadstr);
}

stock CountObjects()
{
	new index = 0;

	for (new i = 0; i < MAX_OBJECTS; i++) {
		index++;
	}

	return index;
}

stock LoadMap(path[])
{
	if (UnloadMap())
	{
		new loadstr[400], string[128];
		strmid(path, path, strfind(path, "/racemaps/")+10, strfind(path, ".ini"), strfind(path, "ini"));
		format(loadstr, sizeof(loadstr), "/racemaps/%s.ini", path);
		
		if (!fexist(loadstr)) return 0;

		format(LoadInfo[MapName],128,path);

		format(string, sizeof(string), "loadfs rmaps/%s", LoadInfo[MapName]);
		SendRconCommand(string);

		LoadSpawnPoints(loadstr);
	}
	return 1;
}

stock LoadMapTrain(playerid, path[])
{
	if (UnloadMapTrain(playerid))
	{
		new loadstr[400], string[128];
		strmid(path, path, strfind(path, "/TrainMaps/")+11, strfind(path, ".ini"), strfind(path, "ini"));
		SetPVarString(playerid, "MapName", path);
		format(loadstr, sizeof(loadstr), "/TrainMaps/%s.ini", path);
		
		if (!fexist(loadstr)) return 0;

		format(LoadInfoTrain[playerid][MapName], 128, path);

		firstobjTrain[playerid] = CountObjects();
		
		format(string, sizeof(string), "loadfs maps/%s", LoadInfoTrain[playerid][MapName]);
		SendRconCommand(string);

		maxobjectTrain[playerid] = firstobjTrain[playerid] + CountObjects();

		printf("Maximale Training Objetkte: %i", maxobjectTrain[playerid]);

		LoadSpawnPointsTrain(playerid, loadstr);
		return 1;
	}
	return 1;
}

stock LoadSpawnPoints(path[])
{

    if (!fexist(path)) return true;
    
    new File:fhandle = fopen(path, io_read);
    new item[512], i = 0, string[128], modelID[30];
    
    while (fread(fhandle, item))
    {
		if (strfind(item, "Vehicle:", true) != -1) {
			strmid(modelID, item, strfind(item, "Vehicle:")+8, sizeof(item), sizeof(item));
			sInfo[i][model] = strval(modelID);
			format(string, sizeof(string), "Veh%i_X =", i);
			continue;
		}
		else if (strfind(item, string, true) != -1) 
		{
		    if (strfind(item, "_X =", true) != -1)
			{
				if (!sscanf(item, "'_X ='f", sInfo[i][sx])) {
					format(string, sizeof(string), "Veh%i_Y =", i);
				}
			}
			else if (strfind(item, "_Y =", true) != -1)
			{
				if (!sscanf(item, "'_Y ='f", sInfo[i][sy])) {
					format(string, sizeof(string), "Veh%i_Z =", i);
				}
			}
			else if (strfind(item, "_Z =", true) != -1)
			{
				if (!sscanf(item, "'_Z ='f", sInfo[i][sz])) {
					format(string, sizeof(string), "Veh%i_R =", i);
				}
			}
			else if (strfind(item, "_R =", true) != -1)
			{
				if (!sscanf(item, "'_R = 'f", sInfo[i][sr])) {
					i ++;
					format(string, sizeof(string), "Veh%i_X =", i);
				}	
			}
		}
    }
    // for (new id = 1; id < sizeof(sInfo); id++) if (!sInfo[id][mID]) return true;
    fclose(fhandle);

    LoadPickups(path);
	return 1;
}

stock LoadSpawnPointsTrain(playerid, path[])
{
    if (!fexist(path)) return 1;
    
    new File:fhandle = fopen(path, io_read);
    new item[512], i = 1, string[128], modelID[30];
    
    while (fread(fhandle, item))
    {
		if (strfind(item, "Vehicle=", true) != -1) {
			strmid(modelID, item, strfind(item, "Vehicle=")+8, sizeof(item), sizeof(item));
			sInfoTrain[playerid][i][model] = strval(modelID);
			format(string, sizeof(string), "Veh%i_x=", i);
		}
		else if (strfind(item, string, true) != -1) 
		{
		    if (strfind(item, "_x=", true) != -1)
			{
				if (!sscanf(item, "'_x='f", sInfoTrain[playerid][i][sx])) {
					format(string, sizeof(string), "Veh%i_y=", i);
				}
			}
			else if (strfind(item, "_y=", true) != -1)
			{
				if (!sscanf(item, "'_y='f", sInfoTrain[playerid][i][sy])) {
					format(string, sizeof(string), "Veh%i_z=", i);
				}
			}
			else if (strfind(item, "_z=", true) != -1)
			{
				if (!sscanf(item, "'_z='f", sInfoTrain[playerid][i][sz])) {
					format(string, sizeof(string), "Veh%i_a=", i);
				}
			}
			else if (strfind(item, "_a=", true) != -1)
			{
				if (!sscanf(item, "'_a='f", sInfoTrain[playerid][i][sr])) {
					i ++;
					format(string, sizeof(string), "Veh%i_x=", i);
				}	
			}
		}
    }
    // for (new id = 1; id < sizeof(sInfo); id++) if (!sInfo[id][mID]) return true;

    LoadPickupsTrain(playerid, path);
    fclose(fhandle);
	return 1;
}

stock LoadPickups(path[])
{
    if (!fexist(path)) return true;


    new File:fhandle = fopen(path, io_read);
    new item[512], i = 0, string[128];
    // new x[64], y[64], z[64], r[64], type[20];
    new Float:px, Float:py, Float:pz, typeval, vID;

    format(string, sizeof(string), "Pick%i_X", i);

    while (fread(fhandle, item))
    {
	    if (strfind(item, string, true) != -1)
		{
			if (strfind(item, "_X =", true) != -1)
			{
				if (!sscanf(item, "'_X =' f", px)) {
					format(string, sizeof(string), "Pick%i_Y", i);
				}
			}
			else if (strfind(item, "_Y =", true) != -1)
			{
				if (!sscanf(item, "'_Y =' f", py)) {
					format(string, sizeof(string), "Pick%i_Z", i);
				}
			}
			else if (strfind(item, "_Z =", true) != -1)
			{
				if (!sscanf(item, "'_Z =' f", pz)) {
					format(string, sizeof(string), "Pick%i_Type", i);
				}
			}
			else if (strfind(item, "_Type", true) != -1)
			{
				if (!sscanf(item, "'_Type:'i", typeval)) {
					if (typeval != 3) {	
		
						if (typeval == 1) {
							format(string, sizeof(string), "{A1DB71}>> {FFFFFF}Nitro{A1DB71} <<");


							SphereDM[sIndexDM] = CreateDynamicSphereEx(px, py, pz+5, 5.0, {sizeof(worldsDM)}, {-1}, {-1}, 81);
							Streamer_SetIntData(STREAMER_TYPE_AREA, SphereDM[sIndexDM], E_STREAMER_EXTRA_ID, 1);
						}	
						if (typeval == 2) {
							format(string, sizeof(string), "{A1DB71}>> {FFFFFF}Repair{A1DB71} <<");

							SphereDM[sIndexDM] = CreateDynamicSphereEx(px, py, pz+5, 5.0, {sizeof(worldsDM)}, {-1}, {-1}, 81);
							Streamer_SetIntData(STREAMER_TYPE_AREA, SphereDM[sIndexDM], E_STREAMER_EXTRA_ID, 2);
						}
						/*else if (typeval == 6) {
							format(string, sizeof(string), "{C13E3E}[{FFFFFF}Repair & Nitro{C13E3E}]");

							SphereDM[sIndexDM] = CreateDynamicSphereEx(px, py, pz, 5.0, {sizeof(worldsDM)}, {-1}, {-1}, 81);
							Streamer_SetIntData(STREAMER_TYPE_AREA, SphereDM[sIndexDM], E_STREAMER_EXTRA_ID, 3);
							print("Repair und Nitro");
						}*/

						textlabelDM[tlindexDM] = CreateDynamic3DTextLabelEx(string, -1, px, py, pz+5, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);

						pickInfo[i][pickX] = px;
						pickInfo[i][pickY] = py;
						pickInfo[i][pickZ] = pz+5;
						pickInfo[i][p_type] = typeval;
						i++, tlindexDM++, sIndexDM++;
						format(string, sizeof(string), "Pick%i_X", i);
					}
					else if (typeval == 3) {
						format(string, sizeof(string), "Pick%i_name", i);
					}	
				}	
			}
			else if (strfind(item, "_name:", true) != -1)
			{
				if (!sscanf(item, "'_name:' i", vID)) {
					format(string, sizeof(string), "{009BFF}>> {FFFFFF}%s{009BFF} <<", GetVehicleName(vID));

					SphereDM[sIndexDM] = CreateDynamicSphereEx(px, py, pz+5, 5.0, {sizeof(worldsDM)}, {-1}, {-1}, 81);
					Streamer_SetIntData(STREAMER_TYPE_AREA, SphereDM[sIndexDM], E_STREAMER_EXTRA_ID, vID);

					textlabelDM[tlindexDM] = CreateDynamic3DTextLabelEx(string, -1, px, py, pz+5, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);
					pickInfo[i][pickX] = px;
					pickInfo[i][pickY] = py;
					pickInfo[i][pickZ] = pz+5;
					pickInfo[i][p_type] = typeval;
					pickInfo[i][p_veh] = vID;

					i++, tlindexDM++, sIndexDM++;

					format(string, sizeof(string), "Pick%i_X", i);
				}					
			}
		}
    }

    new int[3];

    for (new t = 0; t < i; t++)
    {
    	int [0] = floatround(pickInfo[t][pickX], floatround_round);
    	int [1] = floatround(pickInfo[t+1][pickX], floatround_round);
    	
    	if (t > 0) int [2] = floatround(pickInfo[t-1][pickX], floatround_round);

    	if (t > 0 && int[0] == int[1] && pickInfo[t][p_type] == 2 && pickInfo[t+1][p_type] == 1)
 		{
    		DestroyDynamic3DTextLabel(textlabelDM[t]);
    		DestroyDynamic3DTextLabel(textlabelDM[t+1]);

    		format(string, sizeof(string), "{009BFF}>> {FFFFFF}Nitro & Repair{009BFF} <<");
    		textlabelDM[t] = CreateDynamic3DTextLabelEx(string, -1, pickInfo[t][pickX], pickInfo[t][pickY], pickInfo[t][pickZ], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);
    		continue;
    	}
    	else if (t > 0 && int[0] == int[2] && pickInfo[t][p_type] == 2 && pickInfo[t-1][p_type] == 1)
    	{
        	DestroyDynamic3DTextLabel(textlabelDM[t]);
    		DestroyDynamic3DTextLabel(textlabelDM[t-1]);

    		format(string, sizeof(string), "{009BFF}>> {FFFFFF}Nitro & Repair{009BFF} <<");
    		textlabelDM[t] = CreateDynamic3DTextLabelEx(string, -1, pickInfo[t][pickX], pickInfo[t][pickY], pickInfo[t][pickZ], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);
    		continue;	
    	}
		else if (t > 0 && int[0] == int[1] && pickInfo[t][p_type] == 1 && pickInfo[t+1][p_type] == 2)
 		{
    		DestroyDynamic3DTextLabel(textlabelDM[t]);
    		DestroyDynamic3DTextLabel(textlabelDM[t+1]);

    		format(string, sizeof(string), "{009BFF}>> {FFFFFF}Nitro & Repair{009BFF} <<");
    		textlabelDM[t] = CreateDynamic3DTextLabelEx(string, -1, pickInfo[t][pickX], pickInfo[t][pickY], pickInfo[t][pickZ], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);
    		continue;
    	}
    	else if (t > 0 && int[0] == int[2] && pickInfo[t][p_type] == 1 && pickInfo[t-1][p_type] == 2)
    	{
        	DestroyDynamic3DTextLabel(textlabelDM[t]);
    		DestroyDynamic3DTextLabel(textlabelDM[t-1]);

    		format(string, sizeof(string), "{009BFF}>> {FFFFFF}Nitro & Repair{009BFF} <<");
    		textlabelDM[t] = CreateDynamic3DTextLabelEx(string, -1, pickInfo[t][pickX], pickInfo[t][pickY], pickInfo[t][pickZ], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);
    		continue;	
    	}





    	else if (t > 0 && int[0] == int[1] + 1 && pickInfo[t][p_type] == 1 && pickInfo[t+1][p_type] == 2)
 		{
    		DestroyDynamic3DTextLabel(textlabelDM[t]);
    		DestroyDynamic3DTextLabel(textlabelDM[t+1]);

    		format(string, sizeof(string), "{009BFF}>> {FFFFFF}Nitro & Repair{009BFF} <<");
    		textlabelDM[t] = CreateDynamic3DTextLabelEx(string, -1, pickInfo[t][pickX], pickInfo[t][pickY], pickInfo[t][pickZ], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);
    		continue;
    	}
    	else if (t > 0 && int[0] == int[2] + 1 && pickInfo[t][p_type] == 1 && pickInfo[t-1][p_type] == 2)
    	{
        	DestroyDynamic3DTextLabel(textlabelDM[t]);
    		DestroyDynamic3DTextLabel(textlabelDM[t-1]);

    		format(string, sizeof(string), "{009BFF}>> {FFFFFF}Nitro & Repair{009BFF} <<");
    		textlabelDM[t] = CreateDynamic3DTextLabelEx(string, -1, pickInfo[t][pickX], pickInfo[t][pickY], pickInfo[t][pickZ], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);
    		continue;	
    	}
    	else if (t > 0 && int[0] == int[1] - 1 && pickInfo[t][p_type] == 1 && pickInfo[t+1][p_type] == 2)
 		{
    		DestroyDynamic3DTextLabel(textlabelDM[t]);
    		DestroyDynamic3DTextLabel(textlabelDM[t+1]);

    		format(string, sizeof(string), "{009BFF}>> {FFFFFF}Nitro & Repair{009BFF} <<");
    		textlabelDM[t] = CreateDynamic3DTextLabelEx(string, -1, pickInfo[t][pickX], pickInfo[t][pickY], pickInfo[t][pickZ], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);
    		continue;
    	}
    	else if (t > 0 && int[0] == int[2] - 1 && pickInfo[t][p_type] == 1 && pickInfo[t-1][p_type] == 2)
    	{
        	DestroyDynamic3DTextLabel(textlabelDM[t]);
    		DestroyDynamic3DTextLabel(textlabelDM[t-1]);

    		format(string, sizeof(string), "{009BFF}>> {FFFFFF}Nitro & Repair{009BFF} <<");
    		textlabelDM[t] = CreateDynamic3DTextLabelEx(string, -1, pickInfo[t][pickX], pickInfo[t][pickY], pickInfo[t][pickZ], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);
    		continue;	
    	}
    }

    LoadSettings(path);
    fclose(fhandle);
	return 1;
}

stock LoadPickupsTrain(playerid, path[])
{
    if (!fexist(path)) return 1;

    new File:fhandle = fopen(path, io_read);
    new item[512], i = 1, string[128];
    // new x[64], y[64], z[64], r[64], type[20];
    new Float:px, Float:py, Float:pz, typeval, vID;

    format(string, sizeof(string), "Pick%i_x", i);

    while (fread(fhandle, item))
    {
	    if (strfind(item, string, true) != -1)
		{
			if (strfind(item, "x=", true) != -1)
			{
				if (!sscanf(item, "'_x='f", px)) {
					format(string, sizeof(string), "Pick%i_y", i);
				}
			}
			else if (strfind(item, "y=", true) != -1)
			{
				if (!sscanf(item, "'_y='f", py)) {
					format(string, sizeof(string), "Pick%i_z", i);
				}
			}
			else if (strfind(item, "z=", true) != -1)
			{
				if (!sscanf(item, "'_z='f", pz)) {
					format(string, sizeof(string), "Pick%i_type", i);
				}
			}
			else if (strfind(item, "type=", true) != -1)
			{
				if (!sscanf(item, "'_type='i", typeval)) {
					
					if (typeval != 1) {
						if (typeval == 2) {
							format(string, sizeof(string), "{A1DB71}[{FFFFFF}Repair{C13E3E}]");

							SphereTrain[playerid][sIndexTrain[playerid]] = CreateDynamicSphereEx(px, py, pz, 5.0, {sizeof(worldsDM)}, {-1}, {-1}, 81);
							Streamer_SetIntData(STREAMER_TYPE_AREA, SphereTrain[playerid][sIndexTrain[playerid]], E_STREAMER_EXTRA_ID, 2);
						}	
			
						else if (typeval == 3) {
							format(string, sizeof(string), "{A1DB71}[{FFFFFF}Nitro{C13E3E}]");

							SphereTrain[playerid][sIndexTrain[playerid]] = CreateDynamicSphereEx(px, py, pz, 5.0, {sizeof(worldsDM)}, {-1}, {-1}, 81);
							Streamer_SetIntData(STREAMER_TYPE_AREA, SphereTrain[playerid][sIndexTrain[playerid]], E_STREAMER_EXTRA_ID, 1);
						}	
						else if (typeval == 6) {
							format(string, sizeof(string), "{009BFF}[{FFFFFF}Nitro & Repair{009BFF}]");

							SphereTrain[playerid][sIndexTrain[playerid]] = CreateDynamicSphereEx(px, py, pz, 5.0, {sizeof(worldsDM)}, {-1}, {-1}, 81);
							Streamer_SetIntData(STREAMER_TYPE_AREA, SphereTrain[playerid][sIndexTrain[playerid]], E_STREAMER_EXTRA_ID, 3);
						}	
						textlabelTrain[playerid][tlindexTrain[playerid]] = CreateDynamic3DTextLabelEx(string, -1, px, py, pz, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);

						pickInfoTrain[playerid][i][pickX] = px;
						pickInfoTrain[playerid][i][pickY] = py;
						pickInfoTrain[playerid][i][pickZ] = pz;
						pickInfoTrain[playerid][i][p_type] = typeval;
						i++, tlindexTrain[playerid]++, sIndexTrain[playerid]++;
						format(string, sizeof(string), "Pick%i_x", i);
					}
					else if (typeval == 1) {
						format(string, sizeof(string), "Pick%i_name", i);
					}
				}	
			}
			else if (strfind(item, "_name", true) != -1)
			{
				if (!sscanf(item, "'_name='i", vID)) {
					format(string, sizeof(string), "{009BFF}[{FFFFFF}%s{009BFF}]", GetVehicleName(vID));

					SphereTrain[playerid][sIndexTrain[playerid]] = CreateDynamicSphereEx(px, py, pz, 5.0, {sizeof(worldsDM)}, {-1}, {-1}, 81);
					Streamer_SetIntData(STREAMER_TYPE_AREA, SphereTrain[playerid][sIndexTrain[playerid]], E_STREAMER_EXTRA_ID, vID);

					textlabelTrain[playerid][tlindexTrain[playerid]] = CreateDynamic3DTextLabelEx(string, -1, px, py, pz, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 100.0, {sizeof(worldsDM)}, {-1}, {-1}, 89, -1, -1);
					pickInfoTrain[playerid][i][pickX] = px;
					pickInfoTrain[playerid][i][pickY] = py;
					pickInfoTrain[playerid][i][pickZ] = pz;
					pickInfoTrain[playerid][i][p_type] = typeval;
					pickInfoTrain[playerid][i][p_veh] = vID;

					i++, tlindexTrain[playerid]++, sIndexTrain[playerid]++;

					format(string, sizeof(string), "Pick%i_x", i);
				}					
			}
		}
    }
    LoadSettingsTrain(playerid, path);
    fclose(fhandle);
	return 1;
}

stock LoadSettings(path[])
{
    if (!fexist(path)) return 1;
    
    new File:fhandle = fopen(path, io_read);
    new weather, hours, minutes, item[128], tmp_author[40], music_id = -1;
    
    while (fread(fhandle, item))
    {
    	if (!sscanf(item, "'Author:' s[40]", tmp_author)) {
    		strmid(LoadInfo[Author], tmp_author, 0, strlen(tmp_author), strlen(tmp_author));
    	}
    	else if (!sscanf(item, "'Hours:' i", hours)) {

    	}
    	else if (!sscanf(item, "'Weather:' i", weather)) {
    		foreach (new playerid : Player) {
    			if (GetPVarInt(playerid, "mode") != 1) continue;

    			SetPlayerWeather(playerid, weather);
    		}
    	}
    	else if (!sscanf(item, "'Minutes:' i", minutes)) {
    		foreach (new playerid : Player) {
    			if (GetPVarInt(playerid, "mode") != 1) continue;

    			SetPlayerTime(playerid, hours, minutes);

    			printf("Hours: %i | Minutes: %i", hours, minutes);
    		}
    	}
    	else if (!sscanf(item, "'Music:' i", music_id))
    	{
       		foreach (new playerid : Player) {
    			if (GetPVarInt(playerid, "mode") != 1) continue;

  				Audio_Play(playerid, music_id);
    		} 		
    	}
    	/*else if (!sscanf(item, "'Minutes='", minutes)) {
    	}*/
    }

    foreach (new playerid : Player) {
    	SetPVarInt(playerid, "WeatherDM", weather);
    	SetPVarInt(playerid, "TimeDM_hours", hours);
    	SetPVarInt(playerid, "TimeDM_minutes", minutes);
    }

    fclose(fhandle);

    return 1;
} 

stock LoadSettingsTrain(playerid, path[])
{
    if (!fexist(path)) return 1;
    
    new File:fhandle = fopen(path, io_read);
    new weather, hours/*, minutes*/, item[128];
    
    while (fread(fhandle, item))
    {
    	if (!sscanf(item, "'Weather='i", weather)) {
    		SetPlayerWeather(playerid, weather);
    	}
    	else if (!sscanf(item, "'Time='i", hours)) {
    		SetPlayerTime(playerid, hours, 0);
    	}
    	/*else if (!sscanf(item, "'Minutes='", minutes)) {
    	}*/
    }

    fclose(fhandle);

    return 1;
} 

stock static InitalizeMaps()
{
	new dir:dHandle = dir_open("./scriptfiles/racemaps/");
	new item[150], type, i = 1;

	while(dir_list(dHandle, item, type))
	{
		if (strlen(item) < 3) continue;

		printf("%i - InitalizeMaps: %s", i, item);

		setproperty(0, "", i, item);
		i++;
	}

	LoadInfo[MaxMaps] = i;
	dir_close(dHandle);
}

stock static GetVehicleName(modelid)
{
    static vehName[30];
    strunpack(vehName, VehicleName[modelid - 400]);
    return vehName;
}

public CreateGameModeObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:scale, bool:collisions, interiorID, gamemode_id)
{
	if (!collisions) {
		return INVALID_OBJECT_ID;
	}

	dm_object[dm_object_count] = CreateDynamicObjectEx(modelid, X, Y, Z+5.0, rX, rY, rZ, 300.0, 300.0, 	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 80);

	if (scale == 0) {
		for (new t; t < 25; t ++) { 
			SetDynamicObjectMaterial(dm_object[dm_object_count], t, 18072, "gap_window", "cj_white_wall", 0xFFFFFF);
		}
	}

	if (interiorID == 1) {
		for (new t; t < 25; t ++) { 
			SetDynamicObjectMaterial(dm_object[dm_object_count], t, 18072, "gap_window", "cj_white_wall", 0xFFFFFF);
		}	
	}

	if (gamemode_id) {
		SetDynamicObjectNoCameraCol(dm_object[dm_object_count]);
	}

	Streamer_SetIntData(STREAMER_TYPE_OBJECT, dm_object[dm_object_count], E_STREAMER_EXTRA_ID, gamemode_id);

	dm_object_count ++;

	return true;
}

public CreateGameModeMarker(Float:X, Float:Y, Float:Z, m_type[], m_color[])
{
	new a, r, g, b, m_color_hex;

	printf("MARKER TYPE: %s", m_type);

	if (strfind(m_type, "corona", true) != -1)
	{
		print("In Corona drin");
		m_color_hex = ConvertStringToHex(m_color, strlen(m_color));

		toargb(m_color_hex, a, r, g, b);

		if (r > g && r > b)
		{
			print("Red corona erstellt");
			// red corona 
			dm_marker[dm_marker_count] = CreateDynamicObjectEx(19296, X, Y, Z+5.0, 0.0, 0.0, 0.0, 300.0, 300.0, 	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 80);

			Streamer_SetIntData(STREAMER_TYPE_OBJECT, dm_marker[dm_marker_count], E_STREAMER_EXTRA_ID, 19296);		
		}
		else if (g > r && g > b)
		{
			print("Green corona erstellt");
			// green corona 
			dm_marker[dm_marker_count] = CreateDynamicObjectEx(19297, X, Y, Z+5.0, 0.0, 0.0, 0.0, 300.0, 300.0, 	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 80);

			Streamer_SetIntData(STREAMER_TYPE_OBJECT, dm_marker[dm_marker_count], E_STREAMER_EXTRA_ID, 19297);		
		}
		else if (b > r && b > g)
		{
			print("Blue corona erstellt erstellt");
			// blue corona 
			dm_marker[dm_marker_count] = CreateDynamicObjectEx(19298, X, Y, Z+5.0, 0.0, 0.0, 0.0, 300.0, 300.0, 	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 80);

			Streamer_SetIntData(STREAMER_TYPE_OBJECT, dm_marker[dm_marker_count], E_STREAMER_EXTRA_ID, 19298);		
		}
	}
	else
	{
		m_color_hex = ConvertStringToHex(m_color, strlen(m_color));

		dm_marker[dm_marker_count] = CreateDynamicObjectEx(1559, X, Y, Z+5.0, 0.0, 0.0, 0.0, 300.0, 300.0, 	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 80);

		SetDynamicObjectMaterial(dm_marker[dm_marker_count], 0, 1231, "dynsigns", "white64", m_color_hex);

		Streamer_SetIntData(STREAMER_TYPE_OBJECT, dm_marker[dm_marker_count], E_STREAMER_EXTRA_ID, 1559);		
	}

	dm_marker_count ++;

	return true;
}

stock UnloadMap()
{
	KillTimer(LoadInfo[lTimerID]);

	new string[128];

	for (new id = 0; id != sIndexDM; id++) 	DestroyDynamicArea(SphereDM[id]);

	for (new id = 0; id != tlindexDM; id++) DestroyDynamic3DTextLabel(textlabelDM[id]);


	format(string, sizeof(string), "unloadfs rmaps/%s", LoadInfo[MapName]);
	SendRconCommand(string);

	for (new id = 0; id < dm_object_count; id++) 
	{
		DestroyDynamicObject(dm_object[id]); 
	}

	for (new id = 0; id < dm_marker_count; id++) 
	{
		DestroyDynamicObject(dm_marker[id]); 
	}

	for (new id = 0, j = CountDynamicAreas(); id < j; id++) 
	{
		if (Streamer_GetIntData(STREAMER_TYPE_AREA, id, E_STREAMER_WORLD_ID)  >= 0 && Streamer_GetIntData(STREAMER_TYPE_AREA, id, E_STREAMER_WORLD_ID)  <= 89)
		{
			DestroyDynamicArea(id); 
		}
	}


	new idd = 10000+1;

	while(existproperty(0, "", idd)) {
		deleteproperty(0, "", idd);
		idd++;
	}

	for (new id = 0; id < vehindexDM; id++) {
	    DestroyVehicle(vehDM[id]);
	}

	/*printf("[DEBUG]: Es wurden %i DM Objekte entfernt.", index);
	printf("[DEBUG]: Es sind noch %i Dynamische Objekte auf dem Server.", CountDynamicObjects());
	printf("[DEBUG]: Es sind noch %i Objecte auf dem Server.", CountObjects());*/

	sIndexDM = 0, tlindexDM = 0, vehindexDM = 0, dm_marker_count = 0, dm_object_count = 0;
	return 1;
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

stock UnloadMapTrain(playerid)
{
	new string[128], bool:p_found = false;

	for (new i = 0; i < MAX_PLAYERS; i++) {
		if (!IsPlayerConnected(i) || GetPVarInt(i, "mode") != 3) continue;

		if (strcmp(LoadInfoTrain[i][MapName], LoadInfoTrain[playerid][MapName], true)) {
			p_found = true;
			break;
		}
	}

	if (p_found == false)
	{
		new idd = 1000000+1, index = 0;

		while(existproperty(0, "", idd)) {
			deleteproperty(0, "", idd);
			idd++;
		}


		for (new id = 0, j = 10000; id < j; id++) 
		{
			if (Streamer_GetIntData(STREAMER_TYPE_OBJECT, id, E_STREAMER_WORLD_ID) <= 89)
			{
				DestroyDynamicObject(id); 
			}
		}

		for (new id = firstobjTrain[playerid]; id < maxobjectTrain[playerid]; id++)
		{
			if (IsValidObject(id)) DestroyObject(id);
		}

		format(string, sizeof(string), "unloadfs maps/%s", LoadInfoTrain[playerid][MapName]);
		SendRconCommand(string);

		printf("Es wurden %i Trainings Objekte entfernt.", index);

		for (new id = 0; id != sIndexTrain[playerid]; id++) 	DestroyDynamicArea(SphereTrain[playerid][id]);
		for (new id = 0; id != tlindexTrain[playerid]; id++) DestroyDynamic3DTextLabel(textlabelTrain[playerid][id]);


		sIndexTrain[playerid] = 0, tlindexTrain[playerid] = 0, vehindexTrain[playerid] = 0, maxobjectTrain[playerid] = 0;
		return 1;
	}
	return 1;
}

stock InitializeRace()
{
	new pos = 0, id = 0;

	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (!IsPlayerConnected(i))continue;
		if (GetPVarInt(i, "mode") != 1) continue;

		printf("PlayerID: %i", i);

		// if (GetPlayerState(i) == PLAYER_STATE_SPECTATING) TogglePlayerSpectating(i, false);

		SetPlayerInterior(i, 0);

		if (sInfo[id][sx] == 0.0)
		{
			Streamer_UpdateEx(i, sInfo[0][sx], sInfo[0][sy], sInfo[0][sz], id, -1);
			vehDM[vehindexDM] = CreateVehicle(sInfo[0][model], sInfo[0][sx], sInfo[0][sy], sInfo[0][sz]+8, sInfo[0][sr], GetPVarInt(i, "CarColor1"), GetPVarInt(i, "CarColor2"), -1);
		}

		Streamer_UpdateEx(i, sInfo[id][sx], sInfo[id][sy], sInfo[id][sz], id, -1);
		vehDM[vehindexDM] = CreateVehicle(sInfo[id][model], sInfo[id][sx], sInfo[id][sy], sInfo[id][sz]+8, sInfo[id][sr], GetPVarInt(i, "CarColor1"), GetPVarInt(i, "CarColor2"), -1);

		if (sInfo[id][sx] == sInfo[id+1][sx])
		{

			if (id < 89) {
				SetVehicleVirtualWorld(vehDM[vehindexDM], id);
				SetPlayerVirtualWorld(i, id);
			}
		}

		PutPlayerInVehicle(i, vehDM[vehindexDM], 0);
		/*SetPlayerPos(i, sInfo[id][sx], sInfo[id][sy], sInfo[id][sz]+5);
		SetPlayerFacingAngle(i, sInfo[id][sr]);*/
		TogglePlayerControllable(i, false);

		vehindexDM++;
		++pos;
		id++;
	}

	SetTimer("SyncPlayer", 3000, false);
	return 1;
}

stock InitializeRaceTrain(playerid)
{

	new pos = 0, id = 1;

	if (GetPVarInt(playerid, "mode") != 7) return 1;

	// if (GetPlayerState(i) == PLAYER_STATE_SPECTATING) TogglePlayerSpectating(i, false);

	SetPlayerInterior(playerid, 0);

	Streamer_UpdateEx(playerid, sInfoTrain[playerid][id][sx], sInfoTrain[playerid][id][sy], sInfoTrain[playerid][id][sz], id, -1);
	vehTrain[playerid][vehindexTrain[playerid]] = CreateVehicle(sInfoTrain[playerid][1][model], sInfoTrain[playerid][id][sx], sInfoTrain[playerid][id][sy], sInfoTrain[playerid][id][sz]+3, sInfoTrain[playerid][id][sr], GetPVarInt(playerid, "CarColor1"), GetPVarInt(playerid, "CarColor2"), -1);

	if (sInfoTrain[playerid][0][sx] == sInfoTrain[playerid][id][sx])
	{
		SetVehicleVirtualWorld(vehTrain[playerid][vehindexTrain[playerid]], id);
		SetPlayerVirtualWorld(playerid, id);
	}

	SetPlayerPos(playerid, sInfoTrain[playerid][id][sx], sInfoTrain[playerid][id][sy], sInfoTrain[playerid][id][sz]+10);
	SetPlayerFacingAngle(playerid, sInfoTrain[playerid][id][sr]);
	TogglePlayerControllable(playerid, false);

	++pos;
	id++;

	SetTimerEx("SyncPlayerTrain", 3000, false, "i", playerid);
	return 1;
}

stock InitializeHG()
{

	return 1;
}


forward SyncPlayer();
public SyncPlayer()
{
	vehindexDM = 0;

	for (new i = 0; i < MAX_PLAYERS; i++) {

		if (GetPVarInt(i, "mode") != 1) continue;

		SetVehiclePos(vehDM[vehindexDM], sInfo[vehindexDM][sx], sInfo[vehindexDM][sy], sInfo[vehindexDM][sz]+5);
		SetVehicleZAngle(vehDM[vehindexDM], sInfo[vehindexDM][sr]);

		// SetVehicleVirtualWorld(vehDM[vehindexDM], GetPlayerVirtualWorld(i));

		LinkVehicleToInterior(vehDM[vehindexDM], 0);
		// PutPlayerInVehicle(i,vehDM[vehindexDM],0);

		SetPVarInt(i, "VehID", vehDM[vehindexDM]);
		vehindexDM++;
	}
	return 1;
}

forward SyncPlayerTrain(playerid);
public SyncPlayerTrain(playerid)
{
	// vehindexTrain[playerid] = 1;
	new id = 1;

	SetPlayerVirtualWorld(playerid, 0);
	SetVehicleVirtualWorld(vehTrain[playerid][vehindexTrain[playerid]], 0);

	SetVehiclePos(vehTrain[playerid][vehindexTrain[playerid]], sInfoTrain[playerid][id][sx], sInfoTrain[playerid][id][sy], sInfoTrain[playerid][id][sz]);
	SetVehicleZAngle(vehTrain[playerid][vehindexTrain[playerid]], sInfoTrain[playerid][id][sr]);

	LinkVehicleToInterior(vehTrain[playerid][vehindexTrain[playerid]], 0);
	PutPlayerInVehicle(playerid, vehTrain[playerid][vehindexTrain[playerid]], 0);

	TogglePlayerControllable(playerid, true);

	SetPVarInt(playerid, "VehID", vehTrain[playerid][vehindexTrain[playerid]]);

	vehindexTrain[playerid]++;
	return 1;
}

/*stock static CreateRaceSpawn(Modelid, Float:X, Float:Y, Float:Z, Float:rZ, count) 
{
	new savestr[128];

	format(savestr, sizeof(savestr), "%d|%f|%f|%f|%f", Modelid, X, Y, Z, rZ);
	setproperty(0, "", 10000+count, savestr);
	return 1;
}

stock static CreateRaceSpawnBJ(Float:X, Float:Y, Float:Z, Float:rZ, count) 
{
	new savestr[128];

	format(savestr, sizeof(savestr), "%f|%f|%f|%f", X, Y, Z, rZ);
	setproperty(0, "", 70000+count, savestr);
	return 1;
}

stock static CreateRaceSpawnEDM(Modelid, Float:X, Float:Y, Float:Z, Float:rZ, count) 
{
	new savestr[128];

	format(savestr, sizeof(savestr), "%d|%f|%f|%f|%f", Modelid, X, Y, Z, rZ);
	setproperty(0, "", 5000+count, savestr);
	return 1;
}

stock static CreateRaceSpawnDD(Modelid, Float:X, Float:Y, Float:Z, Float:rZ, count) 
{
	new savestr[128];

	format(savestr, sizeof(savestr), "%d|%f|%f|%f|%f", Modelid, X, Y, Z, rZ);
	setproperty(0, "", 100000+count, savestr);
	return 1;
}

stock static CreateRaceSpawnTrain(Modelid, Float:X, Float:Y, Float:Z, Float:rZ, count) 
{
	new savestr[128];

	format(savestr, sizeof(savestr), "%d|%f|%f|%f|%f", Modelid, X, Y, Z, rZ);
	setproperty(0, "", 1000000+count, savestr);
	return 1;
}

stock static CreateSpawnHG(Float:X, Float:Y, Float:Z, Float:rZ, count) 
{
	new savestr[128];

	format(savestr, sizeof(savestr), "%f|%f|%f|%f", X, Y, Z, rZ);
	setproperty(0, "", 1000000+count, savestr);
	return 1;
}*/

stock StartRace(time) {
	if(InitializeRace()){
		setproperty(.name = "CountdownTime", .value = time);
		return LoadInfo[lTimerID] = SetTimerEx("@Countdown",1000,false,"i",time);
	}
	return 1;
}


@Countdown(time){
	new str[3];
	valstr(str,time/1000);
	time -= 1000;
	if(!time)
	{
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if(!IsPlayerConnected(i)) continue;
			if (GetPVarInt(i, "mode") != 1) continue;

			PlayerPlaySound(i, 1057, 0.0, 0.0, 0.0);

			GameTextForPlayer(i, "Go Go Go", 500, 4);
			TogglePlayerControllable(i,true);
		}
	}
	else
	{
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
	    	if(!IsPlayerConnected(i)) continue;
	    	if (GetPVarInt(i, "mode") != 1) continue;

			PlayerPlaySound(i, 1056, 0.0, 0.0, 0.0);
			GameTextForPlayer(i, str, 500, 4);
		}
		return LoadInfo[lTimerID] = SetTimerEx("@Countdown",1000,false,"i",time);
	}
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{
    state _ALS_:hooked;

	new kind = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);

	PlayerPlaySound(playerid, 1133,0.0,0.0,0.0);

	switch(kind)
	{
		case 1: AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);
		case 2: {
		    if (GetPVarInt(playerid, "disablerepair") == 1) return 1;
			RepairVehicle(GetPlayerVehicleID(playerid));
		}
		case 3: {
			AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);
			RepairVehicle(GetPlayerVehicleID(playerid));
		}
		case 4:{
			new Float:vData[3], loadstr[40];
			getproperty(0, "", 1000000+areaid, loadstr);
			strunpack(loadstr, loadstr, sizeof(loadstr));
			sscanf(loadstr,"p<|>a<f>[3]",vData);
			SetVehicleVelocity(GetPlayerVehicleID(playerid), vData[0],vData[1],vData[2]);
		}
		case 5:{
			new vehicle = GetPlayerVehicleID(playerid),Float:vData[8], loadstr[40];

			getproperty(0, "", 1000000+areaid, loadstr);
			strunpack(loadstr, loadstr, sizeof(loadstr));
			print(loadstr);
			sscanf(loadstr,"p<|>a<f>[4]",vData);
			GetVehicleVelocity(vehicle,vData[5],vData[6],vData[7]);
			SetVehiclePos(vehicle,vData[0],vData[1],vData[2]+2);
			SetVehicleZAngle(vehicle,vData[3]);
			TogglePlayerControllable(playerid, false);
			SetVehiclePos(vehicle,vData[0],vData[1],vData[2]);
			SetVehicleZAngle(vehicle,vData[3]);
			TogglePlayerControllable(playerid, true);
			// SetVehicleVelocity(vehicle,vData[5],vData[6],vData[7]);
		}
		case 12: { // Explode
			new Float:vData[3], loadstr[40], bombid;
			getproperty(0, "", 1000000+areaid, loadstr);
			strunpack(loadstr, loadstr, sizeof(loadstr));
			sscanf(loadstr,"p<|>a<f>[3]<i>",vData, bombid);
			CreateExplosionForPlayer(playerid, vData[0], vData[1], vData[2], bombid, 10.0);
		}
		default:
		{
			new vehicleID = GetPlayerVehicleID(playerid);

			if (GetVehicleModel(vehicleID) != kind && kind != 0)
			{
				new Float:vData[7];

				GetVehiclePos(vehicleID,vData[0],vData[1],vData[2]);
				GetVehicleZAngle(vehicleID,vData[3]);
				GetVehicleVelocity(vehicleID,vData[4],vData[5],vData[6]);

				DestroyVehicle(vehicleID);
				vehicleID = CreateVehicle(kind,vData[0],vData[1],vData[2]+2,vData[3],GetPVarInt(playerid, "CarColor1"),GetPVarInt(playerid, "CarColor2"),-1);
				SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(playerid));
				SetVehicleVirtualWorld(vehicleID, GetPlayerVirtualWorld(playerid));
				SetPlayerInterior(playerid, 0);
				LinkVehicleToInterior(vehicleID, 0);
				PutPlayerInVehicle(playerid, vehicleID, 0);
				SetPVarInt(playerid, "VehID", vehicleID);

				if(kind == 425 || kind == 520)
				{
					new Float:px, Float:py, Float:pz;

					GetVehiclePos(vehicleID, px, py, pz);

					SetVehiclePos(vehicleID, px+25, py, pz+120);

					if (GetPVarInt(playerid, "mode") == 1) OnPlayerFinishRace(playerid);

					SetPlayerVirtualWorld(playerid, 0);
					SetVehicleVirtualWorld(vehicleID, 0);

					for (new i = 0; i < MAX_PLAYERS; i++)
					{
						if (GetPVarInt(i, "mode") != GetPVarInt(playerid, "mode")) continue;

						SetPlayerVirtualWorld(i, 0);
					}
				}
				else
				{
        			SetVehicleVelocity(vehicleID, vData[4], vData[5], vData[6]);
				}

				for (new i = 0; i < MAX_PLAYERS; i++)
				{
					if (GetPVarInt(i, "mode") != GetPVarInt(playerid, "mode")) continue;
					if (GetPVarInt(i, "spectateID") != playerid) continue;

					StopSpectate(i);
					StartSpectate(i, playerid);
				}
			}
		}
	}
    return H_OnPlayerEnterDynamicArea(playerid, areaid);
}

forward H_OnPlayerEnterDynamicArea(playerid, areaid);
#if defined _ALS_OnPlayerEnterDynamicArea
    #undef OnPlayerEnterDynamicArea
#else
    #define _ALS_OnPlayerEnterDynamicArea
#endif
public H_OnPlayerEnterDynamicArea(playerid, areaid) <_ALS_:unhooked> return 1;
public H_OnPlayerEnterDynamicArea(playerid, areaid) <> return 1;
#define OnPlayerEnterDynamicArea(%0,%1) H_OnPlayerEnterDynamicArea(%0,%1)<_ALS_:hooked>


public OnPlayerSpawn(playerid)
{
    state _ALS_:hooked;

    if (GetPVarInt(playerid, "mode") == 3) {
    	DestroyVehicle(vehTrain[playerid][vehindexTrain[playerid]-1]);

		new mapstring[164];

		GetPVarString(playerid, "MapName", mapstring, sizeof(mapstring));

		format(mapstring, sizeof(mapstring), "/TrainMaps/%s.ini", mapstring);

		LoadMapTrain(playerid, mapstring);
		InitializeRaceTrain(playerid);
    }

    return H_OnPlayerSpawn(playerid);
}

forward H_OnPlayerSpawn(playerid);
#if defined _ALS_OnPlayerSpawn
    #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif
public H_OnPlayerSpawn(playerid) <_ALS_:unhooked> return 1;
public H_OnPlayerSpawn(playerid) <> return 1;
#define OnPlayerSpawn(%0) H_OnPlayerSpawn(%0)<_ALS_:hooked>

public OnPlayerDeath(playerid, killerid, reason)
{
	state _ALS_:hooked;

	if (GetPVarInt(playerid, "mode") == 3) {
		DestroyVehicle(vehTrain[playerid][vehindexTrain[playerid]-1]);
	}

	return H_OnPlayerDeath(playerid, killerid, reason);
}

forward H_OnPlayerDeath(playerid, killerid, reason);
#if defined _ALS_OnPlayerDeath
    #undef OnPlayerDeath
#else
    #define _ALS_OnPlayerDeath
#endif
public H_OnPlayerDeath(playerid, killerid, reason) <_ALS_:unhooked> return 1;
public H_OnPlayerDeath(playerid, killerid, reason) <> return 1;
#define OnPlayerDeath(%0,%1,%2) H_OnPlayerDeath(%0,%1,%2)<_ALS_:hooked>

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	state _ALS_:hooked;

	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {

		if (GetPVarInt(playerid, "mode") == 3) {
			DestroyVehicle(vehTrain[playerid][vehindexTrain[playerid]-1]);

			new mapstring[164];

			GetPVarString(playerid, "MapName", mapstring, sizeof(mapstring));

			format(mapstring, sizeof(mapstring), "/TrainMaps/%s.ini", mapstring);

			LoadMapTrain(playerid, mapstring);
			InitializeRaceTrain(playerid);
		}
	}
	return H_OnPlayerStateChange(playerid, newstate, oldstate);
}

forward H_OnPlayerStateChange(playerid, newstate, oldstate);
#if defined _ALS_OnPlayerStateChange
    #undef OnPlayerStateChange
#else
    #define _ALS_OnPlayerStateChange
#endif
public H_OnPlayerStateChange(playerid, newstate, oldstate) <_ALS_:unhooked> return 1;
public H_OnPlayerStateChange(playerid, newstate, oldstate) <> return 1;
#define OnPlayerStateChange(%0,%1,%2) H_OnPlayerStateChange(%0,%1,%2)<_ALS_:hooked>

