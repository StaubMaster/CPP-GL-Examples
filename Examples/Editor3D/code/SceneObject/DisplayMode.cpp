#include "SceneObject/DisplayMode.hpp"

void SceneObject_DisplayMode::IndicatorsCycle()
{
	switch (Indicators)
	{
		case SceneObject_DisplayMode::EIndicators::Show: Indicators = SceneObject_DisplayMode::EIndicators::Hide; break;
		case SceneObject_DisplayMode::EIndicators::Hide: Indicators = SceneObject_DisplayMode::EIndicators::Show; break;
	}
}
void SceneObject_DisplayMode::ObjectsCycle()
{
	switch (Objects)
	{
		case SceneObject_DisplayMode::EObjects::Full: Objects = SceneObject_DisplayMode::EObjects::Wire; break;
		case SceneObject_DisplayMode::EObjects::Wire: Objects = SceneObject_DisplayMode::EObjects::None; break;
		case SceneObject_DisplayMode::EObjects::None: Objects = SceneObject_DisplayMode::EObjects::Full; break;
	}
}
