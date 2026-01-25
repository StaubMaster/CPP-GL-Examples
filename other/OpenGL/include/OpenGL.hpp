#ifndef OPEN_GL_HPP
# define OPEN_GL_HPP

# include "../glad/glad.h"
# include <GLFW/glfw3.h>

namespace GL
{
	//	General
	typedef unsigned int	Size;
	typedef char *				CStringBuffer;
	typedef const CStringBuffer	CString;

	typedef bool			VBool;
	typedef float			VFloat;
	typedef int				VInt;
	typedef unsigned int	VUInt;

	typedef VFloat *	VFloatData;
	typedef VInt *		VIntData;
	typedef VUInt *		VUIntData;

	typedef const VFloatData	VFloatCData;
	typedef const VIntData		VIntCData;
	typedef const VUIntData		VUIntCData;

	typedef const void *			VData;





	//	Shader
	typedef unsigned int ShaderID;
	enum class ShaderType : unsigned int
	{
		ComputeShader = GL_COMPUTE_SHADER,
		VertexShader = GL_VERTEX_SHADER,
		TessControlShader = GL_TESS_CONTROL_SHADER,
		TessEvaluationShade = GL_TESS_EVALUATION_SHADER,
		GemoetryShader = GL_GEOMETRY_SHADER,
		FragmentShader = GL_FRAGMENT_SHADER,
	};
	enum class ShaderParameterName : unsigned int
	{
		ShaderType = GL_SHADER_TYPE,
		DeleteStatus = GL_DELETE_STATUS,
		CompileStatus = GL_COMPILE_STATUS,
		InfoLogLength = GL_INFO_LOG_LENGTH,
		ShaderSourceLength = GL_SHADER_SOURCE_LENGTH,
	};
	int				GetShaderiv(ShaderID shader, ShaderParameterName parameterName);
	bool			IsShader(ShaderID shader);
	ShaderID		CreateShader(ShaderType type);
	void			DeleteShader(ShaderID shader);
	void			CompileShader(ShaderID shader);
	void			ShaderSource(ShaderID shader, Size count, CString str[], int len[]);
	void			ShaderSource(ShaderID shader, Size count, CString str[]);
	void			ShaderSource(ShaderID shader, CString str);
	void			GetShaderInfoLog(ShaderID shader, Size maxLength, int & length, CStringBuffer infoLog);
	CStringBuffer	GetShaderInfoLog(ShaderID shader, int & length);



	//	Shader Program
	typedef unsigned int ShaderProgramID;
	enum class ShaderProgramParameterName : unsigned int
	{
		DeleteStatus = GL_DELETE_STATUS,
		LinkStatus = GL_LINK_STATUS,
		ValidateStatus = GL_VALIDATE_STATUS,
		InfoLogLength = GL_INFO_LOG_LENGTH,
		AttachedShaders = GL_ATTACHED_SHADERS,
		ActiveAtomicCounterBuffers = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,
		ActiveAttributes = GL_ACTIVE_ATTRIBUTES,
		ActiveAttributeMaxLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
		ActiveUniforms = GL_ACTIVE_UNIFORMS,
		ActiveUniformBlocks = GL_ACTIVE_UNIFORM_BLOCKS,
		ActiveUniformBlockMaxNameLength = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,
		ActiveUniformMaxLength = GL_ACTIVE_UNIFORM_MAX_LENGTH,
		ComputeWorkGroupSize = GL_COMPUTE_WORK_GROUP_SIZE,
		ProgramBinaryLength = GL_PROGRAM_BINARY_LENGTH,
		TransformFeedbackBufferMode = GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
		TransformFeedbackVaryings = GL_TRANSFORM_FEEDBACK_VARYINGS,
		TransformFeedbackVaryingMaxLength = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
		GeometryVerticesOut = GL_GEOMETRY_VERTICES_OUT,
		GeometryInputType = GL_GEOMETRY_INPUT_TYPE,
		GeometryOutputType = GL_GEOMETRY_OUTPUT_TYPE,
	};
	int					GetProgramiv(ShaderProgramID program, ShaderProgramParameterName parameterName);
	bool				IsProgram(ShaderProgramID program);
	ShaderProgramID		CreateProgram();
	void				DeleteProgram(ShaderProgramID program);
	void				AttachShader(ShaderProgramID program, ShaderID shader);
	void				DetachShader(ShaderProgramID program, ShaderID shader);
	void				ValidateProgram(ShaderProgramID program);
	void				LinkProgram(ShaderProgramID program);
	void				UseProgram(ShaderProgramID program);
	void				GetProgramInfoLog(ShaderProgramID program, int maxLength, int & length, CStringBuffer infoLog);
	CStringBuffer		GetProgramInfoLog(ShaderProgramID program, int & length);



