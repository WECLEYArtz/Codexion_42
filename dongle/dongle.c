#include "../dependencies.h"
#include "../coder/coder.h"

typedef struct s_dongle
{
	t_coder*	mini_queue[2];
	t_params*	params;
} t_dongle;
