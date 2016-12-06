#include "Organism.h"

DNA::Organism::Organism()
{
}

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

int DNA::num_offspring(const Organism& org) {
	
	auto mom_phenotype = org.get_phenotype();

	std::vector<Attribute> strategies(10);

	std::copy_if(mom_phenotype.begin(), mom_phenotype.end(), strategies.begin(),
		[](Attribute feat) { return feat.type == AttributeType::ReproductiveStrat; });

	auto strat = std::max_element(strategies.begin(), strategies.end());

	switch ((*strat).subtype) {
	case ReproductiveStrat::Single: return 1;
	case ReproductiveStrat::Few: return 3;
	case ReproductiveStrat::Many: return 10;
	}
}

std::string DNA::generate_genome(const string& mom, const string& dad)
{
	const int chunk_size = Genome::REPRODUCTION_CHUNK_SIZE;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 1);
	int max_size = std::max(mom.size(), dad.size());
	int end = max_size / chunk_size;
	string child_nucleotides;

	child_nucleotides.reserve(max_size);

	// Randomly choose chunks from mom and dad
	for (int i = 0; i < end - 1; i += chunk_size)
	{
		auto parent = (bool)distribution(generator) ? mom.begin() : dad.begin();
		std::copy(parent + i, parent + i + chunk_size - 1, child_nucleotides.begin() + i);
	}

	// Randomly take the last bit of the dna from mom or dad
	auto parent = (bool)distribution(generator) ? mom : dad;
	int last = chunk_size * (end - 1);
	std::copy(parent.begin() + last, parent.end(), child_nucleotides.begin() + last);

	child_nucleotides.shrink_to_fit();

	// mutate child dna
	mutate(child_nucleotides);

	return child_nucleotides;
}


std::vector<DNA::Organism> DNA::mate(const Organism & mom, const Organism & dad)
{
	vector<Organism> off_spring(num_offspring(mom));

	const int chunk_size = Genome::REPRODUCTION_CHUNK_SIZE;

	for (auto& child : off_spring) {
		child = Organism(generate_genome(mom.get_genome().get_nucleotides(), dad.get_genome().get_nucleotides()));
	}

	return off_spring;
}
