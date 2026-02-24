#ifndef  ARROW_2D_MANAGER_HPP
# define ARROW_2D_MANAGER_HPP

# include "Arrow2D/Shader.hpp"
# include "Arrow2D/Buffer.hpp"
//# include "Arrow2D/Main/Data.hpp"
//# include "Arrow2D/Inst/Data.hpp"
//# include "Miscellaneous/Container/Binary.hpp"
# include "Graphics/Texture/Array2D.hpp"

class DirectoryInfo;

namespace Arrow2D
{
struct Manager
{
	::Arrow2D::Shader	Shader;
	::Arrow2D::Buffer	Buffer;
	::Texture::Array2D	Texture;

	~Manager();
	Manager();

	void InitExternal(const DirectoryInfo & shaderDir);
	void InitInternal(const DirectoryInfo & imageDir);

	void GraphicsCreate();
	void GraphicsDelete();

	void Draw();
};
};

#endif