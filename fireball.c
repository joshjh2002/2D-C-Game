#include "common.h"

static void tick(void);
static void touch(Entity* other);
void extendDistance(Entity* e);

void initFireball(float sx, float ex, float sy, float ey, Entity* spawner)
{
	printf("FIREBALL SPAWNED\n");
	Entity* e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	e->health = 1;
	
	e->sx = sx;
	e->ex = ex;
	e->sy = sy;
	e->ey = ey;

	e->x = e->sx;
	e->y = e->sy;

	e->tick = tick;
	e->touch = touch;

	extendDistance(e);

	e->texture = loadTexture("gfx/fireball.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;

	e->spawner = spawner;

}

static void tick(void)
{
	//check if fireball has reached its end coordinates
	if (self->x == self->ex && self->y == self->ey)
	{
		self->health = 0;
		return;
	}
	if (abs(self->x - self->sx) < FIREBALL_SPEED && abs(self->y - self->sy) < FIREBALL_SPEED)
	{
		calcSlope(self->ex, self->ey, self->x, self->y, &self->dx, &self->dy);

		self->dx *= FIREBALL_SPEED;
		self->dy *= FIREBALL_SPEED;
	}

	if (abs(self->x - self->ex) < FIREBALL_SPEED && abs(self->y - self->ey) < FIREBALL_SPEED)
	{
		calcSlope(self->sx, self->sy, self->x, self->y, &self->dx, &self->dy);

		self->dx *= FIREBALL_SPEED;
		self->dy *= FIREBALL_SPEED;
	}
	
	//when the fireball is on the ground it despawns
	float gradient;
	if (self->ex == self->sx)
	{
		gradient = INFINITY;
	}
	else if (self->ey == self->sy)
	{
		gradient = 0;
	}
	else
	{
		gradient = (self->ey - self->sy) / (self->ex - self->sx);
	}

	//checks is the player fireball has stopped moving
	if (self->health > 0 && (gradient == 0 && self->dx == 0) 
		|| (gradient == INFINITY && self->dy == 0) || (self->isOnGround) 
		|| (gradient != 0 && gradient != INFINITY && (self->dy == 0 || self->dx == 0)))
	{
		self->health = 0;
	}
}

static void touch(Entity* other)
{
	//collides with player
	if (self->health > 0 && other == player)
	{
		self->health = 0;
		player->health--;
	}
	else if (self->health > 0 && other != self->spawner) //when touching other entities that is not it's spawner
	{
		self->health = 0;
	}
}

void extendDistance(Entity* e)
{
	//gradient determines the change in y for every x unit
	float gradient;
	if (e->ex == e->sx)
	{
		gradient = INFINITY;
	}
	else if (e->ey == e->sy)
	{
		gradient = 0;
	}
	else
	{
		gradient = (e->ey - e->sy) / (e->ex - e->sx);
	}

	
	//if gradient is infinity, then it goes directly up or down
	if (gradient == INFINITY)
	{
		if (e->ey > e->sy)
		{
			e->ey = 200000;
		}
		else
		{
			e->ey = 0;
		}
	}
	//if gradient is 0, then it does left or right
	else if (gradient == 0)
	{
		e->ex *= 200;
	}

	//direction determines which side of the fireball the player is
	float direction = e->ex - e->sx;

	//if the player is on the left
	if (direction < 0)
	{			
		e->ex = 0;
		e->ey = gradient * (e->ex - e->sx) + e->sy;
	}
	//if player is on the right
	else if (direction > 0)
	{
		e->ex = 200000;
		e->ey = gradient * (e->ex - e->sx) + e->sy;
	}
}