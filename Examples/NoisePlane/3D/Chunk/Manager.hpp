#ifndef  CHUNK_MANAGER_HPP
# define CHUNK_MANAGER_HPP

# include "Telemetry/WaitDoTime.hpp"

# include "3D/Chunk/Container.hpp"
# include "3D/Chunk/Graphics.hpp"

# include "AuxThread/AuxThread1.hpp"
# include "AuxThread/AuxThread2.hpp"
# include "AuxThread/AuxThread3.hpp"

class DirectoryInfo;

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
	~ChunkManager() = default;
	ChunkManager();
	ChunkManager(const ChunkManager & other) = delete;
	ChunkManager & operator=(const ChunkManager & other) = delete;

	public:
	// store 2D Noise Plane. so that height values only get calculated once per XZ Coordinate
	ChunkContainer	Container;

	public:
	//							// DrawBufferThread
	::AuxThread1	AuxThread1;	// MakeBufferThread
	::AuxThread2	AuxThread2;
	::AuxThread3	AuxThread3;

	public:
	ChunkGraphics	Graphics;

	public:
	void	Draw();
};

#endif