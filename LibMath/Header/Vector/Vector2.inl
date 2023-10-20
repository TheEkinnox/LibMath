#ifndef __LIBMATH__VECTOR__VECTOR2_INL__
#define __LIBMATH__VECTOR__VECTOR2_INL__

#include <sstream>

#include "Trigonometry.h"

#include "Vector/Vector2.h"

namespace LibMath
{
    template <class T>
    TVector2<T> TVector2<T>::zero()
    {
        return TVector2(0);
    }

    template <class T>
    TVector2<T> TVector2<T>::one()
    {
        return TVector2(1);
    }

    template <class T>
    TVector2<T> TVector2<T>::up()
    {
        return { 0, 1 };
    }

    template <class T>
    TVector2<T> TVector2<T>::down()
    {
        return { 0, -1 };
    }

    template <class T>
    TVector2<T> TVector2<T>::left()
    {
        return { -1, 0 };
    }

    template <class T>
    TVector2<T> TVector2<T>::right()
    {
        return { 1, 0 };
    }

    template <class T>
    TVector2<T>::TVector2(const T value)
        : TVector2(value, value)
    {
    }

    template <class T>
    TVector2<T>::TVector2(const T x, const T y)
        : m_x(x), m_y(y)
    {
    }

    template <class T>
    template <class U>
    TVector2<T>::TVector2(const TVector2<U>& other)
        : TVector2(static_cast<T>(other.m_x), static_cast<T>(other.m_y))
    {
    }

    template <class T>
    template <class U>
    TVector2<T>::TVector2(TVector2<U>&& other) noexcept
        : TVector2(static_cast<T>(other.m_x), static_cast<T>(other.m_y))
    {
    }

    template <class T>
    TVector2<T>::operator TVector3<T>() const
    {
        return { m_x, m_y, 0 };
    }

    template <class T>
    template <class U>
    TVector2<T>& TVector2<T>::operator=(const TVector2<U>& other)
    {
        if (reinterpret_cast<const TVector2*>(&other) == this)
            return *this;

        m_x = static_cast<T>(other.m_x);
        m_y = static_cast<T>(other.m_y);

        return *this;
    }

    template <class T>
    template <class U>
    TVector2<T>& TVector2<T>::operator=(TVector2<U>&& other) noexcept
    {
        if (reinterpret_cast<const TVector2*>(&other) == this)
            return *this;

        m_x = static_cast<T>(other.m_x);
        m_y = static_cast<T>(other.m_y);

        return *this;
    }

    template <class T>
    T& TVector2<T>::operator[](const int index)
    {
        switch (index)
        {
        case 0:
        case 'x':
        case 'X':
            return this->m_x;
        case 1:
        case 'y':
        case 'Y':
            return this->m_y;
        default:
            throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
        }
    }

    template <class T>
    T TVector2<T>::operator[](const int index) const
    {
        switch (index)
        {
        case 0:
        case 'x':
        case 'X':
            return this->m_x;
        case 1:
        case 'y':
        case 'Y':
            return this->m_y;
        default:
            throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
        }
    }

    template <class T>
    template <class U>
    TVector2<T>& TVector2<T>::operator+=(const TVector2<U>& other)
    {
        this->m_x += static_cast<T>(other.m_x);
        this->m_y += static_cast<T>(other.m_y);

        return *this;
    }

    template <class T>
    template <class U>
    TVector2<T>& TVector2<T>::operator-=(const TVector2<U>& other)
    {
        this->m_x -= static_cast<T>(other.m_x);
        this->m_y -= static_cast<T>(other.m_y);

        return *this;
    }

    template <class T>
    template <class U>
    TVector2<T>& TVector2<T>::operator*=(const TVector2<U>& other)
    {
        this->m_x = static_cast<T>(this->m_x * other.m_x);
        this->m_y = static_cast<T>(this->m_y * other.m_y);

        return *this;
    }

