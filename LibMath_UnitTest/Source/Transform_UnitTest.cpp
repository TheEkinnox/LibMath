#include <Transform.h>

#include <Angle/Degree.h>

#define GLM_FORCE_XYZW_ONLY

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/compatibility.hpp>

using namespace LibMath::Literal;

#define CHECK_MATRIX(matrix, matrixGlm)                                                 \
    for (LibMath::length_t i = 0; i < (matrix).getRowCount(); i++)                      \
        for(LibMath::length_t j = 0; j < (matrix).getColumnCount(); j++)                \
            CHECK((matrix)[(matrix).getIndex(i, j)] == Catch::Approx((matrixGlm)[i][j]))

#define CHECK_LOCAL_TRANSFORM(transform, position, rotation, scale, matrix) \
    CHECK((transform).getPosition() == (position));                         \
    CHECK((transform).getRotation() == (rotation));                         \
    CHECK((transform).getScale() == (scale));                               \
    CHECK_MATRIX((transform).getMatrix(), glm::transpose(matrix));

#define CHECK_WORLD_TRANSFORM(transform, position, rotation, scale, matrix) \
    CHECK((transform).getWorldPosition() == (position));                    \
    CHECK((transform).getWorldRotation() == (rotation));                    \
    CHECK((transform).getWorldScale() == (scale));                          \
    CHECK_MATRIX((transform).getWorldMatrix(), glm::transpose(matrix));

#define CHECK_TRANSFORM(transform, position, rotation, scale, matrix)   \
    CHECK_LOCAL_TRANSFORM(transform, position, rotation, scale, matrix) \
    CHECK_WORLD_TRANSFORM(transform, position, rotation, scale, matrix)

#define DECOMPOSE_GLM(matGlm, pos, rot, scale)        \
{                                                     \
    pos = { matGlm[3].x, matGlm[3].y, matGlm[3].z };  \
                                                      \
    scale = {                                         \
        glm::length(glm::vec3(matGlm[0])),            \
        glm::length(glm::vec3(matGlm[1])),            \
        glm::length(glm::vec3(matGlm[2]))             \
    };                                                \
                                                      \
    const glm::mat3 rotMtx(                           \
        glm::vec3(matGlm[0]) / scale[0],              \
        glm::vec3(matGlm[1]) / scale[1],              \
        glm::vec3(matGlm[2]) / scale[2]               \
    );                                                \
                                                      \
    const glm::quat rotGlm = glm::quat_cast(rotMtx);  \
    rot = { rotGlm.w, rotGlm.x, rotGlm.y, rotGlm.z }; \
}