	//	Uniform
	typedef int UniformLocation;
	UniformLocation		GetUniformLocation(ShaderProgramID program, CString name);

	//	change names to UniformN, the specific function can be overloaded

	void	Uniform1f(UniformLocation location, VFloat v0);
	void	Uniform2f(UniformLocation location, VFloat v0, VFloat v1);
	void	Uniform3f(UniformLocation location, VFloat v0, VFloat v1, VFloat v2);
	void	Uniform4f(UniformLocation location, VFloat v0, VFloat v1, VFloat v2, VFloat v3);

	void	Uniform1i(UniformLocation location, VInt v0);
	void	Uniform2i(UniformLocation location, VInt v0, VInt v1);
	void	Uniform3i(UniformLocation location, VInt v0, VInt v1, VInt v2);
	void	Uniform4i(UniformLocation location, VInt v0, VInt v1, VInt v2, VInt v3);

	void	Uniform1ui(UniformLocation location, VUInt v0);
	void	Uniform2ui(UniformLocation location, VUInt v0, VUInt v1);
	void	Uniform3ui(UniformLocation location, VUInt v0, VUInt v1, VUInt v2);
	void	Uniform4ui(UniformLocation location, VUInt v0, VUInt v1, VUInt v2, VUInt v3);

	void	Uniform1fv(UniformLocation location, Size count, VFloatCData value);
	void	Uniform2fv(UniformLocation location, Size count, VFloatCData value);
	void	Uniform3fv(UniformLocation location, Size count, VFloatCData value);
	void	Uniform4fv(UniformLocation location, Size count, VFloatCData value);

	void	Uniform1iv(UniformLocation location, Size count, VIntCData value);
	void	Uniform2iv(UniformLocation location, Size count, VIntCData value);
	void	Uniform3iv(UniformLocation location, Size count, VIntCData value);
	void	Uniform4iv(UniformLocation location, Size count, VIntCData value);

	void	Uniform1uiv(UniformLocation location, Size count, VUIntCData value);
	void	Uniform2uiv(UniformLocation location, Size count, VUIntCData value);
	void	Uniform3uiv(UniformLocation location, Size count, VUIntCData value);
	void	Uniform4uiv(UniformLocation location, Size count, VUIntCData value);

	void	UniformMatrix2fv(UniformLocation location, Size count, bool transpose, VFloatCData value);
	void	UniformMatrix3fv(UniformLocation location, Size count, bool transpose, VFloatCData value);
	void	UniformMatrix4fv(UniformLocation location, Size count, bool transpose, VFloatCData value);
	void	UniformMatrix2x3fv(UniformLocation location, Size count, bool transpose, VFloatCData value);
	void	UniformMatrix3x2fv(UniformLocation location, Size count, bool transpose, VFloatCData value);
	void	UniformMatrix2x4fv(UniformLocation location, Size count, bool transpose, VFloatCData value);
	void	UniformMatrix4x2fv(UniformLocation location, Size count, bool transpose, VFloatCData value);
	void	UniformMatrix3x4fv(UniformLocation location, Size count, bool transpose, VFloatCData value);
	void	UniformMatrix4x3fv(UniformLocation location, Size count, bool transpose, VFloatCData value);

	void	GetUniformfv(ShaderProgramID program, UniformLocation location, VFloatData params);
	void	GetUniformiv(ShaderProgramID program, UniformLocation location, VIntData params);
	void	GetUniformuiv(ShaderProgramID program, UniformLocation location, VUIntData params);
//	void	GetUniformdv(ShaderProgramID program, UniformLocation location, GLdouble *params);
//	void	GetnUniformfv(ShaderProgramID program, UniformLocation location, Size bufSize, GLfloat *params);
//	void	GetnUniformiv(ShaderProgramID program, UniformLocation location, Size bufSize, GLint *params);
//	void	GetnUniformuiv(ShaderProgramID program, UniformLocation location, Size bufSize, GLuint *params);
//	void	GetnUniformdv(ShaderProgramID program, UniformLocation location, Size bufSize, GLdouble *params);





	//	VertexArray
	typedef unsigned int VertexArrayID;
	bool			IsVertexArray(VertexArrayID array);
	void			GenVertexArrays(Size n, VertexArrayID arrays[]);
	void			DeleteVertexArrays(Size n, VertexArrayID arrays[]);
	VertexArrayID	CreateVertexArray();
	void			DeleteVertexArray(VertexArrayID array);
	void			BindVertexArray(VertexArrayID array);



