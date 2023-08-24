#pragma once
#include "TransformNotifier.h"

#include "Matrix/Matrix4.h"
#include "Vector/Vector3.h"

namespace LibMath
{
	class Transform
	{
	public:
		/**
		 * \brief Creates a transform with no translation, no rotation
		 * and a scale of 1
		 */
		Transform();

		/**
		 * \brief Creates a transform with the given position, rotation
		 * and scale
		 * \param position The transform's initial position
		 * \param rotation The transform's initial rotation
		 * \param scale The transform's initial scale
		 */
		Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale);

		/**
		 * \brief Creates a copy of the given transform
		 * \param other The transform to copy
		 */
		Transform(const Transform& other);

		/**
		 * \brief Creates a move copy of the given transform
		 * \param other The transform to move
		 */
		Transform(Transform&& other) noexcept;

		/**
		 * \brief Destroys the transform
		 */
		virtual ~Transform();

		/**
		 * \brief Copies the given transform's data into the current one
		 * \param other The transform to copy
		 * \return A reference to the current transform
		 */
		Transform& operator=(const Transform& other);

		/**
		 * \brief Moves the given transform's data into the current one
		 * \param other The transform to move
		 * \return A reference to the current transform
		 */
		Transform& operator=(Transform&& other) noexcept;

		/**
		 * \brief Applies the given transformations to the current transform
		 * \param other The transform to apply to the current transform
		 * \return A reference to the current transform
		 */
		Transform& operator*=(const Transform& other);

		/**
		 * \brief Applies the given transformations to the current transform
		 * \param other The transform to apply to the current transform
		 * \return The transformed transform
		 */
		Transform operator*(const Transform& other) const;

		/**
		 * \brief Checks whether the transform has a parent or not
		 * \return True if the transform has a parent, false otherwise
		 */
		bool hasParent() const;

		/**
		 * \brief Gets the transform's parent
		 * \return A pointer to the parent if it exists, nullptr otherwise
		 */
		Transform* getParent() const;

		/**
		 * \brief Sets the transform's parent
		 * \param parent The transform's new parent
		 */
		void setParent(Transform& parent);

		/**
		 * \brief Removes the transform's current parent
		 * \return True if the parent was removed, false otherwise
		 */
		bool removeParent();

		/**
		 * \brief Computes the transform's forward vector
		 * \return The transform's forward vector
		 */
		Vector3 forward() const;

		/**
		 * \brief Computes the transform's right vector
		 * \return The transform's right vector
		 */
		Vector3 right() const;

		/**
		 * \brief Computes the transform's up vector
		 * \return The transform's up vector
		 */
		Vector3 up() const;

		/**
		 * \brief Computes the transform's back vector
		 * \return The transform's back vector
		 */
		Vector3 back() const;

		/**
		 * \brief Computes the transform's left vector
		 * \return The transform's left vector
		 */
		Vector3 left() const;

		/**
		 * \brief Computes the transform's down vector
		 * \return The transform's down vector
		 */
		Vector3 down() const;

		/**
		 * \brief Gets the transform's current position
		 * \return The transform's position
		 */
		Vector3 getPosition() const;

		/**
		 * \brief Gets the transform's current rotation
		 * \return The transform's rotation
		 */
		Vector3 getRotation() const;

		/**
		 * \brief Gets the transform's current scale
		 * \return The transform's scale
		 */
		Vector3 getScale() const;

		/**
		 * \brief Gets the transform's current local transformation matrix
		 * \return The transform's local transformation matrix
		 */
		Matrix4x4 getMatrix() const;

		/**
		 * \brief Sets the transform's current local position
		 * \param position The transform's new local position
		 * \return A reference to the current transform
		 */
		Transform& setPosition(const Vector3& position);

		/**
		 * \brief Sets the transform's current local rotation
		 * \param rotation The transform's new local rotation
		 * \return A reference to the current transform
		 */
		Transform& setRotation(const Vector3& rotation);

		/**
		 * \brief Sets the transform's current local rotation
		 * \param scale The transform's new local scale
		 * \return A reference to the current transform
		 */
		Transform& setScale(const Vector3& scale);

		/**
		 * \brief Adds the given vector to the transform's current local position
		 * \param translation The translation vector to apply
		 * \return A reference to the current transform
		 */
		Transform& translate(const Vector3& translation);

		/**
		 * \brief Adds the given vector to the transform's current local rotation
		 * \param rotation The rotation vector to apply
		 * \return A reference to the current transform
		 */
		Transform& rotate(const Vector3& rotation);

