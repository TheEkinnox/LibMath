#ifndef __LIBMATH__VECTOR__VECTOR3_H__
#define __LIBMATH__VECTOR__VECTOR3_H__

#include <iostream>
#include <string>

#include "Arithmetic.h"

#include "Angle/Radian.h"

namespace LibMath
{
    template <class T>
    class TVector3
    {
    public:
        static TVector3 zero();  // return a vector with all its component set to 0
        static TVector3 one();   // return a vector with all its component set to 1
        static TVector3 up();    // return a unit vector pointing upward
        static TVector3 down();  // return a unit vector pointing downward
        static TVector3 left();  // return a unit vector pointing left
        static TVector3 right(); // return a unit vector pointing right
        static TVector3 front(); // return a unit vector pointing forward
        static TVector3 back();  // return a unit vector pointing backward

        TVector3() = default;

        /**
         * \brief Creates a vector with the same value for all it's components
         */
        explicit TVector3(T); // set all the component to the same value
        TVector3(T, T, T);    // set all component individually

        template <class U>
        TVector3(const TVector3<U>& other);

        template <class U>
        TVector3(TVector3<U>&& other);

        ~TVector3() = default;

        template <class U>
        TVector3& operator=(const TVector3<U>& other);

        template <class U>
        TVector3& operator=(TVector3<U>&& other);

        T& operator[](int);       // return this vector component value
        T  operator[](int) const; // return this vector component value

        template <class U>
        TVector3& operator+=(const TVector3<U>& other); // addition component wise

        template <class U>
        TVector3& operator-=(const TVector3<U>& other); // subtraction component wise

        template <class U>
        TVector3& operator*=(const TVector3<U>& other); // multiplication component wise

        template <class U>
        TVector3& operator/=(const TVector3<U>& other); // division component wise

        template <class U>
        TVector3& operator+=(U); // add a value to all components

        template <class U>
        TVector3& operator-=(U); // subtract a value from all components

        template <class U>
        TVector3& operator*=(U); // multiply all components by a value

        template <class U>
        TVector3& operator/=(U); // divide all components by a value

        T*       getArray();
        const T* getArray() const;

        Radian angleFrom(const TVector3& other) const; // return smallest angle between 2 vectors
        Radian signedAngleFrom(const TVector3& other,
                               const TVector3& axis) const; // return signed angle between 2 vectors around

        TVector3 cross(const TVector3&) const; // return a copy of the cross product result

        T distanceFrom(const TVector3&) const;        // return distance between 2 points
        T distanceSquaredFrom(const TVector3&) const; // return square value of the distance between 2 points
        T distance2DFrom(const TVector3&) const;      // return the distance between 2 points on the X-Y axis only
        T distance2DSquaredFrom(const TVector3&) const;
        // return the square value of the distance between 2 points points on the X-Y axis only

        T dot(const TVector3&) const; // return dot product result

        template <class U>
        bool isLongerThan(const TVector3<U>&) const; // return true if this vector magnitude is greater than the other

        template <class U>
        bool isShorterThan(const TVector3<U>&) const; // return true if this vector magnitude is less than the other

        bool isUnitVector() const; // return true if this vector magnitude is 1

        T magnitude() const;        // return vector magnitude
        T magnitudeSquared() const; // return square value of the vector magnitude

        void     normalize();        // scale this vector to have a magnitude of 1
        TVector3 normalized() const; // returns this vector scaled to have a magnitude of 1

        void projectOnto(const TVector3&); // project this vector onto an other

        void reflectOnto(const TVector3&); // reflect this vector by an other

        void rotate(const Radian&, const Radian&,
                    const Radian&);                  // rotate this vector using euler angle apply in the z, x, y order
        void rotate(const Radian&, const TVector3&); // rotate this vector around an arbitrary axis
        //void			rotate(Quaternion const&); todo quaternion		// rotate this vector using a quaternion rotor

