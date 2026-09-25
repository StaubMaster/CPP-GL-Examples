#ifndef  MATRIX_3_3_HPP
# define MATRIX_3_3_HPP

struct VectorF3;

struct Angle;

struct VectorF2;
struct EulerAngle3D;
struct Trans2D;

struct Matrix3x3
{
	public:
	float Data[3][3];

	public:
	~Matrix3x3();
	Matrix3x3();
	
	Matrix3x3(const Matrix3x3 & other);
	Matrix3x3 & operator=(const Matrix3x3 & other);

	Matrix3x3(	float data00, float data01, float data02,
				float data10, float data11, float data12,
				float data20, float data21, float data22);

	Matrix3x3	ToTranspose() const;
	Matrix3x3	operator~() const;

	static Matrix3x3	Identity();
	
	static Matrix3x3	Position(VectorF2 p);
	static Matrix3x3	Rotation(Angle a);
	static Matrix3x3	TransformForward(Trans2D t);
	static Matrix3x3	TransformReverse(Trans2D t);

	static Matrix3x3	RotationX(Angle a);
	static Matrix3x3	RotationY(Angle a);
	static Matrix3x3	RotationZ(Angle a);
	static Matrix3x3	Rotation(EulerAngle3D a);

	public:
	Matrix3x3	operator*(const Matrix3x3 & other) const;
	Matrix3x3	operator/(const Matrix3x3 & other) const;
};

VectorF3	operator*(const VectorF3 & p, const Matrix3x3 & mat);
VectorF3	operator/(const VectorF3 & p, const Matrix3x3 & mat);

#endif