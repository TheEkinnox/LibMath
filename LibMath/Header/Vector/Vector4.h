#ifndef __LIBMATH__VECTOR__VECTOR4_H__
#define __LIBMATH__VECTOR__VECTOR4_H__

#include <iostream>
#include <string>

#include "Vector3.h"

namespace LibMath
{
	class Radian;

	class Vector4 : public Vector3
	{
	public:
						Vector4() = default;
		explicit		Vector4(float value);									// set all the component to the same value
						Vector4(float x, float y, float z, float w);			// set all components individually
						Vector4(Vector3 const& other, float w);					// copy x, y, z from vector3 and use given w
						Vector4(Vector4 const& other) = default;
						Vector4(Vector4&& other) = default;
						~Vector4() = default;

		static Vector4	zero();													// return a vector with all its component set to 0
		static Vector4	one();													// return a vector with all its component set to 1
		static Vector4	up();													// return a unit vector pointing upward
		static Vector4	down();													// return a unit vector pointing downward
		static Vector4	left();													// return a unit vector pointing left
		static Vector4	right();												// return a unit vector pointing right
		static Vector4	front();												// return a unit vector pointing forward
		static Vector4	back();													// return a unit vector pointing backward

		Vector4&		operator=(Vector4 const& other) = default;
		Vector4&		operator=(Vector4&& other) = default;

		float&			operator[](int index);									// return this vector component value
		float			operator[](int index) const;							// return this vector component value

		Vector4&		operator+=(Vector4 const& other);						// addition component wise
		Vector4&		operator-=(Vector4 const& other);						// subtraction component wise
		Vector4&		operator*=(Vector4 const& other);						// multiplication component wise
		Vector4&		operator/=(Vector4 const& other);						// division component wise

		Vector4&		operator+=(float const& value);							// add a value to all components
		Vector4&		operator-=(float const& value);							// subtract a value from all components
		Vector4&		operator*=(float const& value);							// multiply all components by a value
		Vector4&		operator/=(float const& value);							// divide all components by a value

		Vector3			xyz() const;											// return the x, y and z components of the Vector4 (safe slicing)

		float			dot(Vector4 const& other) const;						// return dot product result

		float			magnitudeSquared() const;								// return square value of the vector magnitude

		Vector4			normalized() const;										// returns this vector scaled to have a magnitude of 1

		std::string		string() const;											// return a string representation of this vector
		std::string		stringLong() const;										// return a verbose string representation of this vector

		float m_w = 0;
	};

	bool			operator==(Vector4 const& left, Vector4 const& right);		// Vector4{ 1 } == Vector4::one()					// true						// return whether 2 vectors have the same components
	bool			operator!=(Vector4 const& left, Vector4 const& right);		// Vector4{ 1 } != Vector4::zero()					// true						// return whether 2 vectors have different components

	Vector4			operator-(const Vector4& vector);							// -Vector4{ .5, 1.5, -2.5, 0 }						// { -.5, -1.5, 2.5, 0 }	// return a copy of a vector with all its component inverted

	Vector4			operator+(Vector4 left, Vector4 const& right);				// Vector4{ .5, 1.5, -2.5, 0 } + Vector4::one()		// { 1.5, 2.5, -1.5, 1 }	// add 2 vectors component wise
	Vector4			operator-(Vector4 left, Vector4 const& right);				// Vector4{ .5, 1.5, -2.5, 1 } - Vector4{ 1 }		// { -.5, .5, -3.5, 0 }		// subtract 2 vectors component wise
	Vector4			operator*(Vector4 left, Vector4 const& right);				// Vector4{ .5, 1.5, -2.5, 1 } * Vector4::zero()	// { 0, 0, 0, 0 }			// multiply 2 vectors component wise
	Vector4			operator/(Vector4 left, Vector4 const& right);				// Vector4{ .5, 1.5, -2.5, 0 } / Vector4{ 2 }		// { .25, .75, -1.25, 0 }	// divide 2 vectors component wise

	Vector4			operator+(Vector4 vector, float const& value);				// Vector4{ .5, 1.5, -2.5, 0 } + 1					// { 1.5, 2.5, -1.5, 1 }	// add a value to all components of a vector
	Vector4			operator-(Vector4 vector, float const& value);				// Vector4{ .5, 1.5, -2.5, 1 } - 1					// { -.5, .5, -3.5, 0 }		// subtract a value from all components of a vector

	Vector4			operator*(Vector4 vector4, float const& scalar);			// Vector4{ .5, 1.5, -2.5, 1 } * 0					// { 0, 0, 0, 0 }			// multiply all components of a vector by a value
	Vector4			operator*(float const& scalar, Vector4 vector);				// 0 * Vector4{ .5, 1.5, -2.5, 1 }					// { 0, 0, 0, 0 }			// multiply all components of a vector by a value

	Vector4			operator/(Vector4 vector, float const& scalar);				// Vector4{ .5, 1.5, -2.5, 0 } / 2					// { .25, .75, -1.25, 0 }	// divide all components of a vector by a value

	std::ostream&	operator<<(std::ostream& stream, Vector4 const& vector);	// cout << Vector4{ .5, 1.5, -2.5, 1 }				// add a vector string representation to an output stream
	std::istream&	operator>>(std::istream& stream, Vector4& vector);			// ifstream file{ save.txt }; file >> vector;		// parse a string representation from an input stream into a vector
}

#ifdef __LIBMATH__MATRIX__MATRIX4_H__
#include "Matrix4Vector4Operation.h"
#endif // __LIBMATH__MATRIX__MATRIX4_H__

#endif // !__LIBMATH__VECTOR__VECTOR4_H__
