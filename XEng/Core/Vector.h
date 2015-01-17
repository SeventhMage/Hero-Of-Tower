#ifndef VECTOR_H_
#define VECTOR_H_

#include "MathDefine.h"


namespace xeng
{
	///////////////////////////////////////////////////////////////////////////////
	// Inline vector functions
	// Load Vector with (x, y, z, w).
	inline void LoadVector2(Vector2f v, const float x, const float y)
	{
		v[0] = x; v[1] = y;
	}
	inline void LoadVector2(Vector2d v, const float x, const float y)
	{
		v[0] = x; v[1] = y;
	}
	inline void LoadVector3(Vector3f v, const float x, const float y, const float z)
	{
		v[0] = x; v[1] = y; v[2] = z;
	}
	inline void LoadVector3(Vector3d v, const double x, const double y, const double z)
	{
		v[0] = x; v[1] = y; v[2] = z;
	}
	inline void LoadVector4(Vector4f v, const float x, const float y, const float z, const float w)
	{
		v[0] = x; v[1] = y; v[2] = z; v[3] = w;
	}
	inline void LoadVector4(Vector4d v, const double x, const double y, const double z, const double w)
	{
		v[0] = x; v[1] = y; v[2] = z; v[3] = w;
	}


	////////////////////////////////////////////////////////////////////////////////
	// Copy vector src into vector dst
	inline void	CopyVector2(Vector2f dst, const Vector2f src) { memcpy(dst, src, sizeof(Vector2f)); }
	inline void	CopyVector2(Vector2d dst, const Vector2d src) { memcpy(dst, src, sizeof(Vector2d)); }

	inline void	CopyVector3(Vector3f dst, const Vector3f src) { memcpy(dst, src, sizeof(Vector3f)); }
	inline void	CopyVector3(Vector3d dst, const Vector3d src) { memcpy(dst, src, sizeof(Vector3d)); }

	inline void	CopyVector4(Vector4f dst, const Vector4f src) { memcpy(dst, src, sizeof(Vector4f)); }
	inline void	CopyVector4(Vector4d dst, const Vector4d src) { memcpy(dst, src, sizeof(Vector4d)); }


	////////////////////////////////////////////////////////////////////////////////
	// Add Vectors (r, a, b) r = a + b
	inline void AddVectors2(Vector2f r, const Vector2f a, const Vector2f b)
	{
		r[0] = a[0] + b[0];	r[1] = a[1] + b[1];
	}
	inline void AddVectors2(Vector2d r, const Vector2d a, const Vector2d b)
	{
		r[0] = a[0] + b[0];	r[1] = a[1] + b[1];
	}

	inline void AddVectors3(Vector3f r, const Vector3f a, const Vector3f b)
	{
		r[0] = a[0] + b[0];	r[1] = a[1] + b[1]; r[2] = a[2] + b[2];
	}
	inline void AddVectors3(Vector3d r, const Vector3d a, const Vector3d b)
	{
		r[0] = a[0] + b[0];	r[1] = a[1] + b[1]; r[2] = a[2] + b[2];
	}

	inline void AddVectors4(Vector4f r, const Vector4f a, const Vector4f b)
	{
		r[0] = a[0] + b[0];	r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; r[3] = a[3] + b[3];
	}
	inline void AddVectors4(Vector4d r, const Vector4d a, const Vector4d b)
	{
		r[0] = a[0] + b[0];	r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; r[3] = a[3] + b[3];
	}

	////////////////////////////////////////////////////////////////////////////////
	// Subtract Vectors (r, a, b) r = a - b
	inline void SubtractVectors2(Vector2f r, const Vector2f a, const Vector2f b)
	{
		r[0] = a[0] - b[0]; r[1] = a[1] - b[1];
	}
	inline void SubtractVectors2(Vector2d r, const Vector2d a, const Vector2d b)
	{
		r[0] = a[0] - b[0]; r[1] = a[1] - b[1];
	}

