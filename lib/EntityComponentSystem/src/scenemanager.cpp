// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/scenemanager.h>

#include <iostream>

namespace gdk
{
static constexpr char TAG[] = "SceneManager";

std::ostream &operator<<(std::ostream &s, const SceneManager &a)
{    
    s.clear(); s
    << "{"
    << TAG << "'s: " << "operator<< has not been implemented"
    // << "m_Member: " << a.m_Member << ", "
    << "}";
    
    return s;
}

std::weak_ptr<Scene> SceneManager::addScene(const std::string &aName)
{
    auto newScene = std::make_shared<Scene>(Scene(aName));

    m_Scenes.insert({aName,newScene});
    
    return std::weak_ptr<Scene>(newScene);
}

std::weak_ptr<Scene> SceneManager::getScene(const std::string &aName) const
{
    return std::weak_ptr<Scene>(m_Scenes.at(aName));
}

void SceneManager::update()
{
    for (auto &pair : m_Scenes) pair.second->update();
}

void SceneManager::fixedUpdate()
{
    for (auto &pair : m_Scenes) pair.second->fixedUpdate();
}

void SceneManager::draw(const IntVector2 &aFrameBufferSize)
{
    for (auto &pair : m_Scenes) pair.second->draw(aFrameBufferSize);
}

void SceneManager::remove(const std::string &aName)
{
    m_Scenes.erase(aName);
}
}
