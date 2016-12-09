#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

#include "Population.h"
#include "NaturalResource.h"

namespace Environment {
	class World
	{
		std::vector<NaturalResource> resources;
		std::vector<Population> populations;
		static constexpr float POPULATION_IMPORTANCE = 0.12f;

	public:

		World();
		~World();

		// Measures the total diversity of all
		// populations by averaging each population's
		// individual diversity and then adding that
		// to the total number of populations times the
		// population importance constant.
		inline float total_diversity();

		void run_generation();
	};
}


