#ifndef  ARROW_2D_MANAGER_HPP
# define ARROW_2D_MANAGER_HPP

# include "Arrow2D/Shader.hpp"
# include "Arrow2D/Buffer.hpp"

# include "Graphics/Texture/Array2D.hpp"

# include "Arrow2D/Inst/Data.hpp"
# include "Miscellaneous/EntryContainer/Binary.hpp"

class DirectoryInfo;

namespace Arrow2D
{
struct Manager
{
	static Manager * CurrentPointer;
	static Manager & Current();
	static bool CheckCurrent();
	static void ClearCurrent();
	bool IsCurrent() const;
	void MakeCurrent();

	::Arrow2D::Shader								Shader;
	::Arrow2D::Buffer								Buffer;
	::Texture::Array2D								Texture;
	EntryContainer::Binary<Arrow2D::Inst::Data>		Instances;

	~Manager();
	Manager();

	void Dispose();

	void InitExternal(const DirectoryInfo & ShaderDir);
	void InitInternal(const DirectoryInfo & ImageDir);

	void GraphicsCreate();
	void GraphicsDelete();
//	void GraphicsUpdate();

	void Main_Default();
	void Inst_Update();
	void Draw();
};
};

#endif