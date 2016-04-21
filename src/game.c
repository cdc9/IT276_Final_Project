#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect _Camera;
extern SDL_Joystick* gGameController;
int LEVEL_WIDTH = 3024; //original 1024
int LEVEL_HEIGHT = 1000; // 768
int currentLevel = 1;

void Init_All();
void Init_Player();
void Init_Dummy();
void Init_Enemy1();
void Init_Enemy2();
void Init_Enemy3();
void Init_Enemy4();
void Init_Platform();

int getImagePathFromFile(char *filepath,char * filename);
int getCoordinatesFromFile(int *x, int *y,char * filename);
void addCoordinateToFile(char *filepath,int x, int y);


Vec2d camSize;
int deltaTime;

//The music that will be played
extern Mix_Music *gMusic = NULL;

//The sound effects that will be used
extern Mix_Chunk *gScratch = NULL;

/**
 * @brief Main game loop. Initialize everything and have a loop for update functions.
 */
int main(int argc, char *argv[])
{
  SDL_Surface *temp = NULL;
  int lastTime = 0;
  //New variables
  int done;
  int mx,my;

  int doOnce = 0;
  int tx = 0,ty = 0;
  const Uint8 *keys;
  char imagepath[512];
  Sprite *sprite;
  Sprite *bg;
  Sprite *bg2;
  SDL_Rect srcRect={0,0,800,600};
  Init_All();
  lastTime= SDL_GetTicks();
  temp = IMG_Load("images/background.png");/*notice that the path is part of the filename*/
  if(temp != NULL)
  {
      printf("temp image loaded successfully\n");
      SDL_BlitSurface(temp,NULL,buffer,NULL);
  }
  slog("got here");
  gt_graphics_render_surface_to_screen(temp,srcRect,0,0); //Perhaps putting camera here will work?
  SDL_FreeSurface(temp);
  slog("got here");
  done = 0;
  bg = loadSprite("images/background.png",1032,774,1);
  bg2 = loadSprite("images/background2.png",2000,1500,1);

  
  	   //Load music
    gMusic = Mix_LoadMUS( "sounds/piano.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	  //Load sound effects
    gScratch = Mix_LoadWAV( "sounds/jump2.wav" );
    if( gScratch == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }

  do
  {
	deltaTime = SDL_GetTicks() - lastTime;
	lastTime = SDL_GetTicks();
	SDL_RenderClear(gt_graphics_get_active_renderer());
	//drawSprite(bg,0,vec2d(0,0)); 
	if(currentLevel == 1)
	{
		drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
		drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
		drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
	}
	if(currentLevel == 2)
	{
		drawSprite(bg2,0,vec2d(0-_Camera.x,0-_Camera.y));
		drawSprite(bg,0,vec2d(2000-_Camera.x,0-_Camera.y));
	}
	update();
	entity_draw_all();
    NextFrame();
    SDL_PumpEvents();
    keys = SDL_GetKeyboardState(NULL);
	/*
	 //If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( gMusic, -1 );
    }
	*/
    if(keys[SDL_SCANCODE_ESCAPE])
    {
        done = 1;
    }
	
  }while(!done);
  slog("got here");
  exit(0);		/*technically this will end the program, but the compiler likes all functions that can return a value TO return a value*/
  return 0;
}

void Init_All()
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
	//Init_Dummy();
	Init_Player();
	Init_Enemy1();
	Init_Enemy2();
	Init_Enemy3();
	Init_Enemy4();
	Init_Platform();
	camSize.x = 800;
	camSize.y = 600;
	camera_set_size(camSize);
	//DefaultConfig();
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
}
void Init_Dummy()
{
	SpawnDummy(200,200);
}
void Init_Enemy1()
{
	if(currentLevel == 1)
	{
		SpawnEnemy(500,150,1);
		SpawnEnemy(1400,150,1);
	}
	if(currentLevel == 2)
	{
		SpawnEnemy(620,150,1);
	}
}
void Init_Enemy2()
{
	if(currentLevel == 1)
	{
		SpawnEnemy(1920,200,2);
		SpawnEnemy(2500,214,2);
	}
	if(currentLevel == 2)
	{
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
		SpawnEnemy(1500,100,3);
	}
}
void Init_Enemy4()
{
	if(currentLevel == 1)
	{
		SpawnEnemy(1950,740,4);
	}
	if(currentLevel == 2)
	{
		SpawnEnemy(1100,740,4);
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
	//SpawnPlatform2(50,360);
	//SpawnPlatform(50,500);

}
int getImagePathFromFile(char *filepath,char * filename)
{
    FILE *fileptr = NULL;
    char buf[255];
    int returnValue = -1;
    if (!filepath)
    {
        fprintf(stdout,"getImagePathFromFile: warning, no output parameter provided\n");
        return -1;
    }
    if (!filename)
    {
        fprintf(stdout,"getImagePathFromFile: warning, no input file path provided\n");
        return -1;
    }
    fileptr = fopen(filename,"r");
    if (!fileptr)
    {
        fprintf(stderr,"unable to open file: %s\n",filename);
        return -1;
    }
    if (fscanf(fileptr,"%s",buf))
    {
        if (strcmp(buf,"image:")==0)
        {
            fscanf(fileptr,"%s",filepath);
            returnValue = 0;
        }
    }
    fclose(fileptr);
    return returnValue;
}

void addCoordinateToFile(char *filepath,int x, int y)
{
    FILE *fileptr = NULL;
    if (!filepath)
    {
        fprintf(stdout,"addCoordinateToFile: warning, no input file path provided\n");
        return;
    }
    fileptr = fopen(filepath,"a");
    if (!fileptr)
    {
        fprintf(stderr,"unable to open file: %s\n",filepath);
        return;
    }
    fprintf(fileptr,"%s:%i:newcoordinate: %i %i\n",__FILE__,__LINE__,x,y);
    fclose(fileptr);
}

int getCoordinatesFromFile(int *x, int *y,char * filename)
{
    FILE *fileptr = NULL;
    char buf[255];
    int tx,ty;
    int returnValue = -1;
    if ((!x)&&(!y))
    {
        fprintf(stdout,"getCoordinatesFromFile: warning, no output parameter provided\n");
        return -1;
    }
    if (!filename)
    {
        fprintf(stdout,"getCoordinatesFromFile: warning, no input file path provided\n");
        return -1;
    }
    fileptr = fopen(filename,"r");
    if (!fileptr)
    {
        fprintf(stderr,"unable to open file: %s\n",filename);
        return -1;
    }
    while (fscanf(fileptr,"%s",buf) != EOF)
    {
        fprintf(stdout,"buf is: %s\n",buf);
        if (strcmp(buf,"position:")==0)
        {
            fscanf(fileptr,"%i %i",&tx,&ty);
            fprintf(stdout,"as read: %i, %i\n",tx,ty);
            returnValue = 0;
        }
    }
    fclose(fileptr);
    if (x)*x = tx;
    if (y)*y = ty;
    return returnValue;
}
