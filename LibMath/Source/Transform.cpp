#include "Transform.h"

#include "Matrix/Matrix3.h"

#include "Vector/Vector4.h"

namespace LibMath
{
    Transform::Transform()
        : Transform(Vector3::zero(), Quaternion::identity(), Vector3::one())
    {
    }

    Transform::Transform(const Vector3& position, const TVector3<Radian>& euler, const Vector3& scale)
        : Transform(position, Quaternion::fromEuler(euler, ERotationOrder::ZYX), scale)
    {
    }

    Transform::Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
        : m_position(position), m_rotation(rotation), m_scale(scale), m_parent(nullptr)
    {
        m_matrix = generateMatrix(m_position, m_rotation, m_scale);
        updateWorldMatrix();
    }

    Transform::Transform(Matrix4x4 matrix)
        : m_matrix(std::move(matrix)), m_parent(nullptr)
    {
        decomposeMatrix(m_matrix, m_position, m_rotation, m_scale);
        updateWorldMatrix();
    }

    Transform::Transform(const Transform& other)
        : m_position(other.m_position), m_rotation(other.m_rotation), m_scale(other.m_scale),
        m_worldPosition(other.m_worldPosition), m_worldRotation(other.m_worldRotation), m_worldScale(other.m_worldScale),
        m_matrix(other.m_matrix), m_worldMatrix(other.m_worldMatrix), m_parent(other.m_parent)
    {
        Transform::onChange();
    }

    Transform::Transform(Transform&& other) noexcept
        : m_position(other.m_position), m_rotation(other.m_rotation), m_scale(other.m_scale),
        m_worldPosition(other.m_worldPosition), m_worldRotation(other.m_worldRotation), m_worldScale(other.m_worldScale),
        m_matrix(other.m_matrix), m_worldMatrix(other.m_worldMatrix), m_parent(other.m_parent)
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

        m_worldPosition = other.m_worldPosition;
        m_worldRotation = other.m_worldRotation;
        m_worldScale = other.m_worldScale;
        m_worldMatrix = other.m_worldMatrix;

        updateLocalMatrix();

