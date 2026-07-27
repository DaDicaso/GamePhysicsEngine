#pragma once

namespace omni
{
  struct Color
  {
    float r;
    float g;
    float b;
    float a;

    constexpr Color(
      float red,
      float green,
      float blue,
      float aplha = 1.0f)
        : r(red),
          g(green),
          b(blue),
          a(aplha)
    {
    }

  };
  
} // namespace omni
