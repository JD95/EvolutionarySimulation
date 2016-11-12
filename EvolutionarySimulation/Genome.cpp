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
		
		gs.push_back(gene);

		start = next_gene_end + 3;

	} while (start < nucleotides.size());

	return gs;
}
