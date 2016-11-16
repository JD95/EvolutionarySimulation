#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

#include "Population.h"

class World
{
	std::vector<Population> populations;
	static constexpr float POPULATION_IMPORTANCE = 0.12;

public:

	World();
	~World();

	inline float total_diversity();
};

