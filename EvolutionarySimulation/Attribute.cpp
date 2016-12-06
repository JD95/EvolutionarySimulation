#include "Attribute.h"

Attribute::Attribute()
{
}

Attribute::Attribute(AttributeType t, int v, bool d)
	:type(t), value(v), dominant(d)
{
}

Attribute::Attribute(std::string gene)
{
	std::hash<std::string> hash_fn;

	value = hash_fn(gene);
	type = (AttributeType) (value % attribute_types);
	dominant = dominant_gene(gene);
}

Attribute::~Attribute()
{
}

bool dominant_gene(std::string gene)
{
	int as = std::count(gene.begin(), gene.end(), 'A');
	int ts = std::count(gene.begin(), gene.end(), 'T');
	int gs = std::count(gene.begin(), gene.end(), 'G');
	int cs = std::count(gene.begin(), gene.end(), 'C');

	return as + gs > ts + cs;
}

std::string show_AttributeType(AttributeType t)
{
	switch (t) {
	case AttributeType::DefensiveTool: return "Defensive Tool";
	case AttributeType::OffensiveTool: return "Offensive Tool";
	case AttributeType::ReproductiveStrat: return "Reproductive Strat";
	case AttributeType::ResourcePref: return "Resource Preference";
	case AttributeType::ResourcesNeeded: return "Resources Needed";
	default: return "Undefined Attribute Type!";
	}
}
