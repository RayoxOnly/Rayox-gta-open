#include <YSI_Coding\y_hooks>

static
    PlayerText:MoneyNotification[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    MoneyNotification[playerid] = CreatePlayerTextDraw(playerid, 610.000000, 125.000000, "~g~+ $4,000");
    PlayerTextDrawFont(playerid, MoneyNotification[playerid], TEXT_DRAW_FONT_3);
    PlayerTextDrawLetterSize(playerid, MoneyNotification[playerid], 0.400000, 1.600000);
    PlayerTextDrawTextSize(playerid, MoneyNotification[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, MoneyNotification[playerid], 1);
    PlayerTextDrawSetShadow(playerid, MoneyNotification[playerid], 0);
    PlayerTextDrawAlignment(playerid, MoneyNotification[playerid], TEXT_DRAW_ALIGN_RIGHT);
    PlayerTextDrawColor(playerid, MoneyNotification[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, MoneyNotification[playerid], 255);
    PlayerTextDrawBoxColour(playerid, MoneyNotification[playerid], 50);
    PlayerTextDrawUseBox(playerid, MoneyNotification[playerid], false);
    PlayerTextDrawSetProportional(playerid, MoneyNotification[playerid], true);
    PlayerTextDrawSetSelectable(playerid, MoneyNotification[playerid], false);
    return 1;
}

hook native GivePlayerMoney(playerid, money) {
    if(!Player_IsSpawned(playerid)) {
        return 1;
    }

    if(money == 0) {
        return continue(playerid, money);
    }

    new
        string[24];

    // e.g
    // + $10,000 or - $10,000
    format(
        string,
         sizeof(string),
         "%s %m",
         (money > 0) ? ("~g~+") : ("~r~"), // colour
         money
    );
    PlayerTextDrawSetString(
        playerid,
        MoneyNotification[playerid],
        string
    );
    PlayerTextDrawShow(playerid, MoneyNotification[playerid]);

    defer MoneyNotification_Hide(playerid);
    return continue(playerid, money);
}

timer MoneyNotification_Hide[3500](playerid) {
    PlayerTextDrawHide(playerid, MoneyNotification[playerid]);
}
