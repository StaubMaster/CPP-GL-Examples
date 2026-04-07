#ifndef  UI_TEXT_MANAGER_HPP
# define UI_TEXT_MANAGER_HPP

#include "Data.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/EntryContainer/Binary.hpp"

#include "Font/Font.hpp"
#include "Graphics/Texture/Array2D.hpp"



namespace UI
{

namespace Text
{
struct ObjectData;

class Manager
{
	static Manager * CurrentPointer;
	static Manager & Current();
	static bool CheckCurrent();
	static void ClearCurrent();
	bool IsCurrent() const;
	void MakeCurrent();





	public:
	UI::Text::Shader	Shader;
	UI::Text::Buffer	Buffer;

	Container::Binary<UI::Text::ObjectData*>	ObjectDatas;
	Container::Binary<UI::Text::Inst_Data>		Instances;

	Container::Binary<UI::Text::Main_Data>			Main_Data_Container;
	EntryContainer::Binary<UI::Text::Inst_Data>		Inst_Data_Container;

	UI::Text::Font *	TextFont;
	Texture::Array2D	Pallet_Texture;

	public:
	~Manager();
	Manager();
	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	public:
	ObjectData *	PlaceObject();
	ObjectData *	CopyObject(const ObjectData * obj);

	private:
	bool	GraphicsExist;
	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	private:
	bool	GraphicsNeedInit;
	bool	GraphicsNeedMain;
	private:
	void	GraphicsInit(); // Init Buffer Attributes
	void	GraphicsMain(); // put Main in Buffer
	void	GraphicsInst(); // put Inst in Buffer
	private:
	void	PlaceInstance(const ObjectData & obj);

	public:
	void	Draw();
};

};

};

#endif