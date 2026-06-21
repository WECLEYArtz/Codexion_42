#include "../dependencies.h"
#include "../coder/coder.h"
#include <sys/time.h>

void print_report(t_coder* coder, t_sim sim, char *action)
{
	// mutex lock
	t_timeval current;
	gettimeofday(&current, NULL); // search what goes instead of Null
	printf("%d %d is %s\n"
			, ,coder->id, action);
	// mutex unlock
}
