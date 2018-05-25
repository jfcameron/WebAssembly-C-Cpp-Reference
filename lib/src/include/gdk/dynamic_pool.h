// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-23.
#ifndef GDK_MEMORY_DYNAMIC_POOL_H
#define GDK_MEMORY_DYNAMIC_POOL_H

//std inc
#include <functional>
#include <memory>
#include <vector>

namespace gdk
{
    namespace Memory
    {
        /*!
         Object pool of variable length. When get is called, an object with
         a reference count of 1 (unused outside the pool) is returned. If
         no unused objects exist, a new instance of T is added to the pool and returned
         */
        template<typename T>
        class dynamic_pool final
        {
        public: // Types
            using initializer_type = std::function<T()>;
            
            using pool_type =  std::vector<std::shared_ptr<T>>;
            using value_type = typename pool_type::value_type;
            using size_type =  typename pool_type::size_type;

        private: // Data members
            const size_type m_InitialPoolSize;
            const initializer_type m_NewObjectInitializer;

            mutable pool_type m_Pool;

        public: // Public methods
            /// Get an object from the pool
            value_type get() const
            {
                for (const auto &item : m_Pool)
                    if (item.use_count() == 1)
                        return item;
              
                m_Pool.push_back(std::make_shared<T>(m_NewObjectInitializer()));
                
                return m_Pool.back();
            }
          
            /// Try to reduce poolsize back to its initial size by removing any unused items while current size is > init size
            void trim() const
            {
                for (size_type i = 0; i < m_Pool.size(); ++i)
                    if (m_Pool.size() <= m_InitialPoolSize)
                        return;
                    else if (m_Pool[i].use_count() == 1)
                        m_Pool.erase(m_Pool.begin() + i);
            }

            size_type size() const
            {
                return m_Pool.size();
            }

            // Mutating operators
            dynamic_pool &operator=(const dynamic_pool &) = delete;
            dynamic_pool &operator=(dynamic_pool &&) = delete;
      
            // Constructors, destructors
            dynamic_pool(const size_t &aInitialPoolSize, const initializer_type &aNewObjectInitializer /*= [](){return T();}*/)
            : m_InitialPoolSize(aInitialPoolSize)
            , m_NewObjectInitializer(aNewObjectInitializer)
            , m_Pool(aInitialPoolSize, std::make_shared<T>(m_NewObjectInitializer()))
            {}
            
            dynamic_pool(const dynamic_pool &) = delete;
            dynamic_pool(dynamic_pool &&) = default;
            ~dynamic_pool() = default;
        };
    }
}

#endif /* GDK_MEMORY_DYNAMIC_POOL_H  */
