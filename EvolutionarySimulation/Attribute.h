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

bool dominant_gene(std::string gene);

std::string show_AttributeType(AttributeType t);

class Attribute
{
	const int attribute_types = 5;
	AttributeType type;
	int value;
	bool dominant;

public:
	Attribute(AttributeType t, int v, bool d);
	Attribute(std::string gene);
	~Attribute();

	friend std::ostream& operator<< (std::ostream& out, Attribute& obj)
	{
		out << show_AttributeType(obj.type) << " " << obj.value << " "  << (obj.dominant ? "Dominant" : "Recessive");
		return out;
	}
};



