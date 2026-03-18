#ifndef  SCENE_INTERACTION_BASE_HPP
# define SCENE_INTERACTION_BASE_HPP

# include "SceneInteraction/Data.hpp"
# include "Arrow2D/Object.hpp"

struct SceneInteractionBase
{
	virtual ~SceneInteractionBase();
	SceneInteractionBase();

	virtual void Escape(SceneInteractionData & SceneData) = 0;
	virtual void End(SceneInteractionData & SceneData) = 0;
	virtual void Start(SceneInteractionData & SceneData) = 0;
	virtual void Change(SceneInteractionData & SceneData) = 0;
	virtual void Update(SceneInteractionData & SceneData) = 0;

	Arrow2D::Object	Arrows;
	virtual void Show() = 0;
	void Hide();
};

#endif