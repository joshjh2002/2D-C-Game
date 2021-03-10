#include "common.h"

static void tick(void);
static void touch(Entity* other);

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

	e->texture = loadTexture("gfx/fireball.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;

	e->spawner = spawner;

}

static void tick(void)
{
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

	//the fireball will keep going
	self->ex *= 1.1;
	self->ey *= 1.1;

	if (self->health > 0 && self->isOnGround)
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
