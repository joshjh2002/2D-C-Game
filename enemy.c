#include "common.h"
static void tick(void);
static void touch(Entity* other);

//initialises enemy
void initEnemy(char* line)
{
	Entity* e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	//sx and sy denote the starting values of x and y respectivly
	//ex and xy store the ending coordinates
	sscanf(line, "%*s %f %f %f %f", &e->sx, &e->sy, &e->ex, &e->ey);

	e->health = 1;

	e->x = e->sx;
	e->y = e->sy;

	e->tick = tick;
	e->touch = touch;

	e->texture = loadTexture("gfx/enemy.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS; //Given the tag weightless so that the enemies don't fall down in air
}

//this will execute once very frame. The enemy speed is defined in common.h
//it moves the enemy from its starting position to end position and back
static void tick(void)
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

static void touch(Entity* other)
{
	//when the player touches the enemy, this will execute
	if (self->health > 0 && other == player)
	{
		//the enemy always dies when the player touches them
		self->health = 0;

		//the player will only take damage if they don't jump on the enemy
		if (!(self->y - self->h / 2 > other->y - other->h / 2))
		{
			other->health--;
		}
	}
}