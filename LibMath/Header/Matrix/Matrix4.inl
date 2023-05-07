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
		TMatrix<4, 4, DataT> translationMatrix(1);

		translationMatrix(0, 3) = x;
		translationMatrix(1, 3) = y;
		translationMatrix(2, 3) = z;

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

		scalingMatrix(0, 0) = x;
		scalingMatrix(1, 1) = y;
		scalingMatrix(2, 2) = z;
		scalingMatrix(3, 3) = 1;

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
		const DataT cos = LibMath::cos(angle);
		const DataT sin = LibMath::sin(angle);

		TMatrix<4, 4, DataT> mat;

		mat(0, 0) = cos + dir.m_x * dir.m_x * (1 - cos);
		mat(0, 1) = dir.m_x * dir.m_y * (1 - cos) - dir.m_z * sin;
		mat(0, 2) = dir.m_x * dir.m_z * (1 - cos) + dir.m_y * sin;
		mat(0, 3) = 0;

		mat(1, 0) = dir.m_y * dir.m_x * (1 - cos) + dir.m_z * sin;
		mat(1, 1) = cos + dir.m_y * dir.m_y * (1 - cos);
		mat(1, 2) = dir.m_y * dir.m_z * (1 - cos) - dir.m_x * sin;
		mat(1, 3) = 0;

		mat(2, 0) = dir.m_z * dir.m_x * (1 - cos) - dir.m_y * sin;
		mat(2, 1) = dir.m_z * dir.m_y * (1 - cos) + dir.m_x * sin;
		mat(2, 2) = cos + dir.m_z * dir.m_z * (1 - cos);
		mat(2, 3) = 0;

		mat(3, 0) = 0;
		mat(3, 1) = 0;
		mat(3, 2) = 0;
		mat(3, 3) = 1;

		return mat;
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> rotation(const Radian& yaw, const Radian& pitch,
		const Radian& roll)
	{
		const DataT cosYaw = cos(yaw);
		const DataT sinYaw = sin(yaw);

		const DataT cosPitch = cos(pitch);
		const DataT sinPitch = sin(pitch);

		const DataT cosRoll = cos(roll);
		const DataT sinRoll = sin(roll);

		TMatrix<4, 4, DataT> rotationMat;

		rotationMat(0, 0) = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
		rotationMat(0, 1) = -cosYaw * sinRoll + sinYaw * sinPitch * cosRoll;
		rotationMat(0, 2) = sinYaw * cosPitch;
		rotationMat(0, 3) = 0;

		rotationMat(1, 0) = sinRoll * cosPitch;
		rotationMat(1, 1) = cosRoll * cosPitch;
		rotationMat(1, 2) = -sinPitch;
		rotationMat(1, 3) = 0;

		rotationMat(2, 0) = -sinYaw * cosRoll + cosYaw * sinPitch * sinRoll;
		rotationMat(2, 1) = sinRoll * sinYaw + cosYaw * sinPitch * cosRoll;
		rotationMat(2, 2) = cosYaw * cosPitch;
		rotationMat(2, 3) = 0;

		rotationMat(3, 0) = 0;
		rotationMat(3, 1) = 0;
		rotationMat(3, 2) = 0;
		rotationMat(3, 3) = 1;

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
			return TMatrix<4, 4, DataT>(1);

		if (toDir == -fromDir)
			return scaling<DataT>(-1, -1, -1);

		const Vector3 axis = from.cross(to);

		const DataT cosA = from.dot(to);
		const DataT k = static_cast<DataT>(1) / (static_cast<DataT>(1) + cosA);

		TMatrix<4, 4, DataT> rotationMat;

		rotationMat(0, 0) = (axis.m_x * axis.m_x * k) + cosA;
		rotationMat(0, 1) = (axis.m_y * axis.m_x * k) - axis.m_z;
		rotationMat(0, 2) = (axis.m_z * axis.m_x * k) + axis.m_y;
		rotationMat(0, 3) = static_cast<DataT>(0);

		rotationMat(1, 0) = (axis.m_x * axis.m_y * k) + axis.m_z;
		rotationMat(1, 1) = (axis.m_y * axis.m_y * k) + cosA;
		rotationMat(1, 2) = (axis.m_z * axis.m_y * k) - axis.m_x;
		rotationMat(1, 3) = static_cast<DataT>(0);

		rotationMat(2, 0) = (axis.m_x * axis.m_z * k) - axis.m_y;
		rotationMat(2, 1) = (axis.m_y * axis.m_z * k) + axis.m_x;
		rotationMat(2, 2) = (axis.m_z * axis.m_z * k) + cosA;
		rotationMat(2, 3) = static_cast<DataT>(0);

		rotationMat(3, 0) = static_cast<DataT>(0);
		rotationMat(3, 1) = static_cast<DataT>(0);
		rotationMat(3, 2) = static_cast<DataT>(0);
		rotationMat(3, 3) = static_cast<DataT>(1);

		return rotationMat;
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> orthographicProjection(const DataT left, const DataT right,
		const DataT bottom, const DataT top, const DataT zNear, const DataT zFar)
	{
		TMatrix<4, 4, DataT> mat;

		mat(0, 0) = static_cast<DataT>(2) / (right - left);
		mat(0, 3) = (right + left) / (left - right);

		mat(1, 1) = static_cast<DataT>(2) / (top - bottom);
		mat(1, 3) = (top + bottom) / (bottom - top);

		mat(2, 2) = static_cast<DataT>(2) / (zNear - zFar);
		mat(2, 3) = (zFar + zNear) / (zNear - zFar);

		mat(3, 3) = static_cast<DataT>(1);

		return mat;
	}

	template <class DataT>
	constexpr TMatrix<4, 4, DataT> perspectiveProjection(const Radian& fovY,
		const DataT aspect, const DataT zNear, const DataT zFar)
	{
		const DataT tanHalfFovY = tan(fovY * .5f);

		TMatrix<4, 4, DataT> mat;

		mat(0, 0) = static_cast<DataT>(1) / (aspect * tanHalfFovY);
		mat(1, 1) = static_cast<DataT>(1) / tanHalfFovY;
		mat(2, 2) = (zFar + zNear) / (zNear - zFar);
		mat(2, 3) = (static_cast<DataT>(2) * zFar * zNear) / (zNear - zFar);
		mat(3, 2) = static_cast<DataT>(-1);

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

		mat(0, 0) = s.m_x;
		mat(0, 1) = s.m_y;
		mat(0, 2) = s.m_z;
		mat(0, 3) = -s.dot(eye);

		mat(1, 0) = u.m_x;
		mat(1, 1) = u.m_y;
		mat(1, 2) = u.m_z;
		mat(1, 3) = -u.dot(eye);

		mat(2, 0) = -f.m_x;
		mat(2, 1) = -f.m_y;
		mat(2, 2) = -f.m_z;
		mat(2, 3) = f.dot(eye);

		mat(3, 3) = 1;

		return mat;
	}
}

#endif // !__LIBMATH__MATRIX__MATRIX4_INL__
