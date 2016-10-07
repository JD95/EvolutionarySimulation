#include "Genome.h"

using std::vector;
using std::array;

const vector<int> DNA::Genome::att_shift = { 2, 1, 3, 3 };

const vector<int> DNA::Genome::gat_shift = { 1, 1, 3, 2 };

const vector<DNA::Nucleobase> DNA::Genome::att{ Nucleobase::A, Nucleobase::T, Nucleobase::T };

const vector<DNA::Nucleobase> DNA::Genome::gat{ Nucleobase::G, Nucleobase::A, Nucleobase::T };

DNA::Genome::Genome() {}

DNA::Genome::Genome(std::vector<Nucleobase> ns)
	: nucleotides(std::move(ns)) {}

std::string DNA::Genome::to_string() const
{
	auto show_base = [](Nucleobase n)
	{
		switch (n)
		{
		case 0U: return 'A';
		case 1U: return 'T';
		case 2U: return 'C';
		case 3U: return 'G';
		}
	};

	return std::accumulate(nucleotides.begin(), nucleotides.end(), std::string(),
		[&](std::string output, Nucleobase n) { return output + show_base(n); });
}

int DNA::Genome::find_sequence(const int start, const vector<DNA::Nucleobase> &sequence, const vector<int> &shift) const
{
	int sequence_size = sequence.size();

	auto increment = [&](int s) { 
		return shift[nucleotides[s + 2]]; 
	};

	for (int skip = start; nucleotides.size() - skip >= sequence_size; skip += increment(skip))
	{
		for (int i = sequence_size - 1; nucleotides[skip + i] == sequence[i]; i--)
			if (i == 0)	return skip;
	}

	return -1;
}

int DNA::Genome::find_next_gene_start(const int start) const
{
	return find_sequence(start, att, att_shift);
}

int DNA::Genome::find_next_gene_end(const int start) const
{
	return find_sequence(start, gat, gat_shift);
}

vector<DNA::Nucleobase> DNA::Genome::extract_gene(const int start, const int end) const
{
	vector<Nucleobase> gene(end - start);
	std::copy(nucleotides.begin() + start, nucleotides.begin() + end, gene.begin());
	return gene;
}

vector<DNA::Nucleobase> DNA::Genome::find_next_gene(const int start) const
{
	int next_gene_start = find_next_gene_start(start) + 3;

	if (next_gene_start == -1) 
		return vector<Nucleobase>();

	int next_gene_end = find_next_gene_end(next_gene_start);

	if (next_gene_end == -1) 
		return vector<Nucleobase>();
	
	return extract_gene(next_gene_start, next_gene_end);
}

vector<vector<DNA::Nucleobase>> DNA::Genome::genes() const
{
	int start = 0;
	vector<vector<Nucleobase>> gs;

	do
	{
		int next_gene_start = find_next_gene_start(start);

		if (next_gene_start == -1) 
			return gs;

		int next_gene_end = find_next_gene_end(next_gene_start + 3);

		if (next_gene_end == -1) 
			return gs;

		gs.push_back(extract_gene(next_gene_start + 3, next_gene_end));

		start = next_gene_end;

	} while (start < nucleotides.size());
}