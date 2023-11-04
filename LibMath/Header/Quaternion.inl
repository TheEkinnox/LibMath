#ifndef __LIBMATH__QUATERNION_INL__
#define __LIBMATH__QUATERNION_INL__

#include "Quaternion.h"
#include "Trigonometry.h"

namespace LibMath
{
    template <class T>
    constexpr TQuaternion<T> TQuaternion<T>::identity()
    {
        return TQuaternion(1, 0, 0, 0);
    }

    template <class T>
    constexpr TQuaternion<T>::TQuaternion(T value)
        : TQuaternion(value, value, value, value)
    {
    }

    template <class T>
    constexpr TQuaternion<T>::TQuaternion(T w, T x, T y, T z)
        : m_x(x), m_y(y), m_z(z), m_w(w)
    {
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>::TQuaternion(T scalar, TVector3<U> vector)
        : TQuaternion(scalar, vector.m_x, vector.m_y, vector.m_z)
    {
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>::TQuaternion(Radian angle, TVector3<U> axis)
    {
        angle /= 2;
        axis = axis.normalized() * sin(angle);

        m_x = axis.m_x;
        m_y = axis.m_y;
        m_z = axis.m_z;
        m_w = cos(angle);
    }

    template <class T>
    constexpr TQuaternion<T>::TQuaternion(Radian yaw, Radian pitch, Radian roll)
    {
        T cosYaw = cos(yaw /= 2);
        T cosPitch = cos(pitch /= 2);
        T cosRoll = cos(roll /= 2);

        T sinYaw = sin(yaw);
        T sinPitch = sin(pitch);
        T sinRoll = sin(roll);

        m_x = cosYaw * sinPitch * cosRoll + sinYaw * cosPitch * sinRoll;
        m_y = sinYaw * cosPitch * cosRoll - cosYaw * sinPitch * sinRoll;
        m_z = cosYaw * cosPitch * sinRoll - sinYaw * sinPitch * cosRoll;
        m_w = cosYaw * cosPitch * cosRoll + sinYaw * sinPitch * sinRoll;
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>::TQuaternion(const TVector3<U>& angles, const bool isRadian)
    {
        if (isRadian)
            *this = TQuaternion(Radian(static_cast<float>(angles.m_x)), Radian(static_cast<float>(angles.m_y)),
                Radian(static_cast<float>(angles.m_z)));
        else
            *this = TQuaternion(Degree(static_cast<float>(angles.m_x)), Degree(static_cast<float>(angles.m_y)),
                Degree(static_cast<float>(angles.m_z)));
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>::TQuaternion(const TQuaternion<U>& other)
        : TQuaternion(static_cast<T>(other.m_w), static_cast<T>(other.m_x), static_cast<T>(other.m_y), static_cast<T>(other.m_z))
    {
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>::TQuaternion(TQuaternion<U>&& other) noexcept
        : TQuaternion(static_cast<T>(other.m_w), static_cast<T>(other.m_x), static_cast<T>(other.m_y), static_cast<T>(other.m_z))
    {
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>& TQuaternion<T>::operator=(const TQuaternion<U>& other)
    {
        if (this == reinterpret_cast<const TQuaternion*>(&other))
            return *this;

        m_x = static_cast<T>(other.m_x);
        m_y = static_cast<T>(other.m_y);
        m_z = static_cast<T>(other.m_z);
        m_w = static_cast<T>(other.m_w);

        return *this;
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>& TQuaternion<T>::operator=(TQuaternion<U>&& other) noexcept
    {
        if (this == reinterpret_cast<const TQuaternion*>(&other))
            return *this;

        m_x = static_cast<T>(other.m_x);
        m_y = static_cast<T>(other.m_y);
        m_z = static_cast<T>(other.m_z);
        m_w = static_cast<T>(other.m_w);

        return *this;
    }

    template <class T>
    constexpr TQuaternion<T> TQuaternion<T>::fromEuler(const Radian& x, const Radian& y, const Radian& z)
    {
        return TQuaternion(z, x, y);
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T> TQuaternion<T>::fromEuler(const TVector3<U>& angles, const bool isRadian)
    {
        if (isRadian)
            return fromEuler(Radian(angles.m_x), Radian(angles.m_y), Radian(angles.m_z));

        return fromEuler(Degree(angles.m_x), Degree(angles.m_y), Degree(angles.m_z));
    }

    template <class T>
    constexpr TQuaternion<T> TQuaternion<T>::fromEuler(const Radian&        x, const Radian& y, const Radian& z,
                                                       const ERotationOrder rotationOrder)
    {
        TQuaternion xQuat = TQuaternion(x, TVector3<T>{ 1, 0, 0 });
        TQuaternion yQuat = TQuaternion(y, TVector3<T>{ 0, 1, 0 });
        TQuaternion zQuat = TQuaternion(z, TVector3<T>{ 0, 0, 1 });

        switch (rotationOrder)
        {
        case ERotationOrder::XYZ:
            return xQuat * yQuat * zQuat;
        case ERotationOrder::XZY:
            return xQuat * zQuat * yQuat;
        case ERotationOrder::YXZ:
            return yQuat * xQuat * zQuat;
        case ERotationOrder::YZX:
            return yQuat * zQuat * xQuat;
        case ERotationOrder::ZXY:
            return zQuat * xQuat * yQuat;
        case ERotationOrder::ZYX:
            return zQuat * yQuat * xQuat;
        default:
            throw std::out_of_range("Invalid rotation order");
        }
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T> TQuaternion<T>::fromEuler(const TVector3<U>&   angles, const bool isRadian,
                                                       const ERotationOrder rotationOrder)
    {
        if (isRadian)
            return fromEuler(Radian(angles.m_x), Radian(angles.m_y), Radian(angles.m_z), rotationOrder);

        return fromEuler(Degree(angles.m_x), Degree(angles.m_y), Degree(angles.m_z), rotationOrder);
    }

    template <class T>
    constexpr TQuaternion<T>::operator TVector3<T>() const
    {
        return { m_x, m_y, m_z };
    }

    template <class T>
    constexpr T& TQuaternion<T>::operator[](const int index)
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
        case 2:
        case 'z':
        case 'Z':
            return this->m_z;
        case 3:
        case 'w':
        case 'W':
            return this->m_w;
        default:
            throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
        }
    }

    template <class T>
    constexpr T TQuaternion<T>::operator[](const int index) const
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
        case 2:
        case 'z':
        case 'Z':
            return this->m_z;
        case 3:
        case 'w':
        case 'W':
            return this->m_w;
        default:
            throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
        }
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>& TQuaternion<T>::operator+=(const TQuaternion<U>& other)
    {
        m_x = static_cast<T>(m_x + other.m_x);
        m_y = static_cast<T>(m_y + other.m_y);
        m_z = static_cast<T>(m_z + other.m_z);
        m_w = static_cast<T>(m_w + other.m_w);

        return *this;
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>& TQuaternion<T>::operator-=(const TQuaternion<U>& other)
    {
        m_x = static_cast<T>(m_x - other.m_x);
        m_y = static_cast<T>(m_y - other.m_y);
        m_z = static_cast<T>(m_z - other.m_z);
        m_w = static_cast<T>(m_w - other.m_w);

        return *this;
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>& TQuaternion<T>::operator*=(const TQuaternion<U>& other)
    {
        const T a = m_x, b = m_y, c = m_z, s = m_w;

        m_w = static_cast<T>(s * other.m_w - a * other.m_x - b * other.m_y - c * other.m_z);
        m_x = static_cast<T>(s * other.m_x + a * other.m_w + b * other.m_z - c * other.m_y);
        m_y = static_cast<T>(s * other.m_y - a * other.m_z + b * other.m_w + c * other.m_x);
        m_z = static_cast<T>(s * other.m_z + a * other.m_y - b * other.m_x + c * other.m_w);
        // m_z = static_cast<T>(s * other.m_y - a * other.m_z + b * other.m_w + c * other.m_x);
        // m_y = static_cast<T>(s * other.m_z + a * other.m_y - b * other.m_x + c * other.m_w);

        return *this;
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>& TQuaternion<T>::operator/=(const TQuaternion<U>& other)
    {
        return *this *= other.inverse();
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>& TQuaternion<T>::operator+=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        m_w = static_cast<T>(m_w + value);

        return *this;
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>& TQuaternion<T>::operator-=(U value)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        m_w = static_cast<T>(m_w - value);

        return *this;
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>& TQuaternion<T>::operator*=(U scalar)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        m_x = static_cast<T>(m_x * scalar);
        m_y = static_cast<T>(m_y * scalar);
        m_z = static_cast<T>(m_z * scalar);
        m_w = static_cast<T>(m_w * scalar);

        return *this;
    }

    template <class T>
    template <typename U>
    constexpr TQuaternion<T>& TQuaternion<T>::operator/=(U scalar)
    {
        static_assert(std::is_arithmetic_v<U>, "Invalid value - Data type should be an arithmetic type");

        m_x = static_cast<T>(m_x / scalar);
        m_y = static_cast<T>(m_y / scalar);
        m_z = static_cast<T>(m_z / scalar);
        m_w = static_cast<T>(m_w / scalar);

        return *this;
    }

    template <class T>
    constexpr T* TQuaternion<T>::getArray()
    {
        return &m_x;
    }

    template <class T>
    constexpr const T* TQuaternion<T>::getArray() const
    {
        return &m_x;
    }

    template <class T>
    constexpr bool TQuaternion<T>::isUnit() const
    {
        return floatEquals<T>(1, magnitudeSquared());
    }

    template <class T>
    constexpr T TQuaternion<T>::magnitude() const
    {
        return squareRoot(magnitudeSquared());
    }

    template <class T>
    constexpr T TQuaternion<T>::magnitudeSquared() const
    {
        return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
    }

    template <class T>
    template <typename U>
    constexpr T TQuaternion<T>::dot(const TQuaternion<U>& other) const
    {
        return static_cast<T>(this->m_x * other.m_x +
            this->m_y * other.m_y +
            this->m_z * other.m_z +
            this->m_w * other.m_w);
    }

    template <class T>
    constexpr TQuaternion<T> TQuaternion<T>::conjugate() const
    {
        return TQuaternion(m_w, -TVector3<T>(*this));
    }

    template <class T>
    constexpr TQuaternion<T> TQuaternion<T>::inverse() const
    {
        T sqrLen = magnitudeSquared();
        return conjugate() / sqrLen;
    }

    template <class T>
    constexpr void TQuaternion<T>::normalize()
    {
        *this /= magnitude();
    }

    template <class T>
    constexpr TQuaternion<T> TQuaternion<T>::normalized() const
    {
        return *this / magnitude();
    }

    template <class T>
    constexpr std::string TQuaternion<T>::string() const
    {
        std::ostringstream oss;

        oss << "{" << this->m_x << "," << this->m_y << "," << this->m_z << "," << this->m_w << "}";

        return oss.str();
    }

    template <class T>
    constexpr std::string TQuaternion<T>::stringLong() const
    {
        std::ostringstream oss;

        oss << "Quaternion{ x:" << this->m_x << ", y:" << this->m_y << ", z:"
            << this->m_z << ", w:" << this->m_w << " }";

        return oss.str();
    }

    template <class T, class U>
    constexpr bool operator==(const TQuaternion<T>& left, const TQuaternion<U>& right)
    {
        return floatEquals(left.m_x, static_cast<T>(right.m_x))
            && floatEquals(left.m_y, static_cast<T>(right.m_y))
            && floatEquals(left.m_z, static_cast<T>(right.m_z))
            && floatEquals(left.m_w, static_cast<T>(right.m_w));
    }

    template <class T, class U>
    constexpr bool operator!=(const TQuaternion<T>& left, const TQuaternion<U>& right)
    {
        return !(left == right);
    }

    template <class T, class U>
    constexpr bool operator>(const TQuaternion<T>& left, const TQuaternion<U>& right)
    {
        return left.magnitudeSquared() > right.magnitudeSquared();
    }

    template <class T, class U>
    constexpr bool operator<(const TQuaternion<T>& left, const TQuaternion<U>& right)
    {
        return right > left;
    }

    template <class T, class U>
    constexpr bool operator>=(const TQuaternion<T>& left, const TQuaternion<U>& right)
    {
        return !(left < right);
    }

    template <class T, class U>
    constexpr bool operator<=(const TQuaternion<T>& left, const TQuaternion<U>& right)
    {
        return !(left > right);
    }

    template <class T>
    constexpr TQuaternion<T> operator-(const TQuaternion<T>& quat)
    {
        return TQuaternion<T>(-quat.m_w, -quat.m_x, -quat.m_y, -quat.m_z);
    }

    template <class T, class U>
    constexpr TQuaternion<T> operator+(TQuaternion<T> left, const TQuaternion<U>& right)
    {
        return left += right;
    }

    template <class T, class U>
    constexpr TQuaternion<T> operator-(TQuaternion<T> left, const TQuaternion<U>& right)
    {
        return left -= right;
    }

    template <class T, class U>
    constexpr TQuaternion<T> operator*(TQuaternion<T> left, const TQuaternion<U>& right)
    {
        return left *= right;
    }

    template <class T, class U>
    constexpr TQuaternion<T> operator/(TQuaternion<T> left, const TQuaternion<U>& right)
    {
        return left /= right;
    }

    template <class T, class U>
    constexpr TQuaternion<T> operator+(TQuaternion<T> quat, U value)
    {
        return quat += value;
    }

    template <class T, class U>
    constexpr TQuaternion<T> operator-(TQuaternion<T> quat, U value)
    {
        return quat -= value;
    }

    template <class T, class U>
    constexpr TQuaternion<T> operator*(TQuaternion<T> quat, const U scalar)
    {
        return quat *= scalar;
    }

    template <class T, class U>
    constexpr TQuaternion<U> operator*(const U scalar, TQuaternion<T> quat)
    {
        return quat * scalar;
    }

    template <class T, class U>
    constexpr TQuaternion<T> operator/(TQuaternion<T> quat, U scalar)
    {
        return quat /= scalar;
    }

    template <class T>
    constexpr std::ostream& operator<<(std::ostream& stream, const TQuaternion<T>& quat)
    {
        return stream << quat.string();
    }

    template <class T>
    constexpr std::istream& operator>>(std::istream& stream, TQuaternion<T>& quat)
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

            quat[component] = std::stof(line.substr(valStart));

            valStart = line.find(',', valStart) + 1;
            component++;
        }
        while (component < 4 && valStart != 0);

        if (component != 4)
            quat = TQuaternion<T>::identity();

        return stream;
    }
}

#endif // !__LIBMATH__QUATERNION_INL__