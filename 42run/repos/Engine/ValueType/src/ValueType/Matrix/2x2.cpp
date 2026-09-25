#include "ValueType/Matrix/2x2.hpp"
#include "ValueType/Vector/F2.hpp"
#include "ValueType/Angle.hpp"



Matrix2x2::~Matrix2x2()
{ }
Matrix2x2::Matrix2x2()
{
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			Data[x][y] = 0;
		}
	}
}

Matrix2x2::Matrix2x2(const Matrix2x2 & other)
{
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			Data[x][y] = other.Data[x][y];
		}
	}
}
Matrix2x2 & Matrix2x2::operator=(const Matrix2x2 & other)
{
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			Data[x][y] = other.Data[x][y];
		}
	}
	return *this;
}

Matrix2x2::Matrix2x2(	float data00, float data01,
						float data10, float data11)
{
	Data[0][0] = data00;
	Data[0][1] = data01;

	Data[1][0] = data10;
	Data[1][1] = data11;
}



Matrix2x2 Matrix2x2::ToTranspose() const
{
	Matrix2x2 mat;
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			mat.Data[x][y] = Data[y][x];
		}
	}
	return mat;
}
Matrix2x2 Matrix2x2::operator~() const
{
	return ToTranspose();
}

Matrix2x2 Matrix2x2::Identity()
{
	Matrix2x2 mat;
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			mat.Data[x][y] = (x == y);
		}
	}
	return mat;
}
Matrix2x2 Matrix2x2::Rotation(Angle a)
{
	float sin_ = a.Sin();
	float cos_ = a.Cos();
	return Matrix2x2(
		+cos_ , -sin_ ,
		+sin_ , +cos_
	);
}



Matrix2x2 Matrix2x2::operator*(const Matrix2x2 & other) const
{
	Matrix2x2 ret;
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int n = 0; n < 2; n++)
			{
				ret.Data[x][y] += Data[x][n] * other.Data[n][y];
			}
		}
	}
	return ret;
}
Matrix2x2 Matrix2x2::operator/(const Matrix2x2 & other) const
{
	Matrix2x2 ret;
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int n = 0; n < 2; n++)
			{
				ret.Data[x][y] += Data[n][x] * other.Data[n][y];
			}
		}
	}
	return ret;
}



VectorF2 operator*(const VectorF2 & p, const Matrix2x2 & mat)
{
	VectorF2 r;
	float * i = (float*)&p;
	float * o = (float*)&r;
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			o[x] += mat.Data[x][y] * i[y];
		}
	}
	return r;
}
VectorF2 operator/(const VectorF2 & p, const Matrix2x2 & mat)
{
	VectorF2 r;
	float * i = (float*)&p;
	float * o = (float*)&r;
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			o[y] += mat.Data[x][y] * i[x];
		}
	}
	return r;
}