	//	Attribute
	typedef unsigned int AttributeID;
	void	EnableVertexAttribArray(AttributeID index);
	void	DisableVertexAttribArray(AttributeID index);
	enum class AttributeType : unsigned int
	{
		HalfFloat = GL_HALF_FLOAT,
		Float = GL_FLOAT,
		Double = GL_DOUBLE,
		Fixed = GL_FIXED,
		Int2101010Rev = GL_INT_2_10_10_10_REV,
		UnsignedInt2101010Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
		UnsignedInt10f11f11fRev = GL_UNSIGNED_INT_10F_11F_11F_REV,
		Byte = GL_BYTE,
		UnsignedByte = GL_UNSIGNED_BYTE,
		Short = GL_SHORT,
		UnsignedShort = GL_UNSIGNED_SHORT,
		Int = GL_INT,
		UnsignedInt = GL_UNSIGNED_INT,
	};
	enum class AttributeIntType : unsigned int
	{
		Byte = GL_BYTE,
		UnsignedByte = GL_UNSIGNED_BYTE,
		Short = GL_SHORT,
		UnsignedShort = GL_UNSIGNED_SHORT,
		Int = GL_INT,
		UnsignedInt = GL_UNSIGNED_INT,
	};
	void	VertexAttribPointer(AttributeID index, Size size, AttributeType type, bool normalized, Size stride, VData data);
	void	VertexAttribIPointer(AttributeID index, Size size, AttributeIntType type, Size stride, VData data);
	typedef unsigned int AttributeDivisor;
	void	VertexAttribDivisor(AttributeID index, AttributeDivisor divisor);



	//	Drawing
	enum class DrawMode : unsigned int
	{
		Points = GL_POINTS,
		LineStrip = GL_LINE_STRIP,
		LineLoop = GL_LINE_LOOP,
		Lines = GL_LINES,
		LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
		LinesAdjacency = GL_LINES_ADJACENCY,
		TriangleStrip = GL_TRIANGLE_STRIP,
		TriangleFan = GL_TRIANGLE_FAN,
		Triangles = GL_TRIANGLES,
		TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
		TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
		Patches = GL_PATCHES,
	};
	void	DrawArrays(DrawMode mode, unsigned int first, Size count);
	void	DrawArraysInstanced(DrawMode mode, unsigned int first, Size count, Size instancecount);
	enum class DrawIndexType : unsigned int
	{
		UnsignedByte = GL_UNSIGNED_BYTE,
		UnsignedShort = GL_UNSIGNED_SHORT,
		UnsignedInt = GL_UNSIGNED_INT,
	};
	void	DrawElements(DrawMode mode, Size count, DrawIndexType type, VData indices);
	void	DrawElementsInstanced(DrawMode mode, Size count, DrawIndexType type, VData indices, Size instancecount);
	void	DrawElements(DrawMode mode, Size count, DrawIndexType type);
	void	DrawElementsInstanced(DrawMode mode, Size count, DrawIndexType type, Size instancecount);

	//	Buffer
	typedef unsigned int BufferID;
	bool	IsBuffer(BufferID buffer);
	void	GenBuffers(Size n, BufferID buffers[]);
	void	DeleteBuffers(Size n, const BufferID buffers[]);
	BufferID	CreateBuffer();
	void		DeleteBuffer(BufferID buffer);
	enum class BufferTarget : unsigned int
	{
		ArrayBuffer = GL_ARRAY_BUFFER,
		AtomicCounterBuffer = GL_ATOMIC_COUNTER_BUFFER,
		CopyReadBuffer = GL_COPY_READ_BUFFER,
		CopyWriteBuffer = GL_COPY_WRITE_BUFFER,
		DispatchIndirectBuffer = GL_DISPATCH_INDIRECT_BUFFER,
		DrawIndirectBuffer = GL_DRAW_INDIRECT_BUFFER,
		ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
		PixelPackBuffer = GL_PIXEL_PACK_BUFFER,
		PixelUnpackBuffer = GL_PIXEL_UNPACK_BUFFER,
		QueryBuffer = GL_QUERY_BUFFER,
		ShaderStorageBuffer = GL_SHADER_STORAGE_BUFFER,
		TextureBuffer = GL_TEXTURE_BUFFER,
		TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
		UniformBuffer = GL_UNIFORM_BUFFER,
	};
	enum class BufferDataUsage : unsigned int
	{
		StreamDraw = GL_STREAM_DRAW,
		StreamRead = GL_STREAM_READ,
		StreamCopy = GL_STREAM_COPY,
		StaticDraw = GL_STATIC_DRAW,
		StaticRead = GL_STATIC_READ,
		StaticCopy = GL_STATIC_COPY,
		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY,
	};
	void	BindBuffer(BufferTarget target, BufferID buffer);
	void	BufferData(BufferTarget target, Size size, VData data, BufferDataUsage usage);
};

#endif