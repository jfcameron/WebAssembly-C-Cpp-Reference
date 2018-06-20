// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/gameobject.h>
#include <gdk/component.h>
#include <gdk/logger.h>

#include <iostream>

static constexpr char TAG[] = "GameObject";

namespace gdk::ecs
{
std::ostream &operator<<(std::ostream &s, const GameObject &a)
{
    (void)a;
    
    s.clear(); s
    << "{"
    << TAG << "'s: " << "operator<< has not been implemented"
    // << "m_Member: " << a.m_Member << ", "
    << "}";
    
    return s;
}

GameObject::GameObject(const std::weak_ptr<Scene> &aScene)
: m_MyScene(aScene)
{}

void GameObject::update() const
{
    for (auto component : m_Components)
    {
        if (!component->m_DidInit)
        {
            component->initialize();
            component->m_DidInit = true;
        }
        
        component->update();
    }
}

void GameObject::fixedUpdate() const
{
    for (auto component : m_Components)
    {
        if (!component->m_DidInit)
        {
            component->initialize();
            component->m_DidInit = true;
        }
            
        component->fixedUpdate();
    }
}

std::weak_ptr<Component> GameObject::getComponent(const size_t aIndex) const
{
    return m_Components[aIndex];
}

size_t  GameObject::getComponentCount() const
{
    return m_Components.size();
}

std::string GameObject::getName() const
{
    return m_Name;
}

std::weak_ptr<Scene> GameObject::getScene() const
{
    return m_MyScene;
}

void GameObject::setName(const std::string &aName)
{
    m_Name = aName;
}

void GameObject::setPosition(const Math::Vector3 &aPosition)
{
    m_Position = aPosition;
}

void GameObject::setPosition(const float aX,const float aY, const float aZ)
{
    m_Position.x = aX;
    m_Position.y = aY;
    m_Position.z = aZ;
}

void GameObject::setScale(const Math::Vector3 &aScale)
{
    m_Scale = aScale;
}

void GameObject::setRotation(const Math::Quaternion &aRotation)
{
    m_Rotation = aRotation;
}

Math::Vector3 GameObject::getPosition() const
{
    return m_Position;
}

Math::Vector3 GameObject::getScale() const
{
    return m_Scale;
}

Math::Quaternion GameObject::getRotation() const
{
    return m_Rotation;
}
}
