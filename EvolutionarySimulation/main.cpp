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
#include "Interaction.h"
#include "NaturalResource.h"
#include "Population.h"

using namespace DNA;
using namespace Environment;

void test_seed_gen() {

	auto seed_nucleotides = generate_initial_genome();
	Organism subject1(seed_nucleotides, 0);
	Organism subject2(mutate(seed_nucleotides), 0);

	std::cout << (subject1 == subject2 ? "Subject1 is the same species as Subject2!\n" : "Not Same species!\n");

	system("pause");

}

void test_attack() {
	Attribute attackAtt1(AttributeType::OffensiveTool, 8, true);
	attackAtt1.subtype = OffensiveTool::Claws;
	Attribute attackAtt2(AttributeType::OffensiveTool, 8, true);
	attackAtt2.subtype = OffensiveTool::Constrict;
	std::vector <Attribute> attList;
	attList.push_back(attackAtt1);
	attList.push_back(attackAtt2);

	Attribute defender(AttributeType::DefensiveTool, 9, true);
	defender.subtype = DefensiveTool::Posion;
	std::vector <Attribute> defList;
	defList.push_back(defender);

	bool answer = attack(attList, defList);
}

void test_natural_resource() {
	const int pop_a_size = 5;
	const int pop_b_size = 10;

	Population pop_a(generate_initial_genome(), pop_a_size, 0);
	Population pop_b(generate_initial_genome(), pop_b_size, 0);
	NaturalResource water(5);

	// Allow population a to access water
	for (int i = 0; i < pop_a_size; i++)
	{
		if (!water.add_organism(&pop_a[i])) {
			if (!water.challenge_organism(&pop_a[i]))
				pop_a[i].starve();
		}
	}

	// Allow population b to access water
	for (int i = 0; i < pop_b_size; i++)
	{
		if (!water.add_organism(&pop_b[i])) {
			if (!water.challenge_organism(&pop_b[i]))
				pop_b[i].starve();
		}
	}

	water.feed_current_load();

	std::cout << pop_a;
	std::cout << pop_b;

	system("pause");
}

void test_hunting() {
	const int pop_a_size = 5;

	Organism hunter(generate_initial_genome(), 0);
	Population pop_b(generate_initial_genome(), pop_a_size, 0);

	std::cout << pop_b << "\n";

	if (pop_b.hunt(hunter)) {
		std::cout << "Hunt was sucessful!\n";
	}
	else {
		std::cout << "Hunt failed!\n";
	}

	std::cout << pop_b << "\n";

	system("pause");
}

int main()
{
	while (true) {
		//test_natural_resource();
		test_hunting();
		system("cls");
	}

	return 0;
}
