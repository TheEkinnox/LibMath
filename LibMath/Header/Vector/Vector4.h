#ifndef __LIBMATH__VECTOR__VECTOR4_H__
#define __LIBMATH__VECTOR__VECTOR4_H__

#include <string>

#include "Arithmetic.h"

namespace LibMath
{
    class Radian;

    template <class T>
    class TVector3;

    template <class T>
    class TVector4
    {
    public:
        static TVector4 zero();  // return a vector with all its component set to 0
        static TVector4 one();   // return a vector with all its component set to 1
        static TVector4 up();    // return a unit vector pointing upward
        static TVector4 down();  // return a unit vector pointing downward
        static TVector4 left();  // return a unit vector pointing left
        static TVector4 right(); // return a unit vector pointing right
        static TVector4 front(); // return a unit vector pointing forward
        static TVector4 back();  // return a unit vector pointing backward

        TVector4() = default;
        explicit TVector4(T value);   // set all the component to the same value
        TVector4(T x, T y, T z, T w); // set all components individually

        template <class U, class W>
        TVector4(const TVector3<U>& other, W w); // copy x, y, z from vector3 and use given w

        template <class U>
        TVector4(const TVector4<U>& other);

        template <class U>
        TVector4(TVector4<U>&& other);

        ~TVector4() = default;

        template <class U>
        TVector4& operator=(const TVector4<U>& other);

        template <class U>
        TVector4& operator=(TVector4<U>&& other);

        T& operator[](int index);       // return this vector component value
        T  operator[](int index) const; // return this vector component value

        template <class U>
        TVector4& operator+=(const TVector4<U>& other); // addition component wise

        template <class U>
        TVector4& operator-=(const TVector4<U>& other); // subtraction component wise

        template <class U>
        TVector4& operator*=(const TVector4<U>& other); // multiplication component wise

        template <class U>
        TVector4& operator/=(const TVector4<U>& other); // division component wise

        template <class U>
        TVector4& operator+=(U value); // add a value to all components

        template <class U>
        TVector4& operator-=(U value); // subtract a value from all components

        template <class U>
        TVector4& operator*=(U value); // multiply all components by a value

        template <class U>
        TVector4& operator/=(U value); // divide all components by a value

        T*       getArray();
        const T* getArray() const;

        TVector3<T> xyz() const; // return the x, y and z components of the TVector4 (safe slicing)

        T dot(const TVector4& other) const; // return dot product result

        template <class U>
        bool isLongerThan(const TVector4<U>&) const; // return true if this vector magnitude is greater than the other

        template <class U>
        bool isShorterThan(const TVector4<U>&) const; // return true if this vector magnitude is less than the other

        bool isUnitVector() const; // return true if this vector magnitude is 1

        T magnitude() const;        // return vector magnitude
        T magnitudeSquared() const; // return square value of the vector magnitude

        void     normalize();        // scale this vector to have a magnitude of 1
        TVector4 normalized() const; // returns this vector scaled to have a magnitude of 1

        void rotate(const Radian&, const Radian&, const Radian&);
        // rotate this vector using euler angle apply in the z, x, y order
        void rotate(const Radian&, const TVector3<T>&); // rotate this vector around an arbitrary axis
        //void			rotate(Quaternion const&); todo quaternion		// rotate this vector using a quaternion rotor

        void scale(const TVector3<T>&); // scale this vector by a given factor

        void translate(const TVector3<T>&); // offset this vector by a given distance

        std::string string() const;     // return a string representation of this vector
        std::string stringLong() const; // return a verbose string representation of this vector

        T m_x = 0;
        T m_y = 0;
        T m_z = 0;
        T m_w = 0;
    };

    template <class T, class U>
    bool operator==(const TVector4<T>& left, const TVector4<U>& right);
    // TVector4{ 1 } == TVector4::one()					// true						// return whether 2 vectors have the same components

