#include <Vector/Vector2.h>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/exterior_product.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using namespace LibMath::Literal;

#define CHECK_VECTOR2(vector, vectorGlm) CHECK((vector).m_x == Catch::Approx((vectorGlm).x)); CHECK((vector).m_y == Catch::Approx((vectorGlm).y))

TEST_CASE("Vector2", "[.all][vector][Vector2]")
{
    SECTION("Instantiation")
    {
        // default constructor
        LibMath::Vector2 empty;
        glm::vec2        emptyGlm{};
        CHECK_VECTOR2(empty, emptyGlm);

        // destructor
        {
            LibMath::Vector2 temp;
        }

        // basic constructor
        constexpr LibMath::Vector2 oneParam{ 2.5f };
        constexpr glm::vec2        oneParamGlm{ 2.5f };
        CHECK_VECTOR2(oneParam, oneParamGlm);

        constexpr LibMath::Vector2 allParam{ 2.5f, .5f };
        constexpr glm::vec2        allParamGlm{ 2.5f, .5f };
        CHECK_VECTOR2(allParam, allParamGlm);

        // copy constructor
        constexpr LibMath::Vector2 copy{ allParam };
        constexpr glm::vec2        copyGlm{ allParamGlm };
        CHECK_VECTOR2(copy, copyGlm);

        constexpr LibMath::Vector2I iCopy{ allParam };
        constexpr glm::ivec2        iCopyGlm{ allParamGlm };
        CHECK_VECTOR2(iCopy, iCopyGlm);

        // assignment operator
        empty    = allParam;
        emptyGlm = allParamGlm;
        CHECK_VECTOR2(empty, emptyGlm);

        empty    = iCopy;
        emptyGlm = iCopyGlm;
        CHECK_VECTOR2(empty, emptyGlm);

        STATIC_CHECK(sizeof(LibMath::Vector2) == sizeof(glm::vec2));
    }

    SECTION("Accessor")
    {
        constexpr float x = 2.5f;
        constexpr float y = .5f;

        {
            constexpr LibMath::Vector2 vector{ x, y };
            CHECK(vector[0] == Catch::Approx(x));
            CHECK(vector['x'] == Catch::Approx(x));
            CHECK(vector['X'] == Catch::Approx(x));

            CHECK(vector[1] == Catch::Approx(y));
            CHECK(vector['y'] == Catch::Approx(y));
            CHECK(vector['Y'] == Catch::Approx(y));
        }

        {
            LibMath::Vector2 vector{ x, y };
            CHECK(vector[0] == Catch::Approx(x));
            CHECK(vector['x'] == Catch::Approx(x));
            CHECK(vector['X'] == Catch::Approx(x));

            CHECK(vector[1] == Catch::Approx(y));
            CHECK(vector['y'] == Catch::Approx(y));
            CHECK(vector['Y'] == Catch::Approx(y));

            vector[0] += 1.f;
            vector[1] += 1.f;

            CHECK(vector[0] == Catch::Approx(x + 1.f));
            CHECK(vector['x'] == Catch::Approx(x + 1.f));
            CHECK(vector['X'] == Catch::Approx(x + 1.f));

            CHECK(vector[1] == Catch::Approx(y + 1.f));
            CHECK(vector['y'] == Catch::Approx(y + 1.f));
            CHECK(vector['Y'] == Catch::Approx(y + 1.f));
        }
    }

    SECTION("Comparator")
    {
        // compare with self
        constexpr LibMath::Vector2 self{ 2.5f, .5f };
        STATIC_CHECK(self == self);
        STATIC_CHECK_FALSE(self != self);

        // compare with same
        STATIC_CHECK(LibMath::Vector2{ 2.5f, .5f } == LibMath::Vector2{ 2.5f, .5f });
        STATIC_CHECK_FALSE(LibMath::Vector2{ 2.5f, .5f } != LibMath::Vector2{ 2.5f, .5f });

        // trying to find copy/paste mistake
        constexpr LibMath::Vector2 twos{ 2.f, 2.f };
        STATIC_CHECK_FALSE(LibMath::Vector2{ .5f, 2.f } == twos);
        STATIC_CHECK_FALSE(LibMath::Vector2{ 2.f, .5f } == twos);
        STATIC_CHECK_FALSE(twos == LibMath::Vector2{ .5f, 2.f });
        STATIC_CHECK_FALSE(twos == LibMath::Vector2{ 2.f, .5f });

        STATIC_CHECK(LibMath::Vector2{ .5f, 2.f } != twos);
        STATIC_CHECK(LibMath::Vector2{ 2.f, .5f } != twos);
        STATIC_CHECK(twos != LibMath::Vector2{ .5f, 2.f });
        STATIC_CHECK(twos != LibMath::Vector2{ 2.f, .5f });

        // testing comparision functionality
        constexpr LibMath::Vector2 small{ 2.5f, .5f };
        constexpr LibMath::Vector2 big{ 3.75f, 3.f };
        constexpr LibMath::Vector2 big2{ 3.f, 3.75f };

        STATIC_CHECK_FALSE(big2 == big);

        {
            STATIC_CHECK(big.isLongerThan(small));
            STATIC_CHECK_FALSE(small.isLongerThan(big));

            STATIC_CHECK(big > small);
            STATIC_CHECK_FALSE(small > big);
            STATIC_CHECK_FALSE(big2 > big);
        }

        {
            STATIC_CHECK(small.isShorterThan(big));
            STATIC_CHECK_FALSE(big.isShorterThan(small));

            STATIC_CHECK(small < big);
            STATIC_CHECK_FALSE(big < small);
            STATIC_CHECK_FALSE(big2 < big);
        }

        {
            STATIC_CHECK(small <= big);
            STATIC_CHECK(big <= big);
            STATIC_CHECK(big2 <= big);
            STATIC_CHECK_FALSE(big <= small);
        }

        {
            STATIC_CHECK(big >= small);
            STATIC_CHECK(big >= big);
            STATIC_CHECK(big2 >= big);
            STATIC_CHECK_FALSE(small >= big);
        }

        STATIC_CHECK_FALSE(self.isUnitVector());
        STATIC_CHECK(LibMath::Vector2{ 0.707106781f, 0.707106781f }.isUnitVector());
    }

    SECTION("Constant")
    {
        CHECK_VECTOR2(LibMath::Vector2::zero(), glm::vec2(0.f, 0.f));

        CHECK_VECTOR2(LibMath::Vector2::one(), glm::vec2(1.f, 1.f));

        CHECK_VECTOR2(LibMath::Vector2::up(), glm::vec2(0.f, 1.f));

        CHECK_VECTOR2(LibMath::Vector2::down(), glm::vec2(0.f, -1.f));

        CHECK_VECTOR2(LibMath::Vector2::left(), glm::vec2(-1.f, 0.f));

        CHECK_VECTOR2(LibMath::Vector2::right(), glm::vec2(1.f, 0.f));
    }

    SECTION("Arithmetic")
    {
        constexpr LibMath::Vector2 small{ 2.5f, .5f };
        constexpr LibMath::Vector2 big{ 3.75f, 3.f };

        constexpr glm::vec2 smallGlm{ 2.5f, .5f };
        constexpr glm::vec2 bigGlm{ 3.75f, 3.f };

        constexpr float scalar = 3.75f;

        SECTION("Addition")
        {
            {
                LibMath::Vector2 sumAssignment = big;
                sumAssignment += small;

                glm::vec2 sumAssignmentGlm = bigGlm;
                sumAssignmentGlm += smallGlm;

                CHECK_VECTOR2(sumAssignment, sumAssignmentGlm);
            }

            {
                constexpr LibMath::Vector2 sum    = big + small;
                constexpr glm::vec2        sumGlm = bigGlm + smallGlm;

                CHECK_VECTOR2(sum, sumGlm);
            }
        }

        SECTION("Inverse")
        {
            constexpr LibMath::Vector2 inverse    = -LibMath::Vector2{ 3.7f, 3.f };
            constexpr glm::vec2        inverseGlm = -glm::vec2{ 3.7f, 3.f };

            CHECK_VECTOR2(inverse, inverseGlm);
        }

        SECTION("Substraction")
        {
            {
                LibMath::Vector2 differenceAssignment = big;
                differenceAssignment -= small;

                glm::vec2 differenceAssignmentGlm = bigGlm;
                differenceAssignmentGlm -= smallGlm;

                CHECK_VECTOR2(differenceAssignment, differenceAssignmentGlm);
            }

            {
                constexpr LibMath::Vector2 difference    = big - small;
                constexpr glm::vec2        differenceGlm = bigGlm - smallGlm;

                CHECK_VECTOR2(difference, differenceGlm);
            }
        }

        SECTION("Multiplication")
        {
            {
                LibMath::Vector2 productAssignment = big;
                productAssignment *= small;

                glm::vec2 productAssignmentGlm = bigGlm;
                productAssignmentGlm *= smallGlm;

                CHECK_VECTOR2(productAssignment, productAssignmentGlm);
            }

            {
                constexpr LibMath::Vector2 product    = big * small;
                constexpr glm::vec2        productGlm = bigGlm * smallGlm;

                CHECK_VECTOR2(product, productGlm);
            }

            {
                LibMath::Vector2 productAssignment = big;
                productAssignment *= scalar;

                glm::vec2 productAssignmentGlm = bigGlm;
                productAssignmentGlm *= scalar;

                CHECK_VECTOR2(productAssignment, productAssignmentGlm);
            }

            {
                constexpr LibMath::Vector2 product    = big * scalar;
                constexpr glm::vec2        productGlm = bigGlm * scalar;

                CHECK_VECTOR2(product, productGlm);
            }
        }

        SECTION("Division")
        {
            {
                LibMath::Vector2 quotientAssignment = big;
                quotientAssignment /= small;

                glm::vec2 quotientAssignmentGlm = bigGlm;
                quotientAssignmentGlm /= smallGlm;

                CHECK_VECTOR2(quotientAssignment, quotientAssignmentGlm);
            }

            {
                constexpr LibMath::Vector2 quotient    = big / small;
                constexpr glm::vec2        quotientGlm = bigGlm / smallGlm;

                CHECK_VECTOR2(quotient, quotientGlm);
            }

            {
                LibMath::Vector2 quotientAssignment = big;
                quotientAssignment /= scalar;

                glm::vec2 quotientAssignmentGlm = bigGlm;
                quotientAssignmentGlm /= scalar;

                CHECK_VECTOR2(quotientAssignment, quotientAssignmentGlm);
            }

            {
                constexpr LibMath::Vector2 quotient    = big / scalar;
                constexpr glm::vec2        quotientGlm = bigGlm / scalar;

                CHECK_VECTOR2(quotient, quotientGlm);
            }
        }
    }

    SECTION("Transformation")
    {
        constexpr LibMath::Vector2 origin{ 2.5f, .5f };
        constexpr LibMath::Vector2 transformation{ -2.f, 1.25f };

        constexpr glm::vec2 originGlm{ 2.5f, .5f };
        constexpr glm::vec2 transformationGlm{ -2.f, 1.25f };

        SECTION("Translation")
        {
            LibMath::Vector2 translate = origin;
            translate.translate(transformation);

            constexpr glm::vec2 translateGlm = originGlm + transformationGlm;

            CHECK_VECTOR2(translate, translateGlm);
        }

        SECTION("Scale")
        {
            LibMath::Vector2 scale = origin;
            scale.scale(transformation);

            constexpr glm::vec2 scaleGlm = originGlm * transformationGlm;

            CHECK_VECTOR2(scale, scaleGlm);
        }

        SECTION("Rotation")
        {
            LibMath::Vector2 rotate = origin;
            rotate.rotate(LibMath::Radian(transformation.m_x));

            glm::vec2 rotateGlm = glm::rotate(originGlm, transformation.m_x);

            CHECK_VECTOR2(rotate, rotateGlm);
        }
    }

    SECTION("Functionality")
    {
        constexpr LibMath::Vector2 base{ 2.5f, .5f };
        constexpr LibMath::Vector2 other{ 3.75f, 3.f };

        constexpr glm::vec2 baseGlm{ 2.5f, .5f };
        constexpr glm::vec2 otherGlm{ 3.75f, 3.f };

        SECTION("Angle")
        {
            LibMath::Radian angle = base.angleFrom(other);

            float angleGlm   = glm::angle(glm::normalize(baseGlm), glm::normalize(otherGlm));
            float glmDegrees = glm::degrees(angleGlm);

            CHECK(angle.radian() == Catch::Approx(angleGlm));
            CHECK(angle.degree() == Catch::Approx(glmDegrees));
        }

        SECTION("Cross")
        {
            constexpr float cross    = base.cross(other);
            constexpr float crossGlm = glm::cross(baseGlm, otherGlm);

            CHECK(cross == Catch::Approx(crossGlm));
        }

        SECTION("Dot")
        {
            constexpr float dot    = base.dot(other);
            constexpr float dotGlm = glm::dot(baseGlm, otherGlm);

            CHECK(dot == Catch::Approx(dotGlm));
        }

        SECTION("Distance")
        {
            {
                constexpr float distance    = base.distanceFrom(other);
                float           distanceGlm = glm::distance(baseGlm, otherGlm);

                CHECK(distance == Catch::Approx(distanceGlm));
            }

            {
                constexpr float distanceSquare    = base.distanceSquaredFrom(other);
                float           distanceSquareGlm = glm::distance2(baseGlm, otherGlm);

                CHECK(distanceSquare == Catch::Approx(distanceSquareGlm));
            }
        }

        SECTION("Magnitude")
        {
            {
                constexpr float magnitude    = base.magnitude();
                float           magnitudeGlm = glm::length(baseGlm);

                CHECK(magnitude == Catch::Approx(magnitudeGlm));
            }

            {
                constexpr float magnitudeSquare    = base.magnitudeSquared();
                float           magnitudeSquareGlm = glm::length2(baseGlm);

                CHECK(magnitudeSquare == Catch::Approx(magnitudeSquareGlm));
            }
        }

        SECTION("Normal")
        {
            constexpr LibMath::Vector2 normalized = base.normalized();
            LibMath::Vector2           normalize  = base;
            normalize.normalize();

            glm::vec2 normalizeGlm = glm::normalize(baseGlm);

            CHECK_VECTOR2(normalize, normalizeGlm);
            CHECK_VECTOR2(normalized, normalizeGlm);
        }

        SECTION("ProjectOnto")
        {
            LibMath::Vector2 project = base;
            project.projectOnto(other);

            glm::vec2 projectGlm = glm::proj(baseGlm, otherGlm);

            CHECK_VECTOR2(project, projectGlm);
        }

        SECTION("ReflectOnto")
        {
            LibMath::Vector2 reflect = base;
            reflect.reflectOnto(other);

            glm::vec2 reflectGlm = glm::reflect(baseGlm, glm::normalize(otherGlm));

            CHECK_VECTOR2(reflect, reflectGlm);
        }
    }

    SECTION("Extra")
    {
        constexpr LibMath::Vector2 input{ 2.5f, -.5f };
        {
            std::stringstream buffer;
            buffer << input;
            CHECK(buffer.str() == "{2.5,-0.5}");

            buffer << " extra";

            LibMath::Vector2 output;
            buffer >> output;
            CHECK(output == input);

            std::string extra;
            buffer >> extra;
            CHECK(extra == "extra");
        }

        {
            CHECK(input.string() == "{2.5,-0.5}");

            CHECK(input.stringLong() == "Vector2{ x:2.5, y:-0.5 }");
        }
    }

    SECTION("Debug")
    {
#if defined(_DEBUG) || defined(DEBUG) || !defined(NDEBUG)
        constexpr LibMath::Vector2 vector{ 2.5f, .5f };

        CHECK_THROWS(vector[-1]);
        CHECK_THROWS(vector[2]);
        CHECK_THROWS(vector['z']);
        CHECK_THROWS(vector['Z']);
        CHECK_THROWS(vector['w']);
        CHECK_THROWS(vector['W']);
#endif // DEBUG
    }
}
