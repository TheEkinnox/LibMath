#ifndef __LIBMATH__VECTOR__VECTOR2_H__
#define __LIBMATH__VECTOR__VECTOR2_H__

#include <string>

#include "Arithmetic.h"

#include "Angle/Radian.h"

#include "Vector/Vector3.h"

namespace LibMath
{
    template <class T>
    class TVector2
    {
        static_assert(std::is_arithmetic_v<T>, "Invalid vector - Data type should be an arithmetic type");

    public:
        static TVector2 zero();  // return a vector with all its component set to 0
        static TVector2 one();   // return a vector with all its component set to 1
        static TVector2 up();    // return a unit vector pointing upward
        static TVector2 down();  // return a unit vector pointing downward
        static TVector2 left();  // return a unit vector pointing left
        static TVector2 right(); // return a unit vector pointing right

        TVector2() = default;

        /**
         * \brief Creates a vector with the same value for all it's components
         * \param value The vector's components value
         */
        explicit TVector2(T value);

        /**
         * \brief Creates a vector with the given component values
         * \param x The vector's x value
         * \param y The vector's y value
         */
        TVector2(T x, T y);

        template <class U>
        TVector2(const TVector2<U>&);

        template <class U>
        TVector2(TVector2<U>&&) noexcept;

        ~TVector2() = default;

        /**
         * \brief Implicit conversion from TVector2 to TVcetor3
         */
        operator TVector3<T>() const;

        template <class U>
        TVector2& operator=(const TVector2<U>&);

        template <class U>
        TVector2& operator=(TVector2<U>&&) noexcept;

        T& operator[](int);       // return this vector component value
        T  operator[](int) const; // return this vector component value

        template <class U>
        TVector2& operator+=(const TVector2<U>&); // addition component wise

        template <class U>
        TVector2& operator-=(const TVector2<U>&); // subtraction component wise

        template <class U>
        TVector2& operator*=(const TVector2<U>&); // multiplication component wise

        template <class U>
        TVector2& operator/=(const TVector2<U>&); // division component wise

        template <class U>
        TVector2& operator+=(U); // add a value to all components

        template <class U>
        TVector2& operator-=(U); // subtract a value from all components

        template <class U>
        TVector2& operator*=(U); // multiply all components by a value

        template <class U>
        TVector2& operator/=(U); // divide all components by a value

        T* getArray();

        const T* getArray() const;

        Radian angleFrom(const TVector2&) const;             // return smallest angle between 2 vectors
        Radian signedAngleFrom(const TVector2& other) const; // return signed angle between 2 vectors

        T cross(const TVector2&) const; // return a copy of the cross product result

        T distanceFrom(const TVector2&) const;        // return distance between 2 points
        T distanceSquaredFrom(const TVector2&) const; // return square value of the distance between 2 points

        template <class U>
        T dot(const TVector2<U>&) const; // return dot product result

        template <class U>
        bool isLongerThan(const TVector2<U>&) const; // return true if this vector magnitude is greater than the other

        template <class U>
        bool isShorterThan(const TVector2<U>&) const; // return true if this vector magnitude is less than the other

        bool isUnitVector() const; // return true if this vector magnitude is 1

        T magnitude() const;        // return vector magnitude
        T magnitudeSquared() const; // return square value of the vector magnitude

        void     normalize();        // scale this vector to have a magnitude of 1
        TVector2 normalized() const; // returns this vector scaled to have a magnitude of 1

        void projectOnto(const TVector2&); // project this vector onto an other

        void reflectOnto(const TVector2&); // reflect this vector by an other

        void rotate(const Radian&); // rotate this vector using an angle in Radian

        void scale(const TVector2&); // scale this vector by a given factor

        std::string string() const;     // return a string representation of this vector
        std::string stringLong() const; // return a verbose string representation of this vector

        void translate(const TVector2&); // offset this vector by a given distance

        T m_x = 0;
        T m_y = 0;
    };

    template <class T, class U>
    bool operator==(const TVector2<T>&, const TVector2<U>&);
    // TVector2{ 1 } == TVector2::one()				// true				// return whether 2 vectors have the same component

    template <class T, class U>
    bool operator!=(const TVector2<T>&, const TVector2<U>&);
    // TVector2{ 1 } != TVector2::zero()				// true				// return whether 2 vectors have different components

    template <class T, class U>
    bool operator>(const TVector2<T>&, const TVector2<U>&);
    // TVector2{ 2 } > TVector2::one()				// true				// return whether the left vector's magnitude is greater than the right vector's magnitude

    template <class T, class U>
    bool operator<(const TVector2<T>&, const TVector2<U>&);
    // TVector2::zero() < TVector2{ 1 }				// true				// return whether the left vector's magnitude is smaller than the right vector's magnitude

    template <class T, class U>
    bool operator>=(const TVector2<T>&, const TVector2<U>&);
    // TVector2{ 1 } == TVector2::one()				// true				// return whether the left vector's magnitude is greater than or equal to the right vector's magnitude

    template <class T, class U>
    bool operator<=(const TVector2<T>&, const TVector2<U>&);
    // TVector2{ 1 } != TVector2::zero()				// true				// return whether the left vector's magnitude is smaller than or equal to the right vector's magnitude

