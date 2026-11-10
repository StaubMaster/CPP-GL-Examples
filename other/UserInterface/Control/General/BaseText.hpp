#ifndef  UI_CONTROL_GENERAL_BASE_TEXT_HPP
# define UI_CONTROL_GENERAL_BASE_TEXT_HPP

# include "Control/General/Base.hpp"

# include "Text/ObjectData.hpp"

namespace UI
{
namespace Control
{
class BaseText : public Base
{
	public:
	virtual ~BaseText() = default;
	BaseText();
	BaseText(const BaseText & other) = delete;
	BaseText & operator=(const BaseText & other) = delete;

	protected:
	Text::ObjectData	TextObjectData;

	public:
	std::string		GetText() const;
	void			SetText(std::string text);

	protected:
	UI::Text::Alignment		AlignmentX;
	UI::Text::Alignment		AlignmentY;
	public:
	void	AlignmentChangeX(UI::Text::Alignment alignment);
	void	AlignmentChangeY(UI::Text::Alignment alignment);
	private:	bool	AlignmentUpdateFlag = false;
	protected:	void	AlignmentUpdateRequest();
	private:	void	AlignmentUpdateResolve();
	private:	void	AlignmentUpdate();

	protected:
	//void	DepthUpdate() override;

	public:
	void	BoxUpdate() override;
	void	Update() override;
	public:
	void	DisplayPut() const override;
	void	DisplayShow() override;
	void	DisplayHide() override;
};
};
};

#endif