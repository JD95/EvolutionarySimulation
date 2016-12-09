#pragma once

#include <string>
#include <algorithm>
#include <functional>

enum AttributeType { 
	ResourcesNeeded, 
	ResourcePref,
	OffensiveTool,
	DefensiveTool,
	ReproductiveStrat
};

enum OffensiveTool {
	Claws = 0,
	Teeth = 1,
	HornsO = 2,
	Constrict = 3,
	Trap = 4,
	Strength = 5
};

enum DefensiveTool {
	HornsD = 0,
	Hide = 1,
	Posion = 2,
	Spikes = 3,
	Smell = 4,
	Camo = 5
};

enum ReproductiveStrat {
	Single,
	Few,
	Many
};

bool dominant_gene(std::string gene);

std::string show_AttributeType(AttributeType t);

struct Attribute
{
	const int attribute_types = 5;
	AttributeType type;
	int subtype;
	int value;
	bool dominant;

public:
	Attribute();
	Attribute(AttributeType t, int v, bool d);
	Attribute(std::string gene, int num_populations);
	~Attribute();

	Attribute& operator= (Attribute other) {
		std::swap(this->type, other.type);
		std::swap(this->subtype, other.subtype);
		std::swap(this->value, other.value);
		std::swap(this->dominant, other.dominant);
		return *this;
	}

	friend std::ostream& operator<< (std::ostream& out, Attribute& obj)
	{
		out << show_AttributeType(obj.type) << " " << obj.value << " "  << (obj.dominant ? "Dominant" : "Recessive");
		return out;
	}

	friend bool operator== (const Attribute& l, const Attribute& r) {
		return (l.type == r.type) && (l.value == r.value);
	}

	// Used to sort attributes within a genome
	friend bool operator< (const Attribute& l, const Attribute& r) {
		return (l.type == r.type) ? (l.value < r.value) : (l.type < r.type);
	}
};