TEST_CASE("Transform", "[.all][transform]")
{
    const LibMath::Vector3 position{ 2.5f, .5f, 2.f };
    constexpr glm::vec3    positionGlm{ 2.5f, .5f, 2.f };

    const LibMath::Quaternion rotation{ LibMath::cos(45_deg), 0.f, LibMath::sin(45_deg), 0.f };
    const glm::quat           rotationGlm{ glm::cos(glm::radians(45.f)), 0.f, glm::sin(glm::radians(45.f)), 0.f };

    const LibMath::Vector3 scale{ 3.f, .75f, 3.75f };
    constexpr glm::vec3    scaleGlm{ 3.f, .75f, 3.75f };

    const LibMath::Vector3 positionOther{ 4.5f, .9f, 5.4f };
    constexpr glm::vec3    positionOtherGlm{ 4.5f, .9f, 5.4f };

    const LibMath::Quaternion rotationOther{ LibMath::cos(60_deg), LibMath::sin(60_deg), 0.f, 0.f };
    const glm::quat           rotationOtherGlm{ glm::cos(glm::radians(60.f)), glm::sin(glm::radians(60.f)), 0.f, 0.f };

    const LibMath::Vector3 scaleOther{ 8.4f, 2.1f, 10.5f };
    constexpr glm::vec3    scaleOtherGlm{ 8.4f, 2.1f, 10.5f };

    constexpr glm::mat4 idMatGlm{ 1.f };
    glm::mat4 matrixGlm = glm::translate(idMatGlm, positionGlm) * glm::toMat4(rotationGlm) * glm::scale(idMatGlm, scaleGlm);
    glm::mat4 matrixOtherGlm = glm::translate(idMatGlm, positionOtherGlm) * glm::toMat4(rotationOtherGlm) * glm::scale(idMatGlm,
        scaleOtherGlm);

    SECTION("Instantiation")
    {
        // default constructor
        LibMath::Transform empty;
        CHECK_TRANSFORM(empty, LibMath::Vector3{}, LibMath::Quaternion::identity(), LibMath::Vector3::one(), idMatGlm);

        // destructor
        {
            [[maybe_unused]] LibMath::Transform temp;
        }

        // basic constructor

        LibMath::Transform allParam(position, rotation, scale);
        CHECK_TRANSFORM(allParam, position, rotation, scale, matrixGlm);

        // euler angles
        LibMath::TVector3<LibMath::Radian> angles{ 0_deg, 90_deg, 0_deg };
        LibMath::Transform                 euler(position, angles, scale);
        CHECK_TRANSFORM(euler, position, rotation, scale, matrixGlm);

        // copy constructor
        LibMath::Transform copy{ allParam };
        CHECK_TRANSFORM(copy, position, rotation, scale, matrixGlm);

        // assignment operator
        empty = allParam;
        CHECK_TRANSFORM(empty, position, rotation, scale, matrixGlm);

        LibMath::Matrix4 matrix = LibMath::translation(position) * LibMath::rotation(rotation) * LibMath::scaling(scale);

        LibMath::Transform fromMat(matrix);
        CHECK_TRANSFORM(fromMat, position, rotation, scale, matrixGlm);
    }

    SECTION("Accessor")
    {
        // TODO: Transform accessors tests
    }

    SECTION("Arithmetic")
    {
        const LibMath::Transform base{ position, rotation, scale };
        const LibMath::Transform other{ positionOther, rotationOther, scaleOther };

        SECTION("Multiplication")
        {
            glm::mat4 productGlm = matrixGlm * matrixOtherGlm;

            LibMath::Vector3    productPos, productScale;
            LibMath::Quaternion productRot;

            DECOMPOSE_GLM(productGlm, productPos, productRot, productScale);

            {
                LibMath::Transform productAssignment = base;
                productAssignment *= other;

                CHECK_TRANSFORM(productAssignment, productPos, productRot, productScale, productGlm);
            }

            {
                LibMath::Transform product = base * other;

                CHECK_TRANSFORM(product, productPos, productRot, productScale, productGlm);
            }
        }
    }

    SECTION("Functionality")
    {
        const LibMath::Transform base{ position, rotation, scale };
        const LibMath::Transform other{ positionOther, rotationOther, scaleOther };

        SECTION("Inverse")
        {
            LibMath::Transform inverse = base.inverse();
            LibMath::Vector3   invScale = { 1.f / scale.m_x, 1.f / scale.m_y, 1.f / scale.m_z };

            glm::mat4 inverseGlm = glm::translate(idMatGlm, -positionGlm) * glm::toMat4(glm::inverse(rotationGlm)) *
                glm::scale(idMatGlm, { 1.f / scaleGlm.x, 1.f / scaleGlm.y, 1.f / scaleGlm.z });

            CHECK_TRANSFORM(inverse, -position, rotation.inverse(), invScale, inverseGlm);
        }

        SECTION("Interpolation")
        {
            constexpr int interpolationSteps = 10;

            {
                // Local transform interpolation
                const LibMath::Transform lerpStartTransform = LibMath::Transform::interpolate(base, other, 0.f);
                CHECK_TRANSFORM(lerpStartTransform, position, rotation, scale, matrixGlm)

                const LibMath::Transform lerpEndTransform = LibMath::Transform::interpolate(base, other, 1.f);
                CHECK_TRANSFORM(lerpEndTransform, positionOther, rotationOther, scaleOther, matrixOtherGlm)

                for (int step = 1; step < interpolationSteps; ++step)
                {
                    const float alpha = static_cast<float>(step) / interpolationSteps;

                    const LibMath::Transform lerpTransform = LibMath::Transform::interpolate(base, other, alpha);

                    const LibMath::Vector3 lerpPos = LibMath::lerp(position, positionOther, alpha);
                    const glm::vec3        lerpPosGlm = glm::lerp(positionGlm, positionOtherGlm, alpha);

                    const LibMath::Quaternion slerpRotation = LibMath::slerp(rotation, rotationOther, alpha);
                    const glm::quat           slerpRotationGlm = glm::slerp(rotationGlm, rotationOtherGlm, alpha);

                    const LibMath::Vector3 lerpScale = LibMath::lerp(scale, scaleOther, alpha);
                    const glm::vec3        lerpScaleGlm = glm::lerp(scaleGlm, scaleOtherGlm, alpha);

                    glm::mat4 lerpMatrixGlm = glm::translate(idMatGlm, lerpPosGlm) * glm::toMat4(slerpRotationGlm) *
                        glm::scale(idMatGlm, lerpScaleGlm);

                    CHECK_TRANSFORM(lerpTransform, lerpPos, slerpRotation, lerpScale, lerpMatrixGlm);
                }
            }

            {
                // World transform interpolation
                const LibMath::Transform lerpStartTransform = LibMath::Transform::interpolateWorld(base, other, 0.f);
                CHECK_TRANSFORM(lerpStartTransform, position, rotation, scale, matrixGlm)

                const LibMath::Transform lerpEndTransform = LibMath::Transform::interpolateWorld(base, other, 1.f);
                CHECK_TRANSFORM(lerpEndTransform, positionOther, rotationOther, scaleOther, matrixOtherGlm)

                for (int step = 1; step < interpolationSteps; ++step)
                {
                    const float alpha = static_cast<float>(step) / interpolationSteps;

                    const LibMath::Transform lerpTransform = LibMath::Transform::interpolateWorld(base, other, alpha);

                    const LibMath::Vector3 lerpPos = LibMath::lerp(position, positionOther, alpha);
                    const glm::vec3        lerpPosGlm = glm::lerp(positionGlm, positionOtherGlm, alpha);

                    const LibMath::Quaternion slerpRotation = LibMath::slerp(rotation, rotationOther, alpha);
                    const glm::quat           slerpRotationGlm = glm::slerp(rotationGlm, rotationOtherGlm, alpha);

                    const LibMath::Vector3 lerpScale = LibMath::lerp(scale, scaleOther, alpha);
                    const glm::vec3        lerpScaleGlm = glm::lerp(scaleGlm, scaleOtherGlm, alpha);

                    glm::mat4 lerpMatrixGlm = glm::translate(idMatGlm, lerpPosGlm) * glm::toMat4(slerpRotationGlm) *
                        glm::scale(idMatGlm, lerpScaleGlm);

                    CHECK_TRANSFORM(lerpTransform, lerpPos, slerpRotation, lerpScale, lerpMatrixGlm);
                }
            }
        }

        SECTION("Parenting")
        {
            const LibMath::Vector3    parentPos(1.f, 0.f, 2.f);
            const LibMath::Quaternion parentRot(LibMath::Quaternion(90_deg, LibMath::Vector3::up()));
            const LibMath::Vector3    parentScale(1.f, 1.f, 1.f);
            constexpr glm::vec3       parentPosGlm(1.f, 0.f, 2.f);
            const glm::quat           parentRotGlm(glm::angleAxis(glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f)));
            constexpr glm::vec3       parentScaleGlm(1.f, 1.f, 1.f);

            const LibMath::Vector3    childPos(3, 1, 0);
            const LibMath::Quaternion childRot(LibMath::Quaternion(45_deg, LibMath::Vector3::front()));
            const LibMath::Vector3    childScale(.4f, .6f, .8f);
            constexpr glm::vec3       childPosGlm(3, 1, 0);
            const glm::quat           childRotGlm(glm::angleAxis(glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f)));
            constexpr glm::vec3       childScaleGlm(.4f, .6f, .8f);

            LibMath::Transform parent(parentPos, parentRot, parentScale);

            glm::mat4 parentMatGlm = glm::translate(idMatGlm, parentPosGlm) * glm::toMat4(parentRotGlm) *
                glm::scale(idMatGlm, parentScaleGlm);

            glm::mat4 childMatGlm = glm::translate(idMatGlm, childPosGlm) * glm::toMat4(childRotGlm) *
                glm::scale(idMatGlm, childScaleGlm);

            LibMath::Vector3    transformedPos, transformedScale;
            LibMath::Quaternion transformedRot;

            glm::mat4 transformedMatGlm = parentMatGlm * childMatGlm;
            DECOMPOSE_GLM(transformedMatGlm, transformedPos, transformedRot, transformedScale);

            LibMath::Transform childLocal(childPos, childRot, childScale);

            childLocal.setParent(parent, false);

            CHECK_TRANSFORM(parent, parentPos, parentRot, parentScale, parentMatGlm);

            CHECK_LOCAL_TRANSFORM(childLocal, childPos, childRot, childScale, childMatGlm);
            CHECK_WORLD_TRANSFORM(childLocal, transformedPos, transformedRot, transformedScale, transformedMatGlm);

            LibMath::Transform childWorld(childPos, childRot, childScale);

            transformedMatGlm = glm::inverse(parentMatGlm) * childMatGlm;
            DECOMPOSE_GLM(transformedMatGlm, transformedPos, transformedRot, transformedScale);

            childWorld.setParent(parent, true);

            CHECK_TRANSFORM(parent, parentPos, parentRot, parentScale, parentMatGlm);

            CHECK_LOCAL_TRANSFORM(childWorld, transformedPos, transformedRot, transformedScale, transformedMatGlm);
            CHECK_WORLD_TRANSFORM(childWorld, childPos, childRot, childScale, childMatGlm);
        }
    }
}
