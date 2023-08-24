#include "TransformNotifier.h"

#include <ranges>

namespace LibMath
{
    TransformNotifier::ListenerId TransformNotifier::subscribe(const Action& action)
    {
        m_actions[m_currentId] = action;
        return m_currentId++;
    }

    void TransformNotifier::broadcast(const ENotificationType notificationType)
    {
        if (!m_actions.empty())
            for (const auto& handler : m_actions | std::views::values)
                handler(notificationType);
    }

    bool TransformNotifier::unsubscribe(const ListenerId& listener)
    {
        return m_actions.erase(listener) != 0;
    }
}
