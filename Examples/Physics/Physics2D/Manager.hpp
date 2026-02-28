#ifndef  PHYSICS_2D_MANAGER_HPP
# define PHYSICS_2D_MANAGER_HPP

# include "Miscellaneous/EntryContainer/Binary.hpp"

# include "Graphics/Texture/Array2D.hpp"

# include "Physics2D/Shaders/PolyGon.hpp"
# include "WireFrame2D/Shader.hpp"

# include "Arrow2D/Shader.hpp"
# include "Arrow2D/Buffer.hpp"
# include "Arrow2D/Inst/Data.hpp"



struct DirectoryInfo;

namespace Physics2D
{
struct Manager
{
	Physics2D::Shaders::PolyGon	Shader_PolyGon;
	Wire2D::Shader				Shader_WireFrame;
	::Arrow2D::Shader			Shader_Arrow;

	EntryContainer::Binary<Arrow2D::Inst::Data> *	Instances_Arrow;

	::Arrow2D::Buffer	Buffer_Arrow;
	::Texture::Array2D	Texture_Arrow;

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
};
};

#endif