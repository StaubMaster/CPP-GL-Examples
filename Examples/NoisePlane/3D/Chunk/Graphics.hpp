#ifndef  CHUNK_GRAPHICS_HPP
# define CHUNK_GRAPHICS_HPP

# include "Telemetry/ValueAccumulator.hpp"

# include "3D/Voxel/Pallet/Geometry/Graphics/ShaderLayout.hpp"
# include "3D/Voxel/Pallet/Geometry/Graphics/U/Layout.hpp"
# include "3D/Voxel/Pallet/Geometry/Graphics/F/Layout.hpp"

# include "Graphics/Texture/Array2D.hpp"
# include "Graphics/VertexArray/Multi.hpp"

# include "Generics/Container/Binary.hpp"

# include <mutex>

class DirectoryInfo;

struct Chunk;

struct ChunkGraphics
{
	public:
	void	ChangeMedia(const DirectoryInfo & dir);

	public:
	bool	GraphicsExist = false;
	void	GraphicsCreate();
	void	GraphicsDelete();

	public:
	Texture::Array2D				Texture;

	::Shader::Base					ShaderU;
	::Shader::Base					ShaderF;
	VoxelGraphics::ShaderLayout		ShaderLayoutU;
	VoxelGraphics::ShaderLayout		ShaderLayoutF;

	VertexArray::Multi				BufferU;
	VertexArray::Multi				BufferF;
	VoxelGraphics::LayoutU			BufferLayoutU;
	VoxelGraphics::LayoutF			BufferLayoutF;

	/* BufferUpdate
		None: no Vertex Data
		Want: requrest to make Vertex Data
		Make: make Vertex Data
		Have: requrest to put Vertex Data into Buffer
		Bind: put Vertex Data into Buffer
		Done: Vertex Data is freed
	*/

	struct BufferHave
	{
		public:
		Container::Binary<Chunk *>	Queue;
		std::mutex					QueueMutex;
		public:
		unsigned int				QueueCount();
		void						QueuePut(Chunk * chunk);
	};
	ChunkGraphics::BufferHave	BufferDataHave;

	public:
	static ValueAccumulator<float>		DrawTotal;
	static ValueAccumulator<float>		DrawWait;
	static ValueAccumulator<float>		DrawTextureBind;
	static ValueAccumulator<float>		DrawShaderBind;
	static ValueAccumulator<float>		DrawUpdateBind;
	static ValueAccumulator<float>		DrawBufferDraw;

	public:
	void	Draw();
};

#endif