#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL.h>

#include "player.h"
#include "graphics.h"
#include "entity.h"
#include "projectile.h"
#include "simple_logger.h"
#include "camera.h"

extern SDL_Surface *screen;
extern Entity *ThePlayer;
extern SDL_Rect _Camera;
extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;
extern int deltaTime;

enum PlayerInputs {PI_NULL,PI_MovLeft,PI_MovRight,PI_MovDown,PI_MovUp,PI_Fire,PI_Jump,PI_MovUpLeft,PI_MovDownLeft,PI_MovUpRight,PI_MovDownRight,
                   PI_Pause,PI_Powerup1,PI_Powerup2,PI_Powerup3,PI_Powerup4,PI_Powerup5,PI_Max};


Uint32 KeyButtons[PI_Max];

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
	newent->sprite = loadSprite("images/ryuSprite2.png",17,33,1);
	//newent->sprite-> imageSize.x = 32;
	//newent->sprite-> imageSize.y = 32;
	newent -> frameW = 17;	//TODO: make sure that this is always accurate
	newent -> frameH - 33; //TODO: make sure that this is always accurate
	newent -> update = UpdatePlayer;
	newent -> think = PlayerThink;
	newent -> maxhealth = 100;
	newent -> health = 100;
	newent -> cameraEnt = 1;
	newent -> frame = 0;
	newent -> bounds.x = 0;
	newent -> bounds.y = 0;
	newent -> bounds.w = 17;
	newent -> bounds.h = 33;
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
	newent -> jumpAccel = 1;
	newent -> maxJumpSpeed = 5;
	newent -> timer = 0;
	newent -> powerup = 0;
	//drawSprite(newent ->sprite, 5,vec2d(x,y));
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
	newent -> cameraEnt = 1;
	newent -> position.x = x;
	newent -> position.y = y;
	newent -> velocity.x = 0;
	newent -> velocity.y = 0;
	newent -> maxspeed = 3;
	newent -> movespeed = 0;
	newent -> accel = 2;
	newent -> bounds.x = x;
	newent -> bounds.y = y;
	newent -> bounds.w = 200;
	newent -> bounds.h = 200;
	newent -> state = 0;
	newent -> grounded = 1;
	//entity_draw(newent, gt_graphics_get_active_renderer());
	//drawSprite(newent ->sprite, 0,vec2d(x,y));
	UpdateDummy(newent);
	//ThePlayer = newent;
	return newent;
	//atexit(FinalOutput);

}

void PlayerThink(Entity *self)
{
	int moving = 0;
	float t; 
	char text [40];
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	
	UpdateInput();
	GetFace(self);
	if((self->state != ST_DEAD) && (self-> state != ST_DIE))
	{
		
		if(PlayerCommands & (1<<PI_MovLeft))
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
			moving = 1;
			//SpawnThrust(IndexColor(self->Color),self->s.x + 24,self->s.y + 24,2,0,self->movespeed,self->movespeed * 4);
		}
		
		if(PlayerCommands & (1<< PI_MovRight))
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
			moving = 1;
			//SpawnThrust(IndexColor(self->Color),self->s.x + 24,self->s.y + 24,-2,0,self->movespeed,self->movespeed * 4);
		}
		 if(PlayerCommands & (1<< PI_MovUp))
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
			self->position.y += self->velocity.y;
			moving = 1;
		}
		 if(PlayerCommands & (1<< PI_MovDown))
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
			self->position.y += self->velocity.y;
			moving = 1;
			//SpawnThrust(IndexColor(self->Color),self->s.x + 24,self->s.y + 24,0,-1,self->movespeed,self->movespeed * 4);
		}

		if(PlayerCommands & (1<< PI_Jump) && self->timer <= 0)
		{   
			self-> timer = 500;
			moving = 1;
		}
		if( moving == 0)
		{
			self-> velocity.x = 0;
			self-> velocity.y = 0;
		}
		if(PlayerCommands & (1<< PI_Fire) && self->bulletTimer <=0 && self->powerup == 0)
		{
			self-> bulletTimer = 750;
			SpawnBullet(self,self->position.x + self-> offset.x,self->position.y + self->offset.y,0,5,1,5,0);
		}
		if(PlayerCommands & (1<< PI_Fire) && self->bulletTimer <=0 && self->powerup == 1)
		{
			self-> bulletTimer = 750;
			SpawnBullet(self,self->position.x + self-> offset.x,self->position.y + self->offset.y,0,5,1,10,1);
		}
		if(PlayerCommands & (1<< PI_Fire) && self->bulletTimer <=0 && self->powerup == 2)
		{
			self-> bulletTimer = 300;
			SpawnBullet(self,self->position.x + self-> offset.x,self->position.y + self->offset.y,0,5,1,5,2);
		}
		if(PlayerCommands & (1<< PI_Fire) && self->bulletTimer <=0 && self->powerup == 3)
		{
			self-> bulletTimer = 300;
			SpawnBullet(self,self->position.x + self-> offset.x,self->position.y + self->offset.y,0,5,1,10,3);
		}
		if(PlayerCommands & (1<< PI_Powerup1))
		{ 
			GivePlayerPowerUp(self, 0);
			
		}
		if(PlayerCommands & (1<< PI_Powerup2))
		{ 
			GivePlayerPowerUp(self, 1);
		}
		if(PlayerCommands & (1<< PI_Powerup3))
		{ 
			GivePlayerPowerUp(self, 2);
		}
		if(PlayerCommands & (1<< PI_Powerup4))
		{ 
			GivePlayerPowerUp(self, 3);
		}
		if(PlayerCommands & (1<< PI_Powerup5))
		{ 
			GivePlayerPowerUp(self, 4);
		}
	UpdatePlayer(self);

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
void GivePlayerPowerUp(Entity *self,int power)
{
	switch(power)
	{
	case 0:
		self -> powerup = 0;
		slog("power up 0 obtained!");
		break;
	case 1:
		self -> powerup = 1;
		slog("power up 1 obtained!");
		break;
	case 2:
		self -> powerup = 2;
		slog("power up 2 obtained!");
		break;
	case 3:
		self -> powerup = 3;
		slog("power up 3 obtained!");
		break;
	case 4:
		self -> powerup = 4;
		self -> sprite = loadSprite("images/bigryu.png",90,82,1);
		slog("power up 4 obtained!");
		break;
	default:
		self-> powerup = 0;
	}
}

