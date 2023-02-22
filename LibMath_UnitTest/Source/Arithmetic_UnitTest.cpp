#include <Arithmetic.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <glm/glm.hpp>

/*
	float	ceil(float);				// Return lowest integer value higher than or equal to the parameter
	float	clamp(float, float, float);	// Return parameter limited by the given range
	float	floor(float);				// Return highest integer value lower than or equal to the parameter
	float	squareRoot(float);			// Return square root of the parameter
	float	wrap(float, float, float);	// Return parameter as value inside the given range
	float	min(float, float);			// Return smallest parameter
	float	max(float, float);			// Return largest parameter
	float	abs(float);
*/

TEST_CASE("Arithmetic", "[.all][arithmetic]")
{
	float val{ 1.2f };

	CHECK(LibMath::ceil(val) == Catch::Approx(glm::ceil(val)));

	CHECK(LibMath::clamp(val, 0.f, 1.f) == Catch::Approx(glm::clamp(val, 0.f, 1.f)));
	CHECK(LibMath::clamp(val, 1.f, 1.5f) == Catch::Approx(glm::clamp(val, 1.f, 1.5f)));
	CHECK(LibMath::clamp(val, 1.5f, 2.f) == Catch::Approx(glm::clamp(val, 1.5f, 2.f)));

	CHECK(LibMath::floor(val / 2) == Catch::Approx(glm::floor(val / 2)));
	CHECK(LibMath::floor(val) == Catch::Approx(glm::floor(val)));

	CHECK(LibMath::squareRoot(val) == Catch::Approx(glm::sqrt(val)));
	CHECK(LibMath::squareRoot(val * 2.f) == Catch::Approx(glm::sqrt(val * 2.f)));
	CHECK(LibMath::squareRoot(val * 4.f) == Catch::Approx(glm::sqrt(val * 4.f)));
	CHECK(LibMath::squareRoot(val * 20.f) == Catch::Approx(glm::sqrt(val * 20.f)));
	CHECK(LibMath::squareRoot(val * .5f) == Catch::Approx(glm::sqrt(val * .5f)));
	CHECK(LibMath::squareRoot(val * .25f) == Catch::Approx(glm::sqrt(val * .25f)));
	CHECK(LibMath::squareRoot(val * .01f) == Catch::Approx(glm::sqrt(val * .01f)));
	CHECK(LibMath::squareRoot(val * .001f) == Catch::Approx(glm::sqrt(val * .001f)));

	CHECK(LibMath::wrap(90.f, -180.f, 180.f) == Catch::Approx(90.f));
	CHECK(LibMath::wrap(270.f, -180.f, 180.f) == Catch::Approx(-90.f));
	CHECK(LibMath::wrap(-375.f, -180.f, 180.f) == Catch::Approx(-15.f));

	CHECK(LibMath::min(val, 2.f * val) == Catch::Approx(glm::min(val, 2.f * val)));
	CHECK(LibMath::min(2.f * val, val) == Catch::Approx(glm::min(2.f * val, val)));

	CHECK(LibMath::max(val, 2.f * val) == Catch::Approx(glm::max(val, 2.f * val)));
	CHECK(LibMath::max(2.f * val, val) == Catch::Approx(glm::max(2.f * val, val)));

	CHECK(LibMath::abs(-val) == Catch::Approx(glm::abs(-val)));
}