// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_GFX_RESOURCEMANAGER_H
#define GDK_GFX_RESOURCEMANAGER_H

#include <Memory/default_ptr.h>
#include <Debug/Exception.h>

#include <string>
#include <memory>
#include <map>

//TODO: "ResourceManager" can surely be abstracted more. Could it be a specialization of a map with defualt values for example.
//TODO: Why is the key type forced to be a string? This doesnt make much sense.

namespace gdk
{
    /// \brief responsible for solely managing the lifetime of some object T.
    ///
    /// \detailed By serving resources via default_ptrs, the manager can safely destroy any T instance
    /// without risking memory reading issues.
    template<typename T> class resource_manager
    {
    protected:
        std::map<std::string,std::shared_ptr<T>> m_Map;

        std::shared_ptr<T> m_Default;
            
    public:
        //! Get a default_ptr to a managed object
        default_ptr<T> get(const std::string &aName)
        {
            auto it = m_Map.find(aName);
            
            if (it != m_Map.end()) return default_ptr<T>(m_Default,it->second);
            
            return default_ptr<T>(m_Default);
        }
            
        //! Add a new object to be managed
        void add(T &&t)
        {
            m_Map.insert({t.getName(), std::make_shared<T>(std::move(t))});
        }
           
        //! Destroy the managed object with the given name
        void remove(const std::string &aName)
        {
            m_Map.erase(aName);
        }

        //! Destroy all managed objects
        void clear()
        {
            m_Map.clear();
        }

        //! Removes resources with a reference count of 1
        //  \Warn UNIMPLEMENTED
        void trim();
                      
        resource_manager &operator=(const resource_manager &) = delete;
        resource_manager &operator=(resource_manager &&) = delete;

    resource_manager(T &&aDefault)
        : m_Map()
            , m_Default(std::make_shared<T>(std::move(aDefault)))
        {}
            
    resource_manager(const std::shared_ptr<T> &aDefault)
        : m_Map()
            , m_Default(aDefault)
        {}
            
        resource_manager() = delete;
        resource_manager(const resource_manager &) = delete;
        resource_manager(resource_manager &&) = default;
        virtual ~resource_manager() = default;
    };
}

#endif
