#include "ValueType/Matrix/3x3.hpp"
#include "ValueType/Vector/F3.hpp"

#include "ValueType/Angle.hpp"
#include "ValueType/Matrix/2x2.hpp"

#include "ValueType/Vector/F2.hpp"
#include "ValueType/EulerAngle3D.hpp"
#include "ValueType/Trans/2D.hpp"



Matrix3x3::~Matrix3x3()
{ }
Matrix3x3::Matrix3x3()
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			Data[x][y] = 0;
		}
	}
}

Matrix3x3::Matrix3x3(const Matrix3x3 & other)
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			Data[x][y] = other.Data[x][y];
		}
	}
}
Matrix3x3 & Matrix3x3::operator=(const Matrix3x3 & other)
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			Data[x][y] = other.Data[x][y];
		}
	}
	return *this;
}

Matrix3x3::Matrix3x3(	float data00, float data01, float data02,
						float data10, float data11, float data12,
						float data20, float data21, float data22)
{
	Data[0][0] = data00;
	Data[0][1] = data01;
	Data[0][2] = data02;

	Data[1][0] = data10;
	Data[1][1] = data11;
	Data[1][2] = data12;

	Data[2][0] = data20;
	Data[2][1] = data21;
	Data[2][2] = data22;
}



Matrix3x3 Matrix3x3::ToTranspose() const
{
	Matrix3x3 mat;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			mat.Data[x][y] = Data[y][x];
		}
	}
	return mat;
}
Matrix3x3 Matrix3x3::operator~() const
{
	return ToTranspose();
}

Matrix3x3 Matrix3x3::Identity()
{
	Matrix3x3 mat;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			mat.Data[x][y] = (x == y);
		}
	}
	return mat;
}

Matrix3x3 Matrix3x3::Position(VectorF2 p)
{
	return Matrix3x3(
		1, 0, p.X,
		0, 1, p.Y,
		0, 0, 1
	);
}
Matrix3x3 Matrix3x3::Rotation(Angle a)
{
	Matrix2x2 mat = Matrix2x2::Rotation(a);
	return Matrix3x3(
		mat.Data[0][0], mat.Data[0][1], 0,
		mat.Data[1][0], mat.Data[1][1], 0,
		0, 0, 1
	);
}
Matrix3x3 Matrix3x3::TransformForward(Trans2D t)
{
	Matrix3x3 mat = Matrix3x3::Identity();
	mat = mat * Matrix3x3::Position(+t.Pos);
	mat = mat * Matrix3x3::Rotation(t.Rot);
	return mat;
}
Matrix3x3 Matrix3x3::TransformReverse(Trans2D t)
{
	Matrix3x3 mat = Matrix3x3::Identity();
	mat = mat * Matrix3x3::Position(-t.Pos);
	mat = mat / Matrix3x3::Rotation(t.Rot);
	return ~mat;
}

Matrix3x3 Matrix3x3::RotationX(Angle a)
{
	Matrix2x2 mat = Matrix2x2::Rotation(a);
	return Matrix3x3(
		1, 0, 0,
		0, mat.Data[0][0], mat.Data[0][1],
		0, mat.Data[1][0], mat.Data[1][1]
	);
}
Matrix3x3 Matrix3x3::RotationY(Angle a)
{
	Matrix2x2 mat = Matrix2x2::Rotation(a);
	return Matrix3x3(
		mat.Data[1][1], 0, mat.Data[1][0],
		0, 1, 0,
		mat.Data[0][1], 0, mat.Data[0][0]
	);
}
Matrix3x3 Matrix3x3::RotationZ(Angle a)
{
	Matrix2x2 mat = Matrix2x2::Rotation(a);
	return Matrix3x3(
		mat.Data[0][0], mat.Data[0][1], 0,
		mat.Data[1][0], mat.Data[1][1], 0,
		0, 0, 1
	);
}

Matrix3x3 Matrix3x3::Rotation(EulerAngle3D a)
{
	Matrix3x3 mat = Identity();
	mat = mat * RotationY(a.Y2);
	mat = mat * RotationX(a.X1);
	mat = mat * RotationZ(a.Z0);
	return mat;
}



Matrix3x3 Matrix3x3::operator*(const Matrix3x3 & other) const
{
	Matrix3x3 ret;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int n = 0; n < 3; n++)
			{
				ret.Data[x][y] += Data[x][n] * other.Data[n][y];
			}
		}
	}
	return ret;
}
Matrix3x3 Matrix3x3::operator/(const Matrix3x3 & other) const
{
	Matrix3x3 ret;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int n = 0; n < 3; n++)
			{
				ret.Data[x][y] += Data[n][x] * other.Data[n][y];
			}
		}
	}
	return ret;
}



VectorF3 operator*(const VectorF3 & p, const Matrix3x3 & mat)
{
	VectorF3 r;
	float * i = (float*)&p;
	float * o = (float*)&r;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			o[x] += mat.Data[x][y] * i[y];
		}
	}
	return r;
}
VectorF3 operator/(const VectorF3 & p, const Matrix3x3 & mat)
{
	VectorF3 r;
	float * i = (float*)&p;
	float * o = (float*)&r;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			o[y] += mat.Data[x][y] * i[x];
		}
	}
	return r;
}
