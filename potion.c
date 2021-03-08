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
	self->value += 0.1;
	self->y += sin(self->value - 1);
}

static void touch(Entity* other)
{
	//when the player isn't at max health, only then will the potion be collected and used
	if (self->health > 0 && other == player && player->health > player->maxHealth)
	{
		self->health = 0;
		player->health++;
	}
}