#include "../dependencies.h"
#include "../parser/parser.h"

typedef struct s_sim {
	t_dongle* dongles;
	t_coder* coders;

	t_params params;
	t_timeval startup;

	pthread_mutex_t print_mutex;
	pthread_mutex_t running_mutex;
	pthread_mutex_t birth_mutex;
	bool running;
	bool birth_wake;
} t_sim;
