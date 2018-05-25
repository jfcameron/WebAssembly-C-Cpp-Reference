// © 2018 Joseph Cameron - All Rights Reserved
// Project: gdk
// Created on 2017-06-27.
#include <gdk/quaternion.h>
#include <gdk/vector3.h>
#include <gdk/trigonometry.h>

#include <glm/gtc/quaternion.hpp>

#include <iostream>

using namespace gdk;

//static const
const Quaternion Quaternion::Identity = Quaternion();

//stringify
std::ostream &gdk::operator<< (std::ostream &s, const gdk::Quaternion &a)
{
    s.clear(); s
    << "{"
    << "x: " << a.x << ", "
    << "y: " << a.y << ", "
    << "z: " << a.z << ", "
    << "w: " << a.w
    << "}";
    
    return s;
}

//ctors
Quaternion::Quaternion() : x(0.f), y(0.f), z(0.f), w(1.f)
{}

Quaternion::Quaternion(const Vector3 &aEulerAngles)
{
    setFromEuler(aEulerAngles);
}

//Euler convenience
void Quaternion::setFromEuler(const Vector3 &aEulerAngles)
{
    /*Vector3 eulerAngles = aEulerAngles;
    
    glm::quat quat;
    
    quat = glm::rotate(quat, eulerAngles.x, glm::vec3(1.f, 0.f, 0.f));
    quat = glm::rotate(quat, eulerAngles.y, glm::vec3(0.f, 1.f, 0.f));
    quat = glm::rotate(quat, eulerAngles.z, glm::vec3(0.f, 0.f, 1.f));*/
    
    /*glm::quat qPitch = glm::angleAxis(aEulerAngles.x, glm::vec3(1.f, 0.f, 0.f));
    glm::quat qYaw   = glm::angleAxis(aEulerAngles.y, glm::vec3(0.f, 1.f, 0.f));
    glm::quat qRoll  = glm::angleAxis(aEulerAngles.z, glm::vec3(0.f, 0.f, 1.f));
    
    glm::quat quat = qRoll *qPitch * qYaw;*/
    
    
    //convert from euler to radian
    glm::vec3 buff = {aEulerAngles.x, aEulerAngles.y, aEulerAngles.z};
    
    //buff.x *= gdk::Trig::PI/180.f;
    //buff.y *= gdk::Trig::PI/180.f;
    //buff.z *= gdk::Trig::PI/180.f;
    
    glm::quat quat(buff);
    
    
    x = quat.x;
    y = quat.y;
    z = quat.z;
    w = quat.w;
}

Vector3 Quaternion::toEuler() const
{
    glm::quat quaternion(w, x, y, z);
    
    //convert from radian to euler
    glm::vec3 buff = glm::eulerAngles(quaternion);
    
    /*buff.x *= 180.f/gdk::Trig::PI;
    buff.y *= 180.f/gdk::Trig::PI;
    buff.z *= 180.f/gdk::Trig::PI;*/
    
    
    return {buff.x, buff.y, buff.z};
}
