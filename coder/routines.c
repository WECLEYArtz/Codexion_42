#include "../dependencies.h"
#include "../parser/parser.h"
#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "../simulation/simulation.h"

void compile(t_coder *coder)
{
	coder->dongle_l->request(coder->id);
	announce(coder, "compiling\n");
	sleep(coder->sim->params.time_to_compile);
}


void debug(t_coder *coder)
{
	announce(coder, "refactoring\n");
	sleep(coder->sim->params.time_to_debug);
}


void refactor(t_coder *coder)
{
	announce(coder, "refactoring\n");
	sleep(coder->sim->params.time_to_refactor);
}


void announce(t_coder* coder, char *action)
{
	t_timeval current; 
	gettimeofday(&current, NULL); // search what goes instead of Null
	pthread_mutex_lock(&coder->sim->print_mutex);
	printf("%d %d is %s\n"
			,(int)(current.tv_sec - coder->sim->startup.tv_sec) , coder->id, action);
	pthread_mutex_unlock(&coder->sim->print_mutex);
}
