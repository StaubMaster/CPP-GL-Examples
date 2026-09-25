#include "Player.hpp"



#include <math.h>
#include <iostream>

void Player::MakeDefault()
{
	Multiplier = 1.0f;
	TotalDistance = 0.0f;

	Box.Min = VectorF3(-4,  0, -4);
	Box.Max = VectorF3(+4, 20, +4);

	Speed = 4.0f;
	TileDistance = 0.0f;
	JumpImpulse = 5.0f;
	JumpSpeed = 0.0f;
	Gravity = 0.25f;
	Height = 0.0f;

	Change.MakeDefault();

	/* Calculate Jump Parabola
		f (x) : Height
		f'(x) : JumpSpeed
		f"(x) : Gravity
		f (x) = 1*a*x^2 + 1*b*x^1 + 1*c*x^0
		f'(x) = 2*a*x^1 + 1*b*x^0
		f"(x) = 2*a*x^0
	*/
	/* Find
		f(x) = 0	x1 = 0; find x2
		f'(x) = 0	find x
	*/
	/* Known
		f(0) = 0
		f'(0) = JumpImpulse*Speed ?
		f"(x) = -Gravity
	*/
	/*	f"(x) = 2*a*x^0 = -Gravity
				2*a = -Gravity
				a = -Gravity / 2
	*/
	/*	f'(0) = 2*a*x^1 + 1*b*x^0 = JumpImpulse
				b = JumpImpulse
	*/
	/*	f (0) = 1*a*x^2 + 1*b*x^1 + 1*c*x^0 = 0
				c = 0
	*/
	/* seems obvious in hindsight
		a = -Gravity/2
		b = JumpImpulse/Speed
		c = 0
		f (x) = 1*a*x^2 + 1*b*x^1 + 1*c*x^0
		f'(x) = 2*a*x^1 + 1*b*x^0
		f"(x) = 2*a*x^0
	*/
	/* find f (x) = 0
		f (x) = 1*a*x^2 + 1*b*x^1 + 1*c*x^0 = 0
		x1/2 = -b +- (sqrt(b^2-4*a*c)/(2*a))
	*/
	/* find f'(x) = 0
		f'(x) = 2*a*x^1 + 1*b*x^0 = 0
				2*a*x + b = 0
				2*a*x = -b
				x = (-b) / (2*a)
	*/
	/*{
		//float a = -(Gravity / Speed) / 2.0f;
		float a = -(Gravity / Speed);
		float b = JumpImpulse;
		float c = 0.0f;

		float x1 = (-b + sqrt(b*b - 4*a*c))/(2*a);
		float x2 = (-b - sqrt(b*b - 4*a*c))/(2*a);
		float x_ = (-b) / (2*a);

		std::cout << "x1: " << x1 << '\n';
		std::cout << "x2: " << x2 << '\n';
		std::cout << "x_: " << x_ << '\n';

		float x_arr[9] =
		{
			00.0f,
			20.0f,
			40.0f,
			60.0f,
			80.0f,
			100.0f,
			120.0f,
			140.0f,
			160.0f,
		};
		for (unsigned int i = 0; i < 9; i++)
		{
			float x = x_arr[i];
			float y = (a*x*x) + (b*x) + c;
			std::cout << "f(" << x << ") = " << y << '\n';
		}
	}*/
}
