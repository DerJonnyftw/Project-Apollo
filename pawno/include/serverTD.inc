#include <a_samp>

new Text:Alive_TD[4];
new Text:FOOTER_TD[8];
new Text:DMLoad_TD[8];
new Text:ClanWar_TD[13];
new Text:TopTime_TD[33];
new Text:DeathList_TD[4];
new Text:MoneyLabel_TD[3];

new PlayerText:SPECTATOR_PTD[MAX_PLAYERS][4];
new PlayerText:MoneyLabel_PTD[MAX_PLAYERS][1];
new PlayerText:RegLog_PTD[MAX_PLAYERS][41];

stock CreateServerMoneyLabel()
{
	MoneyLabel_TD[0] = TextDrawCreate(498.333343, 79.244422, "box");
	TextDrawLetterSize(MoneyLabel_TD[0], 0.000000, 1.966666);
	TextDrawTextSize(MoneyLabel_TD[0], 607.000000, 0.000000);
	TextDrawAlignment(MoneyLabel_TD[0], 1);
	TextDrawColor(MoneyLabel_TD[0], -1);
	TextDrawUseBox(MoneyLabel_TD[0], 1);
	TextDrawBoxColor(MoneyLabel_TD[0], -1579453953);
	TextDrawSetShadow(MoneyLabel_TD[0], 0);
	TextDrawSetOutline(MoneyLabel_TD[0], 0);
	TextDrawBackgroundColor(MoneyLabel_TD[0], 255);
	TextDrawFont(MoneyLabel_TD[0], 1);
	TextDrawSetProportional(MoneyLabel_TD[0], 1);
	TextDrawSetShadow(MoneyLabel_TD[0], 0);

	MoneyLabel_TD[1] = TextDrawCreate(499.333404, 80.344406, "box");
	TextDrawLetterSize(MoneyLabel_TD[1], 0.000000, 1.700000);
	TextDrawTextSize(MoneyLabel_TD[1], 606.000000, 0.000000);
	TextDrawAlignment(MoneyLabel_TD[1], 1);
	TextDrawColor(MoneyLabel_TD[1], -1);
	TextDrawUseBox(MoneyLabel_TD[1], 1);
	TextDrawBoxColor(MoneyLabel_TD[1], 255);
	TextDrawSetShadow(MoneyLabel_TD[1], 0);
	TextDrawSetOutline(MoneyLabel_TD[1], 0);
	TextDrawBackgroundColor(MoneyLabel_TD[1], 255);
	TextDrawFont(MoneyLabel_TD[1], 1);
	TextDrawSetProportional(MoneyLabel_TD[1], 1);
	TextDrawSetShadow(MoneyLabel_TD[1], 0);

	MoneyLabel_TD[2] = TextDrawCreate(499.266632, 79.270347, "$");
	TextDrawLetterSize(MoneyLabel_TD[2], 0.452666, 1.803259);
	TextDrawAlignment(MoneyLabel_TD[2], 1);
	TextDrawColor(MoneyLabel_TD[2], -1579453953);
	TextDrawSetShadow(MoneyLabel_TD[2], 0);
	TextDrawSetOutline(MoneyLabel_TD[2], 0);
	TextDrawBackgroundColor(MoneyLabel_TD[2], 255);
	TextDrawFont(MoneyLabel_TD[2], 3);
	TextDrawSetProportional(MoneyLabel_TD[2], 1);
	TextDrawSetShadow(MoneyLabel_TD[2], 0);
	return 1;
}

stock CreateServerFooterLabel()
{
	FOOTER_TD[0] = TextDrawCreate(1.066691, 449.426330, "box");
	TextDrawLetterSize(FOOTER_TD[0], 0.000000, -2.899998);
	TextDrawTextSize(FOOTER_TD[0], 640.000000, 0.000000);
	TextDrawAlignment(FOOTER_TD[0], 1);
	TextDrawColor(FOOTER_TD[0], -1);
	TextDrawUseBox(FOOTER_TD[0], 1);
	TextDrawBoxColor(FOOTER_TD[0], 80);
	TextDrawSetShadow(FOOTER_TD[0], 0);
	TextDrawSetOutline(FOOTER_TD[0], 0);
	TextDrawBackgroundColor(FOOTER_TD[0], 255);
	TextDrawFont(FOOTER_TD[0], 1);
	TextDrawSetProportional(FOOTER_TD[0], 1);
	TextDrawSetShadow(FOOTER_TD[0], 0);

	FOOTER_TD[1] = TextDrawCreate(2.500030, 426.385223, "Next_map:");
	TextDrawLetterSize(FOOTER_TD[1], 0.165000, 1.015110);
	TextDrawAlignment(FOOTER_TD[1], 1);
	TextDrawColor(FOOTER_TD[1], -1579453953);
	TextDrawSetShadow(FOOTER_TD[1], 0);
	TextDrawSetOutline(FOOTER_TD[1], 1);
	TextDrawBackgroundColor(FOOTER_TD[1], 255);
	TextDrawFont(FOOTER_TD[1], 1);
	TextDrawSetProportional(FOOTER_TD[1], 1);
	TextDrawSetShadow(FOOTER_TD[1], 0);

	FOOTER_TD[2] = TextDrawCreate(9.700033, 435.585784, "Current_map:");
	TextDrawLetterSize(FOOTER_TD[2], 0.182666, 1.135406);
	TextDrawAlignment(FOOTER_TD[2], 1);
	TextDrawColor(FOOTER_TD[2], -1);
	TextDrawSetShadow(FOOTER_TD[2], 0);
	TextDrawSetOutline(FOOTER_TD[2], 1);
	TextDrawBackgroundColor(FOOTER_TD[2], 255);
	TextDrawFont(FOOTER_TD[2], 1);
	TextDrawSetProportional(FOOTER_TD[2], 1);
	TextDrawSetShadow(FOOTER_TD[2], 0);

	FOOTER_TD[3] = TextDrawCreate(1.200039, 435.370971, "~>~");
	TextDrawLetterSize(FOOTER_TD[3], 0.211333, 1.151999);
	TextDrawAlignment(FOOTER_TD[3], 1);
	TextDrawColor(FOOTER_TD[3], -1);
	TextDrawSetShadow(FOOTER_TD[3], 0);
	TextDrawSetOutline(FOOTER_TD[3], 1);
	TextDrawBackgroundColor(FOOTER_TD[3], 255);
	TextDrawFont(FOOTER_TD[3], 1);
	TextDrawSetProportional(FOOTER_TD[3], 1);
	TextDrawSetShadow(FOOTER_TD[3], 0);

	FOOTER_TD[4] = TextDrawCreate(-1.266639, 427.537719, "box");
	TextDrawLetterSize(FOOTER_TD[4], 0.000000, -0.666665);
	TextDrawTextSize(FOOTER_TD[4], 641.000000, 0.000000);
	TextDrawAlignment(FOOTER_TD[4], 1);
	TextDrawColor(FOOTER_TD[4], -1);
	TextDrawUseBox(FOOTER_TD[4], 1);
	TextDrawBoxColor(FOOTER_TD[4], -1579453953);
	TextDrawSetShadow(FOOTER_TD[4], 0);
	TextDrawSetOutline(FOOTER_TD[4], 0);
	TextDrawBackgroundColor(FOOTER_TD[4], 255);
	TextDrawFont(FOOTER_TD[4], 1);
	TextDrawSetProportional(FOOTER_TD[4], 1);
	TextDrawSetShadow(FOOTER_TD[4], 0);

	FOOTER_TD[5] = TextDrawCreate(635.566040, 430.822326, "Time:_~w~02:00");
	TextDrawLetterSize(FOOTER_TD[5], 0.303999, 1.259852);
	TextDrawAlignment(FOOTER_TD[5], 3);
	TextDrawColor(FOOTER_TD[5], -1579453953);
	TextDrawSetShadow(FOOTER_TD[5], 0);
	TextDrawSetOutline(FOOTER_TD[5], 1);
	TextDrawBackgroundColor(FOOTER_TD[5], 255);
	TextDrawFont(FOOTER_TD[5], 1);
	TextDrawSetProportional(FOOTER_TD[5], 1);
	TextDrawSetShadow(FOOTER_TD[5], 0);

	FOOTER_TD[6] = TextDrawCreate(35.400062, 426.385223, "Random");
	TextDrawLetterSize(FOOTER_TD[6], 0.165000, 1.015110);
	TextDrawAlignment(FOOTER_TD[6], 1);
	TextDrawColor(FOOTER_TD[6], -1579453953);
	TextDrawSetShadow(FOOTER_TD[6], 0);
	TextDrawSetOutline(FOOTER_TD[6], 1);
	TextDrawBackgroundColor(FOOTER_TD[6], 255);
	TextDrawFont(FOOTER_TD[6], 1);
	TextDrawSetProportional(FOOTER_TD[6], 1);
	TextDrawSetShadow(FOOTER_TD[6], 0);

	FOOTER_TD[7] = TextDrawCreate(53.799785, 435.585784, "");
	TextDrawLetterSize(FOOTER_TD[7], 0.182666, 1.135406);
	TextDrawAlignment(FOOTER_TD[7], 1);
	TextDrawColor(FOOTER_TD[7], -1);
	TextDrawSetShadow(FOOTER_TD[7], 0);
	TextDrawSetOutline(FOOTER_TD[7], 1);
	TextDrawBackgroundColor(FOOTER_TD[7], 255);
	TextDrawFont(FOOTER_TD[7], 1);
	TextDrawSetProportional(FOOTER_TD[7], 1);
	TextDrawSetShadow(FOOTER_TD[7], 0);
	return 1;
}

