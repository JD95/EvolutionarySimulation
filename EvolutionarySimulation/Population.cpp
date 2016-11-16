#include "Population.h"



Population::Population()
{
}


Population::~Population()
{
}

float Population::diversity()
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
