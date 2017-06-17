#pragma once

#include <FreeImage.h>

namespace zeta {
	namespace util {

		typedef BYTE* IMAGE_DATA;

		// Remember to FreeImage_Unload() the dib's data after you're done with it!
		IMAGE_DATA loadImage(const char* path, unsigned int& width, unsigned int& height, FIBITMAP** dib_ref);

		void flipBlueRed(IMAGE_DATA data, unsigned int width, unsigned int height);

		void flipY(IMAGE_DATA data, unsigned int width, unsigned int height);
	}
}