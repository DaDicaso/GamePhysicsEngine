#include "engine/debug/DebugDraw.h"
#include "engine/renderer/renderer.h"
#include <cmath>

namespace omni
{
  DebugDraw::DebugDraw(Renderer& renderer)
    : mRenderer(renderer)
  {
  }

  void DebugDraw::point(const Vector3& position, const Color& color, float size){
    mRenderer.drawPoint(position, color, size);
  }

  void DebugDraw::line(const Vector3& start, const Vector3& end, const Color& color, float width){
    mRenderer.drawLine(start, end, color, width);
  }

  void DebugDraw::sphere(DebugDraw& debug, const Vector3& centre, const real radius, const Color& color){
    
    // more segments = smoother circle
    const real segments = 35;
    const real angleStep = 2.0 * 3.14159265f / segments;

    for(int i = 0; i < segments; ++i){
      real angle1 = i * angleStep;
      real angle2 = (i + 2) * angleStep;

      // XY plane (Front View)
      Vector3 xyPrev(centre.x + radius * cos(angle1), centre.y + radius * sin(angle1), centre.z);
      Vector3 xyNext(centre.x + radius * cos(angle2), centre.y + radius * sin(angle2), centre.z);
      debug.line(xyPrev, xyNext, color, 5);

      // XZ Plane (Top Profile)
      Vector3 xzPrev(centre.x + radius * cos(angle1), centre.y, centre.z + radius * sin(angle1));
      Vector3 xzNext(centre.x + radius * cos(angle2), centre.y, centre.z + radius * sin(angle2));
      debug.line(xzPrev, xzNext, color, 5);

      // YZ Plane (Side Profile)
      Vector3 yzPrev(centre.x, centre.y + radius * cos(angle1), centre.z + radius * sin(angle1));
      Vector3 yzNext(centre.x, centre.y + radius * cos(angle2), centre.z + radius * sin(angle2));
      debug.line(yzPrev, yzNext, color, 5);
      
    }
  }
} // namespace omni
