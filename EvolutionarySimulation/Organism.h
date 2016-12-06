#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <time.h>

#include "Genome.h"
#include "Attribute.h"

namespace DNA {

	class Organism
	{
		Genome genome;
		std::vector<Attribute> phenotype;

	public:
		static constexpr float SPECIATION_LIMIT = 0.85f;

		Organism();
		Organism(string dna);
		~Organism();

		Organism& operator= (Organism other) {
			std::swap(this->genome, other.genome);
			std::swap(this->phenotype, other.phenotype);
			return *this;
		}

		// Used to check if another organism is of the same species
		friend bool operator== (const Organism& l, const Organism& r) {
			std::vector<Attribute> diff(1);
			std::set_difference(l.phenotype.begin(), l.phenotype.end(),
				r.phenotype.begin(), r.phenotype.end(),
				std::back_inserter(diff));

			return diff.size() < Organism::SPECIATION_LIMIT * l.phenotype.size()
				&& diff.size() < Organism::SPECIATION_LIMIT * r.phenotype.size();
		}

		const std::vector<Attribute>& get_phenotype() const {
			return phenotype;
		}

		const Genome& get_genome() const { return genome; }
	};

	std::vector<Organism> mate(const Organism& mom, const Organism& dad);

	int num_offspring(const Organism& org);

	std::string generate_genome(const string& mom, const string& dad, std::default_random_engine& parent_choice);
}

