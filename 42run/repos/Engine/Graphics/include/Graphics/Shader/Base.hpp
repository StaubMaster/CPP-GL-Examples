#ifndef  SHADER_BASE_HPP
# define SHADER_BASE_HPP

# include "OpenGLTypes.hpp"

# include "Graphics/Shader/Code.hpp"

# include "Generics/Container/Array.hpp"
# include "Generics/Container/Binary.hpp"

# include <string>

class FileInfo;

namespace Uniform { class Layout; };

namespace Shader
{
class Base
{
	private:
	GL::ShaderProgramID		ID = 0;

	private:
	Container::Array<Shader::Code>	Code;

	private: public:
	Uniform::Layout *	Layout = nullptr;



	public:
	virtual ~Base();
	Base() = default;
	Base(const Shader::Base & other) = default;
	Base & operator=(const Shader::Base & other) = default;



	public:
	static GL::ShaderID		Bound();
	static void				BindNone();

	public:
	bool	IsBound() const;
	void	Bind();



	public:
	bool	Validate() const;
	bool	Exists() const;
	void	Delete();
	void	Create();

	public:
	void	Change(const Container::Array<Shader::Code> & code);
	void	Change(const Container::Array<FileInfo> & files);
	void	Change(std::initializer_list<Shader::Code> code);
	void	Change(std::initializer_list<FileInfo> files);



	public:
	void	AssignLayout(Uniform::Layout & layout);
	void	AssignLayout(Uniform::Layout * layout);



	public:
	GL::UniformLocation		FindUniformLocation(const char * name) const;
	GL::BlockIndex			FindUniformBlockIndex(const char * name) const;

	public:
	void	BindUniformBlockIndex(GL::BlockIndex index, GL::BlockBinding binding);



	public:
	void	LogInfo(bool self = true, bool log = false) const;



	public:
	class ECompileLog : public std::exception
	{
		private:
		std::string		Log;
		std::string		Text;

		public:
		ECompileLog(const std::string log);

		public:
		const char * what() const throw();
	};
};
};

#endif