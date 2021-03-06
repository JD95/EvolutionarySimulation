#include "Organism.h"
#include <random>
#include <time.h>

DNA::Organism::Organism()
	: got_resources(false), starve_counter(STARVE_LIMIT)
{
}

DNA::Organism::Organism(string dna, int pop_index)
	: genome(dna), got_resources(false), starve_counter(STARVE_LIMIT), 
	age(0), needs_fulfilled(0), dead(false)
{
	auto genes = genome.genes();
	phenotype.reserve(genes.size());

	for (auto gene : genes) {
		phenotype.emplace_back(Attribute(gene, pop_index));
	}

	std::sort(phenotype.begin(), phenotype.end());

	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> alpha_upper(65, 90);
	std::uniform_int_distribution<int> alpha_lower(97, 122);
	std::uniform_int_distribution<int> digit(48, 57);
	std::uniform_int_distribution<int> up_or_low(0, 1);

	name = "";
	name += (char)((up_or_low(engine)) ? alpha_upper(engine) : alpha_lower(engine));
	name += (char)digit(engine);
	name += " - ";
	name += (char)((up_or_low(engine)) ? alpha_upper(engine) : alpha_lower(engine));
	name += (char)digit(engine);
}


DNA::Organism::~Organism()
{
}

int DNA::num_offspring(const Organism& org) {
	
	auto mom_phenotype = org.get_phenotype();

	std::vector<Attribute> strategies;

	std::copy_if(mom_phenotype.begin(), mom_phenotype.end(), std::back_inserter(strategies),
		[](const Attribute& feat) { return feat.type == AttributeType::ReproductiveStrat; });

	if (strategies.size() == 0) return 1;

	auto strat = std::max_element(strategies.begin(), strategies.end());

	switch ((*strat).subtype) {
	case ReproductiveStrat::Single: return 1;
	case ReproductiveStrat::Few: return 3;
	case ReproductiveStrat::Many: return 5;
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


void DNA::mate(const Organism & mom, const Organism & dad, int pop_index, std::vector<Organism>& babies)
{
	auto num_off = num_offspring(mom);
	std::default_random_engine parent_choice(time(0));

	const int chunk_size = Genome::REPRODUCTION_CHUNK_SIZE;

	for (int i = 0; i < num_off; i++)
	{
		babies.emplace_back(Organism(generate_genome(mom.get_genome().get_nucleotides(), dad.get_genome().get_nucleotides(), parent_choice), pop_index));
	}
}
