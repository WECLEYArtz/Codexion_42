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
	printf("%s\n", step?"[ After ]":"=============================================\n[ Before ]\n");
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



// t_coder	*burnoutpq_action(short choice, void *pointer)
// {
// 	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
// 	static t_burnoutpq_node	*head = NULL;
// 	t_burnoutpq_node		*tmp;
//
//
// 	pthread_mutex_lock(&mutex);
// 	visualise(head, 0);
// 	if (choice == MVBACK)
// 	{
// 		printf(BLUE"[BQ]: adding coder %d\n"RESET, ((t_burnoutpq_node *)pointer)->coder->id);
// 		_addback(&head, (t_burnoutpq_node *)pointer);
// 	}
// 	else if (choice == POP)
// 	{
// 		printf(YELLOW"[BQ]: extracting coder %d\n"RESET, head->coder->id);
// 		tmp = head;
// 		head = head->next;
// 		tmp->next = NULL;
// 		tmp->previous = NULL;
// 		if (head)
// 			head->previous = NULL;
// 		visualise(head, 1);
// 		return (pthread_mutex_unlock(&mutex), tmp->coder);
// 	}
// 	else if (choice == MWATCH)
// 		while (!head)
// 			pthread_cond_wait(&((t_monitor *)pointer)->general_cond, &mutex);
// 	else if (choice == GWAKE)
// 		pthread_cond_signal((pthread_cond_t *)pointer);
// 	visualise(head, 1);
// 	pthread_mutex_unlock(&mutex);
//
// 	return (NULL);
// }