stock CreateServerAliveLabel()
{
	Alive_TD[0] = TextDrawCreate(501.133239, 23.114835, "box");
	TextDrawLetterSize(Alive_TD[0], 0.000000, 5.485657);
	TextDrawTextSize(Alive_TD[0], 544.000000, 0.000000);
	TextDrawAlignment(Alive_TD[0], 1);
	TextDrawColor(Alive_TD[0], -1);
	TextDrawUseBox(Alive_TD[0], 1);
	TextDrawBoxColor(Alive_TD[0], -1579453953);
	TextDrawSetShadow(Alive_TD[0], 0);
	TextDrawSetOutline(Alive_TD[0], 0);
	TextDrawBackgroundColor(Alive_TD[0], 255);
	TextDrawFont(Alive_TD[0], 1);
	TextDrawSetProportional(Alive_TD[0], 1);
	TextDrawSetShadow(Alive_TD[0], 0);

	Alive_TD[1] = TextDrawCreate(502.366638, 24.414840, "box");
	TextDrawLetterSize(Alive_TD[1], 0.000000, 5.194992);
	TextDrawTextSize(Alive_TD[1], 542.879882, 0.000000);
	TextDrawAlignment(Alive_TD[1], 1);
	TextDrawColor(Alive_TD[1], -1);
	TextDrawUseBox(Alive_TD[1], 1);
	TextDrawBoxColor(Alive_TD[1], 255);
	TextDrawSetShadow(Alive_TD[1], 0);
	TextDrawSetOutline(Alive_TD[1], 0);
	TextDrawBackgroundColor(Alive_TD[1], 255);
	TextDrawFont(Alive_TD[1], 1);
	TextDrawSetProportional(Alive_TD[1], 1);
	TextDrawSetShadow(Alive_TD[1], 0);

	Alive_TD[2] = TextDrawCreate(502.333129, 25.403718, "Alive");
	TextDrawLetterSize(Alive_TD[2], 0.325666, 1.442370);
	TextDrawAlignment(Alive_TD[2], 1);
	TextDrawColor(Alive_TD[2], -1);
	TextDrawSetShadow(Alive_TD[2], 0);
	TextDrawSetOutline(Alive_TD[2], 0);
	TextDrawBackgroundColor(Alive_TD[2], 255);
	TextDrawFont(Alive_TD[2], 2);
	TextDrawSetProportional(Alive_TD[2], 1);
	TextDrawSetShadow(Alive_TD[2], 0);

	Alive_TD[3] = TextDrawCreate(523.232971, 39.681377, "--");
	TextDrawLetterSize(Alive_TD[3], 0.686333, 3.109925);
	TextDrawAlignment(Alive_TD[3], 2);
	TextDrawColor(Alive_TD[3], -1);
	TextDrawSetShadow(Alive_TD[3], 0);
	TextDrawSetOutline(Alive_TD[3], 0);
	TextDrawBackgroundColor(Alive_TD[3], 255);
	TextDrawFont(Alive_TD[3], 3);
	TextDrawSetProportional(Alive_TD[3], 0);
	TextDrawSetShadow(Alive_TD[3], 0);
	return 1;
}

stock CreateServerLoadingLabel()
{
	DMLoad_TD[0] = TextDrawCreate(-1.999971, 0.429632, "box");
	TextDrawLetterSize(DMLoad_TD[0], 0.000000, 53.466598);
	TextDrawTextSize(DMLoad_TD[0], 682.000000, 0.000000);
	TextDrawAlignment(DMLoad_TD[0], 1);
	TextDrawColor(DMLoad_TD[0], -1);
	TextDrawUseBox(DMLoad_TD[0], 1);
	TextDrawBoxColor(DMLoad_TD[0], 84215295);
	TextDrawSetShadow(DMLoad_TD[0], 0);
	TextDrawSetOutline(DMLoad_TD[0], 0);
	TextDrawBackgroundColor(DMLoad_TD[0], 255);
	TextDrawFont(DMLoad_TD[0], 1);
	TextDrawSetProportional(DMLoad_TD[0], 0);
	TextDrawSetShadow(DMLoad_TD[0], 0);

	DMLoad_TD[1] = TextDrawCreate(171.666580, 117.718505, "Project_Apollo");
	TextDrawLetterSize(DMLoad_TD[1], 0.914999, 4.080595);
	TextDrawAlignment(DMLoad_TD[1], 1);
	TextDrawColor(DMLoad_TD[1], -1579453953);
	TextDrawSetShadow(DMLoad_TD[1], 0);
	TextDrawSetOutline(DMLoad_TD[1], 0);
	TextDrawBackgroundColor(DMLoad_TD[1], 255);
	TextDrawFont(DMLoad_TD[1], 2);
	TextDrawSetProportional(DMLoad_TD[1], 1);
	TextDrawSetShadow(DMLoad_TD[1], 0);

	DMLoad_TD[2] = TextDrawCreate(196.933258, 149.367004, "Loading_new_DM_Map");
	TextDrawLetterSize(DMLoad_TD[2], 0.505666, 2.616296);
	TextDrawAlignment(DMLoad_TD[2], 1);
	TextDrawColor(DMLoad_TD[2], -1);
	TextDrawSetShadow(DMLoad_TD[2], 0);
	TextDrawSetOutline(DMLoad_TD[2], 0);
	TextDrawBackgroundColor(DMLoad_TD[2], 255);
	TextDrawFont(DMLoad_TD[2], 2);
	TextDrawSetProportional(DMLoad_TD[2], 1);
	TextDrawSetShadow(DMLoad_TD[2], 0);

	DMLoad_TD[3] = TextDrawCreate(173.333312, 221.008895, "Author:");
	TextDrawLetterSize(DMLoad_TD[3], 0.400000, 1.600000);
	TextDrawAlignment(DMLoad_TD[3], 1);
	TextDrawColor(DMLoad_TD[3], -1);
	TextDrawSetShadow(DMLoad_TD[3], 0);
	TextDrawSetOutline(DMLoad_TD[3], 0);
	TextDrawBackgroundColor(DMLoad_TD[3], 255);
	TextDrawFont(DMLoad_TD[3], 1);
	TextDrawSetProportional(DMLoad_TD[3], 1);
	TextDrawSetShadow(DMLoad_TD[3], 0);

	DMLoad_TD[4] = TextDrawCreate(225.206527, 221.187774, "Jonny_ft._Xer0_ft._SoundwaveZ");
	TextDrawLetterSize(DMLoad_TD[4], 0.271666, 1.575111);
	TextDrawAlignment(DMLoad_TD[4], 1);
	TextDrawColor(DMLoad_TD[4], -1579453953);
	TextDrawSetShadow(DMLoad_TD[4], 0);
	TextDrawSetOutline(DMLoad_TD[4], 0);
	TextDrawBackgroundColor(DMLoad_TD[4], 255);
	TextDrawFont(DMLoad_TD[4], 1);
	TextDrawSetProportional(DMLoad_TD[4], 1);
	TextDrawSetShadow(DMLoad_TD[4], 0);

	DMLoad_TD[5] = TextDrawCreate(173.333312, 238.809982, "Mapname:");
	TextDrawLetterSize(DMLoad_TD[5], 0.400000, 1.600000);
	TextDrawAlignment(DMLoad_TD[5], 1);
	TextDrawColor(DMLoad_TD[5], -1);
	TextDrawSetShadow(DMLoad_TD[5], 0);
	TextDrawSetOutline(DMLoad_TD[5], 0);
	TextDrawBackgroundColor(DMLoad_TD[5], 255);
	TextDrawFont(DMLoad_TD[5], 1);
	TextDrawSetProportional(DMLoad_TD[5], 1);
	TextDrawSetShadow(DMLoad_TD[5], 0);

	DMLoad_TD[6] = TextDrawCreate(242.637542, 238.809982, "(DM)_Jonny_ft._Xer0_ft._SoundwaveZ_-_Among_The_Mountains_III");
	TextDrawLetterSize(DMLoad_TD[6], 0.271666, 1.575111);
	TextDrawAlignment(DMLoad_TD[6], 1);
	TextDrawColor(DMLoad_TD[6], -1579453953);
	TextDrawSetShadow(DMLoad_TD[6], 0);
	TextDrawSetOutline(DMLoad_TD[6], 0);
	TextDrawBackgroundColor(DMLoad_TD[6], 255);
	TextDrawFont(DMLoad_TD[6], 1);
	TextDrawSetProportional(DMLoad_TD[6], 1);
	TextDrawSetShadow(DMLoad_TD[6], 0);

	DMLoad_TD[7] = TextDrawCreate(111.999961, 311.540802, "_______________________________0");
	TextDrawLetterSize(DMLoad_TD[7], 0.400000, 1.600000);
	TextDrawTextSize(DMLoad_TD[7], 109.369438, 0.000000);
	TextDrawAlignment(DMLoad_TD[7], 1);
	TextDrawColor(DMLoad_TD[7], -1);
	TextDrawUseBox(DMLoad_TD[7], 1);
	TextDrawBoxColor(DMLoad_TD[7], 336860415);
	TextDrawSetShadow(DMLoad_TD[7], 0);
	TextDrawSetOutline(DMLoad_TD[7], 0);
	TextDrawBackgroundColor(DMLoad_TD[7], 255);
	TextDrawFont(DMLoad_TD[7], 1);
	TextDrawSetProportional(DMLoad_TD[7], 1);
	TextDrawSetShadow(DMLoad_TD[7], 0);
	return 1;
}

