#ifndef  UI_TEXT_MANAGER_HPP
# define UI_TEXT_MANAGER_HPP

#include "Data.hpp"
#include "Buffer.hpp"
#include "ShaderLayout.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/Container/Array.hpp"
#include "Miscellaneous/Container/BlockLinkedList.hpp"

#include "Font/Font.hpp"
#include "Graphics/Texture/Array2D.hpp"



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

	UI::Text::Buffer		Buffer;
	UI::Text::Main_Layout	LayoutMain;
	UI::Text::Inst_Layout	LayoutInst;

	Container::Binary<UI::Text::ObjectData*>				ObjectDatas;
	Container::BlockLinkedList<1024, UI::Text::Inst_Data>	InstancesBlock;
	Container::Array<UI::Text::Inst_Data>					InstancesArray;

	Container::Array<VectorF2>	FontPalletMin;
	Container::Array<VectorF2>	FontPalletMax;

	unsigned int				TextArrayIdx;
	Container::Array<VectorF2>	TextBoundMin;
	Container::Array<VectorF2>	TextBoundMax;
	Container::Array<ColorF4>	TextColor;

	UI::Text::Font *	TextFont;
	Texture::Array2D	Pallet_Texture;



	public:
	~Manager();
	Manager();
	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	public:
	void	InitMedia(DirectoryInfo & media_dir);
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

	private:
	bool	TextureAssigned;
	void	TextureAssign();

	private:
	bool	BufferMainAttributesBound;
	bool	BufferInstAttributesBound;
	void	BufferMainAttributesBind();
	void	BufferInstAttributesBind();

	private:
	bool	BufferMainNewData;
	bool	BufferInstNewData;
	void	BufferMainUpdateData();
	void	BufferInstUpdateData();

	public:
	void	Draw();
};

};

};

#endif