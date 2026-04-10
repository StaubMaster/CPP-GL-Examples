#include "PlaneManager.hpp"

#include "ValueType/Bool2D.hpp"



PlaneValue::~PlaneValue() { }
PlaneValue::PlaneValue()
	: Known(false)
	, Value(0.0f)
{ }
PlaneValue::PlaneValue(const PlaneValue & other)
	: Known(other.Known)
	, Value(other.Value)
{ }
PlaneValue & PlaneValue::operator=(const PlaneValue & other)
{
	Known = other.Known;
	Value = other.Value;
	return *this;
}

ColorF4 PlaneValue::ToColor() const
{
	if (Value > 0.0f) { return ColorF4(+Value, 0, 0); }
	if (Value < 0.0f) { return ColorF4(0, 0, -Value); }
	return ColorF4(0, 0, 0);
}





PlaneNeighbours::~PlaneNeighbours() { }
PlaneNeighbours::PlaneNeighbours()
	/*: Planes{
		nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr
	}*/
	: Planes{
		nullptr, nullptr,
		nullptr, nullptr,
	}
{ }
PlaneNeighbours::PlaneNeighbours(const PlaneNeighbours & other)
	/*: Planes{
		other.Planes[0], other.Planes[1], other.Planes[2],
		other.Planes[3], other.Planes[4], other.Planes[5],
		other.Planes[6], other.Planes[7], other.Planes[8]
	}*/
	: Planes{
		other.Planes[0b00], other.Planes[0b01],
		other.Planes[0b10], other.Planes[0b11],
	}
{ }
PlaneNeighbours & PlaneNeighbours::operator=(const PlaneNeighbours & other)
{
	//Planes[0] = other.Planes[0];
	//Planes[1] = other.Planes[1];
	//Planes[2] = other.Planes[2];
	//Planes[3] = other.Planes[3];
	//Planes[4] = other.Planes[4];
	//Planes[5] = other.Planes[5];
	//Planes[6] = other.Planes[6];
	//Planes[7] = other.Planes[7];
	//Planes[8] = other.Planes[8];
	Planes[0b00] = other.Planes[0b00];
	Planes[0b01] = other.Planes[0b01];
	Planes[0b10] = other.Planes[0b10];
	Planes[0b11] = other.Planes[0b11];
	return *this;
}

PlaneValue PlaneNeighbours::Value(unsigned int plane_idx, unsigned int tile_idx) const
{
	PlaneValue val;
	if (Planes[plane_idx] != nullptr)
	{
		val.Value = (*Planes[plane_idx]).Values[tile_idx];
		val.Known = true;
	}
	return val;
}





PlaneManager::~PlaneManager() { }
PlaneManager::PlaneManager()
{ }

void PlaneManager::PlanesGenerate(const Perlin2D & noise)
{
	Undex2D size(PLANES_PER_SIDE, PLANES_PER_SIDE);
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Undex2D u = size.ConvertX(i);
		Planes[i].Undex = u;
		Planes[i].Generate(noise);
	}
}
void PlaneManager::PlanesToBuffers()
{
	Undex2D size(PLANES_PER_SIDE, PLANES_PER_SIDE);
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Undex2D udx = size.ConvertX(i);
		PlaneNeighbours neighbours = NeighboursAround(udx);
		PlaneToMainBuffer(neighbours, Buffers[i].Main);
		{
			Container::Binary<PlaneGraphics::InstData> data;
			PlaneGraphics::InstData temp;
			temp.Pos.X = (*neighbours.Planes[0b00]).Undex.X * PLANE_VALUES_PER_SIDE * PLANE_SCALE;
			temp.Pos.Y = 0;
			temp.Pos.Z = (*neighbours.Planes[0b00]).Undex.Y * PLANE_VALUES_PER_SIDE * PLANE_SCALE;
			data.Insert(temp);
			Buffers[i].Inst.Change(data);
		}
	}
}

PlaneNeighbours PlaneManager::NeighboursAround(Undex2D udx)
{
	PlaneNeighbours neighbours;

	Undex2D size(PLANES_PER_SIDE, PLANES_PER_SIDE);
	neighbours.Planes[0b00] = &Planes[size.ConvertX(udx)];

	unsigned int edge = PLANES_PER_SIDE - 1;

	if (udx.X != edge) { neighbours.Planes[0b01] = &Planes[size.ConvertX(Undex2D(udx.X + 1, udx.Y + 0))]; }
	if (udx.Y != edge) { neighbours.Planes[0b10] = &Planes[size.ConvertX(Undex2D(udx.X + 0, udx.Y + 1))]; }
	if (udx.X != edge && udx.Y != edge) { neighbours.Planes[0b11] = &Planes[size.ConvertX(Undex2D(udx.X + 1, udx.Y + 1))]; }

	return neighbours;
}

