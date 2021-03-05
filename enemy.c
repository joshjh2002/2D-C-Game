#include "common.h"
void tick(void);
void touch(Entity* other);

//initialises enemy
void initEnemy(char* line)
{
	Entity* e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f %f %f", &e->sx, &e->sy, &e->ex, &e->ey);

	e->health = 1;

	e->x = e->sx;
	e->y = e->sy;

	e->tick = tick;
	e->touch = touch;

	e->texture = loadTexture("gfx/enemy.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
}

void tick(void)
{
	if (abs(self->x - self->sx) < ENEMY_SPEED && abs(self->y - self->sy) < ENEMY_SPEED)
	{
		calcSlope(self->ex, self->ey, self->x, self->y, &self->dx, &self->dy);

		self->dx *= ENEMY_SPEED;
		self->dy *= ENEMY_SPEED;
	}

	if (abs(self->x - self->ex) < ENEMY_SPEED && abs(self->y - self->ey) < ENEMY_SPEED)
	{
		calcSlope(self->sx, self->sy, self->x, self->y, &self->dx, &self->dy);

		self->dx *= ENEMY_SPEED;
		self->dy *= ENEMY_SPEED;
	}
}

void touch(Entity* other)
{
	if (self->health > 0 && other == player)
	{
		self->health = 0;

		//the player is above self
		if (!(self->y - self->h / 2 > other->y - other->h / 2))
		{
			other->health--;
		}
	}
}