#ifndef __LIBMATH__ARITHMETIC_INL__
#define __LIBMATH__ARITHMETIC_INL__

#include "Arithmetic.h"

namespace LibMath
{
    template <typename T>
	constexpr T floor(const T value)
	{
        static_assert(std::is_arithmetic_v<T>);

        if constexpr (std::is_integral_v<T>)
            return value;

		const T intPart = static_cast<T>(static_cast<int>(value));

		if (intPart > value)
			return intPart - 1;

		return intPart;
	}

    template <typename T>
	constexpr T ceil(const T value)
	{
        static_assert(std::is_arithmetic_v<T>);

        if constexpr (std::is_integral_v<T>)
            return value;

		const auto intPart = static_cast<T>(static_cast<int>(value));

		if (intPart < value)
			return intPart + 1;

		return intPart;
	}

    template <typename T>
	constexpr T round(const T value)
	{
        static_assert(std::is_arithmetic_v<T>);

        if constexpr (std::is_integral_v<T>)
            return value;

		const auto intPart = static_cast<T>(static_cast<int>(value));
		const T decimalPart = value - intPart;

		if (decimalPart < .5f)
			return intPart;

		return intPart + 1;
	}

	template <typename T>
	constexpr T	clamp(T value, T a, T b)
	{
		const T minVal = min(a, b);
		const T maxVal = max(a, b);
		return max(minVal, min(value, maxVal));
	}

	template <typename T>
	constexpr T	snap(T value, T a, T b)
	{
		return abs(value - a) < abs(value - b) ? a : b;
	}

    template <typename T>
	constexpr T wrap(const T value, const T a, const T b)
	{
        static_assert(std::is_arithmetic_v<T>);

		const T min = a < b ? a : b;
		const T max = a > b ? a : b;

		return value - (max - min) * floor((value - min) / (max - min));
	}

	constexpr float squareRoot(const float value, float precision, const size_t maxSteps)
	{
		if (value < 0)
			return NAN;

		if (value == 0.f)
			return 0.f;

		if (precision == 0.f)
			precision = std::numeric_limits<float>::epsilon();
		else
			precision = abs(precision);

		float sqrt = value >= 4.f ? value / 2.f :
			value < .5f ? 1.f / (1 - value) :
			value < 1.f ? 1.f / value : value;

		// Keep repeating until the approximation is close enough to the real value
		for (size_t i = 0; (maxSteps == 0 || i < maxSteps) && abs(sqrt * sqrt - value) > precision; i++)
			sqrt = .5f * (sqrt + value / sqrt); // Babylonian step - cf. https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Heron's_method

		return sqrt;
	}

    template <typename T>
	constexpr T pow(const T value, const int exponent)
	{
        static_assert(std::is_arithmetic_v<T>);

        if (floatEquals(value, static_cast<T>(0)))
            return 0;

		if (floatEquals(value, static_cast<T>(1)) || exponent == 0)
			return 1;

		T result;

		if (exponent > 0)
		{
			result = value;

			for (int i = 1; i < exponent; i++)
				result *= value;
		}
		else
		{
			result = 1.;

			for (int i = 0; i > exponent; i--)
				result /= value;
		}

		return result;
	}

	template <typename T>
	constexpr T	min(T a, T b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	constexpr T	max(T a, T b)
	{
		return a > b ? a : b;
	}

    template<typename T>
	constexpr T abs(const T value)
	{
        static_assert(std::is_arithmetic_v<T>);
		return value < 0 ? -value : value;
	}

    template<typename T>
	constexpr T sign(const T value)
	{
        static_assert(std::is_arithmetic_v<T>);
		return value < 0 ? -1 : 1;
	}

	// adapted from https://stackoverflow.com/a/15012792
    template <typename T>
	constexpr bool floatEquals(const T a, const T b, const T scale)
	{
        static_assert(std::is_arithmetic_v<T>);

        if constexpr (std::is_integral_v<T>)
            return a == b;

		const T maxXYOne = max(max(static_cast<T>(1), abs(a)), abs(b));

		return abs(a - b) <= std::numeric_limits<T>::epsilon() * scale * maxXYOne;
	}

	template <typename T>
	constexpr bool isInRange(T value, T a, T b)
	{
		const T minVal = min(a, b);
		const T maxVal = max(a, b);

		return minVal <= value && value <= maxVal;
	}
}

#endif // !__LIBMATH__ARITHMETIC_INL__
