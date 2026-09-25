#include "Graphics/VertexArray/Multi.hpp"
#include "OpenGL.hpp"





bool VertexArray::Multi::Entry::IsEmpty() const
{
	return (Offset == 0 && Length == 0);
}
void VertexArray::Multi::Entry::MakeEmpty()
{
	Offset = 0;
	Length = 0;
}

unsigned int VertexArray::Multi::Entry::Limit() const
{
	return (Offset + Length);
}
bool VertexArray::Multi::Entry::Check(const Entry & other) const
{
	return ((Offset + Length) > (other.Offset)) && ((Offset) < (other.Offset + other.Length));
}

VertexArray::Multi::Entry::~Entry()
{
	Buffer.Remove(*this);
}
VertexArray::Multi::Entry::Entry(VertexArray::Multi & buffer)
	: Buffer(buffer)
{ }

void VertexArray::Multi::Entry::Put(const Container::Void & data)
{
	Buffer.Remove(*this);
	Length = data.Size / Buffer.SizeOf;
	Buffer.Insert(*this);
	if (!IsEmpty())
	{
		Buffer.Buffer.DataPart(Offset * Buffer.SizeOf, data);
	}
}





VertexArray::Multi::~Multi()
{ }
VertexArray::Multi::Multi()
	: Base()
	, Mode(GL::DrawMode::Triangles)
	, Buffer(GL::BufferDataUsage::DynamicDraw)
{ }

static void FailedPutFunc(unsigned int len);

bool VertexArray::Multi::CheckEntry(VertexArray::Multi::Entry & entry)
{
	if (entry.Limit() >= Buffer.Count)
	{
		return false;
	}
	for (unsigned int i = 0; i < Entrys.Count(); i++)
	{
		const VertexArray::Multi::Entry & other = *(Entrys[i]);
		if (entry.Check(other))
		{
			return false;
		}
	}
	return true;
}
void VertexArray::Multi::Insert(VertexArray::Multi::Entry & entry)
{
	if (entry.Length == 0)
	{
		entry.MakeEmpty();
		return;
	}

	entry.Offset = 0;
	if (CheckEntry(entry))
	{
		Entrys.Insert(&entry);
		Offsets.Insert(entry.Offset);
		Lengths.Insert(entry.Length);
		return;
	}

	for (unsigned int i = 0; i < Entrys.Count(); i++)
	{
		VertexArray::Multi::Entry & other = *(Entrys[i]);
		entry.Offset = other.Offset + other.Length;
		if (CheckEntry(entry))
		{
			Entrys.Insert(&entry);
			Offsets.Insert(entry.Offset);
			Lengths.Insert(entry.Length);
			return;
		}
	}

	entry.MakeEmpty();
	FailedPutFunc(entry.Length);
}
void VertexArray::Multi::Remove(VertexArray::Multi::Entry & entry)
{
	if (entry.IsEmpty())
	{
		return;
	}
	for (unsigned int i = 0; i < Entrys.Count(); i++)
	{
		if (Entrys[i] == &entry)
		{
			Entrys.RemoveAt(i);
			Offsets.RemoveAt(i);
			Lengths.RemoveAt(i);
			break;
		}
	}
	entry.MakeEmpty();
}



void VertexArray::Multi::NewSizeMemory(unsigned int memory)
{
	Buffer.Count = memory / SizeOf;
	Buffer.DataFull(memory);
}



unsigned int VertexArray::Multi::Count() const
{
	return Entrys.Count();
}
unsigned int VertexArray::Multi::LengthSum() const
{
	unsigned int sum = 0;
	for (unsigned int i = 0; i < Entrys.Count(); i++)
	{
		if (!Entrys[i] -> IsEmpty())
		{
			sum += Entrys[i] -> Length;
		}
	}
	return sum;
}



void VertexArray::Multi::Create()
{
	Base::Create();
	Buffer.Create();
}
void VertexArray::Multi::Delete()
{
	Base::Delete();
	Buffer.Delete();
}

void VertexArray::Multi::Init()
{
	Bind();

	Buffer.Init();
}

void VertexArray::Multi::Draw()
{
	GL::MultiDrawArrays(GL::DrawMode::Triangles, Offsets.ToArray().Memory(), Lengths.ToArray().Memory(), Entrys.Count());
}





#include <iostream>
static void FailedPutFunc(unsigned int len)
{
	std::cerr << "VertexArray::Multi::Entry: Failed to put Length: " << len << '\n';
}
