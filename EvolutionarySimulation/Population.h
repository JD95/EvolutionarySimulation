#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Organism.h"
#include "NaturalResource.h"

namespace Environment {

	const std::vector<std::string> pop_name_seg = {
		"goopa",
		"suptup",
		"coxa",
		"mega",
		"tup",
		"sup",
		"flugu",
		"draxa",
		"faxa",
		"cu",
		"setpa",
		"methrol",
		"cy",
		"lept",
		"demo",
		"celio",
		"karaus",
		"mio",
		"opod",
		"sentius",
		"octo",
		"hepta",
		"quad",
		"eliph",
		"nium",
		"grum",
		"phena",
		"draco",
		"tia",
		"via",
		"eptus",
		"vera",
		"cinia",
		"borgo",
		"porsti",
		"misa",
		"mela",
		"char",
		"zard",
		"mus",
		"lio",
		"melae",
		"phium",
		"pides",
		"nida",
		"icus",
		"goxo",
		"gramaka",
		"icles",
		"ria"
	};

	const std::vector<std::string> pop_name_ending = {
		"",
		"pod",
		"sourus"
	};

	class Population
	{
		std::string name;
		std::vector<DNA::Organism> organisms;
		bool extinct;
		int population_age;

	public:
		Population();
		Population(DNA::Organism outcast);
		Population(std::string gene, int size, int pop_index);
		~Population();

		// Measures the overall diversity of the population
		// by comparing the set differences of each of the
		// organisms with every other organism.
		float diversity();

		// The population goes through a mating season
		// where all viable organisms attempt to reproduce.
		// Any organisms which cannot reproduce due to genetic
		// differences will be removed from the population and
		// returned from the function.
		std::vector<DNA::Organism> reproduce();

		friend std::ostream& operator<< (std::ostream& out, Population& population) {
			out << "Population - " << population.name << " " << population.size() << ":\n";
			/*for (auto& o : population.organisms)
				out << "\t" << o << "\n";*/
			return out;
		}

		DNA::Organism& operator[](std::size_t idx) { return organisms[idx]; }
		const DNA::Organism& operator[](std::size_t idx) const { return organisms[idx]; }

		friend bool operator== (const Population& a, const Population& b) {
			return a.name == b.name;
		}

		friend bool operator!= (const Population& a, const Population& b) {
			return a.name != b.name;
		}

		void go_extinct();

		bool hunt(DNA::Organism& o);

		bool is_extinct() { return extinct; }

		void gather_resources(std::vector<Population>& populations, std::vector<NaturalResource>& resources);

		void age_population();

		int size() { return organisms.size(); }

		void add_organism(DNA::Organism o) { organisms.push_back(o); }
		void remove_organism(int i) { 
			if (organisms.size() == 0) return;
			organisms.erase(organisms.begin() + i); 
		}
		void add_babies(std::vector<DNA::Organism> babies) { 
			std::copy(babies.begin(), babies.end(), std::back_inserter(organisms));
		}

		void disaster() {
			std::random_device device;
			std::default_random_engine engine(device());
			std::uniform_int_distribution<int> n(size() / 2, size() - 1);

			organisms.erase(organisms.begin() + n(engine), organisms.end());
		}
	};
}



