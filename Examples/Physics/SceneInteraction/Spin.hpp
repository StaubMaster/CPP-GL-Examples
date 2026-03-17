#ifndef  SCENE_INTERACTION_SPIN_HPP
# define SCENE_INTERACTION_SPIN_HPP

# include "SceneInteraction/Base.hpp"
# include "ValueType/Angle2D.hpp"

struct InteractionObjectSpin : public SceneInteractionBase
{
	Angle2D	Origin;
	Angle2D	Offset;

	InteractionObjectSpin();

	void Escape(SceneInteractionData & SceneData) override;

	void Start(SceneInteractionData & SceneData) override;
	void Update(SceneInteractionData & SceneData) override;

	void Show() override;
};

#endif