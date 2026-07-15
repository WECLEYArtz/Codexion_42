#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "../simulation/simulation.h"

static void	_show(t_dongle *dongle)
{
	static int	i = 0;
	printf("Dongle %d ", dongle->id);
	if (dongle->duel_slots[0])
		printf("[Slot 0 = Coder %d] ", dongle->duel_slots[0]->id);
	else
		printf("[Slot 0 = No Coder] ");
	if (dongle->duel_slots[1])
		printf("[Slot 1 = Coder %d] ", dongle->duel_slots[1]->id);
	else
		printf("[Slot 1 = No Coder] ");
	puts("");
	i++;
}

void	debug_visualise(t_sim *sim)
{
	int			coders_count;
	t_dongle	*dongle;
	int			i;

	coders_count = sim->args.number_of_coders;
	dongle = sim->dongles;
	i = 0;
	while (i < coders_count)
		_show(dongle + i++);
}


static void visualise(t_burnoutpq_node *head, int step)
{
	static pthread_mutex_t hh = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&hh);
	printf("%s\n", step?"[ After ]":"===[ Before ]==========================================");
	int limit = 3;
	while(head && limit--)
	{
		printf(">>> Node: %d\n", head->coder? head->coder->id : 404);
		printf("    Prev: %d - Next: %d\n",
				head->previous? head->previous->coder->id : 404,
				head->next? head->next->coder->id : 404);
		head = head->next;
	}
	printf("%s\n",step?"=======================================================\n":"");
	pthread_mutex_unlock(&hh);
}

