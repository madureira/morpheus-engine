#pragma once

namespace Morpheus {

    struct ColorComponent final
    {
        float r;
        float g;
        float b;
        float a;

        ColorComponent(float red, float green, float blue, float alpha)
            : r(red)
            , g(green)
            , b(blue)
            , a(alpha)
        {
        }
    };

}
