#include "mepch.h"
#include "ImageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Morpheus {

    void ImageLoader::Load(const char* imagePath, bool flipVertically, Image& image)
    {
        stbi_set_flip_vertically_on_load(flipVertically);

        image.pixels = stbi_load(imagePath, &image.width, &image.height, &image.channels, STBI_rgb_alpha);

        if (!image.pixels)
        {
            ME_LOG_ERROR("ImageLoader: Fail to load the image {0}", imagePath);
        }
    }

    void ImageLoader::FreeImage(Image& image)
    {
        stbi_image_free(image.pixels);
    }

}
