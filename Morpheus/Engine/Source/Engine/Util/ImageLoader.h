#pragma once

namespace Morpheus {

	struct Image
	{
		int width;
		int height;
		int channels;
		unsigned char* pixels;

		Image()
			: width(0)
			, height(0)
			, channels(0)
			, pixels(nullptr)
		{
		}
	};

	class ImageLoader
	{
	public:
		static void Load(const char* imagePath, bool flipVertically, Image& image);
		static void FreeImage(Image& image);
	};

}
