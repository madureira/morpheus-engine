#pragma once

namespace Morpheus {

    struct SizeComponent final
    {
        float width = 0.0f;
        float height = 0.0f;

        SizeComponent(float w, float h)
            : width(w)
            , height(h)
        {
        }
    };

}