stock CreateServerTopTimeLabel()
{
	TopTime_TD[0] = TextDrawCreate(493.999969, 176.725952, "box");
	TextDrawLetterSize(TopTime_TD[0], 0.000000, 9.566666);
	TextDrawTextSize(TopTime_TD[0], 629.000000, 0.000000);
	TextDrawAlignment(TopTime_TD[0], 1);
	TextDrawColor(TopTime_TD[0], -1);
	TextDrawUseBox(TopTime_TD[0], 1);
	TextDrawBoxColor(TopTime_TD[0], 80);
	TextDrawSetShadow(TopTime_TD[0], 0);
	TextDrawSetOutline(TopTime_TD[0], 0);
	TextDrawBackgroundColor(TopTime_TD[0], 255);
	TextDrawFont(TopTime_TD[0], 1);
	TextDrawSetProportional(TopTime_TD[0], 1);
	TextDrawSetShadow(TopTime_TD[0], 0);

	TopTime_TD[1] = TextDrawCreate(494.033325, 176.840744, "box");
	TextDrawLetterSize(TopTime_TD[1], 0.000000, -0.004666);
	TextDrawTextSize(TopTime_TD[1], 628.600585, 0.000000);
	TextDrawAlignment(TopTime_TD[1], 1);
	TextDrawColor(TopTime_TD[1], -1);
	TextDrawUseBox(TopTime_TD[1], 1);
	TextDrawBoxColor(TopTime_TD[1], -1579453953);
	TextDrawSetShadow(TopTime_TD[1], 0);
	TextDrawSetOutline(TopTime_TD[1], 0);
	TextDrawBackgroundColor(TopTime_TD[1], 255);
	TextDrawFont(TopTime_TD[1], 1);
	TextDrawSetProportional(TopTime_TD[1], 1);
	TextDrawSetShadow(TopTime_TD[1], 0);

	TopTime_TD[2] = TextDrawCreate(496.500091, 178.385131, "#");
	TextDrawLetterSize(TopTime_TD[2], 0.177999, 1.039999);
	TextDrawAlignment(TopTime_TD[2], 1);
	TextDrawColor(TopTime_TD[2], -1);
	TextDrawSetShadow(TopTime_TD[2], 0);
	TextDrawSetOutline(TopTime_TD[2], 0);
	TextDrawBackgroundColor(TopTime_TD[2], 255);
	TextDrawFont(TopTime_TD[2], 1);
	TextDrawSetProportional(TopTime_TD[2], 1);
	TextDrawSetShadow(TopTime_TD[2], 0);

	TopTime_TD[3] = TextDrawCreate(494.799987, 189.285797, "1st");
	TextDrawLetterSize(TopTime_TD[3], 0.177999, 1.039999);
	TextDrawAlignment(TopTime_TD[3], 1);
	TextDrawColor(TopTime_TD[3], -1);
	TextDrawSetShadow(TopTime_TD[3], 0);
	TextDrawSetOutline(TopTime_TD[3], 0);
	TextDrawBackgroundColor(TopTime_TD[3], 255);
	TextDrawFont(TopTime_TD[3], 1);
	TextDrawSetProportional(TopTime_TD[3], 1);
	TextDrawSetShadow(TopTime_TD[3], 0);

	TopTime_TD[4] = TextDrawCreate(494.799987, 198.386352, "2nd");
	TextDrawLetterSize(TopTime_TD[4], 0.177999, 1.039999);
	TextDrawAlignment(TopTime_TD[4], 1);
	TextDrawColor(TopTime_TD[4], -1);
	TextDrawSetShadow(TopTime_TD[4], 0);
	TextDrawSetOutline(TopTime_TD[4], 0);
	TextDrawBackgroundColor(TopTime_TD[4], 255);
	TextDrawFont(TopTime_TD[4], 1);
	TextDrawSetProportional(TopTime_TD[4], 1);
	TextDrawSetShadow(TopTime_TD[4], 0);

	TopTime_TD[5] = TextDrawCreate(494.799987, 207.586914, "3rd");
	TextDrawLetterSize(TopTime_TD[5], 0.177999, 1.039999);
	TextDrawAlignment(TopTime_TD[5], 1);
	TextDrawColor(TopTime_TD[5], -1);
	TextDrawSetShadow(TopTime_TD[5], 0);
	TextDrawSetOutline(TopTime_TD[5], 0);
	TextDrawBackgroundColor(TopTime_TD[5], 255);
	TextDrawFont(TopTime_TD[5], 1);
	TextDrawSetProportional(TopTime_TD[5], 1);
	TextDrawSetShadow(TopTime_TD[5], 0);

	TopTime_TD[6] = TextDrawCreate(494.799987, 216.787475, "4th");
	TextDrawLetterSize(TopTime_TD[6], 0.177999, 1.039999);
	TextDrawAlignment(TopTime_TD[6], 1);
	TextDrawColor(TopTime_TD[6], -1);
	TextDrawSetShadow(TopTime_TD[6], 0);
	TextDrawSetOutline(TopTime_TD[6], 0);
	TextDrawBackgroundColor(TopTime_TD[6], 255);
	TextDrawFont(TopTime_TD[6], 1);
	TextDrawSetProportional(TopTime_TD[6], 1);
	TextDrawSetShadow(TopTime_TD[6], 0);

	TopTime_TD[7] = TextDrawCreate(494.799987, 225.788024, "5th");
	TextDrawLetterSize(TopTime_TD[7], 0.177999, 1.039999);
	TextDrawAlignment(TopTime_TD[7], 1);
	TextDrawColor(TopTime_TD[7], -1);
	TextDrawSetShadow(TopTime_TD[7], 0);
	TextDrawSetOutline(TopTime_TD[7], 0);
	TextDrawBackgroundColor(TopTime_TD[7], 255);
	TextDrawFont(TopTime_TD[7], 1);
	TextDrawSetProportional(TopTime_TD[7], 1);
	TextDrawSetShadow(TopTime_TD[7], 0);

	TopTime_TD[8] = TextDrawCreate(494.799987, 235.088592, "6th");
	TextDrawLetterSize(TopTime_TD[8], 0.177999, 1.039999);
	TextDrawAlignment(TopTime_TD[8], 1);
	TextDrawColor(TopTime_TD[8], -1);
	TextDrawSetShadow(TopTime_TD[8], 0);
	TextDrawSetOutline(TopTime_TD[8], 0);
	TextDrawBackgroundColor(TopTime_TD[8], 255);
	TextDrawFont(TopTime_TD[8], 1);
	TextDrawSetProportional(TopTime_TD[8], 1);
	TextDrawSetShadow(TopTime_TD[8], 0);

	TopTime_TD[9] = TextDrawCreate(496.733337, 189.999984, "box");
	TextDrawLetterSize(TopTime_TD[9], 0.000000, -0.298999);
	TextDrawTextSize(TopTime_TD[9], 625.694580, 0.000000);
	TextDrawAlignment(TopTime_TD[9], 1);
	TextDrawColor(TopTime_TD[9], -1);
	TextDrawUseBox(TopTime_TD[9], 1);
	TextDrawBoxColor(TopTime_TD[9], -1);
	TextDrawSetShadow(TopTime_TD[9], 0);
	TextDrawSetOutline(TopTime_TD[9], 0);
	TextDrawBackgroundColor(TopTime_TD[9], 255);
	TextDrawFont(TopTime_TD[9], 1);
	TextDrawSetProportional(TopTime_TD[9], 1);
	TextDrawSetShadow(TopTime_TD[9], 0);

	TopTime_TD[10] = TextDrawCreate(496.733337, 247.403488, "box");
	TextDrawLetterSize(TopTime_TD[10], 0.000000, -0.298999);
	TextDrawTextSize(TopTime_TD[10], 625.694580, 0.000000);
	TextDrawAlignment(TopTime_TD[10], 1);
	TextDrawColor(TopTime_TD[10], -1);
	TextDrawUseBox(TopTime_TD[10], 1);
	TextDrawBoxColor(TopTime_TD[10], -1);
	TextDrawSetShadow(TopTime_TD[10], 0);
	TextDrawSetOutline(TopTime_TD[10], 0);
	TextDrawBackgroundColor(TopTime_TD[10], 255);
	TextDrawFont(TopTime_TD[10], 1);
	TextDrawSetProportional(TopTime_TD[10], 1);
	TextDrawSetShadow(TopTime_TD[10], 0);

	TopTime_TD[11] = TextDrawCreate(608.532348, 249.374008, "Press '2' to hide/show this box.");
	TextDrawLetterSize(TopTime_TD[11], 0.177999, 1.039999);
	TextDrawAlignment(TopTime_TD[11], 3);
	TextDrawColor(TopTime_TD[11], -1579453953);
	TextDrawSetShadow(TopTime_TD[11], 0);
	TextDrawSetOutline(TopTime_TD[11], 0);
	TextDrawBackgroundColor(TopTime_TD[11], 255);
	TextDrawFont(TopTime_TD[11], 1);
	TextDrawSetProportional(TopTime_TD[11], 1);
	TextDrawSetShadow(TopTime_TD[11], 0);

	TopTime_TD[12] = TextDrawCreate(508.600830, 178.285125, "Name");
	TextDrawLetterSize(TopTime_TD[12], 0.177999, 1.039999);
	TextDrawAlignment(TopTime_TD[12], 1);
	TextDrawColor(TopTime_TD[12], -1);
	TextDrawSetShadow(TopTime_TD[12], 0);
	TextDrawSetOutline(TopTime_TD[12], 0);
	TextDrawBackgroundColor(TopTime_TD[12], 255);
	TextDrawFont(TopTime_TD[12], 1);
	TextDrawSetProportional(TopTime_TD[12], 1);
	TextDrawSetShadow(TopTime_TD[12], 0);

	TopTime_TD[13] = TextDrawCreate(508.400817, 189.285797, "=ftw=Jonny");
	TextDrawLetterSize(TopTime_TD[13], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[13], 1);
	TextDrawColor(TopTime_TD[13], -1);
	TextDrawSetShadow(TopTime_TD[13], 0);
	TextDrawSetOutline(TopTime_TD[13], 0);
	TextDrawBackgroundColor(TopTime_TD[13], 255);
	TextDrawFont(TopTime_TD[13], 1);
	TextDrawSetProportional(TopTime_TD[13], 1);
	TextDrawSetShadow(TopTime_TD[13], 0);

	TopTime_TD[14] = TextDrawCreate(508.600830, 198.586364, "ftw.Xer0");
	TextDrawLetterSize(TopTime_TD[14], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[14], 1);
	TextDrawColor(TopTime_TD[14], -1);
	TextDrawSetShadow(TopTime_TD[14], 0);
	TextDrawSetOutline(TopTime_TD[14], 0);
	TextDrawBackgroundColor(TopTime_TD[14], 255);
	TextDrawFont(TopTime_TD[14], 1);
	TextDrawSetProportional(TopTime_TD[14], 1);
	TextDrawSetShadow(TopTime_TD[14], 0);

	TopTime_TD[15] = TextDrawCreate(508.600830, 207.886932, "ftw.F4K3");
	TextDrawLetterSize(TopTime_TD[15], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[15], 1);
	TextDrawColor(TopTime_TD[15], -1);
	TextDrawSetShadow(TopTime_TD[15], 0);
	TextDrawSetOutline(TopTime_TD[15], 0);
	TextDrawBackgroundColor(TopTime_TD[15], 255);
	TextDrawFont(TopTime_TD[15], 1);
	TextDrawSetProportional(TopTime_TD[15], 1);
	TextDrawSetShadow(TopTime_TD[15], 0);

	TopTime_TD[16] = TextDrawCreate(508.600830, 216.387451, "[j4F]pandi");
	TextDrawLetterSize(TopTime_TD[16], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[16], 1);
	TextDrawColor(TopTime_TD[16], -1);
	TextDrawSetShadow(TopTime_TD[16], 0);
	TextDrawSetOutline(TopTime_TD[16], 0);
	TextDrawBackgroundColor(TopTime_TD[16], 255);
	TextDrawFont(TopTime_TD[16], 1);
	TextDrawSetProportional(TopTime_TD[16], 1);
	TextDrawSetShadow(TopTime_TD[16], 0);

	TopTime_TD[17] = TextDrawCreate(508.600830, 225.988037, "ftw.SilveR");
	TextDrawLetterSize(TopTime_TD[17], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[17], 1);
	TextDrawColor(TopTime_TD[17], -1);
	TextDrawSetShadow(TopTime_TD[17], 0);
	TextDrawSetOutline(TopTime_TD[17], 0);
	TextDrawBackgroundColor(TopTime_TD[17], 255);
	TextDrawFont(TopTime_TD[17], 1);
	TextDrawSetProportional(TopTime_TD[17], 1);
	TextDrawSetShadow(TopTime_TD[17], 0);

	TopTime_TD[18] = TextDrawCreate(508.600830, 234.988586, "ftw.XectioN");
	TextDrawLetterSize(TopTime_TD[18], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[18], 1);
	TextDrawColor(TopTime_TD[18], -1);
	TextDrawSetShadow(TopTime_TD[18], 0);
	TextDrawSetOutline(TopTime_TD[18], 0);
	TextDrawBackgroundColor(TopTime_TD[18], 255);
	TextDrawFont(TopTime_TD[18], 1);
	TextDrawSetProportional(TopTime_TD[18], 1);
	TextDrawSetShadow(TopTime_TD[18], 0);

	TopTime_TD[19] = TextDrawCreate(574.485778, 178.285125, "Time");
	TextDrawLetterSize(TopTime_TD[19], 0.177999, 1.039999);
	TextDrawAlignment(TopTime_TD[19], 3);
	TextDrawColor(TopTime_TD[19], -1);
	TextDrawSetShadow(TopTime_TD[19], 0);
	TextDrawSetOutline(TopTime_TD[19], 0);
	TextDrawBackgroundColor(TopTime_TD[19], 255);
	TextDrawFont(TopTime_TD[19], 1);
	TextDrawSetProportional(TopTime_TD[19], 1);
	TextDrawSetShadow(TopTime_TD[19], 0);

	TopTime_TD[20] = TextDrawCreate(588.482360, 189.285797, "00:00.000");
	TextDrawLetterSize(TopTime_TD[20], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[20], 3);
	TextDrawColor(TopTime_TD[20], -1);
	TextDrawSetShadow(TopTime_TD[20], 0);
	TextDrawSetOutline(TopTime_TD[20], 0);
	TextDrawBackgroundColor(TopTime_TD[20], 255);
	TextDrawFont(TopTime_TD[20], 1);
	TextDrawSetProportional(TopTime_TD[20], 1);
	TextDrawSetShadow(TopTime_TD[20], 0);

	TopTime_TD[21] = TextDrawCreate(588.349243, 198.486358, "00:00.000");
	TextDrawLetterSize(TopTime_TD[21], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[21], 3);
	TextDrawColor(TopTime_TD[21], -1);
	TextDrawSetShadow(TopTime_TD[21], 0);
	TextDrawSetOutline(TopTime_TD[21], 0);
	TextDrawBackgroundColor(TopTime_TD[21], 255);
	TextDrawFont(TopTime_TD[21], 1);
	TextDrawSetProportional(TopTime_TD[21], 1);
	TextDrawSetShadow(TopTime_TD[21], 0);

	TopTime_TD[22] = TextDrawCreate(588.382385, 207.786926, "00:00.000");
	TextDrawLetterSize(TopTime_TD[22], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[22], 3);
	TextDrawColor(TopTime_TD[22], -1);
	TextDrawSetShadow(TopTime_TD[22], 0);
	TextDrawSetOutline(TopTime_TD[22], 0);
	TextDrawBackgroundColor(TopTime_TD[22], 255);
	TextDrawFont(TopTime_TD[22], 1);
	TextDrawSetProportional(TopTime_TD[22], 1);
	TextDrawSetShadow(TopTime_TD[22], 0);

	TopTime_TD[23] = TextDrawCreate(588.082458, 216.387451, "00:00.000");
	TextDrawLetterSize(TopTime_TD[23], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[23], 3);
	TextDrawColor(TopTime_TD[23], -1);
	TextDrawSetShadow(TopTime_TD[23], 0);
	TextDrawSetOutline(TopTime_TD[23], 0);
	TextDrawBackgroundColor(TopTime_TD[23], 255);
	TextDrawFont(TopTime_TD[23], 1);
	TextDrawSetProportional(TopTime_TD[23], 1);
	TextDrawSetShadow(TopTime_TD[23], 0);

	TopTime_TD[24] = TextDrawCreate(588.382385, 225.888031, "00:00.000");
	TextDrawLetterSize(TopTime_TD[24], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[24], 3);
	TextDrawColor(TopTime_TD[24], -1);
	TextDrawSetShadow(TopTime_TD[24], 0);
	TextDrawSetOutline(TopTime_TD[24], 0);
	TextDrawBackgroundColor(TopTime_TD[24], 255);
	TextDrawFont(TopTime_TD[24], 1);
	TextDrawSetProportional(TopTime_TD[24], 1);
	TextDrawSetShadow(TopTime_TD[24], 0);

	TopTime_TD[25] = TextDrawCreate(588.482360, 234.788574, "00:00.000");
	TextDrawLetterSize(TopTime_TD[25], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[25], 3);
	TextDrawColor(TopTime_TD[25], -1);
	TextDrawSetShadow(TopTime_TD[25], 0);
	TextDrawSetOutline(TopTime_TD[25], 0);
	TextDrawBackgroundColor(TopTime_TD[25], 255);
	TextDrawFont(TopTime_TD[25], 1);
	TextDrawSetProportional(TopTime_TD[25], 1);
	TextDrawSetShadow(TopTime_TD[25], 0);

	TopTime_TD[26] = TextDrawCreate(627.072937, 178.285125, "Date");
	TextDrawLetterSize(TopTime_TD[26], 0.177999, 1.039999);
	TextDrawAlignment(TopTime_TD[26], 3);
	TextDrawColor(TopTime_TD[26], -1);
	TextDrawSetShadow(TopTime_TD[26], 0);
	TextDrawSetOutline(TopTime_TD[26], 0);
	TextDrawBackgroundColor(TopTime_TD[26], 255);
	TextDrawFont(TopTime_TD[26], 1);
	TextDrawSetProportional(TopTime_TD[26], 1);
	TextDrawSetShadow(TopTime_TD[26], 0);

	TopTime_TD[27] = TextDrawCreate(627.872741, 189.285797, "00.00.0000");
	TextDrawLetterSize(TopTime_TD[27], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[27], 3);
	TextDrawColor(TopTime_TD[27], -1);
	TextDrawSetShadow(TopTime_TD[27], 0);
	TextDrawSetOutline(TopTime_TD[27], 0);
	TextDrawBackgroundColor(TopTime_TD[27], 255);
	TextDrawFont(TopTime_TD[27], 1);
	TextDrawSetProportional(TopTime_TD[27], 1);
	TextDrawSetShadow(TopTime_TD[27], 0);

	TopTime_TD[28] = TextDrawCreate(627.672790, 198.686370, "00.00.0000");
	TextDrawLetterSize(TopTime_TD[28], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[28], 3);
	TextDrawColor(TopTime_TD[28], -1);
	TextDrawSetShadow(TopTime_TD[28], 0);
	TextDrawSetOutline(TopTime_TD[28], 0);
	TextDrawBackgroundColor(TopTime_TD[28], 255);
	TextDrawFont(TopTime_TD[28], 1);
	TextDrawSetProportional(TopTime_TD[28], 1);
	TextDrawSetShadow(TopTime_TD[28], 0);

	TopTime_TD[29] = TextDrawCreate(627.672790, 207.586914, "00.00.0000");
	TextDrawLetterSize(TopTime_TD[29], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[29], 3);
	TextDrawColor(TopTime_TD[29], -1);
	TextDrawSetShadow(TopTime_TD[29], 0);
	TextDrawSetOutline(TopTime_TD[29], 0);
	TextDrawBackgroundColor(TopTime_TD[29], 255);
	TextDrawFont(TopTime_TD[29], 1);
	TextDrawSetProportional(TopTime_TD[29], 1);
	TextDrawSetShadow(TopTime_TD[29], 0);

	TopTime_TD[30] = TextDrawCreate(627.672790, 216.287445, "00.00.0000");
	TextDrawLetterSize(TopTime_TD[30], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[30], 3);
	TextDrawColor(TopTime_TD[30], -1);
	TextDrawSetShadow(TopTime_TD[30], 0);
	TextDrawSetOutline(TopTime_TD[30], 0);
	TextDrawBackgroundColor(TopTime_TD[30], 255);
	TextDrawFont(TopTime_TD[30], 1);
	TextDrawSetProportional(TopTime_TD[30], 1);
	TextDrawSetShadow(TopTime_TD[30], 0);

	TopTime_TD[31] = TextDrawCreate(627.672790, 225.888031, "00.00.0000");
	TextDrawLetterSize(TopTime_TD[31], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[31], 3);
	TextDrawColor(TopTime_TD[31], -1);
	TextDrawSetShadow(TopTime_TD[31], 0);
	TextDrawSetOutline(TopTime_TD[31], 0);
	TextDrawBackgroundColor(TopTime_TD[31], 255);
	TextDrawFont(TopTime_TD[31], 1);
	TextDrawSetProportional(TopTime_TD[31], 1);
	TextDrawSetShadow(TopTime_TD[31], 0);

	TopTime_TD[32] = TextDrawCreate(627.339477, 234.988586, "00.00.0000");
	TextDrawLetterSize(TopTime_TD[32], 0.147666, 1.039999);
	TextDrawAlignment(TopTime_TD[32], 3);
	TextDrawColor(TopTime_TD[32], -1);
	TextDrawSetShadow(TopTime_TD[32], 0);
	TextDrawSetOutline(TopTime_TD[32], 0);
	TextDrawBackgroundColor(TopTime_TD[32], 255);
	TextDrawFont(TopTime_TD[32], 1);
	TextDrawSetProportional(TopTime_TD[32], 1);
	TextDrawSetShadow(TopTime_TD[32], 0);
	return 1;
}

