#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

#include "Genome.h"
#include "Search.h"

using namespace DNA;

int main()
{
	const Genome genome("ATTGATCAGCTAGAGCTATTAGCGAGGTATTAGAT");
	
	string s = "boo";
	auto test = s.find("z");

	for (auto gene : genome.genes())
	{
		for (auto base : gene) std::cout << base;
		std::cout << '\n';
	}
	
	system("pause");
	return 0;
}