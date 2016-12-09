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

void Environment::World::run_generation()
{
	// Each organism attempts to acqurie the resources it needs
		// extract resources required attributes
		// try to acquire resource down the list

	// All natural resources feed their current loads

	// Populations mate
		// Organisms which did not get resources do not get to mate
		// Organisms which are incompatible with any other organism becomes new population


	// New populations are added to world
}
