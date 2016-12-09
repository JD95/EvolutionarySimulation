#include "NaturalResource.h"
#include "Interaction.h"
#include <time.h>
#include <random>


Environment::NaturalResource::NaturalResource()
{
}

Environment::NaturalResource::NaturalResource(int capacity)
	: max_capacity(capacity)
{
}


Environment::NaturalResource::~NaturalResource()
{
}

bool Environment::NaturalResource::add_organism(DNA::Organism * o)
{
	if (current_load.size() < max_capacity) {
		current_load.push_back(o);
		return true;
	}
		
	else return false;
}

bool Environment::NaturalResource::challenge_organism(DNA::Organism* o)
{
	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> spot(0, current_load.size() - 1);

	int defender_i = spot(engine);
	auto defender = current_load[defender_i];

	bool successful = attack(o->get_traits(OffensiveTool), defender->get_traits(DefensiveTool));

	if (successful) {
		current_load[defender_i] = o;
		return true;
	}
	else return false;
}

void Environment::NaturalResource::feed_current_load()
{
	for (auto& o : current_load)
		o->give_resources();
}
