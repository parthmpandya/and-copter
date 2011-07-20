#pragma once

#include "Log.h"

#include <stdlib.h>
#include <time.h>

class Random {

public:

	Random()
	{
		srand48(time(0));
	}

	int next(int max) {
		float rand = lrand48() / (float) RAND_MAX;
		return (int)(rand * max);
	}
};