stock CreateServerClanWarLabel()
{
	ClanWar_TD[0] = TextDrawCreate(495.000061, 176.311096, "box");
	TextDrawLetterSize(ClanWar_TD[0], 0.000000, 15.266683);
	TextDrawTextSize(ClanWar_TD[0], 624.000000, 0.000000);
	TextDrawAlignment(ClanWar_TD[0], 1);
	TextDrawColor(ClanWar_TD[0], -1);
	TextDrawUseBox(ClanWar_TD[0], 1);
	TextDrawBoxColor(ClanWar_TD[0], 80);
	TextDrawSetShadow(ClanWar_TD[0], 0);
	TextDrawSetOutline(ClanWar_TD[0], 0);
	TextDrawBackgroundColor(ClanWar_TD[0], 255);
	TextDrawFont(ClanWar_TD[0], 1);
	TextDrawSetProportional(ClanWar_TD[0], 1);
	TextDrawSetShadow(ClanWar_TD[0], 0);

	ClanWar_TD[1] = TextDrawCreate(494.833343, 176.311111, "box");
	TextDrawLetterSize(ClanWar_TD[1], 0.000000, 0.047333);
	TextDrawTextSize(ClanWar_TD[1], 623.850830, 0.000000);
	TextDrawAlignment(ClanWar_TD[1], 1);
	TextDrawColor(ClanWar_TD[1], -1);
	TextDrawUseBox(ClanWar_TD[1], 1);
	TextDrawBoxColor(ClanWar_TD[1], -1579453953);
	TextDrawSetShadow(ClanWar_TD[1], 0);
	TextDrawSetOutline(ClanWar_TD[1], 0);
	TextDrawBackgroundColor(ClanWar_TD[1], 255);
	TextDrawFont(ClanWar_TD[1], 1);
	TextDrawSetProportional(ClanWar_TD[1], 1);
	TextDrawSetShadow(ClanWar_TD[1], 0);

	ClanWar_TD[2] = TextDrawCreate(497.200042, 180.403656, "~y~Team1");
	TextDrawLetterSize(ClanWar_TD[2], 0.235000, 1.056592);
	TextDrawAlignment(ClanWar_TD[2], 1);
	TextDrawColor(ClanWar_TD[2], -1);
	TextDrawSetShadow(ClanWar_TD[2], 0);
	TextDrawSetOutline(ClanWar_TD[2], 1);
	TextDrawBackgroundColor(ClanWar_TD[2], 255);
	TextDrawFont(ClanWar_TD[2], 1);
	TextDrawSetProportional(ClanWar_TD[2], 1);
	TextDrawSetShadow(ClanWar_TD[2], 0);

	ClanWar_TD[3] = TextDrawCreate(622.207397, 179.988845, "~y~Team2");
	TextDrawLetterSize(ClanWar_TD[3], 0.235000, 1.056592);
	TextDrawAlignment(ClanWar_TD[3], 3);
	TextDrawColor(ClanWar_TD[3], -1);
	TextDrawSetShadow(ClanWar_TD[3], 0);
	TextDrawSetOutline(ClanWar_TD[3], 1);
	TextDrawBackgroundColor(ClanWar_TD[3], 255);
	TextDrawFont(ClanWar_TD[3], 1);
	TextDrawSetProportional(ClanWar_TD[3], 1);
	TextDrawSetShadow(ClanWar_TD[3], 0);

	ClanWar_TD[4] = TextDrawCreate(559.689270, 180.403656, "VERSUS");
	TextDrawLetterSize(ClanWar_TD[4], 0.235000, 1.056592);
	TextDrawAlignment(ClanWar_TD[4], 2);
	TextDrawColor(ClanWar_TD[4], -1);
	TextDrawSetShadow(ClanWar_TD[4], 0);
	TextDrawSetOutline(ClanWar_TD[4], 1);
	TextDrawBackgroundColor(ClanWar_TD[4], 255);
	TextDrawFont(ClanWar_TD[4], 1);
	TextDrawSetProportional(ClanWar_TD[4], 1);
	TextDrawSetShadow(ClanWar_TD[4], 0);

	ClanWar_TD[5] = TextDrawCreate(498.333282, 192.574081, "box");
	TextDrawLetterSize(ClanWar_TD[5], 0.000000, -0.302999);
	TextDrawTextSize(ClanWar_TD[5], 620.980224, 0.000000);
	TextDrawAlignment(ClanWar_TD[5], 1);
	TextDrawColor(ClanWar_TD[5], -1);
	TextDrawUseBox(ClanWar_TD[5], 1);
	TextDrawBoxColor(ClanWar_TD[5], -1);
	TextDrawSetShadow(ClanWar_TD[5], 0);
	TextDrawSetOutline(ClanWar_TD[5], 0);
	TextDrawBackgroundColor(ClanWar_TD[5], 255);
	TextDrawFont(ClanWar_TD[5], 1);
	TextDrawSetProportional(ClanWar_TD[5], 1);
	TextDrawSetShadow(ClanWar_TD[5], 0);

	ClanWar_TD[6] = TextDrawCreate(497.666656, 190.473999, "0");
	TextDrawLetterSize(ClanWar_TD[6], 0.488333, 2.118519);
	TextDrawAlignment(ClanWar_TD[6], 1);
	TextDrawColor(ClanWar_TD[6], -1);
	TextDrawSetShadow(ClanWar_TD[6], 0);
	TextDrawSetOutline(ClanWar_TD[6], 1);
	TextDrawBackgroundColor(ClanWar_TD[6], 255);
	TextDrawFont(ClanWar_TD[6], 3);
	TextDrawSetProportional(ClanWar_TD[6], 1);
	TextDrawSetShadow(ClanWar_TD[6], 0);

	ClanWar_TD[7] = TextDrawCreate(622.240600, 190.473999, "0");
	TextDrawLetterSize(ClanWar_TD[7], 0.488333, 2.118519);
	TextDrawAlignment(ClanWar_TD[7], 3);
	TextDrawColor(ClanWar_TD[7], -1);
	TextDrawSetShadow(ClanWar_TD[7], 0);
	TextDrawSetOutline(ClanWar_TD[7], 1);
	TextDrawBackgroundColor(ClanWar_TD[7], 255);
	TextDrawFont(ClanWar_TD[7], 3);
	TextDrawSetProportional(ClanWar_TD[7], 1);
	TextDrawSetShadow(ClanWar_TD[7], 0);

	ClanWar_TD[8] = TextDrawCreate(559.955810, 190.473999, "-");
	TextDrawLetterSize(ClanWar_TD[8], 0.488333, 2.118519);
	TextDrawAlignment(ClanWar_TD[8], 2);
	TextDrawColor(ClanWar_TD[8], -1);
	TextDrawSetShadow(ClanWar_TD[8], 0);
	TextDrawSetOutline(ClanWar_TD[8], 1);
	TextDrawBackgroundColor(ClanWar_TD[8], 255);
	TextDrawFont(ClanWar_TD[8], 3);
	TextDrawSetProportional(ClanWar_TD[8], 1);
	TextDrawSetShadow(ClanWar_TD[8], 0);

	ClanWar_TD[9] = TextDrawCreate(498.333282, 212.075271, "box");
	TextDrawLetterSize(ClanWar_TD[9], 0.000000, -0.302999);
	TextDrawTextSize(ClanWar_TD[9], 620.980224, 0.000000);
	TextDrawAlignment(ClanWar_TD[9], 1);
	TextDrawColor(ClanWar_TD[9], -1);
	TextDrawUseBox(ClanWar_TD[9], 1);
	TextDrawBoxColor(ClanWar_TD[9], -1);
	TextDrawSetShadow(ClanWar_TD[9], 0);
	TextDrawSetOutline(ClanWar_TD[9], 0);
	TextDrawBackgroundColor(ClanWar_TD[9], 255);
	TextDrawFont(ClanWar_TD[9], 1);
	TextDrawSetProportional(ClanWar_TD[9], 1);
	TextDrawSetShadow(ClanWar_TD[9], 0);

	ClanWar_TD[10] = TextDrawCreate(497.200042, 212.305603, "");//Team 1 Names
	TextDrawLetterSize(ClanWar_TD[10], 0.162666, 0.923852);
	TextDrawAlignment(ClanWar_TD[10], 1);
	TextDrawColor(ClanWar_TD[10], -1);
	TextDrawSetShadow(ClanWar_TD[10], 0);
	TextDrawSetOutline(ClanWar_TD[10], 1);
	TextDrawBackgroundColor(ClanWar_TD[10], 255);
	TextDrawFont(ClanWar_TD[10], 1);
	TextDrawSetProportional(ClanWar_TD[10], 1);
	TextDrawSetShadow(ClanWar_TD[10], 0);

	ClanWar_TD[11] = TextDrawCreate(621.574157, 212.305603, "");//Team 2 Names
	TextDrawLetterSize(ClanWar_TD[11], 0.162666, 0.923852);
	TextDrawAlignment(ClanWar_TD[11], 3);
	TextDrawColor(ClanWar_TD[11], -1);
	TextDrawSetShadow(ClanWar_TD[11], 0);
	TextDrawSetOutline(ClanWar_TD[11], 1);
	TextDrawBackgroundColor(ClanWar_TD[11], 255);
	TextDrawFont(ClanWar_TD[11], 1);
	TextDrawSetProportional(ClanWar_TD[11], 1);
	TextDrawSetShadow(ClanWar_TD[11], 0);

	ClanWar_TD[12] = TextDrawCreate(562.355895, 304.844665, "Rounds_left:_~y~Select_Map");
	TextDrawLetterSize(ClanWar_TD[12], 0.187665, 0.936294);
	TextDrawAlignment(ClanWar_TD[12], 2);
	TextDrawColor(ClanWar_TD[12], -1);
	TextDrawSetShadow(ClanWar_TD[12], 0);
	TextDrawSetOutline(ClanWar_TD[12], 1);
	TextDrawBackgroundColor(ClanWar_TD[12], 255);
	TextDrawFont(ClanWar_TD[12], 1);
	TextDrawSetProportional(ClanWar_TD[12], 1);
	TextDrawSetShadow(ClanWar_TD[12], 0);
	return 1;
}

