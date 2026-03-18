#ifndef  SCENE_INTERACTION_DRAG_HPP
# define SCENE_INTERACTION_DRAG_HPP

# include "SceneInteraction/Base.hpp"
# include "ValueType/Undex.hpp"
# include "ValueType/Point2D.hpp"

struct InteractionObjectDrag : public SceneInteractionBase
{
	Undex	Object;
	Point2D	Offset;

	Point2D	Target;

	InteractionObjectDrag();

	void Escape(SceneInteractionData & SceneData) override;
	void End(SceneInteractionData & SceneData) override;
	void Start(SceneInteractionData & SceneData) override;
	void Change(SceneInteractionData & SceneData) override;
	void Update(SceneInteractionData & SceneData) override;

	void Show() override;
};

#endif