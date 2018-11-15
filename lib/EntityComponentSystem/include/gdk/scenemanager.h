// © 2017 Joseph Cameron - All Rights Reserved

#ifndef GDK_ECS_SCENEMANAGER_H
#define GDK_ECS_SCENEMANAGER_H

#include <gdk/scene.h>

#include <iosfwd>
#include <string>
#include <memory>
#include <map>

namespace gdk
{
    /// \brief No description provided for SceneManager
    class SceneManager final
    {
        friend std::ostream& operator<< (std::ostream &, const SceneManager &);
      
        std::map<std::string, std::shared_ptr<Scene>> m_Scenes = {};

    public:
        std::weak_ptr<Scene> addScene(const std::string &aName);
        std::weak_ptr<Scene> getScene(const std::string &aName) const;
            
        void remove(const std::string &aName);
            
        void update();
        void fixedUpdate();
        void draw(const IntVector2 &aFrameBufferSize);
            
        SceneManager &operator=(const SceneManager &) = delete;
        SceneManager &&operator=(SceneManager &&) = delete;
            
        SceneManager() = default;
        SceneManager(const SceneManager &) = delete;
        SceneManager(SceneManager &&) = default;
        ~SceneManager() = default;
    };

    std::ostream &operator<< (std::ostream &, const SceneManager &);
}

#endif