stock CreateServerDeathListLabel()
{
	DeathList_TD[0] = TextDrawCreate(2.200177, 325.021911, "4th._~w~ftw.SilveR_~y~(00:00.000)");
	TextDrawLetterSize(DeathList_TD[0], 0.232666, 0.977777);
	TextDrawAlignment(DeathList_TD[0], 1);
	TextDrawColor(DeathList_TD[0], -994329601);
	TextDrawSetShadow(DeathList_TD[0], 0);
	TextDrawSetOutline(DeathList_TD[0], 1);
	TextDrawBackgroundColor(DeathList_TD[0], 255);
	TextDrawFont(DeathList_TD[0], 1);
	TextDrawSetProportional(DeathList_TD[0], 1);
	TextDrawSetShadow(DeathList_TD[0], 0);

	DeathList_TD[1] = TextDrawCreate(2.200177, 314.421264, "3rd._~w~ftw.Xer0_~y~(00:00.000)");
	TextDrawLetterSize(DeathList_TD[1], 0.232666, 0.977777);
	TextDrawAlignment(DeathList_TD[1], 1);
	TextDrawColor(DeathList_TD[1], -1890109441);
	TextDrawSetShadow(DeathList_TD[1], 0);
	TextDrawSetOutline(DeathList_TD[1], 1);
	TextDrawBackgroundColor(DeathList_TD[1], 255);
	TextDrawFont(DeathList_TD[1], 1);
	TextDrawSetProportional(DeathList_TD[1], 1);
	TextDrawSetShadow(DeathList_TD[1], 0);

	DeathList_TD[2] = TextDrawCreate(2.200177, 303.505798, "2nd._~w~=ftw=Jonny_~y~(00:00.000)");
	TextDrawLetterSize(DeathList_TD[2], 0.232666, 0.977777);
	TextDrawAlignment(DeathList_TD[2], 1);
	TextDrawColor(DeathList_TD[2], -1667457793);
	TextDrawSetShadow(DeathList_TD[2], 0);
	TextDrawSetOutline(DeathList_TD[2], 1);
	TextDrawBackgroundColor(DeathList_TD[2], 255);
	TextDrawFont(DeathList_TD[2], 1);
	TextDrawSetProportional(DeathList_TD[2], 1);
	TextDrawSetShadow(DeathList_TD[2], 0);

	DeathList_TD[3] = TextDrawCreate(1.500177, 292.919952, "1st._~w~ftw.F4K3_~y~(00:00.000)");
	TextDrawLetterSize(DeathList_TD[3], 0.232666, 0.977777);
	TextDrawAlignment(DeathList_TD[3], 1);
	TextDrawColor(DeathList_TD[3], -1182855169);
	TextDrawSetShadow(DeathList_TD[3], 0);
	TextDrawSetOutline(DeathList_TD[3], 1);
	TextDrawBackgroundColor(DeathList_TD[3], 255);
	TextDrawFont(DeathList_TD[3], 1);
	TextDrawSetProportional(DeathList_TD[3], 1);
	TextDrawSetShadow(DeathList_TD[3], 0);	
	return 1;
}

