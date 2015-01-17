#ifndef MATRIX_H_
#define MATRIX_H_

#include "MathDefine.h"

namespace xeng
{
	// Copy Matrix
	// Brain-dead memcpy
	inline void CopyMatrix33(Matrix33f dst, const Matrix33f src)
	{
		memcpy(dst, src, sizeof(Matrix33f));
	}

	inline void CopyMatrix33(Matrix33d dst, const Matrix33d src)
	{
		memcpy(dst, src, sizeof(Matrix33d));
	}

	inline void CopyMatrix44(Matrix44f dst, const Matrix44f src)
	{
		memcpy(dst, src, sizeof(Matrix44f));
	}

	inline void CopyMatrix44(Matrix44d dst, const Matrix44d src)
	{
		memcpy(dst, src, sizeof(Matrix44d));
	}

	// LoadIdentity
	// Implemented in Math3d.cpp
	void LoadIdentity33(Matrix33f m);
	void LoadIdentity33(Matrix33d m);
	void LoadIdentity44(Matrix44f m);
	void LoadIdentity44(Matrix44d m);

	/////////////////////////////////////////////////////////////////////////////
	// Get/Set Column.
	inline void GetMatrixColumn33(Vector3f dst, const Matrix33f src, const int column)
	{
		memcpy(dst, src + (3 * column), sizeof(float)* 3);
	}

	inline void GetMatrixColumn33(Vector3d dst, const Matrix33d src, const int column)
	{
		memcpy(dst, src + (3 * column), sizeof(double)* 3);
	}

	inline void SetMatrixColumn33(Matrix33f dst, const Vector3f src, const int column)
	{
		memcpy(dst + (3 * column), src, sizeof(float)* 3);
	}

	inline void SetMatrixColumn33(Matrix33d dst, const Vector3d src, const int column)
	{
		memcpy(dst + (3 * column), src, sizeof(double)* 3);
	}

	inline void GetMatrixColumn44(Vector4f dst, const Matrix44f src, const int column)
	{
		memcpy(dst, src + (4 * column), sizeof(float)* 4);
	}

	inline void GetMatrixColumn44(Vector4d dst, const Matrix44d src, const int column)
	{
		memcpy(dst, src + (4 * column), sizeof(double)* 4);
	}

	inline void SetMatrixColumn44(Matrix44f dst, const Vector4f src, const int column)
	{
		memcpy(dst + (4 * column), src, sizeof(float)* 4);
	}

	inline void SetMatrixColumn44(Matrix44d dst, const Vector4d src, const int column)
	{
		memcpy(dst + (4 * column), src, sizeof(double)* 4);
	}


	///////////////////////////////////////////////////////////////////////////////
	// Extract a rotation matrix from a 4x4 matrix
	// Extracts the rotation matrix (3x3) from a 4x4 matrix
	inline void ExtractRotationMatrix33(Matrix33f dst, const Matrix44f src)
	{
		memcpy(dst, src, sizeof(float)* 3); // X column
		memcpy(dst + 3, src + 4, sizeof(float)* 3); // Y column
		memcpy(dst + 6, src + 8, sizeof(float)* 3); // Z column
	}

	// Ditto above, but for doubles
	inline void ExtractRotationMatrix33(Matrix33d dst, const Matrix44d src)
	{
		memcpy(dst, src, sizeof(double)* 3); // X column
		memcpy(dst + 3, src + 4, sizeof(double)* 3); // Y column
		memcpy(dst + 6, src + 8, sizeof(double)* 3); // Z column
	}

	// Inject Rotation (3x3) into a full 4x4 matrix...
	inline void InjectRotationMatrix44(Matrix44f dst, const Matrix33f src)
	{
		memcpy(dst, src, sizeof(float)* 4);
		memcpy(dst + 4, src + 4, sizeof(float)* 4);
		memcpy(dst + 8, src + 8, sizeof(float)* 4);
	}

	// Ditto above for doubles
	inline void InjectRotationMatrix44(Matrix44d dst, const Matrix33d src)
	{
		memcpy(dst, src, sizeof(double)* 4);
		memcpy(dst + 4, src + 4, sizeof(double)* 4);
		memcpy(dst + 8, src + 8, sizeof(double)* 4);
	}

	////////////////////////////////////////////////////////////////////////////////
	// MultMatrix
	// Implemented in Math.cpp
	void MatrixMultiply44(Matrix44f product, const Matrix44f a, const Matrix44f b);
	void MatrixMultiply44(Matrix44d product, const Matrix44d a, const Matrix44d b);
	void MatrixMultiply33(Matrix33f product, const Matrix33f a, const Matrix33f b);
	void MatrixMultiply33(Matrix33d product, const Matrix33d a, const Matrix33d b);


