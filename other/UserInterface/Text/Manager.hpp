#ifndef  UI_TEXT_MANAGER_HPP
# define UI_TEXT_MANAGER_HPP

# include "Data.hpp"
# include "Buffer.hpp"
# include "ShaderLayout.hpp"
# include "Graphics/Shader/Base.hpp"

# include "Graphics/VertexArray/MainInst.hpp"
# include "Graphics/Buffer/Array.hpp"

# include "Generics/Container/Binary.hpp"
# include "Generics/Container/Array.hpp"
# include "Generics/Container/BlockLinkedList.hpp"

# include "Font/Font.hpp"
# include "Graphics/Texture/Array2D.hpp"


# include "Graphics/Buffer/Uniform.hpp"


class DirectoryInfo;



namespace UI
{

namespace Text
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
	::Shader::Base			Shader;
	UI::Text::ShaderLayout	ShaderLayout;

	//UI::Text::Buffer		Buffer;
	VertexArray::MainInst		Buffer;
	UI::Text::Main_Layout		LayoutMain;
	UI::Text::Inst_Layout		LayoutInst;

	Container::Binary<UI::Text::ObjectData*>				ObjectDatas;
	Container::BlockLinkedList<1024, UI::Text::Inst_Data>	InstancesBlock;
	Container::Array<UI::Text::Inst_Data>					InstancesArray;

	UI::Text::Font *			Font;
	Texture::Array2D			FontTexture;
	Container::Binary<BoxF2>	FontPalletsList;
	::Buffer::Uniform			FontBuffer;

	Container::Binary<TextData>		TextsList;
	::Buffer::Uniform				TextsBuffer;



	public:
	~Manager();
	Manager();
	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	public:
	void	ChangeMedia(const DirectoryInfo & media_dir);
	void	InitFont();



	public:
	ObjectData *	MakeObject();
	ObjectData *	CopyObject(const ObjectData * obj);



	public:
	void	ShowInstancesTime();
	private:
	void	MakeObjectInstances(const ObjectData & obj);
	public:
	void	MakeInstances();



	private:
	bool	GraphicsExist;
	public:
	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsInit();

	private:
	bool	TextureAssigned;
	void	TextureAssign();

	private:
	void	BufferMainUpdateData();
	void	BufferInstUpdateData();

	public:
	void	Draw();
};

};

};

#endif