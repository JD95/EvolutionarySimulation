 #include "Interaction.h"

void compare_attack(Attribute A, Attribute B, int &wins, int &lose)
{
	tool temp;
		switch (temp.check_with[A.subtype][B.subtype])
	{
	case 0:				//Attacker wins
		wins++;
		break;
	case 1:				//Defender wins
		lose++;
		break;
	case 2:				//Special case
		if (A.value > B.value)	wins++;
		else					lose++;
		break;
	case 3:				//draw
		break;
	}

	return false;
}

	    // Offenders Offensive traits    // Defender's Defense traits
bool attack(std::vector<Attribute> attacker, std::vector<Attribute> defender)
{
	int win_count = 0;
	int lose_count = 0;

	for (Attribute def : defender)
	{
		for (Attribute att : attacker)
		{
			compare_attack(att, def, win_count, lose_count);
		}
	}

	return (win_count > lose_count);
	
}
