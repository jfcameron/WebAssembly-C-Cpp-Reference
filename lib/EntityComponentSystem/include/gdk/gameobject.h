// © 2017 Joseph Cameron - All Rights Reserved

#ifndef GDK_ECS_GAMEOBJECT_H
#define GDK_ECS_GAMEOBJECT_H

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
    /// \brief GameObject has a list of components and belongs to a scene
    class GameObject final : public std::enable_shared_from_this<GameObject>
    {
        friend std::ostream &operator<< (std::ostream &, const ECS::GameObject &);
        friend GDK::ECS::Scene;
            
        std::string m_Name = "Unnamed";
            
        std::weak_ptr<Scene> m_MyScene = {};
        std::vector<std::shared_ptr<Component>> m_Components = {};
            
        Math::Vector3    m_Position = Math::Vector3::Zero;
        Math::Vector3    m_Scale    = {1.f,1.f,1.f};
        Math::Quaternion m_Rotation = Math::Quaternion::Identity;
            
        void update() const;
        void fixedUpdate() const;
            
    public:
        std::string getName() const;
        Math::Vector3 getPosition() const;
        Math::Vector3 getScale() const;
        Math::Quaternion getRotation() const;
        std::weak_ptr<Scene> getScene() const;
        std::weak_ptr<Component> getComponent(const size_t aIndex) const;
        size_t getComponentCount() const;
            
        void setName(const std::string &aName);
        void setPosition(const Math::Vector3 &);
        void setPosition(const float aX, const float aY, const float aZ);
        void setScale(const Math::Vector3 &);
        void setRotation(const Math::Quaternion &);
            
        template<class T> std::weak_ptr<T> addComponent()
        {
            static_assert(std::is_base_of<Component, T>::value == true, "T must be a kind of component");
                
            if (auto pScene = m_MyScene.lock())
            {
                std::weak_ptr<GameObject> wpThis = std::weak_ptr<GameObject>(shared_from_this());
                    
                std::shared_ptr<T> spNewT(new T());
                std::weak_ptr<T>   wpNewT(spNewT);
                    
                std::shared_ptr<Component> spNewComponent = std::static_pointer_cast<Component>(spNewT);
                    
                spNewComponent->m_GameObject = wpThis;
                spNewComponent->onAddedToGameObject(wpThis);
                    
                m_Components.push_back(std::static_pointer_cast<Component>(spNewT));
                    
                pScene->OnComponentAddedToAGameObject(wpNewT);
                    
                for (auto component : m_Components) component->onOtherComponentAddedToMyGameObject(wpNewT);
                    
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
                            
                        pScene->OnComponentRemovedFromAGameObject(removedComponent);
                            
                        for(size_t j; j < m_Components.size(); j++)
                            if (j != i)
                                m_Components[j]->onOtherComponentRemovedFromMyGameObject(removedComponent);
                            
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
            
        GameObject &operator=(const GameObject &) = delete;
        GameObject &operator=(GameObject &&) = delete;
            
    private:
        GameObject(const std::weak_ptr<Scene> &aScene);
        GameObject() = delete;
        GameObject(const GameObject &) = delete;
        GameObject(GameObject &&) = delete;
    public:
        ~GameObject() = default;
    };

    std::ostream &operator<< (std::ostream &, const ECS::GameObject &);
}

#endif
