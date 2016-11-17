#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

#include "Population.h"

namespace Environment {
	class World
	{
		std::vector<Population> populations;
		static constexpr float POPULATION_IMPORTANCE = 0.12;

	public:

		World();
		~World();

		// Measures the total diversity of all
		// populations by averaging each population's
		// individual diversity and then adding that
		// to the total number of populations times the
		// population importance constant.
		inline float total_diversity();
	};
}


