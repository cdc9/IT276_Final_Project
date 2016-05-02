#ifndef _ANIMATION_
#define _ANIMATION_

#define MAX_SETS		20
#define MAX_ANIMATIONS	20

// structures and types
typedef struct animation_s
{
	int refNum; //each animation in the set has a reference number, move to animation set?

	int frameCounter; //to look through array
	short frames[10]; //frames that are part of the animation
	int intervals[10]; //how long each frame is displayed

	int curFrame; //current frame
	int maxFrames; //maximum amount of frames

	void* parent; //pointer to address of which anination set this animation came from void to fix circular dependency

	int nextFrameTime; //time for the next frame to show

}animation_t;

typedef struct animset_s
{
	int inuse; //refnum?
	animation_t set[MAX_ANIMATIONS];  // was doing a pointer when i didn't need one, force of habit

}animset_t;

typedef struct sprite_s
{
	SDL_Surface		*graphic; //can be a single sprite or a spritesheet
	animset_t		*animationSet; //each sprite has a set of animaitions associated with it
	int				background;
	char			filename[40];
	int				priority;
	int				width, height;
	int				framesperline;
	int				used; //reference count

}sprite_t;

// functions for animation
animset_t *InitAnimSet(void);
animset_t *getAnimSet (char *filename); //will find anim set file and see if loaded already, add it to array of loaded ones
void Animate (sprite_t * spritesheet, animation_t *animation, float x, float y);














#endif 