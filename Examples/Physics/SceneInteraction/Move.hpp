#ifndef  SCENE_INTERACTION_MOVE_HPP
# define SCENE_INTERACTION_MOVE_HPP

# include "SceneInteraction/Base.hpp"
# include "ValueType/Point2D.hpp"

struct InteractionObjectMove : public SceneInteractionBase
{
	Point2D	Origin;
	Point2D	Offset;

	InteractionObjectMove();

	void Escape(SceneInteractionData & SceneData) override;

	void Start(SceneInteractionData & SceneData) override;
	void Update(SceneInteractionData & SceneData) override;

	void Show() override;
};

#endif