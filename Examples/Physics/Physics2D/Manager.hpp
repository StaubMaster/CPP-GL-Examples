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

# include "Arrow2D/Manager.hpp"

#include "ValueType/Undex.hpp"
#include "ValueType/View2D.hpp"
#include "ValueType/Point2D.hpp"



struct DirectoryInfo;

namespace Physics2D
{
struct Manager
{
	static Manager * CurrentPointer;
	static Manager & Current();
	static bool CheckCurrent();
	static void ClearCurrent();
	bool IsCurrent() const;
	void MakeCurrent();



	Physics2D::Shaders::PolyGon		Shader_PolyGon;
	Wire2D::Shader					Shader_WireFrame;

	Container::Array<Physics2D::InstanceManager>	MainInstances;

	::Arrow2D::Manager		Arrow;

//	Container::Binary<Physics2D::Object>	Objects;
	Container::Binary<Physics2D::Object *>	Objects;

	Point2D		Gravity;
	float		AirResistance;

	float	GravityToY;

	~Manager();
	Manager();

	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	void Dispose();

	void InitExternal(const DirectoryInfo & ShaderDir);
	void InitInternal(const DirectoryInfo & ImageDir);

	void GraphicsCreate();
	void GraphicsDelete();
	void GraphicsUpdate();

//	void Arrow_Main_Default();
//	void Arrow_Inst_Update();
//	void Arrow_Draw();

	void Draw();



	void UpdateGravity(float timeDelta);
	void UpdateAirResistance(float timeDelta);

	void UpdateCollision(float timeDelta);
	void UpdateTransformation(float timeDelta);
	void Update(float timeDelta);



	Undex FindObjectIndex(Point2D p) const;
};
};

#endif