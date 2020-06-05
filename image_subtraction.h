#pragma once
#include "image.h"

namespace imageoperations {

	class ImageSubtraction
	{
	public:

		ImageSubtraction();
		~ImageSubtraction();

		/*
		* Subtract second image from first image and write difference image with the given file name.
		*
		* @param img1 source image
		* @param img2 source image
		* @param result_image difference image
		* @return status true if subtracted successfully, false if any error occured
		*/
		bool Subtract(const Image& _img1, const Image& _img2, Image& _result_image);	

	private:

	};
}