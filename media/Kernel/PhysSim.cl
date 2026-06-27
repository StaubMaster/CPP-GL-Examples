
typedef float Matrix_3_3 [3][3];

typedef struct
{
	float X;
	float Y;
	float Z;
} VectorF3;

typedef struct
{
	float X;
	float Y;
	float Z;
	Matrix_3_3 Data;
} Angle3D;

typedef struct
{
	VectorF3 Pos;
	Angle3D Rot;
} Trans3D;

typedef struct
{
	VectorF3 Pos;
	VectorF3 Dir;
} RayF3;

typedef struct
{
	Trans3D	Trans;
	Trans3D	Vel;
} Physics3D;



void rot(float * pls, float * mns, float fsin, float fcos)
{
	float temp;
	temp = fcos * (*pls) - fsin * (*mns);
	*mns = fcos * (*mns) + fsin * (*pls);
	*pls = temp;
}



float VectorF3_len2(VectorF3 p)
{
	float ret = 0;
	ret = ret + (p.X * p.X);
	ret = ret + (p.Y * p.Y);
	ret = ret + (p.Z * p.Z);
	return ret;
}
float VectorF3_len(VectorF3 p)
{
	return sqrt(VectorF3_len2(p));
}

VectorF3 VectorF3_add(VectorF3 p0, VectorF3 p1)
{
	VectorF3 ret;
	ret.X = p0.X + p1.X;
	ret.Y = p0.Y + p1.Y;
	ret.Z = p0.Z + p1.Z;
	return ret;
}
VectorF3 VectorF3_sub(VectorF3 p0, VectorF3 p1)
{
	VectorF3 ret;
	ret.X = p0.X - p1.X;
	ret.Y = p0.Y - p1.Y;
	ret.Z = p0.Z - p1.Z;
	return ret;
}

VectorF3 VectorF3_mul_flt(VectorF3 p, float val)
{
	VectorF3 ret;
	ret.X = p.X * val;
	ret.Y = p.Y * val;
	ret.Z = p.Z * val;
	return ret;
}

float VectorF3_dot(VectorF3 p0, VectorF3 p1)
{
	float ret = 0;
	ret = ret + (p0.X * p1.X);
	ret = ret + (p0.Y * p1.Y);
	ret = ret + (p0.Z * p1.Z);
	return ret;
}





void MatrixDefault(Matrix_3_3 * data)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == j)
			{
				(*data)[i][j] = 1;
			}
			else
			{
				(*data)[i][j] = 0;
			}
		}
	}
}
void MatrixCopy(Matrix_3_3 * result, const Matrix_3_3 mat)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			(*result)[i][j] = mat[i][j];
		}
	}
}
void MatrixTransPose(Matrix_3_3 * result, const Matrix_3_3 mat)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			(*result)[i][j] = mat[j][i];
		}
	}
}
void MatrixMultiply(Matrix_3_3 * result, const Matrix_3_3 mat0, const Matrix_3_3 mat1)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			float sum = 0;
			for (int n = 0; n < 3; n++)
			{
				sum += mat0[i][n] * mat1[n][j];
			}
			(*result)[i][j] = sum;
		}
	}
}



void CalcFore(Angle3D * a)
{
	float sinX, cosX;
	sinX = sincos(a -> X, &cosX);
	Matrix_3_3 matX = {
		{ +cosX , 0 , -sinX },
		{   0   , 1 ,   0   },
		{ +sinX , 0 , +cosX },
	};

	float sinY, cosY;
	sinY = sincos(a -> Y, &cosY);
	Matrix_3_3 matY = {
		{ 1 ,   0   ,   0   },
		{ 0 , +cosY , -sinY },
		{ 0 , +sinY , +cosY },
	};

	float sinZ, cosZ;
	sinZ = sincos(a -> Z, &cosZ);
	Matrix_3_3 matZ = {
		{ +cosZ , +sinZ , 0 },
		{ -sinZ , +cosZ , 0 },
		{   0   ,   0   , 1 },
	};

	Matrix_3_3 temp0;
	Matrix_3_3 temp1;
	MatrixDefault(&temp0);
	MatrixMultiply(&temp1, temp0, matZ);
	MatrixMultiply(&temp0, temp1, matY);
	MatrixMultiply(&temp1, temp0, matX);
	MatrixCopy(&(a -> Data), temp1);
}
void CalcBack(Angle3D * a)
{
	float sinZ, cosZ;
	sinZ = sincos(a -> Z, &cosZ);
	Matrix_3_3 matZ = {
		{ +cosZ , -sinZ , 0 },
		{ +sinZ , +cosZ , 0 },
		{   0   ,   0   , 1 },
	};

	float sinY, cosY;
	sinY = sincos(a -> Y, &cosY);
	Matrix_3_3 matY = {
		{ 1 ,   0   ,   0   },
		{ 0 , +cosY , +sinY },
		{ 0 , -sinY , +cosY },
	};
	
	float sinX, cosX;
	sinX = sincos(a -> X, &cosX);
	Matrix_3_3 matX = {
		{ +cosX , 0 , +sinX },
		{   0   , 1 ,   0   },
		{ -sinX , 0 , +cosX },
	};

	Matrix_3_3 temp0;
	Matrix_3_3 temp1;
	MatrixDefault(&temp0);
	MatrixMultiply(&temp1, temp0, matX);
	MatrixMultiply(&temp0, temp1, matY);
	MatrixMultiply(&temp1, temp0, matZ);
	MatrixCopy(&(a -> Data), temp1);
}


