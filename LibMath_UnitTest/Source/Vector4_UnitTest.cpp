#include <Vector/Vector4.h>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using namespace LibMath::Literal;

#define CHECK_VECTOR4(vector, vectorGlm) CHECK((vector).m_x == Catch::Approx((vectorGlm).x)); CHECK((vector).m_y == Catch::Approx((vectorGlm).y)); CHECK((vector).m_z == Catch::Approx((vectorGlm).z)); CHECK((vector).m_w == Catch::Approx((vectorGlm).w))

TEST_CASE("Vector4", "[.all][vector][Vector4]")
{
    SECTION("Instantiation")
    {
        // default constructor
        LibMath::Vector4 empty;
        glm::vec4        emptyGlm{};
        CHECK_VECTOR4(empty, emptyGlm);

        // destructor
        {
            LibMath::Vector4 temp;
        }

        // basic constructor
        constexpr LibMath::Vector4 oneParam{ 2.5f };
        constexpr glm::vec4        oneParamGlm{ 2.5f };
        CHECK_VECTOR4(oneParam, oneParamGlm);

        constexpr LibMath::Vector4 allParam{ 2.5f, .5f, 2.f, 1.f };
        constexpr glm::vec4        allParamGlm{ 2.5f, .5f, 2.f, 1.f };
        CHECK_VECTOR4(allParam, allParamGlm);

        // copy constructor
        constexpr LibMath::Vector4 copy{ allParam };
        constexpr glm::vec4        copyGlm{ allParamGlm };
        CHECK_VECTOR4(copy, copyGlm);

        constexpr LibMath::Vector4I iCopy{ allParam };
        constexpr glm::ivec4        iCopyGlm{ allParamGlm };
        CHECK_VECTOR4(iCopy, iCopyGlm);

        // assignment operator
        empty    = allParam;
        emptyGlm = allParamGlm;
        CHECK_VECTOR4(empty, emptyGlm);

        empty    = iCopy;
        emptyGlm = iCopyGlm;
        CHECK_VECTOR4(empty, emptyGlm);

        STATIC_CHECK(sizeof(LibMath::Vector4) == sizeof(glm::vec4));
    }

    SECTION("Accessor")
    {
        constexpr float x = 2.5f;
        constexpr float y = .5f;
        constexpr float z = 2.f;
        constexpr float w = 1.f;

        {
            constexpr LibMath::Vector4 vector{ x, y, z, w };
            CHECK(vector[0] == Catch::Approx(x));
            CHECK(vector['x'] == Catch::Approx(x));
            CHECK(vector['X'] == Catch::Approx(x));

            CHECK(vector[1] == Catch::Approx(y));
            CHECK(vector['y'] == Catch::Approx(y));
            CHECK(vector['Y'] == Catch::Approx(y));

            CHECK(vector[2] == Catch::Approx(z));
            CHECK(vector['z'] == Catch::Approx(z));
            CHECK(vector['Z'] == Catch::Approx(z));

            CHECK(vector[3] == Catch::Approx(w));
            CHECK(vector['w'] == Catch::Approx(w));
            CHECK(vector['W'] == Catch::Approx(w));
        }

        {
            LibMath::Vector4 vector{ x, y, z, w };
            CHECK(vector[0] == Catch::Approx(x));
            CHECK(vector['x'] == Catch::Approx(x));
            CHECK(vector['X'] == Catch::Approx(x));

            CHECK(vector[1] == Catch::Approx(y));
            CHECK(vector['y'] == Catch::Approx(y));
            CHECK(vector['Y'] == Catch::Approx(y));

            CHECK(vector[2] == Catch::Approx(z));
            CHECK(vector['z'] == Catch::Approx(z));
            CHECK(vector['Z'] == Catch::Approx(z));

            CHECK(vector[3] == Catch::Approx(w));
            CHECK(vector['w'] == Catch::Approx(w));
            CHECK(vector['W'] == Catch::Approx(w));

            vector[0] += 1.f;
            vector[1] += 1.f;
            vector[2] += 1.f;
            vector[3] += 1.f;

            CHECK(vector[0] == Catch::Approx(x + 1.f));
            CHECK(vector['x'] == Catch::Approx(x + 1.f));
            CHECK(vector['X'] == Catch::Approx(x + 1.f));

            CHECK(vector[1] == Catch::Approx(y + 1.f));
            CHECK(vector['y'] == Catch::Approx(y + 1.f));
            CHECK(vector['Y'] == Catch::Approx(y + 1.f));

            CHECK(vector[2] == Catch::Approx(z + 1.f));
            CHECK(vector['z'] == Catch::Approx(z + 1.f));
            CHECK(vector['Z'] == Catch::Approx(z + 1.f));

            CHECK(vector[3] == Catch::Approx(w + 1.f));
            CHECK(vector['w'] == Catch::Approx(w + 1.f));
            CHECK(vector['W'] == Catch::Approx(w + 1.f));
        }
    }

    SECTION("Comparator")
    {
        // compare with self
        constexpr LibMath::Vector4 self{ 2.5f, .5f, 2.f, 1.f };
        STATIC_CHECK(self == self);
        STATIC_CHECK_FALSE(self != self);

        // compare with same
        STATIC_CHECK(LibMath::Vector4{ 2.5f, .5f, 2.f, 1.f } == LibMath::Vector4{ 2.5f, .5f, 2.f, 1.f });
        STATIC_CHECK_FALSE(LibMath::Vector4{ 2.5f, .5f, 2.f, 1.f } != LibMath::Vector4{ 2.5f, .5f, 2.f, 1.f });

        // trying to find copy/paste mistake
        constexpr LibMath::Vector4 twos{ 2.f, 2.f, 2.f, 2.f };
        STATIC_CHECK_FALSE(LibMath::Vector4{ .5f, 2.f, 2.f, 2.f } == twos);
        STATIC_CHECK_FALSE(LibMath::Vector4{ 2.f, .5f, 2.f, 2.f } == twos);
        STATIC_CHECK_FALSE(LibMath::Vector4{ 2.f, 2.f, .5f, 2.f } == twos);
        STATIC_CHECK_FALSE(LibMath::Vector4{ 2.f, 2.f, 2.f, .5f } == twos);
        STATIC_CHECK_FALSE(twos == LibMath::Vector4{ .5f, 2.f, 2.f, 2.f });
        STATIC_CHECK_FALSE(twos == LibMath::Vector4{ 2.f, .5f, 2.f, 2.f });
        STATIC_CHECK_FALSE(twos == LibMath::Vector4{ 2.f, 2.f, .5f, 2.f });
        STATIC_CHECK_FALSE(twos == LibMath::Vector4{ 2.f, 2.f, 2.f, .5f });

        STATIC_CHECK(LibMath::Vector4{ .5f, 2.f, 2.f, 2.f } != twos);
        STATIC_CHECK(LibMath::Vector4{ 2.f, .5f, 2.f, 2.f } != twos);
        STATIC_CHECK(LibMath::Vector4{ 2.f, 2.f, .5f, 2.f } != twos);
        STATIC_CHECK(LibMath::Vector4{ 2.f, 2.f, 2.f, .5f } != twos);
        STATIC_CHECK(twos != LibMath::Vector4{ .5f, 2.f, 2.f, 2.f });
        STATIC_CHECK(twos != LibMath::Vector4{ 2.f, .5f, 2.f, 2.f });
        STATIC_CHECK(twos != LibMath::Vector4{ 2.f, 2.f, .5f, 2.f });
        STATIC_CHECK(twos != LibMath::Vector4{ 2.f, 2.f, 2.f, .5f });

        // testing comparision functionality
        constexpr LibMath::Vector4 small{ 2.5f, .5f, 2.f, 1.f };
        constexpr LibMath::Vector4 big{ 3.75f, 3.f, .75f, 1.f };
        constexpr LibMath::Vector4 big2{ 3.f, 3.75f, .75f, 1.f };

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
        STATIC_CHECK(LibMath::Vector4{ 0.7372098f, 0.147442f, 0.5897678f, 0.29488f }.isUnitVector());
    }

    SECTION("Constant")
    {
        CHECK_VECTOR4(LibMath::Vector4::zero(), glm::vec4(0.f, 0.f, 0.f, 0.f));

        CHECK_VECTOR4(LibMath::Vector4::one(), glm::vec4(1.f, 1.f, 1.f, 1.f));

        CHECK_VECTOR4(LibMath::Vector4::up(), glm::vec4(0.f, 1.f, 0.f, 0.f));

        CHECK_VECTOR4(LibMath::Vector4::down(), glm::vec4(0.f, -1.f, 0., 0.f));

        CHECK_VECTOR4(LibMath::Vector4::left(), glm::vec4(-1.f, 0.f, 0.f, 0.f));

        CHECK_VECTOR4(LibMath::Vector4::right(), glm::vec4(1.f, 0.f, 0.f, 0.f));

        CHECK_VECTOR4(LibMath::Vector4::front(), glm::vec4(0.f, 0.f, 1.f, 0.f));

        CHECK_VECTOR4(LibMath::Vector4::back(), glm::vec4(0.f, 0.f, -1.f, 0.f));
    }

    SECTION("Arithmetic")
    {
        constexpr LibMath::Vector4 small{ 2.5f, .5f, 2.f, 1.f };
        constexpr LibMath::Vector4 big{ 3.75f, 3.f, .75f, 1.f };

        constexpr glm::vec4 smallGlm{ 2.5f, .5f, 2.f, 1.f };
        constexpr glm::vec4 bigGlm{ 3.75f, 3.f, .75f, 1.f };

        constexpr float scalar = 3.75f;

        SECTION("Addition")
        {
            {
                LibMath::Vector4 sumAssignment = big;
                sumAssignment += small;

                glm::vec4 sumAssignmentGlm = bigGlm;
                sumAssignmentGlm += smallGlm;

                CHECK_VECTOR4(sumAssignment, sumAssignmentGlm);
            }

            {
                constexpr LibMath::Vector4 sum    = big + small;
                constexpr glm::vec4        sumGlm = bigGlm + smallGlm;

                CHECK_VECTOR4(sum, sumGlm);
            }
        }

        SECTION("Inverse")
        {
            constexpr LibMath::Vector4 inverse    = -LibMath::Vector4{ 3.7f, 3.f, .7f, 1.f };
            constexpr glm::vec4        inverseGlm = -glm::vec4{ 3.7f, 3.f, .7f, 1.f };

            CHECK_VECTOR4(inverse, inverseGlm);
        }

        SECTION("Substraction")
        {
            {
                LibMath::Vector4 differenceAssignment = big;
                differenceAssignment -= small;

                glm::vec4 differenceAssignmentGlm = bigGlm;
                differenceAssignmentGlm -= smallGlm;

                CHECK_VECTOR4(differenceAssignment, differenceAssignmentGlm);
            }

            {
                constexpr LibMath::Vector4 difference    = big - small;
                constexpr glm::vec4        differenceGlm = bigGlm - smallGlm;

                CHECK_VECTOR4(difference, differenceGlm);
            }
        }

        SECTION("Multiplication")
        {
            {
                LibMath::Vector4 productAssignment = big;
                productAssignment *= small;

                glm::vec4 productAssignmentGlm = bigGlm;
                productAssignmentGlm *= smallGlm;

                CHECK_VECTOR4(productAssignment, productAssignmentGlm);
            }

            {
                constexpr LibMath::Vector4 product    = big * small;
                constexpr glm::vec4        productGlm = bigGlm * smallGlm;

                CHECK_VECTOR4(product, productGlm);
            }

            {
                LibMath::Vector4 productAssignment = big;
                productAssignment *= scalar;

                glm::vec4 productAssignmentGlm = bigGlm;
                productAssignmentGlm *= scalar;

                CHECK_VECTOR4(productAssignment, productAssignmentGlm);
            }

            {
                constexpr LibMath::Vector4 product    = big * scalar;
                constexpr glm::vec4        productGlm = bigGlm * scalar;

                CHECK_VECTOR4(product, productGlm);
            }
        }

        SECTION("Division")
        {
            {
                LibMath::Vector4 quotientAssignment = big;
                quotientAssignment /= small;

                glm::vec4 quotientAssignmentGlm = bigGlm;
                quotientAssignmentGlm /= smallGlm;

                CHECK_VECTOR4(quotientAssignment, quotientAssignmentGlm);
            }

            {
                constexpr LibMath::Vector4 quotient    = big / small;
                constexpr glm::vec4        quotientGlm = bigGlm / smallGlm;

                CHECK_VECTOR4(quotient, quotientGlm);
            }

            {
                LibMath::Vector4 quotientAssignment = big;
                quotientAssignment /= scalar;

                glm::vec4 quotientAssignmentGlm = bigGlm;
                quotientAssignmentGlm /= scalar;

                CHECK_VECTOR4(quotientAssignment, quotientAssignmentGlm);
            }

            {
                constexpr LibMath::Vector4 quotient    = big / scalar;
                constexpr glm::vec4        quotientGlm = bigGlm / scalar;

                CHECK_VECTOR4(quotient, quotientGlm);
            }
        }
    }

    SECTION("Transformation")
    {
        constexpr LibMath::Vector4 origin{ 2.5f, .5f, 2.f, 1.f };
        constexpr LibMath::Vector3 transformation{ -2.f, 0.f, 1.25f };

        constexpr glm::vec4 originGlm{ 2.5f, .5f, 2.f, 1.f };
        constexpr glm::vec3 transformationGlm{ -2.f, 0.f, 1.25f };

        SECTION("Translation")
        {
            LibMath::Vector4 translate = origin;
            translate.translate(transformation);

            glm::vec4 translateGlm = glm::translate(transformationGlm) * originGlm;

            CHECK_VECTOR4(translate, translateGlm);
        }

        SECTION("Scale")
        {
            LibMath::Vector4 scale = origin;
            scale.scale(transformation);

            glm::vec4 scaleGlm = glm::scale(transformationGlm) * originGlm;

            CHECK_VECTOR4(scale, scaleGlm);
        }

        SECTION("Rotation")
        {
            SECTION("Euler Angle")
            {
                LibMath::Vector4 rotate = origin;
                rotate.rotate(LibMath::Radian{ transformation.m_x }, LibMath::Radian{ transformation.m_y },
                    LibMath::Radian{ transformation.m_z });

                glm::vec4 rotateGlm = glm::orientate4(transformationGlm) * originGlm;

                CHECK_VECTOR4(rotate, rotateGlm);
            }

            SECTION("Axis")
            {
                LibMath::Vector4 rotate = origin;
                rotate.rotate(-3_rad, transformation);

                glm::vec4 rotateGlm = glm::rotate(-3.f, transformationGlm) * originGlm;

                CHECK_VECTOR4(rotate, rotateGlm);
            }

            SECTION("Quaternion")
            {
                LibMath::Vector4 rotate = origin;
                rotate.rotate(LibMath::Quaternion(-3_rad, transformation));

                glm::vec4 rotateGlm = glm::rotate(-3.f, transformationGlm) * originGlm;

                CHECK_VECTOR4(rotate, rotateGlm);
            }
        }
    }

    SECTION("Functionality")
    {
        constexpr LibMath::Vector4 base{ 2.5f, .5f, 2.f, 1.f };
        constexpr LibMath::Vector4 other{ 3.75f, 3.f, .75f, 1.f };

        constexpr glm::vec4 baseGlm{ 2.5f, .5f, 2.f, 1.f };
        constexpr glm::vec4 otherGlm{ 3.75f, 3.f, .75f, 1.f };

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
            constexpr LibMath::Vector4 normalized = base.normalized();
            LibMath::Vector4           normalize  = base;
            normalize.normalize();

            glm::vec4 normalizeGlm = glm::normalize(baseGlm);

            CHECK_VECTOR4(normalize, normalizeGlm);
            CHECK_VECTOR4(normalized, normalizeGlm);
        }
    }

    SECTION("Extra")
    {
        constexpr LibMath::Vector4 input{ 2.5f, -.5f, 2.f, 1.f };
        {
            std::stringstream buffer;
            buffer << input;
            CHECK(buffer.str() == "{2.5,-0.5,2,1}");

            buffer << " extra";

            LibMath::Vector4 output;
            buffer >> output;
            CHECK(output == input);

            std::string extra;
            buffer >> extra;
            CHECK(extra == "extra");
        }

        {
            CHECK(input.string() == "{2.5,-0.5,2,1}");

            CHECK(input.stringLong() == "Vector4{ x:2.5, y:-0.5, z:2, w:1 }");
        }
    }

    SECTION("Debug")
    {
#if defined(_DEBUG) || defined(DEBUG) || !defined(NDEBUG)
        constexpr LibMath::Vector4 vector{ 2.5f, .5f, 2.f, 1.f };

        CHECK_THROWS(vector[-1]);
        CHECK_THROWS(vector[4]);
#endif // DEBUG
    }
}