	inline void SubtractVectors3(Vector3f r, const Vector3f a, const Vector3f b)
	{
		r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2];
	}
	inline void SubtractVectors3(Vector3d r, const Vector3d a, const Vector3d b)
	{
		r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2];
	}

	inline void SubtractVectors4(Vector4f r, const Vector4f a, const Vector4f b)
	{
		r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; r[3] = a[3] - b[3];
	}
	inline void SubtractVectors4(Vector4d r, const Vector4d a, const Vector4d b)
	{
		r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; r[3] = a[3] - b[3];
	}



	///////////////////////////////////////////////////////////////////////////////////////
	// Scale Vectors (in place)
	inline void ScaleVector2(Vector2f v, const float scale)
	{
		v[0] *= scale; v[1] *= scale;
	}
	inline void ScaleVector2(Vector2d v, const double scale)
	{
		v[0] *= scale; v[1] *= scale;
	}

	inline void ScaleVector3(Vector3f v, const float scale)
	{
		v[0] *= scale; v[1] *= scale; v[2] *= scale;
	}
	inline void ScaleVector3(Vector3d v, const double scale)
	{
		v[0] *= scale; v[1] *= scale; v[2] *= scale;
	}

	inline void ScaleVector4(Vector4f v, const float scale)
	{
		v[0] *= scale; v[1] *= scale; v[2] *= scale; v[3] *= scale;
	}
	inline void ScaleVector4(Vector4d v, const double scale)
	{
		v[0] *= scale; v[1] *= scale; v[2] *= scale; v[3] *= scale;
	}


	//////////////////////////////////////////////////////////////////////////////////////
	// Cross Product
	// u x v = result
	// 3 component vectors only.
	inline void CrossProduct3(Vector3f result, const Vector3f u, const Vector3f v)
	{
		result[0] = u[1] * v[2] - v[1] * u[2];
		result[1] = -u[0] * v[2] + v[0] * u[2];
		result[2] = u[0] * v[1] - v[0] * u[1];
	}

	inline void CrossProduct3(Vector3d result, const Vector3d u, const Vector3d v)
	{
		result[0] = u[1] * v[2] - v[1] * u[2];
		result[1] = -u[0] * v[2] + v[0] * u[2];
		result[2] = u[0] * v[1] - v[0] * u[1];
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// Dot Product, only for three component vectors
	// return u dot v
	inline float DotProduct3(const Vector3f u, const Vector3f v)
	{
		return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
	}

	inline double DotProduct3(const Vector3d u, const Vector3d v)
	{
		return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// Angle between vectors, only for three component vectors. Angle is in radians...
	inline float GetAngleBetweenVectors3(const Vector3f u, const Vector3f v)
	{
		float dTemp = DotProduct3(u, v);
		return float(acos(double(dTemp)));	// Double cast just gets rid of compiler warning, no real need
	}

	inline double GetAngleBetweenVectors3(const Vector3d u, const Vector3d v)
	{
		double dTemp = DotProduct3(u, v);
		return acos(dTemp);
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// Get Square of a vectors length
	// Only for three component vectors
	inline float GetVectorLengthSquared3(const Vector3f u)
	{
		return (u[0] * u[0]) + (u[1] * u[1]) + (u[2] * u[2]);
	}

	inline double GetVectorLengthSquared3(const Vector3d u)
	{
		return (u[0] * u[0]) + (u[1] * u[1]) + (u[2] * u[2]);
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// Get lenght of vector
	// Only for three component vectors.
	inline float GetVectorLength3(const Vector3f u)
	{
		return sqrtf(GetVectorLengthSquared3(u));
	}

	inline double GetVectorLength3(const Vector3d u)
	{
		return sqrt(GetVectorLengthSquared3(u));
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// Normalize a vector
	// Scale a vector to unit length. Easy, just scale the vector by it's length
	inline void NormalizeVector3(Vector3f u)
	{
		ScaleVector3(u, 1.0f / GetVectorLength3(u));
	}

	inline void NormalizeVector3(Vector3d u)
	{
		ScaleVector3(u, 1.0 / GetVectorLength3(u));
	}


	//////////////////////////////////////////////////////////////////////////////////////
	// Get the distance between two points. The distance between two points is just
	// the magnitude of the difference between two vectors
	// Located in math.cpp
	float GetDistanceSquared3(const Vector3f u, const Vector3f v);
	double GetDistanceSquared3(const Vector3d u, const Vector3d v);

	inline double GetDistance3(const Vector3d u, const Vector3d v)
	{
		return sqrt(GetDistanceSquared3(u, v));
	}

	inline float GetDistance3(const Vector3f u, const Vector3f v)
	{
		return sqrtf(GetDistanceSquared3(u, v));
	}

	inline float GetMagnitudeSquared3(const Vector3f u) { return u[0] * u[0] + u[1] * u[1] + u[2] * u[2]; }
	inline double GetMagnitudeSquared3(const Vector3d u) { return u[0] * u[0] + u[1] * u[1] + u[2] * u[2]; }

	inline float GetMagnitude3(const Vector3f u) { return sqrtf(GetMagnitudeSquared3(u)); }
	inline double GetMagnitude3(const Vector3d u) { return sqrt(GetMagnitudeSquared3(u)); }

}

#endif