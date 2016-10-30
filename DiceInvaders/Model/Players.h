#pragma once
#include "Items.h"
#include "Rockets.h"
class Players :
	public Items
{
public:

	void Fire(Rockets *rockets)
	{
		rockets->Add(Position[0], Altitude[0]);
	}

	void Right(float diff)
	{
		Move(diff, 0);
	}

	void Left(float diff)
	{
		Move(diff * -1, 0);
	}

	void Add(float x)
	{
		Position.push_back(x);
		Altitude.push_back(448);
		Speed = 1.2;
	}

	Players(void)
	{
	}

	~Players(void)
	{
	}
};

