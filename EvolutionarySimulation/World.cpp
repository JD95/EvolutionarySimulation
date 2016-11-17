#include "World.h"



Environment::World::World()
{
}


Environment::World::~World()
{
}

float Environment::World::total_diversity()
{
	return populations.size() * POPULATION_IMPORTANCE 
		 + (std::accumulate(populations.begin(), populations.end(), 0,
			[](Population p, float d) { return p.diversity() + d; }) / populations.size());
}
