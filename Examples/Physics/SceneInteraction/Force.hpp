#ifndef  SCENE_INTERACTION_FORCE_HPP
# define SCENE_INTERACTION_FORCE_HPP

# include "SceneInteraction/Base.hpp"
# include "ValueType/Angle2D.hpp"

# include "Physics2D/Collision.hpp"

/* lock
	the old Force could be Locked
	I dont see a reason why the others should be Lockable
	so I dont want it to be part of the Interactions
	so just have a key, that creats a Force Object based on this Interaction
	which does mostly the same but which works independent of other Interactions
	activating it should deactivate the current Force Interaction

	how to remove ?
	make it so pressing Home removes all Forces, that apply to an Object are removes
	so also allow mutliple Force things to be linked to the same Object
*/

struct InteractionObjectApplyForce : public SceneInteractionBase
{
	Point2D	Contact;

	InteractionObjectApplyForce();

	void Escape(SceneInteractionData & SceneData) override;

	void Start(SceneInteractionData & SceneData) override;
	void Update(SceneInteractionData & SceneData) override;

	void Show() override;
};

#endif