// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MEMORY_LAZY_PTR_H
#define GDK_MEMORY_LAZY_PTR_H

#include <functional>
#include <iostream>
#include <memory>
#include <mutex>

//TODO: change language contained from "internal ptr" and type "T" to resource and resource_type

namespace gdk
{
    /// \brief pointer that delays initialization until the first time it is dereferenced or casted
    /// that is to say, until the first time the resource is used.
    template<typename T> class lazy_ptr final
    {
    public:
        using initializer_type = std::function<T *const()>;

    private:
        const initializer_type m_Initializer; //!< function wrapper called at first dereference to init T instance pointee

        mutable std::once_flag m_IsInitialized; //!< indicates whether or not pointee is initialized 

        mutable std::shared_ptr<T> m_SharedPtr = {}; //!< internal pointer to the T instance

        //! Initializes the pointer
        void initialize() const
        {
            std::call_once(m_IsInitialized, [&]{ m_SharedPtr.reset(m_Initializer()); });
        }

    public:
        //! Check whether or not the lazy_ptr has initialized its internal ptr
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

        //! dereference via standard dereference operator
        T &operator*() const
        {
            return *get();
        }

        //! deref and access member via arrow operator
        T *operator->() const
        {
            return get();
        }
            
        bool operator==(const lazy_ptr &a) const
        {
            return m_Initializer == a.m_Initializer;
        }

        //! initialize pointee and return copy of internal shared_ptr via explicit cast semantic
        explicit operator std::shared_ptr<T>() const
        {
            initialize();
            
            return m_SharedPtr;
        }

        lazy_ptr &operator= (const lazy_ptr &a) = default;
        lazy_ptr &operator= (lazy_ptr &&a) = default;

        //! \param aInitializer function used to lazily initialize the T instance 
        lazy_ptr(const initializer_type aInitializer) 
        : m_Initializer(aInitializer) 
        {}            
        
        lazy_ptr() = delete;
        lazy_ptr(const lazy_ptr &) = default;
        lazy_ptr(lazy_ptr &&) = default;
        ~lazy_ptr() = default;
    };
}

#endif
