#include "Matrix.h"

namespace xeng
{
	// 4x4 float
	void LoadIdentity44(Matrix44f m)
	{
		// Don't be fooled, this is still column major
		static Matrix44f	identity = { 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f };

		memcpy(m, identity, sizeof(Matrix44f));
	}

	// 4x4 double
	void LoadIdentity44(Matrix44d m)
	{
		static Matrix44d	identity = { 1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0 };

		memcpy(m, identity, sizeof(Matrix44d));
	}

#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  product[(col<<2)+row]

	///////////////////////////////////////////////////////////////////////////////
	// Multiply two 4x4 matricies
	void MatrixMultiply44(Matrix44f product, const Matrix44f a, const Matrix44f b)
	{
		for (int i = 0; i < 4; i++) {
			float ai0 = A(i, 0), ai1 = A(i, 1), ai2 = A(i, 2), ai3 = A(i, 3);
			P(i, 0) = ai0 * B(0, 0) + ai1 * B(1, 0) + ai2 * B(2, 0) + ai3 * B(3, 0);
			P(i, 1) = ai0 * B(0, 1) + ai1 * B(1, 1) + ai2 * B(2, 1) + ai3 * B(3, 1);
			P(i, 2) = ai0 * B(0, 2) + ai1 * B(1, 2) + ai2 * B(2, 2) + ai3 * B(3, 2);
			P(i, 3) = ai0 * B(0, 3) + ai1 * B(1, 3) + ai2 * B(2, 3) + ai3 * B(3, 3);
		}
	}

	// Ditto above, but for doubles
	void MatrixMultiply(Matrix44d product, const Matrix44d a, const Matrix44d b)
	{
		for (int i = 0; i < 4; i++) {
			double ai0 = A(i, 0), ai1 = A(i, 1), ai2 = A(i, 2), ai3 = A(i, 3);
			P(i, 0) = ai0 * B(0, 0) + ai1 * B(1, 0) + ai2 * B(2, 0) + ai3 * B(3, 0);
			P(i, 1) = ai0 * B(0, 1) + ai1 * B(1, 1) + ai2 * B(2, 1) + ai3 * B(3, 1);
			P(i, 2) = ai0 * B(0, 2) + ai1 * B(1, 2) + ai2 * B(2, 2) + ai3 * B(3, 2);
			P(i, 3) = ai0 * B(0, 3) + ai1 * B(1, 3) + ai2 * B(2, 3) + ai3 * B(3, 3);
		}
	}
#undef A
#undef B
#undef P


#define A33(row,col)  a[(col*3)+row]
#define B33(row,col)  b[(col*3)+row]
#define P33(row,col)  product[(col*3)+row]

	///////////////////////////////////////////////////////////////////////////////
	// Multiply two 3x3 matricies
	void MatrixMultiply33(Matrix33f product, const Matrix33f a, const Matrix33f b)
	{
		for (int i = 0; i < 3; i++) {
			float ai0 = A33(i, 0), ai1 = A33(i, 1), ai2 = A33(i, 2);
			P33(i, 0) = ai0 * B33(0, 0) + ai1 * B33(1, 0) + ai2 * B33(2, 0);
			P33(i, 1) = ai0 * B33(0, 1) + ai1 * B33(1, 1) + ai2 * B33(2, 1);
			P33(i, 2) = ai0 * B33(0, 2) + ai1 * B33(1, 2) + ai2 * B33(2, 2);
		}
	}

	// Ditto above, but for doubles
	void MatrixMultiply44(Matrix33d product, const Matrix33d a, const Matrix33d b)
	{
		for (int i = 0; i < 3; i++) {
			double ai0 = A33(i, 0), ai1 = A33(i, 1), ai2 = A33(i, 2);
			P33(i, 0) = ai0 * B33(0, 0) + ai1 * B33(1, 0) + ai2 * B33(2, 0);
			P33(i, 1) = ai0 * B33(0, 1) + ai1 * B33(1, 1) + ai2 * B33(2, 1);
			P33(i, 2) = ai0 * B33(0, 2) + ai1 * B33(1, 2) + ai2 * B33(2, 2);
		}
	}

#undef A33
#undef B33
#undef P33