		/**
		 * \brief Multiplies the transform's current local scale by the given vector
		 * \param scale The scaling vector to apply
		 * \return A reference to the current transform
		 */
		Transform& scale(const Vector3& scale);

		/**
		 * \brief Computes the transform's forward vector
		 * \return The transform's forward vector
		 */
		Vector3 worldForward() const;

		/**
		 * \brief Computes the transform's right vector
		 * \return The transform's right vector
		 */
		Vector3 worldRight() const;

		/**
		 * \brief Computes the transform's up vector
		 * \return The transform's up vector
		 */
		Vector3 worldUp() const;

		/**
		 * \brief Computes the transform's back vector
		 * \return The transform's back vector
		 */
		Vector3 worldBack() const;

		/**
		 * \brief Computes the transform's left vector
		 * \return The transform's left vector
		 */
		Vector3 worldLeft() const;

		/**
		 * \brief Computes the transform's down vector
		 * \return The transform's down vector
		 */
		Vector3 worldDown() const;

		/**
		 * \brief Gets the transform's current global position
		 * \return The transform's global position
		 */
		Vector3 getWorldPosition() const;

		/**
		 * \brief Gets the transform's current global rotation
		 * \return The transform's global rotation
		 */
		Vector3 getWorldRotation() const;

		/**
		 * \brief Gets the transform's current global scale
		 * \return The transform's global scale
		 */
		Vector3 getWorldScale() const;

		/**
		 * \brief Gets the transform's current global transformation matrix
		 * \return The transform's global transformation matrix
		 */
		Matrix4x4 getWorldMatrix() const;

		/**
		 * \brief Sets the transform's current global position
		 * \param position The transform's new global position
		 * \return A reference to the current transform
		 */
		Transform& setWorldPosition(const Vector3& position);

		/**
		 * \brief Sets the transform's current global rotation
		 * \param rotation The transform's new global rotation
		 * \return A reference to the current transform
		 */
		Transform& setWorldRotation(const Vector3& rotation);

		/**
		 * \brief Sets the transform's current global rotation
		 * \param scale The transform's new global scale
		 * \return A reference to the current transform
		 */
		Transform& setWorldScale(const Vector3& scale);

		/**
		 * \brief Adds the given vector to the transform's current global position
		 * \param translation The translation vector to apply
		 * \return A reference to the current transform
		 */
		Transform& worldTranslate(const Vector3& translation);

		/**
		 * \brief Adds the given vector to the transform's current global rotation
		 * \param rotation The rotation vector to apply
		 * \return A reference to the current transform
		 */
		Transform& worldRotate(const Vector3& rotation);

		/**
		 * \brief Multiplies the transform's current global scale by the given vector
		 * \param scale The scaling vector to apply
		 * \return A reference to the current transform
		 */
		Transform& worldScale(const Vector3& scale);

	protected:
		/**
		 * \brief Updates the transform's matrix
		 */
		virtual void onChange();

		/**
		* \brief Handles parent notifications
		* \param notificationType The notification type
		*/
		virtual void notificationHandler(TransformNotifier::ENotificationType notificationType);

	private:
		Vector3		m_position;
		Vector3		m_rotation;
		Vector3		m_scale;

		Vector3		m_worldPosition;
		Vector3		m_worldRotation;
		Vector3		m_worldScale;

		Matrix4		m_matrix;
		Matrix4		m_worldMatrix;

		Transform*	m_parent;

		TransformNotifier m_notifier;
		TransformNotifier::ListenerId m_notificationHandlerId = 0;

		/**
		 * \brief Generates a transformation matrix from the given position, rotation and scale
		 * \param position The transform's position
		 * \param rotation The transform's euler angles in degrees
		 * \param scale The transform's scale
		 * \return The generated transformation matrix
		 */
		static Matrix4 generateMatrix(const Vector3& position, const Vector3& rotation, const Vector3& scale);

		/**
		 * \brief Extracts the position, rotation and scale from the given transformation matrix
		 * \param matrix The transformation matrix to decompose
		 * \param position The vector in which the position should be extracted
		 * \param rotation The vector in which the rotation's euler angles in degrees should be extracted
		 * \param scale The vector in which the scale should be extracted
		 */
		static void decomposeMatrix(const Matrix4& matrix, Vector3& position, Vector3& rotation, Vector3& scale);

		/**
		 * \brief Updates the local transformation data based on the current global transform
		 */
		void updateLocalMatrix();

		/**
		 * \brief Updates the global transformation data based on the current local transform
		 */
		void updateWorldMatrix();
	};
}
