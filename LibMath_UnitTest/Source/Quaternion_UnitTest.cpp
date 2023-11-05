#include <Quaternion.h>

#include <Angle/Degree.h>

#define GLM_FORCE_XYZW_ONLY
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace LibMath::Literal;

#define CHECK_QUATERNION(quaternion, quaternionGlm) \
    CHECK((quaternion).m_x == Catch::Approx((quaternionGlm).x)); \
    CHECK((quaternion).m_y == Catch::Approx((quaternionGlm).y)); \
    CHECK((quaternion).m_z == Catch::Approx((quaternionGlm).z)); \
    CHECK((quaternion).m_w == Catch::Approx((quaternionGlm).w))

TEST_CASE("Quaternion", "[.all][quaternion]")
{
    SECTION("Instantiation")
    {
        // default constructor
        LibMath::Quaternion empty;
        glm::quat           emptyGlm{};
        CHECK_QUATERNION(empty, emptyGlm);

        // destructor
        {
            [[maybe_unused]] LibMath::Quaternion temp;
        }

        // basic constructor
        LibMath::Quaternion allParam{ 2.5f, .5f, 2.f, 3.f };
        glm::quat           allParamGlm{ 2.5f, .5f, 2.f, 3.f };
        CHECK_QUATERNION(allParam, allParamGlm);

        LibMath::QuaternionD dAllParam{ 2.5, .5, 2., 3. };
        glm::dquat           dAllParamGlm{ 2.5, .5, 2., 3. };
        CHECK_QUATERNION(dAllParam, dAllParamGlm);

        LibMath::Quaternion oneParam{ 2.5f };
        glm::quat           oneParamGlm{ 2.5f, 2.5f, 2.5f, 2.5f };
        CHECK_QUATERNION(oneParam, oneParamGlm);

        LibMath::QuaternionD dOneParam{ 2.5 };
        glm::dquat           dOneParamGlm{ 2.5, 2.5, 2.5, 2.5 };
        CHECK_QUATERNION(dOneParam, dOneParamGlm);

        LibMath::Quaternion scalarVector{ 2.5f, LibMath::Vector3(.5f, 2.f, 3.f) };
        glm::quat           scalarVectorGlm{ 2.5f, glm::vec3(.5f, 2.f, 3.f) };
        CHECK_QUATERNION(scalarVector, scalarVectorGlm);

        LibMath::QuaternionD dScalarVector{ 2.5, LibMath::Vector3(.5, 2., 3.) };
        glm::dquat           dScalarVectorGlm{ 2.5, glm::dvec3(.5, 2., 3.) };
        CHECK_QUATERNION(dScalarVector, dScalarVectorGlm);

        // copy constructor
        LibMath::Quaternion copy{ allParam };
        glm::quat           copyGlm{ allParamGlm };
        CHECK_QUATERNION(copy, copyGlm);

        LibMath::QuaternionD dCopy{ dAllParam };
        glm::dquat           dCopyGlm{ dAllParamGlm };
        CHECK_QUATERNION(dCopy, dCopyGlm);

        LibMath::Quaternion convCopy{ dAllParam };
        glm::quat           convCopyGlm{ dAllParamGlm };
        CHECK_QUATERNION(convCopy, convCopyGlm);

        LibMath::QuaternionD dConvCopy{ allParam };
        glm::dquat           dConvCopyGlm{ allParamGlm };
        CHECK_QUATERNION(dConvCopy, dConvCopyGlm);

        // assignment operator
        empty = allParam;
        emptyGlm = allParamGlm;
        CHECK_QUATERNION(empty, emptyGlm);

        empty = dAllParam;
        emptyGlm = dAllParamGlm;
        CHECK_QUATERNION(empty, emptyGlm);

        // angle-axis
        LibMath::Quaternion axisAngle{ 180_deg, LibMath::Vector3(1, 0, 0) };
        glm::quat           axisAngleGlm{ glm::angleAxis<float>(glm::radians(180.f), glm::vec3(1, 0, 0)) };
        CHECK_QUATERNION(axisAngle, axisAngleGlm);

        LibMath::QuaternionD dAxisAngle{ 180_deg, LibMath::TVector3<double>(1, 0, 0) };
        glm::dquat           dAxisAngleGlm{ glm::angleAxis<double>(glm::radians(180.f), glm::dvec3(1, 0, 0)) };
        CHECK_QUATERNION(dAxisAngle, dAxisAngleGlm);

        // yaw-pitch-roll
        LibMath::Quaternion yawPitchRoll{ 90_deg, 75_deg, 30_deg };
        LibMath::Quaternion yawPitchRollVec{ LibMath::Vector3(90.f, 75.f, 30.f), false };
        glm::quat           yawPitchRollGlm{ glm::yawPitchRoll(glm::radians(90.f), glm::radians(75.f), glm::radians(30.f)) };
        CHECK_QUATERNION(yawPitchRoll, yawPitchRollGlm);
        CHECK_QUATERNION(yawPitchRollVec, yawPitchRollGlm);

        LibMath::QuaternionD dYawPitchRoll{ 90_deg, 75_deg, 30_deg };
        LibMath::QuaternionD dYawPitchRollVec{ LibMath::TVector3<double>(90., 75., 30.), false };
        glm::dquat           dYawPitchRollGlm{ glm::yawPitchRoll(glm::radians(90.), glm::radians(75.), glm::radians(30.)) };
        CHECK_QUATERNION(dYawPitchRoll, dYawPitchRollGlm);
        CHECK_QUATERNION(dYawPitchRollVec, dYawPitchRollGlm);

        // euler
        LibMath::Quaternion euler = LibMath::Quaternion::fromEuler(90_deg, 75_deg, 30_deg);
        LibMath::Quaternion eulerVec = LibMath::Quaternion::fromEuler(LibMath::Vector3(90., 75., 30.), false);
        glm::quat           eulerGlm = glm::orientate4(glm::vec3(glm::radians(90.f), glm::radians(75.f), glm::radians(30.f)));
        CHECK_QUATERNION(euler, eulerGlm);
        CHECK_QUATERNION(eulerVec, eulerGlm);

        euler = LibMath::Quaternion::fromEuler(90_deg, 75_deg, 30_deg, LibMath::ERotationOrder::XYZ);
        eulerVec = LibMath::Quaternion::fromEuler(LibMath::Vector3(90., 75., 30.), false, LibMath::ERotationOrder::XYZ);
        eulerGlm = glm::angleAxis(glm::radians(90.f), glm::vec3(1, 0, 0)) * glm::angleAxis(glm::radians(75.f), glm::vec3(0, 1, 0))
            * glm::angleAxis(glm::radians(30.f), glm::vec3(0, 0, 1));
        CHECK_QUATERNION(euler, eulerGlm);

        euler = LibMath::Quaternion::fromEuler(90_deg, 75_deg, 30_deg, LibMath::ERotationOrder::XZY);
        eulerVec = LibMath::Quaternion::fromEuler(LibMath::Vector3(90., 75., 30.), false, LibMath::ERotationOrder::XZY);
        eulerGlm = glm::angleAxis(glm::radians(90.f), glm::vec3(1, 0, 0)) * glm::angleAxis(glm::radians(30.f), glm::vec3(0, 0, 1))
            * glm::angleAxis(glm::radians(75.f), glm::vec3(0, 1, 0));
        CHECK_QUATERNION(euler, eulerGlm);

        euler = LibMath::Quaternion::fromEuler(90_deg, 75_deg, 30_deg, LibMath::ERotationOrder::YXZ);
        eulerVec = LibMath::Quaternion::fromEuler(LibMath::Vector3(90., 75., 30.), false, LibMath::ERotationOrder::YXZ);
        eulerGlm = glm::angleAxis(glm::radians(75.f), glm::vec3(0, 1, 0)) * glm::angleAxis(glm::radians(90.f), glm::vec3(1, 0, 0))
            * glm::angleAxis(glm::radians(30.f), glm::vec3(0, 0, 1));
        CHECK_QUATERNION(euler, eulerGlm);

        euler = LibMath::Quaternion::fromEuler(90_deg, 75_deg, 30_deg, LibMath::ERotationOrder::YZX);
        eulerVec = LibMath::Quaternion::fromEuler(LibMath::Vector3(90., 75., 30.), false, LibMath::ERotationOrder::YZX);
        eulerGlm = glm::angleAxis(glm::radians(75.f), glm::vec3(0, 1, 0)) * glm::angleAxis(glm::radians(30.f), glm::vec3(0, 0, 1))
            * glm::angleAxis(glm::radians(90.f), glm::vec3(1, 0, 0));
        CHECK_QUATERNION(euler, eulerGlm);

        euler = LibMath::Quaternion::fromEuler(90_deg, 75_deg, 30_deg, LibMath::ERotationOrder::ZXY);
        eulerVec = LibMath::Quaternion::fromEuler(LibMath::Vector3(90., 75., 30.), false, LibMath::ERotationOrder::ZXY);
        eulerGlm = glm::angleAxis(glm::radians(30.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(90.f), glm::vec3(1, 0, 0))
            * glm::angleAxis(glm::radians(75.f), glm::vec3(0, 1, 0));
        CHECK_QUATERNION(euler, eulerGlm);

        euler = LibMath::Quaternion::fromEuler(90_deg, 75_deg, 30_deg, LibMath::ERotationOrder::ZYX);
        eulerVec = LibMath::Quaternion::fromEuler(LibMath::Vector3(90., 75., 30.), false, LibMath::ERotationOrder::ZYX);
        eulerGlm = glm::angleAxis(glm::radians(30.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(75.f), glm::vec3(0, 1, 0))
            * glm::angleAxis(glm::radians(90.f), glm::vec3(1, 0, 0));
        CHECK_QUATERNION(euler, eulerGlm);

        CHECK(sizeof(LibMath::Quaternion) == sizeof(glm::quat));
    }

    SECTION("Accessor")
    {
        constexpr float     x = 2.5f;
        constexpr float     y = .5f;
        constexpr float     z = 2.f;
        constexpr float     w = 3.f;
        LibMath::Quaternion quaternion{ w, x, y, z };

        {
            const LibMath::Quaternion& quaternionConst = quaternion;
            CHECK(quaternionConst[0] == Catch::Approx(x));
            CHECK(quaternionConst[1] == Catch::Approx(y));
            CHECK(quaternionConst[2] == Catch::Approx(z));
            CHECK(quaternionConst[3] == Catch::Approx(w));
        }

        {
            const LibMath::Quaternion& quaternionConst = quaternion;
            CHECK(quaternionConst['x'] == Catch::Approx(x));
            CHECK(quaternionConst['y'] == Catch::Approx(y));
            CHECK(quaternionConst['z'] == Catch::Approx(z));
            CHECK(quaternionConst['w'] == Catch::Approx(w));
        }

        {
            const LibMath::Quaternion& quaternionConst = quaternion;
            CHECK(quaternionConst['X'] == Catch::Approx(x));
            CHECK(quaternionConst['Y'] == Catch::Approx(y));
            CHECK(quaternionConst['Z'] == Catch::Approx(z));
            CHECK(quaternionConst['W'] == Catch::Approx(w));
        }

        {
            quaternion[0] += 1.f;
            quaternion[1] += 1.f;
            quaternion[2] += 1.f;
            quaternion[3] += 1.f;
            CHECK(quaternion[0] == Catch::Approx(x + 1.f));
            CHECK(quaternion[1] == Catch::Approx(y + 1.f));
            CHECK(quaternion[2] == Catch::Approx(z + 1.f));
            CHECK(quaternion[3] == Catch::Approx(w + 1.f));
        }
    }

    SECTION("Comparator")
    {
        // compare with self
        LibMath::Quaternion self{ 2.5f, .5f, 2.f, 3.f };
        CHECK(self == self);

        // compare with same
        CHECK(LibMath::Quaternion{ 2.5f, .5f, 2.f, 3.f } == LibMath::Quaternion{ 2.5f, .5f, 2.f, 3.f });
        CHECK(LibMath::Quaternion{ 2.5f, .5f, 2.f, 3.f } == LibMath::QuaternionD{ 2.5, .5, 2., 3. });
        CHECK(LibMath::QuaternionD{ 2.5, .5, 2., 3. } == LibMath::Quaternion{ 2.5f, .5f, 2.f, 3.f });

        // trying to find copy/paste mistake
        LibMath::Quaternion twos{ 2.f, 2.f, 2.f, 2.f };
        CHECK_FALSE(LibMath::Quaternion{ .5f, 2.f, 2.f, 2.f } == twos);
        CHECK_FALSE(LibMath::Quaternion{ 2.f, .5f, 2.f, 2.f } == twos);
        CHECK_FALSE(LibMath::Quaternion{ 2.f, 2.f, .5f, 2.f } == twos);
        CHECK_FALSE(LibMath::Quaternion{ 2.f, 2.f, 2.f, .5f } == twos);
        CHECK_FALSE(twos == LibMath::Quaternion{ .5f, 2.f, 2.f, 2.f });
        CHECK_FALSE(twos == LibMath::Quaternion{ 2.f, .5f, 2.f, 2.f });
        CHECK_FALSE(twos == LibMath::Quaternion{ 2.f, 2.f, .5f, 2.f });
        CHECK_FALSE(twos == LibMath::Quaternion{ 2.f, 2.f, 2.f, .5f });

        // testing comparison functionality
        LibMath::Quaternion small{ 2.5f, .5f, 2.f, 3.f };
        LibMath::Quaternion big{ 3.75f, 3.f, .75f, 4.5f };

        CHECK(big > small);
        CHECK_FALSE(small > big);

        CHECK(small < big);
        CHECK_FALSE(big < small);

        CHECK_FALSE(self.isUnit());
        CHECK(LibMath::Quaternion{ 0.7012197f, 0.4634621f, 0.4627225f, 0.2817475f }.isUnit());
    }

    SECTION("Constant")
    {
        CHECK_QUATERNION(LibMath::Quaternion::identity(), glm::quat(1.f, 0.f, 0.f, 0.f));
        CHECK_QUATERNION(LibMath::QuaternionD::identity(), glm::dquat(1., 0., 0., 0));
    }

    SECTION("Arithmetic")
    {
        constexpr LibMath::Quaternion small{ 2.5f, .5f, 2.f, 3.f };
        constexpr LibMath::Quaternion big{ 3.75f, 3.f, .75f, 4.5f };

        constexpr glm::quat smallGlm{ 2.5f, .5f, 2.f, 3.f };
        constexpr glm::quat bigGlm{ 3.75f, 3.f, .75f, 4.5f };

        constexpr float     scalar = 6.25f;
        constexpr glm::quat scalarGlm{ scalar, 0, 0, 0 };

        SECTION("Inverse")
        {
            LibMath::Quaternion inverse = -LibMath::Quaternion{ 3.7f, 3.f, .7f, 4.4f };

            glm::quat inverseGlm = -glm::quat{ 3.7f, 3.f, .7f, 4.4f };

            CHECK_QUATERNION(inverse, inverseGlm);
        }

        SECTION("Addition")
        {
            {
                LibMath::Quaternion sumAssignment = big;
                sumAssignment += small;

                glm::quat sumAssignmentGlm = bigGlm;
                sumAssignmentGlm += smallGlm;

                CHECK_QUATERNION(sumAssignment, sumAssignmentGlm);
            }

            {
                LibMath::Quaternion sumAssignment = big;
                sumAssignment += scalar;

                glm::quat sumAssignmentGlm = bigGlm;
                sumAssignmentGlm += scalarGlm;

                CHECK_QUATERNION(sumAssignment, sumAssignmentGlm);
            }

            {
                LibMath::Quaternion sum = big + small;

                glm::quat sumGlm = bigGlm + smallGlm;

                CHECK_QUATERNION(sum, sumGlm);
            }

            {
                LibMath::Quaternion sum = big + scalar;

                glm::quat sumGlm = bigGlm + scalarGlm;

                CHECK_QUATERNION(sum, sumGlm);
            }
        }

        SECTION("Substraction")
        {
            {
                LibMath::Quaternion differenceAssignment = big;
                differenceAssignment -= small;

                glm::quat differenceAssignmentGlm = bigGlm;
                differenceAssignmentGlm -= smallGlm;

                CHECK_QUATERNION(differenceAssignment, differenceAssignmentGlm);
            }

            {
                LibMath::Quaternion differenceAssignment = big;
                differenceAssignment -= scalar;

                glm::quat differenceAssignmentGlm = bigGlm;
                differenceAssignmentGlm -= scalarGlm;

                CHECK_QUATERNION(differenceAssignment, differenceAssignmentGlm);
            }

            {
                LibMath::Quaternion difference = big - small;

                glm::quat differenceGlm = bigGlm - smallGlm;

                CHECK_QUATERNION(difference, differenceGlm);
            }

            {
                LibMath::Quaternion difference = big - scalar;

                glm::quat differenceGlm = bigGlm - scalarGlm;

                CHECK_QUATERNION(difference, differenceGlm);
            }
        }

        SECTION("Multiplication")
        {
            {
                LibMath::Quaternion productAssignment = big;
                productAssignment *= small;

                glm::quat productAssignmentGlm = bigGlm;
                productAssignmentGlm *= smallGlm;

                CHECK_QUATERNION(productAssignment, productAssignmentGlm);
            }

            {
                LibMath::Quaternion productAssignment = big;
                productAssignment *= scalar;

                glm::quat productAssignmentGlm = bigGlm;
                productAssignmentGlm *= scalar;

                CHECK_QUATERNION(productAssignment, productAssignmentGlm);
            }

            {
                LibMath::Quaternion product = big * small;

                glm::quat productGlm = bigGlm * smallGlm;

                CHECK_QUATERNION(product, productGlm);
            }

            {
                LibMath::Quaternion product = big * scalar;

                glm::quat productGlm = bigGlm * scalar;

                CHECK_QUATERNION(product, productGlm);
            }
        }

        SECTION("Division")
        {
            {
                LibMath::Quaternion quotientAssignment = big;
                quotientAssignment /= small;

                glm::quat quotientAssignmentGlm = bigGlm;
                quotientAssignmentGlm *= glm::inverse(smallGlm);

                CHECK_QUATERNION(quotientAssignment, quotientAssignmentGlm);
            }

            {
                LibMath::Quaternion quotientAssignment = big;
                quotientAssignment /= scalar;

                glm::quat quotientAssignmentGlm = bigGlm;
                quotientAssignmentGlm /= scalar;

                CHECK_QUATERNION(quotientAssignment, quotientAssignmentGlm);
            }

            {
                LibMath::Quaternion quotient = big / small;

                glm::quat quotientGlm = bigGlm * glm::inverse(smallGlm);

                CHECK_QUATERNION(quotient, quotientGlm);

                CHECK(quotient * small == big);
            }

            {
                LibMath::Quaternion quotient = big / scalar;

                glm::quat quotientGlm = bigGlm / scalar;

                CHECK_QUATERNION(quotient, quotientGlm);
            }
        }
    }

    SECTION("Functionality")
    {
        constexpr LibMath::Quaternion base{ 2.5f, .5f, 2.f, 3.f };
        constexpr LibMath::Quaternion other{ 3.75f, 3.f, .75f, 4.5f };

        constexpr glm::quat baseGlm{ 2.5f, .5f, 2.f, 3.f };
        constexpr glm::quat otherGlm{ 3.75f, 3.f, .75f, 4.5f };

        SECTION("Conversion")
        {
            const LibMath::Vector3 vectorPart = base;

            CHECK(vectorPart.m_x == Catch::Approx(base.m_x));
            CHECK(vectorPart.m_y == Catch::Approx(base.m_y));
            CHECK(vectorPart.m_z == Catch::Approx(base.m_z));
        }

        SECTION("Magnitude")
        {
            {
                float magnitude = base.magnitude();

                float magnitudeGlm = glm::length(baseGlm);

                CHECK(magnitude == Catch::Approx(magnitudeGlm));
            }

            {
                float magnitudeSquare = base.magnitudeSquared();

                float magnitudeSquareGlm = glm::length2(baseGlm);

                CHECK(magnitudeSquare == Catch::Approx(magnitudeSquareGlm));
            }
        }

        SECTION("Dot")
        {
            float dot = base.dot(other);
            float dotGlm = glm::dot(baseGlm, otherGlm);

            CHECK(dot == Catch::Approx(dotGlm));
        }

        SECTION("Conjugate")
        {
            LibMath::Quaternion conjugate = base.conjugate();
            glm::quat           conjugateGlm = glm::conjugate(baseGlm);

            CHECK_QUATERNION(conjugate, conjugateGlm);
        }

        SECTION("Inverse")
        {
            LibMath::Quaternion inverse = base.inverse();

            glm::quat inverseGlm = glm::inverse(baseGlm);

            CHECK_QUATERNION(inverse, inverseGlm);
        }

        SECTION("Normal")
        {
            LibMath::Quaternion normalize = base;
            normalize.normalize();

            glm::quat normalizeGlm = glm::normalize(baseGlm);

            CHECK_QUATERNION(normalize, normalizeGlm);

            CHECK_QUATERNION(base.normalized(), normalizeGlm);
        }
    }

    SECTION("Extra")
    {
        constexpr LibMath::Quaternion input{ 3.f, 2.5f, -.5f, 2.f };

        {
            std::stringstream buffer;
            buffer << input;
            CHECK(buffer.str() == "{2.5,-0.5,2,3}");

            buffer << "{2.5, -0.5, 2, 3}";
            buffer << " extra";

            LibMath::Quaternion output;
            buffer >> output;
            CHECK(output == input);

            LibMath::Quaternion outputWithSpaces;
            buffer >> outputWithSpaces;
            CHECK(outputWithSpaces == input);

            std::string extra;
            buffer >> extra;
            CHECK(extra == "extra");
        }

        {
            CHECK(input.string() == "{2.5,-0.5,2,3}");

            CHECK(input.stringLong() == "Quaternion{ x:2.5, y:-0.5, z:2, w:3 }");
        }

        {
            CHECK(input.getArray() == &input.m_x);
            CHECK(input.getArray() + 1 == &input.m_y);
            CHECK(input.getArray() + 2 == &input.m_z);
            CHECK(input.getArray() + 3 == &input.m_w);
        }
    }

    SECTION("Debug")
    {
#if (defined _DEBUG) || (! defined NDEBUG)
        LibMath::Quaternion quaternion{ 2.5f };

        CHECK_THROWS(quaternion[-1]);
        CHECK_THROWS(quaternion[4]);
#endif // DEBUG
    }
}
