#include <vector>
using namespace std;

#pragma once
class Items
{
public:

	vector<float> Position;
	vector<float> Altitude;
	float Speed;

	Items(void)
	{
	}

	bool Any()
	{
		return Count() > 0;
	}

	int Count()
	{
		return Position.size();
	}

	void Move(float x, float y)
	{
		for (int i = Position.size() - 1; i >= 0; --i)
		{
			Position[i] += x*Speed;
			Altitude[i] += y*Speed;
		}
	}

	~Items(void)
	{
	}
};

