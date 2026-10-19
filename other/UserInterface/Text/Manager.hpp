#ifndef  UI_TEXT_MANAGER_HPP
# define UI_TEXT_MANAGER_HPP

# include "DataMain.hpp"
# include "DataInst.hpp"

# include "TextData.hpp"
# include "FontData.hpp"

# include "Layout/Uniform.hpp"
# include "Layout/AttributeMain.hpp"
# include "Layout/AttributeInst.hpp"

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
	::Shader::Base				Shader;
	UI::Text::LayoutUniform		ShaderLayout;

	VertexArray::MainInst				Buffer;
	UI::Text::LayoutAttributeMain		BufferLayoutMain;
	UI::Text::LayoutAttributeInst		BufferLayoutInst;

	Container::Binary<UI::Text::ObjectData*>				ObjectDatas;
	Container::BlockLinkedList<1024, UI::Text::DataInst>	InstancesBlock;
	Container::Array<UI::Text::DataInst>					InstancesArray;

	UI::Text::Font *			Font = nullptr;
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