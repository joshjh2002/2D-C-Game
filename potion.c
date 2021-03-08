#include "common.h"

static void tick(void);
static void touch(Entity* other);

void initPotion(char* line)
{
	Entity* e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->health = 1;

	e->texture = loadTexture("gfx/potion.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = touch;
}

static void tick(void)
{
	//this will make the potion bob up and down
	//I have subtracted 1 so that the bobbing is slightly out of sync to the pizzas sin(x) bobbing
	self->value += 0.1;
	self->y += sin(self->value - 1);
}

static void touch(Entity* other)
{
	//if the potionCount is not 2, only then will the potion be collected
	if (self->health > 0 && other == player && player->potionCount < 2)
	{
		self->health = 0;
		player->potionCount++;
	}
}