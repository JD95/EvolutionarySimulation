#include "World.h"


Environment::World::World(std::vector<NaturalResource> rs)
{
	resources = rs;
}

Environment::World::~World()
{
}

float Environment::World::total_diversity()
{
	return populations.size() * POPULATION_IMPORTANCE 
		 + (std::accumulate(populations.begin(), populations.end(), 0.0f,
			[](float d, Population& p) { return p.diversity() + d; }) / populations.size());
}

void Environment::World::run_generation()
{
	for (auto& r : resources) {
		r.reset();
	}

	// Each organism attempts to acqurie the resources it needs
	for (auto& pop : populations) {

		if (pop.is_extinct()) continue;

		pop.age_population();

		if (pop.is_extinct()) continue;

		pop.gather_resources(populations, resources);
	}
		
	// All natural resources feed their current loads
	for (auto& resource : resources)
		resource.feed_current_load();

	// Populations mate
	int pops = populations.size();

	std::vector<std::thread> threads(pops);

	auto lock = &populations_mutex;
	auto mating = [lock](Population& p, std::vector<Population>& populations) {
		if (p.is_extinct()) return;

		std::vector<DNA::Organism> babies;

		make_babies(p, populations, babies, *lock);

		p.add_babies(babies);
	};

	for (int i = 0; i < pops; i++) {
		threads[i] = std::thread(mating, populations[i], populations);
	}

	for (auto& t : threads) t.join();

	std::cout << "Organisms in world: " << num_organisms() << "\n";
}

void Environment::make_babies(Population& pop, std::vector<Population>& populations, std::vector<DNA::Organism>& babies, std::mutex& lock) {
	// Must recalculate size each time because we may remove organisms
	for (int i = 0; i < pop.size() - 1; i++)
	{
		// Organisms which did not get resources do not get to mate
		if (pop[i].get_needsfulfilled() < pop[i].get_traits(ResourcesNeeded).size()) {
			if (pop[i].get_needsfulfilled() < 2) 
				pop[i].starve();
			continue;
		}

		bool incompatible = true;
		// Attempt to create babies
		for (int j = i + 1; j < pop.size() - 1; j++) {
			if (pop[i] == pop[j]) {
				std::swap(pop[i + 1], pop[j]);
				mate(pop[i], pop[i + 1], populations.size(), babies);
				incompatible = false;
				break;
			}
		}

		if (i+1 == pop.size() - 1)
			incompatible = false;

		// Organisms which are incompatible with any other organism becomes new population
		if (incompatible) {
			make_outcast(i, pop, populations, lock);
			//i--; // population will swap outcast with last and delete the last
		}
	}
}

void Environment::make_outcast(int i, Population& pop, std::vector<Population>& populations, std::mutex& lock)
{
	std::cout << "New Pop created!\n";
	bool found_kind = false;
	for (int pi = 0; pi < populations.size() - 1; pi++) {
		if (pop[i] == populations[pi][0])
		{
			populations[pi].add_organism(pop[i]);
			found_kind = true;
			break;
		}
	}

	if (!found_kind) {
		std::lock_guard<std::mutex> guard(lock);
		populations.push_back(Population(pop[i]));
		pop.remove_organism(i);
	}
}

void Environment::World::add_population(Population p)
{
	populations.push_back(p);
}
