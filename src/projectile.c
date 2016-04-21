#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "entity.h"
#include "simple_logger.h"
#include "camera.h"
#include "player.h"

#define PI	3.141589

extern int deltaTime;

Entity *SpawnProjectile(int sx,int sy,float angle,float speed,float accel,int damage,int type)
{
	float cosine, sine;
	Entity *newent = NULL;
	newent = entity_new(); 
	if (newent == NULL)
	{
		fprintf(stderr, "Unable to generate player entity; %s", SDL_GetError());
		exit(0);
	}
	if(type == 1)
	{
		strcpy(newent->name,"Projectile");
	}
	else if(type == 2)
	{
		strcpy(newent->name,"EnemyProjectile1");
	}
	else if(type == 3)
	{
		strcpy(newent->name,"EnemyProjectile2");
	}
	else if(type == 4)
	{
		strcpy(newent->name,"EnemyProjectile3");
	}
	else if(type == 5)
	{
		strcpy(newent->name,"EnemyProjectile4");
	}
	newent -> damage = damage;
	newent -> cameraEnt = 1;
	newent -> position.x  = sx;
	newent -> position.y = sy;
	newent -> lastPosition.x = newent-> position.x;
	newent -> lastPosition.y = newent-> position.y;
	newent -> velocity.x = speed;
	newent -> velocity.y = speed;
	if(accel != 0)
	{
		newent -> velocity.x = speed;
		newent -> velocity.y = speed;
		newent -> accel = accel;
	}
	newent -> movespeed = (int)speed;
	newent -> maxspeed = (int)speed;
	return newent;
}
Entity *SpawnBullet(Entity *owner,int sx,int sy,float angle,float speed,float accel, int damage,int powerup,int type)
{
	Entity *newent = NULL;
	newent = SpawnProjectile(sx,sy,angle,speed,accel,damage,type);
	if(newent == NULL)
	{
		slog("This bullet has not been created!!");
		return NULL;
	}
	newent -> frame = 0;
	newent -> frate = 30;
	newent -> timer = 2000;
	newent -> facing = owner->facing;
	switch(powerup)
	{
		case 0:
			newent->sprite = loadSprite("images/bullet.png",9,9,1);
			newent -> offset.x = 18;
			newent -> offset.y = 12;
			newent -> bounds.x = 0;
			newent -> bounds.y = 0;
			newent -> bounds.w = 9;
			newent -> bounds.h = 9;
			newent -> frameW = 9;
			newent -> frameH = 9;
			break;
		case 1:
			newent->sprite = loadSprite("images/bigbullet.png",16,16,1);
			newent -> offset.x = 18;
			newent -> offset.y = 12;
			newent -> bounds.x = 1;
			newent -> bounds.y = 1;
			newent -> bounds.w = 16;
			newent -> bounds.h = 16;
			newent -> frameW = 16;
			newent -> frameH = 16;
			break;
		case 2:
			newent->sprite = loadSprite("images/firebullet.png",17,10,1);
			newent -> offset.x = 18;
			newent -> offset.y = 12;
			newent -> bounds.x = 1;
			newent -> bounds.y = 1;
			newent -> bounds.w = 17;
			newent -> bounds.h = 10;
			newent -> frameW = 17;
			newent -> frameH = 10;
			break;
		case 3:
			newent->sprite = loadSprite("images/bluefirebullet.png",30,16,1);
			newent -> offset.x = 18;
			newent -> offset.y = 12;
			newent -> bounds.x = 1;
			newent -> bounds.y = 1;
			newent -> bounds.w = 30;
			newent -> bounds.h = 16;
			newent -> frameW = 30;
			newent -> frameH = 16;
			break;
		default:
			newent->sprite = loadSprite("images/bullet.png",9,9,1);
			newent -> offset.x = 18;
			newent -> offset.y = 12;
			newent -> bounds.x = 1;
			newent -> bounds.y = 1;
			newent -> bounds.w = 9;
			newent -> bounds.h = 9;
			newent -> frameW = 9;
			newent -> frameH = 9;
			break;
	}
//	newent -> update = UpdateBullet;
//	newent -> think = BulletThink;
	return newent;

}

