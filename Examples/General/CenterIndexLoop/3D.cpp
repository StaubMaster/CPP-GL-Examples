# include "General/CenterIndexLoop/3D.hpp"



void CenterIndexLoop3D::Layer1New(unsigned int layer)
{
	Layer1Size = layer;

	Layer1Index = VectorI2(-Layer1Size, 0);

	if (Limit >= Layer1Size)
	{
		Layer1Index = VectorI2(-Layer1Size, 0);
	}
	else
	{
		Layer1Index = VectorI2(-Limit, +Layer1Size - Limit);
	}

	Layer1Control = 0;
	Layer1Done = false;
}
void CenterIndexLoop3D::Layer1Loop()
{
	if (Layer1Index.X == 0 && Layer1Index.Y == 0) { Layer1Done = true; }

	if (Layer1Control == 0)
	{
		if (Layer1Index.X == 0)
		{
			Layer1Control = 1;
			Layer1Index.X++;
			Layer1Index.Y--;
		}
		else if (Limit * 2 <= (unsigned int)Layer1Index.Y)
		{
			Layer1Control = 1;
			Layer1Index.X = -Layer1Index.X;
		}
		else
		{
			Layer1Index.X++;
			Layer1Index.Y++;
		}
	}
	else if (Layer1Control == 1)
	{
		if (Layer1Index.Y == 0)
		{
			Layer1Control = 0;
			Layer1Index.X--;
			Layer1Index.Y--;
			Layer1Done = true;
		}
		else if (Layer1Index.X == +(int)Limit)
		{
			Layer1Control = 0;
			Layer1Index.Y = -Layer1Index.Y;
			Layer1Done = true;
		}
		else
		{
			Layer1Index.X++;
			Layer1Index.Y--;
		}
	}
}

bool CenterIndexLoop3D::Done() const
{
	return (Layer0.Done || Layer1Done);
}
VectorI3 CenterIndexLoop3D::Index() const
{
	return VectorI3(Layer0.Index.X, Layer0.Index.Y, Layer1Index.X);
}

void CenterIndexLoop3D::New(unsigned int limit)
{
	Limit = limit;
	Layer0.Limit = Limit;

	Layer1New(0);
	Layer0.New(Layer1Index.Y);
}
void CenterIndexLoop3D::Continue()
{
	if (!Layer0.Done)
	{
		Layer0.Continue();
		if (Layer0.Done)
		{
			if (!Layer1Done)
			{
				Layer1Loop();
				if (Layer1Done)
				{
					Layer1New(Layer1Size + 1);
				}
				Layer0.New(Layer1Index.Y);
			}
		}
	}
}
