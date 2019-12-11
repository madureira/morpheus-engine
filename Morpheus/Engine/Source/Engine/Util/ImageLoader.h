#pragma once

namespace Morpheus {

	struct Image
	{
		int width;
		int height;
		int channels;
		unsigned char* pixels;

		Image()
			: width(0),
			height(0),
			channels(0),
			pixels(nullptr)
		{
		}
	};

	class ImageLoader
	{
	public:
		static Image Load(const char* imagePath, bool flipVertically);
		static void FreeImage(Image& image);
	};

}
