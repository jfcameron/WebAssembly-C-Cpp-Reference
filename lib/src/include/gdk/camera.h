// © 2018 Joseph Cameron - All Rights Reserved
// Created on 2017-06-25.
#ifndef gdk_GFX_CAMERA_H
#define gdk_GFX_CAMERA_H

#include "gdk/color.h"
#include "gdk/vector2.h"
#include "gdk/mat4x4.h"

#include <iosfwd>

namespace gdk
{
    struct IntVector2;
    struct Vector3;   
    struct Quaternion;
    
    /*!
      Position, orientation and perspective from which Model(s) are drawn
    */
    class Camera final
    {
        friend std::ostream &operator<< (std::ostream &, const Camera &);
            
    public:
        /// Describes camera clear behaviour
        enum class ClearMode {Nothing, Color, DepthOnly};
            
        /// The camera's projection mode
        enum class ProjectionMode {Perspective, Orthographic};
            
    private:
        // Data members
        gdk::Mat4x4 m_ViewMatrix        = gdk::Mat4x4::Identity;
        gdk::Mat4x4 m_ProjectionMatrix  = gdk::Mat4x4::Identity;
            
        ClearMode  m_ClearMode         = ClearMode::Color;
        gdk::Color m_ClearColor        = Color::CornflowerBlue;
            
        gdk::Vector2 m_ViewportPosition  = gdk::Vector2::Zero;
        gdk::Vector2 m_ViewportSize      = gdk::Vector2(1., 1.);
            
        ProjectionMode m_ProjectionMode    = ProjectionMode::Perspective;
        gdk::Vector2   m_OrthoSize         = {10, 10};
        float          m_FieldOfView       = 90.;
        float          m_NearClippingPlane = 0.001f;
        float          m_FarClippingPlane  = 20.;
            
        //RenderTexture m_RenderTexture;
            
    public:
        // Accessors
        void setViewportPosition(const gdk::Vector2 &);
        void setViewportPosition(const float x, const float y);
        gdk::Vector2 getViewportPosition() const;
            
        void setViewportSize(const gdk::Vector2 &);
        void setViewportSize(const float x, const float y);
        gdk::Vector2 getViewportSize() const;
            
        void setOrthographicProjection(
            const gdk::Vector2 &aOrthoSize, const float aNearClippingPlane,
            const float aFarClippingPlane, const float aViewportAspectRatio);
            
        void setPerspectiveProjection(
            const float aFieldOfView, const float aNearClippingPlane,
            const float aFarClippingPlane, const float aViewportAspectRatio);
            
        const gdk::Mat4x4 &getProjectionMatrix() const;
             
        void setViewMatrix(const gdk::Vector3 &aWorldPos, const gdk::Quaternion &aRotation);
        const gdk::Mat4x4 &getViewMatrix() const;
            
        // Public methods
        void draw(const gdk::IntVector2 &aFrameBufferSize);
            
        // Mutating operators
        Camera& operator=(const Camera &) = delete;
        Camera& operator=(Camera &&) = delete;
      
        // Constructors, destructors
        Camera();
        Camera(const Camera &) = delete;
        Camera(Camera &&) = default;
        ~Camera() = default;
    };

    std::ostream &operator<< (std::ostream &, const Camera &);
}

#endif
