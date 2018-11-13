// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/scene.h>
#include <gdk/exception.h>
#include <gdk/logger.h>
#include <gdk/object.h>
#include <gdk/scenegraph.h>

#include <iostream>

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

std::weak_ptr<Object> Scene::getObject(const std::string &aObjectName) const
{
    for (auto pObject : m_Objects)
        if (pObject->getName() == aObjectName)
            return std::weak_ptr<Object>(pObject);
    
    return std::weak_ptr<Object>();
}

std::weak_ptr<Object> Scene::addObject()
{
    m_Objects.push_back(std::shared_ptr<Object>(new Object(std::weak_ptr<Scene>(shared_from_this()))));
    
    return m_Objects.back();
}

void Scene::draw(const Math::IntVector2 &aFrameBufferSize)
{
    for (auto pSceneGraph : m_SceneGraphs) pSceneGraph->draw(aFrameBufferSize);
}

void Scene::fixedUpdate()
{
    switch(m_SceneState)
    {
        case State::Active:
            for (auto pObject : m_Objects) pObject->fixedUpdate();
            
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
            for (auto pObject : m_Objects) pObject->update();
            
            for (auto pSceneGraph : m_SceneGraphs) pSceneGraph->update();
            
            break;
            
        default: break;
    }
}

void Scene::OnComponentAddedToAObject(const std::weak_ptr<Component> &aComponent)
{
    //parseRequireSceneGraphsAnnotation(aComponent);
    
    for (auto pSceneGraph : m_SceneGraphs) pSceneGraph->OnComponentAddedToAObject(aComponent);
}

void Scene::OnComponentRemovedFromAObject(const std::weak_ptr<Component> &)
{
    throw gdk::Exception(TAG, "OnComponentAddedToAObject not supported");
}

void Scene::OnSceneGraphAdded(const std::weak_ptr<SceneGraph> &aSceneGraph)
{
    throw gdk::Exception(TAG, "OnSceneGraphRemoved not supported");
}

void Scene::OnSceneGraphRemoved(const std::weak_ptr<SceneGraph> &aSceneGraphRemoved)
{
    throw gdk::Exception(TAG, "OnSceneGraphRemoved not supported");
}

void Scene::logError()
{
    Debug::error(TAG, "user attempted to add a duplicate kind of scenegraph to the scene: ",m_Name);
}

Scene::Scene(const std::string &aName)
: m_Name(aName)
{}
}
