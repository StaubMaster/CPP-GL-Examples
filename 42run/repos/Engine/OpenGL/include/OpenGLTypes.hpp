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
	typedef unsigned int ShaderID; // None = 0
	enum class ShaderType : unsigned int;
	enum class ShaderParameterName : unsigned int;



	//	Shader Program
	typedef unsigned int ShaderProgramID; // None = 0
	enum class ShaderProgramParameterName : unsigned int;



	//	Uniform
	typedef int UniformLocation;



	//	Buffer
	typedef unsigned int BufferID; // None = 0
	enum class BufferTarget : unsigned int;
	enum class BufferDataUsage : unsigned int;



	//	Attribute
	typedef int AttributeLocation; // None = -1
	enum class AttributeType : unsigned int;
	enum class AttributeIntType : unsigned int;
	typedef unsigned int AttributeDivisor;
	typedef unsigned int AttributeStride;
	typedef const unsigned char * AttributeOffset;



	//	Block
	typedef unsigned int BlockIndex;
	typedef unsigned int BlockBinding;



	//	VertexArray
	typedef unsigned int VertexArrayID; // None = 0



	//	Drawing
	enum class DrawMode : unsigned int;
	enum class DrawIndexType : unsigned int;



	//	Texture
	typedef unsigned int TextureID; // None = 0
	enum class TextureTarget : unsigned int;
	enum class TextureParameterName : unsigned int;



	//	PixelData
	enum class PixelDataType : unsigned int;
	enum class PixelDataFormat : unsigned int;

	//typedef unsigned int InternalFormat;
	//enum class InternalFormatBase : InternalFormat;
	//enum class InternalFormatSized : InternalFormat;
	//enum class InternalFormatCompressed : InternalFormat;
	// enum dosent implcitly convert to base type
	enum class InternalFormat : unsigned int;



	//	FrameBuffer
	typedef unsigned int FrameBufferID; // None = 0
	enum class FrameBufferTarget : unsigned int;
};

#endif