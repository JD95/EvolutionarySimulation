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

std::vector<DNA::Organism> DNA::mate(const Organism & mom, const Organism & dad)
{
	// 1. Determine mating strategy to use
	// 2. For N number of off spring
	//		section parents DNA based on Genome::REPRODUCTION_CHUNK_SIZE
	//		select chunks at random from each parent to create a new child genome
	//      mutate the gene at random
	//      using the new genome, generate a new organism
	return std::vector<Organism>();
}
