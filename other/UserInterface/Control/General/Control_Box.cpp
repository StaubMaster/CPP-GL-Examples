#include "Control/General/Control_Box.hpp"



float UI::Control_Box::MarginBox_Get_X_Min_Min() const { return (AnchorDist.Min.X               ) - AnchorMargin.Min.X; }
float UI::Control_Box::MarginBox_Get_X_Min_Max() const { return (AnchorDist.Min.X + AnchorSize.X) + AnchorMargin.Min.X; }
float UI::Control_Box::MarginBox_Get_X_Max_Min() const { return (AnchorDist.Max.X               ) - AnchorMargin.Max.X; }
float UI::Control_Box::MarginBox_Get_X_Max_Max() const { return (AnchorDist.Max.X + AnchorSize.X) + AnchorMargin.Max.X; }
float UI::Control_Box::MarginBox_Get_Y_Min_Min() const { return (AnchorDist.Min.Y               ) - AnchorMargin.Min.Y; }
float UI::Control_Box::MarginBox_Get_Y_Min_Max() const { return (AnchorDist.Min.Y + AnchorSize.Y) + AnchorMargin.Min.Y; }
float UI::Control_Box::MarginBox_Get_Y_Max_Min() const { return (AnchorDist.Max.Y               ) - AnchorMargin.Max.Y; }
float UI::Control_Box::MarginBox_Get_Y_Max_Max() const { return (AnchorDist.Max.Y + AnchorSize.Y) + AnchorMargin.Max.Y; }

void UI::Control_Box::MarginBox_Set_X_Min_Min(float val) { AnchorDist.Min.X = (val + AnchorMargin.Min.X)               ; }
void UI::Control_Box::MarginBox_Set_X_Min_Max(float val) { AnchorDist.Min.X = (val - AnchorMargin.Min.X) - AnchorSize.X; }
void UI::Control_Box::MarginBox_Set_X_Max_Min(float val) { AnchorDist.Max.X = (val + AnchorMargin.Max.X)               ; }
void UI::Control_Box::MarginBox_Set_X_Max_Max(float val) { AnchorDist.Max.X = (val - AnchorMargin.Max.X) - AnchorSize.X; }
void UI::Control_Box::MarginBox_Set_Y_Min_Min(float val) { AnchorDist.Min.Y = (val + AnchorMargin.Min.Y)               ; }
void UI::Control_Box::MarginBox_Set_Y_Min_Max(float val) { AnchorDist.Min.Y = (val - AnchorMargin.Min.Y) - AnchorSize.Y; }
void UI::Control_Box::MarginBox_Set_Y_Max_Min(float val) { AnchorDist.Max.Y = (val + AnchorMargin.Max.Y)               ; }
void UI::Control_Box::MarginBox_Set_Y_Max_Max(float val) { AnchorDist.Max.Y = (val - AnchorMargin.Max.Y) - AnchorSize.Y; }

static float sMarginBox_Get_X_Min_Max(const UI::Control_Box * other)
{
	if (other != nullptr)
		return other -> MarginBox_Get_X_Min_Max();
	return 0.0f;
}
static float sMarginBox_Get_X_Max_Max(const UI::Control_Box * other)
{
	if (other != nullptr)
		return other -> MarginBox_Get_X_Max_Max();
	return 0.0f;
}
static float sMarginBox_Get_Y_Min_Max(const UI::Control_Box * other)
{
	if (other != nullptr)
		return other -> MarginBox_Get_Y_Min_Max();
	return 0.0f;
}
static float sMarginBox_Get_Y_Max_Max(const UI::Control_Box * other)
{
	if (other != nullptr)
		return other -> MarginBox_Get_Y_Max_Max();
	return 0.0f;
}

#include "AnchorEnum.hpp"

void UI::Control_Box::Make_Anchor_X_Min(const Control_Box * other)
{
	Anchor.X.Anchor = AnchorType::Min;
	MarginBox_Set_X_Min_Min(sMarginBox_Get_X_Min_Max(other));
}
void UI::Control_Box::Make_Anchor_X_Min(const Control_Box * other, float size)
{
	Anchor.X.Anchor = AnchorType::Min;
	MarginBox_Set_X_Min_Min(sMarginBox_Get_X_Min_Max(other));
	AnchorSize.X = size;
}
void UI::Control_Box::Make_Anchor_X_Max(const Control_Box * other)
{
	Anchor.X.Anchor = AnchorType::Max;
	MarginBox_Set_X_Max_Min(sMarginBox_Get_X_Max_Max(other));
}
void UI::Control_Box::Make_Anchor_X_Max(const Control_Box * other, float size)
{
	Anchor.X.Anchor = AnchorType::Max;
	MarginBox_Set_X_Max_Min(sMarginBox_Get_X_Max_Max(other));
	AnchorSize.X = size;
}
void UI::Control_Box::Make_Anchor_X_Both(const Control_Box * other_min, const Control_Box * other_max)
{
	Anchor.X.Anchor = AnchorType::Both;
	MarginBox_Set_X_Min_Min(sMarginBox_Get_X_Min_Max(other_min));
	MarginBox_Set_X_Max_Min(sMarginBox_Get_X_Max_Max(other_max));
}

