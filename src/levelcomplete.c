#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "sprite.h"
#include "simple_logger.h"
#include "levelcomplete.h"

extern int currentLevel;

TTF_Font *levelFont = NULL;


SDL_Color levelTextColor = { 255, 255, 255 };

void showLevelComplete()
{
	SDL_Renderer* renderer = gt_graphics_get_active_renderer();
	SDL_Texture* Title;
	SDL_Texture* Title2;
	SDL_Rect Logo;
	SDL_Rect Logo2;
	SDL_Rect levelCompleteWindow;
	char title[32];
	char title2[32];
	const Uint8 *keys;// the player
	int done;
	SDL_Surface* message; 
	SDL_Surface* message2; 
	//Background
	SDL_Surface *bg;
	SDL_Texture *bgImage;
	SDL_Rect LogoImage;
	//Events
	SDL_Event e; 


	levelFont =TTF_OpenFont("fonts/prstartk.ttf", 36);

	if( levelFont == NULL)
	{
		slog("font is not working");
		return;
	}

	done = 0;

	strcpy(title,"LEVEL COMPLETE");
	strcpy(title2,"ON TO THE NEXT");
	message = TTF_RenderText_Solid( levelFont, title, levelTextColor);
	message2 = TTF_RenderText_Solid( levelFont, title2, levelTextColor);
	Title = SDL_CreateTextureFromSurface(renderer, message);
	Title2 = SDL_CreateTextureFromSurface(renderer, message2);

	Logo.x = 160;
	Logo.y = 100;
	Logo.w = 500;
	Logo.h = 25;

	Logo2.x = 280;
	Logo2.y = 550;
	Logo2.w = 250;
	Logo2.h = 25;

	LogoImage.x = 100;
	LogoImage.y = 175;
	LogoImage.w = 640;
	LogoImage.h = 334;

	levelCompleteWindow.x = 0;
	levelCompleteWindow.y = 0;
	levelCompleteWindow.w = 800;
	levelCompleteWindow.h = 600;

	bg= IMG_Load("images/ryuBackgroundFaceSmaller.png");
	bgImage = SDL_CreateTextureFromSurface(renderer, bg);

	SDL_SetRenderDrawColor(gt_graphics_get_active_renderer(), 0, 0, 0, 0);
	SDL_RenderFillRect ( gt_graphics_get_active_renderer(), &levelCompleteWindow);
	SDL_SetRenderDrawColor(gt_graphics_get_active_renderer(), 0, 0, 0,0xFF );

	SDL_RenderCopy(renderer, Title,NULL, &Logo);
	SDL_RenderCopy(renderer, Title2,NULL, &Logo2);
	SDL_RenderCopy(renderer, bgImage,NULL, &LogoImage);
	SDL_RenderPresent(renderer);

	do 
	{
		SDL_PollEvent (&e);
		if(&e)
		{
			if( e.type == SDL_KEYUP)
			{
				//Select Surface based on key presses
				switch(e.key.keysym.sym)
				{
				case SDLK_RETURN:
					done = 1; 
					e.type = SDLK_CLEAR;
					break;
				}
			}
		}
	keys = SDL_GetKeyboardState(NULL);
	if(keys[SDL_SCANCODE_ESCAPE])
		{
			exit(1);
		}

	}
	while(!done);
	return;
}