    template <class T, class U>
    bool operator!=(const TVector4<T>& left, const TVector4<U>& right);
    // TVector4{ 1 } != TVector4::zero()					// true						// return whether 2 vectors have different components

    template <class T, class U>
    bool operator>(const TVector4<T>& left, const TVector4<U>& right);
    // TVector4{ 2 } > TVector4::one()					// true						// return whether the left vector's magnitude is greater than the right vector's magnitude

    template <class T, class U>
    bool operator<(const TVector4<T>& left, const TVector4<U>& right);
    // TVector4::zero() < TVector4{ 1 }					// true						// return whether the left vector's magnitude is smaller than the right vector's magnitude

    template <class T, class U>
    bool operator>=(const TVector4<T>& left, const TVector4<U>& right);
    // TVector4{ 1 } == TVector4::one()					// true						// return whether the left vector's magnitude is greater than or equal to the right vector's magnitude

    template <class T, class U>
    bool operator<=(const TVector4<T>& left, const TVector4<U>& right);
    // TVector4{ 1 } != TVector4::zero()					// true						// return whether the left vector's magnitude is smaller than or equal to the right vector's magnitude

    template <class T>
    TVector4<T> operator-(const TVector4<T>& vector);
    // -TVector4{ .5, 1.5, -2.5, 0 }						// { -.5, -1.5, 2.5, 0 }	// return a copy of a vector with all its component inverted

    template <class T, class U>
    TVector4<T> operator+(TVector4<T> left, const TVector4<U>& right);
    // TVector4{ .5, 1.5, -2.5, 0 } + TVector4::one()		// { 1.5, 2.5, -1.5, 1 }	// add 2 vectors component wise

    template <class T, class U>
    TVector4<T> operator-(TVector4<T> left, const TVector4<U>& right);
    // TVector4{ .5, 1.5, -2.5, 1 } - TVector4{ 1 }		// { -.5, .5, -3.5, 0 }		// subtract 2 vectors component wise

    template <class T, class U>
    TVector4<T> operator*(TVector4<T> left, const TVector4<U>& right);
    // TVector4{ .5, 1.5, -2.5, 1 } * TVector4::zero()	// { 0, 0, 0, 0 }			// multiply 2 vectors component wise

    template <class T, class U>
    TVector4<T> operator/(TVector4<T> left, const TVector4<U>& right);
    // TVector4{ .5, 1.5, -2.5, 0 } / TVector4{ 2 }		// { .25, .75, -1.25, 0 }	// divide 2 vectors component wise

    template <class T, class U>
    TVector4<T> operator+(TVector4<T> vector, U value);
    // TVector4{ .5, 1.5, -2.5, 0 } + 1					// { 1.5, 2.5, -1.5, 1 }	// add a value to all components of a vector

    template <class T, class U>
    TVector4<T> operator-(TVector4<T> vector, U value);
    // TVector4{ .5, 1.5, -2.5, 1 } - 1					// { -.5, .5, -3.5, 0 }		// subtract a value from all components of a vector

    template <class T, class U>
    TVector4<T> operator*(TVector4<T> vector, U scalar);
    // TVector4{ .5, 1.5, -2.5, 1 } * 0					// { 0, 0, 0, 0 }			// multiply all components of a vector by a value

    template <class T, class U>
    TVector4<U> operator*(U scalar, TVector4<T> vector);
    // 0 * TVector4{ .5, 1.5, -2.5, 1 }					// { 0, 0, 0, 0 }			// multiply all components of a vector by a value

    template <class T, class U>
    TVector4<T> operator/(TVector4<T> vector, U scalar);
    // TVector4{ .5, 1.5, -2.5, 0 } / 2					// { .25, .75, -1.25, 0 }	// divide all components of a vector by a value

    template <class T>
    std::ostream& operator<<(std::ostream& stream, const TVector4<T>& vector);
    // add a vector string representation to an output stream

    template <class T>
    std::istream& operator>>(std::istream& stream, TVector4<T>& vector);
    // parse a string representation from an input stream into a vector

