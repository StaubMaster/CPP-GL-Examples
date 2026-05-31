#include "CenterIndexLoop2D.hpp"



void CenterIndexLoop2D::New(unsigned int layer)
{
	Size = layer;
	if (Limit * 2 < Size)
	{
		Done = true;
		return;
	}

	if (Limit >= Size)
	{
		Index = VectorI2(-Size, 0);
	}
	else
	{
		Index = VectorI2(-Limit, +Size - Limit);
	}

	Control = 0;
	Done = false;
}

void CenterIndexLoop2D::Continue()
{
	if (Index.X == 0 && Index.Y == 0) { Done = true; }

	if (Control == 0)
	{
		if (Index.X == 0)
		{
			Control = 1;
			Index.X++;
			Index.Y--;
		}
		else if (Index.Y == +(int)Limit)
		{
			Control = 1;
			Index.X = -Index.X;
		}
		else
		{
			Index.X++;
			Index.Y++;
		}
	}
	else if (Control == 1)
	{
		if (Index.Y == 0)
		{
			Control = 2;
			Index.X--;
			Index.Y--;
		}
		else if (Index.X == +(int)Limit)
		{
			Control = 2;
			Index.Y = -Index.Y;
		}
		else
		{
			Index.X++;
			Index.Y--;
		}
	}
	else if (Control == 2)
	{
		if (Index.X == 0)
		{
			Control = 3;
			Index.X--;
			Index.Y++;
		}
		else if (Index.Y == -(int)Limit)
		{
			Control = 3;
			Index.X = -Index.X;
		}
		else
		{
			Index.X--;
			Index.Y--;
		}
	}
	else
	{
		if (Index.Y == 0)
		{
			Control = 0;
			Index.X++;
			Index.Y++;
			Done = true;
		}
		else if (Index.X == -(int)Limit)
		{
			Control = 0;
			Index.Y = -Index.Y;
			Done = true;
		}
		else
		{
			Index.X--;
			Index.Y++;
		}
	}

	if (Control == 3 && Index.Y == 0) { Done = true; }
}
