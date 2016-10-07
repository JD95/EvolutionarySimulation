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
	const Genome genome{
	{ (Nucleobase::A)
	, (Nucleobase::T)
	, (Nucleobase::T)
	, (Nucleobase::G)
	, (Nucleobase::C)
	, (Nucleobase::G)
	, (Nucleobase::A)
	, (Nucleobase::T)
	, (Nucleobase::A)
	, (Nucleobase::T)
	, (Nucleobase::T)
	, (Nucleobase::G)
	, (Nucleobase::A)
	, (Nucleobase::G)
	, (Nucleobase::A)
	, (Nucleobase::T)
	}};
	
	for (auto& gene : genome.genes())
	{
		for (auto base : gene) std::cout << base;
		std::cout << '\n';
	}
	
	system("pause");
	return 0;
}