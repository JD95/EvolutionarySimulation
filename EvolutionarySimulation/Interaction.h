#pragma once
#include <string>
#include <vector>

#include "Attribute.h"

struct tool {
	int check_with[6][6] = {
		{ 0, 1, 0, 1, 1, 2 },
		{ 1, 0, 1, 1, 0, 2 },
		{ 3, 2, 0, 1, 1, 2 },
		{ 0, 2, 1, 1, 0, 2 },
		{ 0, 0, 0, 1, 0, 0 },
		{ 2, 2, 2, 2, 1, 2 }
	};
};

bool compare_attack(Attribute A, Attribute B);

bool attack(std::vector<Attribute> attacker, std::vector<Attribute> defender);

