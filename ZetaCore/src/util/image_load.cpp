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
	}
}