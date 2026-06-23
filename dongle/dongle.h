#ifndef DONGLE_H
#define DONGLE_H

#include "../dependencies.h"

typedef struct s_dongle {
	t_coder* duel_slots[2];
	int cooldown;
	void (*request)(int id);
	void (*letgo)(int id);
	// scheduler: probably function pointer that takes the heap and return what's used
} t_dongle;

#endif
