// © 2017 Joseph Cameron - All Rights Reserved
// Created on 2017-06-25.
#include <iostream>

#include <gdk/opengl.h>
#include <gdk/glh.h>
#include <gdk/camera.h>
#include <gdk/color.h>
#include <gdk/exception.h>
#include <gdk/intvector2.h>
#include <gdk/mat4x4.h>
#include <gdk/quaternion.h>
#include <gdk/vector2.h>
#include <gdk/vector3.h>

using namespace gdk;
using namespace GFX;

static constexpr char TAG[] = "Camera";

std::ostream &gdk::GFX::operator<<(std::ostream &s, const GFX::Camera &a)
{
    s.clear(); s
    << "{"
    << "m_ViewMatrix:\n"       << a.m_ViewMatrix        // << ", "
    << "m_ProjectionMatrix:\n" << a.m_ProjectionMatrix  // << ", "
    << "m_ViewportPosition: "  << a.m_ViewportPosition  << ", "
    << "m_ViewportSize: "      << a.m_ViewportSize      << ", "
    << "m_FieldOfView: "       << a.m_FieldOfView       << ", "
    << "m_NearClippingPlane: " << a.m_NearClippingPlane << ", "
    << "m_FarClippingPlane: "  << a.m_FarClippingPlane
    << "}";
    
    return s;
}

Camera::Camera()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);   
}

static inline void calculateOrthographicProjection(gdk::Mat4x4 &aProjectionMatrix, const gdk::Vector2 &aOrthoSize, const float aNearClippingPlane, const float aFarClippingPlane, const float aViewportAspectRatio)
{
    (void)aProjectionMatrix;
    (void)aOrthoSize;
    (void)aNearClippingPlane;
    (void)aFarClippingPlane;
    (void)aViewportAspectRatio;
    
    throw gdk::Exception(TAG, "Camera::setOrthographicProjection not implemented!");
}

static inline void calculatePerspectiveProjection(gdk::Mat4x4& aProjectionMatrix, const float aFieldOfView, const float aNearClippingPlane, const float aFarClippingPlane, const float aViewportAspectRatio)
{
    aProjectionMatrix.setPerspective(aFieldOfView, aNearClippingPlane, aFarClippingPlane, aViewportAspectRatio);
}

void Camera::draw(const gdk::IntVector2 &aFrameBufferSize)
{
    gdk::IntVector2 viewportPixelPosition(aFrameBufferSize * m_ViewportPosition);
    gdk::IntVector2 viewportPixelSize    (aFrameBufferSize * m_ViewportSize);
    
    glh::Viewport(viewportPixelPosition, viewportPixelSize);
    glh::Scissor (viewportPixelPosition, viewportPixelSize);
    
    switch(m_ProjectionMode)
    {
        case ProjectionMode::Perspective:
            calculatePerspectiveProjection(m_ProjectionMatrix,m_FieldOfView,m_NearClippingPlane,m_FarClippingPlane,m_ViewportSize.getAspectRatio());
            break;
            
        case ProjectionMode::Orthographic:
            calculateOrthographicProjection(m_ProjectionMatrix,m_OrthoSize,m_NearClippingPlane,m_FarClippingPlane,m_ViewportSize.getAspectRatio());
            break;
    }
    
    switch(m_ClearMode)
    {
        case ClearMode::Color:
            glh::ClearColor(m_ClearColor);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            break;
            
        case ClearMode::DepthOnly:
            glClear(GL_DEPTH_BUFFER_BIT);
            break;
            
        default:
            case ClearMode::Nothing:
            break;
    }
}

void Camera::setViewMatrix(const gdk::Vector3 &aWorldPos, const gdk::Quaternion &aRotation)
{
    m_ViewMatrix.setIdentity();
    m_ViewMatrix.rotate({aRotation.toEuler() * -1.f});
    m_ViewMatrix.translate(aWorldPos * -1.f);
}

void Camera::setViewportPosition(const gdk::Vector2 &a)
{
    m_ViewportPosition = a;
}

void Camera::setViewportPosition(const float x, const float y)
{
    m_ViewportPosition.x = x;
    m_ViewportPosition.y = y;
}

gdk::Vector2 Camera::getViewportPosition() const
{
    return m_ViewportPosition;
}

void Camera::setViewportSize(const gdk::Vector2 &a)
{
    m_ViewportSize = a;
}
    
void Camera::setViewportSize(const float x, const float y)
{
    m_ViewportSize.x = x;
    m_ViewportSize.y = y;
}

gdk::Vector2 Camera::getViewportSize() const
{
    return m_ViewportSize;
}

const gdk::Mat4x4 &Camera::getProjectionMatrix() const
{
    return m_ProjectionMatrix;
}

const gdk::Mat4x4 &Camera::getViewMatrix() const
{
    return m_ViewMatrix;
}
