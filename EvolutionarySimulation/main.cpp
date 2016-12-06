#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>

#include "Genome.h"
#include "Search.h"
#include "Attribute.h"
#include "Organism.h"

using namespace DNA;

int main()
{
	while (true) {
		auto seed_nucleotides = generate_initial_genome();
		Organism subject1(seed_nucleotides);
		Organism subject2(mutate(seed_nucleotides));

		std::cout << (subject1 == subject2 ? "Subject1 is the same species as Subject2!\n" : "Not Same species!\n");

		system("pause");
	}
	return 0;
}
