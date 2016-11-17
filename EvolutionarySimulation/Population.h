#pragma once

#include <vector>
#include <algorithm>

#include "Organism.h"

namespace Environment {
	class Population
	{
		std::vector<DNA::Organism> organisms;

	public:
		Population();
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
	};
}



