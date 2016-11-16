#include "Population.h"



Environment::Population::Population()
{
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
