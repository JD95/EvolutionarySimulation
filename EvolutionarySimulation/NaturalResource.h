#pragma once

#include <iostream>
#include <vector>

#include "Organism.h"


namespace Environment {

	const int NUM_NAT_RESOURCES = 5;

	enum NaturalResources {
		Water,
		Acorns,
		Berries,
		Grass,
		Worms
	};

	class NaturalResource
	{
		int id;
		int max_capacity;

		// All of the organisms currently using
		// this resource
		std::vector<DNA::Organism*> current_load;

	public:
		NaturalResource();
		NaturalResource(int capacity);
		~NaturalResource();

		// Attempt to allow an organism to use
		// this resource. Will return false if
		// the resource is at capacity.
		bool add_organism(DNA::Organism* o);

		// An organism attempts to take a spot away from
		// another organism using this resource. The two
		// will fight and if the attempt succeeds the
		// organism will take the loser's spot using the
		// resource.
		bool challenge_organism(DNA::Organism* o);

		friend std::ostream& operator<< (std::ostream& out, NaturalResource& r) {
			
			out << "Resource: " << "\n";
			
			for (auto o : r.current_load)
				out << *o << "\n";

			return out;
		}

		void feed_current_load();

		void reset() { current_load.clear(); }

	};
}


