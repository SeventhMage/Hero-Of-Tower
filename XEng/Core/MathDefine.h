#ifndef MATH_DEFINE_H_
#define MATH_DEFINE_H_

#include <string.h>
#include <math.h>

namespace xeng
{
	typedef float	Vector2f[2];
	typedef double	Vector2d[2];

	typedef float	Vector3f[3];
	typedef double	Vector3d[3];

	typedef float	Vector4f[4];
	typedef double	Vector4d[4];


	// 3x3 matrix - column major. X vector is 0, 1, 2, etc.
	//		0	3	6	
	//		1	4	7
	//		2	5	8
	typedef float	Matrix33f[9];
	typedef double	Matrix33d[9];

	// 4x4 matrix - column major. X vector is 0, 1, 2, etc.
	//	0	4	8	12
	//	1	5	9	13
	//	2	6	10	14
	//	3	7	11	15
	typedef float Matrix44f[16];
	typedef double Matrix44d[16];

	///////////////////////////////////////////////////////////////////////////////
	// Useful constants
#define PI (3.14159265358979323846)
#define DOUBLE_PI (2.0 * M3D_PI)
#define PI_DIV_180 (0.017453292519943296)
#define INV_PI_DIV_180 (57.2957795130823229)

#define DEG_TO_RAD(x)	((x)*PI_DIV_180)
#define RAD_TO_DEG(x)	((x)*INV_PI_DIV_180)


}

#endif