#ifndef __LIBMATH__TRANSFORM_NOTIFIER_H__
#define __LIBMATH__TRANSFORM_NOTIFIER_H__

#include <functional>
#include <cstdint>

namespace LibMath
{
    class TransformNotifier
    {
    public:
        enum class ENotificationType
        {
            TRANSFORM_CHANGED,
            TRANSFORM_DESTROYED
        };

        using ListenerId = uint64_t;
        using Action = std::function<void(ENotificationType)>;
        using ActionMap = std::unordered_map<ListenerId, Action>;

        /**
         * \brief Subscribes an action to the notifier and returns its ListenerId
         * \param action The action to perform when a notification is broadcast
         * \return The listener id of the subscribed action
         */
        inline ListenerId subscribe(const Action& action);

        /**
        * \brief Broadcasts the given notification to all subscribers
        * \param notificationType The type of notification to broadcast
        */
        inline void broadcast(ENotificationType notificationType);

        /**
         * \brief Unsubscribes the listener with the given id from this notifier
         * \param listener The id of the listener to unsubscribe
         */
        inline bool unsubscribe(const ListenerId& listener);

    private:
        ListenerId m_currentId = 1;
        ActionMap  m_actions;
    };
}

#include "TransformNotifier.inl"

#endif // !__LIBMATH__TRANSFORM_NOTIFIER_H__
