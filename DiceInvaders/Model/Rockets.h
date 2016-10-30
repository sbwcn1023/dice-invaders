#pragma once
#include "Items.h"
class Rockets :
	public Items
{
public:

	void Add(int x, int y)
	{
		if (Altitude.size() > 0)
			return;

		Position.push_back(x);
		Altitude.push_back(y);

		Speed = 2.0;
	}

	void Step(float d)
	{
		if (Altitude.size() == 0)
			return;

		if (Altitude[0] < 0)
		{
			Altitude.erase(Altitude.begin() + 0);
			Position.erase(Position.begin() + 0);
		}

		if (Altitude.size() == 0)
			return;

		Move(0, -1*d);
	}

	Rockets(void)
	{
	}

	~Rockets(void)
	{
	}
};

