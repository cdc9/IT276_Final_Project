#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL.h>

#include "player.h"
#include "graphics.h"
#include "entity.h"
#include "simple_logger.h"
#include "camera.h"

extern SDL_Surface *screen;
extern Entity *ThePlayer;
extern SDL_Rect _Camera;
extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;

enum PlayerInputs {PI_MovLeft,PI_MovRight,PI_MovDown,PI_MovUp,PI_Fire,PI_Jump,PI_MovUpLeft,PI_MovDownLeft,PI_MovUpRight,PI_MovDownRight,
                   PI_Pause,PI_Powerup1,PI_Powerup2,PI_Powerup3,PI_Powerup4,PI_NULL};


Uint32 KeyButtons[PI_NULL];

int PlayerCommands = PI_NULL;
Entity *ThePlayer = NULL;
//SDL_Surface *titlebar = NULL;
//int attackleft = SDLK_LEFT;
//void UpdatePlayer(Entity *self);
//void PlayerThink(Entity *self);
//void FinalOutput();		****This is just for the score

Player ThisPlayer;

/**
 * @brief Spawn the player in the level. Defines the player's attributes 
 * @param an x and y for the player's position.
 */
Entity *SpawnPlayer(int x, int y)
{
	Entity *newent = NULL;
	newent = entity_new();
	if (newent == NULL)
	{
		fprintf(stderr, "Unable to generate player entity; %s", SDL_GetError());
		exit(0);
	}
	strcpy(newent->name,"Player");
	//newent->sprite = loadSprite("images/marioSprite2.png",128,160,1);
	newent->sprite = loadSprite("images/ryuSprite1.png",16,33,1);
	//newent->sprite-> imageSize.x = 32;
	//newent->sprite-> imageSize.y = 32;
	newent -> frameW = 16;	//TODO: make sure that this is always accurate
	newent -> frameH - 33; //TODO: make sure that this is always accurate
	newent -> update = UpdatePlayer;
	newent -> think = PlayerThink;
	newent -> maxhealth = 100;
	newent -> health = 100;
	newent -> frame = 0;
	newent -> position.x = x;
	newent -> position.y = y;
	newent -> velocity.x = 0;
	newent -> velocity.y = 0;
	newent -> maxspeed = 3;
	newent -> movespeed = 0;
	newent -> accel = 1;
	newent -> bounds.x = x;
	newent -> bounds.y = y;
	newent -> bounds.w = 16;
	newent -> bounds.h = 33;
	newent -> state = 0;

	drawSprite(newent ->sprite, 5,vec2d(x,y));
	//UpdatePlayer(newent);
	ThePlayer = newent;
	return newent;
	//atexit(FinalOutput);

}

Entity *SpawnDummy(int x, int y)
{
	Entity *newent = NULL;
	newent = entity_new();
	if (newent == NULL)
	{
		fprintf(stderr, "Unable to generate player entity; %s", SDL_GetError());
		exit(0);
	}
	strcpy(newent->name,"Dummy");
	newent->sprite = loadSprite("images/marioSprite3.png",200,200,1);
	//newent->sprite-> imageSize.x = 32;
	//newent->sprite-> imageSize.y = 32;
	newent -> frameW = 200;	//TODO: make sure that this is always accurate
	newent -> frameH - 200; //TODO: make sure that this is always accurate
	newent -> update = UpdateDummy;
	newent -> think = DummyThink;
	newent -> maxhealth = 100;
	newent -> health = 100;
	newent -> frame = 0;
	newent -> position.x = x;
	newent -> position.y = y;
	newent -> velocity.x = 0;
	newent -> velocity.y = 0;
	newent -> maxspeed = 3;
	newent -> movespeed = 0;
	newent -> accel = 1;
	newent -> bounds.x = x;
	newent -> bounds.y = y;
	newent -> bounds.w = 200;
	newent -> bounds.h = 200;
	newent -> state = 0;
	//entity_draw(newent, gt_graphics_get_active_renderer());
	drawSprite(newent ->sprite, 0,vec2d(x,y));
	UpdateDummy(newent);
	//ThePlayer = newent;
	return newent;
	//atexit(FinalOutput);

}

