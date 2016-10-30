#include "Items.h";

#pragma once
class Enemies
	: public Items
{
public:

	bool Direction;
	vector<bool> Type;

	void Add(float x, float y, float s, bool t)
	{
		Position.push_back(x);
		Altitude.push_back(y);
		
		Speed = s;
		Type.push_back(t);
		Direction = true;
	}

	void Drop(Bombs *bombs, int from)
	{
		if (bombs->Count() > 6)
			return;

		bombs->Add(Position[from], Altitude[from]);
	}

	void Left()
	{
		if (Direction)
			Down(20);

		Direction = false;
	}

	void Right()
	{
		if (!Direction)
			Down(20);
		
		Direction = true;
	}

	void Down(float d)
	{
		Move(0, d);
	}

	void Step(float d)
	{
		if (Direction)
			Move(d, 0);
		else
			Move(d*-1, 0);
	}

	float FarLeft()
	{
		float l = Position.front();
		
		for (int i = Position.size() - 1; i >= 0; --i)
		{
			if (Position[i] < l)
				l = Position[i];
		}

		return l;
	}

	float FarRight()
	{
		float r = Position.front();
		
		for (int i = Position.size() - 1; i >= 0; --i)
		{
			if (Position[i] > r)
				r = Position[i];
		}

		return r;
	}

	float FarDown()
	{
		if (!Any())
			return 0.0;
		
		float a = Altitude.front();

		for (int i = Altitude.size() - 1; i >= 0; --i)
			if (Altitude[i] > a)
				a = Altitude[i];
		
		return a;
	}

	Enemies(void)
	{
	}

	~Enemies(void)
	{
	}
};

