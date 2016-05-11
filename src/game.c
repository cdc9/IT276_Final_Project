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
#include <time.h>

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect _Camera;
extern SDL_Joystick* gGameController;
extern int LEVEL_WIDTH = 3024; //original 1024
extern int LEVEL_HEIGHT = 1000; // 768
extern int currentLevel = 1;


int getImagePathFromFile(char *filepath,char * filename);
int getCoordinatesFromFile(int *x, int *y,char * filename);
void addCoordinateToFile(char *filepath,int x, int y);


Vec2d camSize;
int deltaTime;

//The music that will be played
extern Mix_Music *gMusic = NULL;

//The sound effects that will be used
extern Mix_Chunk *gJump = NULL;
extern Mix_Chunk *gJump2 = NULL;
extern Mix_Chunk *gJump3 = NULL;
extern Mix_Chunk *gDeath = NULL;
extern Mix_Chunk *gGameOver = NULL;

/**
 * @brief Main game loop. Initialize everything and have a loop for update functions.
 */
int main(int argc, char *argv[])
{
  time_t t;	
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
  //Init_All();
  srand((unsigned) time(&t));
  Init_Begin();
  Init_Level();
  lastTime= SDL_GetTicks();
  temp = IMG_Load("images/background.png");/*notice that the path is part of the filename*/
  if(temp != NULL)
  {
      printf("temp image loaded successfully\n");
      SDL_BlitSurface(temp,NULL,buffer,NULL);
  }
  gt_graphics_render_surface_to_screen(temp,srcRect,0,0); //Perhaps putting camera here will work?
  SDL_FreeSurface(temp);
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
    gJump = Mix_LoadWAV( "sounds/jump2.wav" );
    if( gJump == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	 gJump2 = Mix_LoadWAV( "sounds/jump3.wav" );
    if( gJump2 == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	gJump3 = Mix_LoadWAV( "sounds/jump5.wav" );
    if( gJump3 == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	gDeath = Mix_LoadWAV( "sounds/lifeLost.wav" );
    if( gDeath == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	gGameOver = Mix_LoadWAV( "sounds/gameover.wav" );
    if( gGameOver == NULL )
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
	if(currentLevel == 3)
	{
		drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
		drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
		drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
	}
	update();
	entity_draw_all();
	Draw_HUD();
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