void PlayerThink(Entity *self)
{
	float t; 
	char text [40];
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	
	//UpdateInput();
	if((self->state != ST_DEAD) && (self-> state != ST_DIE))
	{
		
		if(PlayerCommands == PI_MovLeft)
		{      
			self->velocity.x -= self->accel;
			self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
			//self->grounded = 0;
			if(self->movespeed > self->maxspeed)
			{
				self->velocity.y = 0;
				self->velocity.x = self->maxspeed * -1;
				self->movespeed = self->maxspeed;
			}
			self->position.x += self->velocity.x;
			//SpawnThrust(IndexColor(self->Color),self->s.x + 24,self->s.y + 24,2,0,self->movespeed,self->movespeed * 4);
		}
		
		else if(PlayerCommands == PI_MovRight)
		{      
			self->velocity.x += self->accel;
			self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
			//self->grounded = 0;
			if(self->movespeed > self->maxspeed)
			{
				self->velocity.y = 0;
				self->velocity.x = self->maxspeed;
				self->movespeed = self->maxspeed;
			}
			self->position.x += self->velocity.x;
			//SpawnThrust(IndexColor(self->Color),self->s.x + 24,self->s.y + 24,-2,0,self->movespeed,self->movespeed * 4);
		}
		else if(PlayerCommands == PI_NULL)
		{
			self->movespeed = 0;
			}
		
	UpdatePlayer(self);
	UpdateInput();

		/*
		else if(PlayerCommands == PI_MovUpLeft)
		{
			t = self->accel *1.41;
			self->velocity.x -= t;
			self->velocity.y -= t;
			self->movespeed = VectorLength(self->velocity.x, self->velocity.y);
			//self-> grounded = 0;
			if(self ->movespeed = self->maxspeed)
			{
				self-> velocity.x = self-> maxspeed * 1.41;
				self-> velocity.y = self-> velocity.x * -1;
				self->movespeed = self->maxspeed;
			}
		}
		else if(PlayerCommands == PI_MovDownLeft)
		{     
			t = self->accel * 1.41; 
			self->velocity.y += t;
			self->velocity.x -= t;
			//self->grounded = 0;
			self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
			if(self->movespeed > self->maxspeed)
			{
				self->velocity.y = self->maxspeed * 1.41;
				self->velocity.x = self->velocity.y * -1;
				self->movespeed = self->maxspeed;
			}
		}
		 else if(PlayerCommands == PI_MovUp)
		{      
			self->velocity.y -= self->accel;
			self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
			//self->grounded = 0;
			if(self->movespeed > self->maxspeed)
			{
				self->velocity.x = 0;
				self->velocity.y = self->maxspeed * -1;
				self->movespeed = self->maxspeed;
			}
		}
		else if(PlayerCommands == PI_MovDown)
		{      
			self->velocity.y += self->accel;
			self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
			//self->grounded = 0;
			if(self->movespeed > self->maxspeed)
			{
				self->velocity.x = 0;
				self->velocity.y = self->maxspeed;
				self->movespeed = self->maxspeed;
			}
			//SpawnThrust(IndexColor(self->Color),self->s.x + 24,self->s.y + 24,0,-1,self->movespeed,self->movespeed * 4);
		}
		*/
	}
	
}
void UpdatePlayer(Entity *self)
{
//	freeSprite(self->sprite); //TODO: Fix this!
	drawSprite(self->sprite, 0,vec2d(self->position.x,self->position.y));
	//Camera stuff
	/*
	_Camera.x = (self->position.x + self->frameW /2) - 400; //<- This 400 is half the screen width
	_Camera.y = (self->position.y + self->frameH /2) - 300; //<- This 300 is half the screen height
	*/
	_Camera.x = (self->position.x + self->frameW /2) - 400; //<- This 400 is half the screen width
	_Camera.y = (self->position.y + self->frameH /2) - 300; //<- This 300 is half the screen height

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
	/*
	int Goframe =0;
	
	Entity *self;
    if (!entSelf)return;
    if (!*entSelf)return;
    self = *entSelf;
	//UpdateEntityPosition(self,0);
	/*
	if(self->grounded == 0)
	{
		if(self->v.y < 20);
		self->v.y += 2;     /*gravity at work/
	}
    
	if(self->state == ST_DIE)
	{
		self->fcount = 10;
		self->state = ST_DEAD;
		return;
	}
	else if(self->state == ST_DEAD)
	{
		self->fcount--;
		if(self->fcount <= 0)
		{
			entity_free(&self);
			exit(0);
		}
		//ExplodingParticle(self->s.x + self->origin.x,self->s.y + self->origin.y,crandom(),crandom());
		return;
	}
	else
	{
		self->state = ST_IDLE;
	}
	if(self->fcount <= 0)
	{
		Goframe = 1;
		self->fcount = self->frate;
	}
	else
	{
		self->fcount--;
    }
	if(!Goframe)return;
	else GetFace(self);/*check out movement vector to see what direction we are facing.*/
	//return;		//TODO
	/*
      
  if(self->state == ST_ATTACK1)
  {
    self->frame++;
    switch(self->aimdir)
    {
      case F_South:
        if(self->frame > 2)self->frame = 0;
        break;
      case F_SW:
        if((self->frame > 5)||(self->frame < 3))self->frame = 3;
        break;
      case F_West:
        if((self->frame > 8)||(self->frame < 6))self->frame = 6;
        break;
      case F_NW:
        if((self->frame > 11)||(self->frame < 9))self->frame = 9;
        break;
      case F_North:
        if((self->frame > 14)||(self->frame < 12))self->frame = 12;
        break;
      case F_NE:
        if((self->frame > 17)||(self->frame < 15))self->frame = 15;
        break;
      case F_East:
        if((self->frame > 20)||(self->frame < 18))self->frame = 18;
        break;
      case F_SE:
        if((self->frame > 23)||(self->frame < 21))self->frame = 21;
        break;
      default:
        self->frame = 0;
    }
  }
  */
}

