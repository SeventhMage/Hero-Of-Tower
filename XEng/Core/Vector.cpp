#include "Vector.h"

namespace xeng
{
	float xeng::GetDistanceSquared3(const Vector3f u, const Vector3f v)
	{
		float x = u[0] - v[0];
		x = x*x;

		float y = u[1] - v[1];
		y = y*y;

		float z = u[2] - v[2];
		z = z*z;

		return (x + y + z);
	}

	double xeng::GetDistanceSquared3(const Vector3d u, const Vector3d v)
	{
		double x = u[0] - v[0];
		x = x*x;

		double y = u[1] - v[1];
		y = y*y;

		double z = u[2] - v[2];
		z = z*z;

		return (x + y + z);
	}

}

