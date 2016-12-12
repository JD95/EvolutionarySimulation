#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <thread>
#include <mutex>

#include "Population.h"
#include "NaturalResource.h"

namespace Environment {
	class World
	{
		std::vector<NaturalResource> resources;
		std::vector<Population> populations;
		std::mutex populations_mutex;
		static constexpr float POPULATION_IMPORTANCE = 0.12f;
		

	public:
		World(std::vector<NaturalResource> rs);
		~World();

		// Measures the total diversity of all
		// populations by averaging each population's
		// individual diversity and then adding that
		// to the total number of populations times the
		// population importance constant.
		float total_diversity();

		void run_generation();

		void add_population(Population p);

		void print_populations() {
			for (auto& pop : populations) {
				std::cout << pop << "\n";
			}
		}

		void disaster() {
			for (auto& population : populations) {
				population.disaster();
			}
		}

		int num_organisms() {
			return std::accumulate(populations.begin(), populations.end(), 0,
				[](int total, Population& p) { return total + p.size(); });
		}

	};

	void make_babies(Population& pop, std::vector<Population>& populations, std::vector<DNA::Organism>& babies, std::mutex& lock);

	void make_outcast(int i, Population& pop, std::vector<Population>& populations, std::mutex& lock);

}


