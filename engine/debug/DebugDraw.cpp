#include "engine/debug/DebugDraw.h"
#include "engine/renderer/renderer.h"

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
} // namespace omni
