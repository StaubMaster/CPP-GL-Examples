#ifndef  TEXTURE_BASE_HPP
# define TEXTURE_BASE_HPP

# include "OpenGLTypes.hpp"
# include "OpenGLEnums.hpp"

class FileInfo;

struct VectorU3;
typedef VectorU3 VectorU3;
struct ColorU4;

namespace Texture
{
class Base
{
	private:
	static GL::TextureID	None; // put this in GL:

	protected:
	public:
	GL::TextureTarget	Target;
	GL::TextureID		ID;

	public:
	virtual void LogInfo(bool self = true) const;



	public:
	virtual ~Base();
	Base() = delete;
	Base(GL::TextureTarget target);
	Base(const Base & other);
	Base & operator=(const Base & other);



	public:
	bool	Exists() const;
	bool	IsBound() const;
	void	Bind();

	static GL::TextureID	Bound(GL::TextureTarget target);
	static void				BindNone(GL::TextureTarget target);



	public:
	void	Create();
	void	Delete();



	public:
	void	DefaultParams();

	enum class WrapType : int
	{
		ClampToEdge = GL_CLAMP_TO_EDGE,
		ClampToBorder = GL_CLAMP_TO_BORDER,
		MirroredRepeat = GL_MIRRORED_REPEAT,
		Repeat = GL_REPEAT,
		MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE,
	};
	void	WrapX(WrapType wrap);
	void	WrapY(WrapType wrap);
	void	WrapZ(WrapType wrap);

	enum class FilterMinType : int
	{
		Nearest = GL_NEAREST,
		Linear = GL_LINEAR,
		NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
		LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
		NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
		LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR,
	};
	void	FilterMin(FilterMinType filter);

	enum class FilterMagType : int
	{
		Nearest = GL_NEAREST,
		Linear = GL_LINEAR,
	};
	void	FilterMag(FilterMagType filter);

	// operator<< for enums
	// return functions



	public:
	void	Full3D(VectorU3 size, const ColorU4 * data);
	void	Part3D(VectorU3 size, VectorU3 offset, const ColorU4 * data);
};
};

#endif