#ifndef  GRAPHICS_2D_MANAGER_HPP
# define GRAPHICS_2D_MANAGER_HPP

# include "Miscellaneous/EntryContainer/Binary.hpp"
# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Array.hpp"

# include "Graphics/Texture/Array2D.hpp"

# include "Physics2D/InstanceManager.hpp"
# include "Physics2D/Object.hpp"

# include "Physics2D/Shaders/PolyGon.hpp"
# include "WireFrame2D/Shader.hpp"

# include "Arrow2D/Manager.hpp"

#include "ValueType/Undex.hpp"
#include "ValueType/View2D.hpp"
#include "ValueType/Point2D.hpp"



# include "Miscellaneous/EntryContainer/Binary.hpp"

# include "Graphics/Buffer/MainInst.hpp"
# include "Graphics/Buffer/MainElemInst.hpp"

# include "Graphics2D/Inst/Buffer.hpp"
# include "ValueType/Trans2D.hpp"

# include "PolyGon/PolyGon.hpp"
# include "PolyGon/Graphics/Buffer.hpp"

# include "WireFrame2D/WireFrame2D.hpp"
# include "WireFrame2D/Main/Buffer.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "IntrinsicData.hpp"



namespace Graphics2D
{
namespace PolyGon
{
struct Manager
{
	::BufferArray::MainInst<PolyGonGraphics::Buffer, Graphics2D::Inst::Buffer>	Buffer;

	~Manager();
	Manager();

	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	void Dispose();



	void GraphicsInitExternal();
	void GraphicsInitInternal();

	void GraphicsCreate();
	void GraphicsDelete();
	void GraphicsUpdate();
};
};
};

#endif