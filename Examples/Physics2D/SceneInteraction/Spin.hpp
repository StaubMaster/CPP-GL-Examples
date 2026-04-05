#ifndef  SCENE_INTERACTION_SPIN_HPP
# define SCENE_INTERACTION_SPIN_HPP

# include "SceneInteraction/Base.hpp"
# include "ValueType/Undex.hpp"
# include "ValueType/Angle.hpp"

struct InteractionObjectSpin : public SceneInteractionBase
{
	Undex	Object;
	Angle	Offset;

	Angle	Origin;
	Angle	Target;

	InteractionObjectSpin();

	void Escape(SceneInteractionData & SceneData) override;
	void Start(SceneInteractionData & SceneData) override;
	void End(SceneInteractionData & SceneData) override;
	void Change(SceneInteractionData & SceneData) override;
	void Update(SceneInteractionData & SceneData) override;

	void Show() override;
};

#endif