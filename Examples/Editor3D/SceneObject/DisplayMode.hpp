#ifndef  SCENE_OBJECT_DISPLAY_MODE_HPP
# define SCENE_OBJECT_DISPLAY_MODE_HPP

struct SceneObjectDisplayMode
{
	enum class EIndicators
	{
		Show,
		Hide,
	};
	EIndicators		Indicators;

	enum class EObjects
	{
		Full,
		Wire,
		None,
	};
	EObjects	Objects;
};

#endif