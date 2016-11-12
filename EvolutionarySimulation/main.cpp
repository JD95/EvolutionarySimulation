#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>

#include "Genome.h"
#include "Search.h"
#include "Attribute.h"

using namespace DNA;

int main()
{
	const Genome genome("ATTGATCAGCTAGAGCTATTAGCGAGGTATTAGAT");

	for (auto gene : genome.genes())
	{
		std::cout << Attribute(gene) << '\n';
	}
	
	system("pause");
	return 0;
}
