#ifndef  CHUNK_MANAGER_HPP
# define CHUNK_MANAGER_HPP

# include "ValueGen/Perlin2D.hpp"
# include "ValueGen/Perlin3D.hpp"

# include "Graphics/Shader/Base.hpp"
# include "Graphics/ShaderLayout.hpp"
# include "Graphics/Buffer.hpp"

# include "Graphics/Main/Data.hpp"

# include "ValueType/Vector/I3.hpp"
# include "ValueType/Box/I3.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "Graphics/Texture/Array2D.hpp"

//# include "GridCast/GridCast3D.hpp"

# include "Telemetry/ValueAverager.hpp"
# include "Telemetry/StopWatch.hpp"

# include <mutex>
# include <atomic>
# include <condition_variable>

struct Voxel;
struct Chunk;
struct Chunk;
struct ChunkGenerationNoise;
struct AccessLockedChunk;
enum class AxisRel : unsigned char;

struct ChunkNeighbour;

struct Ray3D;
class PolyHedra;

struct VoxelHit;

#include <iostream>
#include "ValueType/_Show.hpp"

# include "Telemetry/WaitDoTime.hpp"
# include "ContainerLock.hpp"
# include "Miscellaneous/Container/Array3D.hpp"

# include "Graphics/MultiBufferChunkU.hpp"



// CenterIndexLoop
# include "ValueType/Vector/I2.hpp"

struct CenterIndexLoop2D
{
	unsigned int	Limit;

	bool			Done;
	unsigned int	Size;
	unsigned char	Control;
	VectorI2		Index;

	void New(unsigned int layer)
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
	void Continue()
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
};
struct CenterIndexLoop3D
{
unsigned int		Limit;

CenterIndexLoop2D	Layer0;

bool				Layer1Done;
unsigned int		Layer1Size;
unsigned char		Layer1Control;
VectorI2			Layer1Index;

void Layer1New(unsigned int layer)
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
void Layer1Loop()
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

bool Done() const
{
	return (Layer0.Done || Layer1Done);
}
VectorI3 Index() const
{
	return VectorI3(Layer0.Index.X, Layer0.Index.Y, Layer1Index.X);
}

void New(unsigned int limit)
{
	Limit = limit;
	Layer0.Limit = Limit;

	Layer1New(0);
	Layer0.New(Layer1Index.Y);
}
void Continue()
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
};



# include "AuxThread1.hpp"

struct ChunkManager
{
	public:
	static WaitDoTime	TimeInsert;

	static WaitDoTime	TimeInsertNew;
	static WaitDoTime	TimeInsertPut;

	static WaitDoTime	TimeRemove;
	static WaitDoTime	TimeUpdate;
	static WaitDoTime	TimeUpdateInsert;
	static WaitDoTime	TimeUpdateRemove;

	static WaitDoTime	TimeGraphicsCreate;
	static WaitDoTime	TimeGraphicsDelete;
	static WaitDoTime	TimeDraw;



	public:
	Texture::Array2D				Texture;
	::Shader::Base					ShaderU;
	VoxelGraphics::ShaderLayout		ShaderLayoutU;
	MultiBufferChunkU				BufferU;

	// store 2D Noise Plane. so that height values only get calculated once per XZ Coordinate

	public:
	Array3D<Chunk*>	Chunks;
	ContainerLock	ChunksLock;

	unsigned int	KnowSize;
	unsigned int	CareSize;

	void	Clear();
	void	ChangeSize(unsigned int know_size, unsigned int care_size);
	void	ChangeCenter(VectorI3 center);

	VectorI3	Center;
	BoxI3		KnowBox;
	BoxI3		CareBox;

	VectorI3	absolute(VectorU3 u) const;
	VectorU3	relative(VectorI3 i) const;

	Chunk *					FindAbsOrNull(VectorI3 idx);
	AccessLockedChunk		FindAccess(VectorI3 idx);

	private:
	public:
	Container::Binary<Chunk*>	ChunksToInsert; // do this in Chunks
	Container::Binary<Chunk*>	ChunksToRemove; // ChunkDisposal
	ContainerLock				ChunksToInsertLock;
	ContainerLock				ChunksToRemoveLock;

	public:
	void	InsertAround();
	void	RemoveAround();

	void	UpdateChunksContainer();



	public:
	~ChunkManager();
	ChunkManager();

	ChunkManager(const ChunkManager & other) = delete;
	ChunkManager & operator=(const ChunkManager & other) = delete;



	private:
	public:
	VoxelHit		HitVoxel(Ray3D ray);



	/* make a Queue for Generating/Assambling ?
		Problem:
			I want the nearest stuff to be generated first
		Solution:
			the thing that Queues a Generation can be a CenterIndexLoop
			so the stuff nearer to the Center get generated first
			which then means that the stuff near the Center get assambled first

		Problem:
			duplicates in Queue
		Solution:
			keep the flags on weather the Chunks actually needs that done or not
			if not, just skip it

		Problem:
			what if the Center changes, a lot
			now the Center is of what was the Edge
			but the Queue is alreay filled with Chunks that area now far away
			the stuff close by should be prioratized
		Solution:
			this would require soring the distances of all Chunks
			and then using Binary insertion to insert new ones
			this would also mean recalculating Distances when Center changes
			could probably just use Manhatton distance to keep Distance simple
	*/

	public:
	std::mutex					GenerateChunkConditionMutex;
	std::condition_variable		GenerateChunkConditionVar;
	CenterIndexLoop3D			GenerateChunkFindLoop;
	unsigned int				GenerateChunkFindCandidateCount;
	AccessLockedChunk			GenerateChunkFind();

	public:
	std::mutex					AssambleChunkConditionMutex;
	std::condition_variable		AssambleChunkConditionVar;
	unsigned int				AssambleChunkFindCandidateCount;
	AccessLockedChunk			AssambleChunkFind();



	public:
	// put Shader /Buffer here ?

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsUpdate();

	/* BufferUpdate
		None: no Vertex Data
		Want: requrest to make Vertex Data
		Make: make Vertex Data
		Have: requrest to put Vertex Data into Buffer
		Bind: put Vertex Data into Buffer
		Done: Vertex Data is freed
	*/

	public:
	::AuxThread1				AuxThread1;

	public:
	std::mutex					BufferDataHaveQueueMutex;
	Container::Binary<Chunk *>	BufferDataHaveQueue;

	public:
	static ValueAverager<float>		DrawTotal;
	static ValueAverager<float>		DrawWait;
	static ValueAverager<float>		DrawTextureBind;
	static ValueAverager<float>		DrawShaderBind;
	static ValueAverager<float>		DrawUpdateBind;
	static ValueAverager<float>		DrawBufferDraw;

	public:
	void	Draw();
};

#endif