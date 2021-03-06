﻿#include "Genome.h"

using std::vector;
using std::array;
using std::function;

DNA::Genome::Genome() {}

DNA::Genome::Genome(string ns)
	: nucleotides(std::move(ns)) {}

std::string DNA::Genome::to_string() const
{
	return nucleotides;
}

int DNA::Genome::find_sequence(const int start, const string &sequence) const
{
	return nucleotides.find(sequence, start);
}

int DNA::Genome::find_next_gene_start(const int start) const
{
	return find_sequence(start, "ATT");
}

int DNA::Genome::find_next_gene_end(const int start) const
{
	return find_sequence(start, "GAT");
}

std::string DNA::Genome::extract_gene(const int start, const int end) const
{
	return nucleotides.substr(start, end - start);;
}

std::tuple<std::string, int> DNA::Genome::find_next_gene(const int start) const
{
	int next_gene_start = find_next_gene_start(start);

	if (next_gene_start == std::string::npos) 
		return std::make_tuple("", std::string::npos);

	int next_gene_end = find_next_gene_end(next_gene_start + MARK_SIZE);

	if (next_gene_end == std::string::npos)
		return std::make_tuple("", std::string::npos);
	
	return std::make_tuple(extract_gene(next_gene_start + MARK_SIZE, next_gene_end), next_gene_end);
}

vector<std::string> DNA::Genome::genes() const
{
	size_t start = 0;
	vector<string> gs;

	do
	{
		auto gene_info = find_next_gene(start);
		auto gene = std::get<0>(gene_info);
		int next_gene_end = std::get<1>(gene_info);
		
		// No more genes found
		if (next_gene_end == -1) break;

		gs.push_back(gene);

		start = next_gene_end + 3;

	} while (start < nucleotides.size());

	return gs;
}

std::string& DNA::mutate(std::string& nucleotides)
{
	std::random_device device;
	std::default_random_engine mutation_engine(device());
	std::uniform_int_distribution<int> distribution(0, nucleotides.size() - 1);
	
	int mutation_spot = distribution(mutation_engine);

	switch (distribution(mutation_engine) % 3) {
			
	case 0: //point insertion
		nucleotides.insert(distribution(mutation_engine), 1,"ATGC"[distribution(mutation_engine) % 4]);
		break;
	case 1: // point deletion
		nucleotides.erase(distribution(mutation_engine), 1);
	case 2: // point change
		nucleotides.replace(distribution(mutation_engine), 1, 1, "ATGC"[distribution(mutation_engine) % 4]);
		break;
	}

	return nucleotides;
}

std::string DNA::generate_initial_genome()
{
	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> rand_nucl(0,3);
	std::uniform_int_distribution<int> rand_chunk(5, 20);

	string nucleotide = "";
	nucleotide.reserve(1000);

	for (int i = 0; i < 20; i++)
	{
		nucleotide += "ATT";

		for (int j = 0; j < rand_chunk(engine); j++)
			nucleotide += ("ATCG")[rand_nucl(engine)];

		nucleotide += "GAT";

		for (int j = 0; j < rand_chunk(engine); j++)
			nucleotide += ("ATCG")[rand_nucl(engine)];
	}

	nucleotide.shrink_to_fit();

	return nucleotide;
}
