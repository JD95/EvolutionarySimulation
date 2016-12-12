#include "Population.h"
#include "Interaction.h"


void gen_pop_name(std::string& name, const std::vector<std::string>& pop_name_seg, const std::vector<std::string>& pop_name_ending)
{
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

Environment::Population::Population()
{
}

Environment::Population::Population(DNA::Organism outcast)
	: extinct(false)
{
	organisms.push_back(outcast);
	gen_pop_name(name, pop_name_seg, pop_name_ending);
}

Environment::Population::Population(std::string gene, int size, int pop_index)
	: extinct(false)
{
	for (int i = 0; i < size; i++)
	{
		organisms.emplace_back(DNA::Organism(DNA::mutate(gene), pop_index));
	}

	gen_pop_name(name, pop_name_seg, pop_name_ending);

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

			std::set_difference(p1.begin(), p1.end(), p2.begin(), p2.end(), std::back_inserter(diff));
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
	extinct = true;
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
		organisms[defender_i].kill();
		o.give_resources();
		return true;
	}
	else return false;
}

void Environment::Population::gather_resources(std::vector<Population>& populations, std::vector<NaturalResource>& resources)
{
	for(int i = 0; i < organisms.size() -1; i++){
		auto org = organisms[i];
		auto needs = org.get_traits(ResourcesNeeded);
		for (auto& need : needs) {
			if (need.subtype >= 0 && need.subtype < NUM_NAT_RESOURCES)
			{
				if (!resources[need.subtype].add_organism(&organisms[i]))
					resources[need.subtype].challenge_organism(&organisms[i]);
			}
			else {
				auto target_pop = populations[need.subtype - NUM_NAT_RESOURCES];
				if (target_pop != *this && target_pop.hunt(organisms[i]))
					organisms[i].give_resources();
			}
		}
	}
}

void Environment::Population::age_population()
{
	population_age++;

	for (auto& organism : organisms) {
		organism.get_older();
	}
	
	// Kill old ones
	std::remove_if(organisms.begin(), organisms.end(),
		[](DNA::Organism& o) { return o.get_age() > 3 
							       || o.get_starve_counter() <= 0
								   || o.is_dead(); });

	if (organisms.size() < 2) go_extinct();
}
