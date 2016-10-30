#include "..\Model\Items.h"
#include <vector>
using namespace std;

#pragma once
class CollisionDetector
{
public:

	bool ResolveCollisions(Items *a, Items *b)
	{
		bool detected = false;

		if (!a->Any() || !b->Any())
			return false;

		for (int i = a->Position.size() - 1; i >= 0; --i)
		{
			for (int j = b->Position.size() - 1; j >= 0; --j)
			{
				float hDiff = abs(a->Position[i] - b->Position[j]);
				float vDiff = abs(a->Altitude[i] - b->Altitude[j]);

				if (hDiff < 12 && vDiff < 12)
				{
					a->Position.erase(a->Position.begin() + i);
					a->Altitude.erase(a->Altitude.begin() + i);

					b->Position.erase(b->Position.begin() + j);
					b->Altitude.erase(b->Altitude.begin() + j);

					return true;
				}
			}
		}

		return detected;
	}

	CollisionDetector(void)
	{
	}

	~CollisionDetector(void)
	{
	}
};

