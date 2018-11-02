// © 2018 Joseph Cameron - All Rights Reserved
/// \brief Internal header, allowing communication among compilation units. do not expose externally.

#ifndef GDK_RESOURCES_PRIVATE_H
#define GDK_RESOURCES_PRIVATE_H

#include <gdk/locking_queue.h>

namespace gdk::resources::PRIVATE
{
    using task_type = std::function<void()>;

    extern locking_queue<task_type> queued_fetches;

    extern std::queue<task_type> queued_responses;
}

#endif
