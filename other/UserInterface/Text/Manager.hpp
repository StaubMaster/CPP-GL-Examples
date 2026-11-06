#ifndef  UI_TEXT_MANAGER_HPP
# define UI_TEXT_MANAGER_HPP

# include "Graphics/Main/Data.hpp"
# include "Graphics/Inst/Data.hpp"

# include "Graphics/Main/Layout.hpp"
# include "Graphics/Inst/Layout.hpp"
# include "Graphics/Layout.hpp"

# include "Graphics/Shader/Base.hpp"
# include "Graphics/VertexArray/MainInst.hpp"
# include "Graphics/Buffer/Array.hpp"

# include "Graphics/TextData.hpp"
# include "Graphics/FontData.hpp"

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
	::Shader::Base		Shader;
	UI::Text::Layout	ShaderLayout;

	VertexArray::MainInst		Buffer;
	UI::Text::Main::Layout		BufferLayoutMain;
	UI::Text::Inst::Layout		BufferLayoutInst;

	Container::Binary<UI::Text::ObjectData *>				ObjectDatas;

	Container::BlockLinkedList<1024, UI::Text::Inst::Data>	InstancesBlock;
	Container::Array<UI::Text::Inst::Data>					InstancesArray;

	UI::Text::Font *			Font = nullptr;
	Texture::Array2D			FontTexture;

	// these are where all the Characters are in the Font
	GL::BlockBinding			FontBinding = 0;
	FontBufferData				FontData;
	::Buffer::Uniform			FontBuffer;

	// these are per Text Object (Position, Size, Bound, Color)
	GL::BlockBinding				TextsBinding = 1;
	unsigned int					TextsCount = 0;
	TextsBufferData					TextsData;
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
	void	InstancesShowTime();

	public:
	void	InstancesClear();
	void	InstancesMake();
	void	InstancesDone();
	void	InstancesPut(const ObjectData & obj);



	private:
	bool	GraphicsExist = false;
	public:
	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsInit();

	private:
	bool	TextureAssigned = false;
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