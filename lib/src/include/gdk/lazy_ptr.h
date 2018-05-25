// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2018-03-06.
#ifndef GDK_MEMORY_LAZY_PTR_H
#define GDK_MEMORY_LAZY_PTR_H

//std inc
#include <memory>
#include <functional>

namespace gdk
{
    /*! 
      Smart pointer that delays initialization until the first time it is dereferenced
    */
    template<typename T> class lazy_ptr final
    {
    public:
        using InitializerSignature = std::function<T *const ()>;

    private:
        //Data members
        const InitializerSignature m_Initializer;

        mutable std::shared_ptr<T> m_SharedPtr = {};

        mutable bool m_Initialized = false;

        void initialize() const
        {
            m_SharedPtr.reset(m_Initializer());
                
            m_Initialized = true;
        }

    public:
        // Public methods
        /// Check if the lazy_ptr has initialized its internal ptr
        bool initialized() const
        {
            return m_Initialized;
        }

        T *get() const 
        {
            if (!m_Initialized) initialize();
                
            return m_SharedPtr.get();
        }

        // Non-mutating operators
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

        // Mutating operators
        lazy_ptr &operator= (const lazy_ptr &a) = default;
        lazy_ptr &operator= (lazy_ptr &&a) = default;
            
        // Instancing rules
    lazy_ptr(const InitializerSignature aInitializer) : m_Initializer(aInitializer) {}
            
        lazy_ptr() = delete;
        lazy_ptr(const lazy_ptr &) = default;
        lazy_ptr(lazy_ptr &&) = default;
        ~lazy_ptr() = default;
    };
}

#endif
