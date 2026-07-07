#ifndef LAUNCH_HANDLER_H
#define LAUNCH_HANDLER_H

# define STOP 0
# define HOLD 1
# define RUN 2
# define STAT 3

bool	sim_running_status(void);
void	sim_stop(void);
void	sim_launch_hold(void);
void	sim_lauch_run(void);

#endif

