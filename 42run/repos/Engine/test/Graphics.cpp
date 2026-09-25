#include "Debug.hpp"
#include "DataShow.hpp"
#include <iostream>

#include "FileInfo.hpp"
#include "DirectoryInfo.hpp"

#include "Generics/Container/Base.hpp"
#include "Generics/Container/Dynamic.hpp"

#include "Graphics/Shader/Base.hpp"
#include "Graphics/Shader/Code.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "Window.hpp"
#include "OpenGL/openGL.h"

int main()
{
	//	Directory and Files should be able to create subdirectorys if it needs them
	Debug::NewFileInDir(DirectoryInfo("/logs"));
	{
		//	put a wrapper for this in OpenGL Namespace ?
		//	throw exception on error
		if (glfwInit() == 0)
		{
			std::cout << "GLFW Init Failed\n";
			return -1;
		}

		Window * win = new Window(480, 360);

		{
			DirectoryInfo shader_dir("../media/Shaders/");
			Shader::Base shader(
				Container::Base<Shader::Code>(
				(Shader::Code[])
					{
						Shader::Code(shader_dir.File("PH_Full.frag")),
						Shader::Code(shader_dir.File("PH_S3D.vert")),
					}, 2
				)
			);
			std::cout << "Shader Compiled" << ' ' << shader.IsCompiled() << '\n';
			shader.Compile();
			std::cout << "Shader Compiled" << ' ' << shader.IsCompiled() << '\n';

			std::cout << "Shader Bound" << ' ' << shader.IsBound() << '\n';
			shader.Bind();
			std::cout << "Shader Bound" << ' ' << shader.IsBound() << '\n';
			std::cout << '\n';

			Uniform::Trans3D uni_ViewTrans(Uniform::NameShader("View", shader));
			std::cout << "Shader Uniforms " << shader.Uniforms.Count() << '\n';
			for (unsigned int i = 0; i < shader.Uniforms.Count(); i++)
			{ std::cout << (shader.Uniforms[i] -> Name) << '\n'; }
			/*	this puts 4 Uniforms in Shader
					View
					View.Pos
					View.Pos
					View.Rot
				only need 1 ?
			*/
			std::cout << '\n';

			Trans3D	trans;
			std::cout << "####    " << "Uniform" << ' ' << "PutData" << "    ####" << '\n';
			uni_ViewTrans.PutData(trans);
			std::cout << '\n';

			std::cout << "####    " << "Multiform" << ' ' << "Find" << "    ####" << '\n';
			Container::Base<Shader::Base *> shaders(1);
			shaders[0] = &shader;
			Multiform::Trans3D multi_ViewTrans("View");
			multi_ViewTrans.FindUniforms(shaders);
			std::cout << "Uniforms " << multi_ViewTrans.Uniforms.Limit() << '\n';
			for (unsigned int i = 0; i < multi_ViewTrans.Uniforms.Limit(); i++)
			{ std::cout << (multi_ViewTrans.Uniforms[i] -> Name) << '\n'; }
			/*	Multiform has 1 Uniform
					View
			*/
			std::cout << '\n';

			std::cout << "####    " << "Multiform" << ' ' << "PutData" << "    ####" << '\n';
			multi_ViewTrans.ChangeData(trans);
			std::cout << '\n';

			std::cout << "####    " << "Multiform" << ' ' << "PutData" << "    ####" << '\n';
			Shader::Base::BindNone();
			multi_ViewTrans.ChangeData(trans);
			std::cout << '\n';

			std::cout << "####    " << "Shader" << ' ' << "Bind" << "    ####" << '\n';
			shader.Bind();
			std::cout << '\n';
		}

		delete win;
		glfwTerminate();
	}

	{
		Container::Base<int> container((int[]){ 1, 2, 3 }, 3);
		for (unsigned int i = 0; i < container.Count(); i++)
		{
			std::cout << container[i] << '\n';
		}
	}

	std::cout << "main return\n";
	return 0;
}