    using Vector4 = TVector4<float>;
    using Vector4I = TVector4<int>;

    template <>
    inline Vector4 clamp<Vector4>(const Vector4 value, const Vector4 a, const Vector4 b)
    {
        return
        {
            clamp(value.m_x, a.m_x, b.m_x),
            clamp(value.m_y, a.m_y, b.m_y),
            clamp(value.m_z, a.m_z, b.m_z),
            clamp(value.m_w, a.m_w, b.m_w)
        };
    }

    template <>
    inline Vector4 snap<Vector4>(const Vector4 value, const Vector4 a, const Vector4 b)
    {
        return
        {
            snap(value.m_x, a.m_x, b.m_x),
            snap(value.m_y, a.m_y, b.m_y),
            snap(value.m_z, a.m_z, b.m_z),
            snap(value.m_w, a.m_w, b.m_w)
        };
    }

    template <>
    constexpr bool isInRange<Vector4>(const Vector4 value, const Vector4 a, const Vector4 b)
    {
        return isInRange(value.m_x, a.m_x, b.m_x)
            && isInRange(value.m_y, a.m_y, b.m_y)
            && isInRange(value.m_z, a.m_z, b.m_z)
            && isInRange(value.m_w, a.m_w, b.m_w);
    }

    template <>
    inline Vector4 min<Vector4>(const Vector4 a, const Vector4 b)
    {
        return {
            min(a.m_x, b.m_x),
            min(a.m_y, b.m_y),
            min(a.m_z, b.m_z),
            min(a.m_w, b.m_w)
        };
    }

    template <>
    inline Vector4 max<Vector4>(const Vector4 a, const Vector4 b)
    {
        return {
            max(a.m_x, b.m_x),
            max(a.m_y, b.m_y),
            max(a.m_z, b.m_z),
            max(a.m_w, b.m_w)
        };
    }

    template <>
    inline Vector4I clamp<Vector4I>(const Vector4I value, const Vector4I a, const Vector4I b)
    {
        return
        {
            clamp(value.m_x, a.m_x, b.m_x),
            clamp(value.m_y, a.m_y, b.m_y),
            clamp(value.m_z, a.m_z, b.m_z),
            clamp(value.m_w, a.m_w, b.m_w)
        };
    }

    template <>
    inline Vector4I snap<Vector4I>(const Vector4I value, const Vector4I a, const Vector4I b)
    {
        return
        {
            snap(value.m_x, a.m_x, b.m_x),
            snap(value.m_y, a.m_y, b.m_y),
            snap(value.m_z, a.m_z, b.m_z),
            snap(value.m_w, a.m_w, b.m_w)
        };
    }

    template <>
    constexpr bool isInRange<Vector4I>(const Vector4I value, const Vector4I a, const Vector4I b)
    {
        return isInRange(value.m_x, a.m_x, b.m_x)
            && isInRange(value.m_y, a.m_y, b.m_y)
            && isInRange(value.m_z, a.m_z, b.m_z)
            && isInRange(value.m_w, a.m_w, b.m_w);
    }

    template <>
    inline Vector4I min<Vector4I>(const Vector4I a, const Vector4I b)
    {
        return {
            min(a.m_x, b.m_x),
            min(a.m_y, b.m_y),
            min(a.m_z, b.m_z),
            min(a.m_w, b.m_w)
        };
    }

    template <>
    inline Vector4I max<Vector4I>(const Vector4I a, const Vector4I b)
    {
        return {
            max(a.m_x, b.m_x),
            max(a.m_y, b.m_y),
            max(a.m_z, b.m_z),
            max(a.m_w, b.m_w)
        };
    }
}

#include "Vector/Vector4.inl"

#ifdef __LIBMATH__MATRIX__MATRIX4_H__
#include "Matrix4Vector4Operation.h"
#endif // __LIBMATH__MATRIX__MATRIX4_H__

#endif // !__LIBMATH__VECTOR__VECTOR4_H__
