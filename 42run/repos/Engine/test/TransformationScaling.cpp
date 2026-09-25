#include <iostream>
#include "ValueType/_Show.hpp"

#include "ValueType/Vector/F2.hpp"
#include "ValueType/Vector/F3.hpp"
#include "ValueType/Vector/F4.hpp"

#include "ValueType/Angle.hpp"
#include "ValueType/EulerAngle3D.hpp"

#include "ValueType/Trans/2D.hpp"
#include "ValueType/Trans/3D.hpp"

#include "ValueType/Matrix/2x2.hpp"
#include "ValueType/Matrix/3x3.hpp"
#include "ValueType/Matrix/4x4.hpp"

#include <math.h>




int main()
{
	std::cout << '\n';
	{
		Trans3D	trans;
		trans.Position = VectorF3(2, 4, 6);
		trans.Rotation = EulerAngle3D::Degrees(43, 54, 9);
		Matrix4x4 mat = Matrix4x4::TransformForward(trans);

		VectorF3 scale0(15, 7, 53);
		Matrix4x4 mat_scale0 = Matrix4x4(
			scale0.X, 0, 0, 0,
			0, scale0.Y, 0, 0,
			0, 0, scale0.Z, 0,
			0, 0, 0, 1
		);
	
		VectorF3 scale1(15, 7, 53);
		Matrix4x4 mat_scale1 = Matrix4x4(
			scale1.X, 0, 0, 0,
			0, scale1.Y, 0, 0,
			0, 0, scale1.Z, 0,
			0, 0, 0, 1
		);

		VectorF3 scale2(15, 7, 53);
		Matrix4x4 mat_scale2 = Matrix4x4(
			scale2.X, 0, 0, 0,
			0, scale2.Y, 0, 0,
			0, 0, scale2.Z, 0,
			0, 0, 0, 1
		);

		VectorF3 test_pos(58, 382, 93);

		// scale0
		// rotation
		// scale1
		// position
		// scale2

		// one might also want to move before scaling
		// scale0
		// position0
		// scale1
		// rotation
		// scale2
		// position
		// scale3
		// most of this would be unused most of the time

		/*	GenericTransformation3D
			Transformer3D
			{
				VectorF3 forward(VectorF3);
				VectorF3 reverse(VectorF3);
			}
			use a Tempalate to store Transformers
			then transforming forward or backward
			or turning into a Matrix, just follow the order of those ?

			make current Trans3D a generic transformtaion ?
			how would I access the Members by Name ?
			maybe referance functions. but those are ugly
		*/

		mat = Matrix4x4::Identity();
		mat = mat * mat_scale0;
		mat = mat * Matrix4x4::Position(+trans.Position);
		mat = mat * mat_scale1;
		mat = mat * Matrix4x4::Rotation(trans.Rotation);
		mat = mat * mat_scale2;

		VectorF3 pos = test_pos;
		pos = pos * scale0;
		pos = trans.Rotation.forward(pos);
		pos = pos * scale1;
		pos = pos + trans.Position;
		pos = pos * scale2;

		std::cout << (test_pos * mat) << '\n';
		std::cout << (pos) << '\n';
	}
	std::cout << '\n';
	std::cout << sizeof(Trans3D) << '\n';
	std::cout << '\n';
	return 0;
}
