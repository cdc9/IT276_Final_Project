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
#include "initialize.h"
#include "vector.h"
#include "leveleditor.h"
#include "entity.h"
#include "camera.h"
#include "loadlevel.h"
#include "mainmenu.h"

extern SDL_Rect _Camera;
extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;

void showEditor()
{
	int i;
	int done = 0;
	int returnDone = 0;
	int objectList = -1;
	const Uint8 *keys;
	SDL_Event e;
	LevelEditor *newEditorEnt;
	SDL_Renderer* renderer = gt_graphics_get_active_renderer();
	

	Sprite *leftButton;
	Sprite *rightButton;
	Sprite *bg;
	Entity *cursor = NULL;

	cursor = entity_new();

	leftButton = loadSprite("images/leftButton.png",100,100,1);
	rightButton = loadSprite("images/rightButton.png",100,100,1);
	cursor->sprite = loadSprite("images/editCursor.png",50,50,1);
	bg = loadSprite("images/background.png",1032,774,1);

	cursor->position.x = 300;
	cursor->position.y = 300;
	cursor->cameraEnt = 1;
	cursor->frameW = 100;
	cursor->frameH = 100;

	SDL_RenderClear(renderer);

	drawSprite(bg,0,vec2d(0,0));
	drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
	drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
	drawSprite(leftButton,0,vec2d(150,500));
	drawSprite(rightButton,0,vec2d(500,500));
	drawSprite(cursor->sprite,0,vec2d(cursor->position.x,cursor->position.y));

	SDL_RenderPresent(renderer);

	do
	{

	_Camera.x = (cursor->position.x + cursor->frameW /2) - 400; //<- This 400 is half the screen width
	_Camera.y = (cursor->position.y + cursor->frameH /2) - 300;//<- This 300 is half the screen height



	//Keep the camera in bounds
	
                if( _Camera.x < 0 )
                { 
                    _Camera.x = 0;
                }
                if( _Camera.y < 0 )
                {
                    _Camera.y = 0;
                }
                if( _Camera.x > LEVEL_WIDTH - _Camera.w )
                {
                    _Camera.x = LEVEL_WIDTH - _Camera.w;
                }
                if( _Camera.y > LEVEL_HEIGHT - _Camera.h )
                {
                    _Camera.y = LEVEL_HEIGHT - _Camera.h;
                }
	SDL_PollEvent (&e);
		if(&e)
		{
			if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					cursor->position.x += .5;
					SDL_RenderClear(renderer);
					drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
					drawSprite(leftButton,0,vec2d(150,500));
					drawSprite(rightButton,0,vec2d(500,500));
					spriteChange(newEditorEnt, objectList);
					entity_draw_all();
					//drawSprite(cursor->sprite,0,vec2d(cursor->position.x,cursor->position.y));
					SDL_RenderPresent(renderer);
					break;
				case SDLK_LEFT:
					cursor->position.x -= .5;
					SDL_RenderClear(renderer);
					drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
					drawSprite(leftButton,0,vec2d(150,500));
					drawSprite(rightButton,0,vec2d(500,500));
					spriteChange(newEditorEnt, objectList);
					entity_draw_all();
					//drawSprite(cursor->sprite,0,vec2d(cursor->position.x,cursor->position.y));
					SDL_RenderPresent(renderer);
					break;
				case SDLK_UP:
					cursor->position.y -= .5;
					SDL_RenderClear(renderer);
					drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
					drawSprite(leftButton,0,vec2d(150,500));
					drawSprite(rightButton,0,vec2d(500,500));
					spriteChange(newEditorEnt, objectList);
					entity_draw_all();
					//drawSprite(cursor->sprite,0,vec2d(cursor->position.x,cursor->position.y));
					SDL_RenderPresent(renderer);

					break;
				case SDLK_DOWN:
					cursor->position.y += .5;
					SDL_RenderClear(renderer);
					drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
					drawSprite(leftButton,0,vec2d(150,500));
					drawSprite(rightButton,0,vec2d(500,500));
					spriteChange(newEditorEnt, objectList);
					entity_draw_all();
					//drawSprite(cursor->sprite,0,vec2d(cursor->position.x,cursor->position.y));
					SDL_RenderPresent(renderer);
					break;
				case SDLK_RETURN:
					returnDone = 1;
					break;
				}
			}
			if(e.type == SDL_KEYUP)
			{
				switch(e.key.keysym.sym)
				{
				case SDLK_x:
					if(objectList < 6)
					{
						objectList++;
					}
					SDL_RenderClear(renderer);
					drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
					drawSprite(leftButton,0,vec2d(150,500));
					drawSprite(rightButton,0,vec2d(500,500));
					spriteChange(newEditorEnt, objectList);
					entity_draw_all();
					//drawSprite(cursor->sprite,0,vec2d(cursor->position.x,cursor->position.y));
					SDL_RenderPresent(renderer);
					slog("up key has been pressed");

					e.type = SDLK_CLEAR;
					break;

				case SDLK_z:
					if(objectList > 0)
					{
						objectList--;
					}
					SDL_RenderClear(renderer);
					drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
					drawSprite(leftButton,0,vec2d(150,500));
					drawSprite(rightButton,0,vec2d(500,500));
					spriteChange(newEditorEnt, objectList);
					entity_draw_all();
					//drawSprite(cursor->sprite,0,vec2d(cursor->position.x,cursor->position.y));
					SDL_RenderPresent(renderer);
					slog("down key has been pressed");
					e.type = SDLK_CLEAR;
					break;
				case SDLK_RIGHT:
					//cursor->position.x += 1;
					SDL_RenderClear(renderer);
					drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
					drawSprite(leftButton,0,vec2d(150,500));
					drawSprite(rightButton,0,vec2d(500,500));
					spriteChange(newEditorEnt, objectList);
					entity_draw_all();
					//drawSprite(cursor->sprite,0,vec2d(cursor->position.x,cursor->position.y));
					SDL_RenderPresent(renderer);
					break;
				case SDLK_LEFT:
					//cursor->position.x -= 1;
					SDL_RenderClear(renderer);
					drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
					drawSprite(leftButton,0,vec2d(150,500));
					drawSprite(rightButton,0,vec2d(500,500));
					spriteChange(newEditorEnt, objectList);
					entity_draw_all();
					//drawSprite(cursor->sprite,0,vec2d(cursor->position.x,cursor->position.y));
					SDL_RenderPresent(renderer);
					break;
				case SDLK_UP:
					//cursor->position.y += 1;
					SDL_RenderClear(renderer);
					drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
					drawSprite(leftButton,0,vec2d(150,500));
					drawSprite(rightButton,0,vec2d(500,500));
					spriteChange(newEditorEnt, objectList);
					entity_draw_all();
					//drawSprite(cursor->sprite,0,vec2d(cursor->position.x,cursor->position.y));
					SDL_RenderPresent(renderer);
					break;
				case SDLK_DOWN:
					//cursor->position.y -= 1;

					SDL_RenderClear(renderer);
					drawSprite(bg,0,vec2d(0-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(1032-_Camera.x,0-_Camera.y));
					drawSprite(bg,0,vec2d(2064-_Camera.x,0-_Camera.y));
					drawSprite(leftButton,0,vec2d(150,500));
					drawSprite(rightButton,0,vec2d(500,500));
					spriteChange(newEditorEnt, objectList);
					entity_draw_all();
					//drawSprite(cursor->sprite,0,vec2d(cursor->position.x,cursor->position.y));
					SDL_RenderPresent(renderer);
					break;

				case SDLK_RETURN:
					if(returnDone == 1)
					{
					placeObject(cursor, newEditorEnt);
					//entity_draw_all();
					SDL_RenderPresent(renderer);
					returnDone = 2;
					}
					break;
				}
			}
		}


		keys = SDL_GetKeyboardState(NULL);
		
		if(keys[SDL_SCANCODE_ESCAPE])
		{
			done = 1;
			level_save();
			showMain();
			//exit(1);
		}
		
	}
	while (!done);
	return;
}

