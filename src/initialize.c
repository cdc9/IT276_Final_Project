#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "graphics.h"
#include "simple_logger.h"
#include "sprite.h"
#include "player.h"
#include "entity.h"
#include "camera.h"
#include "projectile.h"
#include "enemy.h"
#include "platforms.h"
#include "mainmenu.h"
#include "levelcomplete.h"
#include "initialize.h"

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect _Camera;
extern SDL_Joystick* gGameController;
extern int currentLevel;

Vec2d camSize;

void Init_Begin()
{
	float bgcolor[] = {1,1,1,1};
  Init_Graphics(
	"Game Test",
    800,
    600,
    800,
    600,
    bgcolor,
    0);
	initEntitySystem(255);
	initSpriteSystem(255); //TODO

	//For the main menus
	showTitle();
	showMain();
}
void Init_Level()
{
		//For loading the levels and players and stuff
	Init_Player();
	Init_Dummy();
	Init_Platform();

	//Setting camera size
	camSize.x = 800;
	camSize.y = 600;
	camera_set_size(camSize);
	if( SDL_NumJoysticks() < 1 )
        {
            slog( "Warning: No joysticks connected!\n" );
        }
        else
        {
            //Load joystick
            gGameController = SDL_JoystickOpen( 0 );
            if( gGameController == NULL )
            {
                printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
            }
			slog("Joystick has %d buttons \n",SDL_JoystickNumButtons(gGameController));
        }
}
void Init_Player()
{
	if(currentLevel == 1)
	{
		SpawnPlayer(150,200);
	}
	if(currentLevel == 2)
	{
		SpawnPlayer(150,200);
	}
	SpawnCameraCollider();
}
void Init_Dummy()
{
		//Level 1 spawns
	if(currentLevel == 1)
	{
		SpawnDummy(600,150, 1);
		SpawnDummy(700,150, 1);
		SpawnDummy(1200,260, 1);
		SpawnDummy(1920,200,2);
		SpawnDummy(1500,100,3);
		SpawnDummy(1950,740,4);
	}
	if(currentLevel == 2)
	{
		SpawnDummy(620,150,1);
		SpawnDummy(915,300,2);
		SpawnDummy(915,400,2);
		SpawnDummy(915,500,2);
		SpawnDummy(915,600,2);
		SpawnDummy(915,700,2);
		SpawnDummy(1100,740,4);
	}
}

void Init_Platform()
{
		if(currentLevel == 1)
	{
		SpawnPlatform(0,300);
		SpawnPlatform(480,225);
		SpawnPlatform(1000,300);
		SpawnPlatform2(1600,300);
		SpawnPlatform2(1750,200);
		SpawnPlatform2(1850,300);
		SpawnPlatform2(2000,200);
		SpawnPlatform2(2200,300);
		SpawnPlatform2(2100,200);
		SpawnPlatform(2250,193);
		SpawnPlatform2(2400,600);
		SpawnPlatform2(2200,650);
		SpawnPlatform3(2750,0);
		SpawnPlatform3(2750,508);
		SpawnPlatform(1550,730);
		SpawnPlatform(1040,730);
		SpawnPlatform(1550,870);
		SpawnPlatform(1040,870);
	}
	if(currentLevel == 2)
	{
		SpawnPlatform3(0,0);
		SpawnPlatform3(0,508);
		SpawnPlatform2(100,300);
		SpawnPlatform2(350,250);
		SpawnPlatform2(600,200);
		SpawnPlatform3(745,216);
		SpawnPlatform3(745,416);
		SpawnPlatform3(915,0);
		SpawnPlatform3(915,216);
		SpawnPlatform(750,900);
		
	}
}
/*
void Init_Enemy1()
{
	if(currentLevel == 1)
	{
		//SpawnEnemy(500,150,1);
		//SpawnEnemy(1400,150,1);
	}
	if(currentLevel == 2)
	{
		//SpawnEnemy(620,150,1);
	}
}
void Init_Enemy2()
{
	if(currentLevel == 1)
	{
		//SpawnEnemy(1920,200,2);
		//SpawnEnemy(2500,214,2);
	}
	if(currentLevel == 2)
	{
		/*
		SpawnEnemy(915,300,2);
		SpawnEnemy(915,400,2);
		SpawnEnemy(915,500,2);
		SpawnEnemy(915,600,2);
		SpawnEnemy(915,700,2);
		
	}
}
void Init_Enemy3()
{
	if(currentLevel == 1)
	{
		//SpawnEnemy(1500,100,3);
	}
}
void Init_Enemy4()
{
	if(currentLevel == 1)
	{
		//SpawnEnemy(1950,740,4);
	}
	if(currentLevel == 2)
	{
		//SpawnEnemy(1100,740,4);
	}
}
*/