	////////////////////////////////////////////////////////////////////////////////////////////
	// Create a projection matrix
	// Similiar to the old gluPerspective... fov is in radians btw...
	void MakePerspectiveMatrix(Matrix44f mProjection, float fFov, float fAspect, float zMin, float zMax)
	{
		LoadIdentity44(mProjection); // Fastest way to get most valid values already in place

		float yMax = zMin * tanf(fFov * 0.5f);
		float yMin = -yMax;
		float xMin = yMin * fAspect;
		float xMax = -xMin;

		mProjection[0] = (2.0f * zMin) / (xMax - xMin);
		mProjection[5] = (2.0f * zMin) / (yMax - yMin);
		mProjection[8] = (xMax + xMin) / (xMax - xMin);
		mProjection[9] = (yMax + yMin) / (yMax - yMin);
		mProjection[10] = -((zMax + zMin) / (zMax - zMin));
		mProjection[11] = -1.0f;
		mProjection[14] = -((2.0f * (zMax*zMin)) / (zMax - zMin));
		mProjection[15] = 0.0f;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Make a orthographic projection matrix
	void MakeOrthographicMatrix(Matrix44f mProjection, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
	{
		LoadIdentity44(mProjection);

		mProjection[0] = 2.0f / (xMax - xMin);
		mProjection[5] = 2.0f / (yMax - yMin);
		mProjection[10] = -2.0f / (zMax - zMin);
		mProjection[12] = -((xMax + xMin) / (xMax - xMin));
		mProjection[13] = -((yMax + yMin) / (yMax - yMin));
		mProjection[14] = -((zMax + zMin) / (zMax - zMin));
		mProjection[15] = 1.0f;
	}



#define M33(row,col)  m[col*3+row]
	///////////////////////////////////////////////////////////////////////////////
	// Creates a 3x3 rotation matrix, takes radians NOT degrees
	void RotationMatrix33(Matrix33f m, float angle, float x, float y, float z)
	{

		float mag, s, c;
		float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

		s = float(sin(angle));
		c = float(cos(angle));

		mag = float(sqrt(x*x + y*y + z*z));

		// Identity matrix
		if (mag == 0.0f) {
			LoadIdentity33(m);
			return;
		}

		// Rotation matrix is normalized
		x /= mag;
		y /= mag;
		z /= mag;

		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * s;
		ys = y * s;
		zs = z * s;
		one_c = 1.0f - c;

		M33(0, 0) = (one_c * xx) + c;
		M33(0, 1) = (one_c * xy) - zs;
		M33(0, 2) = (one_c * zx) + ys;

		M33(1, 0) = (one_c * xy) + zs;
		M33(1, 1) = (one_c * yy) + c;
		M33(1, 2) = (one_c * yz) - xs;

		M33(2, 0) = (one_c * zx) - ys;
		M33(2, 1) = (one_c * yz) + xs;
		M33(2, 2) = (one_c * zz) + c;
	}

#undef M33

	///////////////////////////////////////////////////////////////////////////////
	// Creates a 4x4 rotation matrix, takes radians NOT degrees
	void RotationMatrix44(Matrix44f m, float angle, float x, float y, float z)
	{
		float mag, s, c;
		float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

		s = float(sin(angle));
		c = float(cos(angle));

		mag = float(sqrt(x*x + y*y + z*z));

		// Identity matrix
		if (mag == 0.0f) {
			LoadIdentity44(m);
			return;
		}

		// Rotation matrix is normalized
		x /= mag;
		y /= mag;
		z /= mag;

#define M(row,col)  m[col*4+row]

		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * s;
		ys = y * s;
		zs = z * s;
		one_c = 1.0f - c;

		M(0, 0) = (one_c * xx) + c;
		M(0, 1) = (one_c * xy) - zs;
		M(0, 2) = (one_c * zx) + ys;
		M(0, 3) = 0.0f;

		M(1, 0) = (one_c * xy) + zs;
		M(1, 1) = (one_c * yy) + c;
		M(1, 2) = (one_c * yz) - xs;
		M(1, 3) = 0.0f;

		M(2, 0) = (one_c * zx) - ys;
		M(2, 1) = (one_c * yz) + xs;
		M(2, 2) = (one_c * zz) + c;
		M(2, 3) = 0.0f;

		M(3, 0) = 0.0f;
		M(3, 1) = 0.0f;
		M(3, 2) = 0.0f;
		M(3, 3) = 1.0f;

#undef M
	}



	///////////////////////////////////////////////////////////////////////////////
	// Ditto above, but for doubles
	void RotationMatrix33(Matrix33d m, double angle, double x, double y, double z)
	{
		double mag, s, c;
		double xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

		s = sin(angle);
		c = cos(angle);

		mag = sqrt(x*x + y*y + z*z);

		// Identity matrix
		if (mag == 0.0) {
			LoadIdentity33(m);
			return;
		}

		// Rotation matrix is normalized
		x /= mag;
		y /= mag;
		z /= mag;

#define M(row,col)  m[col*3+row]

		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * s;
		ys = y * s;
		zs = z * s;
		one_c = 1.0 - c;

		M(0, 0) = (one_c * xx) + c;
		M(0, 1) = (one_c * xy) - zs;
		M(0, 2) = (one_c * zx) + ys;

		M(1, 0) = (one_c * xy) + zs;
		M(1, 1) = (one_c * yy) + c;
		M(1, 2) = (one_c * yz) - xs;

		M(2, 0) = (one_c * zx) - ys;
		M(2, 1) = (one_c * yz) + xs;
		M(2, 2) = (one_c * zz) + c;

#undef M
	}


	///////////////////////////////////////////////////////////////////////////////
	// Creates a 4x4 rotation matrix, takes radians NOT degrees
	void RotationMatrix44(Matrix44d m, double angle, double x, double y, double z)
	{
		double mag, s, c;
		double xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

		s = sin(angle);
		c = cos(angle);

		mag = sqrt(x*x + y*y + z*z);

		// Identity matrix
		if (mag == 0.0) {
			LoadIdentity44(m);
			return;
		}

		// Rotation matrix is normalized
		x /= mag;
		y /= mag;
		z /= mag;

#define M(row,col)  m[col*4+row]

		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * s;
		ys = y * s;
		zs = z * s;
		one_c = 1.0f - c;

		M(0, 0) = (one_c * xx) + c;
		M(0, 1) = (one_c * xy) - zs;
		M(0, 2) = (one_c * zx) + ys;
		M(0, 3) = 0.0;

		M(1, 0) = (one_c * xy) + zs;
		M(1, 1) = (one_c * yy) + c;
		M(1, 2) = (one_c * yz) - xs;
		M(1, 3) = 0.0;

		M(2, 0) = (one_c * zx) - ys;
		M(2, 1) = (one_c * yz) + xs;
		M(2, 2) = (one_c * zz) + c;
		M(2, 3) = 0.0;

		M(3, 0) = 0.0;
		M(3, 1) = 0.0;
		M(3, 2) = 0.0;
		M(3, 3) = 1.0;

#undef M
	}


}