    template <class T>
    template <class U>
    TVector2<T>& TVector2<T>::operator/=(const TVector2<U>& other)
    {
        this->m_x = static_cast<T>(this->m_x / other.m_x);
        this->m_y = static_cast<T>(this->m_y / other.m_y);

        return *this;
    }

    template <class T>
    template <class U>
    TVector2<T>& TVector2<T>::operator+=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x += static_cast<T>(value);
        this->m_y += static_cast<T>(value);

        return *this;
    }

    template <class T>
    template <class U>
    TVector2<T>& TVector2<T>::operator-=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x -= static_cast<T>(value);
        this->m_y -= static_cast<T>(value);

        return *this;
    }

    template <class T>
    template <class U>
    TVector2<T>& TVector2<T>::operator*=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x = static_cast<T>(this->m_x * value);
        this->m_y = static_cast<T>(this->m_y * value);

        return *this;
    }

    template <class T>
    template <class U>
    TVector2<T>& TVector2<T>::operator/=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        this->m_x = static_cast<T>(this->m_x / value);
        this->m_y = static_cast<T>(this->m_y / value);

        return *this;
    }

    template <class T>
    T* TVector2<T>::getArray()
    {
        return &m_x;
    }

    template <class T>
    const T* TVector2<T>::getArray() const
    {
        return &m_x;
    }

    template <class T>
    Radian TVector2<T>::angleFrom(const TVector2& other) const
    {
        return acos(this->dot(other) / squareRoot(this->magnitudeSquared() * other.magnitudeSquared()));
    }

    template <class T>
    Radian TVector2<T>::signedAngleFrom(const TVector2& other) const
    {
        const Radian angle = angleFrom(other);
        return angle * sign(other.cross(*this));
    }

    template <class T>
    T TVector2<T>::cross(const TVector2& other) const
    {
        return this->m_x * other.m_y - this->m_y * other.m_x;
    }

    template <class T>
    T TVector2<T>::distanceFrom(const TVector2& other) const
    {
        return squareRoot(this->distanceSquaredFrom(other));
    }

    template <class T>
    T TVector2<T>::distanceSquaredFrom(const TVector2& other) const
    {
        const T xDist = other.m_x - this->m_x;
        const T yDist = other.m_y - this->m_y;

        return xDist * xDist + yDist * yDist;
    }

    template <class T>
    T TVector2<T>::dot(const TVector2& other) const
    {
        return this->m_x * other.m_x + this->m_y * other.m_y;
    }

    template <class T>
    template <class U>
    bool TVector2<T>::isLongerThan(const TVector2<U>& other) const
    {
        return this->magnitudeSquared() > static_cast<T>(other.magnitudeSquared());
    }

    template <class T>
    template <class U>
    bool TVector2<T>::isShorterThan(const TVector2<U>& other) const
    {
        return this->magnitudeSquared() < static_cast<T>(other.magnitudeSquared());
    }

    template <class T>
    bool TVector2<T>::isUnitVector() const
    {
        return floatEquals<T>(1, this->magnitudeSquared());
    }

    template <class T>
    T TVector2<T>::magnitude() const
    {
        return squareRoot(this->magnitudeSquared());
    }

    template <class T>
    T TVector2<T>::magnitudeSquared() const
    {
        return this->m_x * this->m_x + this->m_y * this->m_y;
    }

    template <class T>
    void TVector2<T>::normalize()
    {
        *this /= this->magnitude();
    }

    template <class T>
    TVector2<T> TVector2<T>::normalized() const
    {
        TVector2 vec = *this;
        vec.normalize();
        return vec;
    }

    template <class T>
    void TVector2<T>::projectOnto(const TVector2& normal)
    {
        *this = this->dot(normal) / normal.magnitudeSquared() * normal;
    }

    // Adapted from https://math.stackexchange.com/a/4325839
    template <class T>
    void TVector2<T>::reflectOnto(const TVector2& other)
    {
        *this -= 2 * this->dot(other) / other.magnitudeSquared() * other;
    }

    template <class T>
    void TVector2<T>::rotate(const Radian& angle)
    {
        m_x = m_x * cos(angle) - m_y * sin(angle);
        m_y = m_x * sin(angle) + m_y * cos(angle);
    }

    template <class T>
    void TVector2<T>::scale(const TVector2& other)
    {
        *this *= other;
    }

    template <class T>
    std::string TVector2<T>::string() const
    {
        std::ostringstream oss;

        oss << "{" << this->m_x << "," << this->m_y << "}";

        return oss.str();
    }

    template <class T>
    std::string TVector2<T>::stringLong() const
    {
        std::ostringstream oss;

        oss << "Vector2{ x:" << this->m_x << ", y:" << this->m_y << " }";

        return oss.str();
    }

    template <class T>
    void TVector2<T>::translate(const TVector2& vect)
    {
        *this += vect;
    }

    template <class T, class U>
    bool operator==(const TVector2<T>& lhs, const TVector2<U>& rhs)
    {
        return floatEquals(lhs.m_x, rhs.m_x)
            && floatEquals(lhs.m_y, rhs.m_y);
    }

    template <class T, class U>
    bool operator!=(const TVector2<T>& lhs, const TVector2<U>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class U>
    bool operator>(const TVector2<T>& lhs, const TVector2<U>& rhs)
    {
        return lhs.isLongerThan(rhs);
    }

    template <class T, class U>
    bool operator<(const TVector2<T>& lhs, const TVector2<U>& rhs)
    {
        return rhs > lhs;
    }

    template <class T, class U>
    bool operator>=(const TVector2<T>& lhs, const TVector2<U>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class U>
    bool operator<=(const TVector2<T>& lhs, const TVector2<U>& rhs)
    {
        return !(lhs > rhs);
    }

    template <class T>
    TVector2<T> operator-(const TVector2<T>& vect)
    {
        return vect * -1;
    }

    template <class T, class U>
    TVector2<T> operator+(TVector2<T> left, const TVector2<U>& right)
    {
        return left += right;
    }

    template <class T, class U>
    TVector2<T> operator-(TVector2<T> left, const TVector2<U>& right)
    {
        return left -= right;
    }

    template <class T, class U>
    TVector2<T> operator*(TVector2<T> left, const TVector2<U>& right)
    {
        return left *= right;
    }

    template <class T, class U>
    TVector2<T> operator/(TVector2<T> left, const TVector2<U>& right)
    {
        return left /= right;
    }

    template <class T, class U>
    TVector2<T> operator+(TVector2<T> vect, U val)
    {
        return vect += val;
    }

    template <class T, class U>
    TVector2<T> operator-(TVector2<T> vect, U val)
    {
        return vect -= val;
    }

    template <class T, class U>
    TVector2<T> operator*(TVector2<T> vect, U val)
    {
        return vect *= val;
    }

    template <class T, class U>
    TVector2<U> operator*(U val, TVector2<T> vect)
    {
        return vect *= static_cast<T>(val);
    }

    template <class T, class U>
    TVector2<T> operator/(TVector2<T> vect, U val)
    {
        return vect /= val;
    }

    template <class T>
    std::ostream& operator<<(std::ostream& stream, const TVector2<T>& vect)
    {
        stream << vect.string();

        return stream;
    }

    template <class T>
    std::istream& operator>>(std::istream& stream, TVector2<T>& vect)
    {
        std::string line;

        std::getline(stream, line, '}');

        int    component = 0;
        size_t valStart = 0;

        do
        {
            if (valStart == std::string::npos)
                break;

            if (line[valStart] == '{' || std::isspace(line[valStart]))
            {
                valStart++;
                continue;
            }

            if (line[valStart] != '-' && !std::isdigit(line[valStart]))
                break;

            vect[component] = std::stof(line.substr(valStart));

            valStart = line.find(',', valStart) + 1;
            component++;
        }
        while (component < 2 && valStart != 0);

        if (component != 2)
            vect = TVector2<T>::zero();

        return stream;
    }
}

#endif // !__LIBMATH__VECTOR__VECTOR2_INL__
