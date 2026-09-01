#include <iostream>
#include <sstream>
#include <exception>

#include "OpenGL.hpp"
#include "Debug.hpp"

#include "DirectoryInfo.hpp"

#include "Window.hpp"
#include "Context.hpp"

#include "Generics/Container/Array.hpp"

#define SHOW_MAIN_INFO

static const char * arg_or_null(int argc, char * argv[], int idx)
{
	if (idx < argc)
	{
		return argv[idx];
	}
	return nullptr;
}

static void init_DebugFile(const char * name)
{
	DirectoryInfo log_dir("./logs/");
	if (!log_dir.Exists())
	{
		log_dir.Create();
		// Create() creates this directory. no Parents. throws error if didnt work
		// CanCreate() checks if this directory can be created
		// TryCreate() trys to create this directory. return false if didnt work
		// CreateRecursive()
		// same with Delete ?
		// same with Files
		// make some of these part of FileSystemInfo
		// Create should recursively create by default
		// make the others CreateThis ?
		// when do I ever only want to create this current File, with no Parent diectorys ?
	}
	Debug::NewFileInDir(log_dir);

	if (name != nullptr)
	{
		Debug::Log << name << Debug::Done;
	}
	else
	{
		Debug::Log << "Unknown File Name" << Debug::Done;
	}
}

static Container::Array<FileInfo> main_args_to_FileInfo(int argc, char * argv[])
{
	argc--;
	if (argc <= 0)
	{
		return Container::Array<FileInfo>();
	}
	Container::Array<FileInfo> files(argc);
	for (int i = 0; i < argc; i++)
	{
		files[i] = FileInfo(argv[i]);
	}
	return files;
}

int main(int argc, char * argv[])
{
#ifdef SHOW_MAIN_INFO
	std::cout << "int main(\n";
	for (int i = 0; i < argc; i++)
	{
		std::cout << "  " << '"' << argv[i] << '"' << '\n';
	}
	std::cout << ")\n";
#endif

	int ret = -1;

	init_DebugFile(arg_or_null(argc, argv, 0));

	try
	{
		Container::Array<FileInfo> files = main_args_to_FileInfo(argc, argv);

		if (glfwInit() == 0)
		{
			throw "glfwInit() failed";
		}

		{
			Window window;
			window.Create();
			ContextBase::WindowPointer = &window;
			{
				Light3DContext context;
				context.Run();
			}
			window.Delete();
			ContextBase::WindowPointer = nullptr;
			ret = 0;
		}
	}
	catch (std::exception & ex)
	{
		Debug::Log << "Main Exception: " << ex.what() << Debug::Done;
		std::cerr << "Main Exception: " << ex.what() << '\n';
	}
	catch (const char * str)
	{
		Debug::Log << "Main Exception: " << str << Debug::Done;
		std::cerr << "Main Exception: " << str << '\n';
	}
	catch (...)
	{
		Debug::Log << "Main Exception: " << "Unknown Type" << Debug::Done;
		std::cerr << "Main Exception: " << "Unknown Type" << '\n';
	}
	glfwTerminate();

#ifdef SHOW_MAIN_INFO
	Debug::Log << "int main() return " << ret << Debug::Done;
	std::cout << "int main() return " << ret << '\n';
#endif

	return ret;
}
