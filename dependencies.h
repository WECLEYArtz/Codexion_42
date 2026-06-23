#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct s_sim t_sim;
typedef struct s_coder t_coder;
typedef struct s_dongle t_dongle;
typedef struct s_params t_params;

typedef struct timeval t_timeval;

// Util functions
void announce(t_coder* coder, char *action);
t_params* getparams(char **args);

#endif
