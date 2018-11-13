// © 2017 Joseph Cameron - All Rights Reserved

#ifndef GDK_ECS_COMPONENT_ANNOTATIONS_H
#define GDK_ECS_COMPONENT_ANNOTATIONS_H

#include <iosfwd>
#include <memory>

namespace gdk
{
    class Object;
    class Component;
    class SceneGraph;
    class Scene;

    /// \brief Object::Add will fail if a T already exists in its component list
    /// \warning Unimplemented
    class UniqueComponent{};
        
    //! Object will silently add a component of type T if one does not already exist in its component list
    template<typename T> class RequireComponent
    {
        friend Object;
        static_assert(std::is_base_of<Component, T>::value == true, "T must be a kind of Component");
            
        std::shared_ptr<T> getType(){return std::shared_ptr<T>(new T());}
    };
        
    //! The scene that holds the object at Object::Add time will add a scenegraph of type T if one does
    /// not already exist
    template<typename T> class RequireSceneGraph
    {
        friend Scene;
        static_assert(std::is_base_of<SceneGraph, T>::value == true, "T must be a kind of SceneGraph");
            
        std::shared_ptr<T> getType(){return std::shared_ptr<T>(new T());}            
    };        
}

#endif
