#include "Arrow2D/RankLengths.hpp"



void RankLengths(unsigned int count, float values[], unsigned int ranks[])
{
	for (unsigned int j = 0; j < count; j++)
	{
		ranks[j] = 0;
		for (unsigned int i = 0; i < count; i++)
		{
			if (i != j)
			{
				if (values[j] < values[i])
				{
					ranks[j]++;
				}
			}
		}
	}
}
