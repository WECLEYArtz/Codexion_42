#include "../dependencies.h"
#include "../coder/coder.h"

typedef struct s_sim {
	t_coder** coders;
	t_params* params;
	pthread_mutex_t print_mutex;
	bool shutdown;
} t_sim;