void PlaneManager::PlaneToMainBuffer(const PlaneNeighbours & neighbours, PlaneGraphics::MainBuffer & buffer)
{
	Container::Binary<PlaneGraphics::MainData> data;
	Undex2D size(PLANE_VALUES_PER_SIDE, PLANE_VALUES_PER_SIDE);
	for (unsigned int i = 0; i < PLANE_VALUES_PER_AREA ; i++)
	{
		Undex2D u = size.ConvertX(i);
		Undex2D u0 = Undex2D(u.X + 0, u.Y + 0) % size;
		Undex2D u1 = Undex2D(u.X + 1, u.Y + 1) % size;
		Bool2D comp = u0 < u1;

		unsigned int udxs[4];
		udxs[0b00] = size.ConvertX(Undex2D(u0.X, u0.Y));
		udxs[0b01] = size.ConvertX(Undex2D(u1.X, u0.Y));
		udxs[0b10] = size.ConvertX(Undex2D(u0.X, u1.Y));
		udxs[0b11] = size.ConvertX(Undex2D(u1.X, u1.Y));

		PlaneValue vals[4];

		if (comp.GetX() && comp.GetY())
		{
			vals[0b00] = neighbours.Value(0b00, udxs[0b00]);
			vals[0b01] = neighbours.Value(0b00, udxs[0b01]);
			vals[0b10] = neighbours.Value(0b00, udxs[0b10]);
			vals[0b11] = neighbours.Value(0b00, udxs[0b11]);
		}

		if (!comp.GetX() && comp.GetY())
		{
			vals[0b00] = neighbours.Value(0b00, udxs[0b00]);
			vals[0b01] = neighbours.Value(0b01, udxs[0b01]);
			vals[0b10] = neighbours.Value(0b00, udxs[0b10]);
			vals[0b11] = neighbours.Value(0b01, udxs[0b11]);
		}

		if (comp.GetX() && !comp.GetY())
		{
			vals[0b00] = neighbours.Value(0b00, udxs[0b00]);
			vals[0b01] = neighbours.Value(0b00, udxs[0b01]);
			vals[0b10] = neighbours.Value(0b10, udxs[0b10]);
			vals[0b11] = neighbours.Value(0b10, udxs[0b11]);
		}

		if (!comp.GetX() && !comp.GetY())
		{
			vals[0b00] = neighbours.Value(0b00, udxs[0b00]);
			vals[0b01] = neighbours.Value(0b01, udxs[0b01]);
			vals[0b10] = neighbours.Value(0b10, udxs[0b10]);
			vals[0b11] = neighbours.Value(0b11, udxs[0b11]);
		}

		PlaneGraphics::MainData temp[4];

		temp[0b00].Pos = Point3D((u.X + 0) * PLANE_SCALE, vals[0b00].Value, (u.Y + 0) * PLANE_SCALE);
		temp[0b01].Pos = Point3D((u.X + 1) * PLANE_SCALE, vals[0b01].Value, (u.Y + 0) * PLANE_SCALE);
		temp[0b10].Pos = Point3D((u.X + 0) * PLANE_SCALE, vals[0b10].Value, (u.Y + 1) * PLANE_SCALE);
		temp[0b11].Pos = Point3D((u.X + 1) * PLANE_SCALE, vals[0b11].Value, (u.Y + 1) * PLANE_SCALE);

		temp[0b00].Col = vals[0b00].ToColor();
		temp[0b01].Col = vals[0b01].ToColor();
		temp[0b10].Col = vals[0b10].ToColor();
		temp[0b11].Col = vals[0b11].ToColor();

		if (vals[0b00].Known && vals[0b01].Known && vals[0b10].Known) { data.Insert(temp[0b00]); data.Insert(temp[0b10]); data.Insert(temp[0b01]); }
		if (vals[0b10].Known && vals[0b01].Known && vals[0b11].Known) { data.Insert(temp[0b01]); data.Insert(temp[0b10]); data.Insert(temp[0b11]); }
	}
	buffer.Change(data);
}



void PlaneManager::GraphicsCreate()
{
	Shader.Create();
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Buffers[i].Create();
		Buffers[i].Main.Init();
		Buffers[i].Inst.Init();
	}
}
void PlaneManager::GraphicsDelete()
{
	Shader.Delete();
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Buffers[i].Delete();
	}
}
void PlaneManager::Draw()
{
	Shader.Bind();
	for (unsigned int i = 0; i < PLANES_PER_AREA; i++)
	{
		Buffers[i].Draw();
	}
}
