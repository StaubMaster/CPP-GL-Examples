#ifndef  SCENE_OBJECT_DISPLAY_MODE_HPP
# define SCENE_OBJECT_DISPLAY_MODE_HPP

struct SceneObject_DisplayMode
{
	enum class EIndicators
	{
		Show,
		Hide,
	};
	EIndicators		Indicators;
	void			IndicatorsCycle();

	enum class EObjects
	{
		Full,
		Wire,
		None,
	};
	EObjects	Objects;
	void		ObjectsCycle();
};

#endif