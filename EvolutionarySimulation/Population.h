#pragma once

#include <vector>
#include <algorithm>

#include "Organism.h"

class Population
{
	std::vector<DNA::Organism> organisms;

public:
	Population();
	~Population();

	float diversity();
};

