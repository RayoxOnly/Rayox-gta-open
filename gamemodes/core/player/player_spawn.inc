#include <YSI_Coding\y_hooks>

static
    const Float:LS_SpawnPoints[][] = {
    {810.63520, -1340.0682, 13.5386, 37.33070},
    {1124.6071, -1427.5155, 15.7969, 350.9336},
    {585.81520, -1247.9160, 17.9521, 335.6035},
    {2025.2626, -1423.2682, 16.9922, 135.4516},
    {2509.2468, -1679.2029, 13.5469, 50.24740},
    {1457.1467, -1011.7307, 26.8438, 51.79910},
    {2017.8206, -1279.4851, 23.9820, 47.38920},
    {1935.7644, -1794.6068, 13.5469, 295.5515},
    {1371.4569, -1090.6387, 24.5459, 92.84640},
    {2298.4055, -1500.3264, 25.3047, 199.6940},
    {1178.0417, -1323.6000, 14.1005, 285.5701},
    {1757.44350, -1456.7, 13.5469, 282.4133}
};

static
    const Float:Police_SpawnPoints[][] = {
    {1526.3353, -1677.9645, 5.8906, 265.4622},
    {1568.4797, -1691.4695, 5.8906, 178.3064},
    {1579.4210, -1636.7090, 13.5529, 91.7339}
};

static
    const Float:Medic_SpawnPoints[][] = {
    {2023.8966, -1407.5162, 17.1811, 174.5757},
    {2037.4469, -1412.0627, 17.1641, 125.2918},
    {2039.6255, -1427.4698, 17.1641, 89.3143}
};

static
    const Float:Army_SpawnPoints[][] = {
    {1130.2200, -2037.3264, 69.0078, 272.0834}
};

static
    PlayerLastSpawn[MAX_PLAYERS],
    bool:PlayerFirstSpawn[MAX_PLAYERS] = true
;
hook OnPlayerConnect(playerid) {
    PlayerFirstSpawn[playerid] = true;
    PlayerLastSpawn[playerid] = -1;
    return 1;
}

hook OnPlayerSpawn(playerid) {

    // Execute this when player spawns for the first time.
    if(PlayerFirstSpawn[playerid]) {

        Logger_Dbg(SERVER_DEBUG_HANDLER, "[OnPlayerSpawn / player_spawn.inc] calling OnPlayerFirstSpawn");
        CallLocalFunction("OnPlayerFirstSpawn", "i", playerid);
        PlayerFirstSpawn[playerid] = false;
    }

    new
        id,
        Float: x,
        Float: y,
        Float: z,
        Float: ang;

    if(Player_GetClass(playerid) == TEAM_CIVILIAN) {
        if(Player_GetJob(playerid) == TYPE_NO_JOB) {
            Player_ShowJobMenu(playerid);
        }
        id = random(sizeof(LS_SpawnPoints));

        if(id == PlayerLastSpawn[playerid]) {
            // regen new id
            id = random(sizeof(LS_SpawnPoints));
            Logger_Dbg(PLAYER_DEBUG_HANDLER, "[OnPlayerSpawn / player_spawn.inc] spawnid same as last, regenerating new spawn for player.",
                Logger_P(playerid),
                Logger_I("id", playerid)
            );
        }

        x = LS_SpawnPoints[id][0],
        y = LS_SpawnPoints[id][1],
        z = LS_SpawnPoints[id][2],
        ang = LS_SpawnPoints[id][3];

        PlayerLastSpawn[playerid] = id;

        Logger_Dbg(PLAYER_DEBUG_HANDLER, "[OnPlayerSpawn / player_spawn.inc] Server spawn coordinates",
            Logger_P(playerid),
            Logger_F("Position X", x),
            Logger_F("Position Y", y),
            Logger_F("Position Z", z)
        );
    }
    else if(Player_GetClass(playerid) == TEAM_MEDIC) {
        id = random(sizeof(Medic_SpawnPoints));

        x = Medic_SpawnPoints[id][0];
        y = Medic_SpawnPoints[id][1];
        z = Medic_SpawnPoints[id][2];
        ang = Medic_SpawnPoints[id][3];
    }
    else if(Player_GetClass(playerid) == TEAM_POLICE) {
        id = random(sizeof(Police_SpawnPoints));

        x = Police_SpawnPoints[id][0];
        y = Police_SpawnPoints[id][1];
        z = Police_SpawnPoints[id][2];
        ang = Police_SpawnPoints[id][3];

        Weapon_DoNotSaveBegin(playerid);
        GivePlayerWeapon(playerid, WEAPON_SILENCED, 	150);
        GivePlayerWeapon(playerid, WEAPON_M4, 			200);
        GivePlayerWeapon(playerid, WEAPON_NITESTICK, 	200);
        Weapon_DoNotSaveEnd(playerid);
    }
    else if(Player_GetClass(playerid) == TEAM_ARMY) {
        id = random(sizeof(Army_SpawnPoints));

        x = Army_SpawnPoints[id][0];
        y = Army_SpawnPoints[id][1];
        z = Army_SpawnPoints[id][2];
        ang = Army_SpawnPoints[id][3];

        Weapon_DoNotSaveBegin(playerid);
        GivePlayerWeapon(playerid, WEAPON_DEAGLE, 	100);
        GivePlayerWeapon(playerid, WEAPON_M4, 		200);
        GivePlayerWeapon(playerid, WEAPON_SNIPER,   50);
        GivePlayerWeapon(playerid, WEAPON_GRENADE, 	4);
        Weapon_DoNotSaveEnd(playerid);


        SendClientMessage(playerid, -1, "called");
    }
    SetPlayerPos(playerid, x, y, z);
    SetPlayerFacingAngle(playerid, ang);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    SetCameraBehindPlayer(playerid);

    Logger_Dbg(PLAYER_DEBUG_HANDLER, "[OnPlayerSpawn / player_spawn.inc] player spawned",
        Logger_P(playerid),
        Logger_I("id", playerid),
        Logger_F("x", x),
        Logger_F("y", y),
        Logger_F("z", z)
    );
    return 1;
}
