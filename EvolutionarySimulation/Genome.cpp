#include "Genome.h"

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
	string gene = nucleotides.substr(start, end - start);
	return gene;
}

std::string DNA::Genome::find_next_gene(const int start) const
{
	int next_gene_start = find_next_gene_start(start) + 3;

	if (next_gene_start == std::string::npos) 
		return "";

	int next_gene_end = find_next_gene_end(next_gene_start);

	if (next_gene_end == std::string::npos)
		return "";
	
	return extract_gene(next_gene_start, next_gene_end);
}

vector<std::string> DNA::Genome::genes() const
{
	int start = 0;
	vector<string> gs;

	do
	{
		int next_gene_start = find_next_gene_start(start);

		if (next_gene_start == std::string::npos)
			return gs;

		int next_gene_end = find_next_gene_end(next_gene_start + 3);

		if (next_gene_end == std::string::npos)
			return gs;

		auto gene = extract_gene(next_gene_start + 3, next_gene_end);
		gs.push_back(gene);

		start = next_gene_end + 3;

	} while (start < nucleotides.size());

	return gs;
}