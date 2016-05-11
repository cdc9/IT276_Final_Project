#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL.h>

#include "player.h"
#include "graphics.h"
#include "entity.h"
#include "projectile.h"
#include "simple_logger.h"
#include "camera.h"

extern SDL_Surface *screen;
extern SDL_Rect _Camera;
extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;
extern int deltaTime;

Entity *ThePlatform = NULL;

Entity *SpawnPlatform(int x, int y)
{
	Entity *newent = NULL;
	newent = entity_new();
	if (newent == NULL)
	{
		fprintf(stderr, "Unable to generate player entity; %s", SDL_GetError());
		exit(0);
	}
	strcpy(newent->name,"Platform");
	newent -> entType = 5;
	newent->sprite = loadSprite("images/levelPlatform1.png",513,23,1);
	newent -> bounds.x = 0;
	newent -> bounds.y = 0;
	newent -> bounds.w = 513;
	newent -> bounds.h = 23;
	newent -> frameW = 513;	
	newent -> frameH = 23; 
	newent -> cameraEnt = 1;
	newent -> frame = 0;
	newent -> position.x = x;
	newent -> position.y = y;
	newent -> lastPosition.x = x;
	newent -> lastPosition.y = y;
	ThePlatform = newent;
	return newent;
}
Entity *SpawnPlatform2(int x, int y)
{
	Entity *newent = NULL;
	newent = entity_new();
	if (newent == NULL)
	{
		fprintf(stderr, "Unable to generate player entity; %s", SDL_GetError());
		exit(0);
	}
	strcpy(newent->name,"Platform2");
	newent -> entType = 6;
	newent->sprite = loadSprite("images/levelPlatform2.png",160,16,1);
	newent -> bounds.x = 0;
	newent -> bounds.y = 0;
	newent -> bounds.w = 160;
	newent -> bounds.h = 16;
	newent -> frameW = 160;	
	newent -> frameH = 16; 
	newent -> cameraEnt = 1;
	newent -> frame = 0;
	newent -> position.x = x;
	newent -> position.y = y;
	newent -> lastPosition.x = x;
	newent -> lastPosition.y = y;
	ThePlatform = newent;
	return newent;
}
Entity *SpawnPlatform3(int x, int y)
{
	Entity *newent = NULL;
	newent = entity_new();
	if (newent == NULL)
	{
		fprintf(stderr, "Unable to generate player entity; %s", SDL_GetError());
		exit(0);
	}
	strcpy(newent->name,"Platform3");
	newent -> entType = 7;
	newent->sprite = loadSprite("images/levelPlatform3.png",16,508,1);
	newent -> bounds.x = 0;
	newent -> bounds.y = 0;
	newent -> bounds.w = 16;
	newent -> bounds.h = 508;
	newent -> frameW = 160;	
	newent -> frameH = 16; 
	newent -> cameraEnt = 1;
	newent -> frame = 0;
	newent -> position.x = x;
	newent -> position.y = y;
	newent -> lastPosition.x = x;
	newent -> lastPosition.y = y;
	ThePlatform = newent;
	return newent;
}