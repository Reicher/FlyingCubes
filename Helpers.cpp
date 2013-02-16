#include "Helpers.h"

int getRandom(int min, int max)
{
	int range = max - min + 1;

	if(range < 0)
		printf("Error getRamdom(Int): min > max \n");

	return (rand() % range) + min;
}

float getRandom(float min, float max)
{
  float range = max-min;
  return min + (float) rand() / ((float)RAND_MAX/range);
}
