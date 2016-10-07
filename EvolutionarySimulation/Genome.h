#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <array>

namespace DNA
{
	using std::vector;
	using std::array;

	enum Nucleobase : unsigned char { A, T, C, G };

	class Genome
	{
		std::vector<Nucleobase> nucleotides;	

	public:

		static const vector<int> att_shift;
		static const vector<int> gat_shift;
		static const vector<Nucleobase> att;
		static const vector<Nucleobase> gat;

		Genome();
		Genome(std::vector<Nucleobase> ns);

		std::string to_string() const;

		/*
			Uses boyer-moore-horspool search algorithm
			to find a specific sequence in the genome
			from the given starting point.
		*/
		int find_sequence(const int start, const vector<DNA::Nucleobase> &sequence, const vector<int> &shift) const;

		// uses find_sequence to get next 'att' occurence
		int find_next_gene_start(const int start) const;

		// uses find_sequence to get next 'gat' occurence
		int find_next_gene_end(const int start) const;

		vector<Nucleobase> extract_gene(const int start, const int end) const;

		vector<Nucleobase> find_next_gene(const int start) const;

		vector<vector<Nucleobase>> genes() const;
	};
}


