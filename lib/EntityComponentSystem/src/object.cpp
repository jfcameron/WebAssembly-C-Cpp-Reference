// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/object.h>
#include <gdk/component.h>
#include <gdk/logger.h>

#include <iostream>

static constexpr char TAG[] = "Object";

namespace gdk::ecs
{
std::ostream &operator<<(std::ostream &s, const Object &a)
{
    (void)a;
    
    s.clear(); s
    << "{"
    << TAG << "'s: " << "operator<< has not been implemented"
    // << "m_Member: " << a.m_Member << ", "
    << "}";
    
    return s;
}

Object::Object(const std::weak_ptr<Scene> &aScene)
: m_MyScene(aScene)
{}

void Object::update() const
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

void Object::fixedUpdate() const
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

std::weak_ptr<Component> Object::getComponent(const size_t aIndex) const
{
    return m_Components[aIndex];
}

size_t  Object::getComponentCount() const
{
    return m_Components.size();
}

std::string Object::getName() const
{
    return m_Name;
}

std::weak_ptr<Scene> Object::getScene() const
{
    return m_MyScene;
}

void Object::setName(const std::string &aName)
{
    m_Name = aName;
}

void Object::setPosition(const Math::Vector3 &aPosition)
{
    m_Position = aPosition;
}

void Object::setPosition(const float aX,const float aY, const float aZ)
{
    m_Position.x = aX;
    m_Position.y = aY;
    m_Position.z = aZ;
}

void Object::setScale(const Math::Vector3 &aScale)
{
    m_Scale = aScale;
}

void Object::setRotation(const Math::Quaternion &aRotation)
{
    m_Rotation = aRotation;
}

Math::Vector3 Object::getPosition() const
{
    return m_Position;
}

Math::Vector3 Object::getScale() const
{
    return m_Scale;
}

Math::Quaternion Object::getRotation() const
{
    return m_Rotation;
}
}
