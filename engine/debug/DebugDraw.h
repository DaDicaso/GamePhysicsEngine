#pragma once

#include "engine/math/vector3.h"
#include "engine/debug/Color.h"
#include "engine/debug/Colors.h"

namespace omni
{
  class Renderer;

  class DebugDraw{
    public:

      explicit DebugDraw(Renderer& renderer);

      void point(
        const Vector3& position,
        const Color& color = Colors::White,
        float size = 12.0f
      );

      void line(
        const Vector3& start,
        const Vector3& end,
        const Color& color,
        float width
      );

      void sphere(
        DebugDraw& debug,
        const Vector3& centre,
        const real radius,
        const Color& color
      );
      
    private:

      Renderer& mRenderer;

  };
} // namespace omni
