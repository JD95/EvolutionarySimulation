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
using namespace DNA;
using namespace Environment;

void test_seed_gen() {

	auto seed_nucleotides = generate_initial_genome();
	Organism subject1(seed_nucleotides);
	Organism subject2(mutate(seed_nucleotides));

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
	auto pop_a_seed = generate_initial_genome();
	auto pop_b_seed = generate_initial_genome();

	std::vector<Organism> pop_a(pop_a_size);
	std::vector<Organism> pop_b(pop_b_size);
	NaturalResource water(5);

	for (auto& o : pop_a)
		o = Organism(mutate(pop_a_seed));

	for (auto& o : pop_b)
		o = Organism(mutate(pop_a_seed));

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

	std::cout << "Population A:\n";
	for (auto& o : pop_a) std::cout << "\t" << o << "\n";

	std::cout << "Population B:\n";
	for (auto& o : pop_b) std::cout << "\t" << o << "\n";

	system("pause");
}

int main()
{
	while (true) {
		test_natural_resource();
		system("cls");
	}

	return 0;
}
