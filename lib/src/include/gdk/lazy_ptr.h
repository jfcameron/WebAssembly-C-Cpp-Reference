// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MEMORY_LAZY_PTR_H
#define GDK_MEMORY_LAZY_PTR_H

#include <functional>
#include <memory>
#include <mutex>
#include <iostream>

namespace gdk
{
    /*! 
      Pointer that delays initialization until the first time it is dereferenced
    */
    template<typename T> class lazy_ptr final
    {
    public:
        using InitializerSignature = std::function<T *const ()>;

    private:
        const InitializerSignature m_Initializer;

        mutable std::once_flag m_IsInitialized;

        mutable std::shared_ptr<T> m_SharedPtr = {};

        //! Initializes the pointer
        void initialize() const
        {
            std::call_once(m_IsInitialized, [&]{ m_SharedPtr.reset(m_Initializer()); });
        }

    public:
        //! Check if the lazy_ptr has initialized its internal ptr
        bool initialized() const
        {
            return m_SharedPtr.get() != nullptr;
        }

        //! dereference the pointer, initializing if this was the first time
        T *get() const 
        {
            initialize();
            
            return m_SharedPtr.get();
        }

        T &operator*() const
        {
            return *get();
        }

        T *operator->() const
        {
            return get();
        }
            
        bool operator==(const lazy_ptr &a) const
        {
            return m_Initializer == a.m_Initializer;
        }

        explicit operator std::shared_ptr<T>() const
        {
            initialize();
            
            return m_SharedPtr;
        }

        lazy_ptr &operator= (const lazy_ptr &a) = default;
        lazy_ptr &operator= (lazy_ptr &&a) = default;
        
        lazy_ptr(const InitializerSignature aInitializer) : m_Initializer(aInitializer) {}            
        lazy_ptr() = delete;
        lazy_ptr(const lazy_ptr &) = default;
        lazy_ptr(lazy_ptr &&) = default;
        ~lazy_ptr() = default;
    };
}

#endif