kernel void Init(
	global Physics3D * buffer
)
{
	Physics3D phys;

	phys.Trans.Pos.X = (get_global_id(0) - 16.0f + 0.5f) * 3;
	phys.Trans.Pos.Y = (get_global_id(1) - 16.0f + 0.5f) * 3;
	phys.Trans.Pos.Z = (get_global_id(2) - 16.0f + 0.5f) * 3;

	phys.Trans.Rot.X = 0.0f;
	phys.Trans.Rot.Y = 0.0f;
	phys.Trans.Rot.Z = 0.0f;

	CalcBack(&phys.Trans.Rot);


	phys.Vel.Pos.X = 0.0f;
	phys.Vel.Pos.Y = 0.0f;
	phys.Vel.Pos.Z = 0.0f;

	phys.Vel.Rot.X = 0.0f;
	phys.Vel.Rot.Y = 0.0f;
	phys.Vel.Rot.Z = 0.0f;

	CalcBack(&phys.Vel.Rot);

	buffer[(32 * (32 * (get_global_id(0)) + get_global_id(1)) + get_global_id(2))] = phys;
}



kernel void Move(
	global Physics3D * buffer
)
{
	Physics3D phys = buffer[get_global_id(0)];

	phys.Trans.Pos = VectorF3_add(phys.Trans.Pos, phys.Vel.Pos);

	buffer[get_global_id(0)] = phys;
}



kernel void Keep(
	global Physics3D * buffer
)
{
	Physics3D phys = buffer[get_global_id(0)];

	if (phys.Trans.Pos.X < -200) { phys.Vel.Pos.X = +0.1; }
	if (phys.Trans.Pos.Y < -200) { phys.Vel.Pos.Y = +0.1; }
	if (phys.Trans.Pos.Z < -200) { phys.Vel.Pos.Z = +0.1; }
	if (phys.Trans.Pos.X > +200) { phys.Vel.Pos.X = -0.1; }
	if (phys.Trans.Pos.Y > +200) { phys.Vel.Pos.Y = -0.1; }
	if (phys.Trans.Pos.Z > +200) { phys.Vel.Pos.Z = -0.1; }

	/*float vel_limit = 10.0;
	float len = VectorF3_len(phys.Vel.Pos);
	if (len > vel_limit)
	{
		phys.Vel.Pos = VectorF3_mul_flt(phys.Vel.Pos, vel_limit / len);
	}*/

	buffer[get_global_id(0)] = phys;
}



kernel void Look(
	global Physics3D * buffer
)
{
	Physics3D phys = buffer[get_global_id(0)];

	float len = VectorF3_len(phys.Vel.Pos);

	phys.Trans.Rot.X = atan2(phys.Vel.Pos.X, phys.Vel.Pos.Z);
	phys.Trans.Rot.Y = atan2(phys.Vel.Pos.Y, len);
	phys.Trans.Rot.Z = 0;

	CalcBack(&phys.Trans.Rot);

	buffer[get_global_id(0)] = phys;
}



kernel void GravRay(
	global const RayF3 * ray,
	global Physics3D * buffer
)
{
	Physics3D phys = buffer[get_global_id(0)];

	VectorF3 diff = VectorF3_sub(ray -> Pos, phys.Trans.Pos);

	float dot = VectorF3_dot(ray -> Dir, diff);
	float sqr = VectorF3_len2(ray -> Dir);
	float t = -(dot / sqr);
	VectorF3 p = VectorF3_add(VectorF3_mul_flt(ray -> Dir, t), ray -> Pos);

	diff = VectorF3_sub(p, phys.Trans.Pos);
	float dist2 = VectorF3_len2(diff);
	diff = VectorF3_mul_flt(diff, 1.0f / sqrt(dist2));

	VectorF3 grav_vel = VectorF3_mul_flt(diff, 0.01f);

//	phys.Vel.Pos = grav_vel;
	phys.Vel.Pos = VectorF3_add(phys.Vel.Pos, grav_vel);

//	phys.Vel.Pos = VectorF3_mul_flt(diff, 0.1f);
//	phys.Vel.Pos = VectorF3_mul_flt(ray -> Dir, 0.1f);

	buffer[get_global_id(0)] = phys;
}
