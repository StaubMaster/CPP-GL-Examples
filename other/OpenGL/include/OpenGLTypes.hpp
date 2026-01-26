#ifndef  OPEN_GL_TYPES_HPP
# define OPEN_GL_TYPES_HPP

namespace GL
{
	//	General
	typedef unsigned int	Size;

	typedef char *			CStringBuffer;
	typedef const char *	CString;

	typedef bool			VBool;

	typedef float			VFloat;
	typedef VFloat *		VFloatData;
	typedef const VFloat *	VFloatCData;

	typedef int				VInt;
	typedef VInt *			VIntData;
	typedef const VInt *	VIntCData;
	
	typedef unsigned int	VUInt;
	typedef VUInt *			VUIntData;
	typedef const VUInt *	VUIntCData;

	typedef const void *	VData;

	enum class Error : unsigned int;
	enum class ParameterName : unsigned int;
	enum class Capability : unsigned int;
	enum class ClearMask : unsigned int;

	enum class Comparison : unsigned int;

	enum class Side : unsigned int;
	enum class FrontSide : unsigned int;



	//	Shader
	typedef unsigned int ShaderID;
	enum class ShaderType : unsigned int;
	enum class ShaderParameterName : unsigned int;



	//	Shader Program
	typedef unsigned int ShaderProgramID;
	enum class ShaderProgramParameterName : unsigned int;



	//	Uniform
	typedef int UniformLocation;



	//	VertexArray
	typedef unsigned int VertexArrayID;



	//	Attribute
	typedef unsigned int AttributeID;
	enum class AttributeType : unsigned int;
	enum class AttributeIntType : unsigned int;
	typedef unsigned int AttributeDivisor;



	//	Drawing
	enum class DrawMode : unsigned int;
	enum class DrawIndexType : unsigned int;



	//	Buffer
	typedef unsigned int BufferID;
	enum class BufferTarget : unsigned int;
	enum class BufferDataUsage : unsigned int;



	//	Texture
	typedef unsigned int TextureID;
	enum class TextureTarget : unsigned int;
	enum class TextureParameterName : unsigned int;
	enum class TextureFormat : unsigned int;
	enum class TextureType : unsigned int;
	enum class TextureInternalFormat : unsigned int;
};

#endif