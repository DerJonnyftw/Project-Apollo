#include <a_samp>

//

#undef MAX_PLAYERS
#define MAX_PLAYERS 500

#define MAX_MARKERS 20

//

new MarkerCreated = 0;
//new Adjust = 0;

new Disabled[MAX_PLAYERS][MAX_MARKERS];

enum mInfo
{
   Float:mX, Float:mY, Float:mZ,
   Float:mRange, Used,
}
new Markers[MAX_MARKERS][mInfo];

//

forward OnPlayerReachMarker(playerid, markerid);
forward CreateMarkerVisible(Float:x, Float:y, Float:z);

//
stock CreateMarker(Float:range, Float:x, Float:y, Float:z)
{

	Markers[MarkerCreated][mX] = x;
	Markers[MarkerCreated][mY] = y;
	Markers[MarkerCreated][mZ] = z;
	Markers[MarkerCreated][mRange] = range;
    
	MarkerCreated ++;
	
	CreateMarkerVisible(x,y,z);
	
	return MarkerCreated-1;
	
}

public CreateMarkerVisible(Float:x, Float:y, Float:z)
{
	CreateObject(19298, x,y,z, 0,0,0);
	return 1;

}

public OnPlayerDeath(playerid)
{
    for(new i = 0; i < MarkerCreated; i++)
    {
         Disabled[playerid][i] = 0;
    }
	return 1;
}

public OnPlayerUpdate(playerid)
{
    if(IsPlayerInAnyVehicle(playerid))
    {
		 new Float:Velocitya[3];
         GetVehicleVelocity(GetPlayerVehicleID(playerid), Velocitya[0], Velocitya[1], Velocitya[2]);
	     new Float:Velo = floatsqroot(Velocitya[0]*Velocitya[0] + Velocitya[1]*Velocitya[1] + Velocitya[2]*Velocitya[2]);
	     new Float:ping = GetPlayerPing(playerid);
	     ping = ping / 1000;
		 for(new i = 0; i < MarkerCreated; i++)
		 {
			  if(IsPlayerInRangeOfPoint(playerid, Markers[i][mRange]+ping*Velo*50, Markers[i][mX], Markers[i][mY], Markers[i][mZ]))
		      {
                 if(Disabled[playerid][i] == 1) return 1;
			     CallLocalFunction("OnPlayerReachMarker", "ii", playerid, i);
			     Disabled[playerid][i] = 1;
			     return 1;
             }
		 }
    }
	return 1;
}


