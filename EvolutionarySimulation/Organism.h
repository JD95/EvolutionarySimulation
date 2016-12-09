#pragma once

#include <iostream>
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
		std::string name;
		bool got_resources;
		int starve_counter;
		int needs_fulfilled;
		int age;
		bool dead;
		

	public:
		static constexpr float SPECIATION_LIMIT = 0.85f;
		const int STARVE_LIMIT = 3;

		Organism();
		Organism(string dna, int pop_index);
		~Organism();

		Organism& operator= (Organism other) {
			std::swap(this->genome, other.genome);
			std::swap(this->phenotype, other.phenotype);
			std::swap(this->name, other.name);
			std::swap(this->got_resources, other.got_resources);
			std::swap(this->starve_counter, other.starve_counter);
			std::swap(this->needs_fulfilled, other.needs_fulfilled);
			std::swap(this->age, other.age);

			return *this;
		}

		// Used to check if another organism is of the same species
		friend bool operator== (const Organism& l, const Organism& r) {
			std::vector<Attribute> diff;
			std::set_difference(l.phenotype.begin(), l.phenotype.end(),
				r.phenotype.begin(), r.phenotype.end(),
				std::back_inserter(diff));

			return diff.size() < Organism::SPECIATION_LIMIT * l.phenotype.size()
				&& diff.size() < Organism::SPECIATION_LIMIT * r.phenotype.size();
		}

		friend std::ostream& operator<<(std::ostream& out, Organism& o) {
			
			out << "Organism: " << o.name << " " << (o.got_resources ? "fed" : "hungry");

			return out;
		}

		const std::vector<Attribute>& get_phenotype() const {
			return phenotype;
		}

		const Genome& get_genome() const { return genome; }

		std::vector<Attribute> get_traits(AttributeType t) const {
			std::vector<Attribute> traits;

			std::copy_if(phenotype.begin(), phenotype.end(), std::back_inserter(traits),
				[&t](Attribute a) { return a.type == t; });
			return traits;
		}

		void give_resources() { needs_fulfilled++; }
		void starve() { starve_counter--; }

		std::string get_name() { return name; }

		void get_older() { age++; needs_fulfilled = 0; }
		int get_age() { return age; }
		int get_needsfulfilled() { return needs_fulfilled; }

		bool is_dead() { return dead; }
		void kill() { dead = true; }
	};

	void mate(const Organism& mom, const Organism& dad, int pop_index, std::vector<Organism>& babies);

	int num_offspring(const Organism& org);

	std::string generate_genome(const string& mom, const string& dad, std::default_random_engine& parent_choice);
}

