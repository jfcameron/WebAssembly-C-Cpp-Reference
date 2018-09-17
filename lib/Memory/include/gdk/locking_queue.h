// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MEMORY_LOCKING_QUEUE_H
#define GDK_MEMORY_LOCKING_QUEUE_H

#include <queue>
#include <mutex>

namespace gdk
{
    /// \brief Thread friendly [locking] queue.
    ///
    /// \detailed Allows concurrent processing of items retrieved from the queue.
    /// queue access however is locking: threads will wait when pushing and or popping.
    ///
    /// \todo write/find a lockless solution and deprecate this one.
    template <typename T>
    class locking_queue
    {
        std::mutex m_mutex;
        
        std::queue<T> m_queue;
        
    public:
        //! adds a new task to the back of the queue.
        void push(T &&task)
        {
            //std::lock_guard<std::mutex> lock(m_mutex);
            
            m_queue.push(std::forward<T>(task));
        }
        
        //! if size > 0, assigns front to out, pops the front and returns true. otherwise returns false.
        bool pop(T &out)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            
            if (!m_queue.empty())
            {
                out = std::move(m_queue.front());
                
                m_queue.pop();
                
                return true;
            }
            
            return false;
        }
    };
}

#endif
