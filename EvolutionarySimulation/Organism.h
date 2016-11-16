#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "Genome.h"
#include "Attribute.h"

namespace DNA {
	class Organism
	{
		Genome genome;
		std::vector<Attribute> phenotype;

	public:

		static constexpr float SPECIATION_LIMIT = 0.85f;

		Organism(string dna);
		~Organism();

		// Used to check if another organism is of the same species
		friend bool operator== (const Organism& l, const Organism& r) {
			std::vector<Attribute> diff;
			std::set_difference(l.phenotype.begin(), l.phenotype.end(), 
								r.phenotype.begin(), r.phenotype.end(),
								diff.begin());

			return diff.size() < Organism::SPECIATION_LIMIT * l.phenotype.size() 
				&& diff.size() < Organism::SPECIATION_LIMIT * r.phenotype.size();
		}

		const std::vector<Attribute>& get_phenotype() {
			return phenotype;
		}
	};
}