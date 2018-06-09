// © 2018 Joseph Cameron - All Rights Reserved

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
        //! Describes camera clear behaviour
        enum class ClearMode {Nothing, Color, DepthOnly};
            
        //! The camera's projection mode
        enum class ProjectionMode {Perspective, Orthographic};
            
    private:
        gdk::Mat4x4 m_ViewMatrix =       gdk::Mat4x4::Identity; //!< World position of camera
        gdk::Mat4x4 m_ProjectionMatrix = gdk::Mat4x4::Identity; //!< Projection of the camera
            
        ClearMode  m_ClearMode =  ClearMode::Color;      //!< Determines which buffers in the FBO to clear before drawing
        gdk::Color m_ClearColor = Color::CornflowerBlue; //!< The color to replace all data in the color buffer with (if color buffer is to be cleared)
            
        gdk::Vector2 m_ViewportPosition = gdk::Vector2::Zero;   //!< position of the camera viewport within the device viewport
        gdk::Vector2 m_ViewportSize =     gdk::Vector2(1., 1.); //!< size of camera viewport within the device viewport

        //This is a bit logically messy. I dont know if this approach for generating the projection matrix is as legible as possible.
        ProjectionMode m_ProjectionMode =    ProjectionMode::Perspective;
        gdk::Vector2   m_OrthoSize =         {10, 10};
        float          m_FieldOfView =       90.;
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
            
        void setToOrthographicProjection(const gdk::Vector2 &aOrthoSize, const float aNearClippingPlane, const float aFarClippingPlane, const float aViewportAspectRatio);            
        void setToPerspectiveProjection(const float aFieldOfView, const float aNearClippingPlane, const float aFarClippingPlane, const float aViewportAspectRatio);
        const gdk::Mat4x4 &getProjectionMatrix() const;
             
        void setViewMatrix(const gdk::Vector3 &aWorldPos, const gdk::Quaternion &aRotation);
        const gdk::Mat4x4 &getViewMatrix() const;

        void setClearColor(const gdk::Color &aColor);
            
        //! \Warn "draw" is misleading. It sets up the viewport and calculates view & projection mats. It preps for draw.
        void draw(const gdk::IntVector2 &aFrameBufferSize);
            
        Camera& operator=(const Camera &) = delete;
        Camera& operator=(Camera &&) = delete;
      
        Camera();
        Camera(const Camera &) = delete;
        Camera(Camera &&) = default;
        ~Camera() = default;
    };

    std::ostream &operator<< (std::ostream &, const Camera &);
}

#endif
