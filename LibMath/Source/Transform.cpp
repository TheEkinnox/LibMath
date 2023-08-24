#include "Transform.h"

#include "Matrix/Matrix3.h"

#include "Vector/Vector4.h"

namespace LibMath
{
    Transform::Transform()
        : m_position(Vector3::zero()), m_rotation(Vector3::zero()),
          m_scale(Vector3::one()), m_parent(nullptr)
    {
        Transform::onChange();
    }

    Transform::Transform(const Vector3& position, const Vector3& rotation,
                         const Vector3& scale)
        : m_position(position), m_rotation(rotation), m_scale(scale), m_parent(nullptr)
    {
        Transform::onChange();
    }

    Transform::Transform(const Transform& other)
        : m_position(other.m_position), m_rotation(other.m_rotation),
          m_scale(other.m_scale), m_parent(other.m_parent)
    {
        Transform::onChange();
    }

    Transform::Transform(Transform&& other) noexcept
        : m_position(other.m_position), m_rotation(other.m_rotation),
          m_scale(other.m_scale), m_parent(other.m_parent)
    {
        Transform::onChange();
    }

    Transform::~Transform()
    {
        m_notifier.broadcast(TransformNotifier::ENotificationType::TRANSFORM_DESTROYED);
    }

    Transform& Transform::operator=(const Transform& other)
    {
        if (&other == this)
            return *this;

        m_position = other.m_position;
        m_rotation = other.m_rotation;
        m_scale = other.m_scale;

        onChange();

        return *this;
    }

    Transform& Transform::operator=(Transform&& other) noexcept
    {
        if (&other == this)
            return *this;

        m_position = other.m_position;
        m_rotation = other.m_rotation;
        m_scale = other.m_scale;

        onChange();

        return *this;
    }

    Transform Transform::operator*(const Transform& other) const
    {
        Transform result = *this;
        return result *= other;
    }

    Transform& Transform::operator*=(const Transform& other)
    {
        const Matrix4 newMat = getMatrix() * other.getMatrix();

        m_position = Vector3(newMat(0, 3), newMat(1, 3), newMat(2, 3));
        m_rotation += other.getRotation();
        m_rotation.m_x *= -1.f;
        m_rotation.m_z *= -1.f;
        m_scale *= other.getScale();

        onChange();

        return *this;
    }

    Vector3 Transform::forward() const
    {
        return up().cross(right());
    }

    Vector3 Transform::right() const
    {
        return (m_matrix * Vector4::right()).xyz().normalized();
    }

    Vector3 Transform::up() const
    {
        return (m_matrix * Vector4::up()).xyz().normalized();
    }

    Vector3 Transform::back() const
    {
        return -forward();
    }

    Vector3 Transform::left() const
    {
        return -right();
    }

    Vector3 Transform::down() const
    {
        return -up();
    }

    Vector3 Transform::getPosition() const
    {
        return m_position;
    }

    Vector3 Transform::getRotation() const
    {
        return m_rotation;
    }

    Vector3 Transform::getScale() const
    {
        return m_scale;
    }

    Matrix4x4 Transform::getMatrix() const
    {
        return m_matrix;
    }

    Transform& Transform::setPosition(const Vector3& position)
    {
        m_position = position;
        m_matrix = generateMatrix(m_position, m_rotation, m_scale);

        updateWorldMatrix();

        return *this;
    }

    Transform& Transform::setRotation(const Vector3& rotation)
    {
        m_rotation = rotation;
        m_matrix = generateMatrix(m_position, m_rotation, m_scale);

        updateWorldMatrix();

        return *this;
    }

    Transform& Transform::setScale(const Vector3& scale)
    {
        m_scale = scale;
        m_matrix = generateMatrix(m_position, m_rotation, m_scale);

        updateWorldMatrix();

        return *this;
    }

    Transform& Transform::translate(const Vector3& translation)
    {
        setPosition(m_position + translation);

        return *this;
    }

    Transform& Transform::rotate(const Vector3& rotation)
    {
        setRotation(m_rotation + rotation);

        return *this;
    }

    Transform& Transform::scale(const Vector3& scale)
    {
        setScale(m_scale * scale);

        return *this;
    }

    bool Transform::hasParent() const
    {
        return m_parent != nullptr;
    }

    Transform* Transform::getParent() const
    {
        return m_parent;
    }

    void Transform::setParent(Transform& parent)
    {
        m_parent = &parent;

        m_notificationHandlerId = m_parent->m_notifier.subscribe(std::bind(&Transform::notificationHandler, this,
            std::placeholders::_1));

        updateWorldMatrix();
    }

    bool Transform::removeParent()
    {
        if (m_parent == nullptr)
            return false;

        m_parent->m_notifier.unsubscribe(m_notificationHandlerId);
        m_parent = nullptr;
        updateWorldMatrix();

        return true;
    }

    Vector3 Transform::worldForward() const
    {
        return worldUp().cross(worldRight());
    }

    Vector3 Transform::worldRight() const
    {
        return (m_worldMatrix * Vector4::right()).xyz().normalized();
    }

    Vector3 Transform::worldUp() const
    {
        return (m_worldMatrix * Vector4::up()).xyz().normalized();
    }

    Vector3 Transform::worldBack() const
    {
        return -worldForward();
    }

    Vector3 Transform::worldLeft() const
    {
        return -worldRight();
    }

