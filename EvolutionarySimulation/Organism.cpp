#include "Organism.h"

DNA::Organism::Organism(string dna)
	: genome(dna)
{
	auto genes = genome.genes();
	phenotype.reserve(genes.size());

	for (auto gene : genes) {
		phenotype.emplace_back(Attribute(gene));
	}

	std::sort(phenotype.begin(), phenotype.end());
}


DNA::Organism::~Organism()
{
}
