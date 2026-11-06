#include "Test/Graph.hpp"



TestGraph::TestGraph()
	: UI::Control::Form()
	//, SliderGroupBox()
	//, SliderHori()
	//, SliderVert()
	, SliderArea()
	, GraphHori()
	, GraphVert()
{
//	SliderGroupBox.Anchor.X.AnchorBoth(0, 200);
//	SliderGroupBox.Anchor.Y.AnchorBoth(0, 200);
//	float x = SliderGroupBox.Anchor.X.GetMaxDist();
//	float y = SliderGroupBox.Anchor.Y.GetMaxDist();
//
//	SliderHori.Anchor.Y.AnchorMin(0, 25);
//	SliderVert.Anchor.X.AnchorMin(0, 25);
//	SliderHori.Anchor.X.AnchorBoth(SliderVert.Anchor.X.GetMinSize(), 0);
//	SliderVert.Anchor.Y.AnchorBoth(SliderHori.Anchor.Y.GetMinSize(), 0);
//	SliderArea.Anchor.X.AnchorBoth(SliderVert.Anchor.X.GetMinSize(), 0);
//	SliderArea.Anchor.Y.AnchorBoth(SliderHori.Anchor.Y.GetMinSize(), 0);
//	SliderHori.NubSize = VectorF2(10, 25);
//	SliderVert.NubSize = VectorF2(25, 10);
//	SliderArea.NubSize = VectorF2(10, 10);
//
//	SliderHori.ValueChangedFunc.Assign(this, &TestGraph::SliderHoriChange);
//	SliderVert.ValueChangedFunc.Assign(this, &TestGraph::SliderVertChange);
//	SliderArea.ValueChangedFunc.Assign(this, &TestGraph::SliderAreaChange);

	AnchorSize = VectorF2(400);

	SliderArea.NubSize = VectorF2(10);
	SliderArea.Anchor.X.AnchorBoth(0, 200);
	SliderArea.Anchor.Y.AnchorBoth(0, 200);
	float x = SliderArea.Anchor.X.GetMaxDist();
	float y = SliderArea.Anchor.Y.GetMaxDist();

	SliderArea.ValueChangedFunc.Assign(this, &TestGraph::SliderAreaChange);

	GraphHori.Anchor.X.AnchorMax(0, x);
	GraphHori.Anchor.Y.AnchorBoth(0, y);
	GraphHori.Center = 0.5f;
	GraphHori.Magnitude = 0.5f;

	GraphVert.Anchor.X.AnchorBoth(0, x);
	GraphVert.Anchor.Y.AnchorMax(0, y);
	GraphVert.Center = 0.5f;
	GraphVert.Magnitude = 0.5f;

	//ChildInsert(SliderGroupBox);
	//SliderGroupBox.ChildInsert(SliderHori);
	//SliderGroupBox.ChildInsert(SliderVert);
	//SliderGroupBox.ChildInsert(SliderArea);

	ChildInsert(SliderArea);
	ChildInsert(GraphHori);
	ChildInsert(GraphVert);
}



void TestGraph::SliderHoriChange(VectorF2 val)
{
	GraphHori.Values.NewValue(val.X);
}
void TestGraph::SliderVertChange(VectorF2 val)
{
	GraphVert.Values.NewValue(val.Y);
}
void TestGraph::SliderAreaChange(VectorF2 val)
{
	GraphHori.Values.NewValue(val.X);
	GraphVert.Values.NewValue(val.Y);
}
