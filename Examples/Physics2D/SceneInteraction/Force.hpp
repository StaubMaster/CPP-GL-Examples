#ifndef  SCENE_INTERACTION_DRAG_HPP
# define SCENE_INTERACTION_DRAG_HPP

# include "SceneInteraction/Base.hpp"
# include "ValueType/Undex.hpp"
# include "ValueType/VectorF2.hpp"

struct InteractionObjectDrag : public SceneInteractionBase
{
	Undex	Object;
	VectorF2	Offset;

	VectorF2	Target;

	InteractionObjectDrag();

	void Escape(SceneInteractionData & SceneData) override;
	void End(SceneInteractionData & SceneData) override;
	void Start(SceneInteractionData & SceneData) override;
	void Change(SceneInteractionData & SceneData) override;
	void Update(SceneInteractionData & SceneData) override;

	void Show() override;
};

#endif