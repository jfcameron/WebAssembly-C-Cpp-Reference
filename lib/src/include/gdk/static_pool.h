// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-23.
#ifndef GDK_MEMORY_STATIC_POOL_H
#define GDK_MEMORY_STATIC_POOL_H

//std inc
#include <array>
#include <functional>
#include <memory>

namespace gdk
{
    namespace Memory
    {
        /*!
         Object pool of a fixed length. When get is called, an object with
         a reference count of 1 (unused outside the pool) is returned. If
         no unused objects exist, a nullptr is returned.
         */
        template<typename T, const size_t length>
        class static_pool final
        {
        public:
            using value_type =      std::shared_ptr<T>;
            using collection_type = std::array<value_type, length>;

        private:
            // Data members
            const collection_type m_Pool;
            
        public:
            // Public methods
            /// Try to get an object from the pool, will be null if all objects are in use
            value_type get() const 
            {
                for (const auto &item : m_Pool) if (item.use_count() == 1) return item;
                
                return {};
            }
            
            // Mutating operators
            static_pool &operator=(const static_pool &) = delete;
            static_pool &operator=(static_pool &&) = default;
      
            // Constructors, destructors
            static_pool(const std::function<T()> &aItemInitializer /*= [](){return T();}*/)
            : m_Pool([this, &aItemInitializer]()
            {
                collection_type pool;

                for(decltype(length) i = 0; i < length; ++i) pool[i] = std::make_shared<T>(aItemInitializer());

                return pool;
            }())
            {}  

            static_pool(const static_pool&) = delete;
            static_pool(static_pool&&) = default;
            ~static_pool() = default;
        };
    }
}

#endif