void UpdateBullet(Entity *self)
{
	Entity *target = NULL;
	if(self -> timer > 0)
	{
		self-> timer -= deltaTime;
	}
	if(self-> timer <= 0)
	{
		entity_free(self);
		//slog("bullet has been freed");
	}
	//Facing left neutral
	if(self->facing == 0)
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
		self->position.x -= self->velocity.x;
		/* Diagonal up left
		self-> velocity.y = self-> velocity.x * sin(PI / 8 );
		self-> velocity.x = self-> velocity.x * cos(PI / 8 );
		self-> velocity.y *= -1;
		self->position.x += self->velocity.x;
		self->position.y += self->velocity.y;
		*/
	}
	//Facing left and up
	if(self->facing == 1 )
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
		self-> velocity.y = self-> velocity.x * sin(PI / 8 );
		self-> velocity.x = self-> velocity.x * cos(PI / 8 );
		self-> velocity.y *= -1;
		self->position.x -= self->velocity.x;
		self->position.y += self->velocity.y;
	}
	//Facing left and down
	if(self->facing == 2 )
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
		self-> velocity.y = self-> velocity.x * sin(PI / 8 );
		self-> velocity.x = self-> velocity.x * cos(PI / 8 );
		self->position.x -= self->velocity.x;
		self->position.y += self->velocity.y;
	}
	//Facing right neutral
	if(self->facing == 3 )
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
	}
	//Facing right and up
	if(self->facing == 4 )
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
		self-> velocity.y = self-> velocity.x * sin(PI / 8 );
		self-> velocity.x = self-> velocity.x * cos(PI / 8 );
		self-> velocity.y *= -1;
		self->position.x += self->velocity.x;
		self->position.y += self->velocity.y;
	}
	//Facing right and down
	if(self->facing == 5 )
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
		self-> velocity.y = self-> velocity.x * sin(PI / 8 );
		self-> velocity.x = self-> velocity.x * cos(PI / 8 );
		self->position.x += self->velocity.x;
		self->position.y += self->velocity.y;
	}
	//Facing up
	if(self->facing == 6 || self-> facing == 7 )
	{
		self->velocity.x += self->accel;
		self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
		//self->grounded = 0;
		if(self->movespeed > self->maxspeed)
		{
			self->velocity.y = self->maxspeed;
			self->movespeed = self->maxspeed;
		}
		self->position.y -= self->velocity.y;
	}
	self -> lastPosition = self-> position;
}
void BulletThink(Entity *self)
{
	UpdateBullet(self);
}

