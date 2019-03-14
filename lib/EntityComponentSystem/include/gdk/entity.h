// © 2017 Joseph Cameron - All Rights Reserved

#ifndef GDK_ECS_Entity_H
#define GDK_ECS_Entity_H

#include <gdk/component.h>
#include <gdk/scene.h>
#include <gdk/quaternion.h>
#include <gdk/vector3.h>

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

namespace gdk
{
    /// \brief Entity has a list of components and belongs to a scene
    class Entity final : public std::enable_shared_from_this<Entity>
    {
        friend std::ostream &operator<< (std::ostream &, const Entity &);
        friend Scene;
            
        std::string m_Name = "Unnamed";
            
        std::weak_ptr<Scene> m_MyScene = {};
        std::vector<std::shared_ptr<Component>> m_Components = {};
            
        Vector3 m_Position = Vector3::Zero;
        Vector3 m_Scale    = {1.f,1.f,1.f};
        Quaternion m_Rotation = Quaternion::Identity;
            
        void update() const;
        void fixedUpdate() const;
            
    public:
        std::string getName() const;
        Vector3 getPosition() const;
        Vector3 getScale() const;
        Quaternion getRotation() const;
        std::weak_ptr<Scene> getScene() const;
        std::weak_ptr<Component> getComponent(const size_t aIndex) const;
        size_t getComponentCount() const;
            
        void setName(const std::string &aName);
        void setPosition(const Vector3 &);
        void setPosition(const float aX, const float aY, const float aZ);
        void setScale(const Vector3 &);
        void setRotation(const Quaternion &);
        
        /*
        void addComponents() /// TODO: variadic template (?) to allow adding loads of components in 1 go
        */

        template<class T> std::weak_ptr<T> addComponent()
        {
            static_assert(std::is_base_of<Component, T>::value == true, "T must be a kind of component");
                
            if (auto pScene = m_MyScene.lock())
            {
                std::weak_ptr<Entity> wpThis = std::weak_ptr<Entity>(shared_from_this());
                    
                std::shared_ptr<T> spNewT(new T());
                std::weak_ptr<T>   wpNewT(spNewT);
                    
                std::shared_ptr<Component> spNewComponent = std::static_pointer_cast<Component>(spNewT);
                    
                spNewComponent->m_Entity = wpThis;
                spNewComponent->onAddedToEntity(wpThis);
                    
                m_Components.push_back(std::static_pointer_cast<Component>(spNewT));
                    
                pScene->OnComponentAddedToAEntity(wpNewT);
                    
                for (auto component : m_Components) component->onOtherComponentAddedToMyEntity(wpNewT);
                    
                return wpNewT;
            }
                    
            return {};
        }
            
        template<class T> void removeComponent()
        {
            static_assert(std::is_base_of<Component, T>::value == true, "T must be a kind of component");
                
            if (auto pScene = m_MyScene.lock())
                for (size_t i = 0; i < m_Components.size(); i++)
                    if (std::dynamic_pointer_cast<T>(m_Components[i]))
                    {
                        std::weak_ptr<Component> removedComponent(m_Components[i]);
                            
                        pScene->OnComponentRemovedFromAEntity(removedComponent);
                            
                        for(size_t j; j < m_Components.size(); j++)
                            if (j != i)
                                m_Components[j]->onOtherComponentRemovedFromMyEntity(removedComponent);
                            
                        m_Components.erase(m_Components.begin()+i);
                    }
        }
            
        template<class T> std::weak_ptr<T> getComponent() const
        {
            for (auto component : m_Components)
                if (std::dynamic_pointer_cast<T>(component))
                    return std::weak_ptr<T>(std::dynamic_pointer_cast<T>(component));
                
            return {};
        }
            
        template<class T> std::vector<std::weak_ptr<T>> getComponents() const
        {
            std::vector<std::weak_ptr<T>> components;
                
            for (auto it = m_Components.begin(), end = m_Components.end(); it != end; ++it)
                if (std::dynamic_pointer_cast<T>(*it))
                    components.push_back(std::weak_ptr<T>(std::dynamic_pointer_cast<T>(*it)));
                
            return components;
        }
            
        Entity &operator=(const Entity &) = delete;
        Entity &operator=(Entity &&) = delete;
            
    private:
        Entity(const std::weak_ptr<Scene> &aScene);
        Entity() = delete;
        Entity(const Entity &) = delete;
        Entity(Entity &&) = delete;
    public:
        ~Entity() = default;
    };

    std::ostream &operator<< (std::ostream &, const Entity &);
}

#endif
