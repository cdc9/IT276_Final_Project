#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "player.h"
#include "graphics.h"
#include "entity.h"
#include "projectile.h"
#include "simple_logger.h"
#include "camera.h"

game_t Game;

SDL_Event event;

extern SDL_Rect _Camera;

//for lvldesign
FILE *fp;
static int spawned;



void begin()
{
	if ( TTF_Init() == -1 )
		printf("SDL TTF error \n", SDL_GetError());
	else printf("sdl ttf success \n");

	setGameState(GSTATE_MENU, true);
}

void setGameState(int gameState, bool setup)
{
	int lvlObject;

	const char * classname, * flag;
	int x, y;

	if (setup == true)
	{
		/*
		if (fp != NULL)
		{
			fprintf (fp, "{\n\t\"name\" : \"level edit\",\n\t\"background\" : [\"bglvl1_1.png\", \"bglvl_1.png\"],\n\n\t \"level\" : \n\t[\n");

		}
		*/
	}











}