Entity *SpawnEnemyBullet(Entity *owner,int sx,int sy,float angle,float speed,float accel, int damage,int type, int enType)
{
	Entity *newent = NULL;
	newent = SpawnProjectile(sx,sy,angle,speed,accel,damage,enType);
	switch(type)
	{
		case 1:
			newent->sprite = loadSprite("images/enemybullet2.png",8,4,1);
			newent -> offset.x = 0;
			newent -> offset.y = 12;
			newent -> bounds.x = 0;
			newent -> bounds.y = 0;
			newent -> bounds.w = 8;
			newent -> bounds.h = 4;
			newent -> frameW = 8;
			newent -> frameH = 4;
			newent -> frame = 0;
			newent -> frate = 30;
			newent -> timer = 1000;
			break;
		case 2:
			newent->sprite = loadSprite("images/firebullet.png",17,10,1);
			newent -> offset.x = 0;
			newent -> offset.y = 12;
			newent -> bounds.x = 0;
			newent -> bounds.y = 0;
			newent -> bounds.w = 17;
			newent -> bounds.h = 10;
			newent -> frameW = 8;
			newent -> frameH = 3;
			newent -> frame = 0;
			newent -> frate = 30;
			newent -> timer = 250;
			break;
		case 3:
			newent->sprite = loadSprite("images/firebullet.png",17,10,1);
			newent -> offset.x = 0;
			newent -> offset.y = 12;
			newent -> bounds.x = 0;
			newent -> bounds.y = 0;
			newent -> bounds.w = 17;
			newent -> bounds.h = 10;
			newent -> frameW = 17;
			newent -> frameH = 10;
			newent -> frame = 0;
			newent -> frate = 30;
			newent -> timer = 3000;
			break;
		case 4:
			newent->sprite = loadSprite("images/bossbullet.png",16,14,1);
			newent -> offset.x = 0;
			newent -> offset.y = 0;
			newent -> bounds.x = 0;
			newent -> bounds.y = 0;
			newent -> bounds.w = 16;
			newent -> bounds.h = 14;
			newent -> frameW = 16;
			newent -> frameH = 14;
			newent -> frame = 0;
			newent -> frate = 30;
			newent -> timer = 3000;
			break;
	}
}
void UpdateEnemyBullet(Entity *self,int type)
{
	if(self -> timer > 0)
	{
		self-> timer -= deltaTime;
	}
	if(self-> timer <= 0)
	{
		entity_free(self);
		//slog("bullet has been freed");
	}
	switch(type)
	{
		case 1:
			self->velocity.x += self->accel;
			self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
				//self->grounded = 0;
				if(self->movespeed > self->maxspeed)
				{
					self->velocity.y = 0;
					self->velocity.x = self->maxspeed;
					self->movespeed = self->maxspeed;
				}
				self->position.x -= self->velocity.x;
			break;
		case 2:
			self->velocity.x += self->accel;
			self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
			//self->grounded = 0;
			if(self->movespeed > self->maxspeed)
			{
				self->velocity.y = 0;
				self->velocity.x = self->maxspeed;
				self->movespeed = self->maxspeed;
			}
			self->position.x -= self->velocity.x;
			break;
		case 3:
			self->velocity.x += self->accel;
			self->velocity.y -= self->accel;
			self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
				//self->grounded = 0;
				if(self->movespeed > self->maxspeed)
				{
					self->velocity.x = self->velocity.y * -1;
					self->velocity.x = self->maxspeed;
					self->movespeed = self->maxspeed;
				}
				self->position.x -= self->velocity.x;
				self->position.y -= self->velocity.y;
				break;
		case 4:
			self->velocity.x += self->accel;
			self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
				//self->grounded = 0;
				if(self->movespeed > self->maxspeed)
				{
					self->velocity.y = 0;
					self->velocity.x = self->maxspeed;
					self->movespeed = self->maxspeed;
				}
				self->position.x -= self->velocity.x;
				break;
		//break;
	}
	self -> lastPosition = self-> position;
}
/*
	GetFace(owner);
	//Getting the correct offset to shoot from depending on where the player is facing
	if(owner -> face == F_East || owner -> face == F_NE || owner -> face == F_SE)
	{
		newent-> offset.x = owner->position.x + 10; 
		newent -> movespeed = speed;
	}
	if(owner -> face == F_West || owner -> face == F_NW || owner -> face == F_SW)
	{
		newent-> offset.x = owner->position.x - 2;
		newent -> movespeed = speed * -1;
	}
	if(owner -> face == F_NE)
	{
		newent -> offset.y = owner -> position.y - 2; 
	}
	if(owner -> face == F_SE)
	{
		newent -> offset.y = owner -> position.y + 2; 
	}
	if(owner -> face == F_NW)
	{
		newent -> offset.y = owner -> position.y - 2; 
	}
	if(owner -> face == F_SW)
	{
		newent -> offset.y = owner -> position.y + 2; 
	}

*/