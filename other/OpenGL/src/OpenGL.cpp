#include "OpenGL.hpp"





int GL::GetShaderiv(ShaderID shader, ShaderParameterName parameterName)
{
	int param;
	glGetShaderiv(shader, (unsigned int)parameterName, &param);
	return param;
}
bool GL::IsShader(ShaderID shader) { return glIsShader(shader); }
GL::ShaderID GL::CreateShader(ShaderType type) { return glCreateShader((unsigned int)type); }
void GL::DeleteShader(ShaderID shader) { glDeleteShader(shader); }
void GL::CompileShader(ShaderID shader) { glCompileShader(shader); }
void GL::ShaderSource(ShaderID shader, Size count, CString str[], int len[]) { glShaderSource(shader, count, str, len); }
void GL::ShaderSource(ShaderID shader, Size count, CString str[]) { glShaderSource(shader, count, str, NULL); }
void GL::ShaderSource(ShaderID shader, CString str) { glShaderSource(shader, 1, &str, NULL); }
void GL::GetShaderInfoLog(ShaderID shader, Size maxLength, int & length, CStringBuffer infoLog)
{
	glGetShaderInfoLog(shader, maxLength, &length, infoLog);
}
GL::CStringBuffer GL::GetShaderInfoLog(ShaderID shader, int & length)
{
	length = GetShaderiv(shader, ShaderParameterName::InfoLogLength);
	CStringBuffer str = new char[length];
	GetShaderInfoLog(shader, length, length, str);
	return str;
}





int GL::GetProgramiv(ShaderProgramID shader, ShaderProgramParameterName parameterName)
{
	int param;
	glGetProgramiv(shader, (unsigned int)parameterName, &param);
	return param;
}
bool GL::IsProgram(ShaderProgramID program) { return glIsProgram(program); }
GL::ShaderProgramID GL::CreateProgram() { return glCreateProgram(); }
void GL::DeleteProgram(ShaderProgramID program) { glDeleteProgram(program); }
void GL::AttachShader(ShaderProgramID program, ShaderID shader) { glAttachShader(program, shader); }
void GL::DetachShader(ShaderProgramID program, ShaderID shader) { glDetachShader(program, shader); }
void GL::ValidateProgram(ShaderProgramID program) { glValidateProgram(program); }
void GL::LinkProgram(ShaderProgramID program) { glLinkProgram(program); }
void GL::UseProgram(ShaderProgramID program) { glUseProgram(program); }
void GL::GetProgramInfoLog(ShaderProgramID program, int maxLength, int & length, CStringBuffer infoLog)
{
	glGetProgramInfoLog(program, maxLength, &length, infoLog);
}
GL::CStringBuffer GL::GetProgramInfoLog(ShaderProgramID program, int & length)
{
	length = GetProgramiv(program, ShaderProgramParameterName::InfoLogLength);
	CStringBuffer str = new char[length];
	GetProgramInfoLog(program, length, length, str);
	return str;
}





GL::UniformLocation GL::GetUniformLocation(ShaderProgramID program, CString name) { return glGetUniformLocation(program, name); }

void GL::Uniform1f(UniformLocation location, VFloat v0) { glUniform1f(location, v0); }
void GL::Uniform2f(UniformLocation location, VFloat v0, VFloat v1) { glUniform2f(location, v0, v1); }
void GL::Uniform3f(UniformLocation location, VFloat v0, VFloat v1, VFloat v2) { glUniform3f(location, v0, v1, v2); }
void GL::Uniform4f(UniformLocation location, VFloat v0, VFloat v1, VFloat v2, VFloat v3) { glUniform4f(location, v0, v1, v2, v3); }

void GL::Uniform1i(UniformLocation location, VInt v0) { glUniform1i(location, v0); }
void GL::Uniform2i(UniformLocation location, VInt v0, VInt v1) { glUniform2i(location, v0, v1); }
void GL::Uniform3i(UniformLocation location, VInt v0, VInt v1, VInt v2) { glUniform3i(location, v0, v1, v2); }
void GL::Uniform4i(UniformLocation location, VInt v0, VInt v1, VInt v2, VInt v3) { glUniform4i(location, v0, v1, v2, v3); }

void GL::Uniform1ui(UniformLocation location, VUInt v0) { glUniform1ui(location, v0); }
void GL::Uniform2ui(UniformLocation location, VUInt v0, VUInt v1) { glUniform2ui(location, v0, v1); }
void GL::Uniform3ui(UniformLocation location, VUInt v0, VUInt v1, VUInt v2) { glUniform3ui(location, v0, v1, v2); }
void GL::Uniform4ui(UniformLocation location, VUInt v0, VUInt v1, VUInt v2, VUInt v3) { glUniform4ui(location, v0, v1, v2, v3); }

void GL::Uniform1fv(UniformLocation location, Size count, VFloatCData value) { glUniform1fv(location, count, value); }
void GL::Uniform2fv(UniformLocation location, Size count, VFloatCData value) { glUniform2fv(location, count, value); }
void GL::Uniform3fv(UniformLocation location, Size count, VFloatCData value) { glUniform3fv(location, count, value); }
void GL::Uniform4fv(UniformLocation location, Size count, VFloatCData value) { glUniform4fv(location, count, value); }

void GL::Uniform1iv(UniformLocation location, Size count, VIntCData value) { glUniform1iv(location, count, value); }
void GL::Uniform2iv(UniformLocation location, Size count, VIntCData value) { glUniform2iv(location, count, value); }
void GL::Uniform3iv(UniformLocation location, Size count, VIntCData value) { glUniform3iv(location, count, value); }
void GL::Uniform4iv(UniformLocation location, Size count, VIntCData value) { glUniform4iv(location, count, value); }

