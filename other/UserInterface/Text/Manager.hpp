#ifndef  UI_TEXT_MANAGER_HPP
# define UI_TEXT_MANAGER_HPP

#include "Data.hpp"
#include "Buffer.hpp"
#include "Shader.hpp"

#include "Miscellaneous/Container/Binary.hpp"

#include "Font/Font.hpp"
#include "Graphics/Texture/Array2D.hpp"



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
	UI::Text::Shader	Shader;
	UI::Text::Buffer	Buffer;

	Container::Binary<UI::Text::ObjectData*>	ObjectDatas;
	Container::Binary<UI::Text::Inst_Data>		Instances;

	UI::Text::Font *	TextFont;
	Texture::Array2D	Pallet_Texture;



	public:
	~Manager();
	Manager();
	Manager(const Manager & other) = delete;
	Manager & operator=(const Manager & other) = delete;

	public:
	void	InitMedia(DirectoryInfo & media_dir);



	public:
	ObjectData *	MakeObject();
	ObjectData *	CopyObject(const ObjectData * obj);



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