void spriteChange(LevelEditor *editorEnt, int objectList)
{

	switch(objectList)
		{
		case 0:
			editorEnt->sprite = loadSprite("images/enemy1.png",24,26,1);
			strcpy(editorEnt->name,"Enemy");
			strcpy(editorEnt->type,"Type1");
			editorEnt->entType = 1;
			drawSprite(editorEnt->sprite,0,vec2d(350,500));
			break;
		case 1:
			editorEnt->sprite = loadSprite("images/enemy2.png",16,32,1);
			strcpy(editorEnt->name,"Enemy");
			strcpy(editorEnt->type,"Type2");
			editorEnt->entType = 2;
			drawSprite(editorEnt->sprite,0,vec2d(350,500));
			break;
		case 2:
			editorEnt->sprite = loadSprite("images/enemy3.png",32,22,1);
			strcpy(editorEnt->name,"Enemy");
			strcpy(editorEnt->type,"Type3");
			editorEnt->entType = 3;
			drawSprite(editorEnt->sprite,0,vec2d(350,500));
			break;
		case 3:
			editorEnt->sprite = loadSprite("images/boss.png",121,135,1);
			strcpy(editorEnt->name,"Enemy");
			strcpy(editorEnt->type,"Type4");
			editorEnt->entType = 4;
			drawSprite(editorEnt->sprite,0,vec2d(325,450));
			break;
		case 4:
			editorEnt->sprite = loadSprite("images/editPlatform1.png",100,23,1);
			strcpy(editorEnt->name,"Platform");
			editorEnt->entType = 5;
			drawSprite(editorEnt->sprite,0,vec2d(325,500));
			break;
		case 5:
			editorEnt->sprite = loadSprite("images/editPlatform2.png",100,16,1);
			strcpy(editorEnt->name,"Platform2");
			editorEnt->entType = 6;
			drawSprite(editorEnt->sprite,0,vec2d(325,500));
			break;
		case 6:
			editorEnt->sprite = loadSprite("images/editPlatform3.png",16,100,1);
			strcpy(editorEnt->name,"Platform3");
			editorEnt->entType = 7;
			drawSprite(editorEnt->sprite,0,vec2d(350,500));
			break;

		}
}

void placeObject(Entity *cursor, LevelEditor *editorEnt)
{
	Entity *newObject = NULL;
	newObject = entity_new();
	if (newObject == NULL)
	{
		fprintf(stderr, "Unable to generate object entity; %s", SDL_GetError());
		exit(0);
	}
	newObject->sprite = editorEnt->sprite;
	newObject->cameraEnt = 1;
	newObject->position.x = cursor->position.x;
	newObject->position.y = cursor->position.y;
	strcpy(newObject->name,editorEnt->name);
	strcpy(newObject->type,editorEnt->type);
	newObject->entType = editorEnt->entType;

	drawSprite(newObject->sprite,0,vec2d(cursor->position.x-_Camera.x ,cursor->position.y-_Camera.y ));
}