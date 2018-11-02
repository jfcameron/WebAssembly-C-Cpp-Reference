// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/resources_private.h>

namespace gdk::resources::PRIVATE
{
    locking_queue<task_type> queued_fetches;

    std::queue<task_type> queued_responses;
}