void UI::Control_Box::Make_Anchor_Y_Min(const Control_Box * other)
{
	Anchor.Y.Anchor = AnchorType::Min;
	MarginBox_Set_Y_Min_Min(sMarginBox_Get_Y_Min_Max(other));
}
void UI::Control_Box::Make_Anchor_Y_Min(const Control_Box * other, float size)
{
	Anchor.Y.Anchor = AnchorType::Min;
	MarginBox_Set_Y_Min_Min(sMarginBox_Get_Y_Min_Max(other));
	AnchorSize.Y = size;
}
void UI::Control_Box::Make_Anchor_Y_Max(const Control_Box * other)
{
	Anchor.Y.Anchor = AnchorType::Max;
	MarginBox_Set_Y_Max_Min(sMarginBox_Get_Y_Max_Max(other));
}
void UI::Control_Box::Make_Anchor_Y_Max(const Control_Box * other, float size)
{
	Anchor.Y.Anchor = AnchorType::Max;
	MarginBox_Set_Y_Max_Min(sMarginBox_Get_Y_Max_Max(other));
	AnchorSize.Y = size;
}
void UI::Control_Box::Make_Anchor_Y_Both(const Control_Box * other_min, const Control_Box * other_max)
{
	Anchor.Y.Anchor = AnchorType::Both;
	MarginBox_Set_Y_Min_Min(sMarginBox_Get_Y_Min_Max(other_min));
	MarginBox_Set_Y_Max_Min(sMarginBox_Get_Y_Max_Max(other_max));
}

void UI::Control_Box::AnchorUpdateRequest()
{
	AnchorUpdateIsRequested = true;
}
void UI::Control_Box::AnchorUpdate()
{
	if (!MetaIs()) { return; }
	Anchor.Update(MetaBoxContent().Size());
	AnchorUpdateIsRequested = false;
}



/*void UI::Control_Box::BoxUpdateRequest()
{
	BoxUpdateIsRequested = true;
}*/
/*void UI::Control_Box::BoxUpdate()
{
	if (Parent == nullptr) { return; }

	Anchor.UpdateO(Parent -> BoxContent());

//	Anchor.UpdateO(Parent -> BoxContent);
//	BoxDisplay = Anchor.ToInnerBox(Parent -> BoxContent);
//
//	BoxBoarder.Min = BoxDisplay.Min + AnchorBoarder.Min;
//	BoxBoarder.Max = BoxDisplay.Max - AnchorBoarder.Max;
//
//	BoxContent.Min = BoxBoarder.Min + AnchorPadding.Min;
//	BoxContent.Max = BoxBoarder.Max - AnchorPadding.Max;

	BoxUpdateIsRequested = false;
}*/

BoxF2 UI::Control_Box::BoxDisplay() const
{
	if (!MetaIs()) { return BoxF2(); }
	BoxF2 box = MetaBoxContent(); //MetaBoxBoarder() ?
	return BoxF2(
		box.Min + AnchorDist.Min,
		box.Max - AnchorDist.Max
	);
}
BoxF2 UI::Control_Box::BoxBoarder() const
{
	if (!MetaIs()) { return BoxF2(); }
	BoxF2 box = BoxDisplay();
	return BoxF2(
		box.Min + AnchorBoarder.Min,
		box.Max - AnchorBoarder.Max
	);
}
BoxF2 UI::Control_Box::BoxContent() const
{
	if (!MetaIs()) { return BoxF2(); }
	BoxF2 box = BoxBoarder();
	return BoxF2(
		box.Min + AnchorPadding.Min,
		box.Max - AnchorPadding.Max
	);
}



void UI::Control_Box::AutoAnchorUpdateRequest()
{
	AutoAnchorUpdateIsRequested = true;
}
void UI::Control_Box::AutoAnchorUpdate()
{
	//if (!IsVisible()) { return; } // why is this check here ?

	switch (AutoAnchorXType)
	{
		case EAutoAnchorType::None: break;
		default: break;
	}

	switch (AutoAnchorYType)
	{
		case EAutoAnchorType::None: break;
		case EAutoAnchorType::StackMin:		AutoAnchorUpdate_Y_StackMin(); break;
		//case EAutoAnchorType::StackMinFit:	AutoAnchorUpdate_Y_StackMinFit(); break;
		default: break;
	}

	AutoAnchorUpdateIsRequested = false;
}



UI::Control_Box::Control_Box()
	: Anchor(
			AnchorSize,
			AnchorDist,
			//AnchorMargin,
			//AnchorBoarder,
			//AnchorPadding,
			AnchorNormal
		)
{
	AnchorSize = VectorF2(0, 0);
	AnchorDist = BoxF2(VectorF2(0, 0), VectorF2(0, 0));
	AnchorNormal = VectorF2(0, 0);

	float margin = 2.5f;
	float boarder = 2.0f;
	float padding = 2.5f;

	AnchorMargin = BoxF2(VectorF2(margin, margin), VectorF2(margin, margin));
	AnchorBoarder = BoxF2(VectorF2(boarder, boarder), VectorF2(boarder, boarder));
	AnchorPadding = BoxF2(VectorF2(padding, padding), VectorF2(padding, padding));
}