	// Transform - Does rotation and translation via a 4x4 matrix. Transforms
	// a point or vector.
	// By-the-way __inline means I'm asking the compiler to do a cost/benefit analysis. If 
	// these are used frequently, they may not be inlined to save memory. I'm experimenting
	// with this....
	// Just transform a 3 compoment vector
	__inline void TransformVector3(Vector3f vOut, const Vector3f v, const Matrix44f m)
	{
		vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12];// * v[3];	// Assuming 1 
		vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13];// * v[3];	
		vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];// * v[3];	
		//vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
	}

	// Ditto above, but for doubles
	__inline void TransformVector3(Vector3d vOut, const Vector3d v, const Matrix44d m)
	{
		vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12];// * v[3];	 
		vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13];// * v[3];	
		vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];// * v[3];	
		//vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
	}

	// Full four component transform
	__inline void TransformVector4(Vector4f vOut, const Vector4f v, const Matrix44f m)
	{
		vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12] * v[3];
		vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13] * v[3];
		vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
		vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
	}

	// Ditto above, but for doubles
	__inline void TransformVector4(Vector4d vOut, const Vector4d v, const Matrix44d m)
	{
		vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12] * v[3];
		vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13] * v[3];
		vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
		vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
	}



	// Just do the rotation, not the translation... this is usually done with a 3x3
	// Matrix.
	__inline void RotateVector(Vector3f vOut, const Vector3f p, const Matrix33f m)
	{
		vOut[0] = m[0] * p[0] + m[3] * p[1] + m[6] * p[2];
		vOut[1] = m[1] * p[0] + m[4] * p[1] + m[7] * p[2];
		vOut[2] = m[2] * p[0] + m[5] * p[1] + m[8] * p[2];
	}

	// Ditto above, but for doubles
	__inline void RotateVector(Vector3d vOut, const Vector3d p, const Matrix33d m)
	{
		vOut[0] = m[0] * p[0] + m[3] * p[1] + m[6] * p[2];
		vOut[1] = m[1] * p[0] + m[4] * p[1] + m[7] * p[2];
		vOut[2] = m[2] * p[0] + m[5] * p[1] + m[8] * p[2];
	}


	// Create a Scaling Matrix
	inline void ScaleMatrix33(Matrix33f m, float xScale, float yScale, float zScale)
	{
		LoadIdentity33(m); m[0] = xScale; m[4] = yScale; m[8] = zScale;
	}

	inline void ScaleMatrix33(Matrix33f m, const Vector3f vScale)
	{
		LoadIdentity33(m); m[0] = vScale[0]; m[4] = vScale[1]; m[8] = vScale[2];
	}

	inline void ScaleMatrix33(Matrix33d m, double xScale, double yScale, double zScale)
	{
		LoadIdentity33(m); m[0] = xScale; m[4] = yScale; m[8] = zScale;
	}

	inline void ScaleMatrix33(Matrix33d m, const Vector3d vScale)
	{
		LoadIdentity33(m); m[0] = vScale[0]; m[4] = vScale[1]; m[8] = vScale[2];
	}

	inline void ScaleMatrix44(Matrix44f m, float xScale, float yScale, float zScale)
	{
		LoadIdentity44(m); m[0] = xScale; m[5] = yScale; m[10] = zScale;
	}

	inline void ScaleMatrix44(Matrix44f m, const Vector3f vScale)
	{
		LoadIdentity44(m); m[0] = vScale[0]; m[5] = vScale[1]; m[10] = vScale[2];
	}

	inline void ScaleMatrix44(Matrix44d m, double xScale, double yScale, double zScale)
	{
		LoadIdentity44(m); m[0] = xScale; m[5] = yScale; m[10] = zScale;
	}

	inline void ScaleMatrix44(Matrix44d m, const Vector3d vScale)
	{
		LoadIdentity44(m); m[0] = vScale[0]; m[5] = vScale[1]; m[10] = vScale[2];
	}


	void MakePerspectiveMatrix(Matrix44f mProjection, float fFov, float fAspect, float zMin, float zMax);
	void MakeOrthographicMatrix(Matrix44f mProjection, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);


	// Create a Rotation matrix
	void RotationMatrix33(Matrix33f m, float angle, float x, float y, float z);
	void RotationMatrix33(Matrix33d m, double angle, double x, double y, double z);
	void RotationMatrix44(Matrix44f m, float angle, float x, float y, float z);
	void RotationMatrix44(Matrix44d m, double angle, double x, double y, double z);

	// Create a Translation matrix. Only 4x4 matrices have translation components
	inline void TranslationMatrix44(Matrix44f m, float x, float y, float z)
	{
		LoadIdentity44(m); m[12] = x; m[13] = y; m[14] = z;
	}

	inline void TranslationMatrix44(Matrix44d m, double x, double y, double z)
	{
		LoadIdentity44(m); m[12] = x; m[13] = y; m[14] = z;
	}

	void InvertMatrix44(Matrix44f mInverse, const Matrix44f m);
	void InvertMatrix44(Matrix44d mInverse, const Matrix44d m);
}

#endif