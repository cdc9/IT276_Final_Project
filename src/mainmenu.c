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

int GP;
extern int currentLevel;

TTF_Font *font = NULL;
TTF_Font *font2 = NULL;

SDL_Color textColor = { 255, 255, 255 };
SDL_Color textColor2 = { 255, 165, 0 };

void showTitle()
{
	SDL_Renderer* renderer = gt_graphics_get_active_renderer();
	SDL_Texture* Title;
	SDL_Texture* Title2;
	SDL_Rect Logo;
	SDL_Rect Logo2;
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


	font =TTF_OpenFont("fonts/prstartk.ttf", 36);
	font2 =TTF_OpenFont("fonts/prstartk.ttf", 18);
	if( font == NULL)
	{
		slog("font is not working");
		return;
	}
	if( font2 == NULL)
	{
		slog("font is not working");
		return;
	}

	done = 0;

	strcpy(title,"WORST NINJA EVER");
	strcpy(title2,"Press Start");
	message = TTF_RenderText_Solid( font, title, textColor2);
	message2 = TTF_RenderText_Solid( font2, title2, textColor);
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

	bg= IMG_Load("images/ryuBackgroundFaceSmaller.png");
	bgImage = SDL_CreateTextureFromSurface(renderer, bg);

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
				case SDLK_UP:
					slog("up key is up");
					e.type = SDLK_CLEAR;
					break;

				case SDLK_DOWN:
					slog("down key is down");
					e.type = SDLK_CLEAR;
					break;
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

void showMain()
{
	SDL_Renderer* renderer = gt_graphics_get_active_renderer();
	const Uint8 *keys;
	int done;
	int OP = 0;
	char option1[32];
	char option2[32];
	char option3[32];
	char option4[32];

	//Creating textures
	SDL_Texture* NewGame;
	SDL_Texture* LoadGame;
	SDL_Texture* Editor;
	SDL_Texture* QuitGame;

	//Creating surfaces to convert to textures
	SDL_Surface *NewGameSurface;
	SDL_Surface *LoadGameSurface;
	SDL_Surface *EditorSurface;
	SDL_Surface *QuitGameSurface;

	SDL_Rect r1;
	SDL_Rect r2;
	SDL_Rect r3;
	SDL_Rect r4;

	//For the background image
	SDL_Surface *bg;
	SDL_Texture *bgImage;
	SDL_Rect LogoImage;

	SDL_Event e;

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	strcpy(option1, "New Game");
	strcpy(option2, "Load Game");
	strcpy(option3, "Level Editor");
	strcpy(option4, "Quit Game");

	if(font == NULL)
	{
		slog("The font has not loaded properly");
		return;
	}

	done = 0;

	r1.x = 200;
	r1.y = 100;
	r1.w = 250;
	r1.h = 25;
	
	r2.x = 200;
	r2.y = 150;
	r2.w = 250;
	r2.h = 25;

	r3.x = 200;
	r3.y = 200;
	r3.w = 150;
	r3.h = 25;

	r4.x = 200;
	r4.y = 250;
	r4.w = 100;
	r4.h = 25;

	LogoImage.x = 300;
	LogoImage.y = 275;
	LogoImage.w = 270;
	LogoImage.h = 246;

	if(font == NULL)
	{
		slog("Font has not loaded properly");
		return;
	}
	done = 0;

	bg= IMG_Load("images/BigRyu2.png");
	bgImage = SDL_CreateTextureFromSurface(renderer, bg);
	SDL_RenderCopy(renderer, bgImage, NULL, &LogoImage);

	do
	{
		
		NewGameSurface = TTF_RenderText_Solid(font, option1, textColor);
		LoadGameSurface = TTF_RenderText_Solid(font, option2, textColor);
		EditorSurface = TTF_RenderText_Solid(font, option3, textColor);
		QuitGameSurface = TTF_RenderText_Solid(font, option4, textColor);

		switch(OP)
		{
		case 0:
			NewGameSurface = TTF_RenderText_Solid(font, option1, textColor2);
		break;

		case 1:
			LoadGameSurface = TTF_RenderText_Solid(font, option2, textColor2);
			break;
		
		case 2:
			EditorSurface = TTF_RenderText_Solid(font, option3, textColor2);
			break;

		case 3:
			QuitGameSurface = TTF_RenderText_Solid(font, option4, textColor2);
			break;

		}
		
		NewGame = SDL_CreateTextureFromSurface(renderer, NewGameSurface);
		LoadGame = SDL_CreateTextureFromSurface(renderer, LoadGameSurface);
		Editor = SDL_CreateTextureFromSurface(renderer, EditorSurface);
		QuitGame = SDL_CreateTextureFromSurface(renderer, QuitGameSurface);
		
		SDL_RenderCopy(renderer, NewGame, NULL, &r1);
		SDL_RenderCopy(renderer, LoadGame, NULL, &r2);
		SDL_RenderCopy(renderer, Editor, NULL, &r3);
		SDL_RenderCopy(renderer, QuitGame, NULL, &r4);
		SDL_RenderPresent(renderer);

		//Freeing the created texture so it doesn't eat all the memory
		SDL_FreeSurface( NewGameSurface);
		SDL_FreeSurface( LoadGameSurface);
		SDL_FreeSurface( EditorSurface);
		SDL_FreeSurface( QuitGameSurface);

		SDL_DestroyTexture( NewGame );
		SDL_DestroyTexture( LoadGame );
		SDL_DestroyTexture( Editor );
		SDL_DestroyTexture( QuitGame );

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
					if(OP < 3)
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
						GP = 1;
						done = 1;
						break;
					case 1:
						GP = 0;
						levelSelect(); 
						done = 1;
						break;
					case 2:
						GP = 0;
						done = 1;
						break;
					case 3:
						exit(1);
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

void levelSelect()
{
	SDL_Renderer* renderer = gt_graphics_get_active_renderer();
	const Uint8 *keys;// the player
	int done;
	int OP = 0;

	SDL_Texture* LVL1;
	SDL_Texture* LVL2;
	SDL_Texture* LVL3;
	SDL_Texture* Quit;

	SDL_Rect r1;
	SDL_Rect r2;
	SDL_Rect r3;
	SDL_Rect r4;// quit rectangle 

	char option1[32];
	char option2[32];
	char option3[32];
	char option4[32];

	SDL_Surface *NewGameSurface;
	SDL_Surface *LoadGameSurface;
	SDL_Surface *EditorSurface;
	SDL_Surface *QuitGameSurface;

	SDL_Event e;

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	strcpy(option1 ,"LEVEL 1");
	strcpy(option2 ,"LEVEL 2");
	strcpy(option3 ,"LEVEL 3");
	strcpy(option4 ,"Back to Main");

	 if( font == NULL )
    {
     slog("font not loaded properly");
		return;
    }

	r1.x = 200;
	r1.y = 100;
	r1.w = 150;
	r1.h = 25;
	
	r2.x = 200;
	r2.y = 150;
	r2.w = 150;
	r2.h = 25;

	r3.x = 200;
	r3.y = 200;
	r3.w = 150;
	r3.h = 25;

	r4.x = 270;
	r4.y = 550;
	r4.w = 250;
	r4.h = 25;

	 if( font == NULL )
    {
     slog("font not loaded properly");
		return;
    }

	done = 0;

	do
	{
		NewGameSurface = TTF_RenderText_Solid(font, option1, textColor);
		LoadGameSurface = TTF_RenderText_Solid(font, option2, textColor);
		EditorSurface = TTF_RenderText_Solid(font, option3, textColor);
		QuitGameSurface = TTF_RenderText_Solid(font, option4, textColor);

		switch(OP)
		{
		case 0:
			NewGameSurface = TTF_RenderText_Solid(font, option1, textColor2);
		break;

		case 1:
			LoadGameSurface = TTF_RenderText_Solid(font, option2, textColor2);
			break;
		
		case 2:
			EditorSurface = TTF_RenderText_Solid(font, option3, textColor2);
			break;

		case 3:
			QuitGameSurface = TTF_RenderText_Solid(font, option4, textColor2);
			break;

		}

		LVL1 = SDL_CreateTextureFromSurface( renderer, NewGameSurface );
		LVL2 = SDL_CreateTextureFromSurface( renderer, LoadGameSurface );
		LVL3 = SDL_CreateTextureFromSurface( renderer, EditorSurface );
		Quit = SDL_CreateTextureFromSurface( renderer, QuitGameSurface );

		SDL_RenderCopy(renderer,LVL1,NULL,&r1);  
		SDL_RenderCopy(renderer,LVL2,NULL,&r2);  
		SDL_RenderCopy(renderer,LVL3,NULL,&r3);  
		SDL_RenderCopy(renderer,Quit,NULL,&r4);  
		SDL_RenderPresent(renderer);

		SDL_FreeSurface( NewGameSurface);
		SDL_FreeSurface( LoadGameSurface);
		SDL_FreeSurface( EditorSurface);
		SDL_FreeSurface( QuitGameSurface);

		SDL_DestroyTexture( LVL1 );
		SDL_DestroyTexture( LVL2 );
		SDL_DestroyTexture( LVL3 );
		SDL_DestroyTexture( Quit );

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
					if(OP < 3)
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
						currentLevel = 1;
						done = 1;
						break;
					case 1:
						currentLevel = 2;
						done = 1;
						break;
					case 2:
						done = 1;
						break;
					case 3:
						done = 1;
						showMain();
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