        void scale(const TVector3&); // scale this vector by a given factor

        void translate(const TVector3&); // offset this vector by a given distance

        std::string string() const;     // return a string representation of this vector
        std::string stringLong() const; // return a verbose string representation of this vector

        T m_x = 0;
        T m_y = 0;
        T m_z = 0;
    };

    template <class T, class U>
    bool operator==(const TVector3<T>&, const TVector3<U>&);
    // TVector3{ 1 } == TVector3::one()				// true					// return whether 2 vectors have the same components

    template <class T, class U>
    bool operator!=(const TVector3<T>&, const TVector3<U>&);
    // TVector3{ 1 } != TVector3::zero()				// true					// return whether 2 vectors have different components

    template <class T, class U>
    bool operator>(const TVector3<T>&, const TVector3<U>&);
    // TVector3{ 2 } > TVector3::one()				// true					// return whether the left vector's magnitude is greater than the right vector's magnitude

    template <class T, class U>
    bool operator<(const TVector3<T>&, const TVector3<U>&);
    // TVector3::zero() < TVector3{ 1 }				// true					// return whether the left vector's magnitude is smaller than the right vector's magnitude

    template <class T, class U>
    bool operator>=(const TVector3<T>&, const TVector3<U>&);
    // TVector3{ 1 } == TVector3::one()				// true					// return whether the left vector's magnitude is greater than or equal to the right vector's magnitude

    template <class T, class U>
    bool operator<=(const TVector3<T>&, const TVector3<U>&);
    // TVector3{ 1 } != TVector3::zero()				// true					// return whether the left vector's magnitude is smaller than or equal to the right vector's magnitude

    template <class T>
    TVector3<T> operator-(const TVector3<T>&);
    // -TVector3{ .5, 1.5, -2.5 }					// { -.5, -1.5, 2.5 }	// return a copy of a vector with all its component inverted

    template <class T, class U>
    TVector3<T> operator+(TVector3<T>, const TVector3<U>&);
    // TVector3{ .5, 1.5, -2.5 } + TVector3::one()	// { 1.5, 2.5, -1.5 }	// add 2 vectors component wise

    template <class T, class U>
    TVector3<T> operator-(TVector3<T>, const TVector3<U>&);
    // TVector3{ .5, 1.5, -2.5 } - TVector3{ 1 }		// { -.5, .5, -3.5 }	// subtract 2 vectors component wise

    template <class T, class U>
    TVector3<T> operator*(TVector3<T>, const TVector3<U>&);
    // TVector3{ .5, 1.5, -2.5 } * TVector3::zero()	// { 0, 0, 0 }			// multiply 2 vectors component wise

    template <class T, class U>
    TVector3<T> operator/(TVector3<T>, const TVector3<U>&);
    // TVector3{ .5, 1.5, -2.5 } / TVector3{ 2 }		// { .25, .75, -1.25 }	// divide 2 vectors component wise

    template <class T, class U>
    TVector3<T> operator+(TVector3<T>, U);
    // TVector3{ .5, 1.5, -2.5 } + 1					// { 1.5, 2.5, -1.5 }	// add a value to all components of a vector

    template <class T, class U>
    TVector3<T> operator-(TVector3<T>, U);
    // TVector3{ .5, 1.5, -2.5 } - 1					// { -.5, .5, -3.5 }	// subtract a value from all components of a vector

    template <class T, class U>
    TVector3<T> operator*(TVector3<T>, U);
    // TVector3{ .5, 1.5, -2.5 } * 0					// { 0, 0, 0 }			// multiply all components of a vector by a value

    template <class T, class U>
    TVector3<U> operator*(U, TVector3<T>);
    // 0 * TVector3{ .5, 1.5, -2.5 }					// { 0, 0, 0 }			// multiply all components of a vector by a value

    template <class T, class U>
    TVector3<T> operator/(TVector3<T>, U);
    // TVector3{ .5, 1.5, -2.5 } / 2					// { .25, .75, -1.25 }	// divide all components of a vector by a value

