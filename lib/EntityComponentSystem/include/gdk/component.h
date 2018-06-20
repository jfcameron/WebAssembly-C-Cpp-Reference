// © 2017 Joseph Cameron - All Rights Reserved

#ifndef GDK_ECS_COMPONENT_H
#define GDK_ECS_COMPONENT_H

#include <iosfwd>
#include <memory>

namespace gdk
{       
    class GameObject;
    class Transform;
    class Scene;
        
    //! Encapsulates behaviour and data used to manipulate GameObjects
    class Component : public std::enable_shared_from_this<Component>
    {
        friend std::ostream &operator<< (std::ostream &, const ECS::Component &);
        friend GDK::ECS::GameObject;
      
        std::weak_ptr<GameObject> m_GameObject = {};
        bool m_DidInit = false;
            
    protected:
        //! called once per component instance, as early as possible
        virtual void initialize() {}
            
        //! called every update frame
        virtual void update() {}
            
        //! called every fixedupdate frame
        virtual void fixedUpdate() {}
            
        //! Another component was added to my gameobject
        virtual void onOtherComponentAddedToMyGameObject(const std::weak_ptr<Component> &) {}
            
        //! Another component was removed from my gameobject
        virtual void onOtherComponentRemovedFromMyGameObject(const std::weak_ptr<Component> &) {}
            
        //! This component instance was added to a gameobject
        virtual void onAddedToGameObject(const std::weak_ptr<GameObject> &) {}
            
        //virtual void onRemovedFromGameObject(const std::weak_ptr<GameObject>&) {}
            
    public:
        std::weak_ptr<GameObject> getGameObject() const;
            
        Component &operator=(const Component &) = delete;
        Component &operator=(Component &&) = delete;
      
    protected:
        Component() = default;
    private:
        Component(const Component &) = delete;
        Component(Component &&) = delete;
    public:
        virtual ~Component() = default;
    };

    std::ostream &operator<< (std::ostream &, const ECS::Component &);
}

#endif
