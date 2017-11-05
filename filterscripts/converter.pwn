#pragma dynamic 100000

#include <a_samp>
#include <ocmd>
#include <sscanf2>
#include <streamer>
#include <xml>
#include <Directory>
#include <filemanager>
#include <dini>
#include <crashdetect>

enum {
	DIALOG_DMMAPS = 0
}

public OnFilterScriptInit()
{
	print("\n-------------------------------------");
	print(" Map Converter by =ftw=Jonny.");
	print("\n-------------------------------------");
	return 1;
}

public OnFilterScriptExit()
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

ocmd:convert(playerid, params[])
{
	new dir:dHandle, item[64], type;
	new string[1024];

    dHandle = dir_open("./scriptfiles/maps");

	while (dir_list(dHandle, item, type))
	{
	    format(string, sizeof(string), "\
		%s\n%s", string, item);
	}

	ShowPlayerDialog(playerid, DIALOG_DMMAPS, DIALOG_STYLE_LIST, "Converting Maps", string, "Convert", "Cancel");

	dir_close(dHandle);
	return true;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == DIALOG_DMMAPS)
	{
		new dir:dhandel, item[512], type, idx, XML:xml, xml_path[264];

		new tmp_mapname[164], file[264], newfile[264], dir:fHandle, nmap[164];
		//new convert_read[300][1024], convert_count;
		new tmp_author[164], tmp_version[24], tmp_hours, tmp_minutes, tmp_weather;
		new f_path[364], fc_path[164], w_string[1024], collision[10];
		new File:convertfile, convert_path[128];

        dhandel = dir_open("./scriptfiles/maps");

		while (dir_list(dhandel, item, type))
		{
			if (idx == listitem)
			{
	            format(xml_path, sizeof(xml_path), "/maps/%s/meta.xml", item);

	            xml = xml_open(xml_path);
	            xml_get_string(xml, "meta/info/@name", tmp_mapname);

				if (strfind(tmp_mapname, "[DM] ", true) != -1)
				{
		            strmid(tmp_mapname, tmp_mapname, strfind(tmp_mapname, "[DM]")+4, sizeof(tmp_mapname));

		            RemoveSpecialCharacter(tmp_mapname);

					format(nmap, sizeof(nmap), "(DM) %s", tmp_mapname);
		            format(tmp_mapname, sizeof(tmp_mapname), "maps/(DM)%s", tmp_mapname);
		        }
		        else if (strfind(tmp_mapname, "[DM]", true) != -1)
		        {
       				strmid(tmp_mapname, tmp_mapname, strfind(tmp_mapname, "[DM]")+4, sizeof(tmp_mapname));

       				RemoveSpecialCharacter(tmp_mapname);

					format(nmap, sizeof(nmap), "(DM) %s", tmp_mapname);
		            format(tmp_mapname, sizeof(tmp_mapname), "maps/(DM) %s", tmp_mapname);
		        }
		        else if (strfind(tmp_mapname, "[DM]", true) == -1)
		        {
       				RemoveSpecialCharacter(tmp_mapname);

					format(nmap, sizeof(nmap), "(DM) %s", tmp_mapname);
		            format(tmp_mapname, sizeof(tmp_mapname), "maps/(DM) %s", tmp_mapname);
		        }
		        else if (strfind(tmp_mapname, "[DM] ", true) == -1)
		        {
       				RemoveSpecialCharacter(tmp_mapname);

					format(nmap, sizeof(nmap), "(DM) %s", tmp_mapname);
		            format(tmp_mapname, sizeof(tmp_mapname), "maps/%s", tmp_mapname);
		        }

				format(item, sizeof(item), "maps/%s", item);
	            rename(item, tmp_mapname);
	            xml_close(xml);

	            format(xml_path, sizeof(xml_path), "/%s/meta.xml", tmp_mapname);

	            format(file, sizeof(file), "./scriptfiles/%s", tmp_mapname);
				fHandle = dir_open(file);

				print("Continue here!");

				while (dir_list(fHandle, item, type))
				{
					if (strfind(item, ".map", true) != -1)
					{
						print(".map found");

						new r_string[128];

						if (strfind(item, "objects.map", true) == -1) {
							format(r_string, sizeof(r_string), "%s/%s", tmp_mapname, item);
							format(newfile, sizeof(newfile), "%s/objects.map", tmp_mapname);
							rename(r_string, newfile);
							continue;
						}


						print(tmp_mapname);
						format(f_path, sizeof(f_path), "%s/%s", tmp_mapname, item);
						print(f_path);

				  	    new File:chandle = fopen(f_path, io_read);

				  	    new m_type[15], m_color[15], Float:pX[1000], Float:pY[1000], Float:pZ[1000];
				  	    new obj_id[10000], interior[10000], count = 0, obj_create[1024], Float:posX[10000], Float:posY[10000], Float:posZ[10000],
				  	    												Float:rotX[10000], Float:rotY[10000], Float:rotZ[10000];

				  	    if (chandle)
				  	    {
				  	    	new Float:scale;

				  	    	print("In fileexists");

				  	    	format(fc_path, sizeof(fc_path), "./filterscripts/r%s.pwn", tmp_mapname);
				  	    	printf("./filterscripts/r%s.pwn", tmp_mapname);

				  	    	file_create(fc_path);
				  	    	printf("file created!");

				  	    	new File:fwHandle = f_open(fc_path, "w");

				  	    	if (fwHandle)
							{
					  	    	format(w_string, sizeof(w_string), "\
					  	    	#include <a_samp>\n\
					  	    	#include <streamer>\n\
					  	    	#include <sscanf2>\n\n\n");

		  	    				file_write(fc_path, w_string);

		  	    				format(w_string, sizeof(w_string), "\
					  	    	\n\nnew sphere[100];\n\
					  	    	new object[100];\n\
					  	    	new savestr[200];\n\n\n");

		  	    				file_write(fc_path, w_string);

		  	    				format(w_string, sizeof(w_string), "\n\npublic OnFilterScriptInit()\n{\n");
		  	    				file_write(fc_path, w_string);


								while (fread(chandle, item))
								{
									if (!sscanf(item, "p<\">'object' 'interior='d'collisions='s[10]'model='d'scale='f'posX='f'posY='f'posZ='f'rotX='f'rotY='f'rotZ='f", 
										interior, collision, obj_id, scale, posX, posY, posZ, rotX, rotY, rotZ))
									{
										/*if (strfind(item, "scale", true) != -1)
			    						{
			        						if (!sscanf(item, "p<\">{s[64]}'scale='f{s[128]}", scale)){}
			    						}*/

			        					format(obj_create, sizeof(obj_create), "\n    CreateGameModeObject(%i, %f, %f, %f, %f, %f, %f, %f, %s, %i);", 
			        					obj_id, posX, posY, posZ, rotX, rotY, rotZ, scale, collision, interior);

										file_write(fc_path, obj_create);
	

									}
									else if (!sscanf(item, "p<\">'object' 'model='d'interior='d'posX='f'posY='f'posZ='f'rotX='f'rotY='f'rotZ='f", 
										obj_id, interior, posX, posY, posZ, rotX, rotY, rotZ))
									{
										/*if (strfind(item, "scale", true) != -1)
			    						{
			        						if (!sscanf(item, "p<\">{s[64]}'scale='f{s[128]}", scale)){}
			    						}*/

			        					format(obj_create, sizeof(obj_create), "\n    CreateGameModeObject(%i, %f, %f, %f, %f, %f, %f, 1.0, true, %i);", 
			        					obj_id, posX, posY, posZ, rotX, rotY, rotZ, interior);

										file_write(fc_path, obj_create);
	

									}
									else if (!sscanf(item, "p<\">'marker''type='s[15]'color='s[10]'posX='f'posY='f'posZ='f",
										m_type, m_color, pX, pY, pZ))
									{
										format(obj_create, sizeof(obj_create), "\n    CreateGameModeMarker(%f, %f, %f, \"%s\", \"%s\");", 
										pX, pY, pZ, m_type, m_color);

										file_write(fc_path, obj_create);
									}

								}

								format(convert_path, sizeof(convert_path), "/%s/Converting.pwn", tmp_mapname);
								convertfile = fopen(convert_path, io_read);

								new conv_item[1024];

								if (convertfile)
								{
									while (fread(convertfile, conv_item))
									{
										format(conv_item, sizeof(conv_item), "    %s", conv_item);
										file_write(fc_path, conv_item);
										//format(convert_read[convert_count], sizeof(convert_read[convert_count]), "%s", conv_item);
										//convert_count++;
									}

									fclose(convertfile);
								}




								format(w_string, sizeof(w_string), "\n    return true;\n}");

								file_write(fc_path, w_string);

								format(w_string, sizeof(w_string), "\nstock CreateGameModeObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:scale, bool:collisions, interiorID)");
								file_write(fc_path, w_string);

								format(w_string, sizeof(w_string), "\n    return CallRemoteFunction(\"CreateGameModeObject\",\"iffffffffii\", modelid, X, Y, Z, rX, rY, rZ, scale, collisions, interiorID, 1);");
								file_write(fc_path, w_string);

								format(w_string, sizeof(w_string), "\n\nstock CreateGameModeMarker(Float:X, Float:Y, Float:Z, m_type[], m_color[])");
								file_write(fc_path, w_string);

								format(w_string, sizeof(w_string), "\n     return CallRemoteFunction(\"CreateGameModeMarker\",\"fffss\", X, Y, Z, m_type, m_color, 1);");
								file_write(fc_path, w_string);

								f_close(fwHandle);
								fclose(chandle);

								// Spawnpoints & Pickups (.ini)

								format(fc_path, sizeof(fc_path), "./scriptfiles/race%s.ini", tmp_mapname);
								printf(".scriptfiles/race%s.ini", tmp_mapname);

					  	    	file_create(fc_path);
					  	    	printf("file created!");

					  	    	new File:cwHandle = f_open(fc_path, "w");

					  	    	if (cwHandle)
					  	    	{
					  	    		print("In fwHandle!");

					  	    		xml = xml_open(xml_path);

					  	    		if (xml)
					  	    		{
					  	    			xml_get_string(xml, "meta/info/@author", tmp_author);
					  	    			xml_get_string(xml, "meta/info/@version", tmp_version);

					  	    			printf("Author: %s", tmp_author);
					  	    			printf("Version: %s", tmp_version);

					  	    			format(w_string, sizeof(w_string), "Author: %s", tmp_author);
					  	    			file_write(fc_path, w_string);

					  	    			format(w_string, sizeof(w_string), "\nVersion: %s", tmp_version);
					  	    			file_write(fc_path, w_string);

					  	    			format(w_string, sizeof(w_string), "\nMode: 2");
					  	    			file_write(fc_path, w_string);

					  	    			format(file, sizeof(file), "%s", xml_path);

										new time_item[128], File:thandle = fopen(file, io_read);

										while (fread(thandle, time_item))
										{
											if (strfind(time_item, "#time") != -1)
											{
												strmid(time_item, time_item, strfind(time_item, "value=")+7, strfind(time_item,":"));

												tmp_hours = strval(time_item);

												printf("Hours: %i", tmp_hours);

												format(w_string, sizeof(w_string), "\nHours: %i", tmp_hours);
					  	    					file_write(fc_path, w_string);

												continue;
											}
											else if (strfind(time_item, "#weather") != -1)
											{
												strmid(time_item, time_item, strfind(time_item, "value=")+9, strfind(time_item,"]"));

												tmp_weather = strval(time_item);
												printf("Weather: %i", tmp_weather);

												format(w_string, sizeof(w_string), "\nWeather: %i", tmp_weather);
					  	    					file_write(fc_path, w_string);
											}
										}

										fclose(thandle);

										thandle = fopen(file, io_read);

										while (fread(thandle, time_item))
										{
											if (strfind(time_item, "#time") != -1)
											{
												strmid(time_item, time_item, strfind(time_item, "value=")+10, strfind(time_item,"value=")+12);
												tmp_minutes = strval(time_item);

												printf("Minutes: %i", tmp_minutes);

					  	    					format(w_string, sizeof(w_string), "\nMinutes: %i", tmp_minutes);
					  	    					file_write(fc_path, w_string);


											}
										}

										format(f_path, sizeof(f_path), "%s/objects.map", tmp_mapname);
										printf("f_path = %s", f_path);

										chandle = fopen(f_path, io_read);

										new veh[500], Float:sX[500], Float:sY[500], Float:sZ[500], Float:rX[500], Float:rY[500], Float:rZ[500];

										count = 0;

										if (chandle)
										{
											while (fread(chandle, item))
											{
			
												if (!sscanf(item, "p<\">'spawnpoint''vehicle='d'posX='f'posY='f'posZ='f'rotX='f'rotY='f'rotZ='f",
													veh[count], sX[count], sY[count], sZ[count], rX[count], rY[count], rZ[count]))
												{
													format(w_string, sizeof(w_string), "\nVehicle: %i", veh[0]);
													file_write(fc_path, w_string);

													format(w_string, sizeof(w_string), "\n\n\
													Veh%i_X = %f\n\
													Veh%i_Y = %f\n\
													Veh%i_Z = %f\n\
													Veh%i_R = %f", count, sX[count], count, sY[count], count, sZ[count], count, rZ[count]);

													file_write(fc_path, w_string);

													count++;
												}
											}

											fclose(chandle);
										}

										chandle = fopen(f_path, io_read);

										if (chandle)
										{
											new pick_type[30];

											count = 0;

											while (fread(chandle, item))
											{
			
												if (!sscanf(item, "p<\">'racepickup''type='s[30]'vehicle='d'posX='f'posY='f'posZ='f'rotX='f'rotY='f'rotZ='f",
													pick_type, veh[count], sX[count], sY[count], sZ[count], rX[count], rY[count], rZ[count]))
												{

													if (strcmp(pick_type, "nitro") == 0)
													{
														format(w_string, sizeof(w_string), "\n\n\
														Pick%i_X = %f\n\
														Pick%i_Y = %f\n\
														Pick%i_Z = %f\n\
														Pick%i_R = %f\n\
														Pick%i_Type: 1", count, sX[count], count, sY[count], count, sZ[count], count, rZ[count], count);
													}
													else if (strcmp(pick_type, "repair") == 0)
													{
														format(w_string, sizeof(w_string), "\n\n\
														Pick%i_X = %f\n\
														Pick%i_Y = %f\n\
														Pick%i_Z = %f\n\
														Pick%i_R = %f\n\
														Pick%i_Type: 2", count, sX[count], count, sY[count], count, sZ[count], count, rZ[count], count);
													}
													else if (strcmp(pick_type, "vehiclechange") == 0)
													{
														format(w_string, sizeof(w_string), "\n\n\
														Pick%i_X = %f\n\
														Pick%i_Y = %f\n\
														Pick%i_Z = %f\n\
														Pick%i_R = %f\n\
														Pick%i_Type: 3\n\
														Pick%i_name: %i", count, sX[count], count, sY[count], count, sZ[count], count, rZ[count], count, count, veh[count]);
													}

													count++;

													file_write(fc_path, w_string);
												}

											}

											fclose(chandle);
										}

										format(f_path, sizeof(f_path), "./scriptfiles/%s/", tmp_mapname);

										new dir:ldHandle = dir_open(f_path);
										new mstring[1024], vstring[1024], counter = 0;
										new Float:mx, Float:my, Float:mz;
									 	new Float:maX[30], Float:maY[30], Float:maZ[30];
									 	new Float:vx, Float:vy, Float:vz, index = 0, id = 0;

										format(fc_path, sizeof(fc_path), "./scriptfiles/%s/Actionsscript.pwn", tmp_mapname);

				  	    				file_create(fc_path);

				  	    				new File:cdhandle;
											
										while(dir_list(ldHandle, item, type))
										{
										    format(file, sizeof(file), "/%s/%s", tmp_mapname, item);
										    cdhandle = fopen(file, io_read);

										    if (cdhandle)
										    {
										    	print("in cdhandle");
												while (fread(cdhandle, item))
												{

									   				if (strfind(item, "table.insert(clientContainer.markerElements, { createMarker(", true) != -1)
												    {
											     		if (!sscanf(item, "'createMarker('p<,>fff{s[45]}'),'fff", mx, my, mz, vx, vy, vz))
												        {
															format(mstring, sizeof(mstring), "\n\n// Velo %i\n", counter);
															format(mstring, sizeof(mstring), "\n\n%sformat(savestr,sizeof(savestr),\"%f|%f|%f\");", mstring, vx, vy, vz);

															format(mstring, sizeof(mstring), "%s\nsphere[%i] = CreateDynamicSphereEx(%f, %f, %f, 12.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,", 
															mstring, counter, mx, my, mz);

															format(mstring, sizeof(mstring), "%s31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,", mstring);
															format(mstring, sizeof(mstring), "%s71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring);
															format(mstring, sizeof(mstring), "%s\n\nsetproperty(0, \"\", 1000000+sphere[%i], savestr);", mstring, counter);
															format(mstring, sizeof(mstring), "%s\n\nStreamer_SetIntData(STREAMER_TYPE_AREA, sphere[%i], E_STREAMER_EXTRA_ID, 4);", mstring, counter);

															
															format(vstring, sizeof(vstring), "%s\
												            \n\nobject[%i] = CreateDynamicObjectEx(19298, %f, %f, %f, 0.0, 0.0, 0.0, 300.0, 300.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,\
												            13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,\
															31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,\
															52,53,54,55,56,57,58,59,\
															60,61,62,63,64,65,66,67,68,69,70,\
															71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring, counter, mx, my, mz);

															file_write(fc_path, vstring);

												        }
												    }
												    else if (strfind(item, "createMarker (", true) != -1)
												    {
												        if (!sscanf(item, "'createMarker ('p<,>fff", maX[index], maY[index], maZ[index]))
												        {
												            index++;
												        }
												    }
												    else if (strfind(item, "createMarker(", true) != -1)
												    {
											     		if (!sscanf(item, "'createMarker('p<,>fff", maX[index], maY[index], maZ[index]))
												        {
											                index++;
												        }
												    }
												    else if (strfind(item, "setElementPosition(vehicle,", true) != -1)
												    {
											         	if(!sscanf(item, "P<(),>{s[25]}{s[15]}fff", vx, vy, vz))
												        {
												        	format(mstring, sizeof(mstring), "\n\n// Teleport %i\n", id);
															format(mstring, sizeof(mstring), "\n\n%sformat(savestr,sizeof(savestr),\"%f|%f|%f\");", mstring, vx, vy, vz);

															format(mstring, sizeof(mstring), "%s\nsphere[%i] = CreateDynamicSphereEx(%f, %f, %f, 12.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,", 
															mstring, id, maX[id], maY[id], maZ[id]);

															format(mstring, sizeof(mstring), "%s31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,", mstring);
															format(mstring, sizeof(mstring), "%s71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring);
															format(mstring, sizeof(mstring), "%s\n\nsetproperty(0, \"\", 1000000+sphere[%i], savestr);", mstring, id);
															format(mstring, sizeof(mstring), "%s\n\nStreamer_SetIntData(STREAMER_TYPE_AREA, sphere[%i], E_STREAMER_EXTRA_ID, 5);", mstring, id);

															
															format(vstring, sizeof(vstring), "%s\
												            \n\nobject[%i] = CreateDynamicObjectEx(19298, %f, %f, %f, 0.0, 0.0, 0.0, 300.0, 300.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,\
												            13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,\
															31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,\
															52,53,54,55,56,57,58,59,\
															60,61,62,63,64,65,66,67,68,69,70,\
															71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring, id, maX[id], maY[id], maZ[id]);

															file_write(fc_path, vstring);

													        id++;
												        }
												    }
												    else if (strfind(item, "setElementPosition (", true) != -1)
												    {
											         	if(!sscanf(item, "P<(),>{s[25]}{s[15]}fff", vx, vy, vz))
												        {
												        	format(mstring, sizeof(mstring), "\n\n// Teleport %i\n", id);
															format(mstring, sizeof(mstring), "\n\n%sformat(savestr,sizeof(savestr),\"%f|%f|%f\");", mstring, vx, vy, vz);

															format(mstring, sizeof(mstring), "%s\nsphere[%i] = CreateDynamicSphereEx(%f, %f, %f, 12.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,", 
															mstring, id, maX[id], maY[id], maZ[id]);

															format(mstring, sizeof(mstring), "%s31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,", mstring);
															format(mstring, sizeof(mstring), "%s71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring);
															format(mstring, sizeof(mstring), "%s\n\nsetproperty(0, \"\", 1000000+sphere[%i], savestr);", mstring, id);
															format(mstring, sizeof(mstring), "%s\n\nStreamer_SetIntData(STREAMER_TYPE_AREA, sphere[%i], E_STREAMER_EXTRA_ID, 5);", mstring, id);

															
															format(vstring, sizeof(vstring), "%s\
												            \n\nobject[%i] = CreateDynamicObjectEx(19298, %f, %f, %f, 0.0, 0.0, 0.0, 300.0, 300.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,\
												            13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,\
															31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,\
															52,53,54,55,56,57,58,59,\
															60,61,62,63,64,65,66,67,68,69,70,\
															71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring, id, maX[id], maY[id], maZ[id]);

															file_write(fc_path, vstring);
													        id++;
												        }
												    }
												    else if (strfind(item, "setElementVelocity(", true) != -1)
												    {
											         	if(!sscanf(item, "P<(),>{s[25]}{s[15]}fff", vx, vy, vz))
												        {
															format(mstring, sizeof(mstring), "\n\n// Velo %i\n", id);
															format(mstring, sizeof(mstring), "\n\n%sformat(savestr,sizeof(savestr),\"%f|%f|%f\");", mstring, vx, vy, vz);

															format(mstring, sizeof(mstring), "%s\nsphere[%i] = CreateDynamicSphereEx(%f, %f, %f, 12.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,", 
															mstring, id, maX[id], maY[id], maZ[id]);

															format(mstring, sizeof(mstring), "%s31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,", mstring);
															format(mstring, sizeof(mstring), "%s71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring);
															format(mstring, sizeof(mstring), "%s\n\nsetproperty(0, \"\", 1000000+sphere[%i], savestr);", mstring, id);
															format(mstring, sizeof(mstring), "%s\n\nStreamer_SetIntData(STREAMER_TYPE_AREA, sphere[%i], E_STREAMER_EXTRA_ID, 4);", mstring, id);

															
															format(vstring, sizeof(vstring), "%s\
												            \n\nobject[%i] = CreateDynamicObjectEx(19298, %f, %f, %f, 0.0, 0.0, 0.0, 300.0, 300.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,\
												            13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,\
															31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,\
															52,53,54,55,56,57,58,59,\
															60,61,62,63,64,65,66,67,68,69,70,\
															71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring, id, maX[id], maY[id], maZ[id]);

															file_write(fc_path, vstring);
														    id++;
												        }
												    }
												    else if (strfind(item, "setElementVelocity (", true) != -1)
												    {
														if (!sscanf(item, "P<(),>{s[25]}{s[15]}fff", vx, vy, vz)) // P<(),>{s[40]}{s[20]}fff
														{
															format(mstring, sizeof(mstring), "\n\n// Velo  %i\n", id);
															format(mstring, sizeof(mstring), "\n\n%sformat(savestr,sizeof(savestr),\"%f|%f|%f\");", mstring, vx, vy, vz);

															format(mstring, sizeof(mstring), "%s\nsphere[%i] = CreateDynamicSphereEx(%f, %f, %f, 12.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,", 
															mstring, id, maX[id], maY[id], maZ[id]);

															format(mstring, sizeof(mstring), "%s31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,", mstring);
															format(mstring, sizeof(mstring), "%s71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring);
															format(mstring, sizeof(mstring), "%s\n\nsetproperty(0, \"\", 1000000+sphere[%i], savestr);", mstring, id);
															format(mstring, sizeof(mstring), "%s\n\nStreamer_SetIntData(STREAMER_TYPE_AREA, sphere[%i], E_STREAMER_EXTRA_ID, 4);", mstring, id);

															
															format(vstring, sizeof(vstring), "%s\
												            \n\nobject[%i] = CreateDynamicObjectEx(19298, %f, %f, %f, 0.0, 0.0, 0.0, 300.0, 300.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,\
												            13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,\
															31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,\
															52,53,54,55,56,57,58,59,\
															60,61,62,63,64,65,66,67,68,69,70,\
															71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring, id, maX[id], maY[id], maZ[id]);

															file_write(fc_path, vstring);
														    id++;
														}
											  		}
											  		else if (strfind(item, "Velocity=", true) != -1)
											  		{
											  		    if (!sscanf(item, "p<\">'Velocity='f,f,f", vx, vy, vz))
											  		    {
											  		    }
											  		}
											  		else if (strfind(item, "posX=", true) != -1)
											  		{
											    		if (!sscanf(item, "p<\">'posX='f", mx))
											  		    {
											  		    }
											  		}
											  		else if (strfind(item, "posY=", true) != -1)
											  		{
											    		if (!sscanf(item, "p<\">'posY='f", my))
											  		    {

											  		    }
											  		}
											  		else if (strfind(item, "posZ=", true) != -1)
											  		{
											    		if (!sscanf(item, "p<\">'posZ='f", mz))
											  		    {
											  		    	format(mstring, sizeof(mstring), "\n\n// Velo  %i\n", id+1);
															format(mstring, sizeof(mstring), "\n\n%sformat(savestr,sizeof(savestr),\"%f|%f|%f\");", mstring, vx, vy, vz);

															format(mstring, sizeof(mstring), "%s\nsphere[%i] = CreateDynamicSphereEx(%f, %f, %f, 12.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,", 
															mstring, id+1, mx, my, mz);

															format(mstring, sizeof(mstring), "%s31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,", mstring);
															format(mstring, sizeof(mstring), "%s71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring);
															format(mstring, sizeof(mstring), "%s\n\nsetproperty(0, \"\", 1000000+sphere[%i], savestr);", mstring, id+1);
															format(mstring, sizeof(mstring), "%s\n\nStreamer_SetIntData(STREAMER_TYPE_AREA, sphere[%i], E_STREAMER_EXTRA_ID, 4);", mstring, id+1);

															
															format(vstring, sizeof(vstring), "%s\
												            \n\nobject[%i] = CreateDynamicObjectEx(19298, %f, %f, %f, 0.0, 0.0, 0.0, 300.0, 300.0, {0,1,2,3,4,5,6,7,8,9,10,11,12,\
												            13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,\
															31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,\
															52,53,54,55,56,57,58,59,\
															60,61,62,63,64,65,66,67,68,69,70,\
															71,72,73,74,75,76,77,78,79,80}, {-1}, {-1}, 81);", mstring, id+1, mx, my, mz);

															file_write(fc_path, vstring);
											  		    }
											  		}
													fclose(cdhandle);
												}	
										    }
										}
												
										dir_close(ldHandle);

										fclose(thandle);
										printf("Map has been Created!");
					  	    		}
					  	    	}
							}
						}
					}
				}

				/*format(fc_path, sizeof(fc_path), "./scriptfiles/%s", tmp_mapname);
				format(newfile, sizeof(newfile), "./scriptfiles/benutze %s", tmp_mapname);
				print(fc_path);
				print(newfile);

				file_move(fc_path, newfile);*/

				ocmd_convert(playerid, "");
				dir_close(dhandel);
				return true;
			}

			idx++;
		}
		return true;
	}
	return 1;
}

stock RemoveSpecialCharacter(text[])
{
	for (new i = 0; i < strlen(text); i++)
	{
		switch (text[i])
		{
			case '/', '?', '>', '\\', '<', '*', '|', ':', '#', '\"':
			{
				strdel(text, i, i+1);
				i--;
			}
		}
	}
	return strlen(text);
}

stock frename(oldname[],newname[])
{
	if(!fexist(oldname)) return false;
	new string[255], File:old, File:neww;
	old = fopen(oldname, io_read);
	neww = fopen(newname, io_write);

	while(fread(old, string))
	{
		StripNewLine(string);
		format(string,sizeof(string),"%s\r\n",string);
		fwrite(neww, string);
	}
	fclose(old);
	fclose(neww);
	fremove(oldname);
	return true;
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
	for(i = strlen(string); i > 0; i--) 
	{
    	if(string[i-1] < 58) res = res + cur * (string[i-1] - 48); else res = res + cur * (string[i-1] - 65 + 10);
	 	cur = cur * 16;
	}
 	return res;
}

stock Converter(mapname[])
{
	new file[264];
	new item[512];
	// Convert Teleport's & Speedboost's
	format(file, sizeof(file), "racemaps/%s/Actions.xml", mapname);
	new mstring[512];
	new Float:posX, Float:posY, Float:posZ, Float:nposX, Float:nposY, Float:nposZ, Float:vPower;
	// Teleport
	new XML:teleport = xml_open(file);
	if(teleport)
	{
	    posX = xml_get_float(teleport, "ActionScript/TeleportIN/@posX");
	    posY = xml_get_float(teleport, "ActionScript/TeleportIN/@posY");
	    posZ = xml_get_float(teleport, "ActionScript/TeleportIN/@posZ");
	    format(mstring, sizeof(mstring), "posX=\"%f\" posY=\"%f\" posZ=\"%f\"", posX, posY, posZ);
	    nposX = xml_get_float(teleport, "ActionScript/TeleportOUT/@posX");
	    nposY = xml_get_float(teleport, "ActionScript/TeleportOUT/@posY");
	    nposZ = xml_get_float(teleport, "ActionScript/TeleportOUT/@posZ");
	    format(vstring, sizeof(vstring), "	<teleport id=""teleport"" %s nposX=\"%f\" nposY=\"%f\" nposZ=\"%f\" rotX=\"0.0\" rotY=\"0.0\" rotZ=\"0.0\"></teleport>\n", mstring, nposX, nposY, nposZ);
        ConverterSendToMap(mapname);
        posX = xml_get_float(teleport, "ActionScript/Jump/@posX");
        posY = xml_get_float(teleport, "ActionScript/Jump/@posY");
        posZ = xml_get_float(teleport, "ActionScript/Jump/@posZ");
        vPower = xml_get_float(teleport, "ActionScript/Jump/@Power");
        format(mstring, sizeof(mstring), "posX=\"%f\" posY=\"%f\" posZ=\"%f\"", posX, posY, posZ);
        format(vstring, sizeof(vstring), "	<speedboost id=\"speedboost\" %s veloX=\"%f\" veloY=\"0.0\" veloZ=\"0.0\"></speedbost>\n", mstring, vPower);
        ConverterSendToMap(mapname);
		xml_close(teleport);
	}
	// Velo
	new file1[512], type, item1[512];
	format(file1, sizeof(file1), "./scriptfiles/racemaps/%s", mapname);
	new dir:dHandle = dir_open(file1);
	new Float:mx, Float:my, Float:mz;
 	new Float:maX[30], Float:maY[30], Float:maZ[30];
 	new Float:vx, Float:vy, Float:vz;
 	new index = 0, id = 0;

	while(dir_list(dHandle, item1, type))
  	{
  	    if (type == FM_FILE) 
  	    {
  	        if (strfind(item1, ".map", true) != -1) continue;
  	    	format(file, sizeof(file), "maps/%s/%s", mapname, item1);
  	    }
  	    new File:chandle = fopen(file, io_read);
  	    if(fexist(file))
  	    {
			while(fread(chandle, item))
			{
   				if(strfind(item, "table.insert(clientContainer.markerElements, { createMarker(", true) != -1)
			    {
		     		if(!sscanf(item, "'createMarker('p<,>fff{s[45]}'),'fff", mx, my, mz, vx, vy, vz))
			        {
			            print("1");
			            format(mstring, sizeof(mstring), "posX=\"%f\" posY=\"%f\" posZ=\"%f\"", mx, my, mz);
  					    format(vstring, sizeof(vstring), "	<speedboost id=\"speedboost\" %s veloX=\"%f\" veloY=\"%f\" veloZ=\"%f\"></speedbost>\n", mstring, vx, vy, vz);
					    ConverterSendToMap(mapname);
			        }
			    }
			    else if(strfind(item, "createMarker (", true) != -1)
			    {
			        if(!sscanf(item, "'createMarker ('p<,>fff", maX[index], maY[index], maZ[index]))
			        {
			            print("2");
			            format(mstring, sizeof(mstring), "posX=\"%f\" posY=\"%f\" posZ=\"%f\"", maX[index], maY[index], maZ[index]);
			            index++;
			        }
			    }
			    else if(strfind(item, "createMarker(", true) != -1)
			    {
		     		if(!sscanf(item, "'createMarker('p<,>fff", maX[index], maY[index], maZ[index]))
			        {
			            print("3");
		                format(mstring, sizeof(mstring), "posX=\"%f\" posY=\"%f\" posZ=\"%f\"", maX[index], maY[index], maZ[index]);
		                index++;
			        }
			    }
			    else if(strfind(item, "setElementPosition(vehicle,", true) != -1)
			    {
		         	if(!sscanf(item, "P<(),>{s[25]}{s[15]}fff", vx, vy, vz))
			        {
					    format(vstring, sizeof(vstring), "	<teleport id=""teleport"" posX=\"%f\" posY=\"%f\" posZ=\"%f\" nposX=\"%f\" nposY=\"%f\" nposZ=\"%f\" rotX=\"0.0\" rotY=\"0.0\" rotZ=\"0.0\"></teleport>\n", maX[id], maY[id], maZ[id], vx, vy, vz);
				        ConverterSendToMap(mapname);
				        id++;
			        }
			    }
			    else if(strfind(item, "setElementPosition (", true) != -1)
			    {
		         	if(!sscanf(item, "P<(),>{s[25]}{s[15]}fff", vx, vy, vz))
			        {
					    format(vstring, sizeof(vstring), "	<teleport id=""teleport"" posX=\"%f\" posY=\"%f\" posZ=\"%f\" nposX=\"%f\" nposY=\"%f\" nposZ=\"%f\" rotX=\"0.0\" rotY=\"0.0\" rotZ=\"0.0\"></teleport>\n", maX[id], maY[id], maZ[id], vx, vy, vz);
				        ConverterSendToMap(mapname);
				        id++;
			        }
			    }
			    else if(strfind(item, "setElementVelocity(", true) != -1)
			    {
		         	if(!sscanf(item, "P<(),>{s[25]}{s[15]}fff", vx, vy, vz))
			        {
					    format(vstring, sizeof(vstring), "	<speedboost id=\"speedboost\" posX=\"%f\" posY=\"%f\" posZ=\"%f\" veloX=\"%f\" veloY=\"%f\" veloZ=\"%f\"></speedbost>\n", maX[id], maY[id], maZ[id], vx, vy, vz);
					    ConverterSendToMap(mapname);
					    id++;
			        }
			    }
			    else if(strfind(item, "setElementVelocity (", true) != -1)
			    {
					if(!sscanf(item, "P<(),>{s[25]}{s[15]}fff", vx, vy, vz))
					{
					    format(vstring, sizeof(vstring), "	<speedboost id=\"speedboost\"  posX=\"%f\" posY=\"%f\" posZ=\"%f\" veloX=\"%f\" veloY=\"%f\" veloZ=\"%f\"></speedbost>\n", maX[id], maY[id], maZ[id], vx, vy, vz);
					    ConverterSendToMap(mapname);
					    id++;
					}
		  		}
		  		else if(strfind(item, "Velocity=", true) != -1)
		  		{
		  		    if(!sscanf(item, "p<\">'Velocity='f,f,f", vx, vy, vz))
		  		    {
		  		        format(vstring, sizeof(vstring), "veloX=\"%f\" veloY=\"%f\" veloZ=\"%f\"", vx, vy, vz);
		  		    }
		  		}
		  		else if(strfind(item, "posX=", true) != -1)
		  		{
		    		if(!sscanf(item, "p<\">'posX='f", mx))
		  		    {
		  		        format(mstring, sizeof(mstring), "posX=\"%f\"", mx);
		  		    }
		  		}
		  		else if(strfind(item, "posY=", true) != -1)
		  		{
		    		if(!sscanf(item, "p<\">'posY='f", my))
		  		    {
		  		        format(mstring, sizeof(mstring), "posX=\"%f\" posY=\"%f\"", mx, my);
		  		    }
		  		}
		  		else if(strfind(item, "posZ=", true) != -1)
		  		{
		    		if(!sscanf(item, "p<\">'posZ='f", mz))
		  		    {
		  		        format(mstring, sizeof(mstring), "posX=\"%f\" posY=\"%f\" posZ=\"%f\"", mx, my, mz);
		  		        format(vstring, sizeof(vstring), "	<speedboost id=\"speedboost\" %s %s></speedbost>\n", mstring, vstring);
		  		        ConverterSendToMap(mapname);
		  		    }
		  		}
			}
			fclose(chandle);
		}
	}
	dir_close(dHandle);
	return 1;
}

stock ConverterSendToMap(mapname[])
{
	new file[264], item[512];
	format(file, sizeof(file), "racemaps/%s/objects.map", mapname);
	new File:lhandle = fopen(file, io_read);
	if(lhandle)
	{
		while(fread(lhandle, item, sizeof(item)))
		{
		    if(strfind(item, vstring, true) != -1) {
		        fclose(lhandle);
				return 1;
		    }
			if(strfind(item, "</map>", true) == 0)
			{
			    fclose(lhandle);
				lhandle = fopen(file, io_append);
				strcat(vstring, item);
				fdeleteline(file, item);
    			fwrite(lhandle, vstring);
				fclose(lhandle);
				return 1;
			}
		}
        fclose(lhandle);
	}
	return 1;
}


public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}

ocmd:xyz(playerid, params[])
{
	new Float:x, Float:y, Float:z;
	if(sscanf(params, "fff", x, y, z)) return SendClientMessage(playerid, -1, "/xyz ");
	SetPlayerPos(playerid, x, y, z);
	return true;
}