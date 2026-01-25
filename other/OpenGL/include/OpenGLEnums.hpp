#ifndef  OPEN_GL_ENUMS_HPP
# define OPEN_GL_ENUMS_HPP

# include "../glad/glad.h"
# include <GLFW/glfw3.h>
# include "OpenGLTypes.hpp"

namespace GL
{
	//	Shader
	enum class ShaderType : unsigned int
	{
		ComputeShader = GL_COMPUTE_SHADER,
		VertexShader = GL_VERTEX_SHADER,
		TessControlShader = GL_TESS_CONTROL_SHADER,
		TessEvaluationShade = GL_TESS_EVALUATION_SHADER,
		GeometryShader = GL_GEOMETRY_SHADER,
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



	//	Shader Program
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



	//	Attribute
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
	enum class DrawIndexType : unsigned int
	{
		UnsignedByte = GL_UNSIGNED_BYTE,
		UnsignedShort = GL_UNSIGNED_SHORT,
		UnsignedInt = GL_UNSIGNED_INT,
	};



	//	Buffer
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
};

#endif