    Vector3 Transform::worldDown() const
    {
        return -worldUp();
    }

    Vector3 Transform::getWorldPosition() const
    {
        return m_worldPosition;
    }

    Vector3 Transform::getWorldRotation() const
    {
        return m_worldRotation;
    }

    Vector3 Transform::getWorldScale() const
    {
        return m_worldScale;
    }

    Matrix4x4 Transform::getWorldMatrix() const
    {
        return m_worldMatrix;
    }

    Transform& Transform::setWorldPosition(const Vector3& position)
    {
        m_worldPosition = position;
        m_worldMatrix = generateMatrix(m_worldPosition, m_worldRotation, m_worldScale);

        updateLocalMatrix();

        return *this;
    }

    Transform& Transform::setWorldRotation(const Vector3& rotation)
    {
        m_worldRotation = rotation;
        m_worldMatrix = generateMatrix(m_worldPosition, m_worldRotation, m_worldScale);

        updateLocalMatrix();

        return *this;
    }

    Transform& Transform::setWorldScale(const Vector3& scale)
    {
        m_worldScale = scale;
        m_worldMatrix = generateMatrix(m_worldPosition, m_worldRotation, m_worldScale);

        updateLocalMatrix();

        return *this;
    }

    Transform& Transform::worldTranslate(const Vector3& translation)
    {
        setWorldPosition(m_worldPosition + translation);

        return *this;
    }

    Transform& Transform::worldRotate(const Vector3& rotation)
    {
        setWorldRotation(m_worldRotation + rotation);

        return *this;
    }

    Transform& Transform::worldScale(const Vector3& scale)
    {
        setWorldScale(m_worldScale * scale);

        return *this;
    }

    void Transform::onChange()
    {
        m_notifier.broadcast(TransformNotifier::ENotificationType::TRANSFORM_CHANGED);
    }

    void Transform::notificationHandler(TransformNotifier::ENotificationType notificationType)
    {
        switch (notificationType)
        {
        case TransformNotifier::ENotificationType::TRANSFORM_CHANGED:
            updateWorldMatrix();
            break;
        case TransformNotifier::ENotificationType::TRANSFORM_DESTROYED:
            m_position = m_worldPosition;
            m_rotation = m_worldRotation;
            m_scale = m_worldScale;

            m_matrix = generateMatrix(m_position, m_rotation, m_scale);

            m_parent = nullptr;
            updateWorldMatrix();
            break;
        default: ;
        }
    }

    Matrix4 Transform::generateMatrix(const Vector3& position, const Vector3& rotation, const Vector3& scale)
    {
        return translation(position)
            * LibMath::rotation(rotation, false)
            * scaling(scale);
    }

    void Transform::decomposeMatrix(const Matrix4& matrix, Vector3& position, Vector3& rotation, Vector3& scale)
    {
        position.m_x = matrix(0, 3);
        position.m_y = matrix(1, 3);
        position.m_z = matrix(2, 3);

        Vector3 columns[3] =
        {
            { matrix(0, 0), matrix(1, 0), matrix(2, 0) },
            { matrix(0, 1), matrix(1, 1), matrix(2, 1) },
            { matrix(0, 2), matrix(1, 2), matrix(2, 2) },
        };

        scale.m_x = columns[0].magnitude();
        scale.m_y = columns[1].magnitude();
        scale.m_z = columns[2].magnitude();

        if (scale.m_x > 0)
            columns[0] /= scale.m_x;

        if (scale.m_y > 0)
            columns[1] /= scale.m_y;

        if (scale.m_z > 0)
            columns[2] /= scale.m_z;

        Matrix3 rotationMatrix;

        rotationMatrix(0, 0) = columns[0].m_x;
        rotationMatrix(0, 1) = columns[1].m_x;
        rotationMatrix(0, 2) = columns[2].m_x;
        rotationMatrix(1, 0) = columns[0].m_y;
        rotationMatrix(1, 1) = columns[1].m_y;
        rotationMatrix(1, 2) = columns[2].m_y;
        rotationMatrix(2, 0) = columns[0].m_z;
        rotationMatrix(2, 1) = columns[1].m_z;
        rotationMatrix(2, 2) = columns[2].m_z;

        rotation.m_x = asinf(-rotationMatrix(1, 2)); // Pitch

        if (cosf(rotation.m_x) > 0.0001f) // Not at poles
        {
            rotation.m_y = atan2f(rotationMatrix(0, 2), rotationMatrix(2, 2)); // Yaw
            rotation.m_z = atan2f(rotationMatrix(1, 0), rotationMatrix(1, 1)); // Roll
        }
        else
        {
            rotation.m_y = 0.0f;                                                // Yaw
            rotation.m_z = atan2f(-rotationMatrix(0, 1), rotationMatrix(0, 0)); // Roll
        }

        rotation *= g_rad2Deg;
    }

    void Transform::updateLocalMatrix()
    {
        m_matrix = m_parent ? m_parent->m_worldMatrix.inverse() * m_worldMatrix : m_worldMatrix;
        decomposeMatrix(m_matrix, m_position, m_rotation, m_scale);

        onChange();
    }

    void Transform::updateWorldMatrix()
    {
        m_worldMatrix = m_parent ? m_parent->m_worldMatrix * m_matrix : m_matrix;
        decomposeMatrix(m_worldMatrix, m_worldPosition, m_worldRotation, m_worldScale);

        onChange();
    }
}
