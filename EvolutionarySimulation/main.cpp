#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>

#include "Genome.h"
#include "Search.h"
#include "Organism.h"
#include "Interaction.h"
#include "Attribute.h"

using namespace DNA;

int main()
{
	const Organism subject1("ATTGATCAGCTAGAGCTATTAGCGAGGTATTAGAT");
	const Organism subject2("ATTGATCAGCTAGAGCTATTAGCGAGGTATTAGAT");

	std::cout << (subject1 == subject2 ? "Subject1 is the same species as Subject2!\n" : "Not Same species!\n");

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

	std::cout << (answer ? "Attacker wins!\n" : "Defender wins!\n");

	system("pause");
	return 0;
}
