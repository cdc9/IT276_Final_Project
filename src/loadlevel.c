#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "player.h"
#include "enemy.h"
#include "platforms.h"
#include "graphics.h"
#include "entity.h"
#include "projectile.h"
#include "simple_logger.h"
#include "camera.h"
#include "pausemenu.h"
#include "levelcomplete.h"
#include "initialize.h"
#include "loadlevel.h"
#include "cJSON.h"
#include "vector.h"

Level *level_load(char *level_def_file)
{
	Level *newLevel = NULL;

	//config file stuff
	cJSON *json, *root, 
		*obj,  *buf;
	FILE *level_config_file;
	long length;
	char *data;

	//entity loading stuff
	int i;
	int id = 0;
	int entityNum;
	Entity *currentEntity = NULL;
	char positionString[100];
	Vec2d currentPos;

	//background loading stuff
	char *background_def_file = NULL;

	newLevel = (Level *) malloc (sizeof (Level));
	memset(newLevel, 0, sizeof (Level));
	
	level_config_file = fopen(level_def_file,"r");
	if(!level_config_file)
	{
		slog("No file found: %s", level_config_file);
		return NULL;
	}

	//get the length of the file
	fseek(level_config_file, 0, SEEK_END);
	length = ftell(level_config_file);
	//reset position to start of the file and allocate data to be the length of the file + 1
	fseek(level_config_file, 0, SEEK_SET);
	data = (char*) malloc(length + 1);
	//store the contents of the file in data, and close the file
	fread(data, 1, length, level_config_file);
	fclose(level_config_file);

	json = cJSON_Parse(data);
	root = cJSON_GetObjectItem(json,"level");

	if(!root)
	{
		slog("error parseing the file, file not a level config");
		return NULL;
	}

	//player
	obj = cJSON_GetObjectItem(root, "player");
	sscanf(cJSON_GetObjectItem(obj, "position")->valuestring, "%f %f", &currentPos.x, &currentPos.y);
	currentEntity = SpawnPlayer(currentPos.x, currentPos.y);
	currentEntity->position = currentPos;
	newLevel->player = currentEntity;

	//enemies
	obj = cJSON_GetObjectItem(root, "Enemy1");
	entityNum = cJSON_GetObjectItem(obj, "number")->valueint;
	for(i = 0; i < entityNum; i++)
	{
		sprintf(positionString, "position%d", i);
		sscanf(cJSON_GetObjectItem(obj, positionString)->valuestring, "%f %f", &currentPos.x, &currentPos.y);
		currentEntity = SpawnEnemy(currentPos.x, currentPos.y, 1);
		currentEntity->position = currentPos;
	}

	obj = cJSON_GetObjectItem(root, "Enemy2");
	entityNum = cJSON_GetObjectItem(obj, "number")->valueint;
	for(i = 0; i < entityNum; i++)
	{
		sprintf(positionString, "position%d", i);
		sscanf(cJSON_GetObjectItem(obj, positionString)->valuestring, "%f %f", &currentPos.x, &currentPos.y);
		currentEntity = SpawnEnemy(currentPos.x, currentPos.y, 2);
		currentEntity->position = currentPos;
	}

	obj = cJSON_GetObjectItem(root, "Enemy3");
	entityNum = cJSON_GetObjectItem(obj, "number")->valueint;
	for(i = 0; i < entityNum; i++)
	{
		sprintf(positionString, "position%d", i);
		sscanf(cJSON_GetObjectItem(obj, positionString)->valuestring, "%f %f", &currentPos.x, &currentPos.y);
		currentEntity = SpawnEnemy(currentPos.x, currentPos.y, 3);
		currentEntity->position = currentPos;
	}

	obj = cJSON_GetObjectItem(root, "Enemy4");
	entityNum = cJSON_GetObjectItem(obj, "number")->valueint;
	for(i = 0; i < entityNum; i++)
	{
		sprintf(positionString, "position%d", i);
		sscanf(cJSON_GetObjectItem(obj, positionString)->valuestring, "%f %f", &currentPos.x, &currentPos.y);
		currentEntity = SpawnEnemy(currentPos.x, currentPos.y, 4);
		currentEntity->position = currentPos;
	}

	obj = cJSON_GetObjectItem(root, "Platform");
	entityNum = cJSON_GetObjectItem(obj, "number")->valueint;
	for(i = 0; i < entityNum; i++)
	{
		sprintf(positionString, "position%d", i);
		sscanf(cJSON_GetObjectItem(obj, positionString)->valuestring, "%f %f", &currentPos.x, &currentPos.y);
		currentEntity = SpawnPlatform(currentPos.x, currentPos.y);
		currentEntity->position = currentPos;
	}

	obj = cJSON_GetObjectItem(root, "Platform2");
	entityNum = cJSON_GetObjectItem(obj, "number")->valueint;
	for(i = 0; i < entityNum; i++)
	{
		sprintf(positionString, "position%d", i);
		sscanf(cJSON_GetObjectItem(obj, positionString)->valuestring, "%f %f", &currentPos.x, &currentPos.y);
		currentEntity = SpawnPlatform2(currentPos.x, currentPos.y);
		currentEntity->position = currentPos;
	}

	obj = cJSON_GetObjectItem(root, "Platform3");
	entityNum = cJSON_GetObjectItem(obj, "number")->valueint;
	for(i = 0; i < entityNum; i++)
	{
		sprintf(positionString, "position%d", i);
		sscanf(cJSON_GetObjectItem(obj, positionString)->valuestring, "%f %f", &currentPos.x, &currentPos.y);
		currentEntity = SpawnPlatform3(currentPos.x, currentPos.y);
		currentEntity->position = currentPos;
	}


	newLevel->level_def_file = level_def_file;
	return newLevel;
}
void level_save()
{
	FILE *saved_level_config;
	cJSON *json, *root, 
		*obj,  *buf;
	char *data;
	char temp[100];
	int i;
	int number;
	Vec2d tempPosition;
	char positionString[100];
	int currentType = 1;
	int maxPosition = 0;

	json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "level", root=cJSON_CreateObject());

	//DEFAULT the player will start at this position
	cJSON_AddItemToObject(root, "player", obj = cJSON_CreateObject());
	sprintf(temp, "%f %f", 100.0f, 200.0f);
	cJSON_AddStringToObject(obj, "position", temp);

	//Enemy 1
	cJSON_AddItemToObject(root, "Enemy1", obj = cJSON_CreateObject());
	number =  entity_get_number_of_type(currentType);
	cJSON_AddNumberToObject(obj, "number", number);
	for(i = 0; i < number; i++)
	{
		tempPosition = entity_get_position_of_type(currentType);
		if(tempPosition.x > maxPosition)
		{
			maxPosition = tempPosition.x;
		}
		sprintf(temp, "%f %f", tempPosition.x, tempPosition.y);
		sprintf(positionString, "position%d", i);
		cJSON_AddStringToObject(obj, positionString, temp);
	}
	currentType++;

	//Enemy 2
	cJSON_AddItemToObject(root, "Enemy2", obj = cJSON_CreateObject());
	number =  entity_get_number_of_type(currentType);
	cJSON_AddNumberToObject(obj, "number", number);
	for(i = 0; i < number; i++)
	{
		tempPosition = entity_get_position_of_type(currentType);
		if(tempPosition.x > maxPosition)
		{
			maxPosition = tempPosition.x;
		}
		sprintf(temp, "%f %f", tempPosition.x, tempPosition.y);
		sprintf(positionString, "position%d", i);
		cJSON_AddStringToObject(obj, positionString, temp);
	}
	currentType++;

	//Enemy 3
	cJSON_AddItemToObject(root, "Enemy3", obj = cJSON_CreateObject());
	number =  entity_get_number_of_type(currentType);
	cJSON_AddNumberToObject(obj, "number", number);
	for(i = 0; i < number; i++)
	{
		tempPosition = entity_get_position_of_type(currentType);
		if(tempPosition.x > maxPosition)
		{
			maxPosition = tempPosition.x;
		}
		sprintf(temp, "%f %f", tempPosition.x, tempPosition.y);
		sprintf(positionString, "position%d", i);
		cJSON_AddStringToObject(obj, positionString, temp);
	}
	currentType++;

	//Enemy 4
	cJSON_AddItemToObject(root, "Enemy4", obj = cJSON_CreateObject());
	number =  entity_get_number_of_type(currentType);
	cJSON_AddNumberToObject(obj, "number", number);
	for(i = 0; i < number; i++)
	{
		tempPosition = entity_get_position_of_type(currentType);
		if(tempPosition.x > maxPosition)
		{
			maxPosition = tempPosition.x;
		}
		sprintf(temp, "%f %f", tempPosition.x, tempPosition.y);
		sprintf(positionString, "position%d", i);
		cJSON_AddStringToObject(obj, positionString, temp);
	}
	currentType++;

	//Platform 1
	cJSON_AddItemToObject(root, "Platform", obj = cJSON_CreateObject());
	number =  entity_get_number_of_type(currentType);
	cJSON_AddNumberToObject(obj, "number", number);
	for(i = 0; i < number; i++)
	{
		tempPosition = entity_get_position_of_type(currentType);
		if(tempPosition.x > maxPosition)
		{
			maxPosition = tempPosition.x;
		}
		sprintf(temp, "%f %f", tempPosition.x, tempPosition.y);
		sprintf(positionString, "position%d", i);
		cJSON_AddStringToObject(obj, positionString, temp);
	}
	currentType++;

	//Platform 2
	cJSON_AddItemToObject(root, "Platform2", obj = cJSON_CreateObject());
	number =  entity_get_number_of_type(currentType);
	cJSON_AddNumberToObject(obj, "number", number);
	for(i = 0; i < number; i++)
	{
		tempPosition = entity_get_position_of_type(currentType);
		if(tempPosition.x > maxPosition)
		{
			maxPosition = tempPosition.x;
		}
		sprintf(temp, "%f %f", tempPosition.x, tempPosition.y);
		sprintf(positionString, "position%d", i);
		cJSON_AddStringToObject(obj, positionString, temp);
	}
	currentType++;

	//Platform 3
	cJSON_AddItemToObject(root, "Platform3", obj = cJSON_CreateObject());
	number =  entity_get_number_of_type(currentType);
	cJSON_AddNumberToObject(obj, "number", number);
	for(i = 0; i < number; i++)
	{
		tempPosition = entity_get_position_of_type(currentType);
		if(tempPosition.x > maxPosition)
		{
			maxPosition = tempPosition.x;
		}
		sprintf(temp, "%f %f", tempPosition.x, tempPosition.y);
		sprintf(positionString, "position%d", i);
		cJSON_AddStringToObject(obj, positionString, temp);
	}
	currentType++;

	data = cJSON_Print(json);

	cJSON_Delete(json);

	saved_level_config = fopen(EDITOR_LEVEL, "w");

	if (saved_level_config == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n",
			  EDITOR_LEVEL);
	  return;
	}

	fprintf(saved_level_config, data);

	fclose(saved_level_config);
}
