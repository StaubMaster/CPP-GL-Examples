#include "ValueType/Matrix/4x4.hpp"
#include "ValueType/Vector/F4.hpp"

#include "ValueType/Angle.hpp"
#include "ValueType/Matrix/3x3.hpp"

#include "ValueType/Vector/F3.hpp"
#include "ValueType/EulerAngle3D.hpp"
#include "ValueType/Trans/3D.hpp"



Matrix4x4::~Matrix4x4()
{ }
Matrix4x4::Matrix4x4()
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			Data[x][y] = 0;
		}
	}
}

Matrix4x4::Matrix4x4(const Matrix4x4 & other)
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			Data[x][y] = other.Data[x][y];
		}
	}
}
Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 & other)
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			Data[x][y] = other.Data[x][y];
		}
	}
	return *this;
}

Matrix4x4::Matrix4x4(	float data00, float data01, float data02, float data03,
						float data10, float data11, float data12, float data13,
						float data20, float data21, float data22, float data23,
						float data30, float data31, float data32, float data33)
{
	Data[0][0] = data00;
	Data[0][1] = data01;
	Data[0][2] = data02;
	Data[0][3] = data03;

	Data[1][0] = data10;
	Data[1][1] = data11;
	Data[1][2] = data12;
	Data[1][3] = data13;

	Data[2][0] = data20;
	Data[2][1] = data21;
	Data[2][2] = data22;
	Data[2][3] = data23;

	Data[3][0] = data30;
	Data[3][1] = data31;
	Data[3][2] = data32;
	Data[3][3] = data33;
}



Matrix4x4 Matrix4x4::ToTranspose() const
{
	Matrix4x4 mat;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			mat.Data[x][y] = Data[y][x];
		}
	}
	return mat;
}
Matrix4x4 Matrix4x4::operator~() const
{
	return ToTranspose();
}



Matrix4x4 Matrix4x4::Identity()
{
	Matrix4x4 mat;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			mat.Data[x][y] = (x == y);
		}
	}
	return mat;
}

Matrix4x4 Matrix4x4::Position(VectorF3 p)
{
	return Matrix4x4(
		1, 0, 0, p.X,
		0, 1, 0, p.Y,
		0, 0, 1, p.Z,
		0, 0, 0, 1
	);
}
Matrix4x4 Matrix4x4::Rotation(EulerAngle3D a)
{
	Matrix3x3 mat = Matrix3x3::Rotation(a);
	return Matrix4x4(
		mat.Data[0][0], mat.Data[0][1], mat.Data[0][2], 0,
		mat.Data[1][0], mat.Data[1][1], mat.Data[1][2], 0,
		mat.Data[2][0], mat.Data[2][1], mat.Data[2][2], 0,
		0, 0, 0, 1
	);
}
Matrix4x4 Matrix4x4::TransformForward(Trans3D t)
{
	Matrix4x4 mat = Matrix4x4::Identity();
	mat = mat * Matrix4x4::Position(+t.Position);
	mat = mat * Matrix4x4::Rotation(t.Rotation);
	return mat;
}
Matrix4x4 Matrix4x4::TransformReverse(Trans3D t)
{
	Matrix4x4 mat = Matrix4x4::Identity();
	mat = mat * Matrix4x4::Position(-t.Position);
	mat = mat / Matrix4x4::Rotation(t.Rotation);
	return ~mat;
}



Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & other) const
{
	Matrix4x4 ret;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int n = 0; n < 4; n++)
			{
				ret.Data[x][y] += Data[x][n] * other.Data[n][y];
			}
		}
	}
	return ret;
}
Matrix4x4 Matrix4x4::operator/(const Matrix4x4 & other) const
{
	Matrix4x4 ret;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int n = 0; n < 4; n++)
			{
				ret.Data[x][y] += Data[n][x] * other.Data[n][y];
			}
		}
	}
	return ret;
}



VectorF4 operator*(const VectorF4 & p, const Matrix4x4 & mat)
{
	VectorF4 r;
	float * i = (float*)&p;
	float * o = (float*)&r;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			o[x] += mat.Data[x][y] * i[y];
		}
	}
	return r;
}
VectorF4 operator/(const VectorF4 & p, const Matrix4x4 & mat)
{
	VectorF4 r;
	float * i = (float*)&p;
	float * o = (float*)&r;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			o[y] += mat.Data[x][y] * i[x];
		}
	}
	return r;
}

VectorF3 operator*(const VectorF3 & p, const Matrix4x4 & mat)
{
	VectorF4 temp = VectorF4(p.X, p.Y, p.Z, 1) * mat;
	return VectorF3(temp.X, temp.Y, temp.Z);
}
VectorF3 operator/(const VectorF3 & p, const Matrix4x4 & mat)
{
	VectorF4 temp = VectorF4(p.X, p.Y, p.Z, 1) / mat;
	return VectorF3(temp.X, temp.Y, temp.Z);
}
