// © 2017 Joseph Cameron - All Rights Reserved

#ifndef GDK_ECS_SCENEGRAPH_H
#define GDK_ECS_SCENEGRAPH_H

#include <iosfwd>
#include <memory>

namespace gdk
{
    struct IntVector2;
    
    class Scene;
    class Component;

    /// \brief Defines a scene capability. ECS abstraction of a Renderer or Physics Engine etc.
    class SceneGraph
    {
        friend std::ostream& operator<< (std::ostream &, const SceneGraph &);
        friend Scene;
      
        Scene *m_MyScene = nullptr; //?
            
    protected:
        Scene *getMyScene() const {return m_MyScene;}
            
        virtual void draw(const IntVector2 &aFrameBufferSize) = 0;
        virtual void fixedUpdate() = 0;
        virtual void update()      = 0;
            
        virtual void OnComponentAddedToAEntity(const std::weak_ptr<Component> &) = 0;
        virtual void OnComponentRemovedFromAEntity(const std::weak_ptr<Component> &) = 0;
            
    public:
        SceneGraph &operator=(const SceneGraph &) = delete;
        SceneGraph &operator=(SceneGraph &&) = delete;
      
    protected:
        SceneGraph(Scene *);
    private:
        SceneGraph() = delete;
        SceneGraph(const SceneGraph &) = delete;
        SceneGraph(SceneGraph &&) = delete;
    public:
        virtual ~SceneGraph() = default;
      
    };

    std::ostream &operator<< (std::ostream &, const SceneGraph &);
}

#endif
