// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 2017-07-13.
#ifndef GDK_MEMORY_DEFAULT_PTR_H
#define GDK_MEMORY_DEFAULT_PTR_H

//std inc
#include <memory>

namespace gdk
{
        /*! 
         a non-owning smart pointer that returns a default instance of T if the internal weak_ptr returns nullptr.
         The design of default_ptr assumes the pointee of m_Default is guaranteed to be valid during the lifetime 
         of the default_ptr instance; It is up to the user of this class to guarantee this is the case.
         */
        template<typename T>
        class default_ptr final
        {
        private: //Data members
            std::weak_ptr<T> m_WeakPtr;
            std::shared_ptr<T> m_Default;
            
        public:
            // Public methods
            std::shared_ptr<T> lock() const 
            {
                if (auto ptr = m_WeakPtr.lock()) return ptr;
                
                return m_Default;
            }
            
            // Non-mutating operators
            bool operator== (const default_ptr &a) const
            {
                return 
                    m_Default ==        a.m_Default && 
                    m_WeakPtr.lock() == a.m_WeakPtr.lock();
            }

            // Mutating operators
            default_ptr &operator= (const default_ptr &a) = default;
            default_ptr &operator= (default_ptr &&a) = default;
            
            // Instancing rules
            default_ptr(const std::shared_ptr<T> &aDefault, const std::shared_ptr<T> &aWeakPtr = {}) 
            : m_WeakPtr(aWeakPtr)
            , m_Default(aDefault)
            {}
            
            default_ptr() = delete;
            default_ptr(const default_ptr &) = default;
            default_ptr(default_ptr &&) = default;
            ~default_ptr() = default;
        };
}

#endif
