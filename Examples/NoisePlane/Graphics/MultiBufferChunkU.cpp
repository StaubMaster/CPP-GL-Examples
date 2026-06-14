#include "MultiBufferChunkU.hpp"
#include <iostream>





bool MultiBufferChunkU::Entry::IsEmpty() const
{
	return (Offset == 0 && Length == 0);
}
void MultiBufferChunkU::Entry::MakeEmpty()
{
	Offset = 0;
	Length = 0;
}
void MultiBufferChunkU::Entry::Put(const Container::Array<VoxelGraphics::MainFaceU> & data)
{
	Buffer.Remove(*this);
	Length = data.Length();
	Buffer.Insert(*this);
	if (!IsEmpty())
	{
		Buffer.Buffer.MainBuffer.DataPart(Offset * sizeof(VoxelGraphics::MainFaceU), data.ToVoid());
	}
}

MultiBufferChunkU::Entry::~Entry()
{
	//std::cout << "delete BufferUEntry of Length: " << Length << " at " << Offset << '\n';
	Buffer.Remove(*this);
}
MultiBufferChunkU::Entry::Entry(MultiBufferChunkU & buffer)
	: Buffer(buffer)
	, Offset(0)
	, Length(0)
{ }





MultiBufferChunkU::~MultiBufferChunkU()
{ }
MultiBufferChunkU::MultiBufferChunkU()
	: Size()
	, Buffer()
	, Layout()
{
	Buffer.MainBuffer.Init(Layout);
}

void MultiBufferChunkU::NewSize(unsigned int size)
{
	Buffer.MainBuffer.DataFull(size);
	Size = size / sizeof(VoxelGraphics::MainFaceU);
}

bool MultiBufferChunkU::CheckEntry(Entry & entry)
{
	if ((entry.Offset + entry.Length) >= Size)
	{
		return false;
	}
	for (unsigned int i = 0; i < Entrys.Count(); i++)
	{
		Entry & other = *(Entrys[i]);
		if (
			(entry.Offset + entry.Length) > (other.Offset) &&
			(entry.Offset) < (other.Offset + other.Length)
		)
		{
			return false;
		}
	}
	return true;
}
void MultiBufferChunkU::Insert(Entry & entry)
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
		Offsets.Insert(entry.Offset * 6);
		Lengths.Insert(entry.Length * 6);
		//std::cout << "insert BufferUEntry of Length: " << entry.Length << " at " << entry.Offset << '\n';
		return;
	}

	for (unsigned int i = 0; i < Entrys.Count(); i++)
	{
		Entry & other = *(Entrys[i]);
		entry.Offset = other.Offset + other.Length;
		if (CheckEntry(entry))
		{
			Entrys.Insert(&entry);
			Offsets.Insert(entry.Offset * 6);
			Lengths.Insert(entry.Length * 6);
			//std::cout << "insert BufferUEntry of Length: " << entry.Length << " at " << entry.Offset << '\n';
			return;
		}
	}

	std::cout << " failed BufferUEntry of Length: " << entry.Length << '\n';

	entry.MakeEmpty();
}
void MultiBufferChunkU::Remove(Entry & entry)
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
	//std::cout << "remove BufferUEntry of Length: " << entry.Length << " at " << entry.Offset << '\n';
	entry.MakeEmpty();
}
void MultiBufferChunkU::Draw()
{
	Buffer.Bind();
	Buffer.MainBuffer.Update();
	glMultiDrawArrays((unsigned int)GL::DrawMode::Triangles, Offsets.ToArray().Memory(), Lengths.ToArray().Memory(), Entrys.Count());
}
