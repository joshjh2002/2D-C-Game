#include "common.h"
#include "math.h"

static void tick(void);

void initEmitter(char* line)
{
	Entity* e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->health = 1;

	e->texture = loadTexture("gfx/emitter.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
}

static void tick(void)
{
	float distance = sqrt(pow((player->x - self->x), 2) + pow((player->y - self->y), 2));
	//if the player gets within 250 pixels of the enemy 
	//and it hasn't spawned a fireball for a second, it will fire a fireball at the enemy
	if (distance < 250 && self->value > 60)
	{
		initFireball(self->x, player->x, self->y, player->y, self);
		self->value = 0;
	}
	self->value++;
}
