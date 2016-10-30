#include <vector>
using namespace std;

#pragma once
class Bombs
	: public Items
{
public:

	void Add(float x, float y)
	{
		Position.push_back(x);
		Altitude.push_back(y);
		Speed = 1.0;
	}

	void Fall(float diff)
	{
		for(int i = Altitude.size() - 1; i >= 0; --i)
			if (Altitude[i] > 480)
			{
				Altitude.erase(Altitude.begin() + i);
				Position.erase(Position.begin() + i);
			}

		Move(0, diff*Speed);
	}

	Bombs(void)
	{
	}

	~Bombs(void)
	{
	}
};