    /**
     * \brief Adds a vector string representation to an output stream
     * \tparam T The vector's data type
     * \param stream The input stream
     * \param vect The output vector
     * \return The modified stream
     */
    template <class T>
    std::ostream& operator<<(std::ostream& stream, const TVector3<T>& vect);

    /**
     * \brief Parses a string representation from an input stream into a vector
     * \tparam T The vector's data type
     * \param stream The input stream
     * \param vect The output vector
     * \return The modified stream
     */
    template <class T>
    std::istream& operator>>(std::istream& stream, TVector3<T>& vect);

    using Vector3 = TVector3<float>;
    using Vector3I = TVector3<int>;

    template <>
    inline Vector3 clamp<Vector3>(const Vector3 value, const Vector3 a, const Vector3 b)
    {
        return
        {
            clamp(value.m_x, a.m_x, b.m_x),
            clamp(value.m_y, a.m_y, b.m_y),
            clamp(value.m_z, a.m_z, b.m_z)
        };
    }

    template <>
    inline Vector3 snap<Vector3>(const Vector3 value, const Vector3 a, const Vector3 b)
    {
        return
        {
            snap(value.m_x, a.m_x, b.m_x),
            snap(value.m_y, a.m_y, b.m_y),
            snap(value.m_z, a.m_z, b.m_z)
        };
    }

    template <>
    constexpr bool isInRange<Vector3>(const Vector3 value, const Vector3 a, const Vector3 b)
    {
        return isInRange(value.m_x, a.m_x, b.m_x)
            && isInRange(value.m_y, a.m_y, b.m_y)
            && isInRange(value.m_z, a.m_z, b.m_z);
    }

    template <>
    inline Vector3 min<Vector3>(const Vector3 a, const Vector3 b)
    {
        return {
            min(a.m_x, b.m_x),
            min(a.m_y, b.m_y),
            min(a.m_z, b.m_z)
        };
    }

    template <>
    inline Vector3 max<Vector3>(const Vector3 a, const Vector3 b)
    {
        return {
            max(a.m_x, b.m_x),
            max(a.m_y, b.m_y),
            max(a.m_z, b.m_z)
        };
    }

    template <>
    inline Vector3I clamp<Vector3I>(const Vector3I value, const Vector3I a, const Vector3I b)
    {
        return
        {
            clamp(value.m_x, a.m_x, b.m_x),
            clamp(value.m_y, a.m_y, b.m_y),
            clamp(value.m_z, a.m_z, b.m_z)
        };
    }

    template <>
    inline Vector3I snap<Vector3I>(const Vector3I value, const Vector3I a, const Vector3I b)
    {
        return
        {
            snap(value.m_x, a.m_x, b.m_x),
            snap(value.m_y, a.m_y, b.m_y),
            snap(value.m_z, a.m_z, b.m_z)
        };
    }

    template <>
    constexpr bool isInRange<Vector3I>(const Vector3I value, const Vector3I a, const Vector3I b)
    {
        return isInRange(value.m_x, a.m_x, b.m_x)
            && isInRange(value.m_y, a.m_y, b.m_y)
            && isInRange(value.m_z, a.m_z, b.m_z);
    }

    template <>
    inline Vector3I min<Vector3I>(const Vector3I a, const Vector3I b)
    {
        return {
            min(a.m_x, b.m_x),
            min(a.m_y, b.m_y),
            min(a.m_z, b.m_z)
        };
    }

    template <>
    inline Vector3I max<Vector3I>(const Vector3I a, const Vector3I b)
    {
        return {
            max(a.m_x, b.m_x),
            max(a.m_y, b.m_y),
            max(a.m_z, b.m_z)
        };
    }
}

#include "Vector/Vector3.inl"

#endif // !__LIBMATH__VECTOR__VECTOR3_H__
