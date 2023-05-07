#ifndef __LIBMATH__MATRIX__MATRIX4_H__
#define __LIBMATH__MATRIX__MATRIX4_H__

#include "TMatrix.h"

namespace LibMath
{
	class Radian;
	class Vector3;

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	translation(DataT x, DataT y, DataT z);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	translation(const Vector3& translation);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	scaling(DataT x, DataT y, DataT z);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	scaling(const Vector3& scale);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	rotation(const Radian& angle, const Vector3& axis);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	rotation(const Radian& yaw, const Radian& pitch, const Radian& roll);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	rotation(const Vector3& angles, bool isRadian);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	rotationEuler(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	rotationEuler(const Vector3& angles, bool isRadian);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	rotationFromTo(const Vector3& from, const Vector3& to);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	orthographicProjection(DataT left, DataT right, DataT bottom, DataT top, DataT zNear, DataT zFar);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	perspectiveProjection(const Radian& fovY, DataT aspect, DataT zNear, DataT zFar);

	template <class DataT = float>
	constexpr TMatrix<4, 4, DataT>	lookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

	typedef TMatrix<4, 2, float> Matrix4x2;

	typedef TMatrix<4, 3, float> Matrix4x3;

	typedef TMatrix<4, 4, float> Matrix4x4;
	typedef Matrix4x4 Matrix4;
}

#ifdef __LIBMATH__VECTOR__VECTOR4_H__
#include "Matrix4Vector4Operation.h"
#endif // __LIBMATH__MATRIX_H__

#include "Matrix4.inl"

#endif // !__LIBMATH__MATRIX__MATRIX4_H__
