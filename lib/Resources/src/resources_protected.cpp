// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/locking_queue.h>
#include <gdk/resources_private.h>
#include <gdk/resources_protected.h>

#include <functional>
#include <string>

namespace gdk::resources::PROTECTED
{
    void WorkerThreadUpdate()
    {
        gdk::resources::PRIVATE::task_type fetchTask;
        
        if (gdk::resources::PRIVATE::queued_fetches.pop(fetchTask)) fetchTask();
    }

    void MainThreadUpdate()
    {
        if (gdk::resources::PRIVATE::queued_responses.size() > 0)
        {
            gdk::resources::PRIVATE::queued_responses.front()();

            gdk::resources::PRIVATE::queued_responses.pop();
        }
    }

    namespace logging_interface
    {
        logging_function_signature log = [](std::string aTag, std::string aMessage){};
    }
}
