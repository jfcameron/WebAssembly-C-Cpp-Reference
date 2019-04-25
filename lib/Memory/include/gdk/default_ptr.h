// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MEMORY_DEFAULT_PTR_H
#define GDK_MEMORY_DEFAULT_PTR_H

#include <memory>

//TODO: replace T with target_type

namespace gdk
{    
    /// \brief a weak pointer that returns a default pointer to T if the target pointer has become null.
    /// \todo rename lock to get. If the internal lock fails, you still get a defualt value.. this is the whole point. should be ptr.get()
    template<typename T>
    class default_ptr final
    {
        std::weak_ptr<T> m_Target;    //! Non-owning pointer to T instance
        std::shared_ptr<T> m_Default; //! Shared pointer to another instance of T, guaranteed to be
                                      ///valid for lifetime of the default_ptr
            
    public:
        //! Attempt to promote m_Target to a shared_ptr. Returns m_Default if m_Target is null
        std::shared_ptr<T> lock() const 
        {
            if (auto pTarget = m_Target.lock()) return pTarget;
                
            return m_Default;
        }
            
        bool operator==(const default_ptr &a) const
        {
            return 
            m_Default == a.m_Default && 
            m_Target.lock() == a.m_Target.lock();
        }

        default_ptr &operator= (const default_ptr &a) = default;
        default_ptr &operator= (default_ptr &&a) = default;

        /// \param aTarget the pointer to attempt to return when lock is called.
        /// \param aDefault the pointer returned by lock if the target is null
        default_ptr(const std::shared_ptr<T> &aDefault, const std::shared_ptr<T> &aTarget = {}) 
        : m_Target(aTarget)
            , m_Default(aDefault)
        {}
            
        default_ptr() = delete;
        default_ptr(const default_ptr &) = default;
        default_ptr(default_ptr &&) = default;
        ~default_ptr() = default;
    };
}

#endif
