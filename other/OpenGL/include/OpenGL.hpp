#ifndef  OPEN_GL_HPP
# define OPEN_GL_HPP

# include "../glad/glad.h"
# include <GLFW/glfw3.h>
# include "OpenGLEnums.hpp"

namespace GL
{
	//	General
	Error GetError();

	void	GetBooleanv(ParameterName pname, bool & data);
//	void	GetDoublev(ParameterName pname, double & data);
	void	GetFloatv(ParameterName pname, float & data);
	void	GetIntegerv(ParameterName pname, int & data);

	bool	GetBooleanv(ParameterName pname);
	float	GetFloatv(ParameterName pname);
	int		GetIntegerv(ParameterName pname);

	//	void	GetInteger64v(ParameterName pname, GLint64 & data);
//	void	GetBooleani_v(GLenum target, GLuint index, GLboolean & data);
//	void	GetIntegeri_v(GLenum target, GLuint index, GLint & data);
//	void	GetInteger64i_v(GLenum target, GLuint index, GLint64 & data);

	void	Enable(Capability cap);
	void	Disable(Capability cap);
	void	Enablei(Capability cap, unsigned int index);
	void	Disablei(Capability cap, unsigned int index);
	bool	IsEnabled(Capability cap);
	bool	IsEnabledi(Capability cap, unsigned int index);

	void	Clear(ClearMask mask);
	void	ClearColor(float red, float green, float blue, float alpha);

	void	CullFace(Side mode);
	void	FrontFace(FrontSide mode);

	void	DepthMask(bool flag);
	void	DepthFunc(Comparison func);
	void	DepthRange(float n, float f);	//	is actually double
	void	ClearDepth(float depth);		//	is actually double



	//	Shader
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
	bool			IsVertexArray(VertexArrayID array);
	void			GenVertexArrays(Size n, VertexArrayID arrays[]);
	void			DeleteVertexArrays(Size n, VertexArrayID arrays[]);
	VertexArrayID	CreateVertexArray();
	void			DeleteVertexArray(VertexArrayID array);
	void			BindVertexArray(VertexArrayID array);



	//	Attribute
	void	EnableVertexAttribArray(AttributeID index);
	void	DisableVertexAttribArray(AttributeID index);
	void	VertexAttribPointer(AttributeID index, Size size, AttributeType type, bool normalized, Size stride, VData data);
	void	VertexAttribIPointer(AttributeID index, Size size, AttributeIntType type, Size stride, VData data);
	void	VertexAttribDivisor(AttributeID index, AttributeDivisor divisor);



	//	Drawing
	void	DrawArrays(DrawMode mode, unsigned int first, Size count);
	void	DrawArraysInstanced(DrawMode mode, unsigned int first, Size count, Size instancecount);
	void	DrawElements(DrawMode mode, Size count, DrawIndexType type, VData indices);
	void	DrawElementsInstanced(DrawMode mode, Size count, DrawIndexType type, VData indices, Size instancecount);
	void	DrawElements(DrawMode mode, Size count, DrawIndexType type);
	void	DrawElementsInstanced(DrawMode mode, Size count, DrawIndexType type, Size instancecount);



	//	Buffer
	bool	IsBuffer(BufferID buffer);
	void	GenBuffers(Size n, BufferID buffers[]);
	void	DeleteBuffers(Size n, const BufferID buffers[]);
	BufferID	CreateBuffer();
	void		DeleteBuffer(BufferID buffer);
	void	BindBuffer(BufferTarget target, BufferID buffer);
	void	BufferData(BufferTarget target, Size size, VData data, BufferDataUsage usage);



	//	Texture
	bool	IsTexture(TextureID texture);
	void	GenTextures(Size n, TextureID textures[]);
	void	DeleteTextures(Size n, const TextureID textures[]);
	TextureID	CreateTexture();
	void		DeleteTexture(TextureID texture);
	void	BindTexture(TextureTarget target, TextureID texture);
	void	GenerateMipmap(TextureTarget target);

	void	TexImage1D(TextureTarget target, int level, TextureInternalFormat internalformat, Size width, int border, TextureFormat format, TextureType type, VData data);
	void	TexImage2D(TextureTarget target, int level, TextureInternalFormat internalformat, Size width, Size height, int border, TextureFormat format, TextureType type, VData data);
	void	TexImage3D(TextureTarget target, int level, TextureInternalFormat internalformat, Size width, Size height, Size depth, int border, TextureFormat format, TextureType type, VData data);

	void	TexSubImage1D(TextureTarget target, int level, int xoffset, Size width, TextureFormat format, TextureType type, VData data);
	void	TexSubImage2D(TextureTarget target, int level, int xoffset, int yoffset, Size width, Size height, TextureFormat format, TextureType type, VData data);
	void	TexSubImage3D(TextureTarget target, int level, int xoffset, int yoffset, int zoffset, Size width, Size height, Size depth, TextureFormat format, TextureType type, VData data);

	void	TexParameterf(TextureTarget target, TextureParameterName pname, VFloat param);
	void	TexParameteri(TextureTarget target, TextureParameterName pname, VInt param);
	void	TexParameterfv(TextureTarget target, TextureParameterName pname, VFloatCData params);
	void	TexParameteriv(TextureTarget target, TextureParameterName pname, VIntCData params);
	void	TexParameterIiv(TextureTarget target, TextureParameterName pname, VIntCData params);
	void	TexParameterIuiv(TextureTarget target, TextureParameterName pname, VUIntCData params);
};

#endif