#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "sprite.h"
#include "simple_logger.h"
#include "mainmenu.h"
#include "player.h"
#include "initialize.h"

TTF_Font *newFont = NULL;

SDL_Color newTextColor = { 255, 255, 255 };
SDL_Color newTextColor2 = { 255, 165, 0 };

void showPause()
{
	SDL_Renderer* renderer = gt_graphics_get_active_renderer();
	//Surfaces
	SDL_Surface* message; 
	SDL_Surface* message2; 
	//Textures
	SDL_Texture* resume;
	SDL_Texture* quitGame;
	//SDL_rects 
	SDL_Rect pauseWindow;
	SDL_Rect logo;
	SDL_Rect logo2;
	//chars for the text
	char resumeText[32];
	char quitGameText[32];
	const Uint8 *keys;// the player
	int done;
	int OP = 0;
	//Events
	SDL_Event e;

	newFont =TTF_OpenFont("fonts/prstartk.ttf", 36);

	if( newFont == NULL)
	{
		slog("font is not working");
		return;
	}

	done = 0;

	strcpy(resumeText,"Resume Game");
	strcpy(quitGameText,"Quit to Main Menu");

	message = TTF_RenderText_Solid( newFont, resumeText, newTextColor2);
	message2 = TTF_RenderText_Solid( newFont, quitGameText, newTextColor);
	resume = SDL_CreateTextureFromSurface(renderer, message);
	quitGame = SDL_CreateTextureFromSurface(renderer, message2);

	logo.x = 280;
	logo.y = 150;
	logo.w = 250;
	logo.h = 25;

	logo2.x = 280;
	logo2.y = 250;
	logo2.w = 250;
	logo2.h = 25;

	pauseWindow.x = 100;
	pauseWindow.y = 100;
	pauseWindow.w = 600;
	pauseWindow.h = 400;
	
	//Black screen for pause window
	SDL_SetRenderDrawColor(gt_graphics_get_active_renderer(), 0, 0, 0, 0);
	SDL_RenderFillRect ( gt_graphics_get_active_renderer(), &pauseWindow);
	SDL_SetRenderDrawColor(gt_graphics_get_active_renderer(), 0, 0, 0,0xFF );


	do
	{
		
		message = TTF_RenderText_Solid(newFont, resumeText, newTextColor);
		message2 = TTF_RenderText_Solid(newFont, quitGameText, newTextColor);

		switch(OP)
		{
		case 0:
			message = TTF_RenderText_Solid(newFont, resumeText, newTextColor2);
		break;

		case 1:
			message2 = TTF_RenderText_Solid(newFont, quitGameText, newTextColor2);
			break;

		}
		
		resume = SDL_CreateTextureFromSurface(renderer, message);
		quitGame = SDL_CreateTextureFromSurface(renderer, message2);

		
		SDL_RenderCopy(renderer, resume, NULL, &logo);
		SDL_RenderCopy(renderer, quitGame, NULL, &logo2);
		SDL_RenderPresent(renderer);

		//Freeing the created texture so it doesn't eat all the memory
		SDL_FreeSurface( message);
		SDL_FreeSurface( message2);

		SDL_DestroyTexture( resume );
		SDL_DestroyTexture( quitGame );

		SDL_PollEvent (&e);
		
		if(&e)
		{
			if(e.type == SDL_KEYUP)
			{
				switch(e.key.keysym.sym)
				{
				case SDLK_UP:
					if(OP > 0)
					{
						OP--;
					}
					slog("up key has been pressed");
					e.type = SDLK_CLEAR;
					break;

				case SDLK_DOWN:
					if(OP < 1)
					{
						OP++;
					}
					slog("down key has been pressed");
					e.type = SDLK_CLEAR;
					break;

				case SDLK_RETURN:
					switch(OP)
					{
					case 0:
						done = 1;
						break;
					case 1:
						done = 1;
						entity_free_all();
						showMain();
						Init_Level();
						break;
					}
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







