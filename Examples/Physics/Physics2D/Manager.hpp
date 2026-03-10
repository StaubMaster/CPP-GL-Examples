#ifndef  PHYSICS_2D_MANAGER_HPP
# define PHYSICS_2D_MANAGER_HPP

# include "Miscellaneous/EntryContainer/Binary.hpp"
# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Array.hpp"

# include "Graphics/Texture/Array2D.hpp"

# include "Physics2D/InstanceManager.hpp"
# include "Physics2D/Object.hpp"

# include "Physics2D/Shaders/PolyGon.hpp"
# include "WireFrame2D/Shader.hpp"

# include "Arrow2D/Shader.hpp"
# include "Arrow2D/Buffer.hpp"
# include "Arrow2D/Inst/Data.hpp"

#include "ValueType/Undex.hpp"
#include "ValueType/View2D.hpp"
#include "ValueType/Point2D.hpp"



struct DirectoryInfo;

namespace Physics2D
{
struct Manager
{
	Physics2D::Shaders::PolyGon		Shader_PolyGon;
	Wire2D::Shader					Shader_WireFrame;
	Container::Array<Physics2D::InstanceManager>	MainInstances;
	
	::Arrow2D::Shader								Shader_Arrow;
	::Arrow2D::Buffer								Buffer_Arrow;
	::Texture::Array2D								Texture_Arrow;
	EntryContainer::Binary<Arrow2D::Inst::Data>		Instances_Arrow;

	Container::Binary<Physics2D::Object>			Objects;
	
	Point2D		Gravity;
	float		AirResistance;

	~Manager();
	Manager();

	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	void Dispose();

	void InitExternal(const DirectoryInfo & ShaderDir);
	void InitInternal(const DirectoryInfo & ImageDir);

	void GraphicsCreate();
	void GraphicsDelete();

	void Arrow_Main_Default();
	void Arrow_Inst_Update();
	void Arrow_Draw();

	void Draw();
	void UpdateGraphics();



	void UpdateGravity(float timeDelta);
	void UpdateAirResistance(float timeDelta);

	void UpdateCollision(float timeDelta);
	void UpdateOrientation(float timeDelta);
	void Update(float timeDelta);



	Undex FindObjectIndex(Point2D p) const;
};
};

#endif