void UpdatePlayer(Entity *self)
{
	//drawSprite(self->sprite, 0,self->position);
	//Camera stuff
	//slog("player's position: %f %f",self->position.x,self->position.y);
	_Camera.x = (self->position.x + self->frameW /2) - 400; //<- This 400 is half the screen width
	_Camera.y = (self->position.y + self->frameH /2) - 300;//<- This 300 is half the screen height

	
	/*_camera.x = self->position.x;
	_camera.y = self->position.y;*/

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
		//Jumping code 
		if(self->timer > 0)
		{
			self->timer -= deltaTime;
			self->velocity.y -= self->jumpAccel;
			self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
			self->grounded = 1;
			if(self->movespeed > self->maxJumpSpeed)
			{
				self->velocity.y = self->maxJumpSpeed * -1;
				self->movespeed = self->maxJumpSpeed;
			}
			self->position.y += self->velocity.y;
		
		if(self->grounded == 1)
		{
			//self -> velocity.y -= 1;
			//self->position.y += 1;
		}
		}
		else
		{
			//self->position.y += 1;
		}
		if(self->bulletTimer > 0)
		{
			self->bulletTimer -= deltaTime;
		}

}

void UpdateInput()
{
	static int pressed = 0;
	SDL_Event event;
	PlayerCommands = PI_NULL;
	while(SDL_PollEvent( &event))
	{
		switch(event.type)
		{
		case SDL_KEYDOWN:
		if (event.key.keysym.scancode==SDL_SCANCODE_LEFT)
		{
			PlayerCommands |= (1<< PI_MovLeft);

			//PlayerCommands = PI_Fire;
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_RIGHT)
		{
			PlayerCommands |= (1<< PI_MovRight);
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_UP)
		{
			PlayerCommands |= (1<< PI_MovUp);
			//PlayerCommands = PI_Jump;
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_DOWN)
		{
			PlayerCommands |= (1<< PI_MovDown);
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_X)
		{

			PlayerCommands |= (1<< PI_Jump);		
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_C)
		{
			PlayerCommands |= (1<< PI_Fire);		
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_1)
		{
			PlayerCommands |= (1<< PI_Powerup1);		
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_2)
		{
			PlayerCommands |= (1<< PI_Powerup2);		
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_3)
		{
			PlayerCommands |= (1<< PI_Powerup3);		
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_4)
		{
			PlayerCommands |= (1<< PI_Powerup4);		
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_5)
		{
			PlayerCommands |= (1<< PI_Powerup5);		
		}
		break;

		case SDL_KEYUP:

		if (event.key.keysym.scancode==SDL_SCANCODE_X)
		{
			PlayerCommands &= ~(1<< PI_Jump);
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_RIGHT)
		{
			PlayerCommands &= ~(1<< PI_MovRight);
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_UP)
		{
			PlayerCommands &= ~(1<< PI_MovUp);
			//PlayerCommands = PI_Jump;
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_DOWN)
		{
			PlayerCommands &= ~(1<< PI_MovDown);
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_C)
		{
			PlayerCommands &= ~(1<< PI_Fire);
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_1)
		{
			PlayerCommands &= ~(1<< PI_Powerup1);		
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_2)
		{
			PlayerCommands &= ~(1<< PI_Powerup2);		
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_3)
		{
			PlayerCommands &= ~(1<< PI_Powerup3);		
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_4)
		{
			PlayerCommands &= ~(1<< PI_Powerup4);		
		}
		if (event.key.keysym.scancode==SDL_SCANCODE_5)
		{
			PlayerCommands &= ~(1<< PI_Powerup5);		
		}
        break;

		default:
        break;
		}
	}

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
	/*
	SDL_Rect camera;
	Vec2d position;
	camera = camera_get_active_camera();
	position.x = self->position.x - camera.x;
    position.y = self->position.y - camera.y;
	drawSprite(self->sprite, 0,position);
	*/
}