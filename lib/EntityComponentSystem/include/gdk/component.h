// © 2017 Joseph Cameron - All Rights Reserved

#ifndef GDK_ECS_COMPONENT_H
#define GDK_ECS_COMPONENT_H

#include <iosfwd>
#include <memory>

namespace gdk
{       
    class Object;
    class Transform;
    class Scene;
        
    /// \brief Encapsulates behaviour and data used to manipulate Objects
    class Component : public std::enable_shared_from_this<Component>
    {
        friend std::ostream &operator<< (std::ostream &, const ECS::Component &);
        friend GDK::ECS::Object;
      
        std::weak_ptr<Object> m_Object = {};
        bool m_DidInit = false;
            
    protected:
        //! called once per component instance, as early as possible
        virtual void initialize() {}
            
        //! called every update frame
        virtual void update() {}
            
        //! called every fixedupdate frame
        virtual void fixedUpdate() {}
            
        //! Another component was added to my object
        virtual void onOtherComponentAddedToMyObject(const std::weak_ptr<Component> &) {}
            
        //! Another component was removed from my object
        virtual void onOtherComponentRemovedFromMyObject(const std::weak_ptr<Component> &) {}
            
        //! This component instance was added to a object
        virtual void onAddedToObject(const std::weak_ptr<Object> &) {}
            
        //virtual void onRemovedFromObject(const std::weak_ptr<Object>&) {}
            
    public:
        std::weak_ptr<Object> getObject() const;
            
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
