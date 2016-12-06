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
		 + (std::accumulate(populations.begin(), populations.end(), 0.0f,
			[](float d, Population p) { return p.diversity() + d; }) / populations.size());
}
