#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "simulation.h"

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
