#include "World.h"



World::World()
{
}


World::~World()
{
}

float World::total_diversity()
{
	return populations.size() * POPULATION_IMPORTANCE 
		 + (std::accumulate(populations.begin(), populations.end(), 0,
			[](Population p, float d) { return p.diversity() + d; }) / populations.size());
}
