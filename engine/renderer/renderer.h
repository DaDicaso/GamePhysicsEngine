#pragma once

#include "engine/math/vector3.h"

#include "engine/debug/Colors.h"
#include "engine/debug/DebugDraw.h"

namespace omni{

  class Window;

  class Renderer{
    public:
    

      Renderer(Window& window);

      DebugDraw& getDebugDraw(){
        return mDebugDraw;
      }

      void initialize();

      void beginFrame();

      void endFrame();

      void setClearColor(
        float red,
        float green,
        float blue,
        float aplha
      );

      void drawPoint(
        const Vector3& position,
        const Color& color = Colors::White,
        float size = 12.0f);

        
      void drawLine(
        const Vector3& start,
        const Vector3& end,
        const Color& color = Colors::White,
        float width = 1.0f);

    private:
    
      Window& mWindow;
      float mClearColor[4];

      DebugDraw mDebugDraw;
  };
}