void GL::Uniform1uiv(UniformLocation location, Size count, VUIntCData value) { glUniform1uiv(location, count, value); }
void GL::Uniform2uiv(UniformLocation location, Size count, VUIntCData value) { glUniform2uiv(location, count, value); }
void GL::Uniform3uiv(UniformLocation location, Size count, VUIntCData value) { glUniform3uiv(location, count, value); }
void GL::Uniform4uiv(UniformLocation location, Size count, VUIntCData value) { glUniform4uiv(location, count, value); }

void GL::UniformMatrix2fv(UniformLocation location, Size count, bool transpose, VFloatCData value) { glUniformMatrix2fv(location, count, transpose, value); }
void GL::UniformMatrix3fv(UniformLocation location, Size count, bool transpose, VFloatCData value) { glUniformMatrix3fv(location, count, transpose, value); }
void GL::UniformMatrix4fv(UniformLocation location, Size count, bool transpose, VFloatCData value) { glUniformMatrix4fv(location, count, transpose, value); }
void GL::UniformMatrix2x3fv(UniformLocation location, Size count, bool transpose, VFloatCData value) { glUniformMatrix2x3fv(location, count, transpose, value); }
void GL::UniformMatrix3x2fv(UniformLocation location, Size count, bool transpose, VFloatCData value) { glUniformMatrix3x2fv(location, count, transpose, value); }
void GL::UniformMatrix2x4fv(UniformLocation location, Size count, bool transpose, VFloatCData value) { glUniformMatrix2x4fv(location, count, transpose, value); }
void GL::UniformMatrix4x2fv(UniformLocation location, Size count, bool transpose, VFloatCData value) { glUniformMatrix4x2fv(location, count, transpose, value); }
void GL::UniformMatrix3x4fv(UniformLocation location, Size count, bool transpose, VFloatCData value) { glUniformMatrix3x4fv(location, count, transpose, value); }
void GL::UniformMatrix4x3fv(UniformLocation location, Size count, bool transpose, VFloatCData value) { glUniformMatrix4x3fv(location, count, transpose, value); }

void GL::GetUniformfv(ShaderProgramID program, UniformLocation location, VFloatData params) { glGetUniformfv(program, location, params); }
void GL::GetUniformiv(ShaderProgramID program, UniformLocation location, VIntData params) { glGetUniformiv(program, location, params); }
void GL::GetUniformuiv(ShaderProgramID program, UniformLocation location, VUIntData params) { glGetUniformuiv(program, location, params); }





bool GL::IsVertexArray(VertexArrayID array) { return glIsVertexArray(array); }
void GL::GenVertexArrays(Size n, VertexArrayID arrays[]) { glGenVertexArrays(n, arrays); }
void GL::DeleteVertexArrays(Size n, VertexArrayID arrays[]) { glDeleteVertexArrays(n, arrays); }
GL::VertexArrayID GL::CreateVertexArray() { VertexArrayID array; glGenVertexArrays(1, &array); return array; }
void GL::DeleteVertexArray(VertexArrayID array) { DeleteVertexArrays(1, &array); }
void GL::BindVertexArray(VertexArrayID array) { glBindVertexArray(array); }





void GL::EnableVertexAttribArray(AttributeID index) { glEnableVertexAttribArray(index); }
void GL::DisableVertexAttribArray(AttributeID index) { glDisableVertexAttribArray(index); }
void GL::VertexAttribPointer(AttributeID index, Size size, AttributeType type, bool normalized, Size stride, VData data) { glVertexAttribPointer(index, size, (unsigned int)type, normalized, stride, data); }
void GL::VertexAttribIPointer(AttributeID index, Size size, AttributeIntType type, Size stride, VData data) { glVertexAttribIPointer(index, size, (unsigned int)type, stride, data); }
void GL::VertexAttribDivisor(AttributeID index, AttributeDivisor divisor) { glVertexAttribDivisor(index, divisor); }






void GL::DrawArrays(DrawMode mode, unsigned int first, Size count) { glDrawArrays((unsigned int)mode, first, count); }
void GL::DrawArraysInstanced(DrawMode mode, unsigned int first, Size count, Size instancecount) { glDrawArraysInstanced((unsigned int)mode, first, count, instancecount); }
void GL::DrawElements(DrawMode mode, Size count, DrawIndexType type, VData indices) { glDrawElements((unsigned int)mode, count, (unsigned int)type, indices); }
void GL::DrawElementsInstanced(DrawMode mode, Size count, DrawIndexType type, VData indices, Size instancecount) { glDrawElementsInstanced((unsigned int)mode, count, (unsigned int)type, indices, instancecount); }
void GL::DrawElements(DrawMode mode, Size count, DrawIndexType type) { DrawElements(mode, count, type, NULL); }
void GL::DrawElementsInstanced(DrawMode mode, Size count, DrawIndexType type, Size instancecount) { DrawElementsInstanced(mode, count, type, NULL, instancecount); }





bool GL::IsBuffer(BufferID buffer) { return glIsBuffer(buffer); }
void GL::GenBuffers(Size n, BufferID buffers[]) { glGenBuffers(n, buffers); }
void GL::DeleteBuffers(Size n, const BufferID buffers[]) { glDeleteBuffers(n, buffers); }
GL::BufferID GL::CreateBuffer() { BufferID buffer; GenBuffers(1, &buffer); return buffer; }
void GL::DeleteBuffer(BufferID buffer) { DeleteBuffers(1, &buffer); }
void GL::BindBuffer(BufferTarget target, BufferID buffer) { glBindBuffer((unsigned int)target, buffer); }
void GL::BufferData(BufferTarget target, Size size, VData data, BufferDataUsage usage) { glBufferData((unsigned int)target, size, data, (unsigned int)usage); }
