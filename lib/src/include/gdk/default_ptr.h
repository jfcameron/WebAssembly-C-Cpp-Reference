// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 2017-07-13.
#ifndef GDK_MEMORY_DEFAULT_PTR_H
#define GDK_MEMORY_DEFAULT_PTR_H

//std inc
#include <memory>

namespace gdk
{
    //template<typename T> class lazy_ptr;
    
    /*! 
      a pointer that returns a default instance of T if the target instance has become null.
    */
    template<typename T> class default_ptr final
    {
        std::weak_ptr<T> m_Target;
        std::shared_ptr<T> m_Default;
            
    public:
        //! Attempt to promote target to a shared ptr, returns default if target is null
        std::shared_ptr<T> lock() const 
        {
            if (auto pTarget = m_Target.lock()) return pTarget;
                
            return m_Default;
        }
            
        bool operator== (const default_ptr &a) const
        {
            return 
            m_Default == a.m_Default && 
            m_Target.lock() == a.m_Target.lock();
        }

        default_ptr &operator= (const default_ptr &a) = default;
        default_ptr &operator= (default_ptr &&a) = default;
            
        default_ptr(const std::shared_ptr<T> &aDefault, const std::shared_ptr<T> &aTarget = {}) 
        : m_Target(aTarget)
            , m_Default(aDefault)
        {}

        //This should probably replaced with an [explicit] cast from Lazy to Shared
        //default_ptr(const lazy_ptr<T> &a, const std::shared_ptr<T> &aTarget = {})
        //    : default_ptr(static_cast<std::shared_ptr<T>>(a), aTarget)
        //{}
            
        default_ptr() = delete;
        default_ptr(const default_ptr &) = default;
        default_ptr(default_ptr &&) = default;
        ~default_ptr() = default;
    };
}

#endif
