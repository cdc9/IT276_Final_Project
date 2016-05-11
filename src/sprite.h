#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL.h>
#include "vector.h"

typedef struct
{
   int refCount;        /**<keeps track of references to this element*/
   char filename[120];  /**<name of the image file loaded*/
   SDL_Texture * image;   /**<texture of the image loaded*/
   Vec2d imageSize;     /**<x and y dimensions of the image loaded*/
   int framesPerLine;        /**<how many frames per line in this sprite sheet*/
   Vec2d frameSize;    /**<the dimensions of a frame in the sprite sheet*/
}Sprite;

/**
 * @brief initializes sprite system and queues up cleanup on exit
 * @param maxSprites how many sprites the system should support.  Should not be zero
 */
void initSpriteSystem(int maxSprites);

/**
 * @brief Goes through the sprite system and cleans up all sprites inuse. Then frees up the memory.
 */
void closeSpriteSystem();

/**
 * @brief loads sprite into memory and prepare it for a draw.
 * @param filename The name of the file
 * @param FrameW The frame width of the image
 * @param FrameH The fram Height of the image
 * @param FPL Frames per line. Used for sprite sheets to know how many images per line
 */
Sprite *loadSprite(char *filename,int frameW,int frameH, int FPL);

/**
 * @brief draws the sprite on the screen.
 * @param sprite The image that was loaded previously
 * @param frame The frame of the sprite sheet you want
 * @param position A 2d Vector dictating the position on screen you want to draw to. 
 */
void drawSprite(Sprite *sprite,int frame,Vec2d position);

/**
 * @brief frees a loaded sprite from memory
 * @param sprite the sprite to be freed
 */
void freeSprite(Sprite *sprite);


#endif
