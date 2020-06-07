#pragma once
#include "image.h"
#include "async_operation.h"

namespace imageoperations {

	class ImageSubtraction : public AsyncOperation
	{
	public:

		ImageSubtraction();
		~ImageSubtraction();

		/*
		* Subtract (pixelwise) the second image from the first one and write the difference image with the given file name.
		*
		* @param img1 first source image
		* @param img2 second source image
		* @param result_image difference image
		* @return status true if subtracted successfully, false if any error occured
		*/
		bool Subtract(const Image& _img1, const Image& _img2, Image& _result_image);

		/*
		* Asynchronous subtraction. Subtract (pixelwise) the second image from the first one and write the difference image 
		* with the given file name. The sources are divided into rois to be processed in parallel.
		* Each thread processes own roi and notifies this function once it's done. Function releases 
		* the main thread when all threads complete the operation.
		*
		* @param img1 first source image
		* @param img2 second source image
		* @param result_image difference image
		* @return status true if subtracted successfully, false if any error occured
		*/
		bool SubtractAysnc(const Image& _img1, const Image& _img2, Image* _result_image);

	private:

		/*
		* Apply image subtraction to the given roi. Used in async operation.
		*
		* @param index index of the thread to calculate corresponding roi on the image.
		*/
		void SubtractRoi(const int& _index);

	private:
		// first source image (stored to be used in async mode)
		Image m_source1;
		// second source image (stored to be used in async mode)
		Image m_source2;
		// difference image (stored to be used in async mode)
		Image* m_result;
		// image width & height
		size_t m_width;
		size_t m_height;
		bool m_size_initialized;
		// mutex to control write operation of the result image
		static std::mutex m_result_mutex;	
	};
}