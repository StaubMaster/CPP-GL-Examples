#ifndef  SCENE_INTERACTION_MOVE_HPP
# define SCENE_INTERACTION_MOVE_HPP

# include "SceneInteraction/Base.hpp"
# include "ValueType/Undex.hpp"
# include "ValueType/VectorF2.hpp"

struct InteractionObjectMove : public SceneInteractionBase
{
	Undex	Object;
	VectorF2	Offset;

	VectorF2	Origin;
	VectorF2	Target;

	InteractionObjectMove();

	void Escape(SceneInteractionData & SceneData) override;
	void End(SceneInteractionData & SceneData) override;
	void Start(SceneInteractionData & SceneData) override;
	void Change(SceneInteractionData & SceneData) override;
	void Update(SceneInteractionData & SceneData) override;

	void Show() override;
};

#endif