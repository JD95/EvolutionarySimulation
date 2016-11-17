 #include "Interaction.h";

bool compare_attack(_attribute A, _attribute B, int &wins, int &lose)
{
	switch (check_with[A.type][B.type])
	{
	case 0:
		wins++;
		break;
	case 1:
		lose++;
		break;
	case 2:
		if (A.value > B.value)
			wins++;
		else
			lose++;
		break;
	case 3:
		break;
	}

}

bool attack(std::vector<_attribute> attacker, std::vector<_attribute> defender)
{
	int win_count = 0;
	int lose_count = 0;
	for (std::vector<int>::size_type att_itt = 0; att_itt != attacker.size(); att_itt++)
	{
		for (std::vector<int>::size_type def_itt = 0; def_itt != defender.size(); def_itt++)
		{
			compare_attack(attacker[att_itt], defender[def_itt], win_count, lose_count);
		}
	}
	return true;
}
