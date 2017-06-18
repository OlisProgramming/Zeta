#include "image_load.h"

namespace zeta {
	namespace util {

		IMAGE_DATA loadImage(const char* filename, unsigned int& width, unsigned int& height, FIBITMAP** dib_ref) {

			//image format
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			//pointer to the image, once loaded
			FIBITMAP *dib = nullptr;
			//pixels of image
			BYTE* bits = nullptr;

			//check the file signature and deduce its format
			fif = FreeImage_GetFileType(filename, 0);
			//if still unknown, try to guess the file format from the file extension
			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(filename);
			//if still unkown, return failure
			if (fif == FIF_UNKNOWN)
				return nullptr;

			//check that the plugin has reading capabilities and load the file
			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, filename);
			//if the image failed to load, return failure
			if (!dib)
				return nullptr;

			//retrieve the image data
			bits = FreeImage_GetBits(dib);
			//get the image width and height
			width = FreeImage_GetWidth(dib);
			height = FreeImage_GetHeight(dib);
			//if this somehow one of these failed (they shouldn't), return failure
			if ((bits == 0) || (width == 0) || (height == 0))
				return nullptr;

			*dib_ref = dib;
			return bits;
		}

		void flipBlueRed(IMAGE_DATA data, unsigned int width, unsigned int height) {

			for (unsigned int i = 0; i < width * height * 4; i += 4) {
				BYTE r = data[i + 0];
				BYTE g = data[i + 1];
				BYTE b = data[i + 2];
				BYTE a = data[i + 3];

				data[i + 0] = b;
				data[i + 1] = g;
				data[i + 2] = r;
				data[i + 3] = a;
			}
		}

		void flipY(IMAGE_DATA data, unsigned int width, unsigned int height) {

			IMAGE_DATA newData = new BYTE[width * height * 4];
			memcpy(newData, data, width * height * 4);

			for (unsigned int x = 0; x < width; ++x) {
				for (unsigned int y = 0; y < height; ++y) {
					
					unsigned int y_ = height - y - 1;
					unsigned int initial = (y*width + x) * 4;
					unsigned int changed = (y_*width + x) * 4;
					
					BYTE r = newData[initial + 0];
					BYTE g = newData[initial + 1];
					BYTE b = newData[initial + 2];
					BYTE a = newData[initial + 3];

					data[changed + 0] = r;
					data[changed + 1] = g;
					data[changed + 2] = b;
					data[changed + 3] = a;
				}
			}

			delete newData;
		}
	}
}