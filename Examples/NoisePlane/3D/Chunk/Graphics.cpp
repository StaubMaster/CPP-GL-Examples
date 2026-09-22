#include "3D/Chunk/Graphics.hpp"
#include "3D/Chunk/GraphicsData.hpp"
#include "3D/Chunk.hpp"

#include "Telemetry/StopWatch.hpp"

#include "Graphics/Shader/Code.hpp"

#include "DirectoryInfo.hpp"



void ChunkGraphics::ChangeMedia(const DirectoryInfo & dir)
{
	ShaderU.Change({
		dir.File("Shaders/Voxel/VoxelU.vert"),
		dir.File("Shaders/Voxel/Voxel.frag"),
	});
	ShaderU.AssignLayout(ShaderLayoutU);

	ShaderF.Change({
		dir.File("Shaders/Voxel/VoxelF.vert"),
		dir.File("Shaders/Voxel/Voxel.frag"),
	});
	ShaderF.AssignLayout(ShaderLayoutF);

	BufferLayoutU.Voxel.Change(0);
	BufferLayoutU.Texture.Change(1);
	BufferLayoutU.Chunk.Change(2);
	BufferU.Buffer.AssignLayout(BufferLayoutU);

	BufferLayoutF.Pos.Change(0);
	BufferLayoutF.Tex.Change(1);
	BufferLayoutF.Normal.Change(2);
	BufferF.Buffer.AssignLayout(BufferLayoutF);
}



void ChunkGraphics::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Texture.Create();
	ShaderU.Create();
	ShaderF.Create();
	BufferU.Create();
	BufferF.Create();

	BufferU.Init();
	BufferU.SizeOf = sizeof(VoxelGraphicsDataU::Vertex);
	BufferU.NewSizeMemory(1024 * 1024 * 1024); // 1GiB

	BufferF.Init();
	BufferF.SizeOf = sizeof(VoxelGraphicsDataF::Vertex);
	BufferF.NewSizeMemory(1024 * 1024 * 1024); // 1GiB

	GraphicsExist = true;
}
void ChunkGraphics::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Texture.Delete();
	ShaderU.Delete();
	ShaderF.Delete();
	BufferU.Delete();
	BufferF.Delete();

	BufferU.Buffer.Count = 0;
	BufferF.Buffer.Count = 0;

	GraphicsExist = false;
}



unsigned int ChunkGraphics::BufferHave::QueueCount()
{
	QueueMutex.lock();
	unsigned int c = Queue.Count();
	QueueMutex.unlock();
	return c;
}
void ChunkGraphics::BufferHave::QueuePut(Chunk * chunk)
{
	if (chunk == nullptr) { return; }

	QueueMutex.lock();

	/*for (unsigned int i = 0; i < Queue.Count(); i++)
	{
		if (Queue[i] == chunk)
		{
			QueueMutex.unlock();
			return;
		}
	}*/
	chunk -> BufferData_Have = true;
	Queue.Insert(chunk);

	QueueMutex.unlock();
}



ValueAccumulator<float> ChunkGraphics::DrawTotal(64);
ValueAccumulator<float> ChunkGraphics::DrawWait(64);
ValueAccumulator<float> ChunkGraphics::DrawTextureBind(64);
ValueAccumulator<float> ChunkGraphics::DrawShaderBind(64);
ValueAccumulator<float> ChunkGraphics::DrawUpdateBind(64);
ValueAccumulator<float> ChunkGraphics::DrawBufferDraw(64);

//#include <iostream>
void ChunkGraphics::Draw()
{
	if (!GraphicsExist) { return; }



	StopWatch sw;

	sw.Clear();
	Texture.Bind();
	DrawTextureBind.NewValue(sw.ElapsedTime());



	sw.Clear();
	BufferDataHave.QueueMutex.lock();
	for (unsigned int i = 0; i < BufferDataHave.Queue.Count(); i++)
	{
		Chunk * ptr = BufferDataHave.Queue[i];
		if (ptr == nullptr) { continue; }
		const Chunk & ref = *ptr;
		if (!ref.BufferData_Have) { continue; }
		ptr -> BufferData_Update();
	}
	BufferDataHave.Queue.Clear();
	BufferDataHave.QueueMutex.unlock();
	DrawUpdateBind.NewValue(sw.ElapsedTime());



	sw.Clear();
	ShaderU.Bind();
	DrawShaderBind.NewValue(sw.ElapsedTime());

	sw.Clear();
	BufferU.Bind();
	BufferU.Draw();
	DrawBufferDraw.NewValue(sw.ElapsedTime());



	sw.Clear();
	ShaderF.Bind();
	DrawShaderBind.NewValue(sw.ElapsedTime());

	/*{
		std::cout << "Entrys: " << BufferF.Entrys.Count() << '\n';
		for (unsigned int i = 0; i < BufferF.Entrys.Count(); i++)
		{
			std::cout << BufferF.Entrys[i] -> Offset << ' ';
			std::cout << BufferF.Entrys[i] -> Length << '\n';
		}
		std::cout << '\n';
	}*/
	sw.Clear();
	BufferF.Bind();
	BufferF.Draw();
	DrawBufferDraw.NewValue(sw.ElapsedTime());
}
