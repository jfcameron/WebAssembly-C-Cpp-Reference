// © 2017 Joseph Cameron - All Rights Reserved

#ifndef GDK_ECS_COMPONENT_H
#define GDK_ECS_COMPONENT_H

#include <iosfwd>
#include <memory>

namespace gdk
{       
    class Entity;
    class Transform;
    class Scene;
        
    /// \brief Encapsulates behaviour and data used to manipulate Entitys
    class Component : public std::enable_shared_from_this<Component>
    {
        //friend std::ostream &operator<< (std::ostream &, const Component &);
        friend gdk::Entity; // is this REALLY necessary? The answwer is no. a potential source of headaches and makes both classes harder to read.
      
        std::weak_ptr<Entity> m_Entity = {};

        bool m_DidInit = false;
            
    protected:
        /// \brief JSON representation of the Component derivative. Required for serializing to JSON, for serializing to disk and logging e.g: state of a Scene
        virtual std::string toJSON();

        /// \brief called once per component instance, as early as possible
        virtual void initialize() {}
            
        /// \brief called every update frame
        virtual void update() {}
            
        /// \brief called every fixedupdate frame
        virtual void fixedUpdate() {}
            
        /// \brief Another component was added to my Entity
        virtual void onOtherComponentAddedToMyEntity(const std::weak_ptr<Component> &) {}
            
        /// \brief Another component was removed from my Entity
        virtual void onOtherComponentRemovedFromMyEntity(const std::weak_ptr<Component> &) {}
            
        /// \brief This component instance was added to a Entity
        virtual void onAddedToEntity(const std::weak_ptr<Entity> &) {}

        //virtual void onRemovedFromEntity(const std::weak_ptr<Entity>&) {}
            
    public:
        std::weak_ptr<Entity> getEntity() const;
            
        std::ostream& operator<<(std::ostream &s);

        Component &operator=(const Component &) = delete;
        Component &operator=(Component &&) = delete;
      
//    protected:
        Component() = default;
    private:
        Component(const Component &) = delete;
        Component(Component &&) = delete;
    public:
        virtual ~Component() = default;
    };

    std::ostream &operator<< (std::ostream &, const Component &);
}

#endif
