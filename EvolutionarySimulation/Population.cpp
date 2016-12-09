#include "Population.h"
#include "Interaction.h"


Environment::Population::Population()
{
}

Environment::Population::Population(std::string gene, int size, int pop_index)
{
	organisms.reserve(size);

	for (int i = 0; i < size; i++)
	{
		organisms.emplace_back(DNA::Organism(DNA::mutate(gene), pop_index));
	}

	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> name_length_seg(1, 3);
	std::uniform_int_distribution<int> name_seg(0, pop_name_seg.size() - 1);
	std::uniform_int_distribution<int> ending(0, pop_name_ending.size() - 1);

	int length = name_length_seg(engine);
	name = "";

	for (int i = 0; i < length; i++)
		name += pop_name_seg[name_seg(engine)];

	name += pop_name_ending[ending(engine)];
}


Environment::Population::~Population()
{
}

float Environment::Population::diversity()
{
	float total = 0;

	for (auto organism : organisms) {
		for (auto other : organisms) {

			auto p1 = organism.get_phenotype();
			auto p2 = other.get_phenotype();
			std::vector<Attribute> diff;

			std::set_difference(p1.begin(), p1.end(), p2.begin(), p2.end(), diff.begin());
			total += diff.size();
		}
	}

	return total / organisms.size();
}

std::vector<DNA::Organism> Environment::Population::reproduce()
{
	// 1. begin with the first organism
	// 2. scan population for suitable mate
	// 3. if mate is found
	//     swap mate with organism after current
	//     create new offspring from parents
	//     set marker to current + 2
	//    else add organism to new population list
	// 4. do while current != end
	return std::vector<DNA::Organism>();
}

void Environment::Population::go_extinct()
{
	exinct = true;
	organisms.clear();
}

bool Environment::Population::hunt(DNA::Organism & o)
{
	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> spot(0, organisms.size() - 1);

	int defender_i = spot(engine);

	bool successful = attack(o.get_traits(OffensiveTool), organisms[defender_i].get_traits(DefensiveTool));

	if (successful) {
		organisms.erase(organisms.begin() + defender_i);
		o.give_resources();
		return true;
	}
	else return false;
}
