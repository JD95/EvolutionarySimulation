#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <array>
#include <string>
#include <functional>
#include <iostream>

namespace DNA
{
	using std::vector;
	using std::array;
	using std::string;
	using std::function;

	class Genome
	{
		string nucleotides;	

	public:
		/*
			Uses boyer-moore-horspool search algorithm
			to find a specific sequence in the genome
			from the given starting point.
		*/
		int find_sequence( const int start
						 , const string &sequence
						 ) const;

		// uses find_sequence to get next 'att' occurence
		int find_next_gene_start( const int start ) const;

		// uses find_sequence to get next 'gat' occurence
		int find_next_gene_end( const int start ) const;

		// pulls out a gene at the specific starting and ending points
		string extract_gene( const int start
									   , const int end
									   ) const;

		// finds the next gene from the given starting point
		string find_next_gene(const int start) const;

	public:

		Genome();
		Genome(string ns);

		std::string to_string() const;

		// Extracts the valid genes within the genome
		vector<string> genes() const;
	};
}