    template <class T>
    TVector2<T> operator-(const TVector2<T>&);
    // -TVector2{ .5, 1.5 }							// { -.5, -1.5 }	// return a copy of a vector with all its component inverted

    template <class T, class U>
    TVector2<T> operator+(TVector2<T>, const TVector2<U>&);
    // TVector2{ .5, 1.5 } + TVector2::one()			// { 1.5, 2.5 }		// add 2 vectors component wise

    template <class T, class U>
    TVector2<T> operator-(TVector2<T>, const TVector2<U>&);
    // TVector2{ .5, 1.5 } - TVector2{ 1 }			// { -.5, .5 }		// subtract 2 vectors component wise

    template <class T, class U>
    TVector2<T> operator*(TVector2<T>, const TVector2<U>&);
    // TVector2{ .5, 1.5 } * TVector2::zero()			// { 0, 0 }			// multiply 2 vectors component wise

    template <class T, class U>
    TVector2<T> operator/(TVector2<T>, const TVector2<U>&);
    // TVector2{ .5, 1.5 } / TVector2{ 2 }			// { .25, .75 }		// divide 2 vectors component wise

    template <class T, class U>
    TVector2<T> operator+(TVector2<T>, U);
    // TVector2{ .5, 1.5 } + 1						// { 1.5, 2.5 }		// add a value to all components of a vector

    template <class T, class U>
    TVector2<T> operator-(TVector2<T>, U);
    // TVector2{ .5, 1.5 } - 1						// { -.5, .5 }		// subtract a value from all components of a vector

    template <class T, class U>
    TVector2<T> operator*(TVector2<T>, U);
    // TVector2{ .5, 1.5 } * 0						// { 0, 0 }			// multiply all components of a vector by a value

    template <class T, class U>
    TVector2<U> operator*(U, TVector2<T>);
    // 0 * TVector2{ .5, 1.5 }						// { 0, 0 }			// multiply all components of a vector by a value

    template <class T, class U>
    TVector2<T> operator/(TVector2<T>, U);
    // TVector2{ .5, 1.5 } / 2						// { .25, .75 }		// divide all components of a vector by a value

    /**
     * \brief Adds a vector string representation to an output stream
     * \tparam T The vector's data type
     * \param stream The input stream
     * \param vect The output vector
     * \return The modified stream
     */
    template <class T>
    std::ostream& operator<<(std::ostream& stream, const TVector2<T>& vect);

    /**
     * \brief Parses a string representation from an input stream into a vector
     * \tparam T The vector's data type
     * \param stream The input stream
     * \param vect The output vector
     * \return The modified stream
     */
    template <class T>
    std::istream& operator>>(std::istream& stream, TVector2<T>& vect);

    using Vector2 = TVector2<float>;
    using Vector2I = TVector2<int>;

    template <>
    inline Vector2 clamp<Vector2>(const Vector2 value, const Vector2 a, const Vector2 b)
    {
        return
        {
            clamp(value.m_x, a.m_x, b.m_x),
            clamp(value.m_y, a.m_y, b.m_y)
        };
    }

    template <>
    inline Vector2 snap<Vector2>(const Vector2 value, const Vector2 a, const Vector2 b)
    {
        return
        {
            snap(value.m_x, a.m_x, b.m_x),
            snap(value.m_y, a.m_y, b.m_y)
        };
    }

    template <>
    constexpr bool isInRange<Vector2>(const Vector2 value, const Vector2 a, const Vector2 b)
    {
        return isInRange(value.m_x, a.m_x, b.m_x)
            && isInRange(value.m_y, a.m_y, b.m_y);
    }

    template <>
    inline Vector2 min<Vector2>(const Vector2 a, const Vector2 b)
    {
        return {
            min(a.m_x, b.m_x),
            min(a.m_y, b.m_y)
        };
    }

    template <>
    inline Vector2 max<Vector2>(const Vector2 a, const Vector2 b)
    {
        return {
            max(a.m_x, b.m_x),
            max(a.m_y, b.m_y)
        };
    }

    template <>
    inline Vector2I clamp<Vector2I>(const Vector2I value, const Vector2I a, const Vector2I b)
    {
        return
        {
            clamp(value.m_x, a.m_x, b.m_x),
            clamp(value.m_y, a.m_y, b.m_y)
        };
    }

    template <>
    inline Vector2I snap<Vector2I>(const Vector2I value, const Vector2I a, const Vector2I b)
    {
        return
        {
            snap(value.m_x, a.m_x, b.m_x),
            snap(value.m_y, a.m_y, b.m_y)
        };
    }

    template <>
    constexpr bool isInRange<Vector2I>(const Vector2I value, const Vector2I a, const Vector2I b)
    {
        return isInRange(value.m_x, a.m_x, b.m_x) && isInRange(value.m_y, a.m_y, b.m_y);
    }

    template <>
    inline Vector2I min<Vector2I>(const Vector2I a, const Vector2I b)
    {
        return {
            min(a.m_x, b.m_x),
            min(a.m_y, b.m_y)
        };
    }

    template <>
    inline Vector2I max<Vector2I>(const Vector2I a, const Vector2I b)
    {
        return {
            max(a.m_x, b.m_x),
            max(a.m_y, b.m_y)
        };
    }
}

#include "Vector/Vector2.inl"

#endif // !__LIBMATH__VECTOR__VECTOR2_H__