        return *this;
    }

    Transform& Transform::operator=(Transform&& other) noexcept
    {
        if (&other == this)
            return *this;

        m_worldPosition = other.m_worldPosition;
        m_worldRotation = other.m_worldRotation;
        m_worldScale = other.m_worldScale;
        m_worldMatrix = other.m_worldMatrix;

        updateLocalMatrix();

        return *this;
    }

    Transform& Transform::operator*=(const Transform& other)
    {
        m_matrix *= other.getWorldMatrix();
        decomposeMatrix(m_matrix, m_position, m_rotation, m_scale);
        updateWorldMatrix();

        return *this;
    }

    Transform Transform::operator*(const Transform& other) const
    {
        Transform result = *this;
        return result *= other;
    }

    Vector3 Transform::forward() const
    {
        return up().cross(right());
    }

    Vector3 Transform::right() const
    {
        Vector3 up = Vector3::up();
        up.rotate(m_rotation);
        return up;
    }

    Vector3 Transform::up() const
    {
        Vector3 up = Vector3::up();
        up.rotate(m_rotation);
        return up;
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

    Quaternion Transform::getRotation() const
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

    Transform& Transform::setEuler(const TVector3<Radian>& euler)
    {
        return setRotation(Quaternion::fromEuler(euler));
    }

    Transform& Transform::setEuler(const TVector3<Radian>& euler, const ERotationOrder rotationOrder)
    {
        return setRotation(Quaternion::fromEuler(euler, rotationOrder));
    }

    Transform& Transform::setRotation(const Quaternion& rotation)
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

    Transform& Transform::setMatrix(const Matrix4x4& matrix)
    {
        m_matrix = matrix;
        decomposeMatrix(m_matrix, m_position, m_rotation, m_scale);

        updateWorldMatrix();

        return *this;
    }

    Transform& Transform::translate(const Vector3& translation)
    {
        setPosition(m_position + translation);

        return *this;
    }

    Transform& Transform::rotate(const TVector3<Radian>& euler)
    {
        setRotation(m_rotation * Quaternion::fromEuler(euler));

        return *this;
    }

    Transform& Transform::rotate(const Quaternion& rotation)
    {
        setRotation(m_rotation * rotation);

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

    void Transform::setParent(Transform& parent, const bool keepWorld)
    {
        if (m_parent == &parent)
            return;

        m_parent = &parent;

        m_notificationHandlerId = m_parent->m_notifier.subscribe([this](const TransformNotifier::ENotificationType notificationType)
        {
            notificationHandler(notificationType);
        });

        if (keepWorld)
            updateLocalMatrix();
        else
            updateWorldMatrix();
    }

    bool Transform::removeParent(const bool keepWorld)
    {
        if (m_parent == nullptr)
            return false;

        m_parent->m_notifier.unsubscribe(m_notificationHandlerId);
        m_parent = nullptr;

        if (keepWorld)
            updateLocalMatrix();
        else
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

    Quaternion Transform::getWorldRotation() const
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

    Transform& Transform::setWorldEuler(const TVector3<Radian>& euler)
    {
        return setWorldRotation(Quaternion::fromEuler(euler));
    }

    Transform& Transform::setWorldEuler(const TVector3<Radian>& euler, const ERotationOrder rotationOrder)
    {
        return setWorldRotation(Quaternion::fromEuler(euler, rotationOrder));
    }

    Transform& Transform::setWorldRotation(const Quaternion& rotation)
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

    Transform& Transform::setWorldMatrix(const Matrix4x4& matrix)
    {
        m_worldMatrix = matrix;
        decomposeMatrix(m_worldMatrix, m_worldPosition, m_worldRotation, m_worldScale);

        updateLocalMatrix();

        return *this;
    }

    Transform& Transform::worldTranslate(const Vector3& translation)
    {
        setWorldPosition(m_worldPosition + translation);

        return *this;
    }

    Transform& Transform::worldRotate(const TVector3<Radian>& euler)
    {
        setWorldRotation(m_worldRotation * Quaternion::fromEuler(euler));

        return *this;
    }

    Transform& Transform::worldRotate(const Quaternion& rotation)
    {
        setWorldRotation(m_worldRotation * rotation);

        return *this;
    }

    Transform& Transform::worldScale(const Vector3& scale)
    {
        setWorldScale(m_worldScale * scale);

        return *this;
    }

    void Transform::invert()
    {
        m_position *= -1.f;
        m_rotation = m_worldRotation.inverse();
        m_scale = { 1.f / m_scale.m_x, 1.f / m_scale.m_y, 1.f / m_scale.m_z };
        m_matrix = generateMatrix(m_position, m_rotation, m_scale);

        updateWorldMatrix();
    }

    Transform Transform::inverse() const
    {
        Transform tmp = *this;
        tmp.invert();
        return tmp;
    }

    void Transform::invertWorld()
    {
        m_worldPosition *= -1.f;
        m_worldRotation = m_worldRotation.inverse();
        m_worldScale = { 1.f / m_worldScale.m_x, 1.f / m_worldScale.m_y, 1.f / m_worldScale.m_z };
        m_worldMatrix = generateMatrix(m_worldPosition, m_worldRotation, m_worldScale);

        updateLocalMatrix();
    }

    Transform Transform::inverseWorld() const
    {
        Transform tmp = *this;
        tmp.invertWorld();
        return tmp;
    }

    Transform Transform::interpolate(Transform from, const Transform& to, const float t)
    {
        from.m_position = lerp(from.m_position, to.m_position, t);
        from.m_rotation = slerp(from.m_rotation, to.m_rotation, t);
        from.m_scale = lerp(from.m_scale, to.m_scale, t);
        from.m_matrix = generateMatrix(from.m_position, from.m_rotation, from.m_scale);

        from.updateWorldMatrix();

        return from;
    }

    Transform Transform::interpolateWorld(Transform from, const Transform& to, const float t)
    {
        from.m_worldPosition = lerp(from.m_worldPosition, to.m_worldPosition, t);
        from.m_worldRotation = slerp(from.m_worldRotation, to.m_worldRotation, t);
        from.m_worldScale = lerp(from.m_worldScale, to.m_worldScale, t);
        from.m_worldMatrix = generateMatrix(from.m_worldPosition, from.m_worldRotation, from.m_worldScale);

        from.updateLocalMatrix();

        return from;
    }

    Matrix4x4 Transform::generateMatrix(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
    {
        return translation(position)
            * LibMath::rotation(rotation)
            * scaling(scale);
    }

    void Transform::decomposeMatrix(const Matrix4x4& matrix, Vector3& position, Quaternion& rotation, Vector3& scale)
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

        rotation = Quaternion(rotationMatrix);
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
