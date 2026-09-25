#ifndef  SHADER_CODE_HPP
# define SHADER_CODE_HPP

//# include <exception>
//# include <string>
//# include <fstream>
//# include "OpenGL/openGL.h"
# include "Generics/Container/Array.hpp"
# include "FileInfo.hpp"
# include <string>

#include "OpenGLTypes.hpp"



class FileInfo;

namespace Shader
{
class Code
{
	private:
	public:
	GL::ShaderID	ID;
	GL::ShaderType	Type;
	FileInfo		File;



	public:
	~Code();
	Code();

	Code(const Shader::Code & other);
	Code & operator=(const Shader::Code & other);

	Code(const FileInfo & file);



	public:
	bool	Valid() const;
	void	Dispose();
	void	Compile();
	void	Attach(GL::ShaderID ProgramID) const;
	void	Detach(GL::ShaderID ProgramID) const;

	public:
	static bool		Valid(Container::Array<Shader::Code> & code);
	static void		Dispose(Container::Array<Shader::Code> & code);
	static void		Compile(Container::Array<Shader::Code> & code);
	static void		Attach(Container::Array<Shader::Code> & code, GL::ShaderID ProgramID);
	static void		Detach(Container::Array<Shader::Code> & code, GL::ShaderID ProgramID);

	private:
	static GL::ShaderType	ShaderTypeFromExtension(const FileInfo & file);



	public:
	void	LogInfo(bool self = true, bool log = false) const;
};
};

#endif