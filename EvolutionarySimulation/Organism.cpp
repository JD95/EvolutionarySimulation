#include "Organism.h"

DNA::Organism::Organism()
{
	int x = 5;
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

	std::vector<Attribute> strategies(1);

	std::copy_if(mom_phenotype.begin(), mom_phenotype.end(), strategies.begin(),
		[](Attribute feat) { return feat.type == AttributeType::ReproductiveStrat; });

	if (strategies.size() == 0) return 1;

	auto strat = std::max_element(strategies.begin(), strategies.end());

	switch ((*strat).subtype) {
	case ReproductiveStrat::Single: return 1;
	case ReproductiveStrat::Few: return 3;
	case ReproductiveStrat::Many: return 10;
	default: return 1;
	}
}



std::string DNA::generate_genome(const string& mom, const string& dad, std::default_random_engine& parent_choice)
{
	const int chunk_size = Genome::REPRODUCTION_CHUNK_SIZE;
	std::uniform_real_distribution<> distribution(0.0, 1.0);
	int max_size = std::min(mom.size(), dad.size());
	int end = max_size / chunk_size;
	string child_nucleotides;

	child_nucleotides.reserve(max_size);

	// Randomly choose chunks from mom and dad
	for (int i = 0; i < end - 1; i += chunk_size)
	{
		auto choice = distribution(parent_choice) >= 0.5;
		auto parent = choice ? mom : dad;
		child_nucleotides += parent.substr(i, i + chunk_size - 1);
	}

	// Randomly take the last bit of the dna from mom or dad
	auto parent = distribution(parent_choice) >= 0.5 ? mom : dad;
	int last = chunk_size * (end - 1);
	child_nucleotides += parent.substr(last);

	child_nucleotides.shrink_to_fit();

	// mutate child dna
	mutate(child_nucleotides);

	return child_nucleotides;
}


std::vector<DNA::Organism> DNA::mate(const Organism & mom, const Organism & dad)
{
	auto num_off = num_offspring(mom);
	vector<Organism> off_spring(num_off);
	std::default_random_engine parent_choice(time(0));

	const int chunk_size = Genome::REPRODUCTION_CHUNK_SIZE;

	for (auto& child : off_spring) {
		child = Organism(generate_genome(mom.get_genome().get_nucleotides(), dad.get_genome().get_nucleotides(), parent_choice));
	}

	return off_spring;
}
