#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sprite.h"
#include "simple_logger.h"
#include "graphics.h"


static Sprite *spriteList = NULL;
static Uint32 MaxSprites = 0;

void initSpriteSystem(int maxSprites)
{
    if (maxSprites == 0)
    {
        slog("cannot allocate zero sprites!");
        return;
    }
    spriteList = (Sprite *)malloc(sizeof(Sprite) * maxSprites);
    if (!spriteList)
    {
        slog("failed to allocate sprite system.");
        return;
    }
    memset(spriteList,0,sizeof(Sprite)*maxSprites);
    MaxSprites = maxSprites;
    atexit(closeSpriteSystem);
}

void closeSpriteSystem()
{
    int i;
    if (!spriteList)
    {
        return;
    }
    for (i = 0; i < MaxSprites; i++)
    {
        if (spriteList[i].image != 0)
        {
            SDL_DestroyTexture(spriteList[i].image);
        }
    }
    free(spriteList);
    spriteList = NULL;
    MaxSprites = 0;
}

Sprite *loadSprite(char *filename,int frameW,int frameH, int FPL)
{
    int i;
	SDL_Renderer* SpriteRender = gt_graphics_get_active_renderer();
    SDL_Surface *surface;
	SDL_Texture *newTexture = NULL;
    Sprite *sprite = NULL;
    if (!spriteList)
    {
        slog("error: using sprite system uninitialized");
        return NULL;
    }
	
    for (i = 0;i < MaxSprites;i++)
    {
        if (spriteList[i].refCount == 0)
        {
            continue;
        }
        if (strcmp(spriteList[i].filename,filename)==0)
        {
            spriteList[i].refCount++;
            return &spriteList[i];
        }
    }
	
    /*not already loaded, need to load a new one*/
    surface = IMG_Load(filename);
    if (!surface)
    {
        slog("failed to load file %s, re: %s",filename,SDL_GetError());
        return NULL;
    }
	newTexture = SDL_CreateTextureFromSurface(SpriteRender, surface);
	for (i = 0;i < MaxSprites;i++)
    {
        if (spriteList[i].refCount == 0)
        {
			//SDL_SetColorKey(surface, SDL_TRUE , SDL_MapRGB(surface->format, 255,255,255));
			spriteList[i].image = newTexture;
			spriteList[i].frameSize.x = frameW;
			spriteList[i].frameSize.y = frameH;
			spriteList[i].imageSize.x = surface->w;
			spriteList[i].imageSize.y = surface->h;
			spriteList[i].framesPerLine = FPL;
			spriteList[i].refCount++;
			sprintf(spriteList[i].filename,"%s",filename);

			slog("Loaded the sprite");
			return &spriteList[i];
		}
	}
    return NULL;
}

void drawSprite(Sprite *sprite,int frame,Vec2d position)
{
    SDL_Rect cell,target;
    SDL_RendererFlip flipFlags = SDL_FLIP_NONE;
    Vec2d scaleFactor = {1,1};
    Vec2d scaleOffset = {0,0};
    if (!sprite)
    {
        return;
    }  
    gt_rect_set(
        cell,
        frame%sprite->framesPerLine * sprite->frameSize.x,
        frame/sprite->framesPerLine * sprite->frameSize.y,
        sprite->frameSize.x,
        sprite->frameSize.y);
    gt_rect_set(
        target,
        position.x - (scaleFactor.x * scaleOffset.x),
                 position.y - (scaleFactor.y * scaleOffset.y),
                 sprite->frameSize.x * scaleFactor.x,
                 sprite->frameSize.y * scaleFactor.y);
    SDL_RenderCopyEx(gt_graphics_get_active_renderer(),
                     sprite->image,
                     &cell,
                     &target,
                     0,
                     NULL,
                     flipFlags);
}
/* 
void freeSprite(Sprite **sprite) //Original
{
    Sprite *target;
    if (!sprite)return;
    if (!*sprite)return;
    target = *sprite;
    target->refCount--;
    if (target->refCount <= 0)
    {
        SDL_DestroyTexture(target->image);
        memset(target,0,sizeof(Sprite));
    }
    *sprite = NULL;
}
*/
void freeSprite(Sprite *sprite)
{
	sprite -> refCount--;
    if (sprite->refCount <= 0)
    {
        SDL_DestroyTexture(sprite->image);
        memset(sprite,0,sizeof(Sprite));
    }
    sprite = NULL;
}
/*eol@eof*/
