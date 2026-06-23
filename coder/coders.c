#include "../coder/coder.h"
#include "../simulation/simulation.h"

static void coder_post_creation_action(t_coder *self)
{
	int sleep_time =
		self->sim->params->time_to_compile +
		self->sim->params->dongle_cooldown;
		
	bool nigger = self->id % 2;
	if (nigger)
	{
		while(!self->sim->running)
			sleep(sleep_time);
	}
	else
	{
		while(!self->sim->running)
			pthread_cond_wait(
					&self->birth_control,
					&self->sim->running_mutex);
	}
	// wether to pick the coder
	// or sleep until then others are done compiling + 
}


void *coder_routine(void* coder_p)
{
	t_coder *self = coder_p;

	int routine_turn;
	void (*rotines[3])(t_coder *) = {
		compile, debug, refactor
	};

	coder_post_creation_action(self);

	routine_turn = 0;
	while(self->sim->running)
	{
		if (routine_turn == 3)
			routine_turn =	0;
		rotines[routine_turn++ - 1 % 3](self);
	}
	return NULL;
}