stock CreatePlayerMoneyLabel(playerid)
{
	MoneyLabel_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 509.300567, 79.170349, "100000000000");
	PlayerTextDrawLetterSize(playerid, MoneyLabel_PTD[playerid][0], 0.408666, 1.803259);
	PlayerTextDrawAlignment(playerid, MoneyLabel_PTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, MoneyLabel_PTD[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, MoneyLabel_PTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MoneyLabel_PTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MoneyLabel_PTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, MoneyLabel_PTD[playerid][0], 3);
	PlayerTextDrawSetProportional(playerid, MoneyLabel_PTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, MoneyLabel_PTD[playerid][0], 0);
	return 1;
}

stock CreatePlayerSpectatorLabel(playerid)
{
	SPECTATOR_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 234.300292, 424.736297, "box");
	PlayerTextDrawLetterSize(playerid, SPECTATOR_PTD[playerid][0], 0.000000, -5.766664);
	PlayerTextDrawTextSize(playerid, SPECTATOR_PTD[playerid][0], 402.600097, 0.000000);
	PlayerTextDrawAlignment(playerid, SPECTATOR_PTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, SPECTATOR_PTD[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, SPECTATOR_PTD[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, SPECTATOR_PTD[playerid][0], 80);
	PlayerTextDrawSetShadow(playerid, SPECTATOR_PTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, SPECTATOR_PTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, SPECTATOR_PTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, SPECTATOR_PTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, SPECTATOR_PTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, SPECTATOR_PTD[playerid][0], 0);

	SPECTATOR_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 331.266662, 377.692687, "~<~ LMB - RMB ~>~");
	PlayerTextDrawLetterSize(playerid, SPECTATOR_PTD[playerid][1], 0.231997, 1.317924);
	PlayerTextDrawAlignment(playerid, SPECTATOR_PTD[playerid][1], 3);
	PlayerTextDrawColor(playerid, SPECTATOR_PTD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, SPECTATOR_PTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, SPECTATOR_PTD[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, SPECTATOR_PTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, SPECTATOR_PTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, SPECTATOR_PTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, SPECTATOR_PTD[playerid][1], 0);

	SPECTATOR_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 315.765716, 390.893493, "Name:");
	PlayerTextDrawLetterSize(playerid, SPECTATOR_PTD[playerid][2], 0.231997, 1.317924);
	PlayerTextDrawAlignment(playerid, SPECTATOR_PTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, SPECTATOR_PTD[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, SPECTATOR_PTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, SPECTATOR_PTD[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, SPECTATOR_PTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, SPECTATOR_PTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, SPECTATOR_PTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, SPECTATOR_PTD[playerid][2], 0);

	SPECTATOR_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 315.765716, 405.294372, "Vehicle_Health:");
	PlayerTextDrawLetterSize(playerid, SPECTATOR_PTD[playerid][3], 0.231997, 1.317924);
	PlayerTextDrawAlignment(playerid, SPECTATOR_PTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, SPECTATOR_PTD[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, SPECTATOR_PTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, SPECTATOR_PTD[playerid][3], 1);
	PlayerTextDrawBackgroundColor(playerid, SPECTATOR_PTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, SPECTATOR_PTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, SPECTATOR_PTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, SPECTATOR_PTD[playerid][3], 0);
	return 1;
}

stock CreatePlayerRegLogLabel(playerid)
{
	RegLog_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 176.866836, 70.070610, "Project_Apollo");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][0], 0.784331, 3.802664);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][0], -1579453953);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][0], 0);

	RegLog_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 140.866821, 154.325973, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][1], 0.000000, 23.899999);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][1], 296.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][1], 85);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][1], 0);

	RegLog_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 140.983444, 154.325988, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][2], 0.000000, 0.033332);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][2], 296.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][2], -1579453953);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][2], 0);

	RegLog_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 216.350418, 156.814895, "Account_credentials");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][3], 0.250333, 1.176887);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][3], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][3], 0);

	RegLog_PTD[playerid][4] = CreatePlayerTextDraw(playerid, 140.983444, 171.327026, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][4], 0.000000, -0.300000);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][4], 296.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][4], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][4], 0);

	RegLog_PTD[playerid][5] = CreatePlayerTextDraw(playerid, 216.050399, 171.524932, "Your_Username");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][5], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][5], 2);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][5], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][5], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][5], 0);

	RegLog_PTD[playerid][6] = CreatePlayerTextDraw(playerid, 143.466812, 183.451736, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][6], 0.000000, 1.299998);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][6], 293.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][6], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][6], 84215295);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][6], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][6], 0);

	RegLog_PTD[playerid][7] = CreatePlayerTextDraw(playerid, 144.766754, 184.843368, "ApolloCrews");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][7], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][7], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][7], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][7], 0);

	RegLog_PTD[playerid][8] = CreatePlayerTextDraw(playerid, 216.050399, 198.776596, "Your_Password");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][8], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][8], 2);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][8], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][8], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][8], 0);

	RegLog_PTD[playerid][9] = CreatePlayerTextDraw(playerid, 143.466812, 210.553390, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][9], 0.000000, 1.299998);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][9], 293.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][9], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][9], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][9], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][9], 84215295);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][9], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][9], 0);

	RegLog_PTD[playerid][10] = CreatePlayerTextDraw(playerid, 144.766754, 212.345046, "]]]]]");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][10], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][10], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][10], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][10], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][10], 2);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][10], 0);

	RegLog_PTD[playerid][11] = CreatePlayerTextDraw(playerid, 245.683151, 50.929866, "Welcome_to");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][11], 0.589999, 3.176517);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][11], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][11], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][11], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][11], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][11], 2);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][11], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][11], 0);

	RegLog_PTD[playerid][12] = CreatePlayerTextDraw(playerid, 216.350418, 231.369445, "Account_statistics");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][12], 0.250333, 1.176887);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][12], 2);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][12], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][12], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][12], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][12], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][12], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][12], 0);

	RegLog_PTD[playerid][13] = CreatePlayerTextDraw(playerid, 140.983444, 245.330093, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][13], 0.000000, -0.300000);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][13], 296.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][13], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][13], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][13], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][13], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][13], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][13], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][13], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][13], 0);

	RegLog_PTD[playerid][14] = CreatePlayerTextDraw(playerid, 142.383728, 247.021209, "Status");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][14], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][14], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][14], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][14], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][14], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][14], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][14], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][14], 0);

	RegLog_PTD[playerid][15] = CreatePlayerTextDraw(playerid, 143.800125, 258.912597, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][15], 0.000000, 1.299998);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][15], 223.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][15], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][15], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][15], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][15], 84215295);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][15], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][15], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][15], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][15], 0);

	RegLog_PTD[playerid][16] = CreatePlayerTextDraw(playerid, 144.383743, 260.070678, "~r~unregistered");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][16], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][16], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][16], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][16], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][16], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][16], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][16], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][16], 0);

	RegLog_PTD[playerid][17] = CreatePlayerTextDraw(playerid, 142.383728, 274.664306, "Money");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][17], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][17], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][17], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][17], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][17], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][17], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][17], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][17], 0);

	RegLog_PTD[playerid][18] = CreatePlayerTextDraw(playerid, 143.800125, 287.405639, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][18], 0.000000, 1.299998);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][18], 223.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][18], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][18], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][18], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][18], 84215295);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][18], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][18], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][18], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][18], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][18], 0);

	RegLog_PTD[playerid][19] = CreatePlayerTextDraw(playerid, 144.383743, 288.813659, "~g~$100.000.000.000");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][19], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][19], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][19], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][19], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][19], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][19], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][19], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][19], 0);

	RegLog_PTD[playerid][20] = CreatePlayerTextDraw(playerid, 142.383728, 302.957397, "Clan");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][20], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][20], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][20], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][20], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][20], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][20], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][20], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][20], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][20], 0);

	RegLog_PTD[playerid][21] = CreatePlayerTextDraw(playerid, 143.800125, 315.248840, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][21], 0.000000, 1.299998);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][21], 223.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][21], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][21], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][21], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][21], 84215295);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][21], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][21], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][21], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][21], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][21], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][21], 0);

	RegLog_PTD[playerid][22] = CreatePlayerTextDraw(playerid, 144.383743, 316.756835, "~p~ABZDEFGHIJKLMN");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][22], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][22], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][22], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][22], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][22], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][22], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][22], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][22], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][22], 0);

	RegLog_PTD[playerid][23] = CreatePlayerTextDraw(playerid, 235.139404, 247.021209, "Account_N");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][23], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][23], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][23], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][23], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][23], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][23], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][23], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][23], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][23], 0);

	RegLog_PTD[playerid][24] = CreatePlayerTextDraw(playerid, 234.851348, 258.948974, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][24], 0.000000, 1.299998);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][24], 293.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][24], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][24], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][24], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][24], 84215295);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][24], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][24], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][24], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][24], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][24], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][24], 0);

	RegLog_PTD[playerid][25] = CreatePlayerTextDraw(playerid, 236.050521, 260.377136, "3452");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][25], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][25], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][25], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][25], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][25], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][25], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][25], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][25], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][25], 0);

	RegLog_PTD[playerid][26] = CreatePlayerTextDraw(playerid, 235.139404, 274.314392, "Join_Date");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][26], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][26], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][26], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][26], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][26], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][26], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][26], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][26], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][26], 0);

	RegLog_PTD[playerid][27] = CreatePlayerTextDraw(playerid, 234.851348, 287.342041, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][27], 0.000000, 1.299998);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][27], 293.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][27], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][27], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][27], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][27], 84215295);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][27], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][27], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][27], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][27], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][27], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][27], 0);

	RegLog_PTD[playerid][28] = CreatePlayerTextDraw(playerid, 235.139404, 303.057373, "Achievements");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][28], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][28], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][28], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][28], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][28], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][28], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][28], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][28], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][28], 0);

	RegLog_PTD[playerid][29] = CreatePlayerTextDraw(playerid, 234.851348, 315.285217, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][29], 0.000000, 1.299998);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][29], 293.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][29], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][29], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][29], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][29], 84215295);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][29], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][29], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][29], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][29], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][29], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][29], 0);

	RegLog_PTD[playerid][30] = CreatePlayerTextDraw(playerid, 236.200454, 316.821746, "~y~0/64");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][30], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][30], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][30], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][30], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][30], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][30], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][30], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][30], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][30], 0);

	RegLog_PTD[playerid][31] = CreatePlayerTextDraw(playerid, 140.983444, 334.758087, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][31], 0.000000, -0.300000);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][31], 296.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][31], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][31], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][31], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][31], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][31], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][31], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][31], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][31], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][31], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][31], 0);

	RegLog_PTD[playerid][32] = CreatePlayerTextDraw(playerid, 150.184646, 340.888946, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][32], 0.000000, 2.366667);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][32], 200.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][32], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][32], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][32], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][32], 84215295);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][32], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][32], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][32], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][32], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][32], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][32], 0);

	RegLog_PTD[playerid][33] = CreatePlayerTextDraw(playerid, 153.466705, 345.030975, "Continue");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][33], 0.276333, 1.288889);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][33], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][33], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][33], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][33], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][33], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][33], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][33], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][33], 0);
	PlayerTextDrawSetSelectable(playerid, RegLog_PTD[playerid][33], true);

	RegLog_PTD[playerid][34] = CreatePlayerTextDraw(playerid, 239.118606, 340.973968, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][34], 0.000000, 2.366667);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][34], 287.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][34], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][34], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][34], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][34], 84215295);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][34], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][34], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][34], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][34], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][34], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][34], 0);

	RegLog_PTD[playerid][35] = CreatePlayerTextDraw(playerid, 248.572509, 345.030975, "Cancel");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][35], 0.276333, 1.288889);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][35], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][35], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][35], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][35], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][35], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][35], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][35], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][35], 0);
	PlayerTextDrawSetSelectable(playerid, RegLog_PTD[playerid][35], true);

	RegLog_PTD[playerid][36] = CreatePlayerTextDraw(playerid, 363.467559, 154.161102, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][36], 0.000000, 23.899999);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][36], 518.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][36], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][36], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][36], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][36], 85);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][36], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][36], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][36], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][36], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][36], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][36], 0);

	RegLog_PTD[playerid][37] = CreatePlayerTextDraw(playerid, 363.483551, 154.175994, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][37], 0.000000, 0.071998);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][37], 517.970947, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][37], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][37], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][37], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][37], -1579453953);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][37], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][37], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][37], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][37], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][37], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][37], 0);

	RegLog_PTD[playerid][38] = CreatePlayerTextDraw(playerid, 438.601531, 156.755691, "Server_statistics");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][38], 0.250333, 1.176887);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][38], 2);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][38], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][38], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][38], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][38], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][38], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][38], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][38], 0);

	RegLog_PTD[playerid][39] = CreatePlayerTextDraw(playerid, 363.667205, 171.491867, "box");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][39], 0.000000, -0.300000);
	PlayerTextDrawTextSize(playerid, RegLog_PTD[playerid][39], 517.842346, 0.000000);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][39], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][39], -1);
	PlayerTextDrawUseBox(playerid, RegLog_PTD[playerid][39], 1);
	PlayerTextDrawBoxColor(playerid, RegLog_PTD[playerid][39], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][39], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][39], 0);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][39], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][39], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][39], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][39], 0);

	RegLog_PTD[playerid][40] = CreatePlayerTextDraw(playerid, 236.050521, 288.878875, "00.00.0000");
	PlayerTextDrawLetterSize(playerid, RegLog_PTD[playerid][40], 0.217666, 0.936294);
	PlayerTextDrawAlignment(playerid, RegLog_PTD[playerid][40], 1);
	PlayerTextDrawColor(playerid, RegLog_PTD[playerid][40], -1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][40], 0);
	PlayerTextDrawSetOutline(playerid, RegLog_PTD[playerid][40], 1);
	PlayerTextDrawBackgroundColor(playerid, RegLog_PTD[playerid][40], 255);
	PlayerTextDrawFont(playerid, RegLog_PTD[playerid][40], 1);
	PlayerTextDrawSetProportional(playerid, RegLog_PTD[playerid][40], 1);
	PlayerTextDrawSetShadow(playerid, RegLog_PTD[playerid][40], 0);
	return 1;
}