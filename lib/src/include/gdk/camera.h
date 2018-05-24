// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 2017-06-25.
#ifndef GDK_GFX_CAMERA_H
#define GDK_GFX_CAMERA_H

//gdk inc
#include "gdk/color.h"
#include "gdk/vector2.h"
#include "gdk/mat4x4.h"
//std inc
#include <iosfwd>

namespace GDK{struct IntVector2;}
namespace GDK{struct Vector3;   }
namespace GDK{struct Quaternion;}

namespace GDK
{
    namespace GFX
    {
        /*!
         Position, orientation and perspective from which Model(s) are drawn
         */
        class Camera final
        {
            friend std::ostream &operator<< (std::ostream &, const GFX::Camera &);
            
        public:
            /// Describes camera clear behaviour
            enum class ClearMode
            {
                Nothing,
                Color,
                DepthOnly
            };
            
            /// The camera's projection mode
            enum class ProjectionMode
            {
                Perspective,
                Orthographic
            };
            
        private:
            // Data members
/*            Math::Mat4x4   m_ViewMatrix        = Math::Mat4x4::Identity;
              Math::Mat4x4   m_ProjectionMatrix  = Math::Mat4x4::Identity;*/
            
            ClearMode      m_ClearMode         = ClearMode::Color;
            gdk::Color     m_ClearColor        = Color::CornflowerBlue;
            
            gdk::Vector2  m_ViewportPosition  = gdk::Vector2::Zero;
            gdk::Vector2  m_ViewportSize      = gdk::Vector2(1.,1.);
            
            ProjectionMode m_ProjectionMode    = ProjectionMode::Perspective;
            gdk::Vector2  m_OrthoSize         = {10,10};
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
            
            //void setOrthographicProjection(const gdk::Vector2 &aOrthoSize, const float &aNearClippingPlane, const float &aFarClippingPlane, const float &aViewportAspectRatio);
            //void setPerspectiveProjection(const float &aFieldOfView, const float &aNearClippingPlane, const float &aFarClippingPlane, const float &aViewportAspectRatio);
            /*const Math::Mat4x4 &getProjectionMatrix() const;
            
            void setViewMatrix(const Math::Vector3 &aWorldPos, const Math::Quaternion &aRotation);
            const Math::Mat4x4 &getViewMatrix() const;*/
            
            // Public methods
            void draw(const GDK::IntVector2 &aFrameBufferSize);
            
            // Mutating operators
            Camera& operator=(const Camera &) = delete;
            Camera& operator=(Camera &&) = delete;
      
            // Constructors, destructors
            Camera();
            Camera(const Camera &) = delete;
            Camera(Camera &&) = default;
            ~Camera() = default;
        };

        std::ostream &operator<< (std::ostream &, const GFX::Camera &);
    }
}

#endif
