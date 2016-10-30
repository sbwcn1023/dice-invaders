#include "../Model/Enemies.h"

#pragma once
class EnemyFactory
{
public:

	void GenerateEnemies(Enemies *enemies)
	{
		for (int row = 0; row < 5; ++row)
			for (int column = 0; column < 9; ++column)
				enemies->Add(5 + column * 40, row * 40, 0.5, (column+row)%2 != 0);
	}

	EnemyFactory(void)
	{
	}

	~EnemyFactory(void)
	{
	}
};

