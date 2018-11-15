// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/entity.h>
#include <gdk/component.h>
//#include <gdk/logger.h>

#include <iostream>

static constexpr char TAG[] = "Entity";

namespace gdk
{
std::ostream &operator<<(std::ostream &s, const Entity &a)
{
    (void)a;
    
    s.clear(); s
    << "{"
    << TAG << "'s: " << "operator<< has not been implemented"
    // << "m_Member: " << a.m_Member << ", "
    << "}";
    
    return s;
}

Entity::Entity(const std::weak_ptr<Scene> &aScene)
: m_MyScene(aScene)
{}

void Entity::update() const
{
    for (auto &component : m_Components)
    {
        if (!component->m_DidInit)
        {
            component->initialize();
            component->m_DidInit = true; // this breaks basic encapsulation rules.
        }
        
        component->update();
    }
}

void Entity::fixedUpdate() const
{
    for (auto component : m_Components)
    {
        if (!component->m_DidInit)
        {
            component->initialize();
            component->m_DidInit = true; // this breaks basic encapsulation rules.
        }
            
        component->fixedUpdate();
    }
}

std::weak_ptr<Component> Entity::getComponent(const size_t aIndex) const
{
    return m_Components[aIndex];
}

size_t  Entity::getComponentCount() const
{
    return m_Components.size();
}

std::string Entity::getName() const
{
    return m_Name;
}

std::weak_ptr<Scene> Entity::getScene() const
{
    return m_MyScene;
}

void Entity::setName(const std::string &aName)
{
    m_Name = aName;
}

void Entity::setPosition(const Vector3 &aPosition)
{
    m_Position = aPosition;
}

void Entity::setPosition(const float aX,const float aY, const float aZ)
{
    m_Position.x = aX;
    m_Position.y = aY;
    m_Position.z = aZ;
}

void Entity::setScale(const Vector3 &aScale)
{
    m_Scale = aScale;
}

void Entity::setRotation(const Quaternion &aRotation)
{
    m_Rotation = aRotation;
}

Vector3 Entity::getPosition() const
{
    return m_Position;
}

Vector3 Entity::getScale() const
{
    return m_Scale;
}

Quaternion Entity::getRotation() const
{
    return m_Rotation;
}
}