void UpdateInput()
{
	SDL_Event event;
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	while(SDL_PollEvent( &event))
	{
		switch(event.type)
		{
		case SDL_KEYDOWN:
		if (keys[SDL_GetScancodeFromKey(SDLK_LEFT)])
		{
			PlayerCommands = PI_MovLeft;
		}
		if (keys[SDL_GetScancodeFromKey(SDLK_RIGHT)])
		{
			PlayerCommands = PI_MovRight;
		}
        break;

		case SDL_KEYUP:
        PlayerCommands = PI_NULL;
        break;

		default:
        break;
		}
	}
	/*
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_GetScancodeFromKey(SDLK_LEFT)])
	{
		PlayerCommands = PI_MovLeft;
	}
	if (keys[SDL_GetScancodeFromKey(SDLK_RIGHT)])
	{
		PlayerCommands = PI_MovRight;
	}
	*/
}
	 

//Doesn't work
/*
void DefaultConfig()
{
	KeyButtons[PI_MovLeft] = SDLK_LEFT;
	KeyButtons[PI_MovRight] = SDLK_RIGHT;
	KeyButtons[PI_MovDown] = SDLK_DOWN;
	KeyButtons[PI_MovUp] = SDLK_UP;
	KeyButtons[PI_Fire] = SDLK_x; 
	KeyButtons[PI_Jump] = SDLK_z;
	KeyButtons[PI_Pause] = SDLK_p;
	KeyButtons[PI_Powerup1] = SDLK_1;
	KeyButtons[PI_Powerup2] = SDLK_2;
	KeyButtons[PI_Powerup3] = SDLK_3;
	KeyButtons[PI_Powerup4] = SDLK_4;
}
*/
void DummyThink(Entity *self)
{
	UpdateDummy(self);
}
void UpdateDummy(Entity *self)
{
	SDL_Rect camera;
	Vec2d position;
	camera = camera_get_active_camera();
	position.x = self->position.x - camera.x;
    position.y = self->position.y - camera.y;
	drawSprite(self->sprite, 0,position);
}