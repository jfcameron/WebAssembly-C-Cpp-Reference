// © 2017 Joseph Cameron - All Rights Reserved

#ifndef GDK_ECS_SCENE_H
#define GDK_ECS_SCENE_H

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

namespace gdk
{
    struct IntVector2;
 
    class Entity;
    class SceneGraph;
    class Component; 
        
    /// \brief the spacial context in which a collection of entities exist. scene components modify the naturue of the context (does it have 3D audio? Does it have 2D graphics? Is there physics?)
    /// see https://en.wikipedia.org/wiki/Scene_graph
    class Scene final : public std::enable_shared_from_this<Scene>
    {
        friend std::ostream &operator<< (std::ostream &, const Scene &);
        friend Entity;
      
    public:
        enum class State { Active, Paused };
            
    private:
        const std::string m_Name;
            
        State m_SceneState = State::Active;
            
        std::vector<std::shared_ptr<SceneGraph>> m_SceneGraphs = {};
        std::vector<std::shared_ptr<Entity>> m_Entitys = {};
            
        void OnComponentAddedToAEntity(const std::weak_ptr<Component> &);
        void OnComponentRemovedFromAEntity(const std::weak_ptr<Component> &);
            
        void OnSceneGraphAdded(const std::weak_ptr<SceneGraph> &aSceneGraph);
        void OnSceneGraphRemoved(const std::weak_ptr<SceneGraph> &aSceneGraphRemoved);
            
        void logError();
            
    public:
        std::weak_ptr<Entity> getEntity(const std::string &) const;
        std::string const &getName() const;
        State const &getSceneState() const;
            
        void setState(const State &);
      
        template<class T> std::weak_ptr<T> getSceneGraph()
        {
            static_assert(std::is_base_of<SceneGraph, T>::value == true, "T must be a kind of SceneGraph");
                
            for(auto sceneGraph : m_SceneGraphs)
                if (auto ptr = std::dynamic_pointer_cast<T>(sceneGraph))
                    return std::weak_ptr<T>(ptr);
                
            return std::weak_ptr<T>();
        }
            
        template<class T> std::weak_ptr<SceneGraph> addSceneGraph()
        {
            static_assert(std::is_base_of<SceneGraph, T>::value == true, "T must be a kind of SceneGraph");
                
            auto newT = std::shared_ptr<T>(new T(this));
                
            for(auto sceneGraph : m_SceneGraphs)
                if (std::dynamic_pointer_cast<T>(sceneGraph))
                {
                    logError();
                    return {}; 
                }
                
            m_SceneGraphs.push_back(newT);
                
            return std::weak_ptr<T>(newT);
        }
            
        void update();
        void fixedUpdate();
        void draw(const IntVector2 &aFrameBufferSize);
            
        std::weak_ptr<Entity> addEntity();
      
        Scene &operator=(const Scene &) = delete;
        Scene &operator=(Scene &&) = delete;
      
        Scene(const std::string &aName);
    private:
        Scene() = delete;
        Scene(const Scene &) = delete;
    public:
        Scene(Scene &&) = default;
        ~Scene() = default;
    };

    std::ostream &operator<< (std::ostream &, const Scene &);
}

#endif
