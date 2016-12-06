#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <array>
#include <string>
#include <functional>
#include <iostream>
#include <tuple>
#include <random>

namespace DNA
{
	using std::vector;
	using std::array;
	using std::string;
	using std::function;
	using std::tuple;

	class Genome
	{
		const int MARK_SIZE = 3;
		string nucleotides;

	public:

		static constexpr int REPRODUCTION_CHUNK_SIZE = 4;

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
		std::tuple<std::string, int> find_next_gene(const int start) const;

	public:

		Genome();
		Genome(string ns);

		Genome& operator= (Genome& other) {
			std::swap(this->nucleotides, other.nucleotides);
			return *this;
		}

		std::string to_string() const;

		// Extracts the valid genes within the genome
		vector<string> genes() const;

		const string& get_nucleotides() const { return nucleotides;  }
	};

	void mutate(std::string& nucleotides);
}


