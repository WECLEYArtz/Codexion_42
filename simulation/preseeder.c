#include "../coder/coder.h"
#include "../dependencies.h"
#include "../dongle/dongle.h"
#include "./simulation.h"

// This is only supposed to be used after both all coders and the monitor get initialised
//

static void	_preseed_dongles_heap(t_sim *sim)
{
	int		i;
	int		coders_count;
	t_coder	*coder;
	short	priority_order = 0;

	coders_count = sim->args.number_of_coders;
	coder = sim->coders;
	i = 1;
	while(priority_order < 2)
	{
		while (i < coders_count)
		{
			(coder+i)->dongle_r->duel_slots[priority_order] = coder+i;
			(coder+i)->dongle_l->duel_slots[priority_order] = coder+i;
			i += 2;
		}
		i = 0 + 2 * (coders_count > 2  && coders_count % 2);
		priority_order++;
	}
	if (coders_count > 2 && coders_count % 2)
	{
		(coder)->dongle_r->duel_slots[0] = coder;
		(coder)->dongle_l->duel_slots[1] = coder;
	}
}

// static void	preseed_burnoutpq(t_sim *sim)
// {
// }



void	preseeder(t_sim *sim)
{
	_preseed_dongles_heap(sim);
	// preseed_burnoutpq();
}
