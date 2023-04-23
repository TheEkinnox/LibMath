#ifndef __LIBMATH__MATRIX__MATRIX4_INL__
#define __LIBMATH__MATRIX__MATRIX4_INL__

#include "Vector/Vector3.h"
#include "Matrix4.h"
#include "Angle.h"
#include "Trigonometry.h"

namespace LibMath
{

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> translation(const DataT x, const DataT y, const DataT z)
	{
		TMatrix<4, 4, DataT> translationMatrix(1.f);

		translationMatrix[translationMatrix.getIndex(0, 3)] = x;
		translationMatrix[translationMatrix.getIndex(1, 3)] = y;
		translationMatrix[translationMatrix.getIndex(2, 3)] = z;

		return translationMatrix;
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> translation(const Vector3& translation)
	{
		return LibMath::translation(translation.m_x, translation.m_y, translation.m_z);
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> scaling(const DataT x, const DataT y, const DataT z)
	{
		TMatrix<4, 4, DataT> scalingMatrix;

		scalingMatrix[scalingMatrix.getIndex(0, 0)] = x;
		scalingMatrix[scalingMatrix.getIndex(1, 1)] = y;
		scalingMatrix[scalingMatrix.getIndex(2, 2)] = z;
		scalingMatrix[scalingMatrix.getIndex(3, 3)] = 1.f;

		return scalingMatrix;
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> scaling(const Vector3& scale)
	{
		return scaling<DataT>(scale.m_x, scale.m_y, scale.m_z);
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> rotation(const Radian& angle, const Vector3& axis)
	{
		const Vector3 dir = axis.normalized();
		const float cos = LibMath::cos(angle);
		const float sin = LibMath::sin(angle);

		TMatrix<4, 4, DataT> mat;

		mat[mat.getIndex(0, 0)] = cos + dir.m_x * dir.m_x * (1.f - cos);
		mat[mat.getIndex(0, 1)] = dir.m_x * dir.m_y * (1 - cos) - dir.m_z * sin;
		mat[mat.getIndex(0, 2)] = dir.m_x * dir.m_z * (1 - cos) + dir.m_y * sin;
		mat[mat.getIndex(0, 3)] = 0.f;

		mat[mat.getIndex(1, 0)] = dir.m_y * dir.m_x * (1 - cos) + dir.m_z * sin;
		mat[mat.getIndex(1, 1)] = cos + dir.m_y * dir.m_y * (1.f - cos);
		mat[mat.getIndex(1, 2)] = dir.m_y * dir.m_z * (1 - cos) - dir.m_x * sin;
		mat[mat.getIndex(1, 3)] = 0.f;

		mat[mat.getIndex(2, 0)] = dir.m_z * dir.m_x * (1 - cos) - dir.m_y * sin;
		mat[mat.getIndex(2, 1)] = dir.m_z * dir.m_y * (1 - cos) + dir.m_x * sin;
		mat[mat.getIndex(2, 2)] = cos + dir.m_z * dir.m_z * (1.f - cos);
		mat[mat.getIndex(2, 3)] = 0.f;

		mat[mat.getIndex(3, 0)] = 0.f;
		mat[mat.getIndex(3, 1)] = 0.f;
		mat[mat.getIndex(3, 2)] = 0.f;
		mat[mat.getIndex(3, 3)] = 1.f;

		return mat;
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> rotation(const Radian& yaw, const Radian& pitch,
		const Radian& roll)
	{
		const float cosYaw = cos(yaw);
		const float sinYaw = sin(yaw);

		const float cosPitch = cos(pitch);
		const float sinPitch = sin(pitch);

		const float cosRoll = cos(roll);
		const float sinRoll = sin(roll);

		TMatrix<4, 4, DataT> rotationMat;

		rotationMat[rotationMat.getIndex(0, 0)] = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
		rotationMat[rotationMat.getIndex(0, 1)] = -cosYaw * sinRoll + sinYaw * sinPitch * cosRoll;
		rotationMat[rotationMat.getIndex(0, 2)] = sinYaw * cosPitch;
		rotationMat[rotationMat.getIndex(0, 3)] = 0.f;

		rotationMat[rotationMat.getIndex(1, 0)] = sinRoll * cosPitch;
		rotationMat[rotationMat.getIndex(1, 1)] = cosRoll * cosPitch;
		rotationMat[rotationMat.getIndex(1, 2)] = -sinPitch;
		rotationMat[rotationMat.getIndex(1, 3)] = 0.f;

		rotationMat[rotationMat.getIndex(2, 0)] = -sinYaw * cosRoll + cosYaw * sinPitch * sinRoll;
		rotationMat[rotationMat.getIndex(2, 1)] = sinRoll * sinYaw + cosYaw * sinPitch * cosRoll;
		rotationMat[rotationMat.getIndex(2, 2)] = cosYaw * cosPitch;
		rotationMat[rotationMat.getIndex(2, 3)] = 0.f;

		rotationMat[rotationMat.getIndex(3, 0)] = 0.f;
		rotationMat[rotationMat.getIndex(3, 1)] = 0.f;
		rotationMat[rotationMat.getIndex(3, 2)] = 0.f;
		rotationMat[rotationMat.getIndex(3, 3)] = 1.f;

		return rotationMat;
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> rotation(const Vector3& angles, const bool isRadian)
	{
		if (isRadian)
			return rotation<DataT>(Radian(angles.m_y), Radian(angles.m_x), Radian(angles.m_z));

		return rotation<DataT>(Degree(angles.m_y), Degree(angles.m_x), Degree(angles.m_z));
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> rotationEuler(const Radian& xAngle, const Radian& yAngle,
		const Radian& zAngle)
	{
		return rotation(zAngle, xAngle, yAngle);
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> rotationEuler(const Vector3& angles, const bool isRadian)
	{
		if (isRadian)
			return rotationEuler<DataT>(Radian(angles.m_x), Radian(angles.m_y), Radian(angles.m_z));

		return rotationEuler<DataT>(Degree(angles.m_x), Degree(angles.m_y), Degree(angles.m_z));
	}

	// Adapted from https://gist.github.com/kevinmoran/b45980723e53edeb8a5a43c49f134724
	template <class DataT>
	constexpr TMatrix<4, 4, DataT> rotationFromTo(const Vector3& from, const Vector3& to)
	{
		const auto& fromDir = from.normalized();
		const auto& toDir = to.normalized();

		if (toDir == fromDir)
			return TMatrix<4, 4, DataT>(1.f);

		if (toDir == -fromDir)
			return scaling<DataT>(-1.f, -1.f, -1.f);

		const Vector3 axis = from.cross(to);

		const float cosA = from.dot(to);
		const float k = 1.0f / (1.0f + cosA);

		TMatrix<4, 4, DataT> rotationMat;

		rotationMat[rotationMat.getIndex(0, 0)] = (axis.m_x * axis.m_x * k) + cosA;
		rotationMat[rotationMat.getIndex(0, 1)] = (axis.m_y * axis.m_x * k) - axis.m_z;
		rotationMat[rotationMat.getIndex(0, 2)] = (axis.m_z * axis.m_x * k) + axis.m_y;
		rotationMat[rotationMat.getIndex(0, 3)] = 0.f;

		rotationMat[rotationMat.getIndex(1, 0)] = (axis.m_x * axis.m_y * k) + axis.m_z;
		rotationMat[rotationMat.getIndex(1, 1)] = (axis.m_y * axis.m_y * k) + cosA;
		rotationMat[rotationMat.getIndex(1, 2)] = (axis.m_z * axis.m_y * k) - axis.m_x;
		rotationMat[rotationMat.getIndex(1, 3)] = 0.f;

		rotationMat[rotationMat.getIndex(2, 0)] = (axis.m_x * axis.m_z * k) - axis.m_y;
		rotationMat[rotationMat.getIndex(2, 1)] = (axis.m_y * axis.m_z * k) + axis.m_x;
		rotationMat[rotationMat.getIndex(2, 2)] = (axis.m_z * axis.m_z * k) + cosA;
		rotationMat[rotationMat.getIndex(2, 3)] = 0.f;

		rotationMat[rotationMat.getIndex(3, 0)] = 0.f;
		rotationMat[rotationMat.getIndex(3, 1)] = 0.f;
		rotationMat[rotationMat.getIndex(3, 2)] = 0.f;
		rotationMat[rotationMat.getIndex(3, 3)] = 1.f;

		return rotationMat;
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> orthographicProjection(const DataT left, const DataT right,
		const DataT bottom, const DataT top, const DataT near, const DataT far)
	{
		TMatrix<4, 4, DataT> mat;

		mat[mat.getIndex(0, 0)] = 2.f / (right - left);
		mat[mat.getIndex(0, 3)] = (right + left) / (left - right);

		mat[mat.getIndex(1, 1)] = 2.f / (top - bottom);
		mat[mat.getIndex(1, 3)] = (top + bottom) / (bottom - top);

		mat[mat.getIndex(2, 2)] = 2.f / (near - far);
		mat[mat.getIndex(2, 3)] = (far + near) / (near - far);

		mat[mat.getIndex(3, 3)] = 1.f;

		return mat;
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> perspectiveProjection(const Radian& fovY,
		const DataT aspect, const DataT near, const DataT far)
	{
		const DataT tanHalfFovY = tan(fovY * .5f);

		TMatrix<4, 4, DataT> mat;

		mat[mat.getIndex(0, 0)] = 1.f / (aspect * tanHalfFovY);
		mat[mat.getIndex(1, 1)] = 1.f / tanHalfFovY;
		mat[mat.getIndex(2, 2)] = (far + near) / (near - far);
		mat[mat.getIndex(2, 3)] = (2.f * far * near) / (near - far);
		mat[mat.getIndex(3, 2)] = -1.f;

		return mat;
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> lookAt(const Vector3& eye, const Vector3& center,
		const Vector3& up)
	{
		const Vector3 f = (center - eye).normalized();
		const Vector3 s = f.cross(up).normalized();
		const Vector3 u = s.cross(f);

		TMatrix<4, 4, DataT> mat;

		mat[mat.getIndex(0, 0)] = s.m_x;
		mat[mat.getIndex(0, 1)] = s.m_y;
		mat[mat.getIndex(0, 2)] = s.m_z;
		mat[mat.getIndex(0, 3)] = -s.dot(eye);

		mat[mat.getIndex(1, 0)] = u.m_x;
		mat[mat.getIndex(1, 1)] = u.m_y;
		mat[mat.getIndex(1, 2)] = u.m_z;
		mat[mat.getIndex(1, 3)] = -u.dot(eye);

		mat[mat.getIndex(2, 0)] = -f.m_x;
		mat[mat.getIndex(2, 1)] = -f.m_y;
		mat[mat.getIndex(2, 2)] = -f.m_z;
		mat[mat.getIndex(2, 3)] = f.dot(eye);

		mat[mat.getIndex(3, 3)] = 1.f;

		return mat;
	}
}

#endif // !__LIBMATH__MATRIX__MATRIX4_INL__
