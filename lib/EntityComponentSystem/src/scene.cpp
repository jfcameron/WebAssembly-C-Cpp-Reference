// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/scene.h>
//#include <gdk/exception.h>
//#include <gdk/logger.h>
#include <gdk/entity.h>
#include <gdk/scenegraph.h>

#include <iostream>
#include <stdexcept>

static constexpr char TAG[] = "Scene";

namespace gdk
{
std::ostream &operator<<(std::ostream &s, const Scene &a)
{
    s.clear(); s
    << "{"
    << "Scene's: " << "operator<< has not been implemented"
    // << "m_Member: " << a.m_Member << ", "
    << "}";
    
    return s;
}

std::weak_ptr<Entity> Scene::getEntity(const std::string &aEntityName) const
{
    for (auto pEntity : m_Entitys)
        if (pEntity->getName() == aEntityName)
            return std::weak_ptr<Entity>(pEntity);
    
    return std::weak_ptr<Entity>();
}

std::weak_ptr<Entity> Scene::addEntity()
{
    m_Entitys.push_back(std::shared_ptr<Entity>(new Entity(std::weak_ptr<Scene>(shared_from_this()))));
    
    return m_Entitys.back();
}

void Scene::draw(const IntVector2 &aFrameBufferSize)
{
    for (auto pSceneGraph : m_SceneGraphs) pSceneGraph->draw(aFrameBufferSize);
}

void Scene::fixedUpdate()
{
    switch(m_SceneState)
    {
        case State::Active:
            for (auto pEntity : m_Entitys) pEntity->fixedUpdate();
            
            for (auto pScene : m_SceneGraphs) pScene->fixedUpdate();
            
            break;
            
        default: break;
    }
}

void Scene::update()
{
    switch(m_SceneState)
    {
        case State::Active:
            for (auto pEntity : m_Entitys) pEntity->update();
            
            for (auto pSceneGraph : m_SceneGraphs) pSceneGraph->update();
            
            break;
            
        default: break;
    }
}

void Scene::OnComponentAddedToAEntity(const std::weak_ptr<Component> &aComponent)
{
    //parseRequireSceneGraphsAnnotation(aComponent);
    
    for (auto pSceneGraph : m_SceneGraphs) pSceneGraph->OnComponentAddedToAEntity(aComponent);
}

void Scene::OnComponentRemovedFromAEntity(const std::weak_ptr<Component> &)
{
    throw std::runtime_error(std::string(TAG).append("/OnComponentAddedToAEntity not supported"));
}

void Scene::OnSceneGraphAdded(const std::weak_ptr<SceneGraph> &aSceneGraph)
{
    throw std::runtime_error(std::string(TAG).append("/OnSceneGraphRemoved not supported"));
}

void Scene::OnSceneGraphRemoved(const std::weak_ptr<SceneGraph> &aSceneGraphRemoved)
{
    throw std::runtime_error(std::string(TAG).append("/OnSceneGraphRemoved not supported"));
}

void Scene::logError()
{
    //Debug::error(TAG, "user attempted to add a duplicate kind of scenegraph to the scene: ",m_Name);
    /// why???????
}

Scene::Scene(const std::string &aName)
: m_Name(aName)
{}
}
