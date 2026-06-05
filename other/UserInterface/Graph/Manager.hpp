#ifndef  UI_GRAPH_MANAGER_HPP
# define UI_GRAPH_MANAGER_HPP

# include "ShaderLayout.hpp"
# include "BufferLayout.hpp"
# include "BufferData.hpp"
# include "Buffer.hpp"

# include "Graphics/Shader/Base.hpp"

# include "Miscellaneous/Container/Binary.hpp"



class DirectoryInfo;

namespace UI
{

namespace Graph
{

struct ObjectData;

class Manager
{
	public:
	static Manager * CurrentPointer;
	static Manager & Current();
	static bool CheckCurrent();
	static void ClearCurrent();
	bool IsCurrent() const;
	void MakeCurrent();





	public:
	::Shader::Base				Shader;
	UI::Graph::ShaderLayout		ShaderLayout;

	UI::Graph::Buffer			Buffer;
	UI::Graph::BufferLayout		BufferLayout;

	Container::Binary<ObjectData*>			ObjectDatas;
	Container::Binary<Graph::BufferData>	Instances;

	public:
	~Manager();
	Manager();
	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	public:
	ObjectData *	PlaceObject();
	ObjectData *	CopyObject(const ObjectData * obj);
	// give these functions static Variants that return if no Current
	// else they do the stuff with current

	public:
	void	ChangeMedia(const DirectoryInfo & dir);

	private:
	bool	GraphicsExist;
	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	private:
	void	PlaceInstance(const ObjectData & obj);
	public:
	void	MakeInstances();

	public:
	void	Draw();
};

};

};

#endif