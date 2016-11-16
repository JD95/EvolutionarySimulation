#pragma once

#include <vector>

#include "Organism.h"

namespace Environment {

	class NaturalResource
	{
		int id;
		int max_capacity;

		// All of the organisms currently using
		// this resource
		std::vector<DNA::Organism&> current_load;

	public:
		NaturalResource();
		~NaturalResource();

		// Attempt to allow an organism to use
		// this resource. Will return false if
		// the resource is at capacity.
		bool add_organism(const DNA::Organism& o);

		// An organism attempts to take a spot away from
		// another organism using this resource. The two
		// will fight and if the attempt succeeds the
		// organism will take the loser's spot using the
		// resource.
		bool challenge_organism(const DNA::Organism o);

	};
}


