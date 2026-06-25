#include "dependencies.h"
#include "simulation/simulation.h"
#include "parser/parser.h"
#include "coder/coder.h"
#include "dongle/dongle.h"

// Initialise the simulation,
// - create the simulation structure.
// - allocate the needed size to fill up with all coders, indexed by their id.
// - get the parsed parameters.
// - initialise the mutexes to be used later.

static void insert_new_dongle(int index, t_sim *sim)
{
	t_dongle dongle;

	dongle.cooldown = sim->params.dongle_cooldown;
	sim->dongles[index] = dongle;
}


static void insert_new_coder(int index, t_sim *sim)
{
	int coders_count_to_mod = sim->params.number_of_coders;
	t_coder coder;

	if(pthread_create(
				&(coder.thread), NULL, coder_routine, sim->coders + index))
		exit(puts("DEBUG: Failed to create a thread"));

	coder.id = index + 1;
	coder.sim = sim;
	coder.time_to_burnout = sim->params.time_to_burnout;

	coder.dongle_l = &(sim->dongles[index]);
	coder.dongle_r = &(sim->dongles[(index+1) % coders_count_to_mod]);
	
	sim->coders[index] = coder;
}


void init_dongles(t_sim *sim)
{
	sim->dongles = malloc(sizeof(t_dongle) * sim->params.number_of_coders);
	if (!sim->dongles)
		exit(puts("DEBUG: Failed allocation, must free"));
	
	int dongle_order;
	dongle_order = 0;
	while(dongle_order < sim->params.number_of_coders)
		// create and append all dongles
		insert_new_dongle(dongle_order++, sim);
}


void init_coders(t_sim *sim)
{
	sim->coders = malloc(sizeof(t_coder) * sim->params.number_of_coders);
	if (!sim->coders)
		exit(puts("DEBUG: Failed allocation, must free"));

	int coder_order;
	coder_order = 0;
	while(coder_order < sim->params.number_of_coders)
		// create and append all coders
		insert_new_coder(coder_order++, sim);
}


t_sim init_simulation(t_params params) {
	t_sim sim;

	init_dongles(&sim);
	init_coders(&sim);
	sim.params = params;

	pthread_mutex_init(&sim.running_mutex, NULL);
	pthread_mutex_init(&sim.birth_mutex, NULL);
	pthread_mutex_init(&sim.print_mutex, NULL);

	sim.running = false;
	sim.birth_wake = false;

	return sim;
}


// here is the main brosha-shisha
int main(int argc, char **argv)
{
	if (argc != 9)
		return -1;
	getparams(argv);
	t_sim sim = init_simulation(getparams(argv));



	printf("\
	time_to_debug : %d \n\
	time_to_burnout : %d \n\
	time_to_compile : %d \n\
	time_to_debug : %d \n\
	time_to_refactor : %d \n\
	number_of_coders : %d \n\
	dongle_cooldown : %d \n\
	scheduler : %d where (1)edf - (2)fifo \n",\

	sim.params.time_to_debug,
	sim.params.time_to_burnout,
	sim.params.time_to_compile,
	sim.params.time_to_debug,
	sim.params.time_to_refactor,
	sim.params.number_of_coders,
	sim.params.dongle_cooldown,
	sim.